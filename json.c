
#include "json.h"


str parse_number(JSON *item, str string){
    double num = 0;
    int power = 0, sign = 1, inner_sign = 1, exp_power = 0;

    if(*string == '-'){  // sign in-front of number.
        sign = -1; string++;
    }
    if(*string == '0') { string++; }
    if(*string >= '1' && *string <= '9'){ // normal number.
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

    num = sign*num*pow(10, power+(inner_sign*exp_power));

    item->type = NUMBER;
    item->double_value = num;
    item->int_value = (int)num;

    return string;
}


str parse_string(JSON *item, str string){
    int len = 0;
    str ptr = string+1, str_ptr, space_ptr;

    if(*string!='\"'){ return 0; }

    while(*ptr != '\"' && *ptr>31){
        len++;
        if(*ptr == '\\'){ ptr++;}
        ptr++;
    }

    ptr = string+1;

    str_ptr = calloc(sizeof(char), len+1);
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

    item->type = JSON_STRING;
    item->str_value = str_ptr;
    return ptr;
}


str parse_value(JSON *item, str string){

    if(!string){ return 0; } // error
    if(*string == '\"'){
        return parse_string(item, string);
    }
    if (*string=='-' || (*string>='0' && *string<='9')){
        return parse_number(item, string);
    }

    if(*string=='{') {return parse_object(item, string);}

    if (*string=='['){
        return parse_array(item, string);
    }
    if (!strncmp(string, "true", 4)){ item->type = TRUE; return string+4; }
    if (!strncmp(string, "false", 5)){ item->type = FALSE; return string+5; }
    if (!strncmp(string, "null", 4)){ item->type = JSON_NULL; return string+4; }

    return 0; // There is an error.
}


str space(str item){
    // skip whitespace between tokens
    while(*item && *item<=32){ item++; }
    return item;
}


str parse_array(JSON *item, str string){
    if(*string != '[') { return 0; } // It does not start with [

    // Skip whitespace
    string = space(string+1);

    // Empty array
    if (*string == ']'){ item->type = ARRAY; return string+1;}

    JSON *a = calloc(sizeof(JSON), 1);
    item->child = a; a->outer = item;

ARRAY_LOOP:
    string = space(parse_value(a, string));

    // Parse inner items
    while (*string==','){
        JSON *b = calloc(sizeof(JSON), 1);
        a->inner = b; b->outer = a; a=b;

        string = space(string+1);
        goto ARRAY_LOOP;
    }

    // properly parsed.
    if(*string==']'){ item->type = ARRAY; return string+1;}
    return 0; // An error has occurred somewhere.
}


str parse_object(JSON *item, str string){

    if(*string != '{'){ return 0; }  // not a json object

    string = space(string+1);
    if(*string == '}'){ item->type=OBJECT; return string+1; }  // empty json object

    JSON *a = calloc(sizeof(JSON), 1);
    item->child = a; a->outer = item;

LOOP:
    if(*string != '\"') { return 0; } // error: not a string

    string = space(parse_string(a, string));
    a->key=a->str_value; a->str_value=NULL;

    if(*string != ':') { return 0; }  // error: ":" not present
    string = parse_value(a, space(string+1));

    while(*string==','){

        JSON *b = calloc(sizeof(JSON), 1);
        a->inner = b; b->outer = a; a=b;

        string = space(string+1);
        goto LOOP;
    }

    string = space(string);
    if (*string == '}') { item->type=OBJECT; return string+1; } // complete json

    return 0; // error!
}
