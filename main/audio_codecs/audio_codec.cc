#include "audio_codec.h"
#include "board.h"
#include "settings.h"

#include <esp_log.h>
#include <cstring>
#include <driver/i2s_common.h>

#define TAG "AudioCodec"

AudioCodec::AudioCodec() {
}

AudioCodec::~AudioCodec() {
}

void AudioCodec::OutputData(std::vector<int16_t>& data) {
    Write(data.data(), data.size());
}

bool AudioCodec::InputData(std::vector<int16_t>& data) {
    int samples = Read(data.data(), data.size());
    if (samples > 0) {
        return true;
    }
    return false;
}

void AudioCodec::Start() {
    // Settings settings("audio", false);
    // output_volume_ = settings.GetInt("output_volume", output_volume_);
    // if (output_volume_ <= 0) {
    //     ESP_LOGW(TAG, "Output volume value (%d) is too small, setting to default (100)", output_volume_);
    //     output_volume_ = 100;
    // }

    // 오디오 볼륨 최대로 설정
    output_volume_ = 100;

    ESP_LOGI(TAG, "Starting audio codec - Sample rates: Input %d Hz, Output %d Hz", 
             input_sample_rate_, output_sample_rate_);
    ESP_LOGI(TAG, "Audio channels: Input %d, Output %d", input_channels_, output_channels_);
    ESP_LOGI(TAG, "Audio volume: %d", output_volume_);

    ESP_ERROR_CHECK(i2s_channel_enable(tx_handle_));
    ESP_ERROR_CHECK(i2s_channel_enable(rx_handle_));

    EnableInput(true);
    EnableOutput(true);
    ESP_LOGI(TAG, "Audio codec started successfully");
}

void AudioCodec::SetOutputVolume(int volume) {
    // 뮤텍스로 동시성 보호 (음성 출력 중 볼륨 변경 시 충돌 방지)
    std::lock_guard<std::mutex> lock(volume_mutex_);
    
    // 볼륨 값 검증
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    
    // 이미 같은 볼륨이면 불필요한 하드웨어 호출 방지
    if (output_volume_ == volume) {
        ESP_LOGD(TAG, "Volume already set to %d, skipping", volume);
        return;
    }
    
    output_volume_ = volume;
    ESP_LOGI(TAG, "🔊 Set output volume to %d (thread-safe)", output_volume_);
    
    Settings settings("audio", true);
    settings.SetInt("output_volume", output_volume_);
}

void AudioCodec::EnableInput(bool enable) {
    if (enable == input_enabled_) {
        return;
    }
    input_enabled_ = enable;
    ESP_LOGI(TAG, "Set input enable to %s", enable ? "true" : "false");
}

void AudioCodec::EnableOutput(bool enable) {
    if (enable == output_enabled_) {
        return;
    }
    output_enabled_ = enable;
    ESP_LOGI(TAG, "Set output enable to %s", enable ? "true" : "false");
}
