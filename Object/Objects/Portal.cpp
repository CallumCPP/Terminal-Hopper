#include "Portal.hpp"

Portal::Portal(Rectangle rect, Color color, Vector2 tpPos, bool shouldTick){
    this->rect = rect;
    this->color = color;
    this->tpPos = tpPos;
    this->shouldTick = shouldCollide;
}

bool Portal::Update(std::vector<Object*> objects, float delta){
    if (this->shouldCollide && this->IsCollidingWith(*objects[0])){
        objects[0]->rect.x = tpPos.x;
        objects[0]->rect.y = tpPos.y;
    }
    return false;
}