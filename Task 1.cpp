#include <iostream>
#include <fstream>
using namespace std;

void fileinput(int* arr, int size) {
    ofstream f1("input.txt");
    f1 << size << endl;
    for (int i = 0; i < size; i++) {
        f1 << arr[i] << " ";
    }
    f1 << endl;
    f1.close();
}

void writeinfile(int* arr, int& size) {
    ofstream write("data.txt");
    for (int i = 0; i < size; i++) {
        write << arr[i] << " ";
    }
    write.close();
}

void growfromstart(int*& arr, int& size, int value) {
    int* newarr = new int[size + 1];
    newarr[0] = value;
    for (int i = 0; i < size; i++) {
        newarr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size++;
}

void growfromend(int*& arr, int& size, int value) {
    int* newarr = new int[size + 1];
    for (int i = 0; i < size; i++) {
        newarr[i] = arr[i];
    }
    newarr[size] = value;
    delete[] arr;
    arr = newarr;
    size++;
}

void growanyposition(int*& arr, int& size, int value, int pos) {
    if (pos < 0 || pos > size) {
        cout << "Invalid position: " << endl;
        return;
    }
    int* newarr = new int[size + 1];
    for (int i = 0; i < pos; i++) {
        newarr[i] = arr[i];
    }
    newarr[pos] = value;
    for (int i = pos; i < size; i++) {
        newarr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size++;
}

void shrinkfromstart(int*& arr, int& size) {
    if (size <= 0) return;
    int* newarr = new int[size - 1];
    for (int i = 1; i < size; i++) {
        newarr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size--;
}

void shrinkfromend(int*& arr, int& size) {
    if (size <= 0) return;
    int* newarr = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        newarr[i] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size--;
}

void shrinkanyposition(int*& arr, int& size, int pos) {
    if (size == 0 || pos < 0 || pos >= size) {
        cout << "Invalid position" << endl;
        return;
    }
    int* newarr = new int[size - 1];
    for (int i = 0; i < pos; i++) {
        newarr[i] = arr[i];
    }
    for (int i = pos + 1; i < size; i++) {
        newarr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size--;
}

void displayarr(int* arr, int& size) {
    cout << "Display the array: " << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int size;
    cout << "Enter the size: " << endl;
    cin >> size;

    int* arr = new int[size];

    cout << "Enter the " << size << " elements: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    fileinput(arr, size);
    writeinfile(arr, size);    

    int choice;
    do {
        cout << "\nMenu: " << endl;
        cout << "1. Grow from start" << endl;
        cout << "2. Grow from end" << endl;
        cout << "3. Grow at position" << endl;
        cout << "4. Shrink from start" << endl;
        cout << "5. Shrink from end" << endl;
        cout << "6. Shrink at position" << endl;
        cout << "7. Exit the program" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        int value, pos;

        switch (choice) {
        case 1:
            cout << "Enter the value to insert at the start: ";
            cin >> value;
            growfromstart(arr, size, value);
            break;

        case 2:
            cout << "Enter the value to insert at the end: ";
            cin >> value;
            growfromend(arr, size, value);
            break;

        case 3:
            cout << "Enter the value and position: ";
            cin >> value >> pos;
            growanyposition(arr, size, value, pos);
            break;

        case 4:
            shrinkfromstart(arr, size);
            break;

        case 5:
            shrinkfromend(arr, size);
            break;

        case 6:
            cout << "Enter the position to shrink: ";
            cin >> pos;
            shrinkanyposition(arr, size, pos);
            break;

        case 7:
            cout << "Exiting the program." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
        }

        if (choice >= 1 && choice <= 6) {
            writeinfile(arr, size);
            displayarr(arr, size);
        }

    } while (choice != 7);

    delete[] arr;
    return 0;
}
