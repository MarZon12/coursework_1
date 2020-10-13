#include "BinaryRepresentation.h"

void BinaryRepresentation::cout_weight_data_types() {
	cout << "Объем памяти, занимаемой различными типами данных:" << endl;
	
	cout << "int:         " << sizeof(int) << " byte" << endl
		 << "short int:   " << sizeof(short) << " byte" << endl
		 << "long int:    " << sizeof(long) << " byte" << endl
		 << "float:       " << sizeof(float) << " byte" << endl
		 << "double:      " << sizeof(double) << " byte" << endl
		 << "long double: " << sizeof(long double) << " byte" << endl
		 << "char:        " << sizeof(char) << " byte"  << endl
		 << "bool:        " << sizeof(bool) << " byte" << endl;
}

bool BinaryRepresentation::cout_binary_representation() {
    if (!bin_is_initialized)
    {
        cout << endl << endl << "\t+=========================================================+" << endl
            << "\t|Attention! You didn't convert a decimal number to binary!|" << endl
            << "\t+=========================================================+" << endl << endl;
        return 0;
    }


    cout << "Тип переменной: " << data_type << endl; //" code: " << data_type_code << endl; //WARNING
    cout << "Значение: " << this->convert_bin_to_dec() << endl;

    cout << "Формат представления: " << endl;

    //sign
    this->SetOutputColor(2, 0, enable_colors);
    cout << "знак";

    //exponent
    if (data_type_code >= 8 && data_type_code <= 10)
    {
        this->SetOutputColor(4, 0, enable_colors);
        cout << " экспонента(порядок)";
    }

    //mantissa
    this->SetOutputColor(6, 0, enable_colors);
    cout << " матисса" << endl;
    this->SetOutputColor();


    //sign
    this->SetOutputColor(2,0,enable_colors);
    cout << bin_result[0];

    //sign separation
    if (data_type_code >= 0 && data_type_code <= 7 || data_type_code >= 8 && data_type_code <= 10 || data_type_code == 11)
        cout << ' ';

    //exponent
    if (exponent_size != 0)
    {
        this->SetOutputColor(4, 0, enable_colors);
        for (int i = 1; i <= exponent_size; i++)
        {
            cout << bin_result[i];
        }
        cout << ' ';
    }

    //mantissa
    this->SetOutputColor(6, 0, enable_colors);
    for (int i = exponent_size + 1; i < sizeof_data_type_value_x8; i++)
    {
        cout << bin_result[i];
    }
    cout << endl;


    this->SetOutputColor();
    return 1;
};

