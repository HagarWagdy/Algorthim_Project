#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void insertionSort(vector<int>& arr) {
    int N = arr.size();
    for (int i = 1; i < N; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int printDominatorIndices(const int original[], int length) {
    if (length == 0) {
        cout << "No dominator found." << endl;
        return INT_MIN;
    }
    if (length == 1) {
        cout << "Dominator found at index: 0" << endl;
        return original[0];
    }

    vector<int> sorted(original, original + length);
    insertionSort(sorted);

    int candidate = 0;
    bool found = false;
    int half = length / 2;

    for (int i = 0; i < length - half; ++i) {
        if (sorted[i] == sorted[i + half]) {
            candidate = sorted[i];
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No dominator found." << endl;
        return INT_MIN;
    }

    cout << "Dominator found at indices: ";
    bool first = true;
    for (int i = 0; i < length; ++i) {
        if (original[i] == candidate) {
            if (!first) cout << ", ";
            cout << i;
            first = false;
        }
    }
    cout << endl;

    return candidate;
}

int main() {
    int A[] = {1, 2, 2, 2, 3, 4, 2};
    int N = sizeof(A) / sizeof(A[0]);

    int val = printDominatorIndices(A, N);
    if (val != INT_MIN)
        cout << "Dominator value: " << val << endl;

    return 0;
}