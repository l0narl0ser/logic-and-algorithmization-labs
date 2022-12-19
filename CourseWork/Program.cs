using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace CourseWork
{
    public class Program
    {
        private static Random _random;

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

            for (int i = 0; i < countColumns; i++)
            {
                if (matrix[i][i] != 0)
                {
                    return false;
                }
            }

            for (int i = 0; i < countColumns; i++)
            {
                for (int j = 0; j < countColumns; j++)
                {
                    if (matrix[i][j] != matrix[j][i])
                    {
                        return false;
                    }
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
                try
                {
                    matrix = ReadMatrixFromConsole();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Неправильный ввод. {e.Message}");
                    PrintMenu();
                }
            }

            if (resultParsing == 3)
            {
                int userMatrixSize;
                Console.WriteLine("Введите размер матрицы: ");
                userMatrixSize = int.Parse(Console.ReadLine());
                matrix = FillMatrixRandom(userMatrixSize);
            }

            PrintMatrix(matrix);
        }

        private static List<List<int>> ReadMatrixFromConsole()
        {
            int userMatrixSize;
            Console.WriteLine("Введите размер матрицы: ");
            userMatrixSize = int.Parse(Console.ReadLine());
            List<List<int>> matrix = new List<List<int>>();

            for (int i = 0; i < userMatrixSize; i++)
            {
                List<int> line = new List<int>();
                line.AddRange(Enumerable.Range(0, userMatrixSize));
                matrix.Add(line);
            }

            for (int i = 0; i < userMatrixSize; i++)
            {
                for (int j = 0; j < userMatrixSize; j++)
                {
                    matrix[i][j] = int.Parse(Console.ReadLine());
                }
            }

            if (!ValidateMatrix(matrix))
            {
                throw new ArgumentException("Матрица введена неправильно");
            }

            return matrix;
        }

        private static List<List<int>> FillMatrixRandom(int inputMatrixSize)
        {
            List<List<int>> matrix = new List<List<int>>();

            for (int i = 0; i < inputMatrixSize; i++)
            {
                List<int> line = new List<int>();
                line.AddRange(Enumerable.Range(0, inputMatrixSize));
                matrix.Add(line);
            }


            for (int i = 0; i < inputMatrixSize; i++)
            {
                for (int j = 0; j < inputMatrixSize; j++)
                {
                    int randomNumber = _random.Next() & 1;
                    if (i == j)
                    {
                        matrix[i][j] = 0;
                    }
                    else
                    {
                        matrix[i][j] = randomNumber;
                        matrix[j][i] = randomNumber;
                    }
                }
            }

            return matrix;
        }

        public static void Main(string[] args)
        {
            _random = new Random();
            PrintMenu();
        }
    }
}