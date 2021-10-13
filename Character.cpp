// Define methods and variables for Character class

#include "Character.h"

// Initialize class variables
int Character::MAX_HEALTH = 17;
int Character::MAX_FAME = 15;
int Character::MAX_MONEY = 20;

// Default constructor initializes private variables
Character::Character(){
    day = 1;
    money = 10;
    fame = 8;
    health = 10;
}
// Returns private health variable
int Character::getHealth(){
    if (health < 0){
        health = 0;
    }
    return health;
}
// Sets private health variable
void Character::setHealth(int h){
    health = h;
}
// Returns private fame variable
int Character::getFame(){
    if (fame < 0){
        fame = 0;
    }
    return fame;
}
// Sets private fame variable
void Character::setFame(int f){
    fame = f;
}
// Returns private money variable
int Character::getMoney(){
    if (money < 0){
        money = 0;
    }
    return money;
}
// Sets private money variable
void Character::setMoney(int m){
    money = m;
}
// Returns private day variable
int Character::getDay(){
    return day;
}
// Deducts three points from each category and increments the day
void Character::dailyDeduction(){
    health -= 3;
    fame -= 3;
    money -= 3;
    day++;
}
