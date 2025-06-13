using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp4
{
    public class Graph
    {
        private class Node
        {

            private int[,] array;

            public int this [int i, int j]
            {
                get { return array[i, j]; }
                set { array[i, j] = value; }
            }

            public int Size
            {
                get { return array.GetLength(0); }
            }

            private bool[] nov;

            public void NovSet()
            {
                for (int i = 0; i < Size; i++)
                    nov[i] = true;
            }

            public Node(int [,] a)
            {
                array = a;
                nov = new bool[a.GetLength(0)];
            }

            public void AddEdge(int a, int b)
            {
                //if (array[a, b] != 0)
                //    Console.WriteLine("Ребро уже существует");
                array[a, b] = 1;
            }
            public void DeleteEdge(int a, int b)
            {
                //if (array[a, b] == 0)
                //    Console.WriteLine("Ребра уже не существует");
                array[a, b] = 0;
            }

            public void Dfs(int v) //обход в глубину
            {
                Console.Write("{0} ", v);
                nov[v] = false;

                for (int u = 0; u < Size; u++)
                {
                    if (array[v, u] != 0 && nov[u])
                        Dfs(u);
                }
            }

            public void Bfs(int v) //обход в ширину 
            {
                Queue<int> q = new Queue<int>();
                q.Enqueue(v);
                nov[v] = false;

                while (q.Count > 0)
                {
                    v = q.Dequeue();
                    Console.Write("{0} ", v);

                    for (int u = 0; u < Size; u++)
                    {
                        if (array[v,u] != 0 && nov[u])
                        {
                            q.Enqueue(u);
                            nov[u] = false;
                        }
                    }
                }
            }

            public void SearchGm(int k, ref int[] St, int ver, ref bool flag)
            {
                int v = St[k - 1];

                for (int j = 0; j < array.GetLength(0); j++)
                {
                    if (array[v,j] != 0)
                    {
                        if (k == array.GetLength(0) && j == ver && flag)
                        {
                            St[k] = j;
                            foreach (int item in St)
                                Console.Write("{0} ", item);
                            flag = false;
                        }
                        else
                        {
                            if (nov[j])
                            {
                                St[k] = j;
                                nov[j] = false;
                                SearchGm(k + 1, ref St, ver, ref flag);
                                nov[j] = true;
                            }
                        }
                    }
                }

                if (flag)
                    Console.WriteLine("Гамильтонов цикл отсутствует");
            }

            public long[] Dijkstr(int v, int vk, List<int> ver, out int[] p)
            {
                nov[v] = false; 
                                
                int[,] c = new int[Size, Size];
                for (int i = 0; i < Size; i++)
                {
                    for (int u = 0; u < Size; u++)
                        if (array[i, u] == 0 || i == u || !ver.Exists(x => x == u))
                            c[i, u] = int.MaxValue;
                        else
                            c[i, u] = array[i, u];
                }

                long[] d = new long[Size];
                p = new int[Size];
                for (int u = 0; u < Size; u++)
                {
                    if (u != v)
                    {
                        d[u] = c[v, u];
                        p[u] = v;
                    }
                }

                for (int i = 0; i < Size - 1; i++) 
                {
                    long min = int.MaxValue;
                    int w = 0;
                    for (int u = 0; u < Size; u++)
                    {
                        if (nov[u] && min > d[u])
                        {
                            min = d[u];
                            w = u;
                        }
                    }

                    nov[w] = false;
                    if (nov[vk] == false)
                        return d;

                    for (int u = 0; u < Size; u++)
                    {
                        long distance = d[w] + c[w, u];
                        if (nov[u] && d[u] > distance)
                        {
                            d[u] = distance;
                            p[u] = w;
                        }
                    }

                }
                return d; 
            } 

            public void WayDijkstr(int a, int b, int[] p, ref Stack<int> items)
            {
                items.Push(b); 
                if (a == p[b]) 
                {
                    items.Push(a);
                }
                else 
                { 
                    WayDijkstr(a, p[b], p, ref items);
                }
            }

            public bool this[int i]
            {
                get { return nov[i]; }
                set { nov[i] = value; }
            }
        }

        private Node graph;

        public Graph(StreamReader IN, int n)
        {
            int[,] a = new int[n, n];

            for (int i = 0; i < n; i++)
            {
                string line = IN.ReadLine();
                string[] mas = line.Split(' ');

                for (int j = 0; j < n; j++)
                a[i, j] = Convert.ToInt32(mas[j]);
            }

            graph = new Node(a);
        }

        public void Recalc(List<Town> towns)
        {
            int c;
            for (int i = 0; i < graph.Size; i++)
            {
                for (int j = 0; j < graph.Size; j++)
                {
                    if (graph[i, j] == 1)
                    {
                        c = (int)Math.Sqrt((towns[i].x - towns[j].x) * (towns[i].x - towns[j].x) + (towns[i].y - towns[j].y) * (towns[i].y - towns[j].y));
                        graph[i, j] = c;
                    }
                }
            }
        }

        public void Show()
        {
            for (int i = 0; i < graph.Size; i++)
            {
                for (int j = 0; j < graph.Size; j++)
                    Console.Write("{0} ", graph[i, j]);
                Console.WriteLine();
            }
        }

        public void Dfs(int v)
        {
            graph.NovSet();
            graph.Dfs(v);
            Console.WriteLine();
        }

        public void Bfs(int v)
        {
            graph.NovSet();
            graph.Bfs(v);
            Console.WriteLine();
        }

        public void AddEdge(int a, int b)
        {
            graph.AddEdge(a, b);
        }

        public void DeleteEdge(int a, int b)
        {
            graph.DeleteEdge(a, b);
        }

        public void SearchGm(int ver)
        {
            bool flag = true;
            graph.NovSet();
            int[] St = new int[graph.Size + 1];
            St[0] = ver;
            graph[ver] = false;
            graph.SearchGm(1, ref St, ver, ref flag);
        }

        public void Dijkstr(int v, int vk, List<int> ver)
        {
            graph.NovSet();
            int[] p;
            long[] d = graph.Dijkstr(v, vk, ver, out p);
            Stack<int> st = new Stack<int>();
            if (d[vk] != int.MaxValue)
            {
                Console.Write("Минимальная длина от {0} до {1} = {2}\nПуть: ", v, vk, d[vk]);
                graph.WayDijkstr(v, vk, p, ref st);
                while (st.Count > 0)
                {
                    Console.Write("{0} ", st.Pop());
                }
            }
            else
            {
                Console.WriteLine("Вершина {1} не достижима из вершины {0}", v, vk);
            }
        }

    }
}