char* BinaryRepresentation::convert_bin_to_dec() {
    if (!bin_is_initialized)
    {
        cout << endl << endl << "\t+=========================================================+" << endl
            << "\t|Attention! You didn't convert a decimal number to binary!|" << endl
            << "\t+=========================================================+" << endl << endl;
        return nullptr;
    }

    //check for the list of supported variable data types
    if (data_type_code > 12 || data_type_code == 10)
    {
        cout << "Переменная не может быть преобразована в десятичное представление, поскольку ее нет в списке поддерживаемых" << endl;
        cout << "The variable cannot be converted to a decimal representation because it is not in the supported list" << endl;
        return nullptr;
    }

    unsigned long long preliminary_integer_value = 0;
    long double preliminary_fractional_value = 0;

    bool is_null = true;
    bool is_negative = false;

    unsigned short integer_length = 0;
    unsigned short fractional_length = 0;
    unsigned short total_length = 0;

    //creating a copy of the bin_result array
    char* bin_result_copy = new char[sizeof_data_type_value_x8 + 1]{ 0 };
    this->char_array_copy(bin_result_copy, sizeof_data_type_value_x8, bin_result);

    //checking for zero
    for (int i = 0; i < sizeof_data_type_value_x8; i++)
    {
        if (bin_result_copy[i] == '1') {
            is_null = false;
            break;
        }
    }

    ///***********************************///
    ///            PROCESSING             ///
    ///***********************************///

    //U integer types and U char types
    if ((data_type_code >= 4 && data_type_code <= 7 || data_type_code == 12) && !is_null) {
        for (int i = 0; i < sizeof_data_type_value_x8; i++)
            if (bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] == '1')
            {
#ifdef DEBUG
                cout << "bin_result_copy[(sizeof_data_type_value_x8 - 1) - i[" << i << "] [=" << (sizeof_data_type_value_x8 - 1) - i << "]] = " << bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] << "   " << (pow(2, i)) << endl;
#endif // DEBUG
                preliminary_integer_value += static_cast<unsigned long long>(pow(2, i));
            }

        //return 1;
    }
    //out: preliminary_integer_value (UNSIGNED) <- if not null. 


    //S integer types and S char types
    if ((data_type_code >= 0 && data_type_code <= 3 || data_type_code == 11) && !is_null) {
        // pre-processing for a negative value 
        if (bin_result_copy[0] == '1')
        {
            short index_first_one_from_the_end;

            is_negative = true;

            // search first '1' from the end
            for (int i = sizeof_data_type_value_x8 - 1; i >= 0; i--)
            {
                if (bin_result_copy[i] == '1') {
                    index_first_one_from_the_end = i;
                    break;
                }
            }

            // subtracting one
            if (index_first_one_from_the_end == sizeof_data_type_value_x8 - 1)
                bin_result_copy[index_first_one_from_the_end] = '0';
            else
            {
                for (int i = index_first_one_from_the_end; i < sizeof_data_type_value_x8; i++)
                    bin_result_copy[i] = '1';
                bin_result_copy[index_first_one_from_the_end] = '0';
            }

            // invert
            for (int i = 0; i < sizeof_data_type_value_x8; i++)
            {
                if (bin_result_copy[i] == '1')
                    bin_result_copy[i] = '0';
                else
                    bin_result_copy[i] = '1';
            }
        }

        for (int i = 0; i < sizeof_data_type_value_x8; i++) {
            if (bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] == '1')
            {
#ifdef DEBUG
                cout << "bin_result_copy[(sizeof_data_type_value_x8 - 1) - i[" << i << "] [=" << (sizeof_data_type_value_x8 - 1) - i << "]] = " << bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] << "   " << (pow(2, i)) << endl;
#endif // DEBUG
                preliminary_integer_value += static_cast<unsigned long long>(pow(2, i));
            }
        }
    }
    //out: preliminary_integer_value (UNSIGNED) && is_negative <- if not null.


    //floating point-based types
    if ((data_type_code >= 8 && data_type_code <= 9) && !is_null)
    {
        short exponent_value = 0;

        if (bin_result_copy[0] == '1')
            is_negative = true;

        // exponent
        for (short i = 1; i <= exponent_size; i++)
        {
#ifdef DEBUG
            cout << "bin_result_copy[(exponent_size + 1 - i[" << i << "] [=" << exponent_size - i + 1 << "]] = " << bin_result_copy[exponent_size - i + 1] << "   " << (pow(2, i - 1)) << endl;
#endif // DEBUG
            if (bin_result_copy[exponent_size - i + 1] == '1')
                exponent_value += static_cast<short>(pow(2, i - 1));
        }
        // subtracting the offset
        switch (data_type_code)
        {
        case 8:
            exponent_value -= 127;
            break;
        case 9:
            exponent_value -= 1023;
            break;
        default:
            break;
        }


        //mantissa
        if (exponent_value == 0)
        {
            preliminary_integer_value = 1;
            for (int i = exponent_size + 1; i < sizeof_data_type_value_x8; i++)
            {
#ifdef DEBUG
                cout << "preliminary_fractional_value i[" << i << "]  [" << (exponent_size + 1) - i - 1 << "] " << bool(bin_result_copy[i] == '1') << " = " << pow(2, (exponent_size + 1) - i - 1) << endl;
#endif // DEBUG
                if (bin_result_copy[i] == '1')
                {
                    preliminary_fractional_value += pow(2, (exponent_size + 1) - i - 1);
                }
            }
        }

        if (exponent_value > 0)
        {
            //integer
            for (int i = exponent_size + exponent_value; i > exponent_size; i--)
            {
#ifdef DEBUG
                cout << "preliminary_integer_value i[" << i << "]  [" << exponent_size + exponent_value - i << "] " << bool(bin_result_copy[i] == '1') << " = " << unsigned long long(pow(2, exponent_size + exponent_value - i)) << endl;
#endif // DEBUG
                if (bin_result_copy[i] == '1')
                    preliminary_integer_value += static_cast<unsigned long long>(pow(2, exponent_size + exponent_value - i));

                if (i == exponent_size + 1) {
#ifdef DEBUG
                    cout << "pow(2, exponent_size + exponent_value - i + 1) = " << unsigned long long(pow(2, exponent_size + exponent_value - i + 1)) << endl;
#endif // DEBUG
                    preliminary_integer_value += static_cast<unsigned long long>(pow(2, exponent_size + exponent_value - i + 1)); //CAN BE OPTIMIZED
                }
            }

            //after dot
            for (int i = exponent_size + exponent_value + 1; i < sizeof_data_type_value_x8; i++)
            {
#ifdef DEBUG
                cout << "preliminary_fractional_value i[" << i << "]  [" << (exponent_size + exponent_value + 1) - i - 1 << "] " << bool(bin_result_copy[i] == '1') << " = " << pow(2, (exponent_size + exponent_value + 1) - i - 1) << endl;
#endif // DEBUG
                if (bin_result_copy[i] == '1')
                    preliminary_fractional_value += pow(2, (exponent_size + exponent_value + 1) - i - 1);
            }

        }

        if (exponent_value < 0)
        {
            //after dot
            for (int i = exponent_size + 1; i < sizeof_data_type_value_x8; i++)
            {
#ifdef DEBUG
                cout << "preliminary_fractional_value i[" << i << "]  [" << (exponent_size + 1) - i - 1 + exponent_value << "] " << bool(bin_result_copy[i] == '1') << " = " << pow(2, (exponent_size + 1) - i - 1 + exponent_value) << endl;
#endif // DEBUG
                if (bin_result_copy[i] == '1')
                {
                    preliminary_fractional_value += pow(2, (exponent_size + 1) - i - 1 + exponent_value);
                }
            }
            preliminary_fractional_value += pow(2, exponent_value);
#ifdef DEBUG
            cout << "pow(2, exponent_value) = " << pow(2, exponent_value) << endl;
#endif // DEBUG
        }
    }
    //out: preliminary_integer_value (UNSIGNED) && preliminary_fractional_value (POSITIVE) && is_negative <- if not null.


    ///**********************************///
    ///            TO STRING             ///
    ///**********************************///

    dec_result = new char[30]{ 0 };
    char dec_result_int_buffer[30]{ 0 };
    char dec_result_fra_buffer[30]{ 0 };

    //INT
    sprintf_s(dec_result_int_buffer, "%llu", preliminary_integer_value);

    //FLOAT POINT-BASED
    switch (data_type_code)
    {
    case 8:
        sprintf_s(dec_result_fra_buffer, "%0.*f", static_cast<unsigned int>(9 - (preliminary_integer_value == 0 ? 0 : strlen(dec_result_int_buffer))), preliminary_fractional_value);
        break;
    case 9:
        sprintf_s(dec_result_fra_buffer, "%0.*f", static_cast<unsigned int>(17 - (preliminary_integer_value == 0 ? 0 : strlen(dec_result_int_buffer))), preliminary_fractional_value);
        break;
    default:

        break;
    }

    // string factory
    if (is_negative)
        dec_result[0] = '-';
    this->char_array_copy(dec_result, strlen(dec_result_int_buffer), dec_result_int_buffer, is_negative); //int
    if (preliminary_fractional_value != 9)
        this->char_array_copy(dec_result, strlen(dec_result_fra_buffer) + 1, dec_result_fra_buffer, strlen(dec_result_int_buffer) + is_negative, 1);

    ////string cleaner
    //int dec_result_strlen = strlen(dec_result);
    //for (int i = 0; i <= dec_result_strlen; i++)
    //{
    //    if (dec_result[dec_result_strlen - i] == '0')
    //        dec_result[dec_result_strlen - i] = 0;
    //    else
    //        break;
    //}

