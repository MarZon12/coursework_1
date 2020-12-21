#include "BinaryRepresentation.h"

BinaryRepresentation::BinaryRepresentation() {
    pBinResult = nullptr;
    pDecResult = nullptr;
    pDataType = nullptr;

    binIsInitialized = false;
    decIsInitialized = false;
    colorsState = true;

    dataTypeCode = 0;
    sizeofDataTypeValue_x8 = 0;
    exponentSize = 0;
}
BinaryRepresentation::~BinaryRepresentation() {
    delete[] pBinResult;
    delete[] pDecResult;
    delete[] pDataType;
}


void BinaryRepresentation::coutWeightDataTypes() {
	cout << "The amount of memory used by different data types:\n";
	
	cout << "int:         " << sizeof(int) << " byte\n"
		 << "short int:   " << sizeof(short) << " byte\n"
		 << "long int:    " << sizeof(long) << " byte\n"
		 << "float:       " << sizeof(float) << " byte\n"
		 << "double:      " << sizeof(double) << " byte\n"
		 << "long double: " << sizeof(long double) << " byte\n"
		 << "char:        " << sizeof(char) << " byte\n"
		 << "bool:        " << sizeof(bool) << " byte" << endl;
}

bool BinaryRepresentation::coutBinRepresentation() {
    if (!binIsInitialized)
    {
        cout << endl << endl 
            << "\t+=========================================================+\n"
            << "\t|Attention! You didn't convert a decimal number to binary!|\n"
            << "\t+=========================================================+\n" << endl;
        return 0;
    }


    cout << "Variable type: " << pDataType << endl; //" code: " << dataTypeCode << endl; //WARNING
    cout << "Value: ";
    //for char && U char
    if (dataTypeCode >= 11 && dataTypeCode <= 12)
        cout << this->convertBinToDec() << " (" << static_cast<char>(atoi(this->convertBinToDec())) << ')' << endl;
    else
        cout << this->convertBinToDec() << endl;

    cout << "Presentation format: " << endl;

    //sign
    this->SetOutputColor(2, 0, colorsState);
    cout << "sign";

    //exponent
    if (dataTypeCode >= 8 && dataTypeCode <= 10)
    {
        this->SetOutputColor(4, 0, colorsState);
        cout << " exponent";
    }

    //mantissa
    this->SetOutputColor(6, 0, colorsState);
    cout << " mantissa" << endl;
    this->SetOutputColor();


    //sign
    this->SetOutputColor(2,0,colorsState);
    cout << pBinResult[0];

    //sign separation
    if (dataTypeCode >= 0 && dataTypeCode <= 7 || dataTypeCode >= 8 && dataTypeCode <= 10 || dataTypeCode == 11)
        cout << ' ';

    //exponent
    if (exponentSize != 0)
    {
        this->SetOutputColor(4, 0, colorsState);
        for (int i = 1; i <= exponentSize; i++)
        {
            cout << pBinResult[i];
        }
        cout << ' ';
    }

    //mantissa
    this->SetOutputColor(6, 0, colorsState);
    for (int i = exponentSize + 1; i < sizeofDataTypeValue_x8; i++)
    {
        cout << pBinResult[i];
    }
    cout << endl;


    this->SetOutputColor();
    return 1;
};

