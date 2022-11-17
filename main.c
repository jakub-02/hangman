#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

int main(){
    srand(time(0));

    //test
    printf("%d\n", is_word_guessed("robota", "bator"));
    char result[30];
    get_guessed_word("comedian", "", result);
    get_available_letters("", result);

    printf("koniec testov, podme hrat\n");

    //hra
    char secret[] = "";
    get_word(secret);
    hangman(secret);

    return 0;
}
