#include <iostream>
#include <locale.h>
#include <windows.h>

#include "BinaryRepresentation.h"
#include "OneDimensionalStaticIntArray.h"
#include "AdvancedSquareMatrix.h"

using std::cout;
using std::cin;
using std::endl;

int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);           // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

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



int main()
{
    setlocale(0, "RU");
    system("color 0F");

    bool is_cout = 1;
    int value = 0;
    
    AdvancedSquareMatrix obj;

    obj.matrix_constructor_interface(9);
    //obj.cout_matrix();
    obj.fill_matrix_snail();
    cout << endl;
    cout << endl;
    //system("pause");
    //obj.matrix_constructor_interface(20);
    //obj.cout_matrix();

}

/*
cout << "Average min and max: " << object.average_min_and_max() << endl;






*/








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