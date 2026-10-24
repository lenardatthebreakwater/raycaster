#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

#define TOTALROWS 12
#define TOTALCOLS 16

#define CELLSIZE 50

#define TURNSPEED 2
#define SPEED 5

typedef struct Player {
    int x;
    int y;
    float radius;
    double angle;
} Player;

double castRay(Player* player, int map[TOTALROWS][TOTALCOLS]);

int main(void) {
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Raycaster");
    SetTargetFPS(60);
    
    int map[TOTALROWS][TOTALCOLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    Player player = {
        .x = (SCREENWIDTH / 2) - ((CELLSIZE / 2) / 2),
        .y = (SCREENHEIGHT / 2) - ((CELLSIZE / 2) / 2),
        .radius = (float)((CELLSIZE / 2) / 2),
        .angle = 0
    };

    while (!WindowShouldClose()) {
        double distance = castRay(&player, map);
        printf("%f\n", distance);

        if (IsKeyDown(KEY_LEFT)) {
            player.angle -= TURNSPEED;         
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player.angle += TURNSPEED;       
        }
        if (IsKeyDown(KEY_UP)) {
            player.x += (SPEED * cosf(player.angle * DEG2RAD));
            player.y += (SPEED * sinf(player.angle * DEG2RAD));
        }

        if (player.angle < 0) {
            player.angle += 360;
        }
        if (player.angle >= 360) {
            player.angle -= 360;
        } 

        BeginDrawing();
        ClearBackground(BLACK);

        for (int row = 0; row < TOTALROWS; row++) {
            for (int col = 0; col < TOTALCOLS; col++) {
                if (map[row][col] == 1) { 
                    DrawRectangle(col * CELLSIZE, row * CELLSIZE, CELLSIZE - 1, CELLSIZE - 1, RAYWHITE);
                }                
            }
        }

        DrawCircle(player.x, player.y, player.radius, RAYWHITE);

        DrawLine(player.x, player.y, player.x + (int)(cosf(player.angle * DEG2RAD) * distance), player.y + (int)(sinf(player.angle * DEG2RAD) * distance), RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

double castRay(Player* player, int map[TOTALROWS][TOTALCOLS]) {
    double total_x = player->x;
    double total_y = player->y;

    while (true) {
        total_x += (1 * cosf(player->angle * DEG2RAD));
        total_y += (1 * sinf(player->angle * DEG2RAD));

        if (map[(int)total_y / CELLSIZE][(int)total_x / CELLSIZE] == 1) {
            double dx = total_x - player->x;
            double dy = total_y - player->y;

            return sqrt((dx * dx) + (dy * dy));
        }
    }
}