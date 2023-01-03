
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
            break;
        case JSON_STRING:
            break;
        case ARRAY:
            break;
        case OBJECT:
            break;
    }
    return string;
}
