/**
 * @file htab_for_each.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-16
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"

/**
 * @brief projde všechny záznamy a zavolá na ně funkci f
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 * @param f funkce
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
    htab_item_t *tmp;
    tmp = NULL;
    for(size_t i = 0; i < t->arr_size; i++){
        if(t->arr_ptr[i] != NULL){
            for(tmp = t->arr_ptr[i]; tmp != NULL; tmp = tmp->next){
                f(tmp->data);
            }
        }
    }
}