#include "main.h"

// main function
int main(void) {
  Robot robot = {-1, -1, 1, NORTH};
  char instructions[11];

  while (1) {
    readInitialCoords(&robot); // read coordinates from the user
    readInstructionsInput(
        instructions); // read instructions to the robot from the user

    // iterate over each instruction with a pointer to each
    // char in the string of instructions
    for (char *p = instructions; *p && robot.isAlive; p++) {
      // move or turn the robot based on the current instruction
      if ('m' == *p)
        move(&robot);
      else if ('t' == *p)
        turn(&robot);

      sleep(1); // 1 second delay
    }

    // if the robot died (went out of bounds), print a message to the user
    if (!robot.isAlive) {
      puts("The robot fell off the map, it's extremely dead.\n");
    } else { // otherwise, print the current coords of the robot
      printf("\nFinal position: x: %d, y: %d\n", robot.xPos, robot.yPos);
    }

    // clear the input buffer to prepare for the next round of inputs
    clearInputBuffer();

    // init the isAlive fields, as well as the directions field of the robot
    robot.isAlive = 1;
    robot.directions = NORTH;
  }

  return 0;
}

// ---------------- ROBOT ACTIONS ----------------

/* Function to move the robot one step in the direction
 * the robot is current facing.
 * Takes the robot's address as an argument. */
void move(Robot *robot) {
  switch (robot->directions) { // switch on the robot's current direction
  case NORTH:                  // robot is facing north
    robot->yPos--;             // move robot 1 step up in the y axis
    robot->isAlive = 0 <= robot->yPos;
    puts("Moving one step north.");
    break;
  case SOUTH:      // robot is facing south
    robot->yPos++; // move robot 1 step down in the y axis
    robot->isAlive = 100 > robot->yPos;
    puts("Moving one step south.");
    break;
  case EAST:       // robot is facing east
    robot->xPos++; // move robot 1 step up in the x axis
    robot->isAlive = 100 > robot->xPos;
    puts("Moving one step east.");
    break;
  case WEST:       // robot is facing west
    robot->xPos--; // move robot 1 step down in the x axis
    robot->isAlive = 0 <= robot->xPos;
    puts("Moving one step west.");
    break;
  default: // catchall if something goes terribly wrong
    puts("Error: Invalid direction");
    exit(1);
  }
}

/* Function to turn the robot 90 degrees clockwise
 * by incrementing the value.
 * Wrap-around when the robot's directions is WEST by
 * subtracting 3 to set it to NORTH again.
 * Takes the address of the robot as an argument. */
void turn(Robot *robot) {
  switch (robot->directions) { // switch on the robot's current direction
  case NORTH:                  // robot is facing north
    robot->directions++; // increment direction to the next direction as defined
                         // in the Directions enum
    puts("Turning to the east.");
    break;
  case EAST:
    robot->directions++; // increment direction to the next direction as defined
                         // in the Directions enum
    puts("Turning to the south.");
    break;
  case SOUTH:
    robot->directions++; // increment direction to the next direction as defined
                         // in the Directions enum
    puts("Turning to the west.");
    break;
  case WEST:
    robot->directions -= 3; // subtract 3 from direction to set it to the first
                            // defined direction in the Directions enum
    puts("Turning to the north.");
    break;
  default: // catchall if something goes terribly wrong
    puts("Something went wrong");
    exit(1);
  }
}

// ---------------- INPUT READING -------------------

/* Function to read the initial coordinates of the robot.
 * Sets the xPos and yPos fields with coords between 0-99
 * entered by a user.
 * If a user enters 'q', the program exits with exit code 0.
 * Takes the address of the robot as an argument. */
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

    if (!inputOk)
      peekInputBuffer(); // peek the input buffer if input was not OK
    clearInputBuffer();  //  clear the input buffer of any remaining chars
  } while (!validateCoordInput(
      inputOk, robot->xPos)); // keep looping until a valid x coord is provided

  // prompt for the starting y coordinate until a valid one is provided
  do {
    printf("\nEnter the starting y coordinate (0-99) or 'q' to exit: ");
    inputOk = scanf("%3d", &robot->yPos);

    if (!inputOk)
      peekInputBuffer(); // peek the input buffer if input was not OK
    clearInputBuffer();  //  clear the input buffer of any remaining chars
  } while (!validateCoordInput(
      inputOk, robot->yPos)); // keep looping until a valid y coord is provided
}

/* Function to read the instructions to the robot from the user.
 * The user will enter a string containing only 'm' and 't'.
 * As with the coordinates, 'q' is also acceptable, but exits the
 * program with exit code 0.
 * 'm' will instruct the robot to move, 't' will instruct the robot
 * to turn. */
void readInstructionsInput(char *instructions) {
  do {
    printf("Please give the robot some instructions (m for more, t for turn) "
           "or 'q' to exit: ");
    scanf("%10s",
          instructions); // read a 10 char string to the instructions variable
                         // the instructions string does have a size of 11 to
                         // ensure the null terminator being included.
  } while (!validateInstructionsInput(instructions));
}

// ---------------- INPUT VALIDATION -------------------

/* Function to validate the coordinate input.
 * Both the input type and the range is validated to ensure
 * the input entered by the user is OK. */
int validateCoordInput(const int inputOk, const int coord) {
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

/* Function to validate the instructions input.
 * We check if the instructions string contains valid
 * instruction letters ('m' and 't') or any 'q' to exit
 * the program.
 * Returns 0 (false) if invalid instructions are passed.
 * Returns 1 (true) if the instructions are valid.*/
int validateInstructionsInput(char *instructions) {
  // use a pointer to the first element in the instructions

  // iterate over the instructions one at a time using a pointer
  for (char *p = instructions; *p; p++) {
    // first check if the instruction == 'q', and if it does, exit the program.
    // if not, check if the instruction is valid ('m' = move, 't' = turn)
    switch (*p) {
    case 'q': // exit program
      puts("Exiting...");
      exit(0);
    case 'm': // move instruction, fallthrough to case 't'
    case 't': // turn instruction, continue loop
      continue;
    default: // invalid input, print error message and return 0 (false)
      puts("Error: Invalid instruction in string.");
      puts("Please ensure the instructions contain only 'm' and 't'. ('q' to "
           "quit)\n");
      return 0;
    }
  }

  return 1; // return 1 (true) if all is well
}

// ---------------- UTILS -------------------

// function to clear the input buffer until a newline char is encountered
void clearInputBuffer(void) {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    continue;
  }
}

/* Function to peek the input buffer (stdin).
 * Used with the readInitialCoords as the scanf expects
 * a decimal. Since the user can enter 'q' to exit the program,
 * we must peek the buffer to check this, as scanf doesn't
 * consume from stdin if invalid input is passed.
 * If the char in stdin == 'q', exit the program with exit code 0.
 * If not, push the fetched char back to stdin to avoid
 * unwanted behavior. */
void peekInputBuffer(void) {
  int ch = getchar();

  if ('q' == ch) {
    puts("Exiting...");
    exit(0); // exit the program with code 0
  } else {
    ungetc(ch, stdin); // push ch back into stdin
  }
}
