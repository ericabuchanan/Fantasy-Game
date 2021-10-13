// Define methods and variables for Warrior class

#include "Warrior.h"

// State global variables
extern ALLEGRO_FONT *font;

// Default constructor initializes images
Warrior::Warrior(){
    Character();
    // Initialize image load variables to true
    load_warrior_attack = true;
    load_warrior_food = true;
    load_warrior_treasure = true;
    // Load images
    warrior_food = al_load_bitmap("fantasyAssets/WarriorFood.png");
    warrior_attack = al_load_bitmap("fantasyAssets/WarriorAttack.png");
    warrior_treasure = al_load_bitmap("fantasyAssets/WarriorTreasure.png");
    // Set image load variables to false if they fail to load
    if (!warrior_food){
        cout << "Failed to load warrior food image." << endl;
        load_warrior_food = false;
    }
    if (!warrior_attack){
        cout << "Failed to load warrior attack image." << endl;
        load_warrior_attack = false;
    }
    if(!warrior_treasure){
        cout << "Failed to load warrior treasure image." << endl;
        load_warrior_treasure = false;
    }
}

// Constructor sets points variables to given values and initializes images
Warrior::Warrior(int m, int f, int h){
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
    load_warrior_attack = true;
    load_warrior_food = true;
    load_warrior_treasure = true;
    // Load images
    warrior_food = al_load_bitmap("fantasyAssets/WarriorFood.png");
    warrior_attack = al_load_bitmap("fantasyAssets/WarriorAttack.png");
    warrior_treasure = al_load_bitmap("fantasyAssets/WarriorTreasure.png");
    // Set image load variables to false if they fail to load
    if (!warrior_food){
        cout << "Failed to load warrior food image." << endl;
        load_warrior_food = false;
    }
    if (!warrior_attack){
        cout << "Failed to load warrior attack image." << endl;
        load_warrior_attack = false;
    }
    if(!warrior_treasure){
        cout << "Failed to load warrior treasure image." << endl;
        load_warrior_treasure = false;
    }
}

// Deconstructor destroys images if they were loaded correctly
Warrior::~Warrior(){
    if (load_warrior_attack){
        al_destroy_bitmap(warrior_attack);
    }
    if (load_warrior_food){
        al_destroy_bitmap(warrior_food);
    }
    if (load_warrior_treasure){
        al_destroy_bitmap(warrior_treasure);
    }
}

// Prints the user's stats by calling toString() and prints final statement when the user dies
int Warrior::Menu(){
    // Set black allegro colour
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    // Initialize and print the image of the dead warrior if any variables are 0
    if (getHealth() == 0 || getFame() == 0 || getMoney() == 0){
        ALLEGRO_BITMAP *warrior_basic = al_load_bitmap("fantasyAssets/WarriorSpriteBasic.png");
        if (!warrior_basic){
            cout << "Failed to load image. Exiting game." << endl;
            return -1;
        }
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_bitmap(warrior_basic, WIDTH/4, HEIGHT/6, 0);
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
void Warrior::toString(){
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    string dayStatement = "DAY "+ to_string(getDay());
    string healthStatement = "Health: " + to_string(getHealth()) + "/" + to_string(MAX_HEALTH);
    string fameStatement = "Fame: " + to_string(getFame()) + "/" + to_string(MAX_FAME);
    string moneyStatement = "Money: " + to_string(getMoney()) + "/" + to_string(MAX_MONEY);
    al_draw_text(font, red, WIDTH, 0, ALLEGRO_ALIGN_RIGHT, dayStatement.c_str());
    al_draw_text(font, red, WIDTH, TEXT_SIZE, ALLEGRO_ALIGN_RIGHT, "Character: Warrior");
    al_draw_text(font, red, WIDTH, TEXT_SIZE*2, ALLEGRO_ALIGN_RIGHT, healthStatement.c_str());
    al_draw_text(font, red, WIDTH, TEXT_SIZE*3, ALLEGRO_ALIGN_RIGHT, fameStatement.c_str());
    al_draw_text(font, red, WIDTH, TEXT_SIZE*4, ALLEGRO_ALIGN_RIGHT, moneyStatement.c_str());
    al_flip_display();
    al_rest(.5);
}

// Gives the warrior a 50% chance of finding a lot of food or none at all
void Warrior::findFood(){
    // Define red allegro colour
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    // Set seed for random number generator
    srand(time(0));
    // Randomly generate a 0 (false) or 1 (true)
    bool foodHealth = rand()%2;
    // Set food to max if a 1 was generated
    if (foodHealth){
        setHealth(MAX_HEALTH);
        // Tell the user if they got food
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You spent the day hunting and managed to find good food. You came home feeling replenished.");
        al_flip_display();
    // Do not change food if a 0 was generated
    }else{
        // Tell the user if they didn't get any food
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You spent the day hunting but couldn't find any food.");
        al_flip_display();
    }
}

// Gives warrior a random fame value from 7 to 14 and reduces health by 2 since warriors are good at fighting
void Warrior::fightMonsters(){
    // Define red allegro colour
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    // Get fame and health values
    int f = getFame();
    int h = getHealth();
    // Seed random number generator and generator a number forom 7 to 14
    srand(time(0));
    int monsterFame = rand()%8+7;
    // Set damage to health to 2
    int monsterDamage = 2;
    // Check if the new fame value is greater than the max value
    if (f+monsterFame >= MAX_FAME){
        monsterFame = MAX_FAME-f;
        // Set the fame to max if the new value is greater than max
        setFame(MAX_FAME);
    }else{
        // Set the fame to the new value if it is less than the max
        f += monsterFame;
        setFame(f);
    }
    // Check if the new health value is less than 0
    if (h - monsterDamage < 0){
        // If it is less than 0 set health to 0
        setHealth(0);
        monsterDamage = h;
    }else{
        // If it is greater than 0 set health to the new health value
        h -= monsterDamage;
        setHealth(h);
    }
    // Tell the user their results
    string statement = "You fought worthy opponent and managed to win. You lost " + to_string(monsterDamage) + " HP in the process but gained " + to_string(monsterFame) + " fame points.";
    al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, statement.c_str());
    al_flip_display();
}

// Warrior is always decent at searching for treasure, this function adds 5 money points
void Warrior::searchTreasure(){
    // Define red allegro colour
    ALLEGRO_COLOR red = al_map_rgb(255,0,0);
    // Get money value
    int m = getMoney();
    // Set value to add
    int treasureMoney = 5;
    // Set the money variable to max if the treasure brings it over max value
    if (m+treasureMoney > MAX_MONEY){
        setMoney(MAX_MONEY);
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, "You searched all day and happened upon a big treasure. Lucky you!");
        al_flip_display();
    // Set the money variable to the new value if it is under the max value
    }else{
        m += treasureMoney;
        setMoney(m);
        string statement = "You spent your day searching and found a bit of treasure. You got " + to_string(treasureMoney) + " money points.";
        al_draw_text(font, red, 0, HEIGHT-TEXT_SIZE, ALLEGRO_ALIGN_LEFT, statement.c_str());
        al_flip_display();
    }
}

// Display the image of warrior hunting
void Warrior::show_warrior_food(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(warrior_food, WIDTH/4, 0, 0);
    al_flip_display();
    al_rest(.5);

}

// Display the image of warrior attacking
void Warrior::show_warrior_attack(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(warrior_attack, WIDTH/4, 0, 0);
    al_flip_display();
    al_rest(.5);
}

// Display the image of warrior finding treasure
void Warrior::show_warrior_treasure(){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(warrior_treasure, WIDTH/4, 0, 0);
    al_flip_display();
    al_rest(.5);
}
