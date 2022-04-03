#include<stdio.h> // Standard I/O contains printf(), scanf(), getchar(), etc.
#include<stdlib.h> // Standard Library contains system(), rand(), etc.
#include<unistd.h> // Contains sleep(), usleep(), etc.
#include<conio.h> // Console I/O contains getch(), kbhit(), etc.

void setup(); // Initialisation function: Initialises the variables.
void draw();  // Output function: Outputs the boundary, current snake position, current fruit position, empty spaces inside the boundary, current score, and an instruction to the user to exit the game.
void input(); // Input function: Listens for any key press - for the change of direction of movement of the snake. Initial Use: To start the movement of the snake in the specified direction by pressing the appropriate key. 
void logic(); // Logic function: Contains all the logic used. Explained in the function itself.

// Global variables used to avoid the use of pointers or parameters and return values.
// Escape Sequences are used for the cursor hiding and colors of the output.

int gameover;
int l, b;
int x, y, fx, fy;
int kb;
int flag;
int score;

void main() // Driver Code
{
    system("cls"); // System call to clear the screen. system() is used to invoke an operating system command from a C/C++ program. Using system(), we can execute any command that can run on terminal if operating system allows.
    
    printf("\033[1;35m"); // Set Output Color: Purple
    printf("\n\n\t\t\t\t    !!!!!!!!!!!!!!!!!!!!!!\n");
    printf("\t\t\t\t       Basic Snake Game\n");
    printf("\t\t\t\t    !!!!!!!!!!!!!!!!!!!!!!\n");

    printf("\033[1;36m"); // Set Output Color: Cyan

    printf("\n\nAim: To make the snake eat more and more fruits to increase the score. 1 fruit eaten => +10 Score.");

    printf("\n\nRule: Getting the snake to go out of the boundary => GameOver.");

    printf("\n\nControls: \n1) Press the following keys to change the snake's direction at any instant: \n   'a': Left \n   'w': Up \n   'd': Right \n   's': Down");
    printf("\n2) Initially press any of the above four keys to start the movement of the snake in the desired direction.");
    printf("\n3) The snake moves in the same direction until it's direction is changed using the above keys.\n");
    
    printf("\nVisuals:\n");
    printf("\033[1;31m"); // Set Output Color: Red
    printf("1) Snake: 0\n");
    printf("\033[1;33m"); // Set Output Color: Yellow
    printf("2) Fruit: -\n");
    printf("\033[1;32m"); // Set Output Color: Green
    printf("3) Boundary: +\n");

    printf("\033[1;36m"); // Set Output Color: Cyan
    printf("\nPress Enter to start.");
    char ch = '\n';
    if(getchar() == ch)
    {
        system("cls");
        printf("\n\nBasic Snake Game\n\n");
        printf("Loading...\n\n");
        sleep(2); // For simulating "Loading Screen" feel. It allows for the current thread execution to wait for the set amount of time passed as the parameter(in seconds).

        setup(); // Called once for initialisation.

        while(gameover == 0) // These 3 functions are run one after the other again and again to:
        {
            draw(); // Output current state after clearing screen at every call. Clearing screen acts as refresh.
            input(); // Taking input for snake's direction at every call.
            logic(); // Using input from the above call to apply the logic at this call.
        }
    }
        printf("\n\n");
}

void setup()
{
    gameover = 0;

    l = 20; 
    b = 40;

    x = l / 2;
    y = b / 2;

    // Generating the random number (fruit) within the boundary: rand() % (max_number - minimum_number + 1) + minimum_number
    fx = rand() % (l-2) + 1; // max_number = l-2 (as boundary lies on l-1), min_number = 1 (as boundary lies on 0) // rand() % (l-2) will give random numbers from 0 to l-3 and when we +1 to each value we get numbers from 1 to l-2.
    fy = rand() % (b-2) + 1; // max_number = b-2 (as boundary lies on b-1), min_number = 1 (as boundary lies on 0) // rand() % (b-2) will give random numbers from 0 to b-3 and when we +1 to each value we get numbers from 1 to b-2.
    
    score = 0;

    printf("\e[?25l"); // To hide the cursor in the calling terminal.     
 // printf("\e[?25h"); // To hide the cursor in the calling terminal.    
}

// else if used in the following manner:
void draw()
{
    system("cls");
    
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < b; j++)
        {
            if(i == 0 || i == l-1 || j == 0 || j == b-1) // Boundary lies on these conditions.
            {
                printf("\033[1;32m"); // Set Output Color: Green
                printf("+"); // Boundary
            }
            else
            {
                if(i == x && j == y) // Current coordinate equals current snake coordinate.
                {
                    printf("\033[1;31m"); // Set Output Color: Red
                    printf("0"); // Snake
                }
                else
                {
                    if(i == fx && j == fy) // Current coordinate equals current fruit coordinate.
                    {
                        printf("\033[1;33m"); // Set Output Color: Yellow
                        printf("-"); // Fruit
                    }
                    else
                    {
                        printf(" "); // Blank Spaces in between the boundary.
                    }
                }
            }
        }
        printf("\n");
    }
    
    printf("\033[0m"); // Resets to the default color: White and to the default font characteristics.
    printf("\nScore = %d\n", score);
    printf("Press 'x' to quit the game.");
}

void input()
{
    if(kbhit()) // This function listens for any key press. Returns 0 if no key is pressed. Returns 1 if any key is pressed. The function is listening to the key hit at all times - even when WE THINK any of the other functions is in execution. Ans. (I think due to) Very fast processing and therefore the fast execution of while loop. Sleep slows down execution which can be used to simulate (by sleeping for larger amounts of time depending upon the processor's single thread's execution speed) the non-working of the keys at some instant.
    {
        switch(getch()) // Inputs the above pressed key. getch() is used as it doesn't print the charater (while inputting) that is inputted on the console screen. - Why doesn't the program stop here due to getch() to wait for the input? Ans. I think it checks the input stream for any characters and due to character press for input one character remains in the input stream which it takes as this is the only input in the whole program after pressing enter to start the main loop. And, until another key(character) is pressed(to input it in getch() from the input stream) we don't go inside the switch statement due to the if statement and the kbhit(). So, as soon as and only when a key is pressed, it goes into the input stream and the if statement is now true as kbhit() returns true and therefore the character is inputted to getch() from the input stream.
        {
            case 'a': flag = 1; break;
            case 'w': flag = 2; break;
            case 'd': flag = 3; break;
            case 's': flag = 4; break;
            case 'x': gameover = 1; break; 
        }
    }
}

void logic()
{
    sleep(0.1); // Controls the Refresh Rate/speed of refresh of the game. Due to while loop in main, the three functions are called again and again unless gameover == 1. This again and again calling happens so fast(according to the speed of a thread execution on a processor).
    switch(flag)
    {
        case 1: y--; break; // Moves the snake 1 position to the left.
        case 2: x--; break; // Moves the snake 1 position up.
        case 3: y++; break; // Moves the snake 1 position to the right.
        case 4: x++; break; // Moves the snake 1 position down.
    }

    if(x == fx && y == fy) // If at current instance, snake's position == fruit's position => The fruit is eaten by the snake => then increment the score by 10 and regenerate the fruit at another random location.
    {
        score += 10;
        fx = rand() % (l-2) + 1;
        fy = rand() % (b-2) + 1;
    }

    if(x == 0 || x == l-1 || y == 0 || y == b-1) // If snake's position == any position on the boundary => gameover => set gameover to 1 => while in main() becomes false and quits the game.
        gameover = 1;
}

// Reference: https://www.geeksforgeeks.org/snake-game-in-c/