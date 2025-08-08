#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Function to choose a random word from the list
string getRandomWord() {
    vector<string> words = {"programming", "computer", "hangman", "science", "keyboard", "developer"};
    srand(time(0));
    return words[rand() % words.size()];
}

// Function to display current guessed word with underscores
void displayWord(const string& word, const vector<bool>& guessed) {
    for (int i = 0; i < word.size(); ++i) {
        if (guessed[i])
            cout << word[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

int main() {
    string word = getRandomWord();
    int attemptsLeft = 6;
    vector<bool> guessed(word.size(), false);
    vector<char> wrongGuesses;
    string guessedLetters = "";

    cout << "?? Welcome to Hangman!\n";

    while (attemptsLeft > 0) {
        cout << "\nWord: ";
        displayWord(word, guessed);

        cout << "Wrong guesses: ";
        for (char c : wrongGuesses) cout << c << " ";
        cout << "\nAttempts left: " << attemptsLeft << endl;

        char guess;
        cout << "Enter a letter: ";
        cin >> guess;
        guess = tolower(guess);

        // Already guessed
        if (guessedLetters.find(guess) != string::npos) {
            cout << "You already guessed that letter.\n";
            continue;
        }

        guessedLetters += guess;

        bool correct = false;
        for (int i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessed[i] = true;
                correct = true;
            }
        }

        if (!correct) {
            wrongGuesses.push_back(guess);
            attemptsLeft--;
        }

        // Check for win
        if (all_of(guessed.begin(), guessed.end(), [](bool b) { return b; })) {
            cout << "\n?? Congratulations! You guessed the word: " << word << endl;
            return 0;
        }
    }

    // If out of attempts
    cout << "\n?? Game Over! The word was: " << word << endl;
    return 0;
}

