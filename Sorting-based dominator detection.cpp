#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 100000;

void insertionSort(vector<int> &arr)
{
    int N = arr.size();
    for (int i = 1; i < N; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int printDominatorIndices(const int original[], int length)
{
    if (length == 0)
    {
        cout << "No dominator found." << endl;
        return -1;
    }
    if (length == 1)
    {
        cout << "Dominator found at index: 0" << endl;
        return 0;
    }

    vector<int> sorted(original, original + length);
    insertionSort(sorted);

    int candidate = 0;
    bool found = false;
    int half = length / 2;

    for (int i = 0; i < length - half; ++i)
    {
        if (sorted[i] == sorted[i + half])
        {
            candidate = sorted[i];
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "No dominator found." << endl;
        return -1;
    }

    int firstIndex = -1;
    cout << "Dominator found at indices: ";
    for (int i = 0; i < length; ++i)
    {
        if (original[i] == candidate)
        {
            if (firstIndex == -1)
                firstIndex = i;
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "Dominator value: " << candidate << endl;

    return firstIndex; 
}

int main()
{
    static int A[MAX_SIZE];
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
        cin >> A[i];

    int result = printDominatorIndices(A, N);
    if (result == -1)
        cout << "No dominator found. Returning -1." << endl;
    else
        cout << "First index: " << result << endl;

    return 0;
}