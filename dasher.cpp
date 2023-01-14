#include "raylib.h"

using namespace std;

int main()
{

    const int windowWidth{512}, windowHeight{380};

    InitWindow(windowWidth, windowHeight, "dasher");

    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1'000};
    int velocity{0};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;

    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;

    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    const int groundPosY = windowHeight - scarfyRec.height;

    // animation frame
    int frame{0};

    // amount of time before we update the animation frame
    float updateTime{1.0 / 12.0};
    float runningTime{0.0};

    // pixels/sec
    const int jumpVel{-600};
    bool isInAir{false};

    // 10 (p/f) * 60 (f/s) = 60 p/s
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time
        float dt{GetFrameTime()};

        // update running time
        runningTime += dt;

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

        // update position
        scarfyPos.y += velocity * dt;

        // update animation frame
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

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();
    return 0;
}