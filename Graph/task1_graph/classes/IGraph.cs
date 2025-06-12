using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    internal interface IGraph<T, N>
    {
        void Print();
        void Save(string path);
        void AddNode(T node);
        void AddEdge(T node1, T node2);
        void DeleteNode(T node);
        void DeleteEdge(T node1, T node2);
        string getType();
        string getWType();
        int getCount();
        
    }
}
