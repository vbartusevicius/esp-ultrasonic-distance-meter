#include "Display.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D6, D5);

Display::Display()
{
    u8g2.begin();

    this->displayWidth = u8g2.getDisplayWidth();
}

void Display::run()
{
    u8g2.firstPage();
    do {
        this->renderProgress();
    } while (u8g2.nextPage());
}

void Display::setProgress(float relative)
{
    this->relativeProgress = relative;
}

void Display::renderProgress()
{
    char value[8];
    snprintf(value, sizeof(value), "%2.0f%%", this->relativeProgress * 100);

    u8g2.drawFrame(0, 0, this->displayWidth, this->progressHeight);
    u8g2.drawBox(1, 1, (int) ((this->displayWidth - 2) * this->relativeProgress), this->progressHeight - 2);

    u8g2.setFontMode(1);
    u8g2.setDrawColor(2);
    u8g2.setFont(u8g2_font_5x7_tr);
    auto charHeight = u8g2.getAscent();
    auto strWidth = u8g2.getStrWidth(value);
    u8g2.drawStr(
        (this->displayWidth - strWidth) / 2, 
        charHeight + floor((progressHeight - charHeight) / 2) - 1, 
        value
    );
}