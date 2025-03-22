#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];  // Tic Tac Toe board

// Function declarations
void initializeBoard();
void printBoard();
int checkWin();
void markWinningLine(int winCode);
int isBoardFull();
void pcMove(char marker);
int isValidMove(int row, int col);

int main() {
    char player1[50], player2[50] = "Computer";
    char currentMarker;
    char currentPlayer[50];
    int row, col, winner = 0, turns = 0;
    int mode;

    srand(time(NULL));  // Seed for random moves by PC

    // Game mode selection
    printf("Tic Tac Toe Game\n");
    printf("1. Play with a friend\n");
    printf("2. Play against the computer\n");
    printf("Choose mode (1 or 2): ");
    scanf("%d", &mode);
    getchar();  // Clear newline after scanf

    if (mode == 1) {
        printf("Enter name of Player 1 (X): ");
        fgets(player1, sizeof(player1), stdin);
        player1[strcspn(player1, "\n")] = 0;

        printf("Enter name of Player 2 (O): ");
        fgets(player2, sizeof(player2), stdin);
        player2[strcspn(player2, "\n")] = 0;
    } else {
        printf("Enter your name (You will be X): ");
        fgets(player1, sizeof(player1), stdin);
        player1[strcspn(player1, "\n")] = 0;
    }

    initializeBoard();
    printBoard();

    strcpy(currentPlayer, player1);
    currentMarker = 'X';

    while (1) {
        if (mode == 2 && strcmp(currentPlayer, "Computer") == 0) {
            printf("Computer's turn (O)...\n");
            pcMove(currentMarker);
        } else {
            printf("%s's turn (%c). Enter row and column (0-2): ", currentPlayer, currentMarker);
            scanf("%d %d", &row, &col);

            if (!isValidMove(row, col)) {
                printf("Invalid move. Try again.\n");
                continue;
            }
            board[row][col] = currentMarker;
        }

        printBoard();
        turns++;

        // Check for winner
        int winCode = checkWin();
        if (winCode) {
            markWinningLine(winCode);  // Highlight the winning line
            printBoard();
            printf("Congratulations %s! You have won the game.\n", currentPlayer);
            break;
        }

        // Check for draw
        if (turns == 9) {
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        if (strcmp(currentPlayer, player1) == 0) {
            strcpy(currentPlayer, player2);
            currentMarker = 'O';
        } else {
            strcpy(currentPlayer, player1);
            currentMarker = 'X';
        }
    }

    printf("Game Over! Thanks for playing.\n");
    return 0;
}

// Initialize the board with spaces
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Print the current state of the board
void printBoard() {
    printf("\n");
    printf("  0   1   2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  ---+---+---\n");
    }
    printf("\n");
}

// Check for a winning condition
int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1 + i;  // Row win
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 4 + i;  // Column win
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return 7;  // Main diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return 8;  // Anti-diagonal

    return 0;  // No winner
}

// Highlight the winning line with '*'
void markWinningLine(int winCode) {
    switch (winCode) {
        case 1: for (int j = 0; j < 3; j++) board[0][j] = '*'; break;  // Row 0
        case 2: for (int j = 0; j < 3; j++) board[1][j] = '*'; break;  // Row 1
        case 3: for (int j = 0; j < 3; j++) board[2][j] = '*'; break;  // Row 2
        case 4: for (int i = 0; i < 3; i++) board[i][0] = '*'; break;  // Col 0
        case 5: for (int i = 0; i < 3; i++) board[i][1] = '*'; break;  // Col 1
        case 6: for (int i = 0; i < 3; i++) board[i][2] = '*'; break;  // Col 2
        case 7: for (int i = 0; i < 3; i++) board[i][i] = '*'; break;  // Main diagonal
        case 8: for (int i = 0; i < 3; i++) board[i][2 - i] = '*'; break;  // Anti-diagonal
    }
}

// Check if the board is full
int isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Check if a move is valid
int isValidMove(int row, int col) {
    return row >= 0 && row <= 2 && col >= 0 && col <= 2 && board[row][col] == ' ';
}

// PC makes a random valid move
void pcMove(char marker) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isValidMove(row, col));
    board[row][col] = marker;
}
