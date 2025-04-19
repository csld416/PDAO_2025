#include <bits/stdc++.h>

using namespace std;

int lastSurvivor(int N, int K) {
  int survivor = 0;
  for (int i = 2; i <= N; ++i) {
    survivor = (survivor + K) % i;
  }
  return survivor;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios_base::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;
  int survivor = lastSurvivor(N, K);
  int res = 0;
  for (int i = 0; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    if (i != survivor) {
      continue;
    }
    res = lastSurvivor(a, b);
  }
  cout << survivor << " " << res << endl;
  return 0;
}