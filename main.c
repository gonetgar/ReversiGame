#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define BOARDTOTALSIZE 20

int displayMenu();
void initBoard(char board[][BOARDTOTALSIZE], int boardSize);
void printBoard(char board[][BOARDTOTALSIZE], int boardSize);
void playTheGame(char* board[][BOARDTOTALSIZE], int boardSize);
char switchPlayerChar(char playerName);
bool checkBoardRight(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardLeft(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardUp(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardDown(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardUpRight(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardUpLeft(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardDownRight(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool checkBoardDownLeft(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
bool newStep(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter);
void theWinnerIs(int boardSize, char board[][BOARDTOTALSIZE]);

void main()
{
	char board[BOARDTOTALSIZE][BOARDTOTALSIZE];
	int boardSize = 0, row, col, turnCounter = 0; // int choice
	//char playerName = 'X';

	boardSize = displayMenu();
	initBoard(board, boardSize);
	printBoard(board, boardSize);

	playTheGame(&board, boardSize);

	theWinnerIs(boardSize, board);
}

// main game course function that handles the entire game
void playTheGame(char* board[][BOARDTOTALSIZE], int boardSize)
{
	char playerName = 'X';
	int turnCounter = 0, row, col;

	while (turnCounter < (boardSize * boardSize - 3))
	{
		bool played = false;

		do
		{
			if (checkAnyAvailableMovesOnBoard(board, boardSize)) // if possible to play
			{
				printf("Player (%c) turn\n", playerName);
				printf("Enter your move (row + column): \n");
				scanf("%d%d", &row, &col);
				printf("\n");
				played = newStep(board, boardSize, row, col, turnCounter);
			}
			else
				played = false;
			
		} while (!played);

		playerName = switchPlayerChar(playerName);

		printf("\n");
		turnCounter++;
	}
}

int displayMenu()
{
	int choice, boardSize;

	do
	{
		printf("Select board size:\n0. Exit\n1. 10x10\n2. 15x15\n3. 20x20\n");
		scanf("%d", &choice);

		if (choice < 0 || choice > 3)
			printf("Invalid option.\n\n");

	} while (choice < 0 || choice > 3);

	switch (choice)
	{
	case 1:
		boardSize = 10;
		break;
	case 2:
		boardSize = 15;
		break;
	case 3:
		boardSize = 20;
		break;
	default:
		return;
		break;
	}

	return boardSize;
}



//this function initiates the board game.
void initBoard(char board[][BOARDTOTALSIZE], int boardSize)
{
	int i, j;

	for (i = 0; i <= boardSize; i++)
	{
		for (j = 0; j <= boardSize; j++)
		{
			board[i][j] = '_';
		}
	}

	// initiallize first places for X and O
	board[boardSize / 2][boardSize / 2] = 'X';
	board[boardSize / 2][boardSize / 2 + 1] = 'O';
	board[boardSize / 2 + 1][boardSize / 2] = 'O';
	board[boardSize / 2 + 1][boardSize / 2 + 1] = 'X';
}

//this function prints out the board at the beginning of the game.
void printBoard(char board[][BOARDTOTALSIZE], int boardSize)
{
	int i, j;

	printf("   ");

	for (i = 1; i <= boardSize; i++)
	{
		printf(" %2d", i);
	}
	printf("\n");

	for (i = 1; i <= boardSize; i++)
	{
		printf(" %2d", i);

		for (j = 1; j <= boardSize; j++)
		{
			printf(" %2c", board[i][j]);
		}

		printf("\n");
	}
}

//this function switches the name of the players
char switchPlayerChar(char playerName)
{
	if (playerName == 'X')
		playerName = 'O';
	else
		playerName = 'X';
	return (playerName);
}

// this function checks which squares to fip. ONLY ON THE RIGHT SIDE of the move.
bool checkBoardRight(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int j, newPlace = col;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[row][newPlace] == 'O' || board[row][newPlace] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[row][newPlace + 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[row][newPlace + 1] == 'X')
			return false;

		while (board[row][newPlace + 1] == 'O')
		{
			newPlace++;
			//if he put in the last sqaure, if there is no 'X' in the end of the row.
			if ((newPlace + 1) == boardSize && board[row][boardSize] == 'O' && board[row][newPlace + 1] == 'O')
				break;

			if (board[row][newPlace + 1] == 'X')
			{
				for (j = col; j < newPlace + 1; j++)
				{
					board[row][j] = 'X';
				}

			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' TURN. 
	{
		if (board[row][newPlace] == 'X' || board[row][newPlace] == 'O')
			return false;

		if (board[row][newPlace + 1] == '_')
			return false;

		if (board[row][newPlace + 1] == 'O')
			return false;

		while (board[row][newPlace + 1] == 'X')
		{
			newPlace++;
			if ((newPlace + 1) == boardSize && board[row][boardSize] == 'X' && board[row][newPlace + 1] == 'X')
				break;

			if (board[row][newPlace + 1] == 'O')
			{
				for (j = col; j < newPlace + 1; j++)
				{
					board[row][j] = 'O';
				}

			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE LEFT SIDE of the move.
bool checkBoardLeft(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int j, newPlace = col;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[row][newPlace] == 'O' || board[row][newPlace] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[row][newPlace - 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[row][newPlace - 1] == 'X')
			return false;

		while (board[row][newPlace - 1] == 'O')
		{
			newPlace--;
			// if the place is taken, if he puts on the last square, if he puts next to his own shape.
			if ((newPlace - 1) == 0 && board[row][0] == 'O' && board[row][newPlace - 1] == 'O')
				break;

			if (board[row][newPlace - 1] == 'X')
			{
				for (j = newPlace; j <= col; j++)
					board[row][j] = 'X';
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' move
	{
		if (board[row][newPlace] == 'X' || board[row][newPlace] == 'O')
			return false;

		if (board[row][newPlace - 1] == '_')
			return false;

		if (board[row][newPlace - 1] == 'O')
			return false;

		while (board[row][newPlace - 1] == 'X')
		{
			newPlace--;
			if ((newPlace - 1) == 0 && board[row][0] == 'X' && board[row][newPlace - 1] == 'X')
				break;

			if (board[row][newPlace - 1] == 'O')
			{
				for (j = newPlace; j <= col; j++)
					board[row][j] = 'O';
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE UP SIDE of the MOVE.
bool checkBoardUp(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int i;
	int newPlace = row;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[newPlace][col] == 'O' || board[newPlace][col] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newPlace - 1][col] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newPlace - 1][col] == 'X')
			return false;

		while (board[newPlace - 1][col] == 'O')
		{
			newPlace--;
			if (newPlace - 1 == 0 && newPlace - 1 == '_')
				break;

			if (board[newPlace - 1][col] == 'X')
			{
				for (i = newPlace; i <= row; i++)
				{
					board[i][col] = 'X';
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' move
	{
		if (board[newPlace][col] == 'X' || board[newPlace][col] == 'O')
			return false;

		if (board[newPlace - 1][col] == '_')
			return false;

		if (newPlace == 0)
			return false;

		while (board[newPlace - 1][col] == 'X')
		{
			newPlace--;
			if (newPlace - 1 == 0 && newPlace == '_')
				break;

			if (board[newPlace - 1][col] == 'O')
			{
				for (i = newPlace; i <= row; i++)
				{
					board[i][col] = 'O';
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE DOWN SIDE of the MOVE.
bool checkBoardDown(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int i;
	int newPlace = row;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[newPlace][col] == 'O' || board[newPlace][col] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newPlace + 1][col] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newPlace + 1][col] == 'X')
			return false;

		while (board[newPlace + 1][col] == 'O')
		{
			newPlace++;
			if ((newPlace + 1) == boardSize - 1 && board[newPlace + 1][col] == '_')
				break;

			if (board[newPlace + 1][col] == 'X')
			{
				for (i = row; i <= newPlace + 1; i++)
				{
					board[i][col] = 'X';
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' TURN
	{
		if (board[newPlace][col] == 'O' || board[newPlace][col] == 'X')
			return false;

		if (board[newPlace + 1][col] == '_')
			return false;

		if (board[newPlace + 1][col] == 'O')
			return false;

		while (board[newPlace + 1][col] == 'X')
		{
			newPlace++;
			if ((newPlace + 1) == boardSize - 1 && board[newPlace + 1][col] == '_')
				break;

			if (board[newPlace + 1][col] == 'O')
			{
				for (i = row; i <= newPlace + 1; i++)
				{
					board[i][col] = 'O';
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE UP RIGHT SIDE of the MOVE.
bool checkBoardUpRight(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int i = row, j = col;
	int newRow = row;
	int newCol = col;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newRow - 1][newCol + 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newRow - 1][newCol + 1] == 'X')
			return false;

		while (board[newRow - 1][newCol + 1] == 'O')
		{
			newRow--;
			newCol++;
			if (board[newRow - 1][newCol + 1] == 'O' || board[newRow - 1][newCol + 1] == '_')
				break;

			if (board[newRow - 1][newCol + 1] == 'X')
			{
				while ((i >= newRow - 1) && (j <= newCol + 1))
				{
					board[i][j] = 'X';
					i--;
					j++;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' TURN
	{
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		if (board[newRow - 1][newCol + 1] == '_')
			return false;

		if (board[newRow - 1][newCol + 1] == 'O')
			return false;

		while (board[newRow - 1][newCol + 1] == 'X')
		{
			newRow--;
			newCol++;
			if (board[newRow - 1][newCol + 1] == 'X' || board[newRow - 1][newCol + 1] == '_')
				break;

			if (board[newRow - 1][newCol + 1] == 'O')
			{
				while ((i >= newRow - 1) && (j <= newCol + 1))
				{
					board[i][j] = 'O';
					i--;
					j++;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE UP LEFT SIDE of the MOVE.
bool checkBoardUpLeft(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int i = row, j = col; // row+col is what the player chose. we need to check which sqaures to flip.
	int newRow = row;
	int newCol = col;

	if (turnCounter % 2 == 0) // X move
	{
		// if the place isn't available.
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newRow - 1][newCol - 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newRow - 1][newCol - 1] == 'X')
			return false;

		while (board[newRow - 1][newCol - 1] == 'O')
		{
			newRow--;
			newCol--;
			if ((newCol - 1 == col || newRow - 1 == row) && (board[newRow - 1][newCol - 1] == 'O'))
				break;

			if (board[newRow - 1][newCol - 1] == 'X')
			{
				while ((i > newRow - 1) && (j > newCol - 1))
				{
					board[i][j] = 'X';
					i--;
					j--;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' move
	{
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		if (board[newRow - 1][newCol - 1] == '_')
			return false;

		if (board[newRow - 1][newCol - 1] == 'O')
			return false;

		while (board[newRow - 1][newCol - 1] == 'X')
		{
			newRow--;
			newCol--;
			if ((newCol - 1 == col || newRow - 1 == row) && (board[newRow - 1][newCol - 1] == 'X'))
				break;

			if (board[newRow - 1][newCol - 1] == 'O')
			{
				while ((i > newRow - 1) && (j > newCol - 1))
				{
					board[i][j] = 'O';
					i--;
					j--;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE DOWN RIGHT SIDE of the MOVE.
bool checkBoardDownRight(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int i = row, j = col; // row+col is what the player chose. we need to check which sqaures to flip.
	int newRow = row;
	int newCol = col;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newRow + 1][newCol + 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newRow + 1][newCol + 1] == 'X')
			return false;

		while (board[newRow + 1][newCol + 1] == 'O')
		{
			newRow++;
			newCol++;
			if ((newCol + 1 == col || newRow + 1 == row) && (board[newRow + 1][newCol + 1] == 'O'))
				break;

			if (board[newRow + 1][newCol + 1] == 'X')
			{
				while ((i < newRow + 1) && (j < newCol + 1))
				{
					board[i][j] = 'X';
					i++;
					j++;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' TURN
	{
		// if the place isn't available.
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newRow + 1][newCol + 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newRow + 1][newCol + 1] == 'O')
			return false;

		while (board[newRow + 1][newCol + 1] == 'X')
		{
			newRow++;
			newCol++;
			if ((newCol + 1 == col || newRow + 1 == row) && (board[newRow + 1][newCol + 1] == 'X'))
				break;

			if (board[newRow + 1][newCol + 1] == 'O')
			{
				while ((i < newRow + 1) && (j < newCol + 1))
				{
					board[i][j] = 'O';
					i++;
					j++;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function checks which squares to fip. ONLY ON THE DOWN LEFT SIDE of the MOVE.
bool checkBoardDownLeft(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	int i = row, j = col;
	int newRow = row;
	int newCol = col;

	if (turnCounter % 2 == 0) // X TURN
	{
		// if the place isn't available.
		if (board[newRow][newCol] == 'O' || board[newRow][newCol] == 'X')
			return false;

		// if there is a space inbetween.
		if (board[newRow + 1][newCol - 1] == '_')
			return false;

		// if he tries to block near a X.
		if (board[newRow + 1][newCol - 1] == 'X')
			return false;

		while (board[newRow + 1][newCol - 1] == 'O')
		{
			newRow++;
			newCol--;
			if ((newCol - 1 == col || newRow + 1 == row) && (board[newRow + 1][newCol - 1] == 'O'))
				break;

			if (board[newRow + 1][newCol - 1] == 'X')
			{
				while ((i < newRow + 1) && (j > newCol - 1))
				{
					board[i][j] = 'X';
					i++;
					j--;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}

	else // 'O' TURN
	{
		while (board[newRow + 1][newCol - 1] == 'X')
		{
			newRow++;
			newCol--;
			if ((newCol - 1 == col || newRow + 1 == row) && (board[newRow + 1][newCol - 1] == 'X'))
				break;
			if (board[newRow + 1][newCol - 1] == 'O')
			{
				while ((i < newRow + 1) && (j > newCol - 1))
				{
					board[i][j] = 'O';
					i++;
					j--;
				}
			}
			else
			{
				continue;
			}
			return true;
		}
	}
}

// this function combines ALL of the checks, so if it's a right move, it'll print the board.
bool newStep(char board[][BOARDTOTALSIZE], int boardSize, int row, int col, int turnCounter)
{
	if (turnCounter % 2 == 0) // X TURN
	{
		if (checkBoardRight(board, boardSize, row, col, turnCounter) == true || checkBoardLeft(board, boardSize, row, col, turnCounter) == true || checkBoardUp(board, boardSize, row, col, turnCounter) == true || checkBoardDown(board, boardSize, row, col, turnCounter) == true || checkBoardUpRight(board, boardSize, row, col, turnCounter) == true || checkBoardUpLeft(board, boardSize, row, col, turnCounter) == true || checkBoardDownRight(board, boardSize, row, col, turnCounter) == true || checkBoardDownLeft(board, boardSize, row, col, turnCounter) == true)
		{
			printBoard(board, boardSize);
			return true;
		}
		else
		{
			printf("Invalid move!\n");
			return false;
		}
	}
	else // O TURN
	{
		if (checkBoardRight(board, boardSize, row, col, turnCounter) == true || checkBoardLeft(board, boardSize, row, col, turnCounter) == true || checkBoardUp(board, boardSize, row, col, turnCounter) == true || checkBoardDown(board, boardSize, row, col, turnCounter) == true || checkBoardUpRight(board, boardSize, row, col, turnCounter) == true || checkBoardUpLeft(board, boardSize, row, col, turnCounter) == true || checkBoardDownRight(board, boardSize, row, col, turnCounter) == true || checkBoardDownLeft(board, boardSize, row, col, turnCounter) == true)
		{
			printBoard(board, boardSize);
			return true;
		}
		else
		{
			printf("Invalid move!\n");
			return false;
		}
	}
}

//this function declares the winner
void theWinnerIs(int boardSize, char board[][BOARDTOTALSIZE])
{
	int i, j, countXs = 0, countOs = 0;

	for (i = 0; i < boardSize; i++)
	{
		for (j = 0; j < boardSize; j++)
		{
			if (board[i][j] == 'X')
				countXs++;
			else
				countOs++;
		}
	}

	if (countXs > countOs)
	{
		printf("The winner is: X!\n");
	}
	else if (countXs < countOs)
	{
		printf("The winner is: O!\n");
	}
	else
	{
		printf("It's a tie!\n");
	}
}