#include <iostream>
#include <fstream>
#include <queue>

struct triple {
    int i;
    int j;
    int len;
};

bool isValidMove(int i, int j, int n) {
    return i >= 0 && i < n && j >= 0 && j < n;
}

int shortestPathBinaryMatrix(int** A, int n) {
    std::queue<triple> q;
    if (A[0][0] == 1) return -1;
    q.push({0,0,0});
    A[0][0] = 1;
    triple tr;
    while (!q.empty()) {
        tr = q.front();
        printf("{%d,%d,%d} ", tr.i + 1, tr.j + 1, tr.len);
        q.pop();
        if (tr.i == n - 1 && tr.j == n - 1) {
            return tr.len;
        }
        if (isValidMove(tr.i, tr.j - 1, n) && A[tr.i][tr.j - 1] == 0) {
            q.push({tr.i, tr.j - 1, tr.len + 1});
            A[tr.i][tr.j - 1] = 1;
        }
        if (isValidMove(tr.i - 1, tr.j - 1, n) && A[tr.i - 1][tr.j - 1] == 0) {
            q.push({tr.i - 1, tr.j - 1, tr.len + 1});
            A[tr.i - 1][tr.j - 1] = 1;
        }
        if (isValidMove(tr.i - 1, tr.j, n) && A[tr.i - 1][tr.j] == 0) {
            q.push({tr.i - 1, tr.j, tr.len + 1});
            A[tr.i - 1][tr.j] = 1;
        }
        if (isValidMove(tr.i - 1, tr.j + 1, n) && A[tr.i - 1][tr.j + 1] == 0) {
            q.push({tr.i - 1, tr.j + 1, tr.len + 1});
            A[tr.i - 1][tr.j + 1] = 1;
        }
        if (isValidMove(tr.i, tr.j + 1, n) && A[tr.i][tr.j + 1] == 0) {
            q.push({tr.i, tr.j + 1, tr.len + 1});
            A[tr.i][tr.j + 1] = 1;
        }
        if (isValidMove(tr.i + 1, tr.j + 1, n) && A[tr.i + 1][tr.j + 1] == 0) {
            q.push({tr.i + 1, tr.j + 1, tr.len + 1});
            A[tr.i + 1][tr.j + 1] = 1;
        }
        if (isValidMove(tr.i + 1, tr.j, n) && A[tr.i + 1][tr.j] == 0) {
            q.push({tr.i + 1, tr.j, tr.len + 1});
            A[tr.i + 1][tr.j] = 1;
        }
        if (isValidMove(tr.i + 1, tr.j - 1, n) && A[tr.i + 1][tr.j - 1] == 0) {
            q.push({tr.i + 1, tr.j - 1, tr.len + 1});
            A[tr.i + 1][tr.j - 1] = 1;
        }
    }
    return -1;
}

int** deserializeMatrix(std::ifstream& ifs, int n) {
    int** A = new int*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ifs >> A[i][j];
        }
    }
    return A;
}

void deallocateMatrix(int**& A, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] A[i];
    }
    delete[] A;
    A = nullptr;
}

int main() {
    // int A[3][3] = {{0,0,0},
    //                {1,1,0},
    //                {1,1,0}};
    std::ifstream ifs("input_matrix.txt");
    if (!ifs.is_open()) {
        std::cout << "invalid file name\n";
        return 1;
    }
    int n;
    ifs >> n;
    int** A = deserializeMatrix(ifs, n);
    std::cout << shortestPathBinaryMatrix(A, n);
    deallocateMatrix(A, n);
    return 0;
}