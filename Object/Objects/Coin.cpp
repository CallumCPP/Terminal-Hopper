#include "Coin.hpp"

Coin::Coin(Rectangle rect, Color color){
    this->shouldCollide = false;
    this->shouldTick = false;
    this->shapeID = 1;
    this->rect = rect;
    this->color = color;
}

bool Coin::Update(std::vector<Object*> objects, float delta){
    if (objects[0]->IsCollidingWith(*this)) {
        ((Player*)objects[0])->coinCount++;
        return true;
    }
    return false;
}