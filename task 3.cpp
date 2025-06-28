#include <iostream>
#include <fstream>
using namespace std;
void writeinfile(int** arr, int* sizes, int rows)
{
    ofstream write("jagged.txt");
    for (int i = 0; i < rows; i++)
    {
        write << sizes[i] << " ";  
        for (int j = 0; j < sizes[i]; j++) 
        {
            write << arr[i][j] << " ";
        }
        write << endl;
    }
    write.close();
}

void display(int** arr, int* sizes, int rows) 
{
    cout << "Jagged Array:\n";
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < sizes[i]; j++) 
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void growFront(int**& arr, int*& sizes, int& rows)
{
    int cols;
    cout << "Enter number of columns for new front row: ";
    cin >> cols;
    int* newRow = new int[cols];
    cout << "Enter " << cols << " values: ";
    for (int i = 0; i < cols; i++) cin >> newRow[i];

    int** newArr = new int* [rows + 1];
    int* newSizes = new int[rows + 1];

    newArr[0] = newRow;
    newSizes[0] = cols;

    for (int i = 0; i < rows; i++) 
    {
        newArr[i + 1] = arr[i];
        newSizes[i + 1] = sizes[i];
    }

    delete[] arr;
    delete[] sizes;
    arr = newArr;
    sizes = newSizes;
    rows++;
}

void growEnd(int**& arr, int*& sizes, int& rows) 
{
    int cols;
    cout << "Enter number of columns for new end row: ";
    cin >> cols;
    int* newRow = new int[cols];
    cout << "Enter " << cols << " values: ";
    for (int i = 0; i < cols; i++) cin >> newRow[i];

    int** newArr = new int* [rows + 1];
    int* newSizes = new int[rows + 1];

    for (int i = 0; i < rows; i++)
    {
        newArr[i] = arr[i];
        newSizes[i] = sizes[i];
    }

    newArr[rows] = newRow;
    newSizes[rows] = cols;

    delete[] arr;
    delete[] sizes;
    arr = newArr;
    sizes = newSizes;
    rows++;
}

void growAtPosition(int**& arr, int*& sizes, int& rows, int pos)
{
    if (pos < 0 || pos > rows) 
    {
        cout << "invalid position!" << endl;
        return;
    }

    int cols;
    cout << "enter number of columns for new row: ";
    cin >> cols;
    int* newRow = new int[cols];
    cout << "enter " << cols << " values: ";
    for (int i = 0; i < cols; i++) cin >> newRow[i];

    int** newArr = new int* [rows + 1];
    int* newSizes = new int[rows + 1];

    for (int i = 0; i < pos; i++)
    {
        newArr[i] = arr[i];
        newSizes[i] = sizes[i];
    }

    newArr[pos] = newRow;
    newSizes[pos] = cols;

    for (int i = pos; i < rows; i++)
    {
        newArr[i + 1] = arr[i];
        newSizes[i + 1] = sizes[i];
    }

    delete[] arr;
    delete[] sizes;
    arr = newArr;
    sizes = newSizes;
    rows++;
}

void shrinkFront(int**& arr, int*& sizes, int& rows) 
{
    if (rows == 0) 
        return;
    delete[] arr[0];

    int** newArr = new int* [rows - 1];
    int* newSizes = new int[rows - 1];

    for (int i = 1; i < rows; i++)
    {
        newArr[i - 1] = arr[i];
        newSizes[i - 1] = sizes[i];
    }

    delete[] arr;
    delete[] sizes;
    arr = newArr;
    sizes = newSizes;
    rows--;
}

void shrinkEnd(int**& arr, int*& sizes, int& rows)
{
    if (rows == 0)
        return;
    delete[] arr[rows - 1];

    int** newArr = new int* [rows - 1];
    int* newSizes = new int[rows - 1];

    for (int i = 0; i < rows - 1; i++)
    {
        newArr[i] = arr[i];
        newSizes[i] = sizes[i];
    }

    delete[] arr;
    delete[] sizes;
    arr = newArr;
    sizes = newSizes;
    rows--;
}

void shrinkAtPosition(int**& arr, int*& sizes, int& rows, int pos)
{
    if (pos < 0 || pos >= rows) 
    {
        cout << "Invalid position!" << endl;
        return;
    }
    delete[] arr[pos];

    int** newArr = new int* [rows - 1];
    int* newSizes = new int[rows - 1];

    for (int i = 0; i < pos; i++) 
    {
        newArr[i] = arr[i];
        newSizes[i] = sizes[i];
    }

    for (int i = pos + 1; i < rows; i++)
    {
        newArr[i - 1] = arr[i];
        newSizes[i - 1] = sizes[i];
    }

    delete[] arr;
    delete[] sizes;
    arr = newArr;
    sizes = newSizes;
    rows--;
}

int main() 
{
    int rows;
    cout << "Enter number of initial rows: ";
    cin >> rows;

    int** arr = new int* [rows];
    int* sizes = new int[rows];

    for (int i = 0; i < rows; i++)
    {
        cout << "Enter number of columns in row " << i << ": ";
        cin >> sizes[i];
        arr[i] = new int[sizes[i]];
        cout << "Enter " << sizes[i] << " values: ";
        for (int j = 0; j < sizes[i]; j++)
        {
            cin >> arr[i][j];
        }
    }

    writeinfile(arr, sizes, rows);

    int choice, pos;

    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Grow front\n";
        cout << "2. Grow end\n";
        cout << "3. Grow at position\n";
        cout << "4. Shrink front\n";
        cout << "5. Shrink end\n";
        cout << "6. Shrink at position\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1: growFront(arr, sizes, rows); 
            break;
        case 2: growEnd(arr, sizes, rows);
            break;
        case 3:
            cout << "Enter position: ";
            cin >> pos;
            growAtPosition(arr, sizes, rows, pos);
            break;
        case 4: shrinkFront(arr, sizes, rows);
            break;
        case 5: shrinkEnd(arr, sizes, rows);
            break;
        case 6:
            cout << "Enter position to remove: ";
            cin >> pos;
            shrinkAtPosition(arr, sizes, rows, pos);
            break;
        case 7: cout << "Exiting...\n";
            break;
        default: cout << "Invalid choice!\n";
        }

        if (choice >= 1 && choice <= 6) 
        {
            writeinfile(arr, sizes, rows);
            display(arr, sizes, rows);
        }

    } while (choice != 7);

    for (int i = 0; i < rows; i++) delete[] arr[i];
    delete[] arr;
    delete[] sizes;

    return 0;
}
