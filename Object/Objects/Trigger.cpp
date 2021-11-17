#include "Trigger.h"

Trigger::Trigger(Rectangle rect, Color color, std::function<void()> event, bool shouldCollide, bool shouldTick) {
    this->rect = rect;
    this->color = color;
    this->originalColor = color;
    this->Event = event;
    this->shouldTick = shouldTick;
    this->shouldCollide = shouldCollide;
}