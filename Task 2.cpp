#include <iostream>
#include <fstream>
using namespace std;

void writeinfile(int** arr, int rows, int cols)
{
    ofstream write("array2D.txt");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            write << arr[i][j] << " ";
        }
        write << endl;
    }
    write.close();
}

void displayarray(int** arr, int rows, int cols)
{
    cout << "Current 2D Array:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void growfront(int**& arr, int& rows, int cols)
{
    int** newarr = new int* [rows + 1];
    newarr[0] = new int[cols];
    cout << "Enter values for new row (front): ";
    for (int j = 0; j < cols; j++)
        cin >> newarr[0][j];
    for (int i = 0; i < rows; i++)
        newarr[i + 1] = arr[i];
    delete[] arr;
    arr = newarr;
    rows++;
}

void growend(int**& arr, int& rows, int cols)
{
    int** newarr = new int* [rows + 1];
    for (int i = 0; i < rows; i++)
        newarr[i] = arr[i];
    newarr[rows] = new int[cols];
    cout << "Enter values for new row end: ";
    for (int j = 0; j < cols; j++)
    cin >> newarr[rows][j];
    delete[] arr;
    arr = newarr;
    rows++;
}

void growatposition(int**& arr, int& rows, int cols, int pos)
{
    if (pos < 0 || pos > rows)
    {
        cout << "Invalid position!\n";
        return;
    }

    int** newarr = new int* [rows + 1];
    for (int i = 0; i < pos; i++)
        newarr[i] = arr[i];

    newarr[pos] = new int[cols];
    cout << "Enter values for new row at position " << pos << ": ";
    for (int j = 0; j < cols; j++)
        cin >> newarr[pos][j];

    for (int i = pos; i < rows; i++)
        newarr[i + 1] = arr[i];

    delete[] arr;
    arr = newarr;
    rows++;
}

void shrinkfront(int**& arr, int& rows)
{
    if (rows == 0)
       return;
    delete[] arr[0];
    int** newarr = new int* [rows - 1];
    for (int i = 1; i < rows; i++)
        newarr[i - 1] = arr[i];
    delete[] arr;
    arr = newarr;
    rows--;
}

void shrinkend(int**& arr, int& rows)
{
    if (rows == 0)
        return;
    delete[] arr[rows - 1];
    int** newarr = new int* [rows - 1];
    for (int i = 0; i < rows - 1; i++)
        newarr[i] = arr[i];
    delete[] arr;
    arr = newarr;
    rows--;
}

void shrinkatposition(int**& arr, int& rows, int pos)
{
    if (pos < 0 || pos >= rows)
    {
        cout << "Invalid position!\n";
        return;
    }

    delete[] arr[pos];
    int** newarr = new int* [rows - 1];
    for (int i = 0; i < pos; i++)
        newarr[i] = arr[i];
    for (int i = pos + 1; i < rows; i++)
        newarr[i - 1] = arr[i];
    delete[] arr;
    arr = newarr;
    rows--;
}

int main()
{
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    int** arr = new int* [rows];
    cout << "Enter " << rows << "x" << cols << " matrix values:\n";
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            cin >> arr[i][j];
    }

    writeinfile(arr, rows, cols);  

    int choice, pos;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Grow from front\n";
        cout << "2. Grow from end\n";
        cout << "3. Grow at position\n";
        cout << "4. Shrink from front\n";
        cout << "5. Shrink from end\n";
        cout << "6. Shrink at position\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            growfront(arr, rows, cols); 
            break;
        case 2: 
            growend(arr, rows, cols);
            break;
        case 3:
            cout << "Enter position: ";
            cin >> pos;
            growatposition(arr, rows, cols, pos);
            break;
        case 4:
            shrinkfront(arr, rows);
            break;
        case 5:
            shrinkend(arr, rows);
            break;
        case 6:
            cout << "Enter position: ";
            cin >> pos;
            shrinkatposition(arr, rows, pos);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (choice >= 1 && choice <= 6)
        {
            writeinfile(arr, rows, cols);
            displayarray(arr, rows, cols);
        }

    } while (choice != 7);

    for (int i = 0; i < rows; i++)
        delete[] arr[i];
    delete[] arr;

    return 0;
}
