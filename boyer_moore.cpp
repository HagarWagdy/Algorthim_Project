#include <iostream>
#include <vector>
using namespace std;

// Returns the index of any element equal to the Dominator,
// or -1 if no Dominator exists.
int findDominator_BoyerMoore(const vector<int>& A) {
    int n = A.size();
    if (n == 0) return -1;

    // ── Phase 1: Find candidate ──────────────────────────
    int candidate = A[0];
    int count     = 1;

    for (int i = 1; i < n; i++) {
        if (count == 0) {
            candidate = A[i];   // reset to new candidate
            count     = 1;
        } else if (A[i] == candidate) {
            count++;             // support candidate
        } else {
            count--;             // cancel one vote
        }
    }

    // ── Phase 2: Verify candidate ────────────────────────
    int freq = 0;
    for (int i = 0; i < n; i++)
        if (A[i] == candidate) freq++;

    if (freq <= n / 2) return -1;  // not a true majority

    // ── Phase 3: Return first occurrence index ───────────
    for (int i = 0; i < n; i++)
        if (A[i] == candidate) return i;

    return -1;
}

int main() {
    vector<int> A = {3, 4, 3, 2, 3, -1, 3, 3};
    int idx = findDominator_BoyerMoore(A);
    if (idx != -1)
        cout << "Dominator index: " << idx
             << "  (value = " << A[idx] << ")" << endl;
    else
        cout << "No Dominator found." << endl;
    return 0;
}