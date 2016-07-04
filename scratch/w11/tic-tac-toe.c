/**
 * tictactoe.c
 *
 * Implements Tic Tac Toe (generalized to a board of size d x d).
 *
 * Usage: tictactoe
 *        tictactoe d
 *
 * if d is not specified, we default to a typical 3x3 board.
 * 
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Some of the input/output functions are generalized from fifteen.c (PS3)
 * 
 * To make our comparisons easy, 
 *      Player 1 is "O" and is the machine player
 *      Player -1 is "X" and is the human player
 */
 
#define MACHINE_PLAYER 1
#define MAX_DEPTH 5

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// machine player best move
int best_row;
int best_col;

// prototypes
void init();
void clear();
void draw();
int check_for_winner(int b[DIM_MAX][DIM_MAX]);
int parse_command_line(int argc, char *argv[]);
int read_player_input(int *r, int *c, int player);
int minimax(int hypothetical_board[DIM_MAX][DIM_MAX], int player, bool mymove, int depth);
        
int main(int argc, char *argv[])
{
    int current_player=-1; // X goes first
    int winner, row, col, score;
    int total_moves = 0;
    
    // parse the command line
    if (parse_command_line(argc, argv) != 0)
        return 1;
        
    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for winners
        winner = check_for_winner(board);
        if (winner != 0)
            {
                printf("VICTORY FOR %s!!!!\n\n",  winner==-1 ?"X":"O");
                break;
            }
            
        // check for a tie
        if (total_moves == (d*d))
            {
                printf("GAME ENDS IN A TIE!!!!\n\n");
                break;  
            }
            
        if(current_player == MACHINE_PLAYER)
        {
            //select the machine player's move
            score = minimax(board, current_player, true, 0);
            
            if (score != -1000)
            {
                row=best_row;
                col=best_col;
            }
        }
        else
        {
            // read in the human player's move            
            if (read_player_input(&row, &col, current_player) != 0)
                {
                    continue;
                }
        }
        
        // check boundaries
        if ((row>=0 && row<d) && (col>=0 && col<d))
        {
            // check board is empty
            if (board[row][col] == 0)
            {
                // put a piece on the board
                board[row][col] = current_player;

                // update the current_player
                current_player=current_player*-1;
                
                // increment move counter
                total_moves++;
            }
        }
    }   
}



int minimax(int hypothetical_board[DIM_MAX][DIM_MAX], int player, bool mymove, int depth) 
{
    int i, j, score;
    
    // if we have gone too deep, return;
    if (depth > MAX_DEPTH)
        return 0;
        
    // see if someone has won
    int winner = check_for_winner(hypothetical_board);
    if (winner != 0) 
    {
        return winner;
    }

    int move_row = -1;
    int move_col = -1;
    if (mymove)
        score = -2; //Losing moves are preferred to no move
    else
        score = 2;
        
    // For all possible locations (moves),
    for(i=0; i<d; i++)
    {
        for(j=0; j<d; j++)    
        {
        if(hypothetical_board[i][j] == 0) 
            {
                // If this is a legal move,
                hypothetical_board[i][j] = player; //Try the move
                int thisScore = minimax(hypothetical_board, -1*player, !mymove, depth+1);

                if (mymove)
                {  
                    // my move, so maximize the score          
                    if(thisScore > score) {
                        score = thisScore;
                        move_row = i;
                        move_col = j;
                    }
                }
                else
                {
                    // not my move, so minimize the score
                    if(thisScore < score) {
                        score = thisScore;
                        move_row = i;
                        move_col = j;
                    }
                }
                hypothetical_board[i][j] = 0;//Reset board after try
            }
        }
    }
    if(move_row == -1) return 0;  // no valid moves, so it is a tie.
    best_row = move_row;
    best_col = move_col;
    return score;
}



/**
 * read in a line from standard input, parsing as a grid location
 */
 
int read_player_input(int *r, int *c, int player)
{
    // prompt for move
    printf("Enter move for player %s (for example, b2):", player==-1 ?"X":"O");

    string loc = GetString();
    if (loc == NULL)
    {
        return 1;
    }
    
    // convert to integers
    *r = tolower(loc[0]) - 'a';
    *c = loc[1] - '0';

    return 0;
}

/**
 *  Parse the command line
 */
int parse_command_line(int argc, char *argv[])
{
    if (argc != 2)
    {
        // if not specified, assume a 3x3 board
        d=3;
    }
    else
    {
        // ensure valid dimensions
        d = atoi(argv[1]);
        if (d < DIM_MIN || d > DIM_MAX)
        {
            printf("Board must be between %i x %i and %i x %i, inclusive.\n",
                DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
            return 1;
        }
    }
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear()
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Initializes the game's board with tiles (numbered 1 through d*d - 1),
 * i.e., fills 2D array with values but does not actually print them).  
 */
void init()
{
    int i,j;
    
    // Set the board to be empty
    for (i=0;i<d;i++)
    {
        for(j=0;j<d;j++)
        {
            board[i][j] = 0;
        }
    }

    best_row=-1000;
    best_col=-1000;
}

/**
 * Prints the board in its current state.
 */
void draw()
{
    int i, j;
    
    // colorcode for red
    printf("\033[31m");
    printf("   ");
    for(j = 0; j < d; j++)
    {
        printf(" %d  ", j);
    }    
    printf("\n");
    for (i = 0; i < d; i++)
    {
        printf("\033[31m %c ", (char)'a'+i);
        for (j = 0; j < d; j++)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] == 1)
                {
                    printf("\033[0m O ");
                }
                else
                {
                    printf("\033[0m X ");
                }
            }
            else
            {
                printf("   ");
            }
            if(j<(d-1))
                printf("\033[31m|");
        }
        if (i<(d-1))
        {
            printf("\n\033[31m   ");
            for(j = 0; j < d-1; j++)
            {
                printf("---+");
            }
            printf("---");
        }
        printf("\033[0m\n");
    }
    printf("\n");
}

/**
 * check to see if someone has won, return the player number of the winner, 
 * or zero if no winner
 */
int check_for_winner(int b[DIM_MAX][DIM_MAX])
{
    // check to see if the board has been won
    int i,j;
    int prev, winner;
    
    for(i=0;i<d;i++)
    {
        // check each row
        prev = b[i][0];
        winner = prev;
        for(j=1;j<d;j++)
        {
            if (prev != b[i][j])
            {
                winner=0;
            }
        }
        if (winner != 0) return(winner);
        
        // check each column
        prev = b[0][i];
        winner = prev;
        for(j=1;j<d;j++)
        {
            if (prev != b[j][i])
            {
                winner=0;
            }
        }
        if (winner != 0) return(winner);
    }
    
    // check diagonals, but only if d is odd
    if ((d%2) == 1)
    {
        prev = b[0][0];
        winner = prev;
        for(j=1;j<d;j++)
        {
            if (prev != b[j][j])
            {
                winner=0;
            }
        }
        if (winner != 0) return(winner);  
        
        prev = b[0][d-1];
        winner = prev;
        for(j=1;j<d;j++)
        {
            if (prev != b[j][d-1-j])
            {
                winner=0;
            }
        }
        if (winner != 0) return(winner); 
    }
    return(0);
}