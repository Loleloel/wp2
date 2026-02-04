#include <stdio.h>
#include <unistd.h>

// enums
typedef enum { MON = 1, TUE, WED, THU, FRI, SAT, SUN } Weekday;
typedef enum { WEEK1 = 1, WEEK2, WEEK3, WEEK4, WEEK5 } Week;

// function declarations
void printWeekAndWeekday(Week, Weekday);
void clearBuffer();
void checkInput(Week, Weekday);

int main(void) {
  Week startWeek;
  Weekday startDay;

  scanf("%1d", &startWeek); // read the starting week
  clearBuffer();            // clear the buffer of any remaining chars
  scanf("%1d", &startDay);  // read the starting day

  checkInput(startWeek, startDay); // check for valid input
  printWeekAndWeekday(startWeek, startDay); // print the week and weekdays to console

  return 0;
}

// function to clear the input buffer
void clearBuffer() {
  while (getchar() != '\n') {
    continue;
  }
}

// function to validate input from the user
void checkInput(Week startWeek, Weekday startDay) {
  // if the startWeek is out of range, enter this if block
  if (1 > startWeek || 5 < startWeek) {
    // if the startDay is also out of range, enter this if block and print error message
    // after error message is printed, return
    if (1 > startDay || 7 < startDay) {
      puts("invalid");
      return;
    }

    // if the startDay is within range, print this error message and return
    puts("invalid week");
    return;
  } else if (1 > startDay || 7 < startDay) { // if startWeek is OK, but not startDay, enter this if-block and print error message
    puts("invalid day");
    return;
  }
}

// function to print the week and weekday to the console
void printWeekAndWeekday(Week startWeek, Weekday startDay) {
  // Loop over the weeks starting at the week number entered by the user
  for (Week w = startWeek; w <= WEEK5; w++) {
    // loop over the days of the week starting at the day number entered by the user
    for (Weekday d = startDay; d <= SUN; d++) {
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
      // reset startDay to start at the Monday when the next week begins
    }
    startDay = MON;
  }
}
