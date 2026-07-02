#include <iostream>
#include <string>

using namespace std;

const string APPLICATION_NAME = "ChatGPT Prompt Assistant";
const string AUTHOR_NAME = "TEO YU XUAN";
const string AUTHOR_EMAIL = "teo.yu.xuan2@student.mmu.edu.my";
const int BORDER_WIDTH = 78;

void printBorder(char borderCharacter = '=') {
    cout << string(BORDER_WIDTH, borderCharacter) << '\n';
}

void printCenteredLine(const string& text) {
    int textLength = static_cast<int>(text.length());
    int padding = (BORDER_WIDTH - textLength) / 2;
    if (padding < 0) {
        padding = 0;
    }

    cout << string(padding, ' ') << text << '\n';
}

void printHeader(const string& title) {
    cout << '\n';
    printBorder('=');
    printCenteredLine(title);
    printBorder('=');
}

void printSubHeader(const string& title) {
    cout << '\n';
    printBorder('-');
    cout << title << '\n';
    printBorder('-');
}

void pauseProgram() {
    cout << "\nPress ENTER to continue...";
    string unusedInput;
    getline(cin, unusedInput);
}

int main() {
    printHeader(APPLICATION_NAME);
    cout << "Prepared by: " << AUTHOR_NAME << '\n';
    cout << "Email: " << AUTHOR_EMAIL << '\n';

    printSubHeader("Project Status");
    cout << "Console interface helpers added successfully.\n";
    pauseProgram();

    return 0;
}