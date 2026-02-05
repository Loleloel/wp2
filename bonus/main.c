#include <stdio.h>
#include <unistd.h>

// enums
typedef enum { WEEK_1 = 1, WEEK_2, WEEK_3, WEEK_4, WEEK_5 } Week;
typedef enum { MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY } Day;

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
  if (WEEK_1 > startWeek || WEEK_5 < startWeek) {
    // if the startDay is also out of range, enter this if block and print error message
    // after error message is printed, return
    if (MONDAY > startDay || SUNDAY < startDay) {
      puts("invalid");
      return 0;
    }

    // if the startDay is within range, print this error message and return
    puts("invalid week");
    return 0;
  } else if (MONDAY > startDay || SUNDAY < startDay) { // if startWeek is OK, but not startDay, enter this if-block and print error message
    puts("invalid day");
    return 0;
  }

  return 1;
}

// function to print the week and weekday to the console
void printWeekAndWeekday(Week week, Day day) {
  // Loop over the weeks starting at the week number entered by the user
  // stopping at the last element in the enum, in this case WEEK5
  // since week already is an int, we don't need any 'int i = 0' in the for loop
  // but instead can use it as the control variable
  for (; week <= WEEK_5; week++) {
    // loop over the days of the week starting at the day number entered by the user
    for (; day <= SUNDAY; day++) {
      printf("Week %d, ", week);

      // switch-case to decide what to print to console
      switch (day) {
      case MONDAY:
        puts("Monday");
        break;
      case TUESDAY:
        puts("Tuesday");
        break;
      case WEDNESDAY:
        puts("Wednesday");
        break;
      case THURSDAY:
        puts("Thursday");
        break;
      case FRIDAY:
        puts("Friday");
        break;
      case SATURDAY:
        puts("Saturday");
        break;
      case SUNDAY:
        puts("Sunday");
        break;
      default:
        puts("something went wrong");
        return;
      }

      sleep(1); // add 1 second delay
    }

    // reset day to start at the Monday when the next week begins
    day = MONDAY;
  }
}
