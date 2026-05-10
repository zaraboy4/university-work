#include <vector>
#include <iostream>

int numIslands(std::vector<std::vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    std::vector<std::vector<int>> A(m);
    int cnt = -1;
    for (int i = 0; i < m; ++i) {
        A[i].resize(n);
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] - '0' == 1) {
                A[i][j] = ++cnt;
            }
            else {
                A[i][j] = -1;
            }
        }
    }
    // for (int i = 0; i < m; ++i) {
    //         //A[i].resize(grid[i].size());
    //         for (int j = 0; j < n; ++j) {
    //             std::cout << A[i][j] << ' ';
    //         }
    //         std::cout << '\n';
    //     }

    std::vector<std::vector<int>> g(cnt + 1);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int curr = A[i][j];
            if (curr != -1) {
                if (j >= 1 && A[i][j-1] != -1) {
                    g[curr].push_back(A[i][j-1]);
                }
                if (i >= 1 && A[i-1][j] != -1) {
                    g[curr].push_back(A[i-1][j]);
                }
                if (j < n - 1 && A[i][j+1] != -1) {
                    g[curr].push_back(A[i][j+1]);
                }
                if (i < m - 1 && A[i+1][j] != -1) {
                    g[curr].push_back(A[i+1][j]);
                }
            }
        }
    }
    // for (int i = 0; i < g.size(); ++i) {
    //     std::cout << i << ": ";
    //     for (int j : g[i]) {
    //         std::cout << j << ' ';
    //     }
    //     std::cout << '\n';
    // }
    return 0;
}

int main() {
    std::vector<std::vector<char>> grid = {
                                            {'1', '1', '0'},
                                            {'1', '0', '1'},
                                            {'0', '0', '0'},
                                            {'1', '1', '0'}
                                        };
    std::cout << numIslands(grid);
    return 0;
}