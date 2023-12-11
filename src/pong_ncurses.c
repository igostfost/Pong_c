#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int key(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
        int bollspeedx, int bollspeedy, int q);

void printfild(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
            int bollspeedx, int bollspeedy, int q);

void core(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
          int bollspeedx, int bollspeedy, int q);

int main() {
    int i = 0, j = 0;
    int pozition1 = 12, pozition2 = 12;
    int score1 = 0, score2 = 0;
    int bollposy = 11, bollposx = 2;
    int bollspeedy = 1, bollspeedx = 1;
    int q = 0, quit = 0;
    int start = 0;

    printf("\033[0d\033[2J");
    printf(
        "-----------------------------------------------------------------------"
        "-----------\n");
    printf("\n                                   PONG GAME - iGOSTFOST\n\n");
    printf(
        "-----------------------------------------------------------------------"
        "----------- \n");
    printf("ЭТА ИГРА ИММИТИРУЕТ ЗНАМЕНИТУЮ ИГРУ ПИНГ ПОНГ\n");
    printf("УПРАВЛЕНИЕ: \n'A' 'Z' ракетка левого игрока (А - выше, Z - ниже) \n'K' 'M' ракетка правого игрока (K - выше, M - ниже)\n");
    printf("Для выхода нажмите 'Q'\n");
    printf("Игра длится до 12 очков\n");
    printf("КОМАНДЫ:\n");
    printf("\033[1;32m");
    printf("1 - ЗАПУСК ИГРЫ\n");
    printf("\033[1;31m");
    printf("0 - ВЫХОД\n");
    printf("\033[0m");
    scanf("%d",&start);
    if(start == 1)
    {
    printf("\033[0d\033[2J");
    initscr();
    nodelay(stdscr, TRUE);
    quit = key(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
    nodelay(stdscr, FALSE);
    refresh();
    endwin();
    printf(
        "-----------------------------------------------------------------------"
        "-----------\n");
    printf("\033[1;32m");
    printf("\n                                ПОБЕДИЛА ДРУЖБА!\n\n");
    printf("\033[0m");
    printf(
        "-----------------------------------------------------------------------"
        "----------- \n");
    }
    return 0;
}

// функция управления ракетками, подключена библиотека ncurses, которая позволяет пользователю не нажимать ENTER
int key(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
        int bollspeedx, int bollspeedy, int q) {
    //start_color();
    //init_pair(1, COLOR_GREEN, COLOR_BLACK);
    //attron(COLOR_PAIR(1));
    char key = getch();
    if (key == 'A' || key == 'a') {
        if (pozition1 >= 1) pozition1 = pozition1 - 2;;
    } else if (key == 'Z' || key == 'z') {
        if (pozition1 <= 23) pozition1 = pozition1 + 2;
    } else if (key == 'M' || key == 'm') {
        if (pozition2 <= 23) pozition2 = pozition2 + 2;
    } else if (key == 'K' || key == 'k') {
        if (pozition2 >= 1) pozition2 = pozition2 - 2;
    } else if (key == 'Q' || key == 'q') {
        q = 1;
        return q;
    } else if (q == 2) {
        return q;
    } else if (q == 3) {
        return q;
    }
    core(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
    return q;
}

// Функция вывода поля, так как по заданию нельзя использовать массивы, реализована циклами и ncurses выводом
void printfild(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
            int bollspeedx, int bollspeedy, int q) {
    clear();
    usleep(50000);
    printw("\nSCORE:                   PLAYER 1 : %2d  || %2d : PLAYER 2\n", score1, score2);
    printw(
        "-----------------------------------------------------------------------"
        "-----------\n");

    for (i = 0; i < 25; i++) {
        printw("|");
        for (j = 0; j < 80; j++) {
            if ((i == pozition1 && j == 0) || (i == pozition1 + 1 && j == 0) ||
                (i == pozition1 - 1 && j == 0))
                printw("|");
            else if ((i == pozition2 && j == 79) || (i == pozition2 + 1 && j == 79) ||
                     (i == pozition2 - 1 && j == 79))
                printw("|");
            else if (i == bollposy && j == bollposx)
                printw("@");
            else if (j == 39)
                printw(":");
            else if (j == 40)
                printw(":");
            else {
                printw(" ");
            }
        }

        printw("|\n");
    }
    printw(
        "-----------------------------------------------------------------------"
        "-----------\n");
    attroff(COLOR_PAIR(1));
    refresh();
    key(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
}

// Функция ядра игры, тут описана логика поведения мяча и начисления счета.
void core(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
          int bollspeedx, int bollspeedy, int q) {
    if (bollposy == 0)
        bollspeedy *= -1;
    else if (bollposy == 24)
        bollspeedy *= -1;
    else if (bollposx == 1 &&
             (bollposy == pozition1 || bollposy == pozition1 + 1 || bollposy == pozition1 - 1))
        bollspeedx *= -1;
    else if (bollposx == 78 &&
             (bollposy == pozition2 || bollposy == pozition2 + 1 || bollposy == pozition2 - 1))
        bollspeedx *= -1;

    bollposx += bollspeedx;
    bollposy += bollspeedy;

    if (bollposx == 0) {
        bollposx = 1;
        bollposy = pozition1;
        score2 += 1;
    } else if (bollposx == 80) {
        bollposx = 78;
        bollposy = pozition2;
        score1 += 1;
    } else if (score2 == 12)
        q = 3;
    else if (score1 == 12)
        q = 2;

    printfild(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
}