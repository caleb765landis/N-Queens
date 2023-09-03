// main.cpp
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <stdlib.h> // abs()
#include <cstdlib> // std::isDigit()

// function prototypes
bool isNumber(std::string string);
void arrange(int n);
bool checkConflicts(std::stack<int> stack, int filled);
void printQueens(std::stack<int> stack, int n);

int main() {
  bool keepGoing = true;
  int n;
  int Nmax = 20;

  // clear screen to start the program
  system("clear");
  while (keepGoing) {
    // get N number of queens
    std::cout << "Please specify number (N) of queens where 3 < N <= 20: ";
    std::cin.clear();
    std::string tempstring;
    std::cin >> tempstring;

    // check if user input is a number
    // if all characters in string are a number, convert string to int, set n = int
    if (isNumber(tempstring)) {
      std::stringstream ss;
      ss << tempstring;
      ss >> n;

      // make sure N is in acceptable range
      if (n < 4) {
        std::cout << "N must be greater than 3." << std::endl;
      } else if (n > Nmax) {
        std::cout << "N must be less than or equal to " << Nmax << "." << std::endl;

      // if N is in acceptable range, arrange queens in an order where there is no conflict
      // 3 < n <= Nmax
      // also end main loop
      } else {
        // arrange(int n) orders the queens into positions where there are no conflicts
        // also prints queen positions
        arrange(n);
        keepGoing = false;
      } // end if N is in acceptable range

    // if user input isn't a number, restart loop
    } else {
      std::cout << "N must be an integer." << std::endl;
      std::cin.clear();
      std::cin.ignore();
    } // end if user input is a number

    //spacing for neatness
    std::cout << std::endl;
  } // end while
} // end main

// checks if all characters in given string are numbers
// returns true if all characters are numbers
bool isNumber(std::string string) {
  // go through each character in string
  for (int i = 0; i < string.length(); i++) {
    // if current character in string is not a digit return false
    if (std::isdigit(string.at(i)) == 0) {
      return false;
    } // end if
  } // end for
  return true;
} // end isNumber()

// arrange(int n) orders the queens into positions where there are no conflicts
// also prints queen positions
void arrange(int n) {
  // each int pushed to stack is column #
  // first item in stack is in first row, second item in second row, etc.
  std::stack<int> stack;
  int filled = 0;
  bool keepArranging = true;

  // push first queen in column 1
  stack.push(1);

  // loop until all queens are arranged in a way where there are no conflicts
  while (keepArranging) {
    // check if top queen is in conflict
    bool conflicts = checkConflicts(stack, filled);

    // if there are no conflicts with queens
    if (conflicts == false) {
      filled = filled + 1;
      if (filled == n) {
        keepArranging = false;
      } else {
        stack.push(1);
      } // end if filled == n

    // if there is conflict and there is room for top queen to shift right
    // shift that queen to the right
    } else if ((conflicts == true) && (stack.top() < n)) {
      // shift queen
      stack.top() = stack.top() + 1;

    // if there is conflict and there is no room for top queen to shift right
    // backtrack until there is a queen with room to shift and shift that queen
    } else if ((conflicts == true) && (stack.top() == n)) {
      bool keepPopping = true;

      while (keepPopping) {
        // if queen can be shifted
        if (stack.top() < n) {
          // stop popping
          keepPopping = false;
          // and shift queen
          stack.top() = stack.top() + 1;

        } else {
          stack.pop();
          filled = filled - 1;
        }// end if queen can be shifted
      } // end while keepPopping
    } // end if conflicts

    //std::cout << " row: " << filled + 1 << " column: " << stack.top() << std::endl;
    //printQueens(stack,n);
  } // end while keepArranging

  // once all queens are arranged properly, print their coordinates and board
  printQueens(stack, n);
} // end arrange

// checks if top queen in stack is in conflict
bool checkConflicts(std::stack<int> stack, int filled) {
  // make a copy of stack to check all other queens against origingal's top queen
  std::stack<int> stackCopy = stack;
  stackCopy.pop();
  int q1row = stack.size();
  int q1col = stack.top();
  // assume there is no conflict
  bool conflict = false;
  bool keepChecking = true;

  // go through each queen in stackCopy
  // check if there is a conflict with top queen in stack
  while (keepChecking) {
    if (stackCopy.empty() || filled == 0) {
      keepChecking = false;

    } else {
      int q2row = stackCopy.size();
      int q2col = stackCopy.top();
      int rowDifference = abs(q1row - q2row);
      int colDifference = abs(q1col - q2col);

      // queens cannot be on the same row because they can't be in the same position on the stack
      // so there is no need to check rows

      // if both queens are in same column, there is confiict
      if (q1col == q2col) {
        conflict = true;
      // if differences in rows and columns between queens are the same,
        // queens are on the same diagonal and there is conflict
      } else if (rowDifference == colDifference) {
        conflict = true;
      } // end if conflict

      // pop queen from stackCopy to check next queen if there is one
      stackCopy.pop();
    } // end if stack is empty
  } // end checking each queen in stackCopy

  return conflict;
} // end checkConflicts()

void printQueens(std::stack<int> stack, int n) {
  // prints queen coordinates
  std::stack<int> stackCopy = stack;
  while (stackCopy.empty() == false) {
    std::cout << "{row: " << stackCopy.size() << " column: " << stackCopy.top() << "}" << std::endl;
    stackCopy.pop();
  }// end while
  std::cout << std::endl;

  // prints each row
  while (stack.empty() == false) {
    // column numbers
    // takes into account # of digits in n for neatness
    if (stack.size() < 10) {
      std::cout << stack.size() << "  ";
    } else {
      std::cout << stack.size() << " ";
    }

    // queen position
    // prints Q if there is a queen, * if there isn't one
    for (int i = 1; i <= n; i++) {
      if (i == stack.top()) {
        std::cout << "Q  ";
      } else {
        std::cout << "*  ";
      } // end if
    } // end for
    std::cout << std::endl;
    stack.pop();
  } // end while

  // row numbers
  // takes into account # of digits in n for neatness
  if (n < 10) {
    std::cout << "   ";
  } else {
    std::cout << "   ";
  } // end if
  for (int j = 1; j <= n; j++) {
    if (j < 10) {
      std::cout << j << "  ";
    } else {
      std::cout << j << " ";
    } // end if
  } // end for
  std::cout << std::endl;
} // end printQueens()

















// space