#ifdef DEBUG_RESULT
    /*cout << "dec_result_strlen = " << dec_result_strlen << endl;*/

    cout << "dec_result_int_buffer = " << dec_result_int_buffer << ' ' << strlen(dec_result_int_buffer) << endl;
    cout << "dec_result_fra_buffer = " << dec_result_fra_buffer << ' ' << strlen(dec_result_fra_buffer) << endl;
    cout << "dec_result = " << dec_result << ' ' << strlen(dec_result) << endl;

    cout << "is_null = " << is_null << endl;
    cout << "is_negative = " << is_negative << endl;
    cout << "preliminary_integer_value = " << preliminary_integer_value << endl;
    cout << "preliminary_fractional_value = " << preliminary_fractional_value << endl << endl << endl;
#endif // DEBUG_RESULT

    dec_is_initialized = true;
    delete[] bin_result_copy;
    return dec_result;
};


//getters
char* BinaryRepresentation::get_dec_representation() {
    if (!dec_is_initialized) {
        cout << endl << endl << "\t+=========================================================+" << endl
            << "\t|Attention! You didn't convert a binary number to decimal!|" << endl
            << "\t+=========================================================+" << endl << endl;
        return nullptr;
    }
    return dec_result;
}

char* BinaryRepresentation::get_bin_representation() {
    if (!bin_is_initialized) {
        cout << endl << endl << "\t+=========================================================+" << endl
            << "\t|Attention! You didn't convert a decimal number to binary!|" << endl
            << "\t+=========================================================+" << endl << endl;
        return nullptr;
    }
    return bin_result;
}


//setters
void BinaryRepresentation::set_enable_colors(bool enable) {
    enable_colors = enable;
}



