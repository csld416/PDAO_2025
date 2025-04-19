#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    const int MAX_POS = 1000;
    vector<bool> occupied(MAX_POS, false);
    int total_moves = 0;

    for (int i = 0; i < N; ++i) {
        char op;
        int P;
        cin >> op >> P;

        if (op == 'I') {
            if (!occupied[P]) {
                // empty, insert directly
                occupied[P] = true;
                total_moves += 1;
            } else {
                // need to shift
                int q = P;
                while (q < MAX_POS && occupied[q]) {
                    q++;
                }

                // shift all from q-1 to P
                for (int j = q; j > P; --j) {
                    occupied[j] = occupied[j - 1];
                    total_moves++; // one move per shift
                }
                occupied[P] = true; // insert
                total_moves += 1;   // count insert move
            }
        } else if (op == 'D') {
            if (occupied[P]) {
                occupied[P] = false;
                total_moves += 1;
            }
        }
    }

    cout << total_moves << endl;
    return 0;
}