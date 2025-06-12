#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

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

void draw_paddle(Paddle *paddle) {
    for (int i = 0; i < paddle->height; ++i)
        mvprintw(paddle->y + i, paddle->x, "|");
}

void erase_paddle(Paddle *paddle) {
    for (int i = 0; i < paddle->height; ++i)
        mvprintw(paddle->y + i, paddle->x, " ");
}

void draw_ball(Ball *ball) {
    mvprintw(ball->y, ball->x, "O");
}

void erase_ball(Ball *ball) {
    mvprintw(ball->y, ball->x, " ");
}

void reset_ball(Ball *ball) {
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->vx = (rand() % 2 == 0) ? 1 : -1;
    ball->vy = (rand() % 2 == 0) ? 1 : -1;
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);

    Paddle player = {HEIGHT / 2 - PADDLE_HEIGHT / 2, 2, PADDLE_HEIGHT};
    Paddle ai = {HEIGHT / 2 - PADDLE_HEIGHT / 2, WIDTH - 3, PADDLE_HEIGHT};
    Ball ball;
    int player_score = 0, ai_score = 0;
    reset_ball(&ball);

    while (1) {
        clear();
        mvprintw(0, WIDTH/2 - 9, "PONG - q to quit");
        mvprintw(1, WIDTH/2 - 10, "Player: %d   AI: %d", player_score, ai_score);
        draw_paddle(&player);
        draw_paddle(&ai);
        draw_ball(&ball);
        refresh();

        // Input
        int ch = getch();
        if (ch == 'q') break;
        if (ch == KEY_UP && player.y > 1) player.y--;
        if (ch == KEY_DOWN && player.y < HEIGHT - PADDLE_HEIGHT - 1) player.y++;

        // AI movement
        if (ball.y < ai.y) ai.y--;
        else if (ball.y > ai.y + ai.height - 1) ai.y++;
        if (ai.y < 1) ai.y = 1;
        if (ai.y > HEIGHT - PADDLE_HEIGHT - 1) ai.y = HEIGHT - PADDLE_HEIGHT - 1;

        // Erase ball for next frame
        erase_ball(&ball);

        // Update ball
        ball.x += ball.vx;
        ball.y += ball.vy;

        // Collision: Top/bottom
        if (ball.y <= 1 || ball.y >= HEIGHT - 2) {
            ball.vy = -ball.vy;
        }

        // Collision: Left paddle
        if (ball.x == player.x + 1 && ball.y >= player.y && ball.y < player.y + player.height) {
            ball.vx = -ball.vx;
        }

        // Collision: Right paddle
        if (ball.x == ai.x - 1 && ball.y >= ai.y && ball.y < ai.y + ai.height) {
            ball.vx = -ball.vx;
        }

        // Score
        if (ball.x <= 0) {
            ai_score++;
            reset_ball(&ball);
        }
        if (ball.x >= WIDTH-1) {
            player_score++;
            reset_ball(&ball);
        }

        usleep(30000); // ~33fps
    }

    endwin();
    return 0;
}
