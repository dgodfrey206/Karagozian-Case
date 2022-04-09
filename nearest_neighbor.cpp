#include <unordered_map>
#include <iostream>
#include <cassert>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>

// 3d coordinate struct
template <class T>
struct coords {
  T x, y, z;
  coords() = delete;

  bool operator==(coords const& c) const noexcept {
      return x == c.x && y == c.y && z == c.z;
  }

  double distance_to(coords const& rhs) const noexcept {
    return sqrt((rhs.x - x) * (rhs.x - x) + (rhs.y - y) * (rhs.y - y) +
                (rhs.z - z) * (rhs.z - z));
  }

  coords operator+(coords const& rhs) const noexcept {
      return {x + rhs.x, y + rhs.y, z + rhs.z};
  }
};

template<>
struct std::hash<coords<int>> {
    std::size_t operator()(coords<int> const& c) const noexcept {
      return std::hash<std::string>()(std::to_string(c.x) + ',' + std::to_string(c.y) + ',' + std::to_string(c.z));
    }
};

// Changes in the x, y, and z axis to find neighbors
coords<int> neighbors[13] = {
    {-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {-1, 0, -1}, {0, 0, -1}, {1, 0, -1}, {-1, 1, -1}, 
    {0, 1, -1}, {1, 1, -1}, {-1, -1, 0}, {0, -1, 0}, {1, -1, 0}, {-1, 0, 0}
};

// finds all pairs of points within distance r inside a lattice cell
void brute_force(std::vector<std::pair<int, int>>& ps,
                 std::vector<int> is,
                 std::vector<coords<float>> p,
                 float r) {
  for (int i = 0; i < is.size(); i++) {
    for (int j = i + 1; j < is.size(); j++) {
      if (p[is[j]].distance_to(p[i]) <= r) {
        ps.push_back({i, is[j]});
      }
    }
  }
}

// finds pairs of points within distance r between neighboring lattice cells
void brute_force(std::vector<std::pair<int, int>>& ps,
                 std::vector<int> is,
                 std::vector<int> js,
                 std::vector<coords<float>> p,
                 float r) {
  for (int i = 0; i < is.size(); i++) {
    for (int j = 0; j < js.size(); j++) {
      if (p[js[j]].distance_to(p[is[i]]) <= r) {
        ps.push_back({is[i], js[j]});
      }
    }
  }
}

// maps each point to another point it's connected to
auto nearest_neighbors(std::unordered_map<coords<int>, std::vector<int>> indices,
                       std::vector<coords<float>> const& p,
                       float r) {
  std::vector<std::pair<int, int>> ps;
  for (auto[cell, is] : indices) {
    // within the cell (size r), finds the pairs of points and places them in ps
    brute_force(ps, is, p, r);

    // iterate over neighboring cells
    for (int i = 0; i < 13; i++) {
      coords<int> neigh_cell = cell + neighbors[i];
      // neighbor is non-empty, find pairs of points between it and the current
      // cell
      if (indices.find(neigh_cell) != indices.end()) {
        auto js = indices[neigh_cell];
        brute_force(ps, is, js, p, r);
      }
    }
  }
  return ps;
}

// creates an integer lattice with r slots. Each point will be rounded
auto create_cell_list(std::vector<coords<float>> p, float r) {
  assert(r > 0);
  // maps each grid point in the lattice to the 3d points the belong to it
  std::unordered_map<coords<int>, std::vector<int>> indices;
  int n = p.size();
  // each grid point in the lattice is of size r, round each point down
  std::vector<coords<int>> cells;
  for (int i = 0; i < n; i++) {
    cells.push_back(
        coords<int>{int(p[i].x / r), int(p[i].y / r), int(p[i].z / r)});
  }

  // map each cell to those points
  for (int j = 0; j < n; j++) {
    indices[cells[j]].push_back(j);
  }
  return indices;
}

int main() {
  // Initialization
  float r;
  int n;
  std::vector<coords<float>> points;
  std::ifstream file("src/points.txt");

  assert(file.is_open());
  assert(file >> r >> n);

  for (int i = 0; i < n; i++) {
    float x, y, z;
    assert(file >> x >> y >> z);
    points.push_back(coords<float>{x, y, z});
  }

  // the adjacency list that will hold the output.
  std::vector<std::vector<int>> adj(n, std::vector<int>{});
  // integer lattice grid
  auto cell_list = create_cell_list(points, r);
  // find the nearest neighbors for each point and enter them into the adjacency list
  for (auto[p, q] : nearest_neighbors(cell_list, points, r)) {
    adj[p].push_back(q);
    adj[q].push_back(p);
  }

  // output result
  for (int i = 0; i < adj.size(); i++) {
    std::cout << i << ": ";
    for (int point : adj[i]) {
      if (point != i)
        std::cout << point << " ";
    }
    std::cout << std::endl;
  }
}