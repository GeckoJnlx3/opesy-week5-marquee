#include <iostream>
#include <windows.h> // Windows API
#include <string>
#include <thread>  // For sleep_for
#include <chrono>  // For milliseconds
#include <conio.h>

void displayHeader() {
    std::cout << "*******************************************************" << std::endl;
    std::cout << "         *   Displaying a marquee console!   *" << std::endl;
    std::cout << "*******************************************************" << std::endl;
}

void gotoXY(int x, int y) {
    // Move the cursor to a specified position in the console
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    // Clear the screen by filling it with spaces
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the console with spaces
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) return;

    // Reset the cursor position
    SetConsoleCursorPosition(hConsole, homeCoords);
}

int main() {
    std::string text = "Hello world in marquee!";
    int text_len = text.length();

    // Set up the console window size
    const int width = 100;
    const int height = 15;

    int x = 0, y = 3;
    int x_direction = 1, y_direction = 1;

    // Hide the cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    char c = ' ';

    while (true) {
        clearScreen(); 
        
        gotoXY(0, 0);
        displayHeader();
        
        gotoXY(x, y);
        std::cout << text;

        // Update the position for the next frame
        x += x_direction;
        y += y_direction;

        if (x <= 0 || x + text_len >= width) {
            x_direction *= -1;
        }
        if (y <= 3 || y >= height) {
            y_direction *= -1;
        }

        
        gotoXY(0, height+2);
        std::cout << "Enter a command for MARQUEE_CONSOLE: Notice the crude refresh. This is very dependent on your monitor" << std::endl;
        // get ch???
        if (_kbhit()) {
            cursorInfo.bVisible = TRUE;
            c = _getch();
            std::cout << "Command processed in MARQUEE_CONSOLE: " << c << std::endl;
        }
        else {
            if (c != ' ') {
                cursorInfo.bVisible = TRUE;
                std::cout << "Command processed in MARQUEE_CONSOLE: " << c << std::endl;
            }
            else {
                cursorInfo.bVisible = TRUE;
                std::cout << "Command processed in MARQUEE_CONSOLE: " << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        cursorInfo.bVisible = FALSE;
    }

    return 0;
}
