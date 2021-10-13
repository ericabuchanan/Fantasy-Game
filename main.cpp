/*********************************************
* Erica Buchanan              Fantasy Game   *
* 20/04/2021                                 *
*                                            *
* This is a fantasy game that lets the user  *
* play as either a hunter or a warrior. As   *
* a fantasy character the user can choose to *
* hunt, to search for treasure or to fight   *
* monsters in order to gain health, money or *
* fame points. They must keep their all of   *
* their points above 0 to keep playing.      *
*********************************************/
#include "includes.h"
#include "Hunter.h"
#include "Warrior.h"
#include "prototypes.h"

// Declare global variables
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *character;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_FONT *font;

int main(int argc, char *argv[]){
    int userCharacterChoice;
    // Initialize allegro and add-ons
    if (!initialize_allegro()){
        return -1;
    }
    // Print intro to game
    printIntro();
    // Initialize and show character image
    if (!show_characters()){
        return -1;
    }
    // Let the user pick their character
    print_character_choices();
    userCharacterChoice = getUserCharacter();
    // Set the user character depending on their choice
    if (userCharacterChoice == 1){
        // Display warrior character to the screen
        show_warrior();
        // Let the user continue to pick their actions if they still have points
        warriorGamePlay();
    }else if (userCharacterChoice == 2){
        // Display hunter character to the screen
        show_hunter();
        // Let the user continue to pick their actions if they still have points
        hunterGamePlay();
    }
    // Destroy the allegro display and image
    al_destroy_display(display);
    al_destroy_bitmap(character);
    return 0;
}
