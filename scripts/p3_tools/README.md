# P3 오디오 포맷 변환 및 재생 도구

이 디렉토리에는 P3 포맷 오디오 파일 처리를 위한 두 개의 Python 스크립트가 포함되어 있습니다:

## 1. 오디오 변환 도구 (convert_audio_to_p3.py)

일반 오디오 파일을 P3 포맷(4바이트 헤더 + Opus 데이터 패킷의 스트리밍 구조)으로 변환하고 음량 표준화를 수행합니다.

### 사용법

```bash
python convert_audio_to_p3.py <입력_오디오_파일> <출력_P3_파일> [-l LUFS] [-d]
```

여기서 선택적 옵션 `-l`은 음량 표준화의 목표 음량을 지정하는 데 사용되며, 기본값은 -16 LUFS입니다. 선택적 옵션 `-d`는 음량 표준화를 비활성화할 수 있습니다.

입력 오디오 파일이 다음 조건 중 하나라도 만족하는 경우 `-d`를 사용하여 음량 표준화를 비활성화하는 것을 권장합니다:
- 오디오가 너무 짧음
- 오디오의 음량이 이미 조정됨
- 기본 TTS의 오디오 (xiaozhi가 현재 사용하는 TTS의 기본 음량은 이미 -16 LUFS임)

예시:
```bash
python convert_audio_to_p3.py input.mp3 output.p3
```

## 2. P3 오디오 재생 도구 (play_p3.py)

P3 형식의 오디오 파일을 재생합니다.

### 특징

- P3 형식의 오디오 파일을 디코딩하고 재생
- 재생 완료 또는 사용자 중단 시 페이드아웃 효과를 적용하여 잡음 방지
- 명령줄 인수를 통해 재생할 파일 지정 가능

### 사용법

```bash
python play_p3.py <P3파일경로>
```

예시:
```bash
python play_p3.py output.p3
```

## 3. 오디오 변환 도구 (convert_p3_to_audio.py)

P3 형식을 일반 오디오 파일로 다시 변환합니다.

### 사용법

```bash
python convert_p3_to_audio.py <입력P3파일> <출력오디오파일>
```

출력 오디오 파일에는 확장자가 필요합니다.

예시:
```bash
python convert_p3_to_audio.py input.p3 output.wav
```
## 4. 오디오/P3 일괄 변환 도구

오디오를 P3로, P3를 오디오로 일괄 변환을 지원하는 그래픽 도구입니다.

![](./img/img.png)

### 사용법:
```bash
python batch_convert_gui.py
```

## 종속성 설치

이러한 스크립트를 사용하기 전에 필요한 Python 라이브러리가 설치되어 있는지 확인하십시오:

```bash
pip install librosa opuslib numpy tqdm sounddevice pyloudnorm soundfile
```

또는 제공된 requirements.txt 파일을 사용하십시오:

```bash
pip install -r requirements.txt
```

## P3 형식 설명

P3 형식은 간단한 스트리밍 오디오 형식으로 구조는 다음과 같습니다:
- 각 오디오 프레임은 4바이트 헤더와 Opus 인코딩된 데이터 패킷으로 구성됩니다
- 헤더 형식: [1바이트 타입, 1바이트 예약, 2바이트 길이]
- 샘플링 레이트는 16000Hz로 고정, 모노
- 프레임당 지속 시간은 60ms입니다