#include <bits/stdc++.h>

class Solver {
  private:
    int sum{0};
    std::vector<int> possibleGames;
    std::vector<int> powers;

    /**
     * The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
    */
    std::unordered_map<std::string, int> maxCubes{{"red", 12}, {"green", 13}, {"blue", 14}};

  public:
    void run(std::string line) {
      bool possible{true};

      line.erase(std::remove(line.begin(), line.end(), ','), line.end());
      line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
      line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

      std::istringstream ss(line);
      std::unordered_map<std::string, int> maxSeenByColor;

      //Game 1: 10 green, 5 blue; 1 red, 9 green, 10 blue; 5 blue, 6 green, 2 red; 7 green, 9 blue, 1 red; 2 red, 10 blue, 10 green; 7 blue, 1 red

      std::string tmp;
      std::string color;
      int gameId;
      int count;

      // skip game fields
      ss >> tmp;
      ss >> tmp;
      gameId = stoi(tmp);

      while (ss >> count) {
        ss >> color;
        maxSeenByColor[color] = std::max(count, maxSeenByColor[color]);

        if (count > maxCubes[color]) {
          possible = false;
        }
      }

      if (possible) {
        possibleGames.push_back(gameId);
      }

      powers.push_back(maxSeenByColor["red"] * maxSeenByColor["green"] * maxSeenByColor["blue"]);
    };

    int sumOfPossible() {
      int sum{0};
      for (auto& p : possibleGames) {
        sum += p;
      }
      return sum;
    }

    int sumOfPowers() {
      int sum{0};
      for (auto& p : powers) {
        sum += p;
      }
      return sum;
    }
};

int main() {
  std::string filename = "input.txt";
  std::ifstream infile (filename);
  std::string line;

    Solver c;

    while (getline(infile, line)) {
      c.run(line);
    }
    std::cout << "Part 1: " << c.sumOfPossible() << std::endl;
    std::cout << "Part 2: " << c.sumOfPowers() << std::endl;
};
