#include <bits/stdc++.h>

class SolverPart1 {
  private:
    int sum{0};

  public:
    void addItUp(std::string s) {
      char first;
      char last;
      bool has_first{false};

      for (auto& ch : s) {
        if (std::isdigit(ch)) {
          if (!has_first) {
            first = ch;
            has_first = true;
          }
          last = ch;
        }
      }

      std::string f;
      f += first;
      f += last;

      sum += std::stoi(f);
    }

    int getSum() {
      return sum;
    }
};

class SolverPart2 {
  private:
    int sum{0};
    std::map<std::string, std::string> numMap = {
      {"0", "0"},
      {"1", "1"},
      {"2", "2"},
      {"3", "3"},
      {"4", "4"},
      {"5", "5"},
      {"6", "6"},
      {"7", "7"},
      {"8", "8"},
      {"9", "9"},
      {"one", "1"},
      {"two", "2"},
      {"three", "3"},
      {"four", "4"},
      {"five", "5"},
      {"six", "6"},
      {"seven", "7"},
      {"eight", "8"},
      {"nine", "9"}
    };

    std::map<int, std::string> findNumbers(std::string& s) {
      std::map<int, std::string> v;

      int pos{0};
      while (pos < s.length()) {

        for (auto& n : numMap) {
          int res = s.find(n.first, pos);
          if (res != std::string::npos) {
            v[res] = n.second;
          }
        }

        ++pos;
      }
      return v;
    }

  public:
    void addItUp(std::string s) {
      auto numbers = findNumbers(s);

      std::string f;
      f += numbers.begin()->second;
      f += numbers.rbegin()->second;

      sum += std::stoi(f);
    }

    int getSum() {
      return sum;
    }
};

int main() {
  std::string filename = "input.txt";
  std::ifstream infile(filename);
  std::string line;

  SolverPart1 p1;

  while (getline(infile, line)) {
      p1.addItUp(line);
  }
  std::cout << "Part 1: " << p1.getSum() << std::endl;

  SolverPart2 p2;

  infile.clear();
  infile.seekg(0);

  while (getline(infile, line)) {
      p2.addItUp(line);
  }
  std::cout << "Part 2: " << p2.getSum() << std::endl;
};
