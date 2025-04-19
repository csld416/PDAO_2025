#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    int bestIndex = 0;
    int bestTime, bestSize;

    // Read the first kingdom to initialize
    {
        int N, M;
        cin >> N >> M;
        if (N == M) {
            M--;
        }
        bestTime = M;      // the night when its triangular envoys all declare
        bestSize = N;      // total number of envoys
    }

    // Process the remaining kingdoms
    for (int i = 1; i < K; i++) {
        int N, M;
        cin >> N >> M;
        if (N == M) {
            M--;
        }
        // Compare completion night
        if (M < bestTime) {
            bestTime = M;
            bestSize = N;
            bestIndex = i;
        }
        else if (M == bestTime) {
            // Tie on night: pick the kingdom with more envoys
            if (N > bestSize) {
                bestSize = N;
                bestIndex = i;
            }
            // if N == bestSize, we keep the earlier (smaller) index
        }
    }

    cout << bestIndex << "\n";
    return 0;
}