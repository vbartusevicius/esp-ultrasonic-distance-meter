#include "Display.h"

#include <U8g2lib.h>
#include <UiUiUi.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D6, D5);

UITextLine textLine=UITextLine(u8g2_font_6x10_tf);
UIDisplay displayManager=UIDisplay(&textLine);

Display::Display()
{
    u8g2.begin();

    displayManager.init(&u8g2);
}

void Display::displayText(String text)
{
    const char* a = text.c_str();
    textLine.setText(a);
    displayManager.render(&u8g2, true);
}