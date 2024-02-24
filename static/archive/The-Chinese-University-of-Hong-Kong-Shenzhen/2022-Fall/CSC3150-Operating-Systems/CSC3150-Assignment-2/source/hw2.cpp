#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>

#define ROW 10
#define COLUMN 50

int exit_status = -1;

int logs_start[ROW], logs_end[ROW], logs_speed[ROW];

pthread_mutex_t mutex;
pthread_cond_t logs_signal[ROW];

struct Node {
        int x, y;
        Node(int _x, int _y) : x(_x), y(_y){};
        Node(){};
} frog;

char map[ROW + 10][COLUMN];

// Determine a keyboard is hit or not. If yes, return 1. If not, return 0.
int kbhit(void)
{
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);

        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch != EOF) {
                ungetc(ch, stdin);
                return 1;
        }
        return 0;
}

int shift(int pos, int delta)
{
        return (pos + delta + COLUMN - 1) % (COLUMN - 1);
}

void swap(int &x, int &y)
{
        int tmp = x;
        x = y;
        y = tmp;
        return;
}

void swap(char &x, char &y)
{
        char tmp = x;
        x = y;
        y = tmp;
        return;
}

void *logs_move(void *t)
{
        int cur_row = *((int *)(&t));

        while (exit_status == -1) {
                pthread_mutex_lock(&mutex);
                // pthread_cond_wait(&logs_signal[cur_row], &mutex);

                /*  Move the logs  */
                // odd row: log moves from right to left
                // even row: log moves from left to right
                int dx[] = { 1, -1 };

                logs_start[cur_row] =
                        shift(logs_start[cur_row], dx[cur_row % 2]);
                logs_end[cur_row] = shift(logs_end[cur_row], dx[cur_row % 2]);

                /*  Check keyboard hits, to change frog's position or quit the game. */
                char keyboard_input = 0;
                if (kbhit() == 1) {
                        keyboard_input = getchar();
                }

                int x, y, frog_dx = 0, frog_dy = 0;
                int logs_dx[] = { 1, -1 };
                if (keyboard_input == 'w' || keyboard_input == 'W') {
                        frog_dx = -1;
                } else if (keyboard_input == 'a' || keyboard_input == 'A') {
                        frog_dy = -1;
                } else if (keyboard_input == 's' || keyboard_input == 'S') {
                        frog_dx = 1;
                } else if (keyboard_input == 'd' || keyboard_input == 'D') {
                        frog_dy = 1;
                } else if (keyboard_input == 'q' || keyboard_input == 'Q') {
                        exit_status = 2;
                }

                x = frog.x + frog_dx;
                y = frog.y + frog_dy;
                if (x > ROW)
                        x = ROW;
                if (y + logs_dx[x % 2] < 0 || y + logs_dx[x % 2] >= COLUMN)
                        exit_status = 1;
                if (x == 0)
                        exit_status = 0;

                for (int j = 0; j < COLUMN - 1; ++j) {
                        map[0][j] = '|';
                        map[ROW][j] = '|';
                }
                for (int j = logs_start[cur_row]; j != logs_end[cur_row];
                     j = shift(j, dx[cur_row % 2])) {
                        map[cur_row][j] = '=';
                }
                for (int j = logs_end[cur_row]; j != logs_start[cur_row];
                     j = shift(j, dx[cur_row % 2])) {
                        map[cur_row][j] = ' ';
                }
                // map[cur_row][logs_start[cur_row]] = ' ';

                swap(frog.x, x);
                swap(frog.y, y);

                if (frog.x == 10) {
                } else if (frog.x == cur_row &&
                           map[frog.x][frog.y + logs_dx[frog.x % 2]] != ' ') {
                        frog.y += logs_dx[frog.x % 2];
                } else if (frog.x == cur_row) {
                        exit_status = 1;
                }

                map[frog.x][frog.y] = (char)('0');

                /*  Check game's status  */
                if (exit_status != -1) {
                        if(exit_status == 0){
                                map[frog.x + 1][frog.y] = '=';
                        }
                        break;
                }

                /*  Print the map on the screen  */
                printf("\033[2J\033[H");
                for (int i = 0; i <= ROW; ++i) {
                        puts(map[i]);
                }

                pthread_mutex_unlock(&mutex);

                usleep(logs_speed[cur_row]);
        }

        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
        srand(time(NULL));
        pthread_mutex_init(&mutex, NULL);

        // Initialize the river map and frog's starting position
        memset(map, 0, sizeof(map));
        int i, j;
        for (i = 1; i < ROW; ++i) {
                for (j = 0; j < COLUMN - 1; ++j)
                        map[i][j] = ' ';
        }

        for (i = 1; i < ROW; ++i) {
                logs_start[i] = rand() % (COLUMN - 1);
                logs_end[i] = (logs_start[i] + (rand() % 8 + 8)) % (COLUMN - 1);
                if (i % 2 == 1) {
                        swap(logs_start[i], logs_end[i]);
                }
                logs_speed[i] = (rand() % 18 + 12) * 6000;
        }

        for (j = 0; j < COLUMN - 1; ++j)
                map[ROW][j] = map[0][j] = '|';

        for (j = 0; j < COLUMN - 1; ++j)
                map[0][j] = map[0][j] = '|';

        frog = Node(ROW, (COLUMN - 1) / 2);
        map[frog.x][frog.y] = '0';

        //Print the map into screen
        for (i = 0; i <= ROW; ++i)
                puts(map[i]);

        /*  Create pthreads for wood move and frog control.  */
        pthread_t logs_t[ROW - 1];
        for (int i = 0; i < ROW - 1; ++i) {
                int rc = pthread_create(&logs_t[i], NULL, logs_move,
                                        (void *)(i + 1));
                // printf("-> %d\n", rc);
        }
        for (int i = 0; i < ROW - 1; ++i) {
                pthread_join(logs_t[i], NULL);
        }
        /*  Display the output for user: win, lose or quit.  */
        const char msg[3][32] = { "win", "lose", "quit" };
        printf("\033[2J\033[H");
        for (int i = 0; i <= ROW; ++i) {
                puts(map[i]);
        }
        printf("%s\n", msg[exit_status]);

        pthread_exit(NULL);

        return 0;
}