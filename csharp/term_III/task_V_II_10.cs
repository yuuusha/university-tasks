using System;

namespace ConsoleApp2
{
    class Program
    {
        static int power(int x, int n)
        { 
            int pow = 1;
            while (n > 0)
            {
                if (n % 2 == 1) pow *= x;
                x *= x;
                n /= 2;
            }
            return pow;
        }
        
        static void Main(string[] args)
        {
            int a = Convert.ToInt32(Console.ReadLine());
            int b = Convert.ToInt32(Console.ReadLine());
            int h = Convert.ToInt32(Console.ReadLine());

            //a
            Console.WriteLine("a:");
            int n = 1;
            for (int i = a; i <= b; i+=h)
            {
                Console.Write(power(i, n) + " ");
                n++;
            }

            /*
             input              output
             -1                 -1 0 1 16 243
             3
             1

            -1                  -1 1 27
            3
            2
             */

            //b
            Console.WriteLine("\nb:");
            n = 1;
            int sum = 0;
            for (int i = a; i <= b; i+=h)
            {
                sum += power(i, n);
                n++;
            }
            Console.WriteLine(sum);
            /*
             input              output
             -1                 259
             3
             1

            -1                  27
            3
            2
             */

            //d
            Console.WriteLine("\nd:");
            int num = Convert.ToInt32(Console.ReadLine());
            n = 0;
            while (power(2,n) <= num)
            {
                n++;
            }
            Console.WriteLine(n);
            /*
            input              output
            511                 9

            513                 10
            */

            //c
            Console.WriteLine("\nc:");
            a = Convert.ToInt32(Console.ReadLine());
            b = Convert.ToInt32(Console.ReadLine());
            for (int x = a; x <= b; x++)
            {
                for (int y = x; y <= b; y++)
                {
                    for (int z = y; z <= b; z++)
                    {
                        if (power(x, 2) + power(y, 2) == power(z, 2))
                            Console.WriteLine(x + " + " + y + " = " + z);
                    }
                }
            }

            /*
             input              output
             2                  3 + 4 = 5
             20                 5 + 12 = 13
                                6 + 8 = 10
                                8 + 15 = 17
                                9 + 12 = 15
                                12 + 16 = 20
             */

            
        }
    }
}
