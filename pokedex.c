// Assignment 2 19T1 COMP1511: Pokedex
// pokedex.c
//
// This program was written by YOUR-NAME-HERE (z5258152)
// on 23-04-2019
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Minor clarifications about `struct pokenode`.
// Version 1.1.0: Moved destroy_pokedex function to correct location.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.
//
// But note you are not permitted to use functions from string.h
// so do not #include <string.h>

#include <ctype.h>
#include "pokedex.h"

// Add your own #defines here.
#define TRUE        1
#define FALSE       0

// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// You are also not permitted to use arrays in any of the functions
// below.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.

struct pokedex {
    struct pokenode *head;
    struct pokenode *curr;
    struct pokenode *destination;  
};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.

struct pokenode {
    struct pokenode *next;
    int             found;
    int             current;
    int             evolution;
    int             id_order;
    Pokemon         pokemon;
};
 
// Add any other structs you define here.


// Add prototypes for any extra functions you create here.
void add_to_end(Pokedex pokedex, struct pokenode *new_pokenode);
char find_pokemon_type(Pokedex pokedex, int type_value);

// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    new_pokedex->head = NULL;
    return new_pokedex;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
        
    // Mallocs memory for Pokenode Struct and asserts that this space is allocated
    struct pokenode *new_pokenode = malloc(sizeof (struct pokenode));
    assert(new_pokenode != NULL);
    
    // Initialising the field values within the new_pokenode struct
    new_pokenode->pokemon = pokemon;
    new_pokenode->found = FALSE;
    new_pokenode->next = NULL;
    new_pokenode->current = FALSE;
    // sets evolution to be a NULL value of -1 since no pokemon has id -1
    new_pokenode->evolution = -1;
    new_pokenode->id_order = 1;
    
    // Checks whether the pokedex struct currently contains a pokenode
    // If not, stores the new_pokenode as the first pokenode
    // If pokedex does contain a pokenode, appends the next pokenode to the end
    if (pokedex->head == NULL){
        pokedex->head = new_pokenode;
        // Sets this pokenodes current value to 
        new_pokenode->current = TRUE;
    }    
    else {
        add_to_end(pokedex, new_pokenode);
    }    
}

void detail_pokemon(Pokedex pokedex) {
    
    struct pokenode *curr = pokedex->head;    
    
    // Loops through linked list of pokenodes until we get the currently selected node
    while (curr != NULL) {
        if (curr->current == TRUE) {
            break;
        }
        
        curr = curr->next;
    }
    
    // Prints out details of the currently selected pokemon
    if(curr != NULL && curr->current == TRUE){
        // Storing the details from pokemon struct into accessible variables
        int id = pokemon_id(curr->pokemon);
        char *name = pokemon_name(curr->pokemon);
        double height = pokemon_height(curr->pokemon);
        double weight = pokemon_weight(curr->pokemon);
        const char *first_type = pokemon_type_to_string(pokemon_first_type(curr->pokemon));
        // Checks whether the type is NONE_TYPE and will set string as " "
        if(pokemon_first_type(curr->pokemon) == NONE_TYPE){
            first_type = "";
        }
        const char *second_type = pokemon_type_to_string(pokemon_second_type(curr->pokemon));
        if(pokemon_second_type(curr->pokemon) == NONE_TYPE){
            second_type = "";
        }
        // Checks whether the Pokemon has been found and prints out details in response
        if (curr->found == FALSE){
            printf("Id: %03d\n", id);
            printf("Name: ");
            // loops through and prints an "*" for each corresponding character in pokemon
            while(*name){printf("*"); name++;}
            printf("\n");
            printf("Height: --\n");
            printf("Weight: --\n");
            printf("Type: --\n");        
        }
        else {
            printf("Id: %03d\n", id);
            printf("Name: %s\n", name);
            printf("Height: %.1lfm\n", height);
            printf("Weight: %.1lfkg\n", weight);
            printf("Type: %s %s\n", first_type, second_type);      
        }
    }
}


Pokemon get_current_pokemon(Pokedex pokedex) {
 
    struct pokenode *curr = pokedex->head;
    
    // Loops through until at the currently selected pokemon
    while(curr->current != TRUE){
        curr = curr->next;
    }
    return curr->pokemon;
}

void find_current_pokemon(Pokedex pokedex) {

    struct pokenode *curr = pokedex->head;    
    
    // Loops through until at currently selected pokemon
    if(curr != NULL){
        while(curr->current != TRUE){
            curr = curr->next;
        }
        // sets the found field to TRUE
        curr->found = TRUE;
    }
}

