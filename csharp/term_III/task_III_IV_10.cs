using System;
namespace Task {
        class Program {
            static void Main(string[] args) {

            int num = Convert.ToInt32(Console.ReadLine());
            int n = 1;
            bool first = true;
            int a = 0; int k = 0;

            while (num > 1)
            {
                n++;
                while (num % n == 0)
                {
                    num /= n;
                    if (first)
                    {
                        a = n;
                        first = false;
                    }
                    k++;
                }
            }

            if (k==1)
            {
                Console.WriteLine("Number is prime");
            }
            else Console.WriteLine("{0} + {1} = " + (a + n), a, n);
                

            }
        }
    }

    /*
    Input           Output
    36              2 + 3 = 5

    100             2 + 5 = 7

    17              Number is prime
    */