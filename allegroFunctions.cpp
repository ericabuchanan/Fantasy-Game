// Includes functions specific to allegro display
#include "includes.h"
#include "Hunter.h"
#include "Warrior.h"
#include "prototypes.h"

// State global variables
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *character;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_FONT *font;

// Initialize allegro, display, font, keyboard and event queue
bool initialize_allegro(){
    // Check if different components were initialized correctly
    if (!al_init_image_addon() || !al_init() || !al_init_font_addon() || !al_init_ttf_addon()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }
    // Create display
    display = al_create_display(WIDTH,HEIGHT+INSTRUCTIONS);
    // Check if display was created
    if (!display){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }
    // Initialize font
    font = al_load_ttf_font("OpenSans-Regular.ttf", TEXT_SIZE, 0);
    // Check if font was initialized
    if (!font){
        cout << "Could not initialize font." << endl;
        return false;
    }

    // Install keyboard and check if it was installed
    al_install_keyboard();
    if (!al_is_keyboard_installed()){
        al_show_native_message_box(display, "Error", "Error", "Failed to install keyboard.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // Create event queue and check if it was created
    event_queue = al_create_event_queue();
    if (!event_queue){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize event queue.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }
    // Create keyboard event source
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    // Set title for graphics window
    al_set_window_title(display, "Fantasy Game");
    return true;
}

// Shows image of both characters
bool show_characters(){
    // Initialize character image and check if it was initialized
    character  = al_load_bitmap("fantasyAssets/GameSprites.png");
    if (!character){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return false;
    }
    // Make screen white and display characters
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(character, 0, 0, 0);
    // Update display
    al_flip_display();
    al_rest(.5);
    return true;
}

// Show basic hunter image
void show_hunter(){
    // Make screen white
    al_clear_to_color(al_map_rgb(255,255,255));
    // Display hunter
    al_draw_bitmap_region(character, WIDTH/2, 0, WIDTH/2, HEIGHT, WIDTH/4, 0, 0);
    // Update display
    al_flip_display();
    al_rest(.5);
}

// Show basic warrior image
void show_warrior(){
    // Make screen white
    al_clear_to_color(al_map_rgb(255,255,255));
    // Display warrior
    al_draw_bitmap_region(character, 0, 0, WIDTH/2, HEIGHT, WIDTH/4, 0, 0);
    // Update display
    al_flip_display();
    al_rest(.5);
}

// Print text showing user's character choices
void print_character_choices(){
    // Initialize black colour
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    // Print character choice text
    al_draw_text(font, black, 0, HEIGHT+TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "Who would you like to play as? (press the corresponding number)");
    al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, "1. Warrior");
    al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*3), ALLEGRO_ALIGN_LEFT, "2. Hunter");
    // Update display
    al_flip_display();
    al_rest(.5);
}

// Print text showing user's action choices
void print_move_choices(){
    // Initialize black colour
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    // Print move choice text
    al_draw_text(font, black, 0, HEIGHT+TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "What would you like to do? (press the corresponding number)");
    al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, "1. Hunt for food");
    al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*3), ALLEGRO_ALIGN_LEFT, "2. Fight monsters");
    al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*4), ALLEGRO_ALIGN_LEFT, "3. Search for treasure");
    // Update display
    al_flip_display();
    al_rest(.5);
}


