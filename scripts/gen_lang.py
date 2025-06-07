#!/usr/bin/env python3
import argparse
import json
import os

HEADER_TEMPLATE = """// Auto-generated language config
#pragma once

#include <string_view>

#ifndef {lang_code_for_font}    #define {lang_code_for_font}  // 기본 언어
#endif

namespace Lang {{
    // 언어 메타데이터
    constexpr const char* CODE = "{lang_code}";

    // 문자열 리소스
    namespace Strings {{
{strings}
    }}

    // 음향 효과 리소스
    namespace Sounds {{
{sounds}
    }}
}}
"""

def generate_header(input_path, output_path):
    with open(input_path, 'r', encoding='utf-8') as f:
        data = json.load(f)    # 데이터 구조 검증
    if 'language' not in data or 'strings' not in data:
        raise ValueError("Invalid JSON structure")

    lang_code = data['language']['type']

    # 문자열 상수 생성
    strings = []
    sounds = []
    for key, value in data['strings'].items():
        value = value.replace('"', '\\"')
        strings.append(f'        constexpr const char* {key.upper()} = "{value}";')

    # 음향 효과 상수 생성
    for file in os.listdir(os.path.dirname(input_path)):
        if file.endswith('.p3'):
            base_name = os.path.splitext(file)[0]
            sounds.append(f'''
        extern const char p3_{base_name}_start[] asm("_binary_{base_name}_p3_start");
        extern const char p3_{base_name}_end[] asm("_binary_{base_name}_p3_end");
        static const std::string_view P3_{base_name.upper()} {{
        static_cast<const char*>(p3_{base_name}_start),
        static_cast<size_t>(p3_{base_name}_end - p3_{base_name}_start)
        }};''')    
    # 공통 음향 효과 생성
    for file in os.listdir(os.path.join(os.path.dirname(output_path), 'common')):
        if file.endswith('.p3'):
            base_name = os.path.splitext(file)[0]
            sounds.append(f'''
        extern const char p3_{base_name}_start[] asm("_binary_{base_name}_p3_start");
        extern const char p3_{base_name}_end[] asm("_binary_{base_name}_p3_end");
        static const std::string_view P3_{base_name.upper()} {{
        static_cast<const char*>(p3_{base_name}_start),
        static_cast<size_t>(p3_{base_name}_end - p3_{base_name}_start)
        }};''')    # 템플릿 채우기
    content = HEADER_TEMPLATE.format(
        lang_code=lang_code,
        lang_code_for_font=lang_code.replace('-', '_').lower(),
        strings="\n".join(sorted(strings)),
        sounds="\n".join(sorted(sounds))
    )

    # 파일에 쓰기
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(content)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", required=True, help="입력 JSON 파일 경로")
    parser.add_argument("--output", required=True, help="출력 헤더 파일 경로")
    args = parser.parse_args()

    generate_header(args.input, args.output)