#pragma coce
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define Color_BLACK      0
#define Color_DarkBlue  1
#define Color_DarkGreen  2
#define Color_DarkCyan  3
#define Color_DarkRed  4
#define Color_DarkPink  5
#define Color_DarkYellow 6
#define Color_DarkWhite  7
#define Color_Grey   8
#define Color_Blue   9
#define Color_Green   10
#define Color_Cyan   11
#define Color_Red   12
#define Color_Pink   13
#define Color_Yellow  14
#define Color_White   15
#define key_Up  1072
#define key_Down 1080
#define key_Left 1075
#define key_Right 1077
#define key_none -1

void gotoXY (int column, int line)
{
 COORD coord;
 coord.X = column;
 coord.Y = line;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor (int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
