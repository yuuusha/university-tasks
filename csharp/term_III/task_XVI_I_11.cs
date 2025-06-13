using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Linq;

namespace Task
{
    class Program
    {
        static List<int> input()
        {
            List<int> mass = new List<int>();
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input16.txt", Encoding.GetEncoding(1251)))
            {
                string[] s = IN.ReadLine().Split(' ');
                foreach (var x in s)
                {
                    mass.Add(Convert.ToInt32(x));
                }
            }
            return mass;
        }

        static void print<T>(List<T> mass)
        {
            using (StreamWriter OUT = new StreamWriter("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/output.txt", false))
            {
                foreach (var x in mass)
                {
                    OUT.Write(x + " ");
                }
                OUT.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            List<int> mass = input();
            List<int> twoDigitNums = new List<int>(mass.Where(x => (x > 9 && x < 100)).Select(x => -x));
            print<int>(twoDigitNums);
        }
    }
}
