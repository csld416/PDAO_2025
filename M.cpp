#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long c0 = 0, c1 = 0, c2 = 0;
    for (int i = 0; i < n; i++) {
        long long k;
        cin >> k;
        int r = k % 3;
        if (r < 0) r += 3;
        if (r == 0) c0++;
        else if (r == 1) c1++;
        else c2++;
    }

    bool merlinWins = false;
    if (c1 == 0 && c2 == 0) {
        // only multiples of 3 -> first move loses
        merlinWins = false;
    } else if (c0 % 2 == 0) {
        // even number of mod-0 bottles: need at least one of each mod-1 and mod-2
        merlinWins = (c1 >= 1 && c2 >= 1);
    } else {
        // odd number of mod-0 bottles: difference must be >= 3
        long long diff = c1 > c2 ? c1 - c2 : c2 - c1;
        merlinWins = (diff >= 3);
    }

    cout << (merlinWins ? "Yes" : "No") << "\n";
    return 0;
}