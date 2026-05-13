#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAX_SIZE = 100000;
const int NO_CANDIDATE = INT_MIN;

int countInRange(const vector<int> &A, int lowestIndex, int highestIndex, int val)
{
    int freq = 0;
    for (int i = lowestIndex; i <= highestIndex; i++)
        if (A[i] == val)
            freq++;
    return freq;
}

int dominatorDC(const vector<int> &A, int lowestIndex, int highestIndex)
{
    if (lowestIndex == highestIndex)
        return A[lowestIndex];

    int mid = (lowestIndex + highestIndex) / 2;
    int leftCand = dominatorDC(A, lowestIndex, mid);
    int rightCand = dominatorDC(A, mid + 1, highestIndex);

    if (leftCand == rightCand)
        return leftCand;

    int size = highestIndex - lowestIndex + 1;

    if (leftCand != NO_CANDIDATE)
    {
        int lCount = countInRange(A, lowestIndex, highestIndex, leftCand);
        if (lCount > size / 2)
            return leftCand;
    }

    if (rightCand != NO_CANDIDATE)
    {
        int rCount = countInRange(A, lowestIndex, highestIndex, rightCand);
        if (rCount > size / 2)
            return rightCand;
    }

    return NO_CANDIDATE;
}

int findDominator_DC(const vector<int> &A)
{
    int n = A.size();
    if (n == 0)
        return -1;

    int candidate = dominatorDC(A, 0, n - 1);
    if (candidate == NO_CANDIDATE)
        return -1;

    int firstIndex = -1;
    cout << "Dominator value: " << candidate << endl;
    cout << "Dominator indices: ";
    for (int i = 0; i < n; ++i)
    {
        if (A[i] == candidate)
        {
            if (firstIndex == -1)
                firstIndex = i;
            cout << i << " ";
        }
    }
    cout << endl;

    return firstIndex;
}

int main()
{
    static int test[MAX_SIZE];
    int N;

    cout << "Enter number of elements (0 to " << MAX_SIZE << "): ";
    cin >> N;

    if (N < 0 || N > MAX_SIZE)
    {
        cout << "Invalid size." << endl;
        return 1;
    }

    cout << "Enter " << N << " integers: ";
    for (int i = 0; i < N; ++i)
        cin >> test[i];

    vector<int> A(test, test + N);

    int result = findDominator_DC(A);
    if (result == -1)
        cout << "No Dominator found. Returning -1." << endl;
    else
        cout << "First index: " << result << endl;

    return 0;
}