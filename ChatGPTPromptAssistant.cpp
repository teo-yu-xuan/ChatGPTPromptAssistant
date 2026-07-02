#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

void printSubHeader(const string& title) {
    cout << '\n';
    printBorder('-');
    cout << title << '\n';
    printBorder('-');
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

void displayGeneratedPrompt(const string& prompt) {
    printSubHeader("Generated ChatGPT Prompt");
    cout << prompt << '\n';
    printBorder('-');
}

void addPromptToHistory(vector<string>& promptHistory, const string& category, const string& prompt) {
    string storedPrompt = "[" + category + "]\n" + prompt;
    promptHistory.push_back(storedPrompt);
}

void viewPromptHistory(const vector<string>& promptHistory) {
    printSubHeader("Prompt History");

    if (promptHistory.empty()) {
        cout << "No prompts have been generated yet.\n";
        return;
    }

    for (size_t index = 0; index < promptHistory.size(); ++index) {
        cout << "\nPrompt " << index + 1 << ":\n";
        cout << promptHistory[index] << "\n";
        printBorder('.');
    }
}

void demoPromptGenerator(vector<string>& promptHistory) {
    printHeader("Prompt Generator Demo");
    string topic = getRequiredText("Enter a topic: ");

    string prompt = "Act as a helpful ChatGPT assistant. Explain " + topic
        + " clearly using examples and a short summary.";

    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Demo Prompt", prompt);
    pauseProgram();
}

void displayMainMenu() {
    printHeader(APPLICATION_NAME);
    cout << "1. Generate Demo Prompt\n";
    cout << "2. View Prompt History\n";
    cout << "3. Exit\n";
    printBorder('-');
}

int main() {
    vector<string> promptHistory;
    bool isRunning = true;

    while (isRunning) {
        displayMainMenu();
        int menuChoice = getValidatedInteger("Enter your choice: ", 1, 3);

        switch (menuChoice) {
            case 1:
                demoPromptGenerator(promptHistory);
                break;
            case 2:
                viewPromptHistory(promptHistory);
                pauseProgram();
                break;
            case 3:
                printHeader("Goodbye");
                cout << "Thank you for using " << APPLICATION_NAME << ".\n";
                isRunning = false;
                break;
        }
    }

    return 0;
}