#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Enums
typedef enum { NORTH, EAST, SOUTH, WEST } Directions;
typedef enum { MOVE, TURN } Action;

// Coordinates struct
typedef struct {
  int xPos;
  int yPos;
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

// main function
int main(void) {
  Robot robot = {-1, -1, NORTH};
  char instructions[10];

  readInitialCoords(&robot);
  readInstructionsInput(instructions);

  printf("Position before instructions: x: %d, y: %d\n\n", robot.xPos, robot.yPos);

  for (int i = 0; i < strlen(instructions); i++) {
    switch (instructions[i]) {
      case 'm':
        move(&robot);
        break;
      case 't':
        turn(&robot);
        break;
      default:
        puts("Mistake somewhere");
        exit(1);
    }

    sleep(1);
  }

  printf("\nFinal position: x: %d, y: %d\n", robot.xPos, robot.yPos);

  return 0;
}

// ---------------- ROBOT ACTIONS ----------------

// function to move the robot one step in the direction
// the robot is current facing
void move(Robot *robot) {
  switch (robot->directions) { // switch on the robot's current direction
    case NORTH: // robot is facing north
      robot->yPos += 1; // move robot 1 step up in the y axis
      puts("Moving north 1 step");
      break;
    case SOUTH: // robot is facing south
      robot->yPos -= 1; // move robot 1 step down in the y axis
      puts("Moving south 1 step");
      break;
    case EAST: // robot is facing east
      robot->xPos += 1; // move robot 1 step up in the x axis
      puts("Moving east 1 step");
      break;
    case WEST: // robot is facing west
      robot->xPos -= 1; // move robot 1 step down in the x axis
      puts("Moving west 1 step");
      break;
    default: // catchall if something goes terribly wrong
      puts("Error: Invalid direction");
      exit(1);
  }
}

// function to turn the robot 90 degrees clockwise
void turn(Robot *robot) {
  switch (robot->directions) { // switch on the robot's current direction
    case NORTH: // robot is facing north
      robot->directions++; // increment direction to the next direction as defined in the Directions enum
      puts("Turning east.");
      break;
    case EAST:
      robot->directions++; // increment direction to the next direction as defined in the Directions enum
      puts("Turning south.");
      break;
    case SOUTH:
      robot->directions++; // increment direction to the next direction as defined in the Directions enum
      puts("Turning west.");
      break;
    case WEST:
      robot->directions -= 3; // subtract 3 from direction to set it to the first defined direction in the Directions enum
      puts("Turning north.");
      break;
    default: // catchall if something goes terribly wrong
      puts("Something went wrong");
      exit(1);
  }
}

// ---------------- INPUT AND INPUT VALIDATION -------------------

// function to read the initial coordinates of the robot
// returns a struct with integer values stored to the x and y fields
void readInitialCoords(Robot *robot) {
  int inputOk;

  // prompt for the starting x coordinate until a valid coord is provided
  do {
    printf("Enter the starting x coordinate (0-99): ");
    inputOk = scanf("%3d", &robot->xPos);
    clearInputBuffer(); //  clear the input buffer of any remaining chars
  } while (!validateCoordInput(inputOk, robot->xPos)); // keep looping until a valid x coord is provided

  // prompt for the starting y coordinate until a valid one is provided
  do {
    printf("\nEnter the starting y coordinate (0-99): ");
    inputOk = scanf("%3d", &robot->yPos);
    clearInputBuffer(); //  clear the input buffer of any remaining chars
  } while (!validateCoordInput(inputOk, robot->yPos)); // keep looping until a valid y coord is provided
}

// function to read the instructions input
void readInstructionsInput(char *instructions) {
  do {
  printf("Please give the robot some instructions (m for more, t for turn): ");
  scanf("%10s", instructions); // read a 10 char string to the instructions variable

  } while (!validateInstructionsInput(instructions));
}

// function to validate the instructions input
// ensuring the input is 't' or 'm'
int validateInstructionsInput(char *instructions) {
  for (int i = 0; i < strlen(instructions); i++) {
    if (instructions[i] != 'm' && instructions[i] != 't') {
      puts("Invalid instruction in string. Please ensure the instructions contain only 'm' and 't'.");
      return 0;
    }
  }

  return 1;
}

// function to clear the input buffer until a newline char is encountered
void clearInputBuffer(void) {
  while (getchar() != '\n') {
    continue;
  }
}

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
