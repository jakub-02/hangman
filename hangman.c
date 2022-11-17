#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "hangman.h"

int get_word(char secret[])
{
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do
    {
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if (result != EOF)
            break;
    } while (1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[])
{
    int secL = strlen(secret);
    int letL = strlen(letters_guessed);
    char test[secL];

    for (int i = 0; i < secL; i++)
    {
        for (int j = 0; j < letL; j++)
        {
            if (letters_guessed[j] == secret[i])
            {
                test[i] = secret[i];
            }
        }
    }

    int a = 0;

    for (int i = 0; i < secL; i++)
    {
        if (test[i] == secret[i])
        {
            a++;
        }
    }

    if (a == secL)
    {
        return 1;
    }

    else
        return 0;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[])
{
    int secL = strlen(secret);
    int letL = strlen(letters_guessed);

    for (int i = 0; i < secL; i++)
    {
        for (int j = 0; j < letL; j++)
        {
            if (letters_guessed[j] == secret[i])
            {
                guessed_word[i] = secret[i];
            }
        }
    }

    for (int i = 0; i < secL; i++)
    {
        if (secret[i] != guessed_word[i])
        {
            guessed_word[i] = '_';
        }
    }

    for (int i = 0; i < secL; i++)
    {
        printf("%c", guessed_word[i]);
    }

    printf("\n");
}

void get_available_letters(const char letters_guessed[], char available_letters[])
{
    char abeceda[] = {"abcdefghijklmnopqrstuvwxyz"};
    int aL = strlen(abeceda);
    int letL = strlen(letters_guessed);

    for (int i = 0; i < aL; i++)
    {
        for (int j = 0; j < letL; j++)
        {
            if (letters_guessed[j] == abeceda[i])
            {
                abeceda[i] = '_';
                break;
            }
        }
    }

    for (int i = 0; i < aL; i++)
    {
        if (abeceda[i] == '_')
        {
            for (int j = i; j < aL; j++)
            {
                abeceda[j] = abeceda[j + 1];
            }
            aL--;
            i--;
        }
    }

    for (int i = 0; i < aL; i++)
    {
        printf("%c", abeceda[i]);
    }
    printf("\n");
}

void hangman(const char secret[])
{
    int dlzka = strlen(secret);

    char letters_guessed[30] = "";
    char abeceda[] = {"abcdefghijklmnopqrstuvwxyz"};
    int pokusy = 8;
    int i = 0;
    char tip[1];
    char result[30];

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", dlzka);

    do
    {
        printf("-------------\n");
        printf("You have %d guesses left.\n", pokusy);
        printf("Available letters: ");
        get_available_letters(letters_guessed, abeceda);
        printf("Please guess a letter: ");
        scanf("%s", tip);
        letters_guessed[i] = tip[0];
        int sranda = 0;
        i++;

        for (int g = 0; g < strlen(abeceda); g++)
        {
            if (tolower(tip[0]) == abeceda[g])
            {
                sranda = 1;
            }
        }

        if (sranda == 1)
        {
            int checker = 0;

            for (int j = 0; j < dlzka; j++)
            {
                if (letters_guessed[i - 1] == secret[j])
                {
                    printf("Good guess:");
                    get_guessed_word(secret, letters_guessed, result);
                    checker = 1;
                    break;
                }
            }

            if (checker != 1)
            {

                for (int j = 0; j < dlzka; j++)
                {
                    if (letters_guessed[i - 1] != secret[j])
                    {
                        printf("Oops! That letter is not in my word:");
                        get_guessed_word(secret, letters_guessed, result);
                        pokusy--;
                        break;
                    }
                }
            }
        }

        else if (sranda == 0)
        {
            printf("Oops! '%c' is not a valid letter: ", tip[0]);
            get_guessed_word(secret, letters_guessed, result);
        }

    } while (pokusy > 0 && is_word_guessed(secret, letters_guessed) == 0);

    printf("-------------\n");

    if (is_word_guessed(secret, letters_guessed) == 1)
    {
        printf("Congratulations, you won!\n");
    }
    else if (is_word_guessed(secret, letters_guessed) == 0)
    {
        printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
    }
}
