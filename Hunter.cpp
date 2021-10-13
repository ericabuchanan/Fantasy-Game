// Define methods and variables for Hunter class

#include "Hunter.h"

// State global variables
extern ALLEGRO_FONT *font;

// Default constructor initializes variables
Hunter::Hunter(){
    Character();
    // Initialize image load variables to true
    load_hunter_attack = true;
    load_hunter_food = true;
    load_hunter_treasure = true;
    // Load images
    hunter_food = al_load_bitmap("fantasyAssets/HunterFood.png");
    hunter_attack = al_load_bitmap("fantasyAssets/HunterAttack.png");
    hunter_treasure = al_load_bitmap("fantasyAssets/HunterTreasure.png");
    // Set image load variables to false if they fail to load
    if (!hunter_food){
        cout << "Failed to load hunter food image." << endl;
        load_hunter_food = false;
    }
    if (!hunter_attack){
        cout << "Failed to load hunter attack image." << endl;
        load_hunter_attack = false;
    }
    if(!hunter_treasure){
        cout << "Failed to load hunter treasure image." << endl;
        load_hunter_treasure = false;
    }
}

// Constructor sets points variables to given values and initializes images
Hunter::Hunter(int m, int f, int h){
    // Set points variables if the given values are in range
    if (m > 0 && m <= MAX_MONEY){
        setMoney(m);
    // If not in range, set to default value
    }else{
        setMoney(10);
    }
    if (f > 0 && f <= MAX_FAME){
        setFame(f);
    }else{
        setFame(8);
    }
    if (h > 0 && h < MAX_HEALTH){
        setHealth(h);
    }else{
        setHealth(10);
    }
    // Initialize image load variables to true
    load_hunter_attack = true;
    load_hunter_food = true;
    load_hunter_treasure = true;
    // Load images
    hunter_food = al_load_bitmap("fantasyAssets/HunterFood.png");
    hunter_attack = al_load_bitmap("fantasyAssets/HunterAttack.png");
    hunter_treasure = al_load_bitmap("fantasyAssets/HunterTreasure.png");
    // Set image load variables to false if they fail to load
    if (!hunter_food){
        cout << "Failed to load hunter food image." << endl;
        load_hunter_food = false;
    }
    if (!hunter_attack){
        cout << "Failed to load hunter attack image." << endl;
        load_hunter_attack = false;
    }
    if(!hunter_treasure){
        cout << "Failed to load hunter treasure image." << endl;
        load_hunter_treasure = false;
    }
}

// Deconstructor destroys images if they were loaded correctly
Hunter::~Hunter(){
    if (load_hunter_attack){
        al_destroy_bitmap(hunter_attack);
    }
    if (load_hunter_food){
        al_destroy_bitmap(hunter_food);
    }
    if (load_hunter_treasure){
        al_destroy_bitmap(hunter_treasure);
    }
}

// Prints the user's stats by calling toString() and prints final statement when the user dies
int Hunter::Menu(){
    // Set black allegro colour
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    // Initialize and print the image of the dead hunter if any variables are 0
    if (getHealth() == 0 || getFame() == 0 || getMoney() == 0){
        ALLEGRO_BITMAP *hunter_basic = al_load_bitmap("fantasyAssets/HunterSpriteBasic.png");
        if (!hunter_basic){
            cout << "Failed to load image. Exiting game." << endl;
            return -1;
        }
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_bitmap(hunter_basic, WIDTH/4, HEIGHT/6, 0);
    }
    // Prints statement if the user dies to indicate why they died and returns 0
    if (getHealth() == 0){
        al_draw_text(font, black, 0, HEIGHT+TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You have died due to poor health.");
        if (getDay() == 2){
            al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, "You survived for 1 day.");
        }else{
            string statement = "You survived for " + to_string(getDay()-1) + " days.";
            al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, statement.c_str());
        }
        al_flip_display();
        al_rest(3);
        return 0;
    }
    if (getFame() == 0){
        al_draw_text(font, black, 0, HEIGHT+TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You no longer have any fans. Poor you.");
        if (getDay() == 2){
            al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, "You survived for 1 day.");
        }else{
            string statement = "You survived for " + to_string(getDay()-1) + " days.";
            al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, statement.c_str());
        }
        al_flip_display();
        al_rest(3);
        return 0;
    }
    if (getMoney() == 0){
        al_draw_text(font, black, 0, HEIGHT+TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "Unfortunately, you have gone broke.");
        if (getDay() == 2){
            al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, "You survived for 1 day.");
        }else{
            string statement = "You survived for " + to_string(getDay()-1) + " days.";
            al_draw_text(font, black, 0, HEIGHT+(TEXT_SIZE*2), ALLEGRO_ALIGN_LEFT, statement.c_str());
        }
        al_flip_display();
        al_rest(3);
        return 0;
    }
    // Call function to print user's stats
    toString();
    // Return 1 if the user has not died yet
    return 1;
}

