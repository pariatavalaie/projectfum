//
// Created by Asus on 12/18/2024.
//

#ifndef UNTITLED10_TYPE_H
#define UNTITLED10_TYPE_H
struct Kingdom {
    int id;
    int x;
    int y;
    int WorkersCount;
    int soldierCount;
    int GoldProduction;
    int FoodProduction;
    int Food;
    int Gold;
};

// Village structure
struct Village {
    int VillageId;
    int x;
    int y;
    int ownerId;
    int GoldProduction;
    int FoodProduction;
};

#endif //UNTITLED10_TYPE_H
