using System;
namespace Task {
    class Program {
        static void Main(string[] args) {

            int current_year = 2022;

            Console.WriteLine("What is your name?");
            string name = Console.ReadLine();
            Console.WriteLine("How old is you?");
            int age = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("You was born in " + (current_year-age));

        }
    }
}

/*

Input           Output
David           You was born in 1999
23

Ilya            You was born in 2003
19

Andrew          You was born in 1822
200

*/