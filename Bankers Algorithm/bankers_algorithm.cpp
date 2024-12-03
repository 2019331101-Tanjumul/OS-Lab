#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max_need, vector<vector<int>> &need, vector<int> &available, int process, int resource, bool printSafeSequence = true) {
    vector<int> work = available;
    vector<bool> finish(process, false);
    vector<int> safeSequence(process);

    int count = 0;
    while (count < process) {
        bool found = false;
        for (int p = 0; p < process; ++p) {
            if (!finish[p]) {
                int r;
                for (r = 0; r < resource; ++r) {
                    if (need[p][r] > work[r]) {
                        break;
                    }
                }
                if (r == resource) {
                    for (int k = 0; k < resource; ++k) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            if (printSafeSequence) {
                cout << "System is not in a safe state" << endl;
            }
            return false;
        }
    }
    if (printSafeSequence) {
        cout << "System is in a safe state.\nSafe sequence is: \n";
        for (int i = 0; i < process; ++i) {
            cout <<"Process " << safeSequence[i] << "\n";
        }
        cout << endl;
    }
    return true;
}

bool requestResources(vector<vector<int>> &allocation, vector<vector<int>> &max_need, vector<vector<int>> &need, vector<int> &available, int process, int resource, int processNum, vector<int> &request) {
    for (int i = 0; i < resource; ++i) {
        if (request[i] > need[processNum][i]) {
            cout << "Error: Process " << processNum <<" has exceeded its maximum claim." << endl;
            return false;
        }
    }

    for (int i = 0; i < resource; ++i) {
        if (request[i] > available[i]) {
            cout << "Resources are not available for this request." << endl;
            return false;
        }
    }

    for (int i = 0; i < resource; ++i) {
        available[i] -= request[i];
        allocation[processNum][i] += request[i];
        need[processNum][i] -= request[i];
    }

    if (isSafe(allocation, max_need, need, available, process, resource, false)) {
        return true;
    } else {
        for (int i = 0; i < resource; ++i) {
            available[i] += request[i];
            allocation[processNum][i] -= request[i];
            need[processNum][i] += request[i];
        }
        return false;
    }
}

int main() {
    int process = 5;
    int resource = 3;

    vector<vector<int>> allocation = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    vector<vector<int>> max_need = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };
    vector<vector<int>> need(process, vector<int>(resource));
    vector<int> available = {3, 3, 2};

    for (int i = 0; i < process; ++i) {
        for (int j = 0; j < resource; ++j) {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    isSafe(allocation, max_need, need, available, process, resource);

    vector<int> request = {1, 0, 2};
    if (requestResources(allocation, max_need, need, available, process, resource, 1, request)) {
        cout << "Your request granted." << endl;
    } else {
        cout << "Your request denied." << endl;
    }

    return 0;
}