char* BinaryRepresentation::convertBinToDec() {
    if (!binIsInitialized)
    {
        cout << endl << endl 
            << "\t+=========================================================+\n"
            << "\t|Attention! You didn't convert a decimal number to binary!|\n"
            << "\t+=========================================================+\n" << endl;
        return nullptr;
    }

    //check for the list of supported variable data types
    if (dataTypeCode > 12 || dataTypeCode == 10)
    {
        cout << "The variable cannot be converted to a decimal representation because it is not in the supported list" << endl;
        return nullptr;
    }

    unsigned long long preliminaryIntegerValue = 0;
    long double preliminaryFractionalValue = 0;

    bool isNull = true;
    bool isNegative = false;

    unsigned short integerLength = 0;
    unsigned short fractionalLength = 0;
    unsigned short totalLength = 0;

    //creating a copy of the pBinResult array
    char* pBinResult_copy = new char[sizeofDataTypeValue_x8 + 1]{ 0 };
    this->copyCharArray(pBinResult_copy, sizeofDataTypeValue_x8, pBinResult);

    //checking for zero
    for (int i = 0; i < sizeofDataTypeValue_x8; i++)
    {
        if (pBinResult_copy[i] == '1') {
            isNull = false;
            break;
        }
    }

    ///***********************************///
    ///            PROCESSING             ///
    ///***********************************///

    //U integer types and U char types
    if ((dataTypeCode >= 4 && dataTypeCode <= 7 || dataTypeCode == 12) && !isNull) {
        for (int i = 0; i < sizeofDataTypeValue_x8; i++)
            if (pBinResult_copy[(sizeofDataTypeValue_x8 - 1) - i] == '1')
                preliminaryIntegerValue += static_cast<unsigned long long>(pow(2, i));
    }
    //out: preliminaryIntegerValue (UNSIGNED) <- if not null. 


    //S integer types and S char types
    if ((dataTypeCode >= 0 && dataTypeCode <= 3 || dataTypeCode == 11) && !isNull) {
        // pre-processing for a negative value 
        if (pBinResult_copy[0] == '1')
        {
            short index_first_one_from_the_end;

            isNegative = true;

            // search first '1' from the end
            for (int i = sizeofDataTypeValue_x8 - 1; i >= 0; i--)
            {
                if (pBinResult_copy[i] == '1') {
                    index_first_one_from_the_end = i;
                    break;
                }
            }

            // subtracting one
            if (index_first_one_from_the_end == sizeofDataTypeValue_x8 - 1)
                pBinResult_copy[index_first_one_from_the_end] = '0';
            else
            {
                for (int i = index_first_one_from_the_end; i < sizeofDataTypeValue_x8; i++)
                    pBinResult_copy[i] = '1';
                pBinResult_copy[index_first_one_from_the_end] = '0';
            }

            // invert
            for (int i = 0; i < sizeofDataTypeValue_x8; i++)
            {
                if (pBinResult_copy[i] == '1')
                    pBinResult_copy[i] = '0';
                else
                    pBinResult_copy[i] = '1';
            }
        }

        for (int i = 0; i < sizeofDataTypeValue_x8; i++) {
            if (pBinResult_copy[(sizeofDataTypeValue_x8 - 1) - i] == '1')
                preliminaryIntegerValue += static_cast<unsigned long long>(pow(2, i));
        }
    }
    //out: preliminaryIntegerValue (UNSIGNED) && isNegative <- if not null.


    //floating point-based types
    if ((dataTypeCode >= 8 && dataTypeCode <= 9) && !isNull)
    {
        short exponentValue = 0;

        if (pBinResult_copy[0] == '1')
            isNegative = true;

        // exponent
        for (short i = 1; i <= exponentSize; i++)
        {
            if (pBinResult_copy[exponentSize - i + 1] == '1')
                exponentValue += static_cast<short>(pow(2, i - 1));
        }

        // subtracting the offset
        switch (dataTypeCode)
        {
        case 8:
            exponentValue -= 127;
            break;

        case 9:
            exponentValue -= 1023;
            break;

        default:
            break;
        }


        //mantissa
        if (exponentValue == 0)
        {
            preliminaryIntegerValue = 1;
            for (int i = exponentSize + 1; i < sizeofDataTypeValue_x8; i++)
            {
                if (pBinResult_copy[i] == '1')
                    preliminaryFractionalValue += pow(2, (exponentSize + 1) - i - 1);
            }
        }

        if (exponentValue > 0)
        {
            //integer
            for (int i = exponentSize + exponentValue; i > exponentSize; i--)
            {
                if (pBinResult_copy[i] == '1')
                    preliminaryIntegerValue += static_cast<unsigned long long>(pow(2, exponentSize + exponentValue - i));

                if (i == exponentSize + 1)
                    preliminaryIntegerValue += static_cast<unsigned long long>(pow(2, exponentSize + exponentValue - i + 1)); //CAN BE OPTIMIZED
            }

            //after dot
            for (int i = exponentSize + exponentValue + 1; i < sizeofDataTypeValue_x8; i++)
            {
                if (pBinResult_copy[i] == '1')
                    preliminaryFractionalValue += pow(2, (exponentSize + exponentValue + 1) - i - 1);
            }

        }

        if (exponentValue < 0)
        {
            //after dot
            for (int i = exponentSize + 1; i < sizeofDataTypeValue_x8; i++)
            {
                if (pBinResult_copy[i] == '1')
                    preliminaryFractionalValue += pow(2, (exponentSize + 1) - i - 1 + exponentValue);
            }
            preliminaryFractionalValue += pow(2, exponentValue);
        }
    }
    //out: preliminaryIntegerValue (UNSIGNED) && preliminaryFractionalValue (POSITIVE) && isNegative <- if not null.


    ///**********************************///
    ///            TO STRING             ///
    ///**********************************///

    pDecResult = new char[30]{ 0 };
    char decResult_intBuffer[30]{ 0 };
    char decResult_fraBuffer[30]{ 0 };

    //INT
    sprintf_s(decResult_intBuffer, "%llu", preliminaryIntegerValue);

    //FLOAT POINT-BASED
    switch (dataTypeCode)
    {
    case 8:
        sprintf_s(decResult_fraBuffer, "%0.*f", static_cast<unsigned int>(9 - (preliminaryIntegerValue == 0 ? 0 : strlen(decResult_intBuffer))), preliminaryFractionalValue);
        break;

    case 9:
        sprintf_s(decResult_fraBuffer, "%0.*f", static_cast<unsigned int>(17 - (preliminaryIntegerValue == 0 ? 0 : strlen(decResult_intBuffer))), preliminaryFractionalValue);
        break;

    default:
        break;
    }

    // string factory
    if (isNegative)
        pDecResult[0] = '-';
    this->copyCharArray(pDecResult, strlen(decResult_intBuffer), decResult_intBuffer, isNegative); //int
    if (preliminaryFractionalValue != 9)
        this->copyCharArray(pDecResult, strlen(decResult_fraBuffer) + 1, decResult_fraBuffer, strlen(decResult_intBuffer) + isNegative, 1);

    decIsInitialized = true;
    delete[] pBinResult_copy;
    return pDecResult;
};


