#include <iostream>
#include <locale.h>
#include <windows.h>

#include "BinaryRepresentation.h"
#include "OneDimensionalStaticIntArray.h"
#include "AdvancedSquareMatrix.h"
#include "StringEditor.h"

using std::cout;
using std::cin;
using std::endl;

/*
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
*/

void SetOutputColor(int text = 15, int bg = 0) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

// WARNING: FIX return;

int main()
{
    setlocale(0, "RU");
    system("color 0F");

    // 1234567890123456789012345

    bool is_cout = 1;
    int value = 0;
    char ch;
    //cin >> ch;

    /*Beep(659, 150);
    Sleep(50);
    Beep(659, 150);
    Sleep(100);
    Beep(659, 200);
    Sleep(100);
    Beep(523, 130);
    Beep(659, 150);
    Sleep(200);
    Beep(790, 300);
    Sleep(400);
    Beep(391, 500);*/

    /*Beep(1480, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(369.99, 200);
    Beep(392, 200);
    Beep(369.99, 200);
    Beep(392, 200);
    Beep(392, 400);
    Beep(196, 400);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(880, 200);
    Beep(830.61, 200);
    Beep(880, 200);
    Beep(987.77, 400);
    Beep(880, 200);
    Beep(783.99, 200);
    Beep(698.46, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(880, 200);
    Beep(830.61, 200);
    Beep(880, 200);
    Beep(987.77, 400);
    Sleep(200);
    Beep(1108, 10);
    Beep(1174.7, 200);
    Beep(1480, 10);
    Beep(1568, 200);
    Sleep(200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(783.99, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(880, 200);
    Beep(830.61, 200);
    Beep(880, 200);
    Beep(987.77, 400);
    Beep(880, 200);
    Beep(783.99, 200);
    Beep(698.46, 200);
    Beep(659.25, 200);
    Beep(698.46, 200);
    Beep(784, 200);
    Beep(880, 400);
    Beep(784, 200);
    Beep(698.46, 200);
    Beep(659.25, 200);
    Beep(587.33, 200);
    Beep(659.25, 200);
    Beep(698.46, 200);
    Beep(784, 400);
    Beep(698.46, 200);
    Beep(659.25, 200);
    Beep(587.33, 200);
    Beep(523.25, 200);
    Beep(587.33, 200);
    Beep(659.25, 200);
    Beep(698.46, 400);
    Beep(659.25, 200);
    Beep(587.33, 200);
    Beep(493.88, 200);
    Beep(523.25, 200);
    Sleep(400);
    Beep(349.23, 400);
    Beep(392, 200);
    Beep(329.63, 200);
    Beep(523.25, 200);
    Beep(493.88, 200);
    Beep(466.16, 200);
    Beep(440, 200);
    Beep(493.88, 200);
    Beep(523.25, 200);
    Beep(880, 200);
    Beep(493.88, 200);
    Beep(880, 200);
    Beep(1760, 200);
    Beep(440, 200);
    Beep(392, 200);
    Beep(440, 200);
    Beep(493.88, 200);
    Beep(783.99, 200);
    Beep(440, 200);
    Beep(783.99, 200);
    Beep(1568, 200);
    Beep(392, 200);
    Beep(349.23, 200);
    Beep(392, 200);
    Beep(440, 200);
    Beep(698.46, 200);
    Beep(415.2, 200);
    Beep(698.46, 200);
    Beep(1396.92, 200);
    Beep(349.23, 200);
    Beep(329.63, 200);
    Beep(311.13, 200);
    Beep(329.63, 200);
    Beep(659.25, 200);
    Beep(698.46, 400);
    Beep(783.99, 400);
    Beep(440, 200);
    Beep(493.88, 200);
    Beep(523.25, 200);
    Beep(880, 200);
    Beep(493.88, 200);
    Beep(880, 200);
    Beep(1760, 200);
    Beep(440, 200);
    Beep(392, 200);
    Beep(440, 200);
    Beep(493.88, 200);
    Beep(783.99, 200);
    Beep(440, 200);
    Beep(783.99, 200);
    Beep(1568, 200);
    Beep(392, 200);
    Beep(349.23, 200);
    Beep(392, 200);
    Beep(440, 200);
    Beep(698.46, 200);
    Beep(659.25, 200);
    Beep(698.46, 200);
    Beep(739.99, 200);
    Beep(783.99, 200);
    Beep(392, 200);
    Beep(392, 200);
    Beep(392, 200);
    Beep(392, 200);
    Beep(196, 200);
    Beep(196, 200);
    Beep(196, 200);
    Beep(185, 200);
    Beep(196, 200);
    Beep(185, 200);
    Beep(196, 200);
    Beep(207.65, 200);
    Beep(220, 200);
    Beep(233.08, 200);
    Beep(246.94, 200);*/

    /*Beep(247, 500);
    Beep(417, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(417, 500);
    Beep(329, 500);
    Beep(247, 500);
    Beep(247, 500);
    Beep(247, 500);
    Beep(417, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(417, 500);
    Beep(497, 500);
    Sleep(500);
    Beep(497, 500);
    Beep(277, 500);
    Beep(277, 500);
    Beep(440, 500);
    Beep(440, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(329, 500);
    Beep(247, 500);
    Beep(417, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(417, 500);
    Beep(329, 500);*/

    StringEditor obj;
    obj.read(2, "  toDay   we wILl test THIS program for eRRoRs    , ,,,  ,, ,    it Is possible   tHAt   (they)   exISt .. .. ..   tOfaO    . a  000000075   ...   3448,, 4487  ..  мда    .... ");
    obj.edit_remove_extra_spaces();
    obj.cout_string();

    obj.edit_uppercase_lowercase_letters();
    obj.cout_string();

    obj.edit_remove_duplicate_punctuation_marks();
    obj.cout_string();
    //cout << char(7); // WARNING SOUND

    for (int i = 0; i <= -255; i++)
    {
        cout << i << char(7) << '\t' << static_cast<char>(i) << endl;
    }

    //system("pause");
}


/*
    short value1 = -12344; //-32767
    int value2 = -4521; //-2147483648
    long value3 = -2147483648; //-2147483648
    long long value4 = -9223372036854775807; //-9223372036854775807

    unsigned short uvalue1 = 0; //65535
    unsigned int uvalue2 = 4294967295;
    unsigned long uvalue3 = 0; //4294967295
    unsigned long long uvalue4 = 18446744073709551615;


    float valueF = 0.15625;        // 0.156250000
    float valueF2 = 0;             // 0.00000000
    float valueF3 = 1.15625;       // 1.15625000
    float valueF4 = 12.15625;      //12.1562500

    double valueD =  -0.16543664364643657; //-  0.16543664364643651
    double valueD2 =  0.1654366436464365;  //+  0.16543664364643651
    double valueD3 = -1.1654366436464365;  //-  1.1654366436464365
    double valueD4 = -13.1654366436464365; //- 13.165436643646437

    long double valueLD = 1.1654366436464365134143143;


    char valueC = -0; //-23
    char valueC2 = -127;
    char valueC3 = -1;
    char valueC4 = -88;
    unsigned char valueUC = 23;
*/