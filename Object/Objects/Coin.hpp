#ifndef OBJECT_OBJECTS_COIN
#define OBJECT_OBJECTS_COIN
#include "../Object.hpp"
#include "Player.hpp"

class Coin : public Object {
public:
    Coin(Rectangle rect, Color color);
    bool Update(std::vector<Object*> objects, float delta) override;
};

#endif /* OBJECT_OBJECTS_COIN */
