using System;
using System.Collections.Generic;
using System.IO;

namespace CourseWork
{
    public class Program
    {
        private static void PrintMatrix(List<List<int>> matrix)
        {
            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    Console.Write($"{matrix[i][j]}\t");
                }
                Console.WriteLine();
            }
        }
        private static bool ValidateMatrix(List<List<int>> matrix)
        {
            var countColumns = matrix.Count;
            for (int i = 0; i < countColumns; i++)
            {
                if (matrix[i].Count != countColumns)
                {
                    return false;
                }
            }

            return true;
        }

        private static List<List<int>> ReadFromFile()
        {
            List<List<int>> matrix = new List<List<int>>();
            using (var reader = new StreamReader("./matrix.csv"))
            {
                while (!reader.EndOfStream)
                {
                    var stringLine = reader.ReadLine();
                    var values = stringLine.Split(',');
                    List<int> line = new List<int>();
                    foreach (var value in values)
                    {
                        var parsedValue = int.Parse(value);
                        line.Add(parsedValue);
                    }

                    matrix.Add(line);
                }
            }

            if (!ValidateMatrix(matrix))
            {
                throw new ArgumentException();
            }

            return matrix;
        }

        public static void PrintMenu()
        {
            Console.WriteLine("Выберите действие:");
            Console.WriteLine("1 - Чтение  с файла");
            Console.WriteLine("2 - Ввести с клавиатуры");
            Console.WriteLine("3 - Ввести случайную матрицу");
            var userInput = Console.ReadLine();
            if (!int.TryParse(userInput, out int resultParsing))
            {
                Console.WriteLine("Команды не существует");
                PrintMenu();
                return;
            }

            if (resultParsing > 4 || resultParsing <= 0)
            {
                Console.WriteLine("Команды не существует");
                PrintMenu();
            }

            List<List<int>> matrix = new List<List<int>>();
            if (resultParsing == 1)
            {
                try
                {
                    matrix = ReadFromFile();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Неправильный формат файла. Тип ошибки {e.Message}");
                    PrintMenu();
                }
            }

            if (resultParsing == 2)
            {
            }

            if (resultParsing == 3)
            {
            }
            PrintMatrix(matrix);

        }

        public static void Main(string[] args)
        {
            PrintMenu();
        }
    }
}