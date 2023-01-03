
#include "json.h"


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
