// ============================================================
//  SNAKE GAME — Console C++
//  Headers: <conio.h>, <windows.h>, standard C++ only
//  Concepts: arrays, loops, direction handling, collision detection
// ============================================================

#include <iostream>   // cout, cin
#include <conio.h>    // _kbhit(), _getch() — non-blocking keyboard input
#include <windows.h>  // Sleep(), system("cls"), COORD, SetConsoleCursorPosition
#include <cstdlib>    // rand(), srand()
#include <ctime>      // time() — seed for random food placement

using namespace std;

// ─────────────────────────────────────────────
//  SECTION 1: CONSTANTS & CONFIGURATION
//  Centralise all magic numbers here so the
//  game is easy to tune without hunting code.
// ─────────────────────────────────────────────
const int WIDTH      = 40;   // Board columns (playfield cells)
const int HEIGHT     = 20;   // Board rows    (playfield cells)
const int MAX_LENGTH = WIDTH * HEIGHT; // Absolute max snake size
const int SPEED_MS   = 150;  // Milliseconds between frames (lower = faster)

// ─────────────────────────────────────────────
//  SECTION 2: DIRECTION ENUM
//  Using an enum prevents accidental integer
//  mix-ups and makes direction logic readable.
// ─────────────────────────────────────────────
enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

// ─────────────────────────────────────────────
//  SECTION 3: GLOBAL GAME STATE
//  All state is kept in plain arrays + scalars
//  — no STL containers, no classes.
// ─────────────────────────────────────────────
bool gameOver;

// Snake body stored as two parallel arrays of (x, y) coordinates.
// snakeX[0], snakeY[0] is always the HEAD.
int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int snakeLength;          // How many body segments currently exist

int foodX, foodY;         // Food position
int score;
Direction dir;            // Current movement direction

// ─────────────────────────────────────────────
//  SECTION 4: UTILITY — HIDE CURSOR
//  The blinking cursor looks ugly during
//  frame-by-frame rendering. We hide it once.
// ─────────────────────────────────────────────
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize   = 100;
    info.bVisible = FALSE;          // Hide the cursor
    SetConsoleCursorInfo(consoleHandle, &info);
}

// ─────────────────────────────────────────────
//  SECTION 5: UTILITY — MOVE CURSOR TO (x, y)
//  Instead of clearing the whole screen each
//  frame (which causes flicker), we reposition
//  the cursor to the top-left and redraw.
//  This is much smoother than system("cls").
// ─────────────────────────────────────────────
void gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ─────────────────────────────────────────────
//  SECTION 6: SETUP — INITIALISE GAME STATE
//  Called once at start and again on restart.
// ─────────────────────────────────────────────
void setup()
{
    gameOver   = false;
    dir        = STOP;
    score      = 0;
    snakeLength = 3;          // Snake starts with 3 segments

    // Place the head in the middle of the board
    snakeX[0] = WIDTH  / 2;
    snakeY[0] = HEIGHT / 2;

    // Body segments start directly to the left of the head
    for (int i = 1; i < snakeLength; i++)
    {
        snakeX[i] = snakeX[0] - i;  // Each segment one cell behind
        snakeY[i] = snakeY[0];
    }

    // Seed random and place first food
    srand((unsigned)time(0));
    foodX = rand() % (WIDTH  - 2) + 1;   // Keep food inside borders
    foodY = rand() % (HEIGHT - 2) + 1;
}

