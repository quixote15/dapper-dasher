#include "raylib.h"

using namespace std;

int main()
{

    const int windowWidth{512}, windowHeight{380};

    InitWindow(windowWidth, windowHeight, "dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1'000};
    int velocity{0};

    // Scarfy textures
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;

    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;

    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // Nebula texture
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};

    Vector2 nebulaPos{windowWidth, windowHeight - nebulaRec.height};

    const int groundPosY = windowHeight - scarfyRec.height;

    // animation frame
    int frame{0};

    // amount of time before we update the animation frame
    float updateTime{1.0 / 12.0};
    float runningTime{0.0};

    // amount of time we updat enebula animation frame
    int nebFrame{0};
    const float nebUpdateTime{1.0 / 12.0};
    float nebRunningTime{0.0};

    // pixels/sec
    const int jumpVel{-600};
    const int nebVel{-200};
    bool isInAir{false};

    // 10 (p/f) * 60 (f/s) = 60 p/s
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time
        float dt{GetFrameTime()};

        // update scarfy running time
        runningTime += dt;

        // update nebula running time
        nebRunningTime += dt;

        BeginDrawing();
        ClearBackground(WHITE);

        // apply gravity
        if (scarfyPos.y >= groundPosY)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dt;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update scarfy position
        scarfyPos.y += velocity * dt;

        // update nebula position
        nebulaPos.x += nebVel * dt;

        if (nebulaPos.x < 0)
        {
            nebulaPos.x = windowWidth;
        }

        // update  scarfy animation frame
        if (runningTime >= updateTime && !isInAir)
        {

            // formula: fram * spritesWidth/6
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }

            runningTime = 0;
        }

        // update nebula animation frame
        if (nebRunningTime >= nebUpdateTime)
        {
            nebulaRec.x = nebFrame * nebulaRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
            nebRunningTime = 0;
        }

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    return 0;
}