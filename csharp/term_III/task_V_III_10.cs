using System;
namespace Task {
        class Program {

            static double f(int x, int n, int i=1)
            {

                if (n == i)
                    return (x / (double)(n + x));

                return (x / (double)(i + f(x, n, ++i)));

            }
            static void Main(string[] args) 
            {

                int x = Convert.ToInt32(Console.ReadLine());
                int n = Convert.ToInt32(Console.ReadLine());
                double a = f(x, n);
                Console.WriteLine(a);
                

            }
        }
    }

/*
    Input           Output
    1 1             0.5
    1 2             0.75
    1 3             0.692307692307692

*/