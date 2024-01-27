#include "Display.h"

#include <U8g2lib.h>
#include <UiUiUi.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D6, D5);

// progress bar
UISize progressSize = UISize(0, 8);
UITextLine progressText = UITextLine(u8g2_font_5x7_tr);
UIHorizontalLine progressSeparator=UIHorizontalLine(&progressText);

UICheckerboard progressBar = UICheckerboard(&progressSize);
UIEnvelope barEnvelope = UIEnvelope(UIExpansion::Ui_None, UIAlignment::TopLeft, &progressBar, &progressSeparator);

UIRows progressRows = UIRows(&barEnvelope);
UICards progress = UICards(&progressRows);


UIDisplay displayManager=UIDisplay(&progress);

Display::Display()
{
    u8g2.begin();

    displayManager.init(&u8g2);
}

void Display::displayText(String text)
{
    progressSize.set(random(0, 128), 8);
    progress.hide();
    delay(100);
    displayManager.render(&u8g2, true);
    progress.showFirstWidget();

    const char* a = text.c_str();
    progressText.setText(a);
    displayManager.render(&u8g2, true);
}