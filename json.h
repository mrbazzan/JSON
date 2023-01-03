
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define JSON_NULL 0
#define TRUE 1
#define FALSE 2
#define NUMBER 3
#define JSON_STRING 4
#define ARRAY 5
#define OBJECT 6

typedef char * str;

typedef struct JSON{
    struct JSON *child;
    struct JSON *inner, *outer;

    unsigned int type;

    int int_value;
    double double_value;
    str str_value;
    str key;
} JSON;

//prototype
str parse_value(JSON *item, str string);
str parse_array(JSON *item, str string);
str parse_object(JSON *item, str string);

void free_memory(JSON *item);
