#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // For _kbhit() and _getch()
#include <windows.h>  // For Sleep(), system functions
#include <time.h>  // For high-precision timing

#define WIDTH 80
#define HEIGHT 24
#define PADDLE_HEIGHT 4
#define BALL_SIZE 1

typedef struct {
    int y, x;
    int height;
} Paddle;

typedef struct {
    int y, x;
    int vy, vx;
} Ball;

// Clears the console screen efficiently using cursor repositioning
void clearScreen() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Draw game state using a buffered output approach
void drawGame(Paddle player, Paddle ai, Ball ball, int player_score, int ai_score) {
    clearScreen();
    printf("PONG - Press 'Q' to Quit\n");
    printf("Player: %d   AI: %d\n\n", player_score, ai_score);

    char screenBuffer[HEIGHT][WIDTH];
    memset(screenBuffer, ' ', sizeof(screenBuffer));

    // Draw paddles and ball into buffer
    for (int i = 0; i < player.height; i++)
        screenBuffer[player.y + i][player.x] = '|';
    for (int i = 0; i < ai.height; i++)
        screenBuffer[ai.y + i][ai.x] = '|';
    
    screenBuffer[ball.y][ball.x] = 'O';

    // Print buffer in one optimized step
    for (int y = 0; y < HEIGHT; y++) {
        printf("%.*s\n", WIDTH, screenBuffer[y]);
    }
}

// Resets ball position and direction
void resetBall(Ball *ball) {
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->vx = (rand() % 2 == 0) ? 1 : -1;
    ball->vy = (rand() % 2 == 0) ? 1 : -1;
}

int main() {
    Paddle player = {HEIGHT / 2 - PADDLE_HEIGHT / 2, 2, PADDLE_HEIGHT};
    Paddle ai = {HEIGHT / 2 - PADDLE_HEIGHT / 2, WIDTH - 3, PADDLE_HEIGHT};
    Ball ball;
    int player_score = 0, ai_score = 0;
    resetBall(&ball);

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    while (1) {
        QueryPerformanceCounter(&start);
        drawGame(player, ai, ball, player_score, ai_score);

        // Handle player input (non-blocking key press detection)
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q') break;
            if (ch == 'w' && player.y > 0) player.y--;
            if (ch == 's' && player.y < HEIGHT - PADDLE_HEIGHT) player.y++;
        }

        // AI movement (every frame for better responsiveness)
        if (ball.y < ai.y) ai.y--;
        else if (ball.y > ai.y + ai.height - 1) ai.y++;

        // Update ball position
        ball.x += ball.vx;
        ball.y += ball.vy;

        // Ball collision with top/bottom walls
        if (ball.y <= 0 || ball.y >= HEIGHT - 1)
            ball.vy *= -1;

        // Ball collision with paddles
        if (ball.x == player.x + 1 && ball.y >= player.y && ball.y < player.y + player.height)
            ball.vx = -ball.vx;
        if (ball.x == ai.x - 1 && ball.y >= ai.y && ball.y < ai.y + ai.height)
            ball.vx = -ball.vx;

        // Scoring
        if (ball.x <= 0) {
            ai_score++;
            resetBall(&ball);
        }
        if (ball.x >= WIDTH - 1) {
            player_score++;
            resetBall(&ball);
        }

        // Adaptive frame control using high-resolution timing
        QueryPerformanceCounter(&end);
        double frameTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        Sleep(max(1, (int)(16 - frameTime * 1000)));  // Aim for 60 FPS
    }

    printf("Game Over! Final Score: Player %d | AI %d\n", player_score, ai_score);
    return 0;
}
