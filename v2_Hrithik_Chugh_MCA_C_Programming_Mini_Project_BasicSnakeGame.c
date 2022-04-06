// Changelog v2:

/*
    1. Included an option for the user to enter the speed of the snake/Refresh Rate of the game out of High or Low speeds.
    2. Addition of more fruits. Eating one of them changes the speed of the snake and eating the other restores the speed back to the selected speed. Also, one fruit gives double score addition than the other.
    3. New maze/boundary with teleportation capabilities.
    
*/

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
int x, y, f1x, f1y, f2x, f2y;
int kb;
int flag;
int score;
int actsp;
int ptx, pty;
int f;

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

    int speed;
    printf("\nSet speed of snake: 1: Slow or 2: High.\nEnter here: ");
    do
    {
        scanf("%d", &speed);
        if(speed < 1 || speed > 3)
            printf("\nInvalid input. Enter again: ");
    } while (speed < 1 || speed > 3);

    switch(speed)
    {
        case 1: actsp = 150000; break;
        case 2: actsp = 10000; break;
    }
    // Faster refresh rate => faster snake speed. In this code only. Not generally. This is an observation
    while ((getchar()) != '\n'); // Clearing the input buffer. Reads the buffer characters till the end and discards them (including newline in the last check when it becomes false) and using it after the “scanf()” statement clears the input buffer and allows the input in the desired container. The reason for this is an occupied Buffer. The “\n” character from the previous input (enter press which is required for scanf()) remains there in buffer and is read as the next input. Additional info at the end of this code.
    
    printf("\nPress Enter to start.");
    char in;
    scanf("%c", &in);

    char ch = '\n';
    if(in == ch)
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
    f1x = rand() % (l-2) + 1; // max_number = l-2 (as boundary lies on l-1), min_number = 1 (as boundary lies on 0) // rand() % (l-2) will give random numbers from 0 to l-3 and when we +1 to each value we get numbers from 1 to l-2.
    f1y = rand() % (b-2) + 1; // max_number = b-2 (as boundary lies on b-1), min_number = 1 (as boundary lies on 0) // rand() % (b-2) will give random numbers from 0 to b-3 and when we +1 to each value we get numbers from 1 to b-2.

    do // Making sure the positions of the two fruits do not coincide.
    {
        f2x = rand() % (l-2) + 1;
        f2y = rand() % (b-2) + 1;
    } while(f1x == f2x && f1y == f2y);
    
    score = 0;

    f = -1; // For the default value that the user enters. // variable f keeps in account which speed value of the snake is in use in the current call.

    printf("\e[?25l"); // To hide the cursor.    
 // printf("\e[?25h"); // To unhide the cursor.
}

