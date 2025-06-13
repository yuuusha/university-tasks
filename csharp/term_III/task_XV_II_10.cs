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
        struct employee
        {
            public string name, job;
            public int year, salary, exp;

            public employee(string[] s)
            {
                name = s[0];
                year = Convert.ToInt32(s[1]);
                job = s[2];
                salary = Convert.ToInt32(s[3]);
                exp = Convert.ToInt32(s[4]);
            }
            public void Show(StreamWriter OUT)
            {
                OUT.Write("{0} {1} {2} {3}", name, year, salary, exp);
                OUT.WriteLine();
            }
        }
        static List<employee> input()
        {
            List<employee> mass = new List<employee>();
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input15_2.txt", Encoding.GetEncoding(1251)))
            {
                char[] separator = { '\n', '\t', '\r' };
                string[] s = IN.ReadToEnd().Split(separator, StringSplitOptions.RemoveEmptyEntries);
                foreach (var x in s)
                {
                    mass.Add(new employee(x.Split(' ')));
                }
            }
            return mass;
        }

        static void print(List<employee> mass)
        {
            using (StreamWriter OUT = new StreamWriter("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/output.txt", false))
            {
                foreach (var x in mass)
                {
                    x.Show(OUT);
                }
            }
        }

        static void Main(string[] args)
        {
            List<employee> mass = input();
            var jobs = from x in mass
                        group x by x.job;


            using (StreamWriter OUT = new StreamWriter("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/output.txt", false))
            {
                foreach (var x in jobs)
                {
                    OUT.Write(x.Key + "ы: ");
                    foreach (var i in x)
                    {
                        i.Show(OUT);
                        OUT.Write("             ");
                    }
                    OUT.WriteLine();
                }
                OUT.WriteLine();
            }
           
        }
    }
}
