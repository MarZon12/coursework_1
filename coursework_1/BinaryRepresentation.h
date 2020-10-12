#pragma once
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

//#define DEBUG
#define DEBUG_RESULT



class BinaryRepresentation
{
public:
    BinaryRepresentation();
    ~BinaryRepresentation();

    // displays the amount of memory used by different types of variables
	void cout_weight_data_types();

    // [- - - - - - - - - - - - - - - - - - - - - - - - - - IEEE 754 - - - - - - - - - - - - - - - - - - - - - - - - - - -]                                     
    // Converts values of various standard data types to a binary representation and writes them to an array of characters.
    // - - returns a pointer to an array of characters in the binary representation of the value received as a parameter - -
    // - - - - - - - - - - - - - - - - - - - - - - - - - - Attention - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // The "long double" data type is not supported. Maximum size of a variable in memory: 8 bytes
    // Special States, such as +-Infinity or NaN, are not processed. 
    // Values presented in denormalized form are also not processed.
    template <typename T>
    char* convert_dec_to_bin(T all_standart_data_type_value) {
        union ToolUnion {
            long long tool;
            T data_type_value;
        };
        ToolUnion tools;
        tools.data_type_value = all_standart_data_type_value;

        // initialization
        data_type = new char[strlen(typeid(all_standart_data_type_value).name()) + 1];
        char_array_copy(data_type, strlen(typeid(all_standart_data_type_value).name()), typeid(all_standart_data_type_value).name());
        initialize_the_data_type_code();
        if (data_type_code > 12 || data_type_code == 10)
        {
            cout << "Переменная не может быть преобразована в двоичное представление, поскольку ее нет в списке поддерживаемых типов данных" << endl;
            cout << "The variable cannot be converted to a binary representation because it is not in the supported data types list" << endl;
            return nullptr;
        }

        variable_value = static_cast<long double>(all_standart_data_type_value);
        sizeof_data_type_value_x8 = 8 * sizeof(tools.data_type_value);

        bin_result = new char[sizeof_data_type_value_x8 + 1]{ 0 };

        // performs a bitwise conjunction, then writes the result to an array
        for (int i = sizeof_data_type_value_x8 - 1; i >= 0; i--)
        {
            if ((tools.tool >> i) & 0b00000001) 
                bin_result[sizeof_data_type_value_x8 - 1 - i] = '1';
            else
                bin_result[sizeof_data_type_value_x8 - 1 - i] = '0';
        }

        bin_is_initialized = true;

        cout_binary_representation(); //WARNING
        convert_bin_to_dec(); //WARNING

        return bin_result;
	};

    //returns 1 if output is successful; 0 if an error occurred or some variables were not initialized
    bool cout_binary_representation() {
        if (!bin_is_initialized)
        {
            cout << endl << endl << "\t+=========================================================+" << endl
                                 << "\t|Attention! You didn't convert a decimal number to binary!|" << endl
                                 << "\t+=========================================================+" << endl << endl;
            return 0;
        }
        
        //17 double; 
        cout.precision(19);
        
        cout << "Тип переменной: " << data_type << endl;//" code: " << data_type_code << endl;
        cout << "Значение: " << variable_value << endl;
   
        cout << "Формат представления: знак экспонента(порядок) матисса" << endl;
  
        //знак
        //sign
        cout << bin_result[0];

        //отделение знака
        if (data_type_code >= 0 && data_type_code <= 3 || data_type_code >= 8 && data_type_code <= 10 || data_type_code == 11)
            cout << ' ';

        //exponent
        if (exponent_size != 0)
        {
            for (int i = 1; i <= exponent_size; i++)
            {
                cout << bin_result[i];
            }
            cout << ' ';
        }

        //mantissa
        for (int i = exponent_size + 1; i < sizeof_data_type_value_x8; i++)
        {
            cout << bin_result[i];
        }
        cout << endl;

        return 1;
    };

    //returns 1 if the operation was successful; 0 if an error occurred or some variables were not initialized
    bool convert_bin_to_dec();

    //getters

    //returns a pointer to an array of characters if the operation was successful; nullptr if an error occurred or some variables were not initialized
    char* get_dec_representation() {
        if (!dec_is_initialized) {
            cout << endl << endl << "\t+=========================================================+" << endl
                                 << "\t|Attention! You didn't convert a binary number to decimal!|" << endl
                                 << "\t+=========================================================+" << endl << endl;
            return nullptr;
        }
        return dec_result;
    }

    //returns a pointer to an array of characters if the operation was successful; nullptr if an error occurred or some variables were not initialized
    char* get_bin_representation() {
        if (!bin_is_initialized) {
            cout << endl << endl << "\t+=========================================================+" << endl
                                 << "\t|Attention! You didn't convert a decimal number to binary!|" << endl
                                 << "\t+=========================================================+" << endl << endl;
            return nullptr;
        }
        return bin_result;
    }

private:
    // stores the binary representation of a number
    char* bin_result;

    // stores the data type of the variable, received as an argument, in an array of characters
    char* data_type;
    
    // stores the decimal representation of a number
    char* dec_result;

    // Signed integer: 0 = short; 1 = int; 2 = long; 3 = __int64
    // Unsigned integer: 4 = short; 5 = int; 6 = long; 7 = __int64
    // Floating point-based: 8 = float; 9 = double; 10 = long double
    // Character: 11 = Signed char; 12 = Unsigned char
    // Another: N = everything else, if not included in the supported list
    // - - - - - - - - - - - - - - - - INFO - - - - - - - - - - - - - - - -
    // 10 <- introduced for possible implementation in future updates
    // default: 0
    unsigned short data_type_code;

    long double variable_value; //default: 0
    int sizeof_data_type_value_x8; //default: 0

    // number of bits of memory occupied by the exponent
    // default: 0
    unsigned short exponent_size;
    
    // settings
    bool bin_is_initialized; //default: false
    bool dec_is_initialized; //default: false
    bool enable_colors;  //default: true


    void initialize_the_data_type_code();

    // don't forget to leave the last character of the array under the null-terminator, which means the end of the string
    void char_array_copy(char* destination_str, size_t number_of_characters_to_copy, const char* source_str, size_t destination_pos_offset = 0, size_t source_pos_offset = 0, bool replace_spaces_with_underscores = false);

    bool compare_arrays(const char* first_array, const char* second_array);

    
};

//cout.setf(ios::fixed); //WARNING
//cout.precision(16);

// добавить взятие значения заместо копирования переменной, ц: оптимизация памяти
// const MyString & other <- оптимизация памяти