#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int main() {
    setlocale(LC_ALL, "pl_PL");

    int shift;
    cout << "Wpisz wartość liczbową przesunięcia: ";
    if (!(cin >> shift)) {
        cout << "Przesunięcie nie jest liczbą. Ustawiono wartość domyślną 1." << endl;
        shift = 1;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string inputFilename = "input.txt"; // nazwa pliku wejściowego
    string outputFilename = "output.txt";

    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cout << "Nie udało się otworzyć pliku wejściowego." << endl;
        return 1;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cout << "Nie udało się otworzyć pliku wyjściowego." << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();

    char c;
    while (inputFile.get(c)) {
        if (isalpha(c)) {
            c = toupper(c);
            c = ((c - 'A') + shift) % 26 + 'A';
        }
        outputFile << c;
    }

    inputFile.close();
    outputFile.close();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Plik został zaszyfrowany z przesunięciem o wartości " << shift % 26 << " i zapisany jako " << outputFilename << "." << endl;
    cout << "Czas trwania szyfrowania: " << duration.count() << " mikrosekund." << endl;

    return 0;
}