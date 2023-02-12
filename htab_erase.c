/**
 * @file htab_erase.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-16
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief ruší zadaný záznam
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 * @param key klic
 * @return true zaznam byl zrusen
 * @return false zaznam nebyl zrusen
 */
bool htab_erase(htab_t * t, htab_key_t key) 
{
   //nejdrive se zkusi zaznam najit
   htab_pair_t *zaznam;
   zaznam = htab_find(t, key);

    //zaznam neexistuje
    if(zaznam == NULL){
        return false;
    }

    //zaznam existuje -> musi se smazat
    size_t index; 
    index = (htab_hash_function(key)%t->arr_size);

    htab_item_t *tmp;
    tmp = NULL;
    htab_item_t *item_to_erase;
    item_to_erase = NULL;
    //nalezeni posledni polozky v seznamu na indexu

    for(tmp = t->arr_ptr[index]->next; t->arr_ptr[index]->next != NULL; tmp = t->arr_ptr[index]->next){
        if(strcmp(t->arr_ptr[index]->data->key, key) == 0){
            item_to_erase = t->arr_ptr[index];
            break;
        }
        t->arr_ptr[index] = tmp;
    }

    item_to_erase = t->arr_ptr[index];
    

    //prenastaveni ukazatelu next
    t->arr_ptr[index] = item_to_erase->next;

    //zruseni zaznamu
    free(item_to_erase->data->key);
    free(item_to_erase->data);
    free(item_to_erase);

    //snizeni pocitadla
    t->size--;

    return true;
}   