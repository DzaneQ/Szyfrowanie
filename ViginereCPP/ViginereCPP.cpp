#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

int main() {
    setlocale(LC_ALL, "pl_PL");

    string key;
    cout << "Wpisz klucz: ";
    cin >> key;

    if (key.empty())
    {
        cout << "Klucz nie moze byc pusty." << endl;
        return 1;
    }

    for (char c : key)
    {
        if (!isalpha(static_cast<unsigned char>(c)))
        {
            cout << "Klucz musi zawierac wylacznie litery." << endl;
            return 1;
        }
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

    vector<int> keyInt;
    for (char c : key) {
        keyInt.push_back(toupper(c) - 'A');
    }

    int keyIndex = 0;

    auto start = chrono::high_resolution_clock::now();

    char c;
    while (inputFile.get(c)) {
        if (isalpha(c)) {
            int shift = keyInt[keyIndex];
            c = toupper(c);
            c = ((c - 'A') + shift) % 26 + 'A';

            keyIndex++;
            if (keyIndex == keyInt.size()) {
                keyIndex = 0;
            }
        }
        outputFile << c;
    }

    inputFile.close();
    outputFile.close();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Plik został zaszyfrowany i zapisany jako " << outputFilename << "." << endl;
    cout << "Czas trwania szyfrowania: " << duration.count() << " mikrosekund." << endl;

    return 0;
}