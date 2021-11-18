#ifndef OBJECT_OBJECT
#define OBJECT_OBJECT
#include <vector>
#include <cstdio>
#include <string>
#include "raylib.h"
#include "raymath.h"

class Object {
public:
    Object(){}
    Object(Rectangle rect, Color color, bool shouldCollide = true, bool shouldTick = true, int shapeID = 0);
    virtual bool Update(std::vector<Object*> objects, float delta) { return false; }
    bool IsCollidingWith(Object object);
    int shapeID = 0;
    bool shouldCollide = true;
    bool shouldTick = true;
    Rectangle rect;
    Color originalColor;
    Color color;
};

#endif /* OBJECT_OBJECT */
