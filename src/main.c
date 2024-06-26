/*
Diferencia entre 
    #include <header1.h>
    #include "header2.h"
*/

#include <greetings.h>
#include <stdio.h>

#include "shared.h"
#include "static.h"

int main(int argc, char* argv[])
{
    printf("Hello, OS II. Welcome to 2024 course!|\n");
    greetings();
    printf("Calling shared lib. I get %d\n", shared_lib_function("Hello, OS II"));
    printf("Calling static lib. I get %d\n", static_lib_function("Hello, OS II"));
    return 0;
}