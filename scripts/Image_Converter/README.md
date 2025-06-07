# LVGL 이미지 변환 도구  

이 디렉토리는 이미지를 처리하고 LVGL 형식으로 변환하는 두 개의 Python 스크립트를 포함합니다:

## 1. LVGLImage (LVGLImage.py)

LVGL [공식 레포지토리](https://github.com/lvgl/lvgl)의 변환 스크립트 [LVGLImage.py](https://github.com/lvgl/lvgl/blob/master/scripts/LVGLImage.py)에서 참조  

## 2. LVGL 이미지 변환 도구 (lvgl_tools_gui.py)

`LVGLImage.py`를 호출하여 이미지를 LVGL 이미지 형식으로 일괄 변환
샤오즈히의 기본 표정을 수정하는 데 사용할 수 있습니다. 구체적인 수정 튜토리얼은 [여기](https://www.bilibili.com/video/BV12FQkYeEJ3/)

### 특징

- 그래픽 조작, 더 친화적인 인터페이스
- 일괄 이미지 변환 지원
- 이미지 형식을 자동으로 인식하고 최적의 색상 형식 변환 선택
- 다중 해상도 지원

### 사용법

Pillow 설치

```bash
pip install Pillow # 이미지 처리에 필요
```

변환 도구 실행

```bash
python lvgl_tools_gui.py
```
