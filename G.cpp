#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> V(N);
    for (int i = 0; i < N; ++i) {
        cin >> V[i];
    }

    int min_val = *min_element(V.begin(), V.end());
    int max_val = *max_element(V.begin(), V.end());

    vector<int> min_pos, max_pos;
    for (int i = 0; i < N; ++i) {
        if (V[i] == min_val) min_pos.push_back(i);
        if (V[i] == max_val) max_pos.push_back(i);
    }

    int res = 1e9;
    for (int i : min_pos) {
        for (int j : max_pos) {
            int swaps = i + (N - 1 - j);
            if (i > j) swaps--; // overlap
            res = min(res, swaps);
        }
    }

    cout << res << endl;
    return 0;
}