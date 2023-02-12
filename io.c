/**
 * @file io.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-17
 * přeloženo pomocí gcc 9.4.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "io.h"

/**
 * @brief čte jedno slovo ze souboru f do zadaného pole znaků a vrátí délku slova (z delších slov načte prvních max-1 znaků, a zbytek přeskočí
 * 
 * @param s pole, do ktereho se slovo ulozi
 * @param max z delších slov načte prvních max-1 znaků, a zbytek přeskočí
 * @param f soubor, ze ktereho se cte
 * @return int delka slova
 *         EOF konec souboru
 */
int read_word(char *s, int max, FILE *f)
{
    int c;
    int cnt = 1;
    
    //!= 0 -> whitespace
    while((isspace(c = fgetc(f)) == 0) && (c != EOF)){
        if(cnt != (max - 1)){
            s[cnt-1] = c;
            s[cnt] = '\0';
            cnt++;
        }
    }

    if(c != EOF){
        return cnt-1;
    }
    else{
        return EOF;
    }
    
}