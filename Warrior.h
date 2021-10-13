// Define warrior class inheriting from Character class

#include "Character.h"

class Warrior: public Character{
    public:
        Warrior();
        Warrior(int m, int f, int h);
        ~Warrior();
        int Menu();
        void toString();
        void findFood();
        void fightMonsters();
        void searchTreasure();
        void show_warrior_food();
        void show_warrior_attack();
        void show_warrior_treasure();

        bool load_warrior_attack;
        bool load_warrior_food;
        bool load_warrior_treasure;

    private:
        ALLEGRO_BITMAP *warrior_food;
        ALLEGRO_BITMAP *warrior_attack;
        ALLEGRO_BITMAP *warrior_treasure;
};
