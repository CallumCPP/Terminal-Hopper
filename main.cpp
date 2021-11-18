#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "Object/Object.hpp"
#include "Object/Objects/Player.hpp"
#include "Object/Objects/Trigger.hpp"
#include "Object/Objects/Coin.hpp"
#include "Object/Objects/Portal.hpp"
#include <vector>
#include <string>

typedef unsigned char u_char;
std::vector<Object*> objects;
std::vector<Trigger*> triggers;
void GameLoop();
void NewTrigger(Rectangle rect, Color color, std::function<void()> event);
void UpdateCamera(Camera2D* camera, Player* player, int width, int height);
Color NewColor(u_char r, u_char g, u_char b, u_char a = 255);
void FlipGravity();
void LoadObjects();
void ShowMenu();

bool showMenu;
bool shouldClose;
int screenWidth;
int screenHeight;
Player* currPlayer;
Camera2D* camera; 

enum ShapeID {
    Rect,
    Ellipse
};

bool ticked = false;
float timeSinceTick = 0;
float tickThreshold = 1;
int main(void) {
    InitWindow(0, 0, "2D Platformer");
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    SetExitKey(-1);
    ToggleFullscreen();

    Player player({ -20, -40, 40, 40 }, PINK);
    currPlayer = &player;
    objects.push_back(&player);
    LoadObjects();
    

    Camera2D camera = { 0 };
    camera.target = (Vector2){player.rect.x + 20, player.rect.y + 20};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose() && !shouldClose) {
        float deltaTime = GetFrameTime();
        if (IsKeyDown(KEY_ESCAPE)) showMenu = true;
        if (!showMenu) {
            timeSinceTick += deltaTime;
            for(int i = 0; i < objects.size(); i++){
                if (timeSinceTick > tickThreshold && objects[i]->shouldTick){
                    ticked = true;
                    objects[i]->shouldCollide = !objects[i]->shouldCollide;
                    objects[i]->color = NewColor(
                        objects[i]->originalColor.r * objects[i]->shouldCollide, 
                        objects[i]->originalColor.g * objects[i]->shouldCollide,
                        objects[i]->originalColor.b * objects[i]->shouldCollide
                    );
                }
            }
            if (ticked) {
                timeSinceTick = 0;
                ticked = false;
            }
        }
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        if (IsKeyPressed(KEY_R)) {
            player.rect = { -20, -40, 40, 40 };
            player.speed = 0;
            camera.zoom = 1.0f;
        }

        UpdateCamera(&camera, &player, screenWidth, screenHeight);
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(camera);
                for (int i = 0; i < objects.size(); i++) {
                    if (i){
                        if (objects[i]->shapeID == 0) DrawRectangleRec(objects[i]->rect, objects[i]->color);
                        else if (objects[i]->shapeID == 1) 
                            DrawEllipse(objects[i]->rect.x + objects[i]->rect.width/2, 
                                        objects[i]->rect.y + objects[i]->rect.height/2,
                                        objects[i]->rect.width/2,
                                        objects[i]->rect.height/2,
                                        objects[i]->color);
                    }
                    DrawRectangleRec(objects[0]->rect, objects[0]->color);
                    if (objects[i]->Update(objects, deltaTime)) objects[i]->rect = { 0, -810, 0, 0};
                }

                for (int i = 0; i < triggers.size(); i++) {
                    DrawRectangleRec(triggers[i]->rect, triggers[i]->color);
                    if (triggers[i]->IsCollidingWith(*currPlayer)) triggers[i]->Event();
                }
            EndMode2D();
            DrawText(std::string("Coins: " + std::to_string(player.coinCount)).c_str(), 40, screenHeight - 40, 10, DARKGRAY);
            if (showMenu) ShowMenu();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void LoadObjects(){
    objects.push_back(new Object({ -30, -500, 10000, 10}, GREEN, true, false));
    objects.push_back(new Object({ 250, -400, 100, 10}, GREEN, true));
    objects.push_back(new Object({ 250, 300, 100, 10}, GREEN, true));
    objects.push_back(new Object({ 300, 200, 400, 10}, GREEN, false));
    objects.push_back(new Object({ 650, 300, 100, 10}, GREEN, true));
    objects.push_back(new Object({ -30, 400, 10000, 10}, GREEN, true, false));
    objects.push_back(new Portal({ 100, 200, 100, 10}, GREEN, {100, -400}, false));
    
    objects.push_back(new Coin({ 300, 150, 50, 50}, YELLOW));
    objects.push_back(new Coin({ 360, 150, 50, 50}, YELLOW));
    objects.push_back(new Coin({ 420, 150, 50, 50}, YELLOW));
    objects.push_back(new Coin({ 480, 150, 50, 50}, YELLOW));

    NewTrigger({ 100, 398, 100, 2}, NewColor(255, 255, 0), FlipGravity);
    NewTrigger({ 100, -490, 100, 2}, NewColor(255, 255, 0), FlipGravity);
}

void ShowMenu(){
    if (GuiButtonCustom((Rectangle){ screenWidth / 4, screenHeight / 2 - 30, screenWidth / 2, 50 }, "Resume", NewColor(0, 255, 0), NewColor(0, 0, 0), NewColor(0, 255, 0))) showMenu = false;
    if (GuiButtonCustom((Rectangle){ screenWidth / 4, screenHeight / 2 + 30, screenWidth / 2, 50 }, "Exit", NewColor(0, 255, 0), NewColor(0, 0, 0), NewColor(0, 255, 0))) shouldClose = true;

    DrawText("- Right/Left or D/A to move", 40, 40, 10, DARKGRAY);
    DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
    DrawText("- S to unstick", 40, 80, 10, DARKGRAY);
    DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 100, 10, DARKGRAY);
}

void UpdateCamera(Camera2D* camera, Player* player, int width, int height) {
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = (Vector2){player->rect.x + 20, player->rect.y + 20};
}

Color NewColor(u_char r, u_char g, u_char b, u_char a){
    return CLITERAL(Color){ r, g, b, a };
}

void NewTrigger(Rectangle rect, Color color, std::function<void()> event){
    triggers.push_back(new Trigger(
        rect,
        color,
        event
    ));
}

void FlipGravity(){
    currPlayer->G = -currPlayer->G;
    currPlayer->speed = -currPlayer->jumpSpeed;
    currPlayer->jumpSpeed = -currPlayer->jumpSpeed;
}