void print_pokemon(Pokedex pokedex) {

    struct pokenode *curr = pokedex->head;
    
    // Loops through linked list while pokenode is not NULL
    while(curr != NULL){
        
        int id = pokemon_id(curr->pokemon);
        char *name = pokemon_name(curr->pokemon);
        
        // if currently selected, prints "-->" in front of id
        switch(curr->current){
            
            case TRUE:
                printf("--> #%03d: ", id);
                break;
            
            default:
                printf("    #%03d: ", id);
                break;
        }
        
        // if found, prints out name instead of asterisks
        switch(curr->found){
        
            case TRUE:
                printf("%s", name);
                break;
            
            default:
                // Loops through name and prints * at each character
                while(*name){printf("*"); name++;}
                break;         
        }
        
        printf("\n");
        curr = curr->next;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void next_pokemon(Pokedex pokedex) {

    struct pokenode *curr = pokedex->head;
    
    // If the pokedex contains a node, enter this condition
    if(curr != NULL){
        // Loops through list until at the currently selected pokemon
        while(curr->current != TRUE){
            curr = curr->next;
        }    
        
        // If the next node is not NULL set the next node to be the currently selected pokemon
        if(curr->next != NULL){
        
            curr->current = FALSE;    
            curr->next->current = TRUE;
        }
    }
}

void prev_pokemon(Pokedex pokedex) {
    struct pokenode *curr = pokedex->head;
    
    struct pokenode *destination = NULL;
    
    // If pokenode within pokedex, enter this statement
    if(curr != NULL){
        // loops through pokenode until at currently selected pokenode
        // stores pokenode of the previous pokemon in destination
        while(curr->current != 1){
            destination = curr;
            curr = curr->next;
        }
        // If the pokenode in destination is not NULL, set the previous pokenode as currently selected
        if(destination != NULL){
            destination->current = TRUE;
            destination->next->current = FALSE;
        }
    }
}

void change_current_pokemon(Pokedex pokedex, int destination_pokemon_id) {

    struct pokenode *destination = pokedex->head;

    struct pokenode *curr = pokedex->head;
    
    // loops through until at currently selected pokemon
    while(curr->current != TRUE){
        curr = curr->next;
    }   
     
    int id = pokemon_id(destination->pokemon);
    
    // loops through list to ensure that the id they want to move to is valid
    // stops if we reach the end of list or if we find that the id is value
    while(id != destination_pokemon_id && destination != NULL){
        destination = destination->next;
        id = pokemon_id(destination->pokemon);
    }
    // if the id is valid, set that new id as currently selected
    if(id == destination_pokemon_id){
        destination->current = TRUE;
        curr->current = FALSE;
    }
}

void remove_pokemon(Pokedex pokedex) {

    struct pokenode *curr = pokedex->head;
    
    struct pokenode *destination = NULL;
    
    while(curr != NULL){
        // loops through until at the currently selected pokemon
        if(curr->current != TRUE){
            destination = curr;
            curr = curr->next;
        }
        else{
            break;
        }
    }
    // if the currently selected pokemon is the first pokenode and there is a node
    // stored in the next pokenode, set the next pokenode to be currently selected
    if(pokedex->head == curr && pokedex->head->next != NULL){
        curr = pokedex->head;
        pokedex->head = pokedex->head->next;
        pokedex->head->current = TRUE;
    }
    // if the next pokemon after currently selected is not NULL
    // set the next pokemon to be currently selected
    else if(curr->next != NULL){
        // sets previous pokenode next to link to node after the one about to be removed
        destination->next = curr->next;
        destination->next->current = TRUE;
    }
    // if the next pokenode is NULL and the previous pokenode is not NULL
    // sets the previous pokenode to be the currently selected pokemon
    else if(curr->next == NULL && destination != NULL){
        destination->current = TRUE;
        destination->next = NULL;
    }
    // otherwise if only one pokenode, set head now equal to NULL
    else{
        pokedex->head = NULL;
    }
    // free pokemon struct
    destroy_pokemon(curr->pokemon);
    // free pokenode struct
    free(curr);
}

void destroy_pokedex(Pokedex pokedex) {
    
    struct pokenode *destination = NULL;
    
    // loops through while a pokenode stored in the list
    while(pokedex->head != NULL){
        // sets destination to equal next pokenode
        destination = pokedex->head->next;
        // sets link to next pokenode to NULL
        pokedex->head->next = NULL;
        // free pokemon struct in head
        destroy_pokemon(pokedex->head->pokemon);
        // free pokenode struct
        free(pokedex->head);
        // sets the pokemon head to the next pokenode 
        pokedex->head = destination;
    }
    // free the pokedex struct 
    free(pokedex);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    
    int pokemon_found = FALSE;
    int pokemon_between_range = 0;
    // sets a seed for rand to use
    srand(seed);
    
    struct pokenode *curr = pokedex->head;
    
    // loops while the current pokenode is not NULL
    while(curr != NULL){
        // if the pokemon id is between the range(0-(factor-1)) add one to the counter
        if (pokemon_id(curr->pokemon) <= factor - 1){
            pokemon_between_range++;
        }
        curr = curr->next; 
    }
    
    // if there are pokemon between the range the user wishes to search, search for pokemon
    if (pokemon_between_range > 0){
        // loops until the designated amount of pokemon are found and there are still pokemon
        // to be found within the range
        while(pokemon_found < how_many && pokemon_found < pokemon_between_range){
            // sets a random id to search for
            int rand_id = rand()%(factor + 1);
            struct pokenode *curr = pokedex->head;
            
            // searches through pokedex for id matching rand_id
            // if nothing found it will exit and get another rand_id to search for
            while(curr != NULL){
                if (rand_id == pokemon_id(curr->pokemon)){
                    curr->found = TRUE;
                    pokemon_found++;
                    break;
                }
                curr = curr->next; 
            }     
        }
    }
    // exits pokedex and lets user know that there were no pokemon between the range selected
    else{
        fprintf(stderr, "There aren't any Pokemon to find with pokemon_id between 0 and (%d - 1)!\n", factor);
        exit(1);
    }
}

int count_found_pokemon(Pokedex pokedex) {
    
    struct pokenode *curr = pokedex->head;
    
    int how_many_found = 0;
    
    // loops through the pokenode list
    while(curr != NULL){
        
        // if the pokenode field value for found is true, incrememnt counter
        if(curr->found == TRUE){
            how_many_found++;
        }
        curr = curr->next;
    }
    return how_many_found;
}

int count_total_pokemon(Pokedex pokedex) {
    
    struct pokenode *curr = pokedex->head;
    
    int total_pokemon = 0;
    
    // loops through pokenode list
    while(curr!= NULL){
        // increment counter for each pokemon within the list
        total_pokemon++;
        curr = curr->next;
    }
    return total_pokemon;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {

    // variables to store whether there are pokemon with id 'from_id' & id 'to_id'
    int is_pokemon_from_id = FALSE;
    int is_pokemon_to_id = TRUE;

    // if 'from_id' is equal to 'to_id' exit program and tell user that they input an invalid evolution
    if(from_id == to_id){
        fprintf(stderr, "Invalid Pokemon Evolution!\n");
        exit(1);   
    }
    
    struct pokenode *curr = pokedex->head;
    // loops through each pokenode within the list
    while(curr != NULL){
        // if the pokenode currently selected has id equal to 'to_id'
        // set is_pokemon_to_id equal to TRUE
        if (pokemon_id(curr->pokemon) == to_id){
            is_pokemon_to_id = TRUE;
        }
        curr = curr->next; 
    }
    
    curr = pokedex->head;
    // loops through each pokenode within pokedex
    while(curr != NULL){
        // if the id of currently select is equal to 'from_id'
        // and is_pokemon_to_id is true
        if (pokemon_id(curr->pokemon) == from_id && is_pokemon_to_id){
            // sets evolution field equal to 'to_id' if conditions are met
            curr->evolution = to_id;
            is_pokemon_from_id = TRUE;
            break;
        }
        curr = curr->next; 
    }
    
    // if is_pokemon_to_id is false or is_pokemon_from_id is false
    // exit program and let user know that they input an invalid evolution
    if (is_pokemon_to_id != 1 || is_pokemon_from_id != 1){
        fprintf(stderr, "Invalid Pokemon Evolution!\n");
        exit(1);         
    }
}

void show_evolutions(Pokedex pokedex) {
    
    struct pokenode *curr = pokedex->head;
    // NULL value for evolution initialised as -1 as no pokemon id can be -1
    int evolution_to_find = -1;
    
    // loops through pokenode within pokedex
    while(curr != NULL){
        // sets variables for pokemon id,name,first type, second type to the current pokemons values
        int id = pokemon_id(curr->pokemon);
        char *name = pokemon_name(curr->pokemon);
        const char *first_type = pokemon_type_to_string(pokemon_first_type(curr->pokemon));
        const char *second_type = pokemon_type_to_string(pokemon_second_type(curr->pokemon));       
        // if the pokemon is the currently selected pokemon    
        if(curr->current == TRUE){
            printf("#%03d ", id);
            // sets variable evolution_to_find equal to the current pokemon's evolution field
            evolution_to_find = curr->evolution;
            // if the current pokemon has been found, print name and type out
            if(curr->found){
                printf("%s ", name);
                printf("[");
                // if the pokemon has two types print out statement with , separating the two
                if(pokemon_first_type(curr->pokemon) != NONE_TYPE && pokemon_second_type(curr->pokemon) != NONE_TYPE){
                    printf("%s, %s", first_type, second_type);
                }
                // otherwise print out the single type within the square brackets with no comma
                else{
                    printf("%s", first_type);
                }
                printf("]");
            }
            // otherwise print out place holders of '?'
            else{
                printf("???? [????]");
            }
            break;
        }
        curr = curr->next;
    }
    
    curr = pokedex->head;
    // loops through while there is an evolution id which we wish to find
    while(evolution_to_find != -1){
        // prints an arrow to indicate there is an evolution
        printf(" --> ");
        while(curr != NULL){
            // sets variables for pokemon id,name,first type, second type to the current pokemons values
            int id = pokemon_id(curr->pokemon);
            char *name = pokemon_name(curr->pokemon);
            const char *first_type = pokemon_type_to_string(pokemon_first_type(curr->pokemon));
            const char *second_type = pokemon_type_to_string(pokemon_second_type(curr->pokemon)); 
            // if the pokemon id is the evolution_id we are searching for print out its details 
            if(id == evolution_to_find){
                printf("#%03d ", id);
                evolution_to_find = curr->evolution;
                if(curr->found){
                    printf("%s ", name);
                    printf("[");
                    // if the pokemon has two types print out statement with , separating the two
                    if(pokemon_first_type(curr->pokemon) != NONE_TYPE && pokemon_second_type(curr->pokemon) != NONE_TYPE){
                        printf("%s, %s", first_type, second_type);
                    }
                    // otherwise print out the single type within the square brackets with no comma
                    else{
                        printf("%s", first_type);
                    }
                    printf("]");
                }
                else{
                    printf("???? [????]");
                }
                // if the evolution id to find is not NULL, reset curr to pokedex head
                // and search for next id
                if(evolution_to_find != -1){
                    curr = pokedex->head;
                }
                break;
            }
            curr = curr->next;
        }
        
    }
    
    printf("\n");
}

int get_next_evolution(Pokedex pokedex) {
 
    struct pokenode *curr = pokedex->head;    
   
    // if the pokedex is empty exit program and let user know
    if (curr == NULL){
        fprintf(stderr, "The Pokedex is empty!\n");
        exit(1);    
    }
    else{
        // loops through until at the currently selected pokemon
        while(curr != NULL){
            if(curr->current){
                break;
            }
            curr = curr->next;
        }
        // if the pokenode evolution value is NULL return 'DOES_NOT_EVOLVE'
        if(curr->evolution == -1){
            return DOES_NOT_EVOLVE;
        }   
         else{
            return curr->evolution;    
        }
    }             
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    // creates new pokedex 'type_pokedex' storing only pokemon of a certain type
    struct pokedex *type_pokedex = new_pokedex();
    struct pokenode *curr = pokedex->head;
    // loops through current pokedex and stores pokemon of the type we want within type_pokedex
    // also only stores these pokemon if they have already been found
    while(curr != NULL){
        pokemon_type first_type = pokemon_first_type(curr->pokemon);
        pokemon_type second_type = pokemon_second_type(curr->pokemon);
        if( (first_type == type || second_type == type) && curr->found == 1){
            add_pokemon(type_pokedex, clone_pokemon(curr->pokemon));
        }
        curr = curr->next;
    }
    
    curr = type_pokedex->head;
    // sets all pokenodes found field to TRUE within the pokedex 'type_pokedex'
    while(curr != NULL){
        curr->found = TRUE;
        curr = curr->next;
    }
    
    return type_pokedex;
    
}

Pokedex get_found_pokemon(Pokedex pokedex) {

    // creates new pokedex 'get_found_pokedex' storing only pokemon that have been found    
    struct pokedex *get_found_pokedex = new_pokedex();
    struct pokenode *curr = pokedex->head;
    
    // counts how many found pokemon within original pokedex
    int total_pokemon = count_found_pokemon(pokedex);
    // keeps track how many of the found pokemon have been copied
    int how_many_copied = 0;
    // variable used to store pokemon in ascending order of id
    int id_order = 1;
    // loops through pokedex while pokenode is not null and not all the found pokemon have been copied
    while(curr != NULL && how_many_copied < total_pokemon){
        // if the pokemon has been found and their id is next one in ascending order
        // copy into pokedex 'get_found'
        if( curr->found == 1 && curr->id_order == id_order){
            add_pokemon(get_found_pokedex, clone_pokemon(curr->pokemon));
            how_many_copied++;
            id_order++;
            curr = pokedex->head;
        }
        // if the pokemon is not found but is the next pokemon in id order
        // increment id order and reset curr to the pokedex head
        else if(curr->found != 1 && curr->id_order == id_order){
            curr = pokedex->head;
            id_order++;
        }
        else{
            curr = curr->next;
        }
    }
    
    curr = get_found_pokedex->head;
    // loops through each value of get_found pokedex and sets found field to one
    // since it only stores found pokemon
    while(curr != NULL){
        curr->found = TRUE;
        curr = curr->next;
    }
    
    return get_found_pokedex;
}

Pokedex search_pokemon(Pokedex pokedex, char *text) {
   
    // creates new pokedex 'get_found_pokedex' storing only pokemon that have been found 
    struct pokedex *search_pokedex = new_pokedex();
    struct pokenode *curr = pokedex->head;
    
    
    while(curr != NULL){
        // variable used to keep track whether the pokemon names match what we are looking for
        int search_found = FALSE;
        char *name = pokemon_name(curr->pokemon);
        // temp values uesed to store the lower case version of characters so we can compare accurately
        char name_compare;
        char text_compare; 
        int name_length = 0;
        int text_length = 0;
        int d = 0; 
        int i = 0; 
        // increments throguh string and counts it length
        while(name[d]){name_length++; d++;}
        while(text[i]){text_length++; i++;} 
        // used to keep track of previous character to fix certain bug where d increments unintended
        int d_prev = 0;
        i = 0;
        d = 0;        
        // loops through while still comparing characters within the strigns
        while(d < name_length && i < text_length){
            name_compare = tolower(name[d]);
            text_compare = tolower(text[i]);
            // if the values are the same, increment the counter for text_length
            if (name_compare == text_compare){
                i++;
            }       
            // if the previous name character is the same as current name character
            // and i > 0 let the current character which would've been skipped
            // be properly tested
            else if(name[d_prev] == name[d] && i > 0){
                d = d - 1;
                i = 0;
            }     
            // otherwise reset i = 0, to test for first character again
            else{
                i = 0;
            }
            d_prev = d;
            d++;
        }
        // if we reached the NULL terminator of text, set search_found to true
        if(text[i] == '\0'){
            search_found = TRUE;
        }    
        // if the string matches and the pokemon has been found
        // store within search pokedex
        if( search_found && curr->found == TRUE){
            add_pokemon(search_pokedex, clone_pokemon(curr->pokemon));
        }
        curr = curr->next;
    }
    
    curr = search_pokedex->head;
    // loops through each pokenode in search pokedex and sets found field to true
    while(curr != NULL){
        curr->found = 1;
        curr = curr->next;
    }
    
    return search_pokedex;
}

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.
void add_to_end(Pokedex pokedex, struct pokenode *new_pokenode){

    struct pokenode *curr = pokedex->head;

    // loops through each pokenode in pokedex and compares their id
    while (curr != NULL) {
        int id = pokemon_id(curr->pokemon);
        int new_id = pokemon_id(new_pokenode->pokemon);
        // if id has already been used, let user know the error and exit program
        if (id == new_id) {
            fprintf(stderr, "There's already a Pokemon with pokemon_id %d!\n", new_id);
            exit(1);
        }
        // if the new id is larger than current pokemon id, increment the new pokemon id order by 1
        else if(new_id > id){
            new_pokenode->id_order = new_pokenode->id_order + 1; 
        }
        // if the new id is smaller than current id, increment current id order by 1
        else if(new_id < id){
            curr->id_order = curr->id_order + 1;
        } 
        curr = curr->next;
    }
    
    curr = pokedex->head;
    // loops through until at last pokenode before null
    while (curr->next != NULL){
        curr = curr->next;
    }
    // appends the new pokenode to the end of the list
    curr->next = new_pokenode;
    
}

