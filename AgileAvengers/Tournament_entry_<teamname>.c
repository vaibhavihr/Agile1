void playMove_AgileAvengers(char board[SIZE][SIZE], char player, int *x, int *y) {
    int row, col;

    // Check for winning moves and blocking opponent's forks
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (isValidMove(board, row, col)) {
                // Try making the move
                board[row][col] = player;

                // Check if this move results in a win
                int countX[5], countO[5];
                scoreBoard(board, countX, countO);
                if (countX[4] > 0) {
                    // If this move leads to a win, set the coordinates and return
                    *x = row;
                    *y = col;
                    return;
                }

                // Check if opponent's move leads to occupying more than 3 spaces
                bool opponentThreat = false;
                char opponent = (player == 'X') ? 'O' : 'X'; // Opponent of player 'X'
                
                // Check horizontally
                int horizontalCount = 0;
                for (int i = 0; i < SIZE; i++) {
                    if (board[row][i] == opponent)
                        horizontalCount++;
                }
                if (horizontalCount >= 3) {
                    opponentThreat = true;
                }

                // Check vertically
                int verticalCount = 0;
                for (int i = 0; i < SIZE; i++) {
                    if (board[i][col] == opponent)
                        verticalCount++;
                }
                if (verticalCount >= 3) {
                    opponentThreat = true;
                }

                              
                // Check diagonally (top-right to bottom-left)
                if (row + col == SIZE - 1) {
                    int diagonalCount = 0;
                    for (int i = 0; i < SIZE; i++) {
                        if (board[i][SIZE - 1 - i] == opponent)
                            diagonalCount++;
                    }
                    if (diagonalCount >= 3) {
                        opponentThreat = true;
                    }
                }

                // If opponent's move threatens to occupy more than 3 spaces, block it
                if (opponentThreat) {
                    board[row][col] = player;
                    *x = row;
                    *y = col;
                    return;
                }

                // Undo the move
                board[row][col] = ' ';
            }
        }
    }

    // If no winning, blocking, or threatening moves, choose a random valid move
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));

    *x = row;
    *y = col;
}
