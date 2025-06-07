#pragma once

#include <libs/gif/lv_gif.h>

#include "display/lcd_display.h"

// Electron Bot 표정 GIF 선언 - Otto와 동일한 6개 표정 사용
LV_IMAGE_DECLARE(staticstate);  // 정적 상태/중성 표정
LV_IMAGE_DECLARE(sad);          // 슬픔
LV_IMAGE_DECLARE(happy);        // 행복
LV_IMAGE_DECLARE(scare);        // 놀람/놀라움
LV_IMAGE_DECLARE(buxue);        // 모름/혼란
LV_IMAGE_DECLARE(anger);        // 분노

/**
 * @brief Electron Bot GIF 표정 디스플레이 클래스
 * LcdDisplay를 상속하여 GIF 표정 지원 추가
 */
class ElectronEmojiDisplay : public SpiLcdDisplay {
public:    /**
     * @brief 생성자, SpiLcdDisplay와 동일한 매개변수
     */
    ElectronEmojiDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel,
                         int width, int height, int offset_x, int offset_y, bool mirror_x,
                         bool mirror_y, bool swap_xy, DisplayFonts fonts);

    virtual ~ElectronEmojiDisplay() = default;    // 표정 설정 메서드 오버라이드
    virtual void SetEmotion(const char* emotion) override;

    // 채팅 메시지 설정 메서드 오버라이드
    virtual void SetChatMessage(const char* role, const char* content) override;

private:
    void SetupGifContainer();    lv_obj_t* emotion_gif_;  ///< GIF 표정 컴포넌트

    // 표정 매핑
    struct EmotionMap {
        const char* name;
        const lv_image_dsc_t* gif;
    };

    static const EmotionMap emotion_maps_[];
};