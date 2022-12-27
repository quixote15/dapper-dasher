#include "raylib.h"

using namespace std;

int main()
{

    int width{800}, height{450};
    int circle_x{200}, circle_y{200};
    int circle_radius = 25;
    int axe_length = 50;

    int axe_x{400}, axe_y{0};

    int direction{10};

    /**
     *
     *  The dot "." is the circle center coordinate (circle_x, circle_y)
     *
     *     __ circle_x - radius
     *      O
     *    O   O
     *   O  .  O|-> circle_x + radius
     *    O   O
     *      O
     *      __ circle_x + radius
     */
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int upper_circle_y{circle_y - circle_radius};
    int bottom_circle_y{circle_y + circle_radius};

    int l_axe_x{axe_x};
    int r_axe_x{axe_x + axe_length};
    int upper_axe_y{axe_y};
    int bottom_axe_y{axe_y + axe_length};

    bool collision_with_axe = false;
    bool collision_with_bottom_r_edge = false;
    bool collision_with_bottom_l_edge = false;
    bool collision_with_upper_r_edge = false;
    bool collision_with_upper_l_edge = false;

    InitWindow(width, height, "Tiago da janela");

    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        collision_with_bottom_r_edge = (bottom_axe_y >= upper_circle_y && bottom_axe_y < bottom_circle_y) && (l_circle_x <= r_axe_x && l_circle_x > l_axe_x);
        collision_with_bottom_l_edge = (bottom_axe_y >= upper_circle_y && bottom_axe_y < bottom_circle_y) && (r_circle_x >= l_axe_x && r_circle_x < r_axe_x);

        collision_with_upper_l_edge = (upper_axe_y <= bottom_circle_y && upper_axe_y > upper_circle_y) && (l_circle_x <= r_axe_x && l_circle_x > l_axe_x);
        collision_with_upper_r_edge = (upper_axe_y <= bottom_circle_y && upper_axe_y > upper_circle_y) && (r_circle_x >= l_axe_x && r_circle_x < r_axe_x);

        collision_with_axe = collision_with_bottom_l_edge || collision_with_bottom_r_edge || collision_with_upper_l_edge || collision_with_upper_r_edge;

        if (collision_with_axe)
        {
            DrawText("Game over!", 400, 200, 20, RED);
        }
        else
        {

            // Game logic begin

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            axe_y += direction;
            if (axe_y > height || axe_y < 0)
            {
                direction = -direction;
            }
            if (IsKeyDown(KEY_D) && circle_x < width - 30)
            {
                circle_x += 10;
            }

            if (IsKeyDown(KEY_A) && circle_x > 30)
            {
                circle_x -= 10;
            }

            // Update edges
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            upper_circle_y = circle_y - circle_radius;
            bottom_circle_y = circle_y + circle_radius;

            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            upper_axe_y = axe_y;
            bottom_axe_y = axe_y + axe_length;

            // Game logic end
        }

        EndDrawing();
    }

    return 0;
}