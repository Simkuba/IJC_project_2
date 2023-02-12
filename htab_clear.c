/**
 * @file htab_clear.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */


#include "htab_private.h"
#include <stdlib.h>
/**
 * @brief ruší všechny záznamy, tabulka zustane prazdna
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 */
void htab_clear(htab_t * t)
{
    htab_item_t *tmp;
    tmp = NULL;

    for(size_t i = 0; i < t->arr_size; i++){
        if(t->arr_ptr[i] != NULL){
            for(tmp = t->arr_ptr[i]->next; t->arr_ptr[i]->next != NULL; tmp = t->arr_ptr[i]->next){
                free(t->arr_ptr[i]->data->key);
                free(t->arr_ptr[i]->data);
                free(t->arr_ptr[i]);
                t->arr_ptr[i] = tmp;
            }
            free(t->arr_ptr[i]->data->key);
            free(t->arr_ptr[i]->data);
            free(t->arr_ptr[i]);
        }
    }

    //vynulovani pocitadla zaznamu
    t->size = 0;
}