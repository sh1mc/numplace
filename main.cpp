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
      printf("out of range%d, %d\n", x, y);
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

  bool isvalid() {
    for (int i = 0; i < 9; i++) {
      bool ish[10];
      bool isv[10];
      for (int j = 0; j < 10; j++) {
        ish[j] = false;
        isv[j] = false;
      }
      for (int j = 0; j < 9; j++) {
        if ((at(i, j) != 0 && ish[at(i, j)]) ||
            (at(j, i) != 0 && isv[at(j, i)]))
          return false;
        ish[at(i, j)] = true;
        isv[at(j, i)] = true;
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        bool is[10];
        for (int k = 0; k < 10; k++) is[k] = false;
        int x0 = j * 3;
        int y0 = i * 3;
        for (int k = 0; k < 9; k++) {
          int x = x0 + k % 3;
          int y = y0 + k / 3;
          if (at(x, y) != 0 && is[at(x, y)]) return false;
          is[at(x, y)] = true;
        }
      }
    }
    return true;
  }

 protected:
  std::array<std::array<int, 9>, 9> data;
};

int main() {
  Board b;
  for (int i = 0; i < 9; i++) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < 9; j++) {
      b.at(j, i) = s.at(j) - '0';
    }
  }
  b.print();
  if (b.isvalid())
    printf("valid.\n");
  else
    printf("invalid\n");
  return 0;
}