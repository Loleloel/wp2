#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GRID_SIZE 100

// Enums
typedef enum { NORTH, EAST, SOUTH, WEST } Directions;

// Coordinates struct
typedef struct {
  // xPos and yPos are coordinate representations
  // isAlive is a flag to track the robot being
  // within bounds or not
  int xPos, yPos, isAlive;
  Directions directions;
} Robot;

// Function declarations
void move(Robot *robot);
void turn(Robot *robot);
void readInitialCoords(Robot *robot);
void readInstructionsInput(char *);
int validateInstructionsInput(char *);
int validateCoordInput(int inputOk, int coord);
void clearInputBuffer(void);
void peekInputBuffer(void);
void drawGrid(Robot *robot);
void drawRobot(int robotDirection);

// main function
int main(void) {
  Robot robot = {-1, -1};
  char *currentInstruction;
  char instructions[11];

  while (1) {
    readInitialCoords(&robot);
    readInstructionsInput(instructions);
    currentInstruction = &instructions[0];

    // init the robot's alive and direction at the start of the loop
    robot.isAlive = 1;
    robot.directions = NORTH;

    // iterate over the instructions
    do {
      drawGrid(&robot);
      // check the value of instructions[i]
      switch (*currentInstruction) {
      case 'm': // move robot in the direction it's currently facing
        move(&robot);
        break;
      case 't': // turn robot 90 degrees clockwise
        turn(&robot);
        break;
      default: // catchall in case of terrible terrible things
        printf("%c\n", *currentInstruction);
        exit(1); // exit program with exit code 1
      }
      
      sleep(1); // 1 second delay
    } while (*++currentInstruction && robot.isAlive);

    // if the robot died (went out of bounds), print a message to the user
    if (!robot.isAlive) {
      puts("The robot fell off the map, it's extremely dead.\n");
    } else { // otherwise, print the current coords of the robot
      printf("\nFinal position: x: %d, y: %d\n", robot.xPos, robot.yPos);
    }

    // clear the input buffer to prepare for the next round of inputs
    clearInputBuffer();
  }

  return 0;
}

// ---------------- ROBOT ACTIONS ----------------

// function to move the robot one step in the direction
// the robot is current facing
void move(Robot *robot) {
  switch (robot->directions) { // switch on the robot's current direction
  case NORTH:                  // robot is facing north
    robot->yPos--;             // move robot 1 step up in the y axis
    robot->isAlive = 0 <= robot->yPos;
    break;
  case SOUTH:      // robot is facing south
    robot->yPos++; // move robot 1 step down in the y axis
    robot->isAlive = 100 > robot->yPos;
    break;
  case EAST:       // robot is facing east
    robot->xPos++; // move robot 1 step up in the x axis
    robot->isAlive = 100 > robot->xPos;
    break;
  case WEST:       // robot is facing west
    robot->xPos--; // move robot 1 step down in the x axis
    robot->isAlive = 0 <= robot->xPos;
    break;
  default: // catchall if something goes terribly wrong
    puts("Error: Invalid direction");
    exit(1);
  }
}

// function to turn the robot 90 degrees clockwise
void turn(Robot *robot) {
  switch (robot->directions) { // switch on the robot's current direction
  case NORTH:                  // robot is facing north
    robot->directions++; // increment direction to the next direction as defined
                         // in the Directions enum
    break;
  case EAST:
    robot->directions++; // increment direction to the next direction as defined
                         // in the Directions enum
    break;
  case SOUTH:
    robot->directions++; // increment direction to the next direction as defined
                         // in the Directions enum
    break;
  case WEST:
    robot->directions -= 3; // subtract 3 from direction to set it to the first
                            // defined direction in the Directions enum
    break;
  default: // catchall if something goes terribly wrong
    puts("Something went wrong");
    exit(1);
  }
}

// ---------------- INPUT READING -------------------

