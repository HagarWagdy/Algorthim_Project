#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int NO_CANDIDATE = INT_MIN;  // sentinel for 'no majority'

// Count occurrences of val in A[lowestIndex..highestIndex]
int countInRange(const vector<int>& A, int lowestIndex, int highestIndex, int val) {
    int freq = 0;
    for (int i = lowestIndex; i <= highestIndex; i++)
        if (A[i] == val) freq++;
    return freq;
}

// Recursive helper: returns a majority candidate in A[lowestIndex..highestIndex],
// or NO_CANDIDATE if none exists in this sub-array.
int dominatorDC(const vector<int>& A, int lowestIndex, int highestIndex) {
    // ── Base case ─────────────────────────────────────────
    if (lowestIndex == highestIndex) return A[lowestIndex];

    int mid = (lowestIndex + highestIndex) / 2;

    // ── Divide ────────────────────────────────────────────
    int leftCand  = dominatorDC(A, lowestIndex,      mid);
    int rightCand = dominatorDC(A, mid + 1, highestIndex);

    // ── Merge: trivial case ───────────────────────────────
    if (leftCand == rightCand) return leftCand;

    int size = highestIndex - lowestIndex + 1;

    // ── Merge: count left candidate in full range ─────────
    if (leftCand != NO_CANDIDATE) {
        int lCount = countInRange(A, lowestIndex, highestIndex, leftCand);
        if (lCount > size / 2) return leftCand;
    }

    // ── Merge: count right candidate in full range ────────
    if (rightCand != NO_CANDIDATE) {
        int rCount = countInRange(A, lowestIndex, highestIndex, rightCand);
        if (rCount > size / 2) return rightCand;
    }

    return NO_CANDIDATE;  // no majority in this range
}

// Returns index of any Dominator element, or -1.
int findDominator_DC(const vector<int>& A) {
    int n = A.size();
    if (n == 0) return -1;

    int candidate = dominatorDC(A, 0, n - 1);
    if (candidate == NO_CANDIDATE) return -1;

    // Return first occurrence index
    for (int i = 0; i < n; i++)
        if (A[i] == candidate) return i;

    return -1;
}

int main() {
    vector<int> A = {3, 4, 3, 2, 3, -1, 3, 3};
    int idx = findDominator_DC(A);
    if (idx != -1)
        cout << "Dominator index: " << idx
             << "  (value = " << A[idx] << ")" << endl;
    else
        cout << "No Dominator found." << endl;
    return 0;
}
