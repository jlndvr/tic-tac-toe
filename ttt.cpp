#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Constants
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Function prototypes
void printBoard(const vector<vector<char>>& board);
bool makeMove(vector<vector<char>>& board, int row, int col, char player);
bool checkWin(const vector<vector<char>>& board, char player);
bool checkDraw(const vector<vector<char>>& board);
void switchPlayer(char& currentPlayer);
void clearScreen();
int getValidInput(const string& prompt, int min, int max);

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    char currentPlayer = PLAYER_X;
    bool gameOver = false;

    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Player 1: X | Player 2: O\n\n";

    while (!gameOver) {
        printBoard(board);
        
        // Get player move
        cout << "Player " << currentPlayer << "'s turn\n";
        int row = getValidInput("Enter row (1-3): ", 1, 3) - 1;
        int col = getValidInput("Enter column (1-3): ", 1, 3) - 1;

        // Process move
        if (makeMove(board, row, col, currentPlayer)) {
            clearScreen();
            
            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                gameOver = true;
            } else if (checkDraw(board)) {
                printBoard(board);
                cout << "It's a draw!\n";
                gameOver = true;
            } else {
                switchPlayer(currentPlayer);
            }
        } else {
            cout << "That spot is already taken. Try again.\n";
        }
    }

    return 0;
}

void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
        if (i < 2) cout << "-----------\n";
    }
    cout << "\n";
}

bool makeMove(vector<vector<char>>& board, int row, int col, char player) {
    if (board[row][col] == EMPTY) {
        board[row][col] = player;
        return true;
    }
    return false;
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    
    return false;
}

bool checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}

void switchPlayer(char& currentPlayer) {
    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int getValidInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}
