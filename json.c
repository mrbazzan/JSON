
#include "json.h"


str parse_number(str string){
    double num = 0;
    int power = 0, sign = 1, inner_sign = 1, exp_power = 0;

    if(*string == '-'){  // sign in-front of number.
        sign = -1; string++;
    }
    //TODO: Rework the condition here
    if(*string >= '0' && *string <= '9'){ // normal number.
        do{
            num = (num * 10) + (*string - '0'); string++;
        }while (*string >= '0' && *string <= '9');
    }
    if(*string == '.'){ string++; }
    if(*string >= '0' && *string <= '9'){  // decimal part of number.
        do{
            num = (num * 10) + (*string - '0'); string++; power--;
        }while (*string >= '0' && *string <= '9');
    }
    if(*string == 'e' || *string == 'E'){ string++; }
    if(*string == '+'){ string++; } // sign in-front of exponential.
    else if(*string == '-'){ string++; inner_sign = -1;}
    if(*string >= '0' && *string <= '9'){ // exponential power.
        do{
            exp_power = (exp_power * 10) + (*string - '0'); string++;
        }while (*string >= '0' && *string <= '9');
    }
    if (*string == '\"') {string++;}

    return string;
}


str parse_string(str string){
    int len = 0;
    str ptr = string+1, str_ptr, space_ptr;

    if(*string!='\"'){ return 0; }

    while(*ptr != '\"' && *ptr>31){
        len++;
        if(*ptr == '\\'){ ptr++;}
        ptr++;
    }

    ptr = string+1;

    str_ptr = malloc(len+1);
    space_ptr = str_ptr;

    while(*ptr != '\"' && *ptr>31){
        if(*ptr == '\\'){
            ptr++;
            switch (*ptr){
                case 'b':
                    *space_ptr = '\b'; space_ptr++;
                    break;
                case 'f':
                    *space_ptr = '\f'; space_ptr++;
                    break;
                case 'n':  // replace \\n --> \\\n
                    *space_ptr = '\n'; space_ptr++;
                    break;
                case 'r':
                    *space_ptr = '\r'; space_ptr++;
                     break;
                case 't':
                    *space_ptr = '\t'; space_ptr++;
                    break;
                case 'u':
                case 'U':
                    // TODO: utf16 to utf8 conversion.
                    break;

                default:
                    *space_ptr = *ptr; space_ptr++;
                    break;
            }
            ptr++;
        }
        else{
            *space_ptr = *ptr;
            space_ptr++; ptr++;
        }
    }
    space_ptr=0;
    if (*ptr == '\"') {ptr++;}

    return ptr;
}
