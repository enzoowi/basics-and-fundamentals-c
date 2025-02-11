//Brian Lorenz U. Miranda
//IT2B
#include <iostream>
using namespace std;

int main() {
    int arr1[10], arr2[10], mergedArr[20];
    int size1, size2;

    while (true)
    {
        cout << "Enter the number of elements for the first array (1 to 10): ";
        cin >> size1;
        if (cin.fail() || size1 < 1 || size1 > 10)
        {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 10.\n";
        }
    else
    {
        break;
    }
    }

    cout << "Enter " << size1 << " elements for the first array:\n";
    for (int i = 0; i < size1; ++i)
    {
        while (true)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> arr1[i];
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter an integer.\n";
        }
    else
    {
        break;
    }
    }
    }

    while (true) {
        cout << "Enter the number of elements for the second array (1 to 10): ";
        cin >> size2;
        if (cin.fail() || size2 < 1 || size2 > 10)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 10.\n";
    }
    else
    {
        break;
    }
    }

    cout << "Enter " << size2 << " elements for the second array:\n";
    for (int i = 0; i < size2; ++i)
    {
        while (true)
    {
    cout << "Element " << i + 1 << ": ";
    cin >> arr2[i];
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter an integer.\n";
    }
    else
    {
        break;
    }
    }
    }

    int mergedSize = size1 + size2;
    for (int i = 0; i < size1; ++i) mergedArr[i] = arr1[i];
    for (int i = 0; i < size2; ++i) mergedArr[size1 + i] = arr2[i];
    for (int i = 0; i < mergedSize - 1; ++i)
    {
    for (int j = i + 1; j < mergedSize; ++j)
    {
        if (mergedArr[i] < mergedArr[j])
        {
            int temp = mergedArr[i];
            mergedArr[i] = mergedArr[j];
            mergedArr[j] = temp;
        }
    }
}
    cout << "Merged and sorted array in descending order:\n";
    for (int i = 0; i < mergedSize; ++i) cout << mergedArr[i] << " ";
    cout << endl;
    return 0;
}