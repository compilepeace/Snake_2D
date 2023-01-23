#ifndef _FOOD_H
#define _FOOD_H



class Food{
public:
    enum Type {
        kPoison,        // RED
        kHealthy,       // GREEN
        kBonus,         // YELLOW 
        kSizeOfEnum     // used to mark size of this enum
    };
    Food(Type s): type(s), x(-1), y(-1), onGrid(false) {}
    int x;
    int y;
    bool onGrid;       // each constructed food item in by default NOT present on grid
    Type type;
};

#endif  // _FOOD_H