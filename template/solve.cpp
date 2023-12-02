#include <bits/stdc++.h>

class Solver {
  public:
    void run(std::string line) {
    };
};

int main() {
  std::string filename = "input.txt";
  std::ifstream infile (filename);
  std::string line;

    Solver c;

    std::string s;
    while (getline(infile, line)) {
      std::istringstream ss(line);
        ss >> s;
    }

    c.run(s);
};
