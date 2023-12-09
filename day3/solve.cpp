#include <bits/stdc++.h>

#define S 140

class Solver {
  private:
    struct hasherizer {
      template <class T1, class T2>
      std::size_t operator() (const std::pair<T1, T2> &pair) const
      {
          return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
      }
    };

    std::unique_ptr<std::vector<std::vector<int>>> lines;
    std::unordered_map<std::pair<int,int>, std::vector<int>, hasherizer> gears;

    int partSum{0};

    std::tuple<bool, std::pair<int,int>> isPartNumber(std::pair<int,int> indexes) {
      // first == line, second == character
      // Check each valid direction (including diagonally) for a symbol indicating it's a part number
      std::vector<std::pair<int,int>> pairs;

      pairs.push_back({indexes.first-1, indexes.second});
      pairs.push_back({indexes.first, indexes.second-1});

      pairs.push_back({indexes.first+1, indexes.second});
      pairs.push_back({indexes.first, indexes.second+1});

      pairs.push_back({indexes.first-1, indexes.second-1});
      pairs.push_back({indexes.first+1, indexes.second+1});

      pairs.push_back({indexes.first+1, indexes.second-1});
      pairs.push_back({indexes.first-1, indexes.second+1});

      for (auto& p : pairs) {
        if (p.first < 0 || p.first > S-1 || p.second < 0 || p.second > S-1) { continue; }

        auto& ch = ((*lines)[p.first][p.second]);
        if (!std::isdigit(ch) && ch != '.') {
          return std::make_tuple(true, std::make_pair(p.first, p.second));
        }
      }

      return std::make_tuple(false, std::make_pair(-1,-1));
    };

  public:
    Solver(std::unique_ptr<std::vector<std::vector<int>>>& line) : lines(std::move(line)) { }

    void run() {
      for (int linenum=0; linenum < S; ++linenum) {
        for (int idx=0; idx < S; ++idx) {
          if (std::isdigit((*lines)[linenum][idx])) {
            std::string foundNum;
            std::vector<int> indexes;
            bool ipn{false};

            std::vector<std::pair<int,int>> locations;
            while (idx <= S && std::isdigit((*lines)[linenum][idx])) {
                auto [isPart, localLocations] = isPartNumber({linenum, idx});
                if (isPart) {
                  locations.push_back(std::make_pair(localLocations.first, localLocations.second));
                  ipn = true;
                }

                foundNum += (*lines)[linenum][idx];
                ++idx;
            }

            if (ipn) {
              partSum += std::stoi(foundNum);
              auto loc = locations.back();
              locations.pop_back();
              gears[loc].push_back(std::stoi(foundNum));
            };
          }
        }
      }

      std::cout << "Part 1: " << partSum << std::endl;

      int totalSum = 0;
      for (auto& x : gears) {
        if (x.second.size() == 2) {
          totalSum += x.second[0] * x.second[1];
        }
      }
      std::cout << "Part 2: " << totalSum << std::endl;
    };
};

int main() {
  std::string filename = "input.txt";
  std::ifstream infile{filename};
  std::string line;

  std::string s;
  auto matrix = std::make_unique<std::vector<std::vector<int>>>();
  matrix->resize(S);

  int linecnt = 0;

  while (getline(infile, line)) {
    (*matrix)[linecnt].resize(S);
    for (int i=0; i < line.length(); ++i) {
      (*matrix)[linecnt][i] = line[i];
    }
    ++linecnt;
  }

  Solver c(matrix);
  c.run();
};
