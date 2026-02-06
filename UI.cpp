#include "DxLib.h"

// 文字列をセンタリングして表示する関数
void drawTextC(int x, int y, const char* txt, int col, int siz)
{
    SetFontSize(siz);
    int strWidth = GetDrawStringWidth(txt, strlen(txt));
    x -= strWidth / 2;
    y -= siz / 2;
    DrawString(x + 1, y + 1, txt, 0x000000);
    DrawString(x, y, txt, col);
}

