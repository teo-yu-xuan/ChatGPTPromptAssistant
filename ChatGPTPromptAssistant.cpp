#include <algorithm>
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

string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char character) {
        return static_cast<char>(tolower(character));
    });
    return text;
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

string chooseFromList(const string& prompt, const vector<string>& options) {
    for (size_t index = 0; index < options.size(); ++index) {
        cout << "  " << index + 1 << ". " << options[index] << '\n';
    }

    int choice = getValidatedInteger(prompt, 1, static_cast<int>(options.size()));
    return options[choice - 1];
}

void displayGeneratedPrompt(const string& prompt) {
    printSubHeader("Generated ChatGPT Prompt");
    cout << prompt << "\n";
    printBorder('-');
}

void addPromptToHistory(vector<string>& promptHistory, const string& category, const string& prompt) {
    string storedPrompt = "[" + category + "]\n" + prompt;
    promptHistory.push_back(storedPrompt);
}

string buildStudyPrompt(const string& subject, const string& difficulty, const string& learningStyle) {
    return "Act as an expert " + subject + " tutor. Explain the topic at a "
        + toLowerCase(difficulty) + " level using a " + learningStyle
        + " learning style. Break the lesson into clear sections, define important terms, "
          "give practical examples, ask three checkpoint questions, and finish with a short revision summary.";
}

string buildCodingPrompt(const string& language, const string& problemType, const string& level) {
    return "Act as a professional " + language
        + " programming mentor for a learner at the " + toLowerCase(level)
        + " level. Help me solve this type of problem: " + problemType
        + ". Explain the approach first, provide clean and well-commented " + language
        + " code, describe the time and space complexity, and include test cases with expected output.";
}

string buildBusinessPrompt(const string& task, const string& audience, const string& goal) {
    return "Act as a professional business consultant. Create a high-quality " + task
        + " for the following goal: " + goal + ". The target audience is " + audience
        + ". Use a clear business tone, organize the response with headings, include practical recommendations, "
          "and make the final output suitable for a university or workplace presentation.";
}

string buildTranslationPrompt(const string& sourceLanguage, const string& targetLanguage,
                              const string& tone, const string& textToTranslate) {
    return "Act as a professional translator. Translate the following text from " + sourceLanguage
        + " to " + targetLanguage + " using a " + tone
        + " tone. Preserve the original meaning, improve natural fluency, and provide a short note explaining any cultural or wording choices.\n\nText: "
        + textToTranslate;
}

void studyAssistant(vector<string>& promptHistory) {
    printHeader("Study Assistant");
    string subject = getRequiredText("Enter subject or topic: ");
    string difficulty = chooseFromList("Choose difficulty level: ", {"Beginner", "Intermediate", "Advanced"});
    string learningStyle = getRequiredText("Enter preferred learning style: ");
    string prompt = buildStudyPrompt(subject, difficulty, learningStyle);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Study Assistant", prompt);
    pauseProgram();
}

void codingAssistant(vector<string>& promptHistory) {
    printHeader("Coding Assistant");
    string programmingLanguage = getRequiredText("Enter programming language: ");
    string problemType = getRequiredText("Enter problem type: ");
    string level = chooseFromList("Choose user level: ", {"Beginner", "Advanced"});
    string prompt = buildCodingPrompt(programmingLanguage, problemType, level);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Coding Assistant", prompt);
    pauseProgram();
}

void businessAssistant(vector<string>& promptHistory) {
    printHeader("Business Assistant");
    string businessTask = chooseFromList("Choose business task: ", {
        "Marketing Plan",
        "Business Proposal",
        "Presentation Outline",
        "SWOT Analysis",
        "Meeting Agenda",
        "Custom Business Task"
    });

    if (businessTask == "Custom Business Task") {
        businessTask = getRequiredText("Enter custom business task: ");
    }

    string audience = getRequiredText("Enter target audience: ");
    string goal = getRequiredText("Enter main business goal: ");
    string prompt = buildBusinessPrompt(businessTask, audience, goal);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Business Assistant", prompt);
    pauseProgram();
}

void translationAssistant(vector<string>& promptHistory) {
    printHeader("Translation Assistant");
    vector<string> languages = {"English", "Malay", "Chinese", "Japanese"};
    string sourceLanguage = chooseFromList("Choose source language: ", languages);
    string targetLanguage;

    while (true) {
        targetLanguage = chooseFromList("Choose target language: ", languages);
        if (toLowerCase(sourceLanguage) != toLowerCase(targetLanguage)) {
            break;
        }
        cout << "Source and target languages must be different.\n";
    }

    string tone = getRequiredText("Enter desired tone: ");
    string textToTranslate = getRequiredText("Enter text to translate: ");
    string prompt = buildTranslationPrompt(sourceLanguage, targetLanguage, tone, textToTranslate);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Translation Assistant", prompt);
    pauseProgram();
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

void displayMainMenu() {
    printHeader(APPLICATION_NAME);
    cout << "1. Study Assistant\n";
    cout << "2. Coding Assistant\n";
    cout << "3. Business Assistant\n";
    cout << "4. Translation Assistant\n";
    cout << "5. Prompt History\n";
    cout << "6. Exit\n";
    printBorder('-');
}

int main() {
    vector<string> promptHistory;
    bool isRunning = true;

    while (isRunning) {
        displayMainMenu();
        int menuChoice = getValidatedInteger("Enter your choice: ", 1, 6);

        switch (menuChoice) {
            case 1:
                studyAssistant(promptHistory);
                break;
            case 2:
                codingAssistant(promptHistory);
                break;
            case 3:
                businessAssistant(promptHistory);
                break;
            case 4:
                translationAssistant(promptHistory);
                break;
            case 5:
                viewPromptHistory(promptHistory);
                pauseProgram();
                break;
            case 6:
                printHeader("Goodbye");
                cout << "Thank you for using " << APPLICATION_NAME << ".\n";
                isRunning = false;
                break;
        }
    }

    return 0;
}