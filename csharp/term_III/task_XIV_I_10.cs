using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Task
{
    class Program
    {
        public struct Point3
        {
            public int x, y, z;
            public Point3(int x, int y, int z)
            {
                this.x = x;
                this.y = y;
                this.z = z;
            }
            public void Show()
            {
                Console.Write("({0}, {1}, {2})", x, y, z);
            }
        }
        public struct Point
        {
            public int x, y;
            public Point(int x, int y)
            {
                this.x = x;
                this.y = y;
            }
            public void Show()
            {
                Console.WriteLine("({0}, {1})", x, y);
            }
        }

        public static double dist3(Point3 a, Point3 b)
        {
            return Math.Sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
        }
        public static double dist(Point a, Point b)
        {
            return Math.Sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
        }

        static void Main(string[] args)
        {
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/oxy.txt", Encoding.GetEncoding(1251)))
            {

                List<Point3> mass = new List<Point3>();
                string[] s;

                int n = Convert.ToInt32(IN.ReadLine());
                for (int i = 0; i < n; i++)
                {
                    s = IN.ReadLine().Split();
                    mass.Add(new Point3(Convert.ToInt32(s[0]), Convert.ToInt32(s[1]), Convert.ToInt32(s[2])));
                }

                

                int r = 3, k, maxk = 0, ik = 0;

                for (int i = 0; i < mass.Count; i++)
                {
                    k = 0;

                    for (int j = 0; j < mass.Count; j++)
                        if (dist3(mass[i], mass[j]) <= r)
                            k++;

                    if (k > maxk)
                    {
                        maxk = k;
                        ik = i;
                    }
                    mass[i].Show();
                    Console.WriteLine(" = " + k);
                }

                Console.WriteLine("answer:");
                mass[ik].Show();
                Console.WriteLine();
            }
        }
    }
}
