#pragma once
#include <iostream>
#include <cmath>
#include <cstdio>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

//#define DEBUG
//#define DEBUG_RESULT



class BinaryRepresentation
{
public:
    BinaryRepresentation();
    ~BinaryRepresentation();

    // [- - - - - - - - - - - - - - - - - - - - - - - - - - IEEE 754 - - - - - - - - - - - - - - - - - - - - - - - - - - -]                                     
    // Converts values of various standard data types to a binary representation and writes them to an array of characters.
    // - - returns a pointer to an array of characters in the binary representation of the value received as a parameter - -
    // - - - - - - - - - - - - - - - - - - - - - - - - - - Attention - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // The "long double" data type is not supported. Maximum size of a variable in memory: 8 bytes
    // Special States, such as +-Infinity or NaN, are not processed. 
    // Values presented in denormalized form are also not processed.
    template <typename T>
    char* convertDecToBin(T allStandartDataTypeValue) {
        union ToolUnion {
            long long bufferTool;
            T dataTypeValue;
        };
        ToolUnion tools;
        tools.dataTypeValue = allStandartDataTypeValue;

        // initialization data type
        pDataType = new char[strlen(typeid(allStandartDataTypeValue).name()) + 1];
        this->copyCharArray(pDataType, strlen(typeid(allStandartDataTypeValue).name()), typeid(allStandartDataTypeValue).name());
        this->initializeDataTypeCode();
        if (dataTypeCode > 12 || dataTypeCode == 10)
        {
            cout << "The variable cannot be converted to a binary representation because it is not in the supported list" << endl;
            return nullptr;
        }

        sizeofDataTypeValue_x8 = 8 * sizeof(tools.dataTypeValue);

        pBinResult = new char[sizeofDataTypeValue_x8 + 1]{ 0 };

        // performs a bitwise conjunction, then writes the result to an array
        for (int i = sizeofDataTypeValue_x8 - 1; i >= 0; i--)
        {
            if ((tools.bufferTool >> i) & 0b00000001) 
                pBinResult[sizeofDataTypeValue_x8 - 1 - i] = '1';
            else
                pBinResult[sizeofDataTypeValue_x8 - 1 - i] = '0';
        }

        binIsInitialized = true;

        return pBinResult;
	};

    //returns a pointer to an array of characters if the operation was successful; nullptr if an error occurred or some variables were not initialized
    char* convertBinToDec();


    // displays the amount of memory used by different types of variables
    void coutWeightDataTypes();

    //returns 1 if output is successful; 0 if an error occurred or some variables were not initialized
    bool coutBinRepresentation();


    //returns a pointer to an array of characters if the operation was successful; nullptr if an error occurred or some variables were not initialized
    char* getDecRepresentation();

    //returns a pointer to an array of characters if the operation was successful; nullptr if an error occurred or some variables were not initialized
    char* getBinRepresentation();

    bool getColorsState();

    void setColorsState(bool state);

private:
    // stores the binary representation of a number
    char* pBinResult;
    
    // stores the decimal representation of a number
    char* pDecResult;

    // stores the data type of the variable, received as an argument, in an array of characters
    char* pDataType;

    // Signed integer: 0 = short; 1 = int; 2 = long; 3 = __int64
    // Unsigned integer: 4 = short; 5 = int; 6 = long; 7 = __int64
    // Floating point-based: 8 = float; 9 = double; 10 = long double
    // Character: 11 = Signed char; 12 = Unsigned char
    // Another: N = everything else, if not included in the supported list
    // - - - - - - - - - - - - - - - - INFO - - - - - - - - - - - - - - - -
    // 10 <- introduced for possible implementation in future updates
    // default: 0
    unsigned short dataTypeCode;

    int sizeofDataTypeValue_x8; //default: 0

    // number of bits of memory occupied by the exponent
    // default: 0
    unsigned short exponentSize;
    
    // settings
    bool binIsInitialized; //default: false
    bool decIsInitialized; //default: false
    bool colorsState;  //default: true


    void SetOutputColor(int text = 15, int bg = 0, bool isEnableColors = true);

    void initializeDataTypeCode();

    // don't forget to leave the last character of the array under the null-terminator, which means the end of the string
    void copyCharArray(char* pDestinationCharStr, size_t numberOfCharactersToCopy, const char* pSourceCharStr, size_t destinationPosOffset = 0, size_t sourcePosOffset = 0, bool replaceSpacesWithUnderscores = false);

    bool compareCharArrays(const char* pFirstCharArray, const char* pSecondCharArray);
};