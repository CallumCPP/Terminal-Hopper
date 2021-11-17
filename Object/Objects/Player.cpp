#include "Player.h"

Player::Player(Rectangle rect, Color color, bool shouldCollide){
    this->rect = rect;
    this->originalColor = color;
    this->color = color;
    this->shouldCollide = shouldCollide;
    this->shouldTick = false;
}

void Player::Update(std::vector<Object*> objects, float delta) {
    if (this->rect.y > 800) { this->rect.x = 0; this->rect.y = -40; }
    bool jumped = false;
    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W)) && this->canJump) {
        this->speed = -jumpSpeed;
        this->canJump = false;
        jumped = true;
    }
    bool hitObstacle = 0;
    bool above = 0;
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i] != this){
            Object obj = *objects[i];
            Rectangle* rect = &this->rect;

            if (obj.shouldCollide && IsCollidingWith(obj) &&
                obj.rect.y < rect->y + rect->height + this->speed*delta)
            {
                if (obj.rect.y < rect->y + rect->height && G > 0) above = true;
                else if (obj.rect.y > rect->y) above = true;
                hitObstacle = 1;
                this->speed = 0.0f;
            }
        }
    }

    if (!hitObstacle) {
        if (IsKeyDown(KEY_A)) this->rect.x -= horSpeed*delta;
        if (IsKeyDown(KEY_D)) this->rect.x += horSpeed*delta;
        
        this->rect.y += this->speed*delta;
        this->speed += G*delta;
        this->canJump = false;
    }
    else {
        if (jumped && !above) this->rect.y -= this->jumpSpeed*delta;
        this->canJump = true;
    }
}