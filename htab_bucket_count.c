/**
 * @file htab_bucket_count.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */


#include "htab_private.h"

/**
 * @brief vraci pocet prvku pole (.arr_size)
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 * @return size_t pocet prvku pole
 */
size_t htab_bucket_count(const htab_t * t)
{
    return t->arr_size;
}