//private
void BinaryRepresentation::SetOutputColor(int text, int bg, bool is_enable_colors) {
    if (is_enable_colors)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
    }
}

void BinaryRepresentation::initialize_the_data_type_code() {
    //converting the variable type to a numeric code: find the sum of the codes of all characters of the data type, getting the preliminary data type code
    unsigned short preliminary_data_type_code = 0;
    for (int i = 0; i < strlen(data_type); i++)
    {
        preliminary_data_type_code += data_type[i];
    }

    // setting the final code of the data type
    // S = Signed; U = Unsigned; __int64 = long long
    switch (preliminary_data_type_code)
    {
        // SECTION 1: SIGNED INTEGER
    case 560: //S short
        data_type_code = 0;
        exponent_size = 0;
        break;

    case 331: //S int
        data_type_code = 1;
        exponent_size = 0;
        break;

    case 432: //S long
        data_type_code = 2;
        exponent_size = 0;
        break;

    case 627: //S __int64
        data_type_code = 3;
        exponent_size = 0;
        break;

        // SECTION 2: UNSIGNED INTEGER
    case 1453: //U short
        data_type_code = 4;
        exponent_size = 0;
        break;

    case 1224: //U int
        data_type_code = 5;
        exponent_size = 0;
        break;

    case 1325: //U long
        data_type_code = 6;
        exponent_size = 0;
        break;

    case 1520: //U __int64
        data_type_code = 7;
        exponent_size = 0;
        break;

        // SECTION 3: FLOATING POINT–BASED
    case 534: //float
        data_type_code = 8;
        exponent_size = 8;
        break;

    case 635: //double
        data_type_code = 9;
        exponent_size = 11;
        break;

    case 1099: //long double
        data_type_code = 10;
        exponent_size = 0; // WARNING
        break;

        // SECTION 4: CHARACTER
    case 414: //S char
        data_type_code = 11;
        exponent_size = 0;
        break;

    case 1307: //U char
        data_type_code = 12;
        exponent_size = 0;
        break;

        // SECTION 5: ANOTHER
    default: //everything else, if not included in the supported list
        data_type_code = 9999;
        exponent_size = 0;
        break;
    }
}

void BinaryRepresentation::char_array_copy(char* destination_str, size_t number_of_characters_to_copy, const char* source_str, size_t destination_pos_offset, size_t source_pos_offset, bool replace_spaces_with_underscores) {
    for (size_t i = 0; i < number_of_characters_to_copy; i++)
        destination_str[i + destination_pos_offset] = source_str[i + source_pos_offset];
    
    destination_str[number_of_characters_to_copy + destination_pos_offset] = '\0';
    
    // Replacing spaces with underscores
    if (replace_spaces_with_underscores)
        for (size_t i = 0; i < number_of_characters_to_copy; i++)
            if (destination_str[i] == ' ')
                destination_str[i] = '_';
}

bool BinaryRepresentation::compare_arrays(const char* first_array, const char* second_array) {
    if (strlen(first_array) != strlen(second_array))
        return false;

    for (size_t i = 0; i < strlen(first_array); i++)
        if (first_array[i] != second_array[i])
            return false;

    return true;
}



BinaryRepresentation::BinaryRepresentation() {
    bin_result = nullptr;
    dec_result = nullptr;
    data_type = nullptr;

    bin_is_initialized = false;
    dec_is_initialized = false;
	enable_colors = false;

	data_type_code = 0;
    sizeof_data_type_value_x8 = 0;
    exponent_size = 0;
}
BinaryRepresentation::~BinaryRepresentation() {
    delete[] bin_result;
    delete[] dec_result;
    delete[] data_type;
}

//Задание к практической работе №1 "ТИПЫ ДАННЫХ И ИХ ВНУТРЕННЕЕ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ"
//
//Разработать алгоритм и написать программу, которая позволяет :
//
// +1) Вывести, сколько памяти(в байтах) на вашем компьютере отводится под различные типы данных со спецификаторами и без : int, short int, long int, float, double, long double, char и bool.
//
// 2) Вывести на экран двоичное представление в памяти(все разряды) целого числа.При выводе необходимо визуально обозначить знаковый разряд и значащие разряды отступами или цветом.
//
// 3) Вывести на экран двоичное представление в памяти(все разряды) типа float.При выводе необходимо визуально обозначить знаковый разряд мантиссы, знаковый разряд порядка(если есть), мантиссу и порядок.
//
// 4) Вывести на экран двоичное представление в памяти(все разряды) типа double.При выводе необходимо визуально обозначить знаковый разряд мантиссы, знаковый разряд порядка(если есть), мантиссу и порядок. (*)
//
//(*) - Задание повышенной сложности.Подобные задания могут использовать методы и структуры следующих модулей.