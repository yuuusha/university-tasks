using System;
namespace Task {
    class Program {
        static void Main(string[] args) {

            int A = Convert.ToInt32(Console.ReadLine());
            int num = Math.Abs(Convert.ToInt32(Console.ReadLine()));

            int a = num % 10;
            int b = (num / 10) % 10;
            int c = num / 100;

            Console.WriteLine( ((A != 0) && ((a+b+c) % A == 0)) ? "Yes" : "No");

        }
    }
}

/*

Input           Output
2               Yes
123

-2              Yes
123

0               No
123
*/