// ─────────────────────────────────────────────
//  SECTION 7: PLACE NEW FOOD
//  Regenerates food at a random cell that is
//  NOT currently occupied by any snake segment.
// ─────────────────────────────────────────────
void placeFood()
{
    bool onSnake = true;
    while (onSnake)
    {
        foodX = rand() % (WIDTH  - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;

        onSnake = false;
        // Check every body segment
        for (int i = 0; i < snakeLength; i++)
        {
            if (snakeX[i] == foodX && snakeY[i] == foodY)
            {
                onSnake = true;   // Collision → retry
                break;
            }
        }
    }
}

// ─────────────────────────────────────────────
//  SECTION 8: DRAW — RENDER THE BOARD
//  We build the frame by scanning every cell
//  (row by row) and printing the right symbol.
//  gotoxy(0,0) resets the cursor so we redraw
//  in-place without flicker.
// ─────────────────────────────────────────────
void draw()
{
    gotoxy(0, 0);   // Jump cursor to top-left; no screen clear needed

    // ── Top border ──────────────────────────────────────────
    cout << "\xC9";                            // ╔
    for (int x = 0; x < WIDTH; x++) cout << "\xCD";  // ═
    cout << "\xBB" << "\n";                    // ╗

    // ── Rows ────────────────────────────────────────────────
    for (int y = 0; y < HEIGHT; y++)
    {
        cout << "\xBA";   // ║  left wall

        for (int x = 0; x < WIDTH; x++)
        {
            bool printed = false;

            // Head check (segment 0)
            if (x == snakeX[0] && y == snakeY[0])
            {
                // Direction-aware head symbol
                switch (dir)
                {
                    case UP:    cout << "\x1e"; break;  // ▲
                    case DOWN:  cout << "\x1f"; break;  // ▼
                    case LEFT:  cout << "\x11"; break;  // ◄
                    case RIGHT: cout << "\x10"; break;  // ►
                    default:    cout << "O";    break;
                }
                printed = true;
            }

            // Body segments (index 1 onward)
            if (!printed)
            {
                for (int i = 1; i < snakeLength; i++)
                {
                    if (x == snakeX[i] && y == snakeY[i])
                    {
                        cout << "\xFE";   // ■  body block
                        printed = true;
                        break;
                    }
                }
            }

            // Food
            if (!printed && x == foodX && y == foodY)
            {
                cout << "\x04";   // ♦  food symbol
                printed = true;
            }

            // Empty cell
            if (!printed) cout << " ";
        }

        cout << "\xBA" << "\n";   // ║  right wall
    }

    // ── Bottom border ───────────────────────────────────────
    cout << "\xC8";                            // ╚
    for (int x = 0; x < WIDTH; x++) cout << "\xCD";  // ═
    cout << "\xBC" << "\n";                    // ╝

    // ── HUD ─────────────────────────────────────────────────
    cout << "  Score: " << score
         << "   Length: " << snakeLength
         << "   [W/A/S/D or arrow keys]   " << "\n";
}

// ─────────────────────────────────────────────
//  SECTION 9: INPUT — HANDLE KEYBOARD
//  _kbhit() returns non-zero if a key is
//  waiting. _getch() reads it WITHOUT waiting.
//  This keeps the game loop non-blocking.
// ─────────────────────────────────────────────
void handleInput()
{
    if (!_kbhit()) return;   // No key pressed this frame → skip

    int key = _getch();

    // Arrow keys send a two-byte sequence: 0xE0 then the code
    if (key == 0xE0 || key == 0)
    {
        key = _getch();      // Read the actual arrow key code
        switch (key)
        {
            case 72: if (dir != DOWN)  dir = UP;    break;  // ↑
            case 80: if (dir != UP)    dir = DOWN;  break;  // ↓
            case 75: if (dir != RIGHT) dir = LEFT;  break;  // ←
            case 77: if (dir != LEFT)  dir = RIGHT; break;  // →
        }
    }
    else
    {
        // WASD alternative
        switch (key)
        {
            case 'w': case 'W': if (dir != DOWN)  dir = UP;    break;
            case 's': case 'S': if (dir != UP)    dir = DOWN;  break;
            case 'a': case 'A': if (dir != RIGHT) dir = LEFT;  break;
            case 'd': case 'D': if (dir != LEFT)  dir = RIGHT; break;
            case 'q': case 'Q': gameOver = true;               break; // Quit
        }
    }
}

// ─────────────────────────────────────────────
//  SECTION 10: LOGIC — UPDATE GAME STATE
//  This runs every frame and is the core of
//  the game engine.
//
//  Step-by-step what happens each tick:
//   1. Shift body segments backward by one slot
//   2. Move head in the current direction
//   3. Boundary collision → game over
//   4. Self collision   → game over
//   5. Food collision   → grow + new food
// ─────────────────────────────────────────────
void update()
{
    if (dir == STOP) return;   // Don't move until the player presses a key

    // ── Step 1: Shift body ──────────────────────────────────
    // Move each segment to the position of the segment ahead of it.
    // We iterate from the TAIL to segment [1] so we don't overwrite
    // a position before it has been copied forward.
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // ── Step 2: Advance the head ────────────────────────────
    switch (dir)
    {
        case UP:    snakeY[0]--; break;
        case DOWN:  snakeY[0]++; break;
        case LEFT:  snakeX[0]--; break;
        case RIGHT: snakeX[0]++; break;
        default: break;
    }

    // ── Step 3: Boundary collision ──────────────────────────
    // The playfield is bounded by the border walls.
    // Valid head positions: x in [0, WIDTH-1], y in [0, HEIGHT-1]
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH ||
        snakeY[0] < 0 || snakeY[0] >= HEIGHT)
    {
        gameOver = true;
        return;
    }

    // ── Step 4: Self-collision ──────────────────────────────
    // If the head overlaps ANY body segment, it's game over.
    // We skip index 0 (the head itself).
    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameOver = true;
            return;
        }
    }

    // ── Step 5: Food collision ──────────────────────────────
    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
        score += 10;
        snakeLength++;         // Grow: the tail segment stays in place
                               // next frame instead of being overwritten
        placeFood();           // Spawn new food in a safe position
    }
}

// ─────────────────────────────────────────────
//  SECTION 11: GAME OVER SCREEN
// ─────────────────────────────────────────────
void showGameOver()
{
    system("cls");
    cout << "\n\n";
    cout << "  ╔══════════════════════════════╗\n";
    cout << "  ║         GAME  OVER           ║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  Final Score  : " << score      << "║\n";
    cout << "  ║  Snake Length : " << snakeLength << "║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  [R] Restart   [Q] Quit      ║\n";
    cout << "  ╚══════════════════════════════╝\n\n";
}

// ─────────────────────────────────────────────
//  SECTION 12: MAIN — GAME LOOP
//  Classic game-loop structure:
//      Setup → loop { Input → Update → Draw }
//      → Game Over → optional Restart
// ─────────────────────────────────────────────
int main()
{
    hideCursor();
    system("cls");

    bool running = true;

    while (running)
    {
        setup();

        // ── Core game loop ───────────────────────────────────
        while (!gameOver)
        {
            draw();          // 1. Render current state
            handleInput();   // 2. Poll keyboard (non-blocking)
            update();        // 3. Advance game logic
            Sleep(SPEED_MS); // 4. Cap frame rate
        }

        // ── Post-game ────────────────────────────────────────
        showGameOver();

        // Wait for Restart or Quit
        while (true)
        {
            if (_kbhit())
            {
                char ch = (char)_getch();
                if (ch == 'r' || ch == 'R') break;          // Restart
                if (ch == 'q' || ch == 'Q') { running = false; break; }
            }
        }
    }

    system("cls");
    cout << "\n  Thanks for playing! Final score: " << score << "\n\n";
    return 0;
}
