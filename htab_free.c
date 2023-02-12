/**
 * @file htab_free.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"
#include <stdlib.h>

/**
 * @brief destruktor tabulky
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 */
void htab_free(htab_t * t)
{
    //zruseni polozek tabulky
    htab_clear(t);

    //uvolneni tabulky
    free(t);

}