// else if used in the following manner:
void draw()
{
    system("cls");
    
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < b; j++)
        {
            if(i == 0 && j <= b-6 || i == l-1 && j <= b-1 || j == 0 && i <= l-6 || j == b-1 && i <= l-1) // Boundary lies on these conditions. Open boundary for teleportation of the snake.
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
                    if(i == f1x && j == f1y) // Current coordinate equals 1st fruit coordinate.
                    {
                        printf("\033[1;33m"); // Set Output Color: Yellow
                        printf("-"); // 1st Fruit
                    }
                    else if(i == f2x && j == f2y) // Current coordinate equals 2nd fruit coordinate.
                    {
                        printf("\033[1;36m"); // Set Output Color: Cyan
                        printf("*"); // 2nd Fruit
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
    
    printf("\033[0m"); // Resets to the default color: White
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
    if(f == -1)
        usleep(actsp); // Controls the Refresh Rate/speed of refresh of the game. Due to while loop in main, the three functions are called again and again unless gameover == 1. This again and again calling happens so fast(according to the speed of a thread execution on a processor).
    if(f == 0) // 1st fruit eaten.
        usleep(150000); 
    if(f == 1) // 2nd fruit eaten.
        usleep(10000);

    switch(flag)
    {
        case 1: y--; break; // Moves the snake 1 position to the left.
        case 2: x--; break; // Moves the snake 1 position up.
        case 3: y++; break; // Moves the snake 1 position to the right.
        case 4: x++; break; // Moves the snake 1 position down.
    }

    if(x == f1x && y == f1y) // If at current instance, snake's position == fruit's position => The fruit is eaten by the snake => then increment the score by 10 and regenerate the fruit at another random location.
    {
        score += 10;
        f = 0;
        do
        {
            f1x = rand() % (l-2) + 1;
            f1y = rand() % (b-2) + 1;
        } while (x == f1x && y == f1y); // Making sure the positions of the fruit and the snake do not coincide at the time of generation of the fruit.
    }

    if(x == f2x && y == f2y) // If at current instance, snake's position == fruit's position => The fruit is eaten by the snake => then increment the score by 10 and regenerate the fruit at another random location.
    {
        score += 20;
        f = 1;
        do 
        {
            f2x = rand() % (l-2) + 1;
            f2y = rand() % (b-2) + 1; 
        } while(f1x == f2x && f1y == f2y); // Making sure the positions of the two fruits do not coincide.
    }

    // Logic used for the teleportation of the snake (For this maze only => this logic resembles the transpose of a matrix):
    int cx, cy; 
    // Current snake coordinates x and y are assigned to cx and cy respectively as temporary variables for the swap/transpose.
    cx = x;
    cy = y;
    if(x == -1 && y >= b-5 && y != b-1) // When the snake's coordinates equal the open boundary on the top side - 1. (Snake crosses the boundary on the top side.)
    {
        x = cy - l; // -l (Small L) shifts the current ordinate to the next abscissa using the fact that l = 20 and b = 40. b = 2*l so x = cy - (2-1)*l => This (--1) and --2 makes the transpose kind of teleportation in the maze possible with different l and b, i.e., not a square matrix.
        y = cx + 1; // -1 + 1 would make the current ordinate of the snake = 0, i.e., within the playable area. This and the above statement complete the transpose one way for the snake's movement.
        flag = 3; // After teleportation from the top side to the left side, setting the direction of snake towards right.
    }
    else if(y == -1 && x >= l-5 && x != l-1) // When the snake's coordinates equal the open boundary on the left side - 1. (Snake crosses the boundary on the left side.)
    {
        x = cy + 1; // -1 + 1 would make the current abscissa of the snake = 0, i.e., within the playable area. This and the below statement complete the transpose one way for the snake's movement.
        y = cx + l; // +l (Small L) shifts the current abscissa to the next ordinate using the fact that l = 20 and b = 40. b = 2*l so y = cx + (2-1)*l => This (--2) and --1 makes the transpose kind of teleportation in the maze possible with different l and b, i.e., not a square matrix.
        flag = 4; // After teleportation from the left side to the top side, setting the direction of snake towards down.
    }

    if(x == 0 && y <= b-6 || x == l-1 && y <= b-1 || y == 0 && x <= l-6 || y == b-1 && x <= l-1) // If snake's position == any position on the boundary => gameover => set gameover to 1 => while in main() becomes false and quits the game.
        gameover = 1;
}

// Reference: https://www.geeksforgeeks.org/snake-game-in-c/

/*

What is a buffer? 
A temporary storage area is called a buffer. All standard input and output devices contain an input and output buffer. In standard C/C++, streams
are buffered, for example in the case of standard input, when we press the key on the keyboard, it isn’t sent to your program, rather it is 
buffered by the operating system till the time is allotted to that program.

How does it affect Programming? 
On various occasions, you may need to clear the unwanted buffer so as to get the next input in the desired container and not in the buffer of the
previous variable. For example, in the case of C after encountering “scanf()”, if we need to input a character array or character, and in the case
of C++, after encountering the “cin” statement, we require to input a character array or a string, we require to clear the input buffer or else
the desired input is occupied by a buffer of the previous variable, not by the desired container. On pressing “Enter” (carriage return) on the
output screen after the first input, as the buffer of the previous variable was the space for a new container(as we didn’t clear it), the
program skips the following input of the container.

Reference: https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/

*/