/**
 * @file tail.c
 * @author Jakub Čoček (xcocek00), FIT
 * @brief Řešení IJC-DU2, 1)
 * @date 2022-04-10
 * přeloženo pomocí gcc 9.4.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief pojemnovani struktury node
 */
typedef struct node Node_t;

/**
 * @brief Polozka seznamu
 */
struct node
{
    char arr[4096];     //4095 znaku + '\0'
    unsigned int counter;
    Node_t *next;
};

typedef struct list
{
    Node_t *head;
}List_t;

/**
 * @brief konstruktor senznamu, vytvori prazdny seznam
 * 
 * @param list struktura typu seznam
 * @return List_t* alokovany prazdny seznam
 */
List_t *list_ctor(List_t *list)
{
    if((list = (List_t *)malloc(sizeof(List_t))) == NULL){
        fprintf(stderr, "Allocation of list failed!\n");
        exit(1);
    }

    list->head = NULL;
    return list;
}

/**
 * @brief Pridani prvku na zacatek seznamu
 * 
 * @param object polozka seznamu
 * @param counter pocitadlo polozek
 * @param head ukazatel na prvni polozku
 * @return List_t* vrati aktualizovany seznam
 */
Node_t *list_add(unsigned int counter, List_t *list)
{
    Node_t *object;
    object = NULL;
    if((object = (Node_t *)calloc(1,sizeof(Node_t))) == NULL){
        fprintf(stderr, "Allocation of list node failed!\n");
        exit(1);
    }

    object->next = list->head;    //prenastaveni ukazatele next tam, kam ukazoval head
    object->counter = counter;  //nastavi cislo polozky seznamu
    list->head = object;  //nastavi hlavicku seznamu na tento prvek

    return object;
}

/**
 * @brief Prida polozku na zacatek seznamu, ale zaroven odstrani posledni polozku a precisluje country polozek, tj. zanecha pocet uzlu
 * 
 * @param counter pocitadlo polozky
 * @param list typ seznam
 */
void list_rem_append(unsigned int counter, List_t *list, char *tmp_storage)
{
    Node_t *object;
    object = NULL;
    if((object = (Node_t *)malloc(sizeof(Node_t))) == NULL){
        fprintf(stderr, "Allocation of list node failed!\n");
        exit(1);
    }
    //odebrani poslendi polozky
    Node_t *temp;
    temp = NULL;
    for(temp = list->head; temp->next->next != NULL; temp = temp->next){
        ;
    }
    Node_t *tmp = temp; //predposledni polozka
    free(temp->next);   //uvolneni posledni polozky
    tmp->next = NULL;

    object->next = list->head;
    list->head = object;
    object->counter = counter;
    strcpy(object->arr, tmp_storage);

    Node_t *temp2;
    temp2 = NULL;
    for(temp2 = list->head; temp2 != NULL; temp2 = temp2->next){
        temp2->counter--;
    }

}

/**
 * @brief Destruktor seznamku
 * 
 * @param list seznam
 * @return int vraci 1 jako uspech
 */
int list_dtor(List_t *list)
{
    //seznam je prazdny
    if(list->head == NULL){
        return 1;
    }

    //postupne uvolneni seznamu
    Node_t *tmp;
    tmp = NULL;
    for(tmp = list->head->next; list->head->next != NULL; tmp = list->head->next){
        free(list->head);
        list->head = tmp;
    }
    free(list->head);
    free(tmp);
    return 1;
}

/**
 * @brief Zpracovani argumentu
 * 
 * @param argc pocet argumentu
 * @param argv pole argumentu
 * @return int pocet radku, ktera ma program vypsat
 */
unsigned int params(int argc, char **argv)
{
    char *param_n = "-n";
    unsigned int pocet_radku;
    if(argc <= 2){
        //parametr -n nebyl zadan
        pocet_radku = 10;
    }
    else if((argc == 4 || argc == 3) && !(strcmp(param_n, argv[1]) != 0)){
        //parametr -n byl pravdepodne zadan
        int tmp = atoi(argv[2]);
        
        if(tmp > 0){
            pocet_radku = tmp;
        }
        else if(tmp == 0){
            exit(0);
        }
        else{
            fprintf(stderr, "Invalid number of lines!\n");
            exit (1);
        }
    }
    else if(strcmp(param_n, argv[1]) != 0){
        fprintf(stderr, "Param %s is not supported!\n", argv[1]);
        exit(1);
    }
    else{
        fprintf(stderr, "Invalid number of arguments!\n");
        exit(1);
    } 
    
    return pocet_radku;
}

/**
 * @brief Inicializuje seznam a zaroven tiskne poslednich 'pocet_radku' radku
 * 
 * @param pocet_radku pocet radku, ktere maji byt vytisknuty
 * @param argc pocet argumentu
 * @param argv argumenty
 * @param list typ seznam
 */
