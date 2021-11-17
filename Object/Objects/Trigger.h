#ifndef OBJECT_OBJECTS_TRIGGER
#define OBJECT_OBJECTS_TRIGGER
#include <functional>
#include "../Object.h"

class Trigger : public Object {
public:
    Trigger(Rectangle rect, Color color, std::function<void()> event, bool shouldCollide = true, bool shouldTick = true);
    std::function<void()> Event;
};

#endif /* OBJECT_OBJECTS_TRIGGER */
