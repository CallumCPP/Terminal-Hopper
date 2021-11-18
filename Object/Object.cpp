#include "Object.hpp"

Object::Object(Rectangle rect, Color color, bool shouldCollide, bool shouldTick, int shapeID){
    this->shouldCollide = shouldCollide;
    this->shouldTick = shouldTick;
    this->color = color;
    this->originalColor = color;
    this->rect = rect;
    this->shapeID = shapeID;
}

bool Object::IsCollidingWith(Object object){
    Rectangle rect1 = this->rect;
    Rectangle rect2 = object.rect;
    return (rect1.x < rect2.x + rect2.width &&
        rect1.x + rect1.width > rect2.x &&
        rect1.y < rect2.y + rect2.height &&
        rect1.height + rect1.y > rect2.y);
}