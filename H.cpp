#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

struct Cell {
    int height, x, y;
    bool operator>(const Cell& other) const {
        return height > other.height;
    }
};

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> height(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> height[i][j];

    if (m <= 2 || n <= 2) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;

    // Push all border cells
    for (int i = 0; i < m; ++i) {
        pq.push({height[i][0], i, 0});
        pq.push({height[i][n - 1], i, n - 1});
        visited[i][0] = visited[i][n - 1] = true;
    }
    for (int j = 1; j < n - 1; ++j) {
        pq.push({height[0][j], 0, j});
        pq.push({height[m - 1][j], m - 1, j});
        visited[0][j] = visited[m - 1][j] = true;
    }

    int total_water = 0;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!pq.empty()) {
        Cell curr = pq.top(); pq.pop();
        for (auto [dx, dy] : directions) {
            int nx = curr.x + dx;
            int ny = curr.y + dy;
            if (nx < 0 || ny < 0 || nx >= m || ny >= n || visited[nx][ny]) continue;

            visited[nx][ny] = true;
            int nh = height[nx][ny];
            if (nh < curr.height) {
                total_water += curr.height - nh;
            }
            pq.push({max(nh, curr.height), nx, ny});
        }
    }

    cout << total_water << endl;
    return 0;
}