
#include "json.h"


str print_number(JSON *item){
    double d = item->double_value;
    int length;

    // In representing large number types, set aside
    // at most 20 characters to represent number
    //
    str arr = malloc(64);

    if (arr == NULL){
        printf("Memory not allocated");
        exit(1);
    }

    if (item->int_value == d){
        length = sprintf(arr, "%d", item->int_value);
    }else{
        if (fabs(item->int_value - d) < 10e-6 || fabs(item->int_value -d) > 10e9){
            length = sprintf(arr, "%e", item->double_value);
        } else {
            length = sprintf(arr, "%f", item->double_value);
        }
    }

    if (length < 0){
        printf("print number error");
        exit(1);
    }

    return arr;
}


str _print_string(str string){
    int string_length = 0;

    str ptr = string;
    str output, str_ptr;

    // Count the length of **string**
    while(*ptr){
        string_length++;

        // Ensure that when a special character is encountered, 1 is added
        // to the total length to account for its escape character. i.e
        // The length of '\t' is 2 (\\ + \t)
        if (*ptr < 32 || *ptr == '\\' || *ptr == '\"'){
            string_length++;
        }
        ptr++;
    }
    ptr = string;

    // we are adding 3 because of the opening, closing quote and null.
    output = malloc(sizeof(char) * string_length+3);
    str_ptr = output;

    *str_ptr++ = '\"';
    while(*ptr){
        if(*ptr < 32 || *ptr == '\"' || *ptr == '\\'){
            *str_ptr++ = '\\';
            switch (*ptr){
                case '\b': *str_ptr++ = 'b'; break;
                case '\f': *str_ptr++ = 'f'; break;
                case '\n': *str_ptr++ = 'n'; break;
                case '\r': *str_ptr++ = 'r'; break;
                case '\t': *str_ptr++ = 't'; break;
                case '\"':
                case '\\':
                    *str_ptr++ = *ptr; break;

                default:
                    str_ptr--;  // remove the '\\'
                    break;
            }
            ptr++;
        }
        else{
            *str_ptr++ = *ptr++;
        }
    }

    *str_ptr++ = '\"';
    *str_ptr++ = 0;

    return output;
}


str print_string(JSON *item) {
    return _print_string(item->str_value);
}


extern str JSON_print(JSON *item){
    str string = 0;
    switch(item->type){
        case JSON_NULL:
            break;
        case TRUE:
            break;
        case FALSE:
            break;
        case NUMBER:
            string = print_number(item); break;
        case JSON_STRING:
            string = print_string(item); break;
        case ARRAY:
            break;
        case OBJECT:
            break;
    }
    return string;
}
