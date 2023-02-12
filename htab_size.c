/**
 * @file htab_size.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */


#include "htab_private.h"

/**
 * @brief počet polozek tabulky (.size)
 * 
 * @param t ukazatel na tabulku (typu h_tab *)
 * @return size_t 
 */
size_t htab_size(const htab_t * t)
{
    return t->size;
}
