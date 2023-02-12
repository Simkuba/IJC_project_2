/**
 * @file htab_resize.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-16
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"
#include <stdlib.h>

/**
 * @brief změna velikosti pole (umožňuje rezervaci místa), pokud alokace selze, nemeni nic
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 * @param newn pocet prvku pole (.arr_size), na ktere se ma pole zvetsit
 */
htab_t * htab_resize(htab_t *t, size_t newn)
{
    htab_t *new_table = htab_init(newn);

    new_table->arr_size = newn;

    htab_item_t *tmp;
    tmp = NULL;
    for(size_t i = 0; i < t->arr_size; i++){
        if(t->arr_ptr[i] != NULL){
            for(tmp = t->arr_ptr[i]->next; t->arr_ptr[i]->next != NULL; tmp = t->arr_ptr[i]->next){
                
                htab_lookup_add(new_table, t->arr_ptr[i]->data->key);
                t->arr_ptr[i] = tmp;
            }
            //posledni polozka
            htab_lookup_add(new_table, t->arr_ptr[i]->data->key);
        }
    }

    htab_free(t);
    t = new_table;
    
    return t;

}
