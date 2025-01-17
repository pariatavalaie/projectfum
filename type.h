//
// Created by Asus on 12/18/2024.
//

#ifndef UNTITLED10_TYPE_H
#define UNTITLED10_TYPE_H
//Kingdom structure
typedef struct Kingdom {
    int id;
    int x;
    int y;
    int WorkersCount;
    int soldierCount;
    int GoldProduction;
    int FoodProduction;
    int Serve;
    int Gold;
    int villagenumber;
}Kingdom;

// Village structure
typedef struct Village {
    int VillageId;
    int x;
    int y;
    int ownerId;
    int GoldProduction;
    int FoodProduction;
}Village;

typedef struct map{
    int type;
    int road;
    int dificulty;
}Map;

#endif //UNTITLED10_TYPE_H
