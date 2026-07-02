#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string APPLICATION_NAME = "ChatGPT Prompt Assistant";
const string AUTHOR_NAME = "TEO YU XUAN";
const string AUTHOR_EMAIL = "teo.yu.xuan2@student.mmu.edu.my";
const int BORDER_WIDTH = 78;

string trim(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

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

void pauseProgram() {
    cout << "\nPress ENTER to return to the main menu...";
    string unusedInput;
    getline(cin, unusedInput);
}

bool isInteger(const string& text) {
    if (text.empty()) {
        return false;
    }

    for (char character : text) {
        if (!isdigit(static_cast<unsigned char>(character))) {
            return false;
        }
    }
    return true;
}

int getValidatedInteger(const string& prompt, int minimumValue, int maximumValue) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (!isInteger(input)) {
            cout << "Invalid input. Please enter a number only.\n";
            continue;
        }

        int value = 0;
        stringstream converter(input);
        converter >> value;

        if (value < minimumValue || value > maximumValue) {
            cout << "Invalid choice. Please enter a number from "
                 << minimumValue << " to " << maximumValue << ".\n";
            continue;
        }

        return value;
    }
}

string getRequiredText(const string& prompt) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        if (input.empty()) {
            cout << "This field cannot be empty. Please try again.\n";
            continue;
        }

        return input;
    }
}

void displayMainMenu() {
    printHeader(APPLICATION_NAME);
    cout << "1. Study Assistant\n";
    cout << "2. Coding Assistant\n";
    cout << "3. Help / About ChatGPT\n";
    cout << "4. Exit\n";
    printBorder('-');
}

int main() {
    bool isRunning = true;

    while (isRunning) {
        displayMainMenu();
        int menuChoice = getValidatedInteger("Enter your choice: ", 1, 4);

        switch (menuChoice) {
            case 1:
                printHeader("Study Assistant");
                cout << "Study Assistant will be added in a later commit.\n";
                pauseProgram();
                break;
            case 2:
                printHeader("Coding Assistant");
                cout << "Coding Assistant will be added in a later commit.\n";
                pauseProgram();
                break;
            case 3:
                printHeader("Help / About ChatGPT");
                cout << "Prepared by: " << AUTHOR_NAME << '\n';
                cout << "Email: " << AUTHOR_EMAIL << '\n';
                pauseProgram();
                break;
            case 4:
                printHeader("Goodbye");
                cout << "Thank you for using " << APPLICATION_NAME << ".\n";
                isRunning = false;
                break;
        }
    }

    return 0;
}