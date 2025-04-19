#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N, R, M;
    cin >> N >> R >> M;

    vector<int> G(M), B(M);
    for (int i = 0; i < M; ++i) {
        cin >> G[i] >> B[i];
    }

    vector<vector<int>> dp(N + 1, vector<int>(R + 1, 0));
    dp[0][0] = 1;

    for (int m = 0; m < M; ++m) {
        int g = G[m], b = B[m];

        for (int a = N - g; a >= 0; --a) {
            for (int prev_b = 0; prev_b <= R; ++prev_b) {
                if (dp[a][prev_b] == 0) continue;

                int new_b = min(R, prev_b + b);
                dp[a + g][new_b] = (dp[a + g][new_b] + dp[a][prev_b]) % MOD;
            }
        }
    }

    // Sum up all dp[a][R] where a in [0..N]
    int result = 0;
    for (int a = 0; a <= N; ++a) {
        result = (result + dp[a][R]) % MOD;
    }

    cout << result << '\n';
    return 0;
}