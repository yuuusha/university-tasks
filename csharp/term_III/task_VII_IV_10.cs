using System;
namespace Task
{
    class Program
    {

        static void read1(int[] mass)
        {
            for (int i = 0; i < mass.Length; i++)
                mass[i] = Convert.ToInt32(Console.ReadLine());
        }

        static void print1(int[] mass)
        {
            for (int i = 0; i < mass.Length; i++)
                Console.Write(mass[i] + " ");
            Console.WriteLine();
        }

        static void read2(int[,] mass)
        {
            for (int i = 0; i < mass.GetLength(0); i++)
                for (int j = 0; j < mass.GetLength(1); j++)
                    mass[i, j] = Convert.ToInt32(Console.ReadLine());
        }

        static void print2(int[,] mass)
        {
            for (int i = 0; i < mass.GetLength(0); i++)
            {
                for (int j = 0; j < mass.GetLength(1); j++)
                    Console.Write(mass[i, j] + " ");
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        static void Main(string[] args)
        {

            int n = Convert.ToInt32(Console.ReadLine());
            int[,] mass = new int[n, n];
            int[] ans = new int[n];
            read2(mass);
            print2(mass);

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (mass[j, i] > 0)
                    {
                        ans[i] = mass[j, i];
                        break;
                    }
                }
            }

            for (int i = 0; i < n; i++)
            {
                if (ans[i] == 0)
                    Console.WriteLine("There are no positive numbers in this column");
                else
                    Console.WriteLine("{0} - first positive number in {1} column", ans[i], i+1);
            }

        }
    }
}