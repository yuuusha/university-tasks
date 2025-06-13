using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace ConsoleApp4
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = @"C:\Users\jojom\source\repos\ConsoleApp4\ConsoleApp4\bin\Debug\input.txt";
            int n;
            Graph g;
            List<Town> towns = new List<Town>(); 

            using (StreamReader IN = new StreamReader(path))
            {
                n = Convert.ToInt32(IN.ReadLine());
                for (int i = 0; i < n; i++)
                {
                    string[] s = IN.ReadLine().Split();
                    towns.Add(new Town(s[0], Convert.ToInt32(s[1]), Convert.ToInt32(s[2])));
                }
                g = new Graph(IN, n);
            }
            g.Recalc(towns);

            Console.WriteLine("Начальная точка:");
            int a = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Конечная точка:");
            int b = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Путь может проходить только через города...");
            int t = 0;
            List<int> ver = new List<int>();
            while (t != -1)
            {
                t = Convert.ToInt32(Console.ReadLine());
                ver.Add(t);
            }

            g.Dijkstr(a, b, ver);
        }
    }
}

/*

Граф для отладки
5
0 2 0 7 1
2 0 5 4 0
0 5 0 3 0
7 4 3 0 1
1 0 0 1 0

*/