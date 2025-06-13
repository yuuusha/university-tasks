using System;
using System.Diagnostics;
using System.Collections.Generic;
namespace Task
{
    class Program
    {
        static void Main(string[] args)
        {
            int k = 0;
            string s = Console.ReadLine();
            string[] splt = { ",", ".", "!", "- " };

            foreach (string x in splt)
                s = s.Replace(x, "");

            string[] smass = s.Split();

            foreach (string x in smass)
            {
                if (x == x.ToUpper())
                {
                    Console.WriteLine(x);
                    k++;
                }
            }
            Console.WriteLine(k);
        }
    }
}
//привет, ЗЕМЛЯНЕ! мое ИМЯ - ИЛЬЯ! я пришел С миРОМ, ДАВАЙТЕ дружить!
