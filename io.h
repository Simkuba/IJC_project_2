/**
 * @file io.h
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-17
 * přeloženo pomocí gcc 9.4.0
 */

//guard
#ifndef IO_H
#define IO_H
#include <stdio.h>

/**
 * @brief čte jedno slovo ze souboru f do zadaného pole znaků a vrátí délku slova (z delších slov načte prvních max-1 znaků, a zbytek přeskočí
 * 
 * @param s pole, do ktereho se slovo ulozi
 * @param max z delších slov načte prvních max-1 znaků, a zbytek přeskočí
 * @param f soubor, ze ktereho se cte
 * @return int delka slova
 *         EOF konec souboru
 */
int read_word(char *s, int max, FILE *f);

#endif
