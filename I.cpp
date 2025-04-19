#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<vector<int>> P(M, vector<int>(N));
    vector<tuple<int, int, int>> cells; // (value, row, col)

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            cin >> P[i][j];
            cells.emplace_back(P[i][j], i, j);
        }

    // Output grid
    vector<vector<int>> res(M, vector<int>(N, 0));

    // Process in increasing order of original power levels
    sort(cells.begin(), cells.end());

    vector<int> rowMax(M, 0), colMax(N, 0);

    for (auto& [val, i, j] : cells) {
        res[i][j] = max(rowMax[i], colMax[j]) + 1;
        rowMax[i] = max(rowMax[i], res[i][j]);
        colMax[j] = max(colMax[j], res[i][j]);
    }

    // Output formatted: M lines, each with N space-separated integers
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << res[i][j];
            if (j < N - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}