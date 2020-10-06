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

void BinaryRepresentation::initialize_the_data_type_code() {
    //converting the variable type to a numeric code: find the sum of the codes of all characters of the data type, getting the preliminary data type code
    unsigned short preliminary_data_type_code = 0;
    for (size_t i = 0; i < strlen(data_type); i++)
    {
        preliminary_data_type_code += data_type[i];
    }

    //setting the final code of the data type
    //P.s. S = Signed; U = Unsigned; __int64 = long long
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
        data_type_code = preliminary_data_type_code;
        exponent_size = 0;
        break;
    }
}

void BinaryRepresentation::char_array_copy(char* destination_str, size_t number_of_characters_to_copy, const char* source_str, bool replace_spaces_with_underscores) {
    for (size_t i = 0; i < number_of_characters_to_copy; i++)
        destination_str[i] = source_str[i];
    destination_str[number_of_characters_to_copy] = '\0';
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
	enable_colors = true;

	data_type_code = 0;
    variable_value = 0;
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