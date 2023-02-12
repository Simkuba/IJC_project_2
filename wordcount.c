/**
 * @file wordcount.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 2)
 * @date 2022-04-15
 * přeloženo pomocí gcc 9.4.0
 */

/*
    +----------+
    | size     | // aktuální počet záznamů [(key,data),next]
    +----------+
    | arr_size | // velikost pole ukazatelů (počet položek)
    +----------+
    | arr_ptr  | // ukazatel na dynamicky alokované pole ukazatelů
    +----------+
      |
      V
    +---+
    |ptr|-->[(key,data),next]-->[(key,data),next]-->[(key,data),next]--|
    +---+
    |ptr|--|
    +---+
    |ptr|-->[(key,data),next]-->[(key,data),next]--|
    +---+
    |ptr|--|
    +---+
*/

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"
#include "io.h"

/**
 * @brief tiskne tabulku
 * 
 * @param table tabulka
 */
void tisk(htab_t *table)
{
    htab_item_t *tmp;
    tmp = NULL;
    for(size_t i = 0; i < htab_bucket_count(table); i++){
        if(table->arr_ptr[i] != NULL){
            for(tmp = table->arr_ptr[i]; tmp != NULL; tmp = tmp->next){
                printf("%s\t%d\n", tmp->data->key,tmp->data->value);
            }
        }
    }
}

int main()
{
   //vytvoreni tabulky
    htab_t *table;
    table = htab_init(ARR_PTR_SIZE);


    char *arr;
    int rd_id = 0;
    arr = malloc(ARR_LIMIT * sizeof(char));
    while((rd_id = read_word(arr, ARR_LIMIT, stdin)) != EOF){
        if(rd_id == 0){
            //mezera
            continue;
        }
        else{
            htab_lookup_add(table, arr);
        }
    }

    tisk(table);

    htab_free(table);
    free(arr);
}
