#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define RANDOM_MAX_VALUE 101 // since a number like 2200 % 100 == 0, we need to
                             // have the max set to 100 + 1, since 2200 % 101 == 100
                             // thus giving us a range of 0 - 100.

typedef struct listNode {
  int number;
  struct listNode *next, *prev;
} REGTYPE;

REGTYPE* randomList(void);

int main(void) {
  int num = 1;

  srandom(time(NULL)); // random seed

  REGTYPE *head = randomList(); // declare and assign a head of our linked list
  REGTYPE *currentNode = head; // declare and assign the currentNode to be a pointer to head

  // loop as long as currentNode has a valid value
  while (currentNode != NULL) {
    printf("Post number: %d : %d\n", num++, currentNode->number);
    currentNode = currentNode->next; // set currentNode to point to the next node
  }

  /* To free up the memory, loop for as long as currentNode has a valid value
   * after assigning it the pointer to the list's head again. */
  while ((currentNode = head) != NULL) {
    /* since we're freeing from the head first, assign the head the 
     * currentNode's pointer to the next node. */
    head = currentNode->next;
    free(currentNode); // free up currentNode (first iteration would free up the initial head)
    currentNode = NULL; // set currentNode to NULL to ensure the variable is no longer accessible
                        // since the while condition sets currentNode = head, this somewhat only 
                        // ensures the last node is nulled.
  }

  return 0;
}

/* Function to generate a linked list of size MAX
 * Values to the 'number' fields are randomly generated between 0 - 100.
 * Returns the address of the head node. */
REGTYPE* randomList(void) {
  REGTYPE *head = malloc(sizeof(*head)); // allocate memory to the head node

  if (!head) {
    puts("Error: Memory allocation failed.");
    exit(1);
  }

  head->number = random() % RANDOM_MAX_VALUE; // generate a random number and assign it to the head's number field
  head->next = head->prev = NULL; // init both the next, and the prev pointers of the head to NULL

  REGTYPE *currentNode = head; // create a new REGTYPE and assign it the head node

  /* Loop from 1 to MAX, in this case, the length of the linked list will be 5 nodes long.
   * We start at 1 since the head is created outside of the loop. */
  for (int i = 1; i < MAX; ++i) {
    /* Allocate memory for a new node, assign it to the currentNode's next field.
     * Then check if it is successful in doing so.
     * If unsuccessful, print an error message and exit program with exit code 1. */
    if (!(currentNode->next = malloc(sizeof(*currentNode)))) {
      puts("Error: Memory allocation failed.");
      exit(1);
    };

    currentNode->next->prev = currentNode; // set the next node's prev pointer to the current node
    currentNode = currentNode->next; // assign current node to be the next node
    currentNode->number = random() % RANDOM_MAX_VALUE; // give a value to the number field betweek 0-100
    currentNode->next = NULL; // set the next pointer to NULL
  }

  return head; // return the head only, as the other nodes are accessible through the head-node
}
