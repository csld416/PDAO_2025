#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<ll> initH(N);
    for (int i = 0; i < N; i++) cin >> initH[i];
    // difference array for range add
    vector<ll> diff(N+1, 0);

    vector<ll> Hcur(N);
    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int L, R, v;
            cin >> L >> R >> v;
            diff[L] += v;
            if (R+1 < N) diff[R+1] -= v;
        } else if (type == 2) {
            int L, R, v;
            cin >> L >> R >> v;
            diff[L] -= v;
            if (R+1 < N) diff[R+1] += v;
        } else if (type == 3) {
            int LEN, P1, P2;
            cin >> LEN >> P1 >> P2;
            if (LEN > N) {
                cout << "Oiiaioiiiai\n";
                continue;
            }
            // build current heights
            ll acc = 0;
            for (int i = 0; i < N; i++) {
                acc += diff[i];
                Hcur[i] = initH[i] + acc;
            }
            // sliding-window max + running sum
            deque<int> dq;
            ll sum = 0;
            // first window
            for (int i = 0; i < LEN; i++) {
                sum += Hcur[i];
                while (!dq.empty() && Hcur[dq.back()] <= Hcur[i]) dq.pop_back();
                dq.push_back(i);
            }
            ll bestVal = LLONG_MIN;
            int bestL = 0;
            // evaluate first window
            ll curVal = (ll)P1 * Hcur[dq.front()] + (ll)P2 * sum;
            bestVal = curVal;
            bestL = 0;
            // slide
            for (int i = LEN; i < N; i++) {
                // remove out-of-window
                while (!dq.empty() && dq.front() <= i - LEN) dq.pop_front();
                // add new
                while (!dq.empty() && Hcur[dq.back()] <= Hcur[i]) dq.pop_back();
                dq.push_back(i);
                // update sum
                sum += Hcur[i] - Hcur[i - LEN];
                int L = i - LEN + 1;
                ll maxH = Hcur[dq.front()];
                ll val = (ll)P1 * maxH + (ll)P2 * sum;
                if (val > bestVal) {
                    bestVal = val;
                    bestL = L;
                }
            }
            if (bestVal > 0) {
                cout << bestL << " " << (bestL + LEN - 1) << " " << bestVal << '\n';
            } else {
                cout << "Oiiaioiiiai\n";
            }
        }
    }
    return 0;
}
