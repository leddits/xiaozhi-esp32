#pragma once

#include <libs/gif/lv_gif.h>

#include "display/lcd_display.h"
#include "otto_emoji_gif.h"

/**
 * @brief Otto 로봇 GIF 표정 디스플레이 클래스
 * LcdDisplay를 상속하여 GIF 표정 지원 추가
 */
class OttoEmojiDisplay : public SpiLcdDisplay {
public:    /**
     * @brief 생성자, SpiLcdDisplay와 동일한 매개변수
     */
    OttoEmojiDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel, int width,
                     int height, int offset_x, int offset_y, bool mirror_x, bool mirror_y,
                     bool swap_xy, DisplayFonts fonts);

    virtual ~OttoEmojiDisplay() = default;    // 표정 설정 메서드 오버라이드
    virtual void SetEmotion(const char* emotion) override;

    // 채팅 메시지 설정 메서드 오버라이드
    virtual void SetChatMessage(const char* role, const char* content) override;

private:
    void SetupGifContainer();    lv_obj_t* emotion_gif_;  ///< GIF 표정 컴포넌트

    // 표정 매핑
    struct EmotionMap {
        const char* name;
        const lv_img_dsc_t* gif;
    };

    static const EmotionMap emotion_maps_[];
};