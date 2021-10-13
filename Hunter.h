// Define Hunter class inheriting from Character class

#include "Character.h"

class Hunter: public Character{
    public:
        Hunter();
        Hunter(int m, int f, int h);
        ~Hunter();
        int Menu();
        void toString();
        void findFood();
        void fightMonsters();
        void searchTreasure();
        void show_hunter_food();
        void show_hunter_attack();
        void show_hunter_treasure();

        bool load_hunter_attack;
        bool load_hunter_food;
        bool load_hunter_treasure;

    private:
        ALLEGRO_BITMAP *hunter_food;
        ALLEGRO_BITMAP *hunter_attack;
        ALLEGRO_BITMAP *hunter_treasure;
};
