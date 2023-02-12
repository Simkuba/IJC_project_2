/**
 * @file htab_private.h
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */


//guard
#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include "htab.h"

/**
 * @brief zaznam v tabulce
 */
typedef struct htab_item htab_item_t;

struct htab_item{
    htab_item_t *next;
    struct htab_pair *data;
};

/**
 * @brief definice tabulky
 */
struct htab{
    size_t size;  //aktualni pocet zaznamu (polozek)
    size_t arr_size;  //velikost pole ukazatelu
    htab_item_t *arr_ptr[]; //pole ukazatelu na strukturu (zaznamy v tabulce)
};


#endif  //HTAB_PRIVATE_H