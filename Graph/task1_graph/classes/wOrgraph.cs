using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    internal class wOrgraph<T, N> : Orgraph<T, N>
    {
        internal wOrgraph()
        {
            count = 0;
            adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>();
            type = "";
            wtype = "";
        }
        internal wOrgraph(string[] param)
        {
            count = 0;
            adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>();
            type = param[0];
            wtype = param[1];
        }
        internal wOrgraph(string path)
        {
            using (StreamReader IN = new StreamReader(path))
            {
                string[] _ = IN.ReadLine().Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries); ;
                type = _[0];
                wtype = _[1];
                count = int.Parse(IN.ReadLine());
                adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>();

                string[] s;
                string[] nods;
                for (int i = 0; i < count; i++)
                {
                    s = IN.ReadLine().Split(':');
                    nods = s[1].Split(new string[] { ", ", " " }, StringSplitOptions.RemoveEmptyEntries);


                    Dictionary<Node<T>, Edge<N>> tmp = new Dictionary<Node<T>, Edge<N>>();
                    string[] pair;
                    for (int j = 0; j < nods.Length; j++)
                    {
                        pair = nods[j].Split(new string[] { "(", ")" }, StringSplitOptions.RemoveEmptyEntries);
                        tmp.Add(new Node<T>(Node<T>.ConvertT(pair[0])), new Edge<N>(Edge<N>.ConvertN(pair[1])));
                    }
                    adj.Add(new Node<T>(Node<T>.ConvertT(s[0])), new Dictionary<Node<T>, Edge<N>>(tmp));
                }
            }
        }

        internal wOrgraph(wOrgraph<T, N> o)
        {
            count = o.count;
            adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>(o.adj);
            type = "";
            wtype = "";
        }

        public override void Print()
        {
            foreach (var node in adj)
            {
                Console.Write($"{node.Key.Name}: ");
                foreach (var edge in node.Value)
                {
                    Console.Write($"{edge.Key.Name}({edge.Value.Weight})");
                    if (!edge.Equals(node.Value.Last()))
                    {
                        Console.Write(", ");
                    }
                }
                Console.WriteLine();
            }
        }

        public override void Save(string path)
        {
            using (StreamWriter OUT = new StreamWriter(path))
            {
                OUT.WriteLine($"{getType()} {getWType()}");
                OUT.WriteLine(count);
                foreach (var node in adj)
                {
                    OUT.Write($"{node.Key.Name}: ");
                    foreach (var edge in node.Value)
                    {
                        OUT.Write($"{edge.Key.Name}({edge.Value.Weight})");
                        if (!edge.Equals(node.Value.Last()))
                        {
                            OUT.Write(", ");
                        }
                    }
                    OUT.WriteLine();
                }
            }
        }

        public virtual void AddEdge(T node1, T node2, N weight)
        {
            Node<T> Node1 = new Node<T>(node1);
            Node<T> Node2 = new Node<T>(node2);

            if (!adj.ContainsKey(Node1) || !adj.ContainsKey(Node2))
            {
                throw new Exception("The node does not exist");
            }

            if (!adj[Node1].ContainsKey(Node2))
            {
                adj[Node1].Add(Node2, new Edge<N>(weight));
            }
            else
            {
                throw new Exception("The arc already exist");
            }
        }

        public virtual void OverwriteWeight(T node1, T node2, N weight)
        {
            Node<T> Node1 = new Node<T>(node1);
            Node<T> Node2 = new Node<T>(node2);

            if (!adj.ContainsKey(Node1) || !adj.ContainsKey(Node2))
            {
                throw new Exception("The node does not exist");
            }
            if (adj[Node1].ContainsKey(Node2))
            {
                adj[Node1][Node2].Weight = weight;
            }
            else
            {
                throw new Exception("The arc does not exist");
            }
        }
    }
}
