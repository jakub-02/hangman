#include <stdio.h>
#include "hangman.h"

int main(){
    
    printf("%d\n", is_word_guessed("robota", "ator"));

    char result[30];

    get_guessed_word("container", "kokotkokotkokot", result);

    get_available_letters("aroeitv", result);

    get_available_letters("", result);

    char secret[] = "";
    get_word(secret);

    return 0;
}