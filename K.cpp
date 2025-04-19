#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>
using namespace std;

// Parses a chemical formula into a map of atom -> count
unordered_map<string, int> parseFormula(const string& formula) {
    int i = 0, n = formula.length();
    stack<unordered_map<string, int>> stk;
    stk.push({});

    while (i < n) {
        if (formula[i] == '(') {
            stk.push({});
            i++;
        } else if (formula[i] == ')') {
            i++;
            int start = i;
            while (i < n && isdigit(formula[i])) i++;
            int mult = start < i ? stoi(formula.substr(start, i - start)) : 1;

            auto top = stk.top(); stk.pop();
            for (auto& [atom, cnt] : top) {
                stk.top()[atom] += cnt * mult;
            }
        } else {
            int start = i++;
            while (i < n && islower(formula[i])) i++;
            string atom = formula.substr(start, i - start);

            start = i;
            while (i < n && isdigit(formula[i])) i++;
            int count = start < i ? stoi(formula.substr(start, i - start)) : 1;

            stk.top()[atom] += count;
        }
    }

    return stk.top();
}

int main() {
    int n1, n2;
    cin >> n1 >> n2;
    string f1, f2;
    cin >> f1 >> f2;

    auto map1 = parseFormula(f1);
    auto map2 = parseFormula(f2);

    if (map1 == map2) cout << "Yes\n";
    else cout << "No\n";

    return 0;
}