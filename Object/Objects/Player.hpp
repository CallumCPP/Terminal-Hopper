#ifndef OBJECT_OBJECTS_PLAYER
#define OBJECT_OBJECTS_PLAYER
#include "../Object.hpp"

class Player : public Object {
public:
    Player(Rectangle rect, Color color);
    bool Update(std::vector<Object*> objects, float delta) override;
    bool canJump;
    int coinCount = 0;
    float speed = 0;
    float G = 800.f;
    float horSpeed = 300.f;
    float jumpSpeed = 600.f;
};

#endif /* OBJECT_OBJECTS_PLAYER */
