using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Graph
{
    internal class wGraph<T, N> : wOrgraph<T, N>
    {
        internal wGraph() : base() { }

        internal wGraph(string path) : base(path) { }

        internal wGraph(wOrgraph<T, N> o) : base(o) { }
        internal wGraph(string[] param) : base(param) { }

        public override void AddEdge(T node1, T node2, N weight)
        {
            if (node1.Equals(node2))
            {
                throw new Exception("The self-loop is not possible in the graph");
            }
            else
            {
                base.AddEdge(node1, node2, weight);
                adj[new Node<T>(node2)].Add(new Node<T>(node1), new Edge<N>(weight));
            }
        }

        public override void DeleteEdge(T node1, T node2)
        {
            base.DeleteEdge(node1, node2);
            adj[new Node<T>(node2)].Remove(new Node<T>(node1));
        }

        public override void OverwriteWeight(T node1, T node2, N weight)
        {
            base.OverwriteWeight(node1, node2, weight);
            adj[new Node<T>(node2)][new Node<T>(node1)].Weight = weight;
        }
    }
}
