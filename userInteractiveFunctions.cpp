// Includes all functions that the user interacts with throughout the game

#include "includes.h"
#include "Hunter.h"
#include "Warrior.h"
#include "prototypes.h"

// State global variables
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *character;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_FONT *font;

// Prints the game intro to to the screen for the user to see until they press enter
void printIntro(){
    // Define colours
    ALLEGRO_COLOR white = al_map_rgb(255,255,255);
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    // Make screen white
    al_clear_to_color(white);
    // Display instructions
    al_draw_text(font, black, WIDTH/2, (HEIGHT/2)-(TEXT_SIZE*3), ALLEGRO_ALIGN_CENTER, "Welcome to the Fantasy Character Game!");
    al_draw_text(font, black, WIDTH/2, (HEIGHT/2)-TEXT_SIZE, ALLEGRO_ALIGN_CENTER, "You can play as one of two characters.");
    al_draw_text(font, black, WIDTH/2, (HEIGHT/2), ALLEGRO_ALIGN_CENTER, "You will need to manage your health, fame and money in order to survive!");
//    al_draw_text(font, black, WIDTH/2, (HEIGHT/2)+TEXT_SIZE, ALLEGRO_ALIGN_CENTER, "Direct your attention to the console for updates on your health as you make your decisions.");
    al_draw_text(font, black, WIDTH/2, (HEIGHT/2)+(TEXT_SIZE*3), ALLEGRO_ALIGN_CENTER, "Press enter to continue.");
    // Update display
    al_flip_display();
    al_rest(.5);
    // Keep the intro visible until the user presses enter
    bool startGame = false;
    while (!startGame){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                startGame = true;
            }
        }
    }
}

// Get the user's character choice and return it
int getUserCharacter(){
    // Does not exit the function until user has entered a valid character
    bool pickedCharacter = false;
    while (!pickedCharacter){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if (ev.keyboard.keycode == ALLEGRO_KEY_1){
                pickedCharacter = true;
                return 1;
            }else if (ev.keyboard.keycode == ALLEGRO_KEY_2){
                pickedCharacter = true;
                return 2;
            }
        }
    }
}

// Allows hunter character to play game until they are out of points
void hunterGamePlay(){
    // Initialize hunter's money, fame and health variables
    Hunter userHunter(10, 6, 13);
    // Initialize variable to a number that doesn't correspond to a real event
    int userFinishedGame = -1;
    // Call game functions once to start the game
    userFinishedGame = userHunter.Menu();
    userHunter.dailyDeduction();
    print_move_choices();
    // Continue to ask for the player's action choice until they run out of points
    while (userFinishedGame != 0){
        // Declare event
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        // Check for event type
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            // Call different actions depending on user input
            if (ev.keyboard.keycode == ALLEGRO_KEY_1){
                // Show hunter in action if the image is loaded
                if (userHunter.load_hunter_food){
                    userHunter.show_hunter_food();
                }
                // Alter user's points based on the action they picked and print the result
                userHunter.findFood();
            }else if (ev.keyboard.keycode == ALLEGRO_KEY_2){
                if (userHunter.load_hunter_attack){
                    userHunter.show_hunter_attack();
                }
                userHunter.fightMonsters();
            }else if (ev.keyboard.keycode == ALLEGRO_KEY_3){
                if (userHunter.load_hunter_treasure){
                    userHunter.show_hunter_treasure();
                }
                userHunter.searchTreasure();
            }else{
                continue;
            }
        // If another event type is registered restart the loop
        }else{
            continue;
        }
        // Call game functions again to continue playing
        userFinishedGame = userHunter.Menu();
        if (userFinishedGame != 0){
            userHunter.dailyDeduction();
            print_move_choices();
        }
    }
}

// Allows warrior character to play game until they are out of points
void warriorGamePlay(){
    // Initialize hunter's money, fame and health variables
    Warrior userWarrior(10, 11, 8);
    // Initialize variable to a number that doesn't correspond to a real event
    int userFinishedGame = -2;
    // Call game functions once to start the game
    userFinishedGame = userWarrior.Menu();
    userWarrior.dailyDeduction();
    print_move_choices();
    // Continue to ask for the player's action choice until they run out of points
    while (userFinishedGame != 0){
        if (userFinishedGame == -1){
            break;
        }
        // Declare event
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        // Check for event type
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            // Call different actions depending on user input
            if (ev.keyboard.keycode == ALLEGRO_KEY_1){
                // Show warrior in action if the image is loaded
                if (userWarrior.load_warrior_food){
                    userWarrior.show_warrior_food();
                }
                // Alter user's points based on the action they picked and print the result
                userWarrior.findFood();
            }else if (ev.keyboard.keycode == ALLEGRO_KEY_2){
                if (userWarrior.load_warrior_attack){
                    userWarrior.show_warrior_attack();
                }
                userWarrior.fightMonsters();
            }else if (ev.keyboard.keycode == ALLEGRO_KEY_3){
                if (userWarrior.load_warrior_treasure){
                    userWarrior.show_warrior_treasure();
                }
                userWarrior.searchTreasure();
            }else{
                continue;
            }
        // If another event type is registered restart the loop
        }else{
            continue;
        }
        // Call game functions again to continue playing
        userFinishedGame = userWarrior.Menu();
        if (userFinishedGame != 0){
            userWarrior.dailyDeduction();
            print_move_choices();
        }
    }
}