// function to read the initial coordinates of the robot
// returns a struct with integer values stored to the x and y fields
void readInitialCoords(Robot *robot) {
  int inputOk;
  char ch;

  // prompt for the starting x coordinate until a valid coord is provided
  do {
    printf("Enter the starting x coordinate (0-99) or 'q' to exit: ");
    inputOk = scanf("%3d", &robot->xPos);

    /* If a user entered a char, then scanf will return 0.
     * In these cases, scanf does not consume the char from stdin
     * so we can take a peek with getchar() and ungetc(char, stream).
     * The exact implementation is shown further down in the
     * peekInputBuffer() function.*/

    if (!inputOk) peekInputBuffer(); // peek the input buffer if input was not OK
    clearInputBuffer(); //  clear the input buffer of any remaining chars
  } while (!validateCoordInput(
      inputOk, robot->xPos)); // keep looping until a valid x coord is provided

  // prompt for the starting y coordinate until a valid one is provided
  do {
    printf("\nEnter the starting y coordinate (0-99) or 'q' to exit: ");
    inputOk = scanf("%3d", &robot->yPos);

    if (!inputOk) peekInputBuffer(); // peek the input buffer if input was not OK
    clearInputBuffer(); //  clear the input buffer of any remaining chars
  } while (!validateCoordInput(
      inputOk, robot->yPos)); // keep looping until a valid y coord is provided
}

// function to read the instructions input
void readInstructionsInput(char *instructions) {
  do {
    printf("Please give the robot some instructions (m for more, t for turn) or 'q' to exit: ");
    scanf("%10s", instructions); // read a 10 char string to the instructions variable
                                 // the instructions string does have a size of 11 to ensure the
                                 // null terminator being included.
  } while (!validateInstructionsInput(instructions));
}

// ---------------- INPUT VALIDATION -------------------

// function to validate the coordinate input.
// validation on both input type and the range of the input.
int validateCoordInput(int inputOk, int coord) {
  if (!inputOk) { // input is not an integer
    puts("Invalid input. Please ensure the coordinate is an integer between 0 "
         "and 99.");
    return 0;
  } else if (0 > coord || 99 < coord) { // input is out of range
    puts("Coordinate out of range. Please ensure the coordinate is between 0 "
         "and 99.");
    return 0;
  }

  return 1;
}

// function to validate the instructions input
// ensuring the input is 't' or 'm'
// Returns either 0 (false) if invalid instructions are passed
// or 1 (true) if input is valid
int validateInstructionsInput(char *instructions) {
  // use a pointer to the first element in the instructions
  char *ptrInstruction = &instructions[0];

  // if 'q' == instructions[0], then print exit message to user
  if ('q' == instructions[0]) {
    puts("Exiting...");
    exit(0); // exit program with exit code 0
  }

  // iterate over the instructions one at a time
  do {
    // ensure the instructions are valid ('m' = move, 't' = turn)
    if (*ptrInstruction != 'm' && *ptrInstruction != 't') {
      puts("Invalid instruction in string. Please ensure the instructions "
           "contain only 'm' and 't'.");
      return 0; // if invalid, return 0 (false)
    }
  } while (*++ptrInstruction); // while the pointer points to a valid value
                               // null terminator is always present at the end
                               // as scanf inserts it at the end of the read string
  return 1;
}

// ---------------- GRID DRAWING -------------------

// function to print the grid to console, including the robot's current position
void drawGrid(Robot *robot) {
  system("clear"); // clear the console output

  // iterate over all rows in the grid
  for (int row = 0; row < GRID_SIZE; row++) {
    // iterate over all cols in the grid
    for (int col = 0; col < GRID_SIZE; col++) {
      // if the robot's x and y position matches the values
      // of col and row, then print an 'o' to represent the robot
      if (robot->xPos == col && robot->yPos == row) {
        // print the robot to the grid
        drawRobot(robot->directions);
      } else {
        putchar('.'); // put a dot to represent the grid where the robot is not
      }
    }
    putchar('\n');
  }
}

// function to draw the robot and its current direction to the grid
void drawRobot(int robotDirection) {
  // represent the robot with different "arrow-like" symbols
  // to show the robot's current facing direction
  switch (robotDirection) {
          case NORTH: // put a '^' to act as arrow up
            putchar('^');
            break;
          case EAST: // '>' to act as arrow right
            putchar('>');
            break;
          case SOUTH: // 'v' to act as arrow down
            putchar('v');
            break;
          case WEST: // '<' to act as arrow left
            putchar('<');
            break;
        }
}
// ---------------- UTILS -------------------

// function to clear the input buffer until a newline char is encountered
void clearInputBuffer(void) {
  int ch;
  while ((ch = getchar() != '\n' && ch != EOF)) {
    continue;
  }
}

// function to peek the input buffer (stdin)
// if the char == 'q', we exit the program with exit code 0
// else, we push ch back into the input buffer
void peekInputBuffer(void) {
  int ch = getchar();

  if ('q' == ch) {
    puts("Exiting...");
    exit(0); // exit the program with code 0
  } else {
    ungetc(ch, stdin); // push ch back into stdin
  }
}
