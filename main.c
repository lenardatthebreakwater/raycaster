#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define TOTALROWS 16
#define TOTALCOLS 12

#define CELLSIZE 50

#define TURNSPEED 2
#define SPEED 5

typedef struct Player {
    int x;
    int y;
    float radius;
    double angle;
} Player;

int main(void) {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Raycaster");
    SetTargetFPS(60);
    
    int map[TOTALROWS][TOTALCOLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    Player player = {
        .x = (SCREENWIDTH / 2) - ((CELLSIZE / 2) / 2),
        .y = (SCREENHEIGHT / 2) - ((CELLSIZE / 2) / 2),
        .radius = (float)((CELLSIZE / 2) / 2),
        .angle = 0
    };

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT)) {
            player.angle += TURNSPEED;
            if (player.angle == 360) {
                player.angle = 0;
            }
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player.angle -= TURNSPEED;
            if (player.angle == 0) {
                player.angle = 360;
            }
        }
        if (IsKeyDown(KEY_UP)) {
            player.x += (SPEED * cosf(player.angle));
            player.y += (SPEED * sinf(player.angle));
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int row = 0; row < TOTALROWS; row++) {
            for (int col = 0; col < TOTALCOLS; col++) {
                if (map[row][col] == 1) { 
                    DrawRectangle(row * CELLSIZE, col * CELLSIZE, CELLSIZE - 1, CELLSIZE - 1, RAYWHITE);
                }                
            }
        }

        DrawCircle(player.x, player.y, player.radius, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

