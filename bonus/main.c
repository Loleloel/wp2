#include <stdio.h>
#include <unistd.h>

// enums
typedef enum { WEEK1 = 1, WEEK2, WEEK3, WEEK4, WEEK5 } Week;
typedef enum { MON = 1, TUE, WED, THU, FRI, SAT, SUN } Day;

// function declarations
void printWeekAndWeekday(Week, Day);
void clearBuffer();
int checkInput(Week, Day);

int main(void) {
  Week startWeek;
  Day startDay;

  /* We can read a decimal directly into our
   * startWeek and startDay variables as they
   * are both enums, and the values of an enum
   * are by default ints */

  scanf("%d", &startWeek); // read the starting week
  clearBuffer();            // clear the buffer of any remaining chars
  scanf("%d", &startDay);  // read the starting day

  if (checkInput(startWeek, startDay)) { // check for valid input
    printWeekAndWeekday(startWeek, startDay); // print the week and weekdays to console
  }

  return 0;
}

// function to clear the input buffer
void clearBuffer() {
  while (getchar() != '\n') {
    continue;
  }
}

// function to validate input from the user
// returns 0 (false) if input is invalid, else 1 (true)
int checkInput(Week startWeek, Day startDay) {
  // if the startWeek is out of range, enter this if block
  if (1 > startWeek || 5 < startWeek) {
    // if the startDay is also out of range, enter this if block and print error message
    // after error message is printed, return
    if (1 > startDay || 7 < startDay) {
      puts("invalid");
      return 0;
    }

    // if the startDay is within range, print this error message and return
    puts("invalid week");
    return 0;
  } else if (1 > startDay || 7 < startDay) { // if startWeek is OK, but not startDay, enter this if-block and print error message
    puts("invalid day");
    return 0;
  }

  return 1;
}

// function to print the week and weekday to the console
void printWeekAndWeekday(Week startWeek, Day day) {
  // Loop over the weeks starting at the week number entered by the user
  for (Week w = startWeek; w <= WEEK5; w++) {
    // loop over the days of the week starting at the day number entered by the user
    for (Day d = day; d <= SUN; d++) {
      printf("Week %d, ", w);

      // switch-case to decide what to print to console
      switch (d) {
      case MON:
        puts("Monday");
        break;
      case TUE:
        puts("Tuesday");
        break;
      case WED:
        puts("Wednesday");
        break;
      case THU:
        puts("Thursday");
        break;
      case FRI:
        puts("Friday");
        break;
      case SAT:
        puts("Saturday");
        break;
      case SUN:
        puts("Sunday");
        break;
      default:
        puts("something went wrong");
        return;
      }

      sleep(1); // add 1 second delay
    }

    // reset startDay to start at the Monday when the next week begins
    day = MON;
  }
}
