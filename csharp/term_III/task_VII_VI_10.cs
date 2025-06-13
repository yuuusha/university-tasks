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

        static void read2(int[][] mass, int n, int m)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    mass[i][j] = Convert.ToInt32(Console.ReadLine());
        }

        static void print2(int[][] mass, int n, int m)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    Console.Write(mass[i][j] + " ");
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        static void deleted(int[][] mass, int k, ref int n)
        {

            for (int i = k; i < n-1; i++)
            {
                mass[i] = mass[i + 1];
                
            }
            mass[n-1] = null;
            n--;
        }

        static void Main(string[] args)
        {

            int n = Convert.ToInt32(Console.ReadLine());
            int m = n;
            int A = Convert.ToInt32(Console.ReadLine());
            int B = Convert.ToInt32(Console.ReadLine());
            bool del = true;

            int[][] mass = new int[n][];
            
            for (int i = 0; i < n; i++)
            {
                    mass[i] = new int[n];
            }


            read2(mass, n, m);
            print2(mass, n, m);

            for (int i = 0; i < n; i++)
            {
                del = true;
                for (int j = 0; j < n; j++)
                {
                    if (mass[i][j] > B || mass[i][j] < A)
                    {
                        del = false;
                        break;
                    }
                }
                if (del)
                {
                    deleted(mass, i, ref n);
                    i--;
                }
            }
            
            print2(mass, n, m);

        }
    }
}