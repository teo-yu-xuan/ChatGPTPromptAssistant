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

// Removes spaces from the front and back of a string.
string trim(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

// Converts a string to lowercase for easier comparisons.
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

// Waits for the user before returning to the main menu.
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

// Reads and validates a menu number. Letters and out-of-range values are rejected.
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

// Reads a required text field and prevents empty answers.
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

string buildCreativeWritingPrompt(const string& writingType, const string& topic,
                                  const string& audience, const string& tone) {
    return "Act as a creative writing coach. Write a " + writingType + " about " + topic
        + " for " + audience + ". Use a " + tone
        + " tone, include a strong opening, organize the ideas clearly, and make the writing engaging and original.";
}

string buildResumePrompt(const string& documentType, const string& targetRole,
                         const string& experience, const string& strengths) {
    return "Act as a professional career coach. Create a strong " + documentType
        + " for a candidate applying for " + targetRole
        + ". Candidate background: " + experience
        + ". Key strengths: " + strengths
        + ". Use action verbs, measurable achievements where possible, and a confident professional tone.";
}

string buildEmailPrompt(const string& emailType, const string& recipient,
                        const string& purpose, const string& tone) {
    return "Act as a professional communication assistant. Write a " + emailType
        + " email to " + recipient + " about " + purpose
        + ". Use a " + tone
        + " tone, include a clear subject line, concise message body, polite closing, and a specific next step.";
}

string improveWeakPrompt(const string& weakPrompt) {
    return "Act as an expert ChatGPT assistant. Please respond to the following request in a clear, accurate, and structured way: \""
        + weakPrompt
        + "\". Ask clarifying questions if important details are missing, use headings or bullet points where helpful, "
          "provide practical examples, and finish with a concise summary or recommendation.";
}

void studyAssistant(vector<string>& promptHistory) {
    printHeader("Study Assistant");

    string subject = getRequiredText("Enter subject or topic: ");
    string difficulty = chooseFromList("Choose difficulty level: ", {
        "Beginner",
        "Intermediate",
        "Advanced"
    });
    string learningStyle = getRequiredText("Enter preferred learning style (visual, examples, step-by-step, etc.): ");

    string prompt = buildStudyPrompt(subject, difficulty, learningStyle);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Study Assistant", prompt);
    pauseProgram();
}

void codingAssistant(vector<string>& promptHistory) {
    printHeader("Coding Assistant");

    string programmingLanguage = getRequiredText("Enter programming language: ");
    string problemType = getRequiredText("Enter problem type (debugging, algorithm, OOP, etc.): ");
    string level = chooseFromList("Choose user level: ", {
        "Beginner",
        "Advanced"
    });

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

    vector<string> languages = {
        "English",
        "Malay",
        "Chinese",
        "Japanese"
    };

    string sourceLanguage = chooseFromList("Choose source language: ", languages);
    string targetLanguage;

    while (true) {
        targetLanguage = chooseFromList("Choose target language: ", languages);
        if (toLowerCase(sourceLanguage) != toLowerCase(targetLanguage)) {
            break;
        }
        cout << "Source and target languages must be different.\n";
    }

    string tone = getRequiredText("Enter desired tone (formal, casual, academic, etc.): ");
    string textToTranslate = getRequiredText("Enter text to translate: ");

    string prompt = buildTranslationPrompt(sourceLanguage, targetLanguage, tone, textToTranslate);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Translation Assistant", prompt);
    pauseProgram();
}

void creativeWritingAssistant(vector<string>& promptHistory) {
    printHeader("Creative Writing Assistant");

    string writingType = chooseFromList("Choose writing type: ", {
        "Story",
        "Essay",
        "Speech",
        "Poem",
        "Social Media Post"
    });
    string topic = getRequiredText("Enter topic or theme: ");
    string audience = getRequiredText("Enter target audience: ");
    string tone = getRequiredText("Enter desired tone or style: ");

    string prompt = buildCreativeWritingPrompt(writingType, topic, audience, tone);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Creative Writing Assistant", prompt);
    pauseProgram();
}

void resumeAssistant(vector<string>& promptHistory) {
    printHeader("Resume & CV Assistant");

    string documentType = chooseFromList("Choose document type: ", {
        "Resume",
        "Cover Letter",
        "LinkedIn Summary"
    });
    string targetRole = getRequiredText("Enter target job role or industry: ");
    string experience = getRequiredText("Enter education, experience, or background: ");
    string strengths = getRequiredText("Enter key skills or achievements: ");

    string prompt = buildResumePrompt(documentType, targetRole, experience, strengths);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Resume & CV Assistant", prompt);
    pauseProgram();
}

void emailAssistant(vector<string>& promptHistory) {
    printHeader("Email Assistant");

    string emailType = chooseFromList("Choose email type: ", {
        "Formal",
        "Professional",
        "Customer Support",
        "Complaint",
        "Follow-up"
    });
    string recipient = getRequiredText("Enter recipient: ");
    string purpose = getRequiredText("Enter email purpose: ");
    string tone = getRequiredText("Enter desired tone: ");

    string prompt = buildEmailPrompt(emailType, recipient, purpose, tone);
    displayGeneratedPrompt(prompt);
    addPromptToHistory(promptHistory, "Email Assistant", prompt);
    pauseProgram();
}

void promptImprovementTool(vector<string>& promptHistory) {
    printHeader("Prompt Improvement Tool");

    string weakPrompt = getRequiredText("Enter your weak or basic prompt: ");
    string improvedPrompt = improveWeakPrompt(weakPrompt);

    displayGeneratedPrompt(improvedPrompt);
    addPromptToHistory(promptHistory, "Prompt Improvement Tool", improvedPrompt);
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

void deleteSinglePrompt(vector<string>& promptHistory) {
    if (promptHistory.empty()) {
        cout << "History is empty. There is nothing to delete.\n";
        return;
    }

    viewPromptHistory(promptHistory);
    int promptNumber = getValidatedInteger(
        "\nEnter the prompt number to delete: ",
        1,
        static_cast<int>(promptHistory.size())
    );

    promptHistory.erase(promptHistory.begin() + promptNumber - 1);
    cout << "Prompt " << promptNumber << " deleted successfully.\n";
}

void clearPromptHistory(vector<string>& promptHistory) {
    if (promptHistory.empty()) {
        cout << "History is already empty.\n";
        return;
    }

    cout << "This will delete all saved prompts in the current session.\n";
    int confirmation = getValidatedInteger("Enter 1 to confirm or 2 to cancel: ", 1, 2);

    if (confirmation == 1) {
        promptHistory.clear();
        cout << "All prompt history cleared successfully.\n";
    } else {
        cout << "Clear history cancelled.\n";
    }
}

void promptHistoryMenu(vector<string>& promptHistory) {
    bool returnToMainMenu = false;

    while (!returnToMainMenu) {
        printHeader("Prompt History");
        cout << "1. View History\n";
        cout << "2. Delete One Prompt\n";
        cout << "3. Clear All History\n";
        cout << "4. Return to Main Menu\n";
        printBorder('-');

        int choice = getValidatedInteger("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:
                viewPromptHistory(promptHistory);
                pauseProgram();
                break;
            case 2:
                deleteSinglePrompt(promptHistory);
                pauseProgram();
                break;
            case 3:
                clearPromptHistory(promptHistory);
                pauseProgram();
                break;
            case 4:
                returnToMainMenu = true;
                break;
        }
    }
}

void helpAboutChatGPT() {
    printHeader("Help / About ChatGPT");
    cout << "Program: " << APPLICATION_NAME << '\n';
    cout << "Prepared by: " << AUTHOR_NAME << '\n';
    cout << "Email: " << AUTHOR_EMAIL << "\n\n";

    cout << "ChatGPT is an AI chatbot that can understand natural language and generate\n";
    cout << "human-like responses for learning, coding, business, writing, translation,\n";
    cout << "career preparation, and communication tasks.\n\n";

    cout << "This offline program does not connect to the real ChatGPT service. Instead,\n";
    cout << "it demonstrates one important reason ChatGPT is disruptive: users can achieve\n";
    cout << "better results when they give clear roles, context, tasks, constraints, and\n";
    cout << "output expectations in their prompts.\n\n";

    cout << "Prompt writing tips:\n";
    cout << "  1. Tell ChatGPT what role to perform.\n";
    cout << "  2. Give enough background information.\n";
    cout << "  3. State the exact task clearly.\n";
    cout << "  4. Specify tone, audience, format, and difficulty.\n";
    cout << "  5. Ask for examples, checks, or summaries when useful.\n";

    pauseProgram();
}

void displayMainMenu() {
    printHeader(APPLICATION_NAME);
    cout << "1.  Study Assistant\n";
    cout << "2.  Coding Assistant\n";
    cout << "3.  Business Assistant\n";
    cout << "4.  Translation Assistant\n";
    cout << "5.  Creative Writing Assistant\n";
    cout << "6.  Resume & CV Assistant\n";
    cout << "7.  Email Assistant\n";
    cout << "8.  Prompt Improvement Tool\n";
    cout << "9.  Prompt History\n";
    cout << "10. Help / About ChatGPT\n";
    cout << "11. Exit\n";
    printBorder('-');
}

int main() {
    vector<string> promptHistory;
    bool isRunning = true;

    while (isRunning) {
        displayMainMenu();
        int menuChoice = getValidatedInteger("Enter your choice: ", 1, 11);

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
                creativeWritingAssistant(promptHistory);
                break;
            case 6:
                resumeAssistant(promptHistory);
                break;
            case 7:
                emailAssistant(promptHistory);
                break;
            case 8:
                promptImprovementTool(promptHistory);
                break;
            case 9:
                promptHistoryMenu(promptHistory);
                break;
            case 10:
                helpAboutChatGPT();
                break;
            case 11:
                printHeader("Goodbye");
                cout << "Thank you for using " << APPLICATION_NAME << ".\n";
                cout << "Prepared by " << AUTHOR_NAME << " (" << AUTHOR_EMAIL << ").\n";
                cout << "Use your generated prompts to communicate with ChatGPT more effectively.\n";
                isRunning = false;
                break;
        }
    }

    return 0;
}