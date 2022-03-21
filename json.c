
#include "json.h"


str parse_number(str string){
    double num = 0;
    int power = 0, sign = 1, inner_sign = 1, exp_power = 0;

    if (*string == '\"'){ string++; }

    while (*string != '\"'){
        if(*string == '-'){  // sign in-front of number.
            sign = -1; string++;
        }
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
    }
    if (*string == '\"') {string++;}

    return string;
}
