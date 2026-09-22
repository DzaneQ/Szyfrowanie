using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Wpisz klucz: ");
        string key = Console.ReadLine();

        if (string.IsNullOrWhiteSpace(key) || !key.All(char.IsLetter))
        {
            Console.WriteLine("Klucz musi być niepustym słowem zawierającym wyłącznie litery.");
            return;
        }


        string inputFilename = "input.txt"; // nazwa pliku wejściowego
        string outputFilename = "output.txt";

        StreamReader inputFile = new StreamReader(inputFilename);
        if (inputFile == null)
        {
            Console.WriteLine("Nie udało się otworzyć pliku wejściowego.");
            return;
        }

        StreamWriter outputFile = new StreamWriter(outputFilename);
        if (outputFile == null)
        {
            Console.WriteLine("Nie udało się otworzyć pliku wyjściowego.");
            return;
        }

        List<int> keyInt = key.ToUpper().Select(c => c - 'A').ToList();
        int keyIndex = 0;

        DateTime start = DateTime.Now;

        int c;
        while ((c = inputFile.Read()) != -1)
        {
            char ch = (char)c;
            if (Char.IsLetter(ch))
            {
                int shift = keyInt[keyIndex];
                ch = Char.ToUpper(ch);
                ch = (char)(((ch - 'A') + shift) % 26 + 'A');

                keyIndex++;
                if (keyIndex == keyInt.Count)
                {
                    keyIndex = 0;
                }
            }
            outputFile.Write(ch);
        }

        inputFile.Close();
        outputFile.Close();

        DateTime end = DateTime.Now;

        Console.WriteLine("Plik został zaszyfrowany kluczem [" + key + "] i zapisany jako " + outputFilename + ".");
        Console.WriteLine("Czas szyfrowania: " + (end - start).TotalSeconds + " sekund.");
    }
}