#include <iostream>
#include <vector>
#include <limits>

using namespace std;
using ll = long long;

const int INF = numeric_limits<int>::max();

pair<int, vector<int>> hungarian(const vector<vector<int>>& cost_matrix) {
    if (cost_matrix.empty()) return {0, {}};

    int n = cost_matrix.size();
    int m = cost_matrix[0].size();
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i + 1][j + 1] = cost_matrix[i][j];
        }
    }

    vector<int> u(n + 1, 0);
    vector<int> v(m + 1, 0);

    vector<int> p(m + 1, 0);

    vector<int> way(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;

        vector<int> minv(m + 1, INF);
        vector<bool> used(m + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0];
            int delta = INF;
            int j1 = 0;

            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    vector<int> ans(n);
    for (int j = 1; j <= m; ++j) {
        if (p[j] != 0) {
            ans[p[j] - 1] = j - 1;
        }
    }

    int min_cost = -v[0];
    return {min_cost, ans};
}


int main() {
    vector<vector<int>> cost = {
        {5, 3, 2, 8, 1},
        {7, 9, 2, 6, 1},
        {6, 4, 5, 7, 1},
        {5, 7, 7, 8, 1}
    };
    auto [min_cost, assignment] = hungarian(cost);

    cout << "Минимальная стоимость: " << min_cost << "\n\n";
    cout << "Оптимальное распределение:\n";
    for (int i = 0; i < assignment.size(); ++i) {
        cout << "Работник " << i << " -> Задача " << assignment[i]
             << " (стоимость: " << cost[i][assignment[i]] << ")\n";
    }
    return 0;
}
