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
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input15.txt", Encoding.GetEncoding(1251)))
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
            List<int> threeDigitNums = new List<int> (from x in mass
                                                      where (x > 99 && x < 1000)
                                                      select x - 100);
            print<int>(threeDigitNums);
        }
    }
}