//getters
char* BinaryRepresentation::getDecRepresentation() {
    if (!decIsInitialized) {
        cout << endl << endl 
            << "\t+=========================================================+\n"
            << "\t|Attention! You didn't convert a binary number to decimal!|\n"
            << "\t+=========================================================+\n" << endl;
        return nullptr;
    }
    return pDecResult;
}

char* BinaryRepresentation::getBinRepresentation() {
    if (!binIsInitialized) {
        cout << endl << endl 
            << "\t+=========================================================+\n"
            << "\t|Attention! You didn't convert a decimal number to binary!|\n"
            << "\t+=========================================================+\n" << endl;
        return nullptr;
    }
    return pBinResult;
}

bool BinaryRepresentation::getColorsState() {
    return colorsState;
};


//setters
void BinaryRepresentation::setColorsState(bool state) {
    colorsState = state;
}


//private
void BinaryRepresentation::SetOutputColor(int text, int bg, bool isEnableColors) {
    if (isEnableColors)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
    }
}

void BinaryRepresentation::initializeDataTypeCode() {
    //converting the variable type to a numeric code: find the sum of the codes of all characters of the data type, getting the preliminary data type code
    unsigned short preliminaryDataTypeCode = 0;
    for (int i = 0; i < strlen(pDataType); i++)
        preliminaryDataTypeCode += static_cast<short>(pDataType[i]);

    // setting the final code of the data type
    // S = Signed; U = Unsigned; __int64 = long long
    switch (preliminaryDataTypeCode)
    {
        // SECTION 1: SIGNED INTEGER
    case 560: //S short
        dataTypeCode = 0;
        exponentSize = 0;
        break;

    case 331: //S int
        dataTypeCode = 1;
        exponentSize = 0;
        break;

    case 432: //S long
        dataTypeCode = 2;
        exponentSize = 0;
        break;

    case 627: //S __int64
        dataTypeCode = 3;
        exponentSize = 0;
        break;

        // SECTION 2: UNSIGNED INTEGER
    case 1453: //U short
        dataTypeCode = 4;
        exponentSize = 0;
        break;

    case 1224: //U int
        dataTypeCode = 5;
        exponentSize = 0;
        break;

    case 1325: //U long
        dataTypeCode = 6;
        exponentSize = 0;
        break;

    case 1520: //U __int64
        dataTypeCode = 7;
        exponentSize = 0;
        break;

        // SECTION 3: FLOATING POINT–BASED
    case 534: //float
        dataTypeCode = 8;
        exponentSize = 8;
        break;

    case 635: //double
        dataTypeCode = 9;
        exponentSize = 11;
        break;

    case 1099: //long double
        dataTypeCode = 10;
        exponentSize = 0; // WARNING
        break;

        // SECTION 4: CHARACTER
    case 414: //S char
        dataTypeCode = 11;
        exponentSize = 0;
        break;

    case 1307: //U char
        dataTypeCode = 12;
        exponentSize = 0;
        break;

        // SECTION 5: ANOTHER
    default: //everything else, if not included in the supported list
        dataTypeCode = 9999;
        exponentSize = 0;
        break;
    }
}

void BinaryRepresentation::copyCharArray(char* pDestinationCharStr, size_t numberOfCharactersToCopy, const char* pSourceCharStr, size_t destinationPosOffset, size_t sourcePosOffset, bool replaceSpacesWithUnderscores) {
    for (size_t i = 0; i < numberOfCharactersToCopy; i++)
        pDestinationCharStr[i + destinationPosOffset] = pSourceCharStr[i + sourcePosOffset];
    
    pDestinationCharStr[numberOfCharactersToCopy + destinationPosOffset] = '\0';
    
    // Replacing spaces with underscores
    if (replaceSpacesWithUnderscores)
        for (size_t i = 0; i < numberOfCharactersToCopy; i++)
            if (pDestinationCharStr[i] == ' ')
                pDestinationCharStr[i] = '_';
}

bool BinaryRepresentation::compareCharArrays(const char* pFirstCharArray, const char* pSecondCharArray) {
    if (strlen(pFirstCharArray) != strlen(pSecondCharArray))
        return false;

    for (size_t i = 0; i < strlen(pFirstCharArray); i++)
        if (pFirstCharArray[i] != pSecondCharArray[i])
            return false;

    return true;
}
