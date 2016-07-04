/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int rowa, int cola, int rowb, int colb);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // calculate total number of tiles
    int total = (d * d) - 1;
    
    // fill 2D array with tile values in descending order
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            board[row][col] = total;
            total--;
        }
    }
    
    // swap tiles 1 and 2 for boards with odd number of game tiles
    if (d % 2 == 0)
    {
        swap((d - 1), (d - 2), (d - 1), (d - 3));
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n");
    for(int row = 0; row < d; row++)
    {
        printf(" ");
        for(int col = 0; col < d; col++)
        {
            if(board[row][col] > 9)
            {
                printf(" %i", board[row][col]);
            }
            else if(board[row][col] < 10 && board[row][col] > 0)
            {
                printf("  %i", board[row][col]);
            }
            else if(board[row][col] == 0)
            {
                printf("  _");
            }
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // find blank tile in array
    for(int row = 0; row < d; row++)
    {
        for(int col = 0; col < d; col++)
        {
            if(board[row][col] == 0)
            {
                // check tiles bordering blank tile and swap if there is a match
                if((row - 1) > -1 && tile == board[(row - 1)][col])
                {
                    swap(row, col, (row - 1), col);
                    return true;
                }
                else if((row + 1) < d && tile == board[(row + 1)][col])
                {
                    swap(row, col, (row + 1), col);
                    return true;
                }
                else if((col - 1) > -1 && tile == board[(row)][(col - 1)])
                {
                    swap(row, col, row, (col - 1));
                    return true;
                }
                else if((col + 1) < d && tile == board[(row)][(col + 1)])
                {
                    swap(row, col, row, (col + 1));
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int tilecount = 1;
    
    for(int row = 0; row < d; row++)
    {
        for(int col = 0; col < d; col++, tilecount++)
        {
            if(board[row][col] != tilecount)
            {
                while (tilecount < d * d)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Swaps values within 2D board array
 */
void swap(int rowa, int cola, int rowb, int colb)
{
    int temp = board[rowa][cola];
    board[rowa][cola] = board[rowb][colb];
    board[rowb][colb] = temp;
}