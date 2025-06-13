using System;
namespace Task {
        class Program {

            static void draw(int n)
            {
                for (int i = 0; i < n; i++)
                    Console.Write("*");
                Console.WriteLine();
            }

            static void f(int n)
            {
                if (n == 1)
                    draw(1);
                else
                {
                    draw(n);
                    f(--n);
                }
            }

            static void Main(string[] args) 
            {
                int x = Convert.ToInt32(Console.ReadLine());
                f(x);
            }
        }
    }