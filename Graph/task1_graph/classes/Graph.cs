using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Graph
{
    internal class Graph<T, N> : Orgraph<T, N>
    {
        internal Graph() : base() { }

        internal Graph(string path) : base(path) { }

        internal Graph(Graph<T, N> o) : base(o) { }

        internal Graph(string[] param) : base (param) { }

        public override void AddEdge(T node1, T node2)
        {
            if (node1.Equals(node2))
            {
                throw new Exception("The self-loop is not possible in the graph");
            }
            else
            {
                base.AddEdge(node1, node2);
                adj[new Node<T>(node2)].Add(new Node<T>(node1), new Edge<N>());
            }
        }

        public override void DeleteEdge(T node1, T node2)
        {
            base.DeleteEdge(node1, node2);
            adj[new Node<T>(node2)].Remove(new Node<T>(node1));
        }
    }
}
