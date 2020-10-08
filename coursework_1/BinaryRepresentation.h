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
    // Attention: the "long double" data type is not supported. Maximum size of a variable in memory: 8 bytes
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

        variable_value = (long double)all_standart_data_type_value;
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

        initialize_the_data_type_code();
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
            for (size_t i = 1; i <= exponent_size; i++)
            {
                cout << bin_result[i];
            }
            cout << ' ';
        }

        //mantissa
        for (size_t i = exponent_size + 1; i < sizeof_data_type_value_x8; i++)
        {
            cout << bin_result[i];
        }
        cout << endl;

        return 1;
    };

    //returns 1 if the operation was successful; 0 if an error occurred or some variables were not initialized
    bool convert_bin_to_dec() {
        if (!bin_is_initialized)
        {
            cout << endl << endl << "\t+=========================================================+" << endl
                                 << "\t|Attention! You didn't convert a decimal number to binary!|" << endl
                                 << "\t+=========================================================+" << endl << endl;
            return 0;
        }

        //check for the list of supported variable data types
        if (data_type_code > 12 || data_type_code == 10)
        {
            cout << "Переменная не может быть преобразована в десятичное представление, поскольку ее нет в списке поддерживаемых" << endl;
            cout << "The variable cannot be converted to a decimal representation because it is not in the supported list" << endl;
            return 0;
        }

        unsigned long long preliminary_integer_value = 0;
        long double preliminary_fractional_value = 0;
        
        bool is_null = true;
        bool is_negative = false;

        //creating a copy of the bin_result array
        char* bin_result_copy = new char[sizeof_data_type_value_x8 + 1]{ 0 };
        char_array_copy(bin_result_copy, sizeof_data_type_value_x8, bin_result);

        //checking for zero
        for (size_t i = 0; i < sizeof_data_type_value_x8; i++)
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
            for (size_t i = 0; i < sizeof_data_type_value_x8; i++)
                if (bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] == '1')
                {
#ifdef DEBUG
                    cout << "bin_result_copy[(sizeof_data_type_value_x8 - 1) - i[" << i << "] [=" << (sizeof_data_type_value_x8 - 1) - i << "]] = " << bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] << "   " << (pow(2, i)) << endl;
#endif // DEBUG
                   preliminary_integer_value += unsigned long long(pow(2, i));
                }

            //return 1;
        }
        //out: preliminary_integer_value <- if not null. 


        //S integer types and S char types
        if ((data_type_code >= 0 && data_type_code <= 3 || data_type_code == 11) && !is_null) {
            // processing for a negative value 
            if (bin_result_copy[0] == '1')
            {
                short index_first_one_from_the_end;

                is_negative = true;

                // search first '1' from the end
                for (short i = sizeof_data_type_value_x8 - 1; i >= 0; i--)
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
                    for (size_t i = index_first_one_from_the_end; i < sizeof_data_type_value_x8; i++)
                        bin_result_copy[i] = '1';
                    bin_result_copy[index_first_one_from_the_end] = '0';
                }

                // invert
                for (size_t i = 0; i < sizeof_data_type_value_x8; i++)
                {
                    if (bin_result_copy[i] == '1')
                        bin_result_copy[i] = '0';
                    else
                        bin_result_copy[i] = '1';
                }
            }

            for (size_t i = 0; i < sizeof_data_type_value_x8; i++) {
                if (bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] == '1')
                {
#ifdef DEBUG
                    cout << "bin_result_copy[(sizeof_data_type_value_x8 - 1) - i[" << i << "] [=" << (sizeof_data_type_value_x8 - 1) - i << "]] = " << bin_result_copy[(sizeof_data_type_value_x8 - 1) - i] << "   " << (pow(2, i)) << endl;
#endif // DEBUG
                    preliminary_integer_value += unsigned long long(pow(2, i));
                }
            }
        }
        //out: preliminary_integer_value (UNSIGNED) && is_negative <- if not null.
        
        cout.precision(50); //WARNING

        //floating point-based types
        short exponent_value = 0; //WARNING
        if ((data_type_code >=8 && data_type_code <= 9) && !is_null)
        {
            //short exponent_value = 0;

            if (bin_result_copy[0] == '1')
                is_negative = true;

            // exponent
            for (size_t i = 1; i <= exponent_size; i++)
            {
#ifdef DEBUG
                cout << "bin_result_copy[(exponent_size + 1 - i[" << i << "] [=" << exponent_size - i + 1 << "]] = " << bin_result_copy[exponent_size - i + 1] << "   " << (pow(2, i - 1)) << endl;
#endif // DEBUG
                if (bin_result_copy[exponent_size - i + 1] == '1')
                    exponent_value += unsigned long long(pow(2, i - 1));
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
                    cout << "preliminary_fractional_value i[" << i << "]  [" << (exponent_size + 1) - i - 1 << "] " << bool(bin_result_copy[i] == '1') << " = "<< pow(2, (exponent_size + 1) - i - 1) << endl;
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
                        preliminary_integer_value += unsigned long long (pow(2, exponent_size + exponent_value - i));

                    if (i == exponent_size + 1) {
#ifdef DEBUG
                        cout << "pow(2, exponent_size + exponent_value - i + 1) = " << unsigned long long(pow(2, exponent_size + exponent_value - i + 1)) << endl;
#endif // DEBUG
                        preliminary_integer_value += unsigned long long(pow(2, exponent_size + exponent_value - i + 1));
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
                //integer
                preliminary_integer_value = 0; //WARNING

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



        // ОСТАНОВИЛСЯ ТУТ: добавить bool, сообщающий об успешном переводе, рассчитать количество цифр после точки и записать все это в массив char

#ifdef DEBUG_RESULT
        cout << "is_null = " << is_null << endl;
        cout << "is_negative = " << is_negative << endl;
        cout << "exponent_value = " << exponent_value << endl;
        cout << "preliminary_integer_value = " << preliminary_integer_value << endl;
        cout << "preliminary_fractional_value = " << preliminary_fractional_value << endl << endl << endl;
#endif // DEBUG_RESULT

        delete[] bin_result_copy;
        return 0;
    };

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
    void char_array_copy(char* destination_str, size_t number_of_characters_to_copy, const char* source_str, bool replace_spaces_with_underscores = false);

    bool compare_arrays(const char* first_array, const char* second_array);
};

//cout.setf(ios::fixed); //WARNING
//cout.precision(16);
