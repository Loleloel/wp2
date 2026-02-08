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
int validateCoordInput(const int inputOk, const int coord);
int validateInstructionsInput(char *);
void clearInputBuffer(void);
void peekInputBuffer(void);
