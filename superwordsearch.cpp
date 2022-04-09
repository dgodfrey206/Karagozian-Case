#include <unordered_set>
#include <optional>
#include <iostream>
#include <utility>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <tuple>

struct SuperWordSearch {
  // The array of words that will be used for the search
  std::vector<std::string> grid;
  // Current word being queried
  std::string word;
  // height, width
  int n, m;
  // each value represents a change in the x and y axis (index) respectively. Used for neighbor search.
  int dx[8] = {-1, 0, 1, -1, 1, -1,  0,  1};
  int dy[8] = { 1, 1, 1,  0, 0, -1, -1, -1};

  // if we need to wrap around to the opposite side of the board when searching a word
  bool wrapAround = false;

  // this will be accessed by our main program to print the end coordinates
  std::pair<int, int> ans;

  // returns a pair of indexes that wrap to the other side of the board if they are currently out of bounds
  auto wrap(int i, int j) {
    if (i < 0)  i = n - 1;
    if (i >= n) i =     0;
    if (j < 0)  j = m - 1;
    if (j >= m) j =     0;
    return std::make_pair(i, j);
  }

  // returns the index (wrapped if needed)
  auto neighbor(int i, int j) {
      return wrapAround ? wrap(i, j) : std::make_pair(i, j);
  }

 // performs the search and updates ans if found. std::optional<std::pair<int, int>> as a return value
 // could have also been used
 bool dfs(int idx, int i, int j) {
    // Recursive invariant: 0 <= i < n && 0 <= j < m and word[idx] == grid[i][j]

    // the entire word has been found, update ans and return true
    if (idx == word.size() - 1) {
      ans = {i, j};
      return true;
    }
    // iterate through all neighbors
    for (int k = 0; k < 8; k++) {
      auto [y, x] = neighbor(i + dy[k], j + dx[k]);
      // both indexes must be in bounds and the neighbor must contain the next character
      // to maintain the invariant and continue the search
      if ((0 <= y && y < n && 0 <= x && x < m) &&
          (grid[y][x] == word[idx + 1]) && dfs(idx + 1, y, x)) {
        // the search found the word, so ans was updated and we can return true
        return true;
      }
    }
    // search failed
    return false;
  }
};

// returns true if str contains duplicate characters
bool has_duplicates(std::string const& str) {
  std::unordered_set<char> s;
  for (char c : str) {
    if (s.find(c) != s.end())
      return true;
    s.insert(c);
  }
  return false;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "File argument required.\n";
    std::exit(0);
  }

  std::ifstream file(argv[1]);
  assert(file.is_open());

  // init variables
  int p;
  std::string tmp;

  SuperWordSearch sws;
  assert(file >> sws.n >> sws.m);

  for (int i = 0; i < sws.n; i++) {
    assert(file >> tmp);
    sws.grid.push_back(tmp);
  }

  assert(std::getline(file >> std::ws, tmp) && file >> p);
  sws.wrapAround = tmp == "WRAP";

  // iterate through each query
  for (int i = 0; i < p; i++) {
    // when the word was found in the search, break out of all inner loops and report success 
    bool found = false;
    // the next query
    assert(file >> sws.word);
    // iterate through grid
    for (int i = 0; i < sws.n; i++) {
      if (has_duplicates(sws.word))
        break;
      for (int j = 0; j < sws.m; j++) {
        // the search can start here
        if (sws.grid[i][j] == sws.word[0]) {
          if (sws.dfs(0, i, j)) {
            std::cout << "(" << i << ", " << j << ") (" << sws.ans.first << ", "
                      << sws.ans.second << ")\n";
            found = true;
            break;
          }
        }
      }
      if (found)
        break;
    }
    if (!found) {
      std::cout << "NOT FOUND\n";
    }
  }
}