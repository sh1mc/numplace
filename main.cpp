#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "unistd.h"

class Board {
 public:
  Board(Board &b) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        at(i, j) = b.at(i, j);
      }
    }
  }
  Board() {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        data.at(i).at(j) = 0;
      }
    }
  }
  int &at(int x, int y) {
    if (x >= 9 || x < 0 || y >= 9 || y < 0) {
      printf("out of range\n");
      exit(1);
    } else {
      return data.at(x).at(y);
    }
  }
  void print() {
    system("clear");
    std::string hline1 = "+-----------------------------+\n";
    std::string hline2 = "+---------+---------+---------+\n";
    std::string lines[4] = {"| ", "  ", " | ", " |\n"};
    std::cout << hline1;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        char c;
        if (at(i, j) == 0)
          c = ' ';
        else
          c = std::to_string(at(i, j)).at(0);
        if (j == 0)
          std::cout << lines[0] << c << lines[1];
        else if (j == 8)
          std::cout << c << lines[3];
        else if ((j + 1) % 3 == 0)
          std::cout << c << lines[2];
        else
          std::cout << c << lines[1];
      }
      if ((i + 1) % 3 == 0) std::cout << hline2;
    }
  }

 protected:
  std::array<std::array<int, 9>, 9> data;
};

int main() {
  Board b;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      b.at(i, j) = (i + j) % 9 + 1;
      b.print();
      usleep(1e6);
    }
  }
  return 0;
}