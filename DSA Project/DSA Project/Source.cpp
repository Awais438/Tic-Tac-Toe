#include<iostream>
#include<conio.h>

using namespace std;

struct Move
{
	int row, col;
};

//function to display board
void DisplayBoard(char Board[3][3])
{
	cout << endl;
	cout << "\t\t " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << endl;
	cout << "\t\t___|___|___\n\t\t   |   |\n";
	cout << "\t\t " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << endl;
	cout << "\t\t___|___|___\n\t\t   |   |\n";
	cout << "\t\t " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << endl;
	cout << endl;
}

// This function returns true if there are moves remaining on the board
bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
				return true;
		}
	}
	return false;
}

//function to evaluate board to check if someone has won or lost or  draw
int EvaluateBoard(char Board[3][3])
{
	//checking horizontal 
	for (int row = 0; row < 3; row++)
	{
		if (Board[row][0] == Board[row][1] && Board[row][1] == Board[row][2])
		{
			if (Board[row][row] == 'x')
				return 1;

			if(Board[row][row]=='o')
				return -1;
		}
	}

	//checking vertical
	for (int col = 0; col < 3; col++)
	{
		if (Board[0][col] == Board[1][col] && Board[1][col] == Board[2][col])
		{
			if (Board[col][col] == 'x')
				return 1;

			if (Board[col][col] == 'o')
				return -1;
		}
	}

	//checking diagonal
	if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])
	{
		if (Board[0][0] == 'x')
			return 1;

		if (Board[0][0] == 'o')
			return -1;
	}

	//checking diagonal
	if (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0])
	{
		if (Board[0][2] == 'x')
			return 1;

		if (Board[0][2] == 'o')
			return -1;
	}

	//incase of draw
	return 0;
}

//this fuction returns maximum value
int max(int x, int y)
{
	if (x >= y)
		return x;
	else
		return y;
}

//this fuction returns minimum value
int min(int x, int y)
{
	if (x <= y)
		return x;
	else
		return y;
}

// This function check all the possible ways the game can go and return board value
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = EvaluateBoard(board);

	//incase maximizer won
	if (score == 1)
		return score;

	//incase minimizer won
	if (score == -1)
		return score;

	//incase of tie
	if (isMovesLeft(board) == false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == ' ')
				{
					// Make the move
					board[i][j] = 'x';

					// Call minimax recursively and choose the maximum value
					best = max(best, minimax(board, depth + 1, !isMax));

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty
				if (board[i][j] == ' ')
				{
					// Make the move
					board[i][j] = 'o';

					// Call minimax recursively and choose the minimum value
					best = min(best, minimax(board, depth + 1, !isMax));

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the player
Move findBestMove(char board[3][3])
{
	int bestVal = -1000;

	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for all empty cells. And return the cell with optimal value.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Check if cell is empty
			if (board[i][j] == ' ')
			{
				// Make the move
				board[i][j] = 'x';

				// compute evaluation function for this move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = ' ';

				// If the value of the current move is more than the best value, then update best
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}

//this function check if the cell entered is available or not
bool iscellavilable(char Board[3][3], Move m)
{
	if (Board[m.row][m.col] == ' ')
		return true;

	else
	{
		cout << "Cell occupied!!  Try Another Cell" << endl << endl;
		return false;
	}
}

//Function that prompt Player's move
Move Player_move(char Board[3][3])
{
	Move Player;
	do
	{
		cout << "Player Turn 'o'" << endl;
		cout << "Enter Row: ";
		cin >> Player.row;
		cout << "Enter Column: ";
		cin >> Player.col;

	} while (!iscellavilable(Board, Player));

	return Player;
}

//main body
int main()
{
	Move Player, ai;
	int result = 0;
	char ch;

	do
	{
		char Board[3][3] = { {' ',' ',' '},{' ',' ',' ',},{' ',' ',' '} };

		cout << "\t _________________________________" << endl;
		cout << "\t|                                 |" << endl;
		cout << "\t|     TWO PLAYERS TIC-TAC-TOE     |" << endl;
		cout << "\t|_________________________________|" << endl << endl;

		//execute untill no move left or someone won
		while (isMovesLeft(Board))
		{
			cout << "AI Turn 'x'" << endl;
			ai = findBestMove(Board);		//finding best optimal move for AI
			Board[ai.row][ai.col] = 'x';

			DisplayBoard(Board);
			cout << endl << endl;

			//after AI turn, evaluating board to check if someone won
			result = EvaluateBoard(Board);

			if (result == 1)
			{
				cout << endl << "\t\tAI Won" << endl;
				break;
			}
			else if (result == -1)
			{
				cout << endl << "\t\tPlayer Won" << endl;
				break;
			}
			else if (!isMovesLeft(Board))
			{
				cout << endl << "\t\tGame Draw!" << endl;
				break;
			}

			Player = Player_move(Board);
			Board[Player.row][Player.col] = 'o';

			DisplayBoard(Board);

			//after player's turn, evaluating board to check if someone won
			result = EvaluateBoard(Board);

			if (result == 1)
			{
				cout << endl << "\t\tAI Won" << endl;
				break;
			}
			else if (result == -1)
			{
				cout << endl << "\t\tPlayer Won" << endl;
				break;
			}
			else if (!isMovesLeft(Board))
			{
				cout << endl << "\t\tGame Draw!" << endl;
				break;
			}
		}
		cout << "\n Play Again: (y or n): ";
		cin >> ch;

	} while (ch == 'y');

	_getch();
	return 0;
}