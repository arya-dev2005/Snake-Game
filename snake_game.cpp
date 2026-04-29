// ============================================================
//  PREMIUM SNAKE GAME — Console C++
//  Uses: arrays, loops, functions, conio.h, windows.h
// ============================================================

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---------------- CONFIG ----------------
const int WIDTH = 50;
const int HEIGHT = 20;
const int MAX_LENGTH = WIDTH * HEIGHT;
const int SPEED_MS = 115;

enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

bool gameOver;
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int snakeLength;
int foodX, foodY;
int score;
Direction dir;

// ---------------- CONSOLE UTILITIES ----------------
void gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(h, &info);
}

// ---------------- PREMIUM HEADER ----------------
void printHeader()
{
    setColor(10);
    cout << "  ============================================================\n";
    cout << "   ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗\n";
    cout << "   ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝\n";
    cout << "   ███████╗██╔██╗ ██║███████║█████╔╝ █████╗  \n";
    cout << "   ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  \n";
    cout << "   ███████║██║ ╚████║██║  ██║██║  ██╗███████╗\n";
    cout << "   ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝\n";
    cout << "\n";
    cout << "    ██████╗  █████╗ ███╗   ███╗███████╗\n";
    cout << "   ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
    cout << "   ██║  ███╗███████║██╔████╔██║█████╗  \n";
    cout << "   ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n";
    cout << "   ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
    cout << "    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n";
    cout << "  ============================================================\n";
    setColor(7);
}

// ---------------- FOOD ----------------
void placeFood()
{
    bool invalid = true;

    while (invalid)
    {
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        invalid = false;

        for (int i = 0; i < snakeLength; i++)
        {
            if (snakeX[i] == foodX && snakeY[i] == foodY)
            {
                invalid = true;
                break;
            }
        }
    }
}

// ---------------- SETUP ----------------
void setup()
{
    gameOver = false;
    dir = STOP;
    score = 0;
    snakeLength = 4;

    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;

    for (int i = 1; i < snakeLength; i++)
    {
        snakeX[i] = snakeX[0] - i;
        snakeY[i] = snakeY[0];
    }

    placeFood();
}

// ---------------- START SCREEN ----------------
void showStartScreen()
{
    system("cls");
    printHeader();

    setColor(11);
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    cout << "  ║                 PREMIUM CONSOLE EDITION                  ║\n";
    cout << "  ╠══════════════════════════════════════════════════════════╣\n";
    cout << "  ║  Objective : Eat food, grow longer, avoid collisions     ║\n";
    cout << "  ║  Controls  : W A S D  or  Arrow Keys                     ║\n";
    cout << "  ║  Quit      : Q                                           ║\n";
    cout << "  ╠══════════════════════════════════════════════════════════╣\n";
    cout << "  ║              Press any key to start the game             ║\n";
    cout << "  ╚══════════════════════════════════════════════════════════╝\n";
    setColor(7);

    _getch();
    system("cls");
}

// ---------------- DRAW GAME ----------------
void draw()
{
    gotoxy(0, 0);

    setColor(11);

    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║                  SNAKE GAME                          ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n";
    cout << "  ║  Objective : Eat food, grow longer, avoid collisions ║\n";
    cout << "  ╠══════════════════════════════════════════════════════╣\n  ║";
    setColor(14);
    cout << " SCORE: ";

    cout.width(5);
    cout << left << score;

    cout << " LENGTH: ";
    cout.width(5);
    cout << left << snakeLength;

    cout << " MOVE: W/A/S/D    QUIT: Q " << " ";
    setColor(11);
    cout << "║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n";
    setColor(7);

    cout << "  ╔";
    for (int i = 0; i < WIDTH; i++) cout << "═";
    cout << "╗\n";

    for (int y = 0; y < HEIGHT; y++)
    {
        cout << "  ║";

        for (int x = 0; x < WIDTH; x++)
        {
            bool printed = false;

            if (x == snakeX[0] && y == snakeY[0])
            {
                setColor(10);
                cout << "O";
                setColor(7);
                printed = true;
            }

            if (!printed)
            {
                for (int i = 1; i < snakeLength; i++)
                {
                    if (x == snakeX[i] && y == snakeY[i])
                    {
                        setColor(10);
                        cout << "o";
                        setColor(7);
                        printed = true;
                        break;
                    }
                }
            }

            if (!printed && x == foodX && y == foodY)
            {
                setColor(12);
                cout << "*";
                setColor(7);
                printed = true;
            }

            if (!printed) cout << " ";
        }

        cout << "║\n";
    }

    cout << "  ╚";
    for (int i = 0; i < WIDTH; i++) cout << "═";
    cout << "╝\n";

    cout << "    Tip: Instant reverse movement is blocked.  \n";
}