// Prints the user's stats every day
void Hunter::toString(){
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    string dayStatement = "DAY "+ to_string(getDay());
    string healthStatement = "Health: " + to_string(getHealth()) + "/" + to_string(MAX_HEALTH);
    string fameStatement = "Fame: " + to_string(getFame()) + "/" + to_string(MAX_FAME);
    string moneyStatement = "Money: " + to_string(getMoney()) + "/" + to_string(MAX_MONEY);
    al_draw_text(font, red, WIDTH, 0, ALLEGRO_ALIGN_RIGHT, dayStatement.c_str());
    al_draw_text(font, red, WIDTH, TEXT_SIZE, ALLEGRO_ALIGN_RIGHT, "Character: Hunter");
    al_draw_text(font, red, WIDTH, TEXT_SIZE*2, ALLEGRO_ALIGN_RIGHT, healthStatement.c_str());
    al_draw_text(font, red, WIDTH, TEXT_SIZE*3, ALLEGRO_ALIGN_RIGHT, fameStatement.c_str());
    al_draw_text(font, red, WIDTH, TEXT_SIZE*4, ALLEGRO_ALIGN_RIGHT, moneyStatement.c_str());
    al_flip_display();
    al_rest(.5);
}

// Increases hunter's health by a random number between 6 and 11
void Hunter::findFood(){
    // Define red allegro colour
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    // Get health value
    int h = getHealth();
    // Set seed for random number generator
    srand(time(0));
    // Randomly generate a number from 6 to 11
    int foodHealth = rand()%6+6;
    // Check if new health value is greater than max
    if (h+foodHealth >= MAX_HEALTH){
        // Sets value to max if it was greater and print statement to user
        setHealth(MAX_HEALTH);
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You hunted very successfully and returned home feeling replenished.");
        al_flip_display();
    }else{
        // Find new health value and set it if it is less than the max value
        h += foodHealth;
        setHealth(h);
        // Tell the user they got points
        string statement = "You hunted successfully and gained " + to_string(foodHealth) + " health points.";
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, statement.c_str());
        al_flip_display();

    }
}

// Hunter isn't as good at fighting monsters, this increases fame values by a random value from 6 to 10 and reduces health by half of that value
void Hunter::fightMonsters(){
    // Define red allegro colour
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    // Get fame and health values
    int f = getFame();
    int h = getHealth();
    // Seed random number generator
    srand(time(0));
    // Generate random number for 6 to 10 for fame increase
    int monsterFame = rand()%5+6;
    // Set health lost to half that value
    int monsterDamage = monsterFame/2;
    // Check if new fame value is greater than max value
    if (f+monsterFame >= MAX_FAME){
        // Set fame to max value if new value was greater
        monsterFame = MAX_FAME-f;
        setFame(MAX_FAME);
    }else{
        // Set fame to new value if not
        f += monsterFame;
        setFame(f);
    }
    // Check if new health value is below 0
    if (h - monsterDamage < 0){
        // Set health value to 0 if new value was lower
        setHealth(0);
        monsterDamage = h;
    }else{
        // Set health value to new health value otherwise
        h -= monsterDamage;
        setHealth(h);
    }
    // Tell the user the outcome of their battle
    string statement = "You fought a long battle, losing " + to_string(monsterDamage) + " HP through injuries. In the end you won and gained " + to_string(monsterFame) + " fame points.";
    al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, statement.c_str());
    al_flip_display();
}

// Hunter is decent at finding treasure, this increases the money value by 7
void Hunter::searchTreasure(){
    // Define red allegro colour
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    // Get money value
    int m = getMoney();
    // Set treasure value
    int treasureMoney = 7;
    // Check if new money value is greater than max value
    if (m+treasureMoney > MAX_MONEY){
        // Set money to max if new value is greater and tell user
        setMoney(MAX_MONEY);
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You searched all day and happened upon a big treasure. Lucky you!");
        al_flip_display();
    }else{
        // Set money to new money value and tell user if it is not greater than max
        m += treasureMoney;
        setMoney(m);
        string statement = "You spent your day searching and found a bit of treasure. You got " + to_string(treasureMoney) + " money points.";
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, statement.c_str());
        al_flip_display();
    }
}

// Display the image of hunter hunting
void Hunter::show_hunter_food(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(hunter_food, WIDTH/4, 0, 0);
    al_flip_display();
    al_rest(.5);
}

// Display the image of hunter attacking
void Hunter::show_hunter_attack(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(hunter_attack, WIDTH/4, 0, 0);
    al_flip_display();
    al_rest(.5);
}

// Display the image of hunter finding treasure
void Hunter::show_hunter_treasure(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(hunter_treasure, WIDTH/4, 0, 0);
    al_flip_display();
    al_rest(.5);
}
