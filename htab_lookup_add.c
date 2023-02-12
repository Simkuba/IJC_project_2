/**
 * @file htab_lookup_add.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-16
 * přeloženo pomocí gcc 9.4.0
 */

#include "htab_private.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


htab_item_t *last_in_list(htab_item_t *polozka)
{
    if(polozka == NULL){
        return polozka;
    }
    else{
        htab_item_t *tmp;
        tmp = polozka->next;
        for(; tmp != NULL; tmp = tmp->next){
            ;
        }

        return tmp;
    }
}


/**
 * @brief V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
 *         - pokud jej nalezne, vrátí ukazatel na záznam
 *         - pokud nenalezne, automaticky přidá záznam a vrátí ukazatel
 * 
 * @param t ukazatel na tabulku (typu htab_t *)
 * @param key klic, podle ktereho hledame
 * @return htab_pair_t* ukazatel na zaznam
 *         NULL v pripade chyby alokace
 */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key)  
{
   //nejdrive se zkusi zaznam najit
   htab_pair_t *zaznam;
   zaznam = htab_find(t, key);

    //zaznam existuje
   if(zaznam != NULL){
       zaznam->value++;
       return zaznam;
   }

   //zaznam neexistuje -> musi se pridat 
    size_t index; 
    index = (htab_hash_function(key)%t->arr_size);

    htab_item_t *new_item;
    new_item = last_in_list(t->arr_ptr[index]);
    
    //posledni polozka -> sem muzu pridat
    htab_item_t *n_polozka;
    if((n_polozka = (htab_item_t *)malloc(sizeof(htab_item_t))) == NULL){
        fprintf(stderr, "Allocation fault! Couldn't add the item!\n");
        return NULL;
    }
    
    if((zaznam = (htab_pair_t *)malloc(sizeof(htab_pair_t))) == NULL){
        fprintf(stderr, "Allocation fault! Couldn't add the item!\n");
        return NULL;
    }

    new_item = n_polozka;
    new_item->data = zaznam;

    new_item->data->value = 1;
    if((new_item->data->key = calloc(strlen(key)+1, sizeof(char))) == NULL){
        fprintf(stderr, "Allocation fault! Couldn't add the item!\n");
        return NULL;
    }
    strcpy(new_item->data->key, key);
    new_item->next = NULL;
    t->size++;

    if(t->arr_ptr[index] != NULL){
        htab_item_t *tmp;
        tmp = NULL;
        for(tmp = t->arr_ptr[index]->next; t->arr_ptr[index]->next != NULL; tmp = t->arr_ptr[index]->next){
            t->arr_ptr[index] = tmp;
        }
        t->arr_ptr[index]->next = new_item;
    }
    else{
        t->arr_ptr[index]= new_item;
    }

    //kontrola presahnuti AVG_LEN_MIN
    htab_item_t *tmp2;
    tmp2 = NULL;
    int counter = 0;
    bool r_flag = false;

    for(size_t i = 0; i < t->arr_size; i++){
        if(t->arr_ptr[i] != NULL){
            for(tmp2 = t->arr_ptr[i]; tmp2 != NULL; tmp2 = tmp2->next){
                counter++;
                if(counter >= AVG_LEN_MIN){
                    r_flag = true;
                    break;
                }
            }
        }
        if(r_flag){
            break;
        }
        counter = 0;
    }

    if(r_flag){
        t = htab_resize(t, (t->arr_size)*2);
    }

    return t->arr_ptr[index]->data;

}