void tisk(unsigned int pocet_radku, int argc, char **argv, List_t *list)
{
    FILE *fp;
    bool long_line = false;     //flag pro detekci prilis dlouheho radku, true -> error msg byla jiz jednout vypsana
    //vytiskne jen posledni radek - varianta tail -n 1 soubor
    if(pocet_radku == 1 && argc == 4){
        if((fp = fopen(argv[3], "r")) == NULL){
            fprintf(stderr, "Failed to open file %s!\n", argv[1]);
            list_dtor(list);
            free(list);
            exit(1);
        }
        //vytvoreni nutneho poctu listu seznamu
        list->head = list_add(0, list);

        while(fgets(list->head->arr, 4096, fp) != NULL){
            //osetreni delky radku, zkraceni v pripade presazeni limitu
            
            if(list->head->arr[strlen(list->head->arr)-1] != '\n'){
                int c;
                while((c = fgetc(fp)) != '\n');
                list->head->arr[strlen(list->head->arr)-1] = '\n';
                if(!long_line){
                    fprintf(stderr, "Input contains line(s), which is/are too long, the rest of the line will be skipped!\n");
                    long_line = true;
                }
            } 
        }
        fclose(fp);
    }//varianta tail -n 1 <soubor
    else if(pocet_radku == 1 && argc == 3){
        //vytvoreni nutneho poctu listu seznamu
        list->head = list_add(0, list);

        while(fgets(list->head->arr, 4096, stdin) != NULL){
             //osetreni delky radku, zkraceni v pripade presazeni limitu
            if(list->head->arr[strlen(list->head->arr)-1] != '\n'){
                int c;
                while((c = fgetc(stdin)) != '\n');
                list->head->arr[strlen(list->head->arr)-1] = '\n';
                if(!long_line){
                    fprintf(stderr, "Input contains line(s), which is/are too long, the rest of the line will be skipped!\n");
                    long_line = true;
                }
            }
        }
    }//varinta tail soubor || tail -n x soubor
    else if((pocet_radku == 10 && argc == 2) || (pocet_radku != 10 && argc == 4)){
        //byl zadan soubor
        if(argc == 2){
            if((fp = fopen(argv[1], "r")) == NULL){
                fprintf(stderr, "Failed to open file %s!\n", argv[1]);
                list_dtor(list);
                free(list);
                exit(1);
            }
        }
        else{
            if((fp = fopen(argv[3], "r")) == NULL){
                fprintf(stderr, "Failed to open file %s!\n", argv[1]);
                list_dtor(list);
                free(list);
                exit(1);
            }
        }

        //vytvoreni nutneho poctu listu seznamu
        for(unsigned i = 0; i < pocet_radku; i++){
            list->head = list_add(i, list);
        }

        //kopirovani radku do seznamu
        unsigned int counter = 0;
        bool app_flag = 0;  //flag na kontrolu, zda se sezam ma nebo nema zacit 'posouvat' dolu
        char tmp_storage[4096];
        while(fgets(tmp_storage, 4096, fp) != NULL){
            //osetreni delky radku, zkraceni v pripade presazeni limitu
            if(tmp_storage[strlen(tmp_storage)-1] != '\n'){
                int c;
                while((c = fgetc(fp)) != '\n');
                tmp_storage[strlen(tmp_storage)-1] = '\n';
                if(!long_line){
                    fprintf(stderr, "Input contains line(s), which is/are too long, the rest of the line will be skipped!\n");
                    long_line = true;
                }
            }

            for(Node_t *tmp = list->head; tmp != NULL; tmp = tmp->next){
                if(tmp->counter == counter && app_flag == 0){
                    strcpy(tmp->arr, tmp_storage);
                    break;
                }
            }
            //nyni se musi zacit odebirat od konce, aby se seznam posunul
            if(app_flag == 1){
                list_rem_append(counter, list, tmp_storage);
            }

            if(app_flag == 0){
                counter++;
                if(counter >= pocet_radku){
                    app_flag = 1;
                }
            }

        }
        fclose(fp);
    }//ostatni pripustne varianty
    else{
        //vytvoreni nutneho poctu listu seznamu
        for(unsigned i = 0; i < pocet_radku; i++){
            list->head = list_add(i, list);
        }

        //kopirovani radku do seznamu
        unsigned int counter = 0;
        bool app_flag = 0;  //flag na kontrolu, zda se sezam ma nebo nema zacit 'posouvat' dolu
        char tmp_storage[4096];
        while(fgets(tmp_storage, 4096, stdin) != NULL){
            //osetreni delky radku, zkraceni v pripade presazeni limitu
            if(tmp_storage[strlen(tmp_storage)-1] != '\n'){
                int c;
                while((c = fgetc(stdin)) != '\n');
                tmp_storage[strlen(tmp_storage)-1] = '\n';
                if(!long_line){
                    fprintf(stderr, "Input contains line(s), which is/are too long, the rest of the line will be skipped!\n");
                    long_line = true;
                }
            }

            for(Node_t *tmp = list->head; tmp != NULL; tmp = tmp->next){
                if(tmp->counter == counter && app_flag == 0){
                    strcpy(tmp->arr, tmp_storage);
                    break;
                }
            }
            
            //nyni se musi zacit odebirat od konce, aby se seznam posunul
            if(app_flag == 1){
                list_rem_append(counter, list, tmp_storage);
            }

            if(app_flag == 0){
                counter++;
                if(counter >= pocet_radku){
                    app_flag = 1;
                }
            }

        }
    }

    //tisk seznamu, resp. pozadovaneho poctu radku na konci
    unsigned cnt = 0;
    for(Node_t *tmp = list->head; tmp != NULL; tmp = tmp->next){
        for(Node_t *tmp2 = list->head; tmp2 != NULL; tmp2 = tmp2->next){
            if(cnt == tmp2->counter){
                printf("%s",tmp2->arr); 
            }
        }
        cnt++;
    }
}

int main(int argc, char *argv[])
{
    unsigned int pocet_radku = params(argc, argv);

    //vytvoreni seznamu
    List_t *list;
    list = NULL;
    list = list_ctor(list);

    tisk(pocet_radku, argc, argv, list);

    list_dtor(list);
    free(list);
}
