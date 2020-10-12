#include <iostream>
#include <locale.h>
#include <windows.h>

#include "BinaryRepresentation.h"

//using
using std::cout;
using std::cin;
using std::endl;

enum ConsoleColor {
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
};

void SetOutputColor(int text = 15, int bg = 0) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

//#define DEBUG

int main()
{
    setlocale(0, "RU");
    system("color 0F");
    //system("color 0F");

    //32767 2147483647 4294967295 18446744073709551615 1.1654366436464364364387 1.165436643646436436438745745747245987957895789
    //              1.1654366436464364364
    //              1.1654366436464365

    short value1 = -12344; //-32767
    int value2 = -4521; //-2147483648
    long value3 = -2147483648; //-2147483648
    long long value4 = -9223372036854775807; //-9223372036854775807
    // +
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

    BinaryRepresentation object;

    SetOutputColor(14);
    cout << "DEBUG MODULE 1: short/int/long/__int64" << endl;
    object.convert_dec_to_bin(value1);
    cout << endl;
    object.convert_dec_to_bin(value2);
    cout << endl;
    object.convert_dec_to_bin(value3);
    cout << endl;
    object.convert_dec_to_bin(value4);
    cout << endl;
    cout << endl;

    /*SetOutputColor(13);
    cout << "DEBUG MODULE 2: U short/U int/U long/U __int64" << endl;
    object.convert_dec_to_bin(uvalue1);
    cout << endl;
    object.convert_dec_to_bin(uvalue2);
    cout << endl;
    object.convert_dec_to_bin(uvalue3);
    cout << endl;
    object.convert_dec_to_bin(uvalue4);
    cout << endl;
    cout << endl;*/

    SetOutputColor(1);
    cout << "DEBUG MODULE 3: float" << endl;
    object.convert_dec_to_bin(valueF);
    cout << endl;
    object.convert_dec_to_bin(valueF2);
    cout << endl;
    object.convert_dec_to_bin(valueF3);
    cout << endl;
    object.convert_dec_to_bin(valueF4);
    cout << endl;
    cout << endl;

   
    SetOutputColor(9);
    cout << "DEBUG MODULE 4: double / L double" << endl;
    object.convert_dec_to_bin(valueD);
    cout << endl;
    object.convert_dec_to_bin(valueD2);
    cout << endl;
    object.convert_dec_to_bin(valueD3);
    cout << endl;
    object.convert_dec_to_bin(valueD4);
    cout << endl;
    cout << endl;

    /*SetOutputColor();
    cout << "DEBUG MODULE 5: char / U char" << endl;
    object.convert_dec_to_bin(valueC);
    cout << endl;
    object.convert_dec_to_bin(valueC2);
    cout << endl;
    object.convert_dec_to_bin(valueC3);
    cout << endl;
    object.convert_dec_to_bin(valueC4);
    cout << endl;*/

   /* object.convert_dec_to_bin(valueUC);
    cout << endl;*/

    cout << endl;

    //system("pause");
}

//обработать unsigned
//обработать отображение
//обработать неточность округления (обработать блок восстановления числа)