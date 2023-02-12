/**
 * @file htab_find.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief V tabulce t vyhledá záznam odpovídající řetězci key
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 * @param key klic
 * @return htab_pair_t* ukazatel na zaznam
 *         NULL v pripade, ze zaznam neexistuje
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key)
{
    //overeni platne velikosti tabulky, pokud neexistuji zaznamy, nemam co hledat
    if(t->size == 0){
        return NULL;
    }

    //vypocitani indexu v tabulce (v poli ukazatelu)
    size_t index = htab_hash_function(key)%t->arr_size;
    htab_item_t *tmp;
    tmp = NULL;

    //hledani shody
    if(t->arr_ptr[index] != NULL){
        for(tmp = t->arr_ptr[index]->next; t->arr_ptr[index]->next != NULL; tmp = t->arr_ptr[index]->next){
            if (strcmp(t->arr_ptr[index]->data->key, key) == 0){  
                return t->arr_ptr[index]->data;
            }
            t->arr_ptr[index] = tmp;
        }
    }

    //posledni polozka
    if(t->arr_ptr[index] != NULL){
        if (strcmp(t->arr_ptr[index]->data->key, key) == 0){
                return t->arr_ptr[index]->data;
        }
    }

    //zaznam neexistuje
    return NULL;
}
