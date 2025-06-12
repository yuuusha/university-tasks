using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Graph
{
    class Orgraph<T, N> : IGraph<T, N>
    {
        protected int count;
        protected Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>> adj;
        public string type;
        public string wtype;

        internal Orgraph()
        {
            count = 0;
            adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>();
            type = "";
            wtype = "";
        }

        internal Orgraph(string[] param)
        {
            count = 0;
            adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>();
            type = param[0];
            wtype = param[1];
        }

        internal Orgraph(string path)
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
                    for (int j = 0; j < nods.Length; j++)
                    {
                        tmp.Add(new Node<T>(Node<T>.ConvertT(nods[j])), new Edge<N>());
                    }
                    adj.Add(new Node<T>(Node<T>.ConvertT(s[0])), new Dictionary<Node<T>, Edge<N>>(tmp));
                }
            }
        }

        internal Orgraph(Orgraph<T, N> o)
        {
            count = o.count;
            adj = new Dictionary<Node<T>, Dictionary<Node<T>, Edge<N>>>(o.adj);
            type = o.type;
            wtype = o.wtype;
        }

        public string getType()
        {
            return type;
        }
        public string getWType()
        {
            return wtype;
        }
        public int getCount()
        {
            return count;
        }

        public virtual void Print()
        {
            foreach (var node in adj)
            {
                Console.Write($"{node.Key.Name}: ");
                foreach (var edge in node.Value)
                {
                    Console.Write($"{edge.Key.Name}");
                    if (!edge.Equals(node.Value.Last()))
                    {
                        Console.Write(", ");
                    }
                }
                Console.WriteLine();
            }
        }

        public virtual void Save(string path)
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
                        OUT.Write($"{edge.Key.Name}");
                        if (!edge.Equals(node.Value.Last()))
                        {
                            OUT.Write(", ");
                        }
                    }
                    OUT.WriteLine();
                }
            }
        }

        public void AddNode(T node)
        {
            Node<T> node_ = new Node<T>(node);
            if (!adj.ContainsKey(node_))
            {
                adj.Add(node_, new Dictionary<Node<T>, Edge<N>>());
            }
            else
            {
                throw new Exception("The node already exists");
            }
        }

        public virtual void AddEdge(T node1, T node2)
        {
            Node<T> Node1 = new Node<T>(node1);
            Node<T> Node2 = new Node<T>(node2);

            if (!adj.ContainsKey(Node1) || !adj.ContainsKey(Node2))
            {
                throw new Exception("The node does not exist");
            }

            if (!adj[Node1].ContainsKey(Node2))
            {
                adj[Node1].Add(Node2, new Edge<N>());
            }
            else
            {
                throw new Exception("The arc already exists");
            }
        }

        public void DeleteNode(T node)
        {
            Node<T> node_ = new Node<T>(node);
            if (adj.ContainsKey(node_))
            {
                adj.Remove(node_);
                
                foreach (var n in adj.Keys)
                {
                    if (adj[n].ContainsKey(node_))
                    {
                        adj[n].Remove(node_);
                    }
                }
            }
            else
            {
                throw new Exception("The node does not exist");
            }
        }

        public virtual void DeleteEdge(T node1, T node2)
        {
            Node<T> Node1 = new Node<T>(node1);
            Node<T> Node2 = new Node<T>(node2);

            if (!adj.ContainsKey(Node1) || !adj.ContainsKey(Node2))
            {
                throw new Exception("The node does not exist");
            }

            if (adj[Node1].ContainsKey(Node2))
            {
                adj[Node1].Remove(Node2);
            }
            else
            {
                throw new Exception("The arc does not exist");
            }
        }

        public int InDegree(T node)
        {
            Node<T> Node = new Node<T>(node);

            if (!adj.ContainsKey(Node))
            {
                throw new Exception("The node does not exist");
            }

            int k = 0;
            foreach (var n in adj)
            {
                if (n.Value.ContainsKey(Node)) {
                    k++;
                }
            }

            return k;
        }
    }
}
