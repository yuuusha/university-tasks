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


            Console.WriteLine("Исходный граф: ");
            g.Show();

            int a = Convert.ToInt32(Console.ReadLine());
            int b = Convert.ToInt32(Console.ReadLine());

            g.DeleteEdge(a, b);

            Console.WriteLine("Удалено ребро ({0}, {1}): ", a, b);
            g.Show();

        }
    }
}
