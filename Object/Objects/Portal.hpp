#ifndef OBJECT_OBJECTS_PORTAL
#define OBJECT_OBJECTS_PORTAL
#include "../Object.hpp"

class Portal : public Object {
public:
    Portal(Rectangle rect, Color color, Vector2 tpPos, bool shouldTick = true);
    bool Update(std::vector<Object*> objects, float delta) override;
    Vector2 tpPos;
};

#endif /* OBJECT_OBJECTS_PORTAL */
