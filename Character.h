// Define Character class

#include "includes.h"
#include "prototypes.h"

#ifndef CHARACTER
#define CHARACTER
class Character{
    public:
        Character();
        ~Character(){};

        int getHealth();
        void setHealth(int h);
        int getFame();
        void setFame(int f);
        int getMoney();
        void setMoney(int m);
        int getDay();

        void dailyDeduction();

        static int MAX_HEALTH;
        static int MAX_FAME;
        static int MAX_MONEY;

    private:
        int health;
        int fame;
        int money;
        int day;

};
#endif

