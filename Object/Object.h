#ifndef OBJECT_OBJECT
#define OBJECT_OBJECT
#include "raylib.h"
#include "raymath.h"

class Object {
public:
    Object(){}
    Object(Rectangle rect, Color color, bool shouldCollide = true, bool shouldTick = true);
    bool IsCollidingWith(Object object);
    bool shouldCollide;
    bool shouldTick;
    Rectangle rect;
    Color originalColor;
    Color color;
};

#endif /* OBJECT_OBJECT */
