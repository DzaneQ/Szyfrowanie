using System;
using System.IO;

class Program
{
    static void Main()
    {
        Console.Write("Wpisz wartość liczbową przesunięcia: ");
        if (!int.TryParse(Console.ReadLine(), out int shift))
        {
            Console.WriteLine("Przesunięcie nie jest liczbą. Ustawiono wartość domyślną 1.");
            shift = 1;
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

        DateTime start = DateTime.Now;

        char c;
        while (inputFile.Peek() >= 0)
        {
            c = (char)inputFile.Read();
            if (char.IsLetter(c))
            {
                c = char.ToUpper(c);
                c = (char)(((c - 'A') + shift) % 26 + 'A');
            }
            outputFile.Write(c);
        }

        inputFile.Close();
        outputFile.Close();

        DateTime stop = DateTime.Now;
        TimeSpan duration = stop - start;

        Console.WriteLine("Plik został zaszyfrowany z przesunięciem o wartości " + (shift % 26) + " i zapisany jako " + outputFilename + ".");
        Console.WriteLine("Czas trwania szyfrowania: " + duration.TotalMilliseconds + " milisekund.");
    }
}