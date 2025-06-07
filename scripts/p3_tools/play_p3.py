# P3 형식의 오디오 파일 재생
import opuslib
import struct
import numpy as np
import sounddevice as sd
import argparse

def play_p3_file(input_file):
    """
    P3 형식의 오디오 파일 재생
    P3 형식: [1바이트 타입, 1바이트 예약, 2바이트 길이, Opus 데이터]
    """
    # Opus 디코더 초기화
    sample_rate = 16000  # 샘플링 레이트는 16000Hz로 고정
    channels = 1  # 모노
    decoder = opuslib.Decoder(sample_rate, channels)
    
    # 帧大小 (60ms)
    frame_size = int(sample_rate * 60 / 1000)
    
    # 打开音频流
    stream = sd.OutputStream(
        samplerate=sample_rate,
        channels=channels,
        dtype='int16'
    )
    stream.start()
    
    try:
        with open(input_file, 'rb') as f:
            print(f"正在播放: {input_file}")
            
            while True:
                # 读取头部 (4字节)
                header = f.read(4)
                if not header or len(header) < 4:
                    break
                
                # 解析头部
                packet_type, reserved, data_len = struct.unpack('>BBH', header)
                
                # 读取Opus数据
                opus_data = f.read(data_len)
                if not opus_data or len(opus_data) < data_len:
                    break
                
                # 解码Opus数据
                pcm_data = decoder.decode(opus_data, frame_size)
                
                # 将字节转换为numpy数组
                audio_array = np.frombuffer(pcm_data, dtype=np.int16)
                
                # 播放音频
                stream.write(audio_array)
                
    except KeyboardInterrupt:
        print("\n播放已停止")
    finally:
        stream.stop()
        stream.close()
        print("播放完成")

def main():
    parser = argparse.ArgumentParser(description='播放p3格式的音频文件')
    parser.add_argument('input_file', help='输入的p3文件路径')
    args = parser.parse_args()
    
    play_p3_file(args.input_file)

if __name__ == "__main__":
    main() 
