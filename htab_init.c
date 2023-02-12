/**
 * @file htab_init.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"
#include <stdlib.h>

/**
 * @brief konstruktor tabulky
 * 
 * @param n velikost pole ukazatelu (.arr_size)
 * @return htab_t* vytvorena a inicializovana tabulka
 *         NULL v pripade chyby alokace
 */
htab_t *htab_init(size_t n)
{
    htab_t *htab;
    htab = NULL;

    if ((htab = (htab_t *)malloc(sizeof(htab_t) + n * sizeof(htab_item_t *))) == NULL){
        return NULL;
    }

    //incializace velikosti
    htab->arr_size = n;
    htab->size = 0;

    //nastaveni polozek ukazatelu v poli na NULL
    for(size_t i = 0; i < n; i++){
        htab->arr_ptr[i] = NULL;
    }
  
    return htab;
}