// ---------------- INPUT ----------------
void handleInput()
{
    if (!_kbhit()) return;

    int key = _getch();

    if (key == 0 || key == 224)
    {
        key = _getch();

        switch (key)
        {
            case 72: if (dir != DOWN)  dir = UP;    break;
            case 80: if (dir != UP)    dir = DOWN;  break;
            case 75: if (dir != RIGHT) dir = LEFT;  break;
            case 77: if (dir != LEFT)  dir = RIGHT; break;
        }
    }
    else
    {
        switch (key)
        {
            case 'w': case 'W': if (dir != DOWN)  dir = UP;    break;
            case 's': case 'S': if (dir != UP)    dir = DOWN;  break;
            case 'a': case 'A': if (dir != RIGHT) dir = LEFT;  break;
            case 'd': case 'D': if (dir != LEFT)  dir = RIGHT; break;
            case 'q': case 'Q': gameOver = true;               break;
        }
    }
}

// ---------------- UPDATE LOGIC ----------------
void update()
{
    if (dir == STOP) return;

    for (int i = snakeLength - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    switch (dir)
    {
        case UP:    snakeY[0]--; break;
        case DOWN:  snakeY[0]++; break;
        case LEFT:  snakeX[0]--; break;
        case RIGHT: snakeX[0]++; break;
        default: break;
    }

    if (snakeX[0] < 0 || snakeX[0] >= WIDTH ||
        snakeY[0] < 0 || snakeY[0] >= HEIGHT)
    {
        gameOver = true;
        return;
    }

    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameOver = true;
            return;
        }
    }

    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
        score += 10;

        if (snakeLength < MAX_LENGTH)
            snakeLength++;

        placeFood();
    }
}

// ---------------- GAME OVER ----------------
void showGameOver()
{
    system("cls");
    printHeader();

    const int BOX_WIDTH = 58; // total inner width

    setColor(12);

    cout << "\n";

    // Top border
    cout << "  ╔";
    for(int i = 0; i < BOX_WIDTH; i++) cout << "═";
    cout << "╗\n";

    // Title
    string title = "GAME OVER";
    int padding = (BOX_WIDTH - title.length()) / 2;

    cout << "  ║";
    for(int i = 0; i < padding; i++) cout << " ";
    cout << title;
    for(int i = 0; i < BOX_WIDTH - padding - title.length(); i++) cout << " ";
    cout << "║\n";

    // Divider
    cout << "  ╠";
    for(int i = 0; i < BOX_WIDTH; i++) cout << "═";
    cout << "╣\n";

    // Score line
    string scoreLine = "Final Score : " + to_string(score);
    cout << "  ║ " << scoreLine;
    for(int i = 0; i < BOX_WIDTH - scoreLine.length() - 1; i++) cout << " ";
    cout << "║\n";

    // Length line
    string lenLine = "Snake Length : " + to_string(snakeLength);
    cout << "  ║ " << lenLine;
    for(int i = 0; i < BOX_WIDTH - lenLine.length() - 1; i++) cout << " ";
    cout << "║\n";

    // Divider
    cout << "  ╠";
    for(int i = 0; i < BOX_WIDTH; i++) cout << "═";
    cout << "╣\n";

    // Controls
    string control = "[R] Restart        [Q] Quit";
    padding = (BOX_WIDTH - control.length()) / 2;

    cout << "  ║";
    for(int i = 0; i < padding; i++) cout << " ";
    cout << control;
    for(int i = 0; i < BOX_WIDTH - padding - control.length(); i++) cout << " ";
    cout << "║\n";

    // Bottom border
    cout << "  ╚";
    for(int i = 0; i < BOX_WIDTH; i++) cout << "═";
    cout << "╝\n";

    setColor(7);
}

// ---------------- MAIN ----------------
int main()
{
    srand((unsigned)time(0));
    hideCursor();
    showStartScreen();

    bool running = true;

    while (running)
    {
        setup();

        while (!gameOver)
        {
            handleInput();
            update();
            draw();
            Sleep(SPEED_MS);
        }

        showGameOver();

        while (true)
        {
            char ch = _getch();

            if (ch == 'r' || ch == 'R')
            {
                system("cls");
                break;
            }

            if (ch == 'q' || ch == 'Q')
            {
                running = false;
                break;
            }
        }
    }

    system("cls");
    setColor(10);
    cout << "\n  Thanks for playing Snake Game!\n\n";
    setColor(7);

    return 0;
}