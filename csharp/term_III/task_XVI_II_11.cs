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
        struct product
        {
            public string type, grade;
            public int price, amount;

            public product(string[] s)
            {
                type = s[0];
                price = Convert.ToInt32(s[1]);
                grade = s[2];
                amount = Convert.ToInt32(s[3]);
            }
            public void Show(StreamWriter OUT)
            {
                OUT.Write("{0} {1} {2} {3}", type, price, grade, amount);
                OUT.WriteLine();
            }
        }
        static List<product> input()
        {
            List<product> mass = new List<product>();
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input16_2.txt", Encoding.GetEncoding(1251)))
            {
                char[] separator = { '\n', '\t', '\r' };
                string[] s = IN.ReadToEnd().Split(separator, StringSplitOptions.RemoveEmptyEntries);
                foreach (var x in s)
                {
                    mass.Add(new product(x.Split(' ')));
                }
            }
            return mass;
        }

        static void print(List<product> mass)
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
            List<product> mass = input();
            int max_amount = Convert.ToInt32(Console.ReadLine());
            List<product> amountLowerThen = new List<product>(mass.Where(x => x.amount < max_amount).OrderBy(x => x.amount));
            print(amountLowerThen);
        }
    }
}
