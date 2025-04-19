#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> predicted(n), actual(n);
    for (int &x : predicted) cin >> x;
    for (int &x : actual) cin >> x;

    vector<int> sorted_pred = predicted;
    sort(sorted_pred.begin(), sorted_pred.end());

    long long total_error = 0;
    long long max_reduction = 0;

    for (int i = 0; i < n; ++i) {
        int orig = predicted[i];
        int target = actual[i];
        int current_error = abs(orig - target);
        total_error += current_error;

        // Binary search for closest value to actual[i] in sorted_pred
        auto it = lower_bound(sorted_pred.begin(), sorted_pred.end(), target);
        
        // Check value at it
        if (it != sorted_pred.end() && *it != orig) {
            int new_error = abs(*it - target);
            max_reduction = max(max_reduction, (long long)current_error - new_error);
        }
        // Check value before it
        if (it != sorted_pred.begin()) {
            --it;
            if (*it != orig) {
                int new_error = abs(*it - target);
                max_reduction = max(max_reduction, (long long)current_error - new_error);
            }
        }
    }

    cout << total_error - max_reduction << '\n';
    return 0;
}