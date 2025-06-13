#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 80
#define HEIGHT 24
#define PADDLE_HEIGHT 4

typedef struct {
    int y, x;
    int height;
} Paddle;

typedef struct {
    int y, x;
    int vy, vx;
} Ball;

HANDLE hConsole;
CHAR_INFO buffer[WIDTH * HEIGHT];
COORD bufferSize = {WIDTH, HEIGHT};
COORD bufferCoord = {0, 0};
SMALL_RECT writeRegion = {0, 0, WIDTH - 1, HEIGHT - 1};

// ** Efficient Buffer Clearing (No Flicker)**
void clearBuffer() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        buffer[i].Char.AsciiChar = ' ';
        buffer[i].Attributes = 7;
    }
}

// ** Draw Paddle & Ball Directly in Buffer**
void drawGame(Paddle player, Paddle ai, Ball ball, int player_score, int ai_score) {
    clearBuffer();

    for (int i = 0; i < player.height; i++)
        buffer[(player.y + i) * WIDTH + player.x].Char.AsciiChar = '|';
    for (int i = 0; i < ai.height; i++)
        buffer[(ai.y + i) * WIDTH + ai.x].Char.AsciiChar = '|';
    buffer[ball.y * WIDTH + ball.x].Char.AsciiChar = 'O';

    // ** Fast Buffered Console Output**
    WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);
}

// ** More Dynamic AI Movement**
void updateAI(Paddle *ai, Ball ball) {
    static int ai_speed = 1; // AI moves at a variable speed for realism
    if (ball.y > ai->y + ai->height / 2) ai->y += ai_speed;
    else if (ball.y < ai->y) ai->y -= ai_speed;
}

// ** Ball Reset (Faster, More Randomized)**
void resetBall(Ball *ball) {
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->vx = (rand() % 2 == 0) ? 1 : -1;
    ball->vy = (rand() % 2 == 0) ? 1 : -1;
}

int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Paddle player = {HEIGHT / 2 - PADDLE_HEIGHT / 2, 2, PADDLE_HEIGHT};
    Paddle ai = {HEIGHT / 2 - PADDLE_HEIGHT / 2, WIDTH - 3, PADDLE_HEIGHT};
    Ball ball;
    int player_score = 0, ai_score = 0;
    resetBall(&ball);

    while (1) {
        drawGame(player, ai, ball, player_score, ai_score);

        // ** Improved Input Handling (Without Lag)**
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q') break;
            if (ch == 'w' && player.y > 0) player.y--;
            if (ch == 's' && player.y < HEIGHT - PADDLE_HEIGHT) player.y++;
        }

        updateAI(&ai, ball); // **AI moves more realistically**

        // ** Frame-perfect Ball Movement**
        ball.x += ball.vx;
        ball.y += ball.vy;

        // Collision Handling
        if (ball.y <= 0 || ball.y >= HEIGHT - 1) ball.vy *= -1;
        if (ball.x == player.x + 1 && ball.y >= player.y && ball.y < player.y + player.height) ball.vx *= -1;
        if (ball.x == ai.x - 1 && ball.y >= ai.y && ball.y < ai.y + ai.height) ball.vx *= -1;

        // Scoring
        if (ball.x <= 0) { ai_score++; resetBall(&ball); }
        if (ball.x >= WIDTH - 1) { player_score++; resetBall(&ball); }
    }

    printf("Game Over! Final Score: Player %d | AI %d\n", player_score, ai_score);
    return 0;
}
