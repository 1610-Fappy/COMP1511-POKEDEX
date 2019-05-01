// Assignment 2 19T1 COMP1511: Pokedex
// test_pokedex.c
//
// This file allows you to automatically test the functions you
// implement in pokedex.c.
//
// This program was written by YOUR-NAME-HERE (z5258152)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Added pointer check for the provided tests.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

// Add your own #defines here.


// Sample data on Bulbasaur, the Pokemon with pokemon_id 1.
#define BULBASAUR_ID 1
#define BULBASAUR_NAME "Bulbasaur"
#define BULBASAUR_HEIGHT 0.7
#define BULBASAUR_WEIGHT 6.9
#define BULBASAUR_FIRST_TYPE GRASS_TYPE
#define BULBASAUR_SECOND_TYPE POISON_TYPE

// Sample data on Ivysaur, the Pokemon with pokemon_id 2.
#define IVYSAUR_ID 2
#define IVYSAUR_NAME "Ivysaur"
#define IVYSAUR_HEIGHT 1.0
#define IVYSAUR_WEIGHT 13.0
#define IVYSAUR_FIRST_TYPE GRASS_TYPE
#define IVYSAUR_SECOND_TYPE POISON_TYPE

#define VENUSAUR_ID 3 
#define VENUSAUR_NAME "Venusaur"
#define VENUSAUR_HEIGHT 1.0 
#define VENUSAUR_WEIGHT 100.0 
#define VENUSAUR_FIRST_TYPE GRASS_TYPE
#define VENUSAUR_SECOND_TYPE POISON_TYPE

#define CHARMANDER_ID 4 
#define CHARMANDER_NAME "Charmander"
#define CHARMANDER_HEIGHT 0.6 
#define CHARMANDER_WEIGHT 8.5 
#define CHARMANDER_FIRST_TYPE FIRE_TYPE 
#define CHARMANDER_SECOND_TYPE NONE_TYPE

#define CHARMELEON_ID 5 
#define CHARMELEON_NAME "Charmeleon"
#define CHARMELEON_HEIGHT 1.1 
#define CHARMELEON_WEIGHT 19.0 
#define CHARMELEON_FIRST_TYPE FIRE_TYPE
#define CHARMELEON_SECOND_TYPE NONE_TYPE

#define CHARIZARD_ID 6 
#define CHARIZARD_NAME "Charizard"
#define CHARIZARD_HEIGHT 1.7
#define CHARIZARD_WEIGHT 90.5
#define CHARIZARD_FIRST_TYPE FIRE_TYPE
#define CHARIZARD_SECOND_TYPE FLYING_TYPE


// Add your own prototypes here.


// Tests for Pokedex functions from pokedex.c.
static void test_new_pokedex(void);
static void test_add_pokemon(void);
static void test_get_found_pokemon(void);
static void test_next_pokemon(void);

// Helper functions for creating/comparing Pokemon.
static Pokemon create_bulbasaur(void);
static Pokemon create_ivysaur(void);
static Pokemon create_venusaur(void);
static Pokemon create_charmander(void);
static Pokemon create_charmeleon(void);
static Pokemon create_charizard(void);
static int is_same_pokemon(Pokemon first, Pokemon second);
static int is_copied_pokemon(Pokemon first, Pokemon second);



int main(int argc, char *argv[]) {
    printf("Welcome to the COMP1511 Pokedex Tests!\n");

    printf("\n==================== Pokedex Tests ====================\n");

    test_new_pokedex();
    test_add_pokemon();
    test_next_pokemon();
    test_get_found_pokemon();

    printf("\nAll Pokedex tests passed, you are Awesome!\n");
}


////////////////////////////////////////////////////////////////////////
//                     Pokedex Test Functions                         //
////////////////////////////////////////////////////////////////////////

// `test_new_pokedex` checks whether the new_pokedex and destroy_pokedex
// functions work correctly, to the extent that it can.
//
// It does this by creating a new Pokedex, checking that it's not NULL,
// then calling destroy_pokedex.
//
// Note that it isn't possible to check whether destroy_pokedex has
// successfully destroyed/freed the Pokedex, so the best we can do is to
// call the function and make sure that it doesn't crash..
static void test_new_pokedex(void) {
    printf("\n>> Testing new_pokedex\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("       --> Checking that the returned Pokedex is not NULL\n");
    assert(pokedex != NULL);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed new_pokedex tests!\n");
}

// `test_add_pokemon` checks whether the add_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur (using the helper
// functions in this file and the provided code in pokemon.c), and
// calling add_pokemon to add it to the Pokedex.
//
// Some of the ways that you could extend these test would include:
//   - ... and more!
static void test_add_pokemon(void) {
    printf("\n>> Testing add_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur\n");
    Pokemon bulbasaur = create_bulbasaur();

    printf("    ... Adding Bulbasaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    
    printf("    ...Checking Bulbasaur was successfully added to the Pokedex\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    
    printf("    ... Checking Bulbasaur is correctly set as currently selected\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    
    printf("    ... Checking that the total amount of pokemon counted is correct\n");
    assert(count_total_pokemon(pokedex) == 1);

    printf("    ... Creating Ivysaur\n");
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, ivysaur);

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    
    printf("    ...Checking Ivysaur was successfully added to the Pokedex\n");   
    assert(is_same_pokemon(get_current_pokemon(pokedex),ivysaur));
    
    printf("    ... Checking Ivysaur is correctly set as currently selected\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    printf("    ... Checking that the total amount of pokemon counted is correct\n");
    assert(count_total_pokemon(pokedex) == 2);

    printf("    ... Creating Venusaur\n");
    Pokemon venusaur = create_venusaur();

    printf("    ... Adding Venusaur to the Pokedex\n");
    add_pokemon(pokedex, venusaur);

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    
    printf("    ...Checking Venusaur was successfully added to the Pokedex\n");   
    assert(is_same_pokemon(get_current_pokemon(pokedex), venusaur));
    
    printf("    ... Checking Venusaur is correctly set as currently selected\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), venusaur));
    
    printf("    ... Checking that the total amount of pokemon counted is correct\n");
    assert(count_total_pokemon(pokedex) == 3);
    
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon tests!\n");
}

// `test_next_pokemon` checks whether the next_pokemon function works
// correctly.
//
// Some of the ways that you could extend these tests would include:
//   - ... and more!
static void test_next_pokemon(void) {
    printf("\n>> Testing next_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Testing \"next\" works when no pokemon in pokedex\n");
    assert(pokedex != NULL);
    
    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon venusaur = create_venusaur();
    Pokemon charmander = create_charmander();
    Pokemon charmeleon = create_charmeleon();
    Pokemon charizard = create_charizard();

    printf("    ... Adding Bulbasaur, Ivysaur, Venusaur, Charmander, Charmeleon, Charizard to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, venusaur);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, charmeleon);
    add_pokemon(pokedex, charizard);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Venusaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), venusaur));
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Charmander\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charmander));
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Charmeleon\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charmeleon));
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Charizard\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), charizard));
    
    printf("    ... Testing \"next\" works when no pokemon next in pokedex\n");
    assert(pokedex != NULL);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed next_pokemon tests!\n");
}



// `test_get_found_pokemon` checks whether the get_found_pokemon
// function works correctly.
//
// Some of the ways that you could extend these tests would include:
//   - checking that the original Pokedex has not been modified,
//   - ... and more!
static void test_get_found_pokemon(void) {
    printf("\n>> Testing get_found_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Testing that get_found_pokemon works with an empty Pokedex\n");

    printf("    ... Getting all found Pokemon\n");
    Pokedex found_pokedex = get_found_pokemon(pokedex);
    
    printf("    ... Testing that total found pokemon is 0\n");    
    assert(count_total_pokemon(found_pokedex) == 0);
    
    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon venusaur = create_venusaur();
    Pokemon charmander = create_charmander();
    Pokemon charmeleon = create_charmeleon();
    Pokemon charizard = create_charizard();    

    printf("    ... Adding Bulbasaur, Ivysaur, Venusaur, Charmander, Charmeleon, Charizard to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, venusaur);
    add_pokemon(pokedex, charmeleon);
    add_pokemon(pokedex, charmander);
    add_pokemon(pokedex, charizard);
    
    printf("    ... Testing that get_found_pokemon works with no pokemon found in Pokedex\n");
    assert(count_found_pokemon(found_pokedex) == 0);
    found_pokedex = get_found_pokemon(pokedex);
    
    printf("    ... Testing that total found pokemon is 0\n");    
    assert(count_total_pokemon(found_pokedex) == 0);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);    
    
    printf("       --> Checking that the current Pokemon is Charmeleon\n");
    assert(get_current_pokemon(pokedex) == charmeleon);
    
    printf("    ... Setting Charmeleon to be found\n");
    find_current_pokemon(pokedex);
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Charmander\n");
    assert(get_current_pokemon(pokedex) == charmander);
    
    printf("    ... Setting Charmander to be found\n");
    find_current_pokemon(pokedex);


    printf("    ... Getting all found Pokemon\n");
    found_pokedex = get_found_pokemon(pokedex);

    printf("       --> Checking the correct Pokemon were copied and returned in Ascending Order\n");
    assert(count_total_pokemon(found_pokedex) == 3);
    assert(count_found_pokemon(found_pokedex) == 3);
    
    printf("    ... Checking that Bulbasaur was copied into the get_found Pokedex\n");
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(found_pokedex);
    
    printf("    ... Checking that Charmander was copied into the get_found Pokedex\n");
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), charmander));
    
    printf("    ... Moving to the next pokemon\n");
    next_pokemon(found_pokedex);
    
    printf("    ... Checking that Charmeleon was copied into the get_found Pokedex\n");
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), charmeleon));
       
    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    printf(">> Passed get_found_pokemon tests!\n");
}




// Write your own Pokedex tests here!


////////////////////////////////////////////////////////////////////////
//                     Helper Functions                               //
////////////////////////////////////////////////////////////////////////

// Helper function to create Bulbasaur for testing purposes.
static Pokemon create_bulbasaur(void) {
    Pokemon pokemon = new_pokemon(
            BULBASAUR_ID, BULBASAUR_NAME,
            BULBASAUR_HEIGHT, BULBASAUR_WEIGHT,
            BULBASAUR_FIRST_TYPE,
            BULBASAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Ivysaur for testing purposes.
static Pokemon create_ivysaur(void) {
    Pokemon pokemon = new_pokemon(
            IVYSAUR_ID, IVYSAUR_NAME,
            IVYSAUR_HEIGHT, IVYSAUR_WEIGHT,
            IVYSAUR_FIRST_TYPE,
            IVYSAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Venusaur for testing purposes.
static Pokemon create_venusaur(void) {
    Pokemon pokemon = new_pokemon(
            VENUSAUR_ID, VENUSAUR_NAME,
            VENUSAUR_HEIGHT, VENUSAUR_WEIGHT,
            VENUSAUR_FIRST_TYPE,
            VENUSAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Charmander for testing purposes.
static Pokemon create_charmander(void) {
    Pokemon pokemon = new_pokemon(
            CHARMANDER_ID, CHARMANDER_NAME,
            CHARMANDER_HEIGHT, CHARMANDER_WEIGHT,
            CHARMANDER_FIRST_TYPE,
            CHARMANDER_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Charmeleon for testing purposes.
static Pokemon create_charmeleon(void) {
    Pokemon pokemon = new_pokemon(
            CHARMELEON_ID, CHARMELEON_NAME,
            CHARMELEON_HEIGHT, CHARMELEON_WEIGHT,
            CHARMELEON_FIRST_TYPE,
            CHARMELEON_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Charizard for testing purposes.
static Pokemon create_charizard(void) {
    Pokemon pokemon = new_pokemon(
            CHARIZARD_ID, CHARIZARD_NAME,
            CHARIZARD_HEIGHT, CHARIZARD_WEIGHT,
            CHARIZARD_FIRST_TYPE,
            CHARIZARD_SECOND_TYPE
    );
    return pokemon;
}
// Helper function to compare whether two Pokemon are the same.
// This checks that the two pointers contain the same address, i.e.
// they are both pointing to the same pokemon struct in memory.
//
// Pokemon ivysaur = new_pokemon(0, 'ivysaur', 1.0, 13.0, GRASS_TYPE, POISON_TYPE)
// Pokemon also_ivysaur = ivysaur
// is_same_pokemon(ivysaur, also_ivysaur) == TRUE
static int is_same_pokemon(Pokemon first, Pokemon second) {
    return first == second;
}

// Helper function to compare whether one Pokemon is a *copy* of
// another, based on whether their attributes match (e.g. pokemon_id,
// height, weight, etc).
// 
// It also checks that the pointers do *not* match -- i.e. that the
// pointers aren't both pointing to the same pokemon struct in memory.
// If the pointers both contain the same address, then the second
// Pokemon is not a *copy* of the first Pokemon.
// 
// This function doesn't (yet) check that the Pokemon's names match
// (but perhaps you could add that check yourself...).
static int is_copied_pokemon(Pokemon first, Pokemon second) {
    return (pokemon_id(first) == pokemon_id(second))
    &&  (first != second)
    &&  (pokemon_height(first) == pokemon_height(second))
    &&  (pokemon_weight(first) == pokemon_weight(second))
    &&  (pokemon_first_type(first) == pokemon_first_type(second))
    &&  (pokemon_second_type(first) == pokemon_second_type(second));
}

// Write your own helper functions here!
