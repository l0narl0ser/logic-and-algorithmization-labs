using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using MultiConsoleOutput;

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

                Console.WriteLine("\n");
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

        public static bool PrintMenu()
        {
            Console.WriteLine("Выберите действие:");
            Console.WriteLine("1 - Чтение  с файла");
            Console.WriteLine("2 - Ввести случайную матрицу");
            Console.WriteLine("3 - Выйти");

            var userInput = Console.ReadLine();

            if (!int.TryParse(userInput, out int resultParsing))
            {
                Console.WriteLine("Команды не существует");
                return false;
            }

            if (resultParsing > 3 || resultParsing <= 0)
            {
                Console.WriteLine("Команды не существует");
                return false;
            }

            if (resultParsing == 3)
            {
                return true;
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
                    return false;
                }
            }
            
            
            if (resultParsing == 2)
            {
                try
                {
                    matrix = CreateMatrixByUserInput();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Неправильный пользовательский ввод {e.Message}");
                    return false;
                }
            }
            PrintMatrix(matrix);
            Console.WriteLine("Введите вершину, с которой начинается поиск");
            int vertex;

            try
            {
                vertex = int.Parse( Console.ReadLine());
                if (vertex > matrix.Count || vertex < 0)
                {
                    throw new AggregateException("Некорректный Ввод вершины");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return false;
            }
            //PrintMatrix(matrix);

            DijkstraAlgo(matrix, vertex);
            return false;
        }

        private static List<List<int>> CreateMatrixByUserInput()
        {
            List<List<int>> matrix;
            Console.WriteLine("Введите размер матрицы: ");
            var userMatrixSize = int.Parse(Console.ReadLine());

            Console.WriteLine("Выберите: взвешенный граф - 1, не взвешенный - 0");
            var userNumberInput = int.Parse(Console.ReadLine());

            Console.WriteLine("Выберите: ориентированный граф - 1, не ориентированный граф  - 0 ");
            var userSelectedOrintationGrapth = int.Parse(Console.ReadLine());

            if (userNumberInput < 0 || userNumberInput > 1)
            {
                throw new ArgumentException("Пользователь ввел недопустимые цифры");
            }

            if (userSelectedOrintationGrapth < 0 || userSelectedOrintationGrapth > 1)
            {
                throw new ArgumentException("Пользователь ввел недопустимые цифры");
            }

            Action<int, int, List<List<int>>, int> orintationAction;

            if (userSelectedOrintationGrapth == 0)
            {
                orintationAction = FillNotOrientedGraph;
            }
            else
            {
                orintationAction = FillOrientedGraph;
            }


            if (userNumberInput == 1)
            {
                matrix = FillMatrixRandom(userMatrixSize, GenerateAnyRandomNumber, orintationAction);
            }
            else
            {
                matrix = FillMatrixRandom(userMatrixSize, GenerateRandomZeroOreOne, orintationAction);
            }


            return matrix;
        }
        
        private static List<List<int>> FillMatrixRandom(int inputMatrixSize, Func<int> generator,
            Action<int, int, List<List<int>>, int> fillMatrix)
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
                    int randomNumber = generator.Invoke();
                    fillMatrix(i, j, matrix, randomNumber);
                }
            }

            return matrix;
        }

        private static void FillOrientedGraph(int i, int j, List<List<int>> matrix, int randomNumber)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = randomNumber;
            }
        }

        private static void FillNotOrientedGraph(int i, int j, List<List<int>> matrix, int randomNumber)
        {
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

        public static int GenerateRandomZeroOreOne()
        {
            return _random.Next() & 1;
        }

        public static int GenerateAnyRandomNumber()
        {
            return _random.Next() % 20;
        }

        private static int MinimumDistance(int[] distance, bool[] shortestPathTreeSet, int verticesCount)
        {
            int min = int.MaxValue;
            int minIndex = 0;

            for (int v = 0; v < verticesCount; ++v)
            {
                if (shortestPathTreeSet[v] == false && distance[v] <= min)
                {
                    min = distance[v];
                    minIndex = v;
                }
            }

            return minIndex;
        }

        public static void DijkstraAlgo(List<List<int>> graph, int source)
        {
            int verticesCount = graph.Count;
            int[] distance = new int[verticesCount];
            bool[] shortestPathTreeSet = new bool[verticesCount];

            for (int i = 0; i < verticesCount; ++i)
            {
                distance[i] = int.MaxValue;
                shortestPathTreeSet[i] = false;
            }

            distance[source] = 0;

            for (int count = 0; count < verticesCount - 1; ++count)
            {
                int u = MinimumDistance(distance, shortestPathTreeSet, verticesCount);
                shortestPathTreeSet[u] = true;

                for (int v = 0; v < verticesCount; ++v)
                {
                    if (!shortestPathTreeSet[v] && graph[u][v] != 0 && distance[u] != int.MaxValue &&
                        distance[u] + graph[u][v] < distance[v])
                    {
                        distance[v] = distance[u] + graph[u][v];
                    }
                }
            }

            Print(distance, verticesCount);
        }

        private static void Print(int[] distance, int verticesCount)
        {
            Console.WriteLine("Вершина    Расстояние от источника");

            for (int i = 0; i < verticesCount; ++i)
                Console.WriteLine("{0}\t  {1}", i, distance[i]);
        }

        
        public static void Main(string[] args)
        {
            _random = new Random();
            ConsoleFileOutput dualOutput = new ConsoleFileOutput("outPut.txt", Console.Out);  
            Console.SetOut(dualOutput);
            var needQuiet = false;
            while (!needQuiet)
            {
                needQuiet = PrintMenu();
                Console.WriteLine("\n\n\n");
            }
            
        }
    }
}