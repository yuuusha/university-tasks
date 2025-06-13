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
            Graph g = new Graph(@"C:\Users\jojom\source\repos\ConsoleApp4\ConsoleApp4\bin\Debug\input.txt");

            int n = Convert.ToInt32(Console.ReadLine());

            g.SearchGm(n);
        }
    }
}

/*

Граф с гамильтоновым циклом
4
0 1 0 0
0 0 1 1
1 0 0 1
1 0 1 0

Граф без гамильтонового цикла
5
0 1 0 1 0
1 0 0 1 0
0 0 0 0 0
0 0 1 0 0
0 0 0 1 0

*/