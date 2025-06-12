using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    internal class Node<T>
    {
        T name;

        internal T Name
        {
            get { return name; }
            set { name = value; }
        }

        internal Node(T name)
        {
            Name = name;
        }

        public static T ConvertT(string s)
        {
            T result;
            try
            {
                result = (T)Convert.ChangeType(s, typeof(T));
            }
            catch (InvalidCastException)
            {
                throw new Exception("Invalid input");
            }

            return result;
        }

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }

            Node<T> otherNode = (Node<T>)obj;

            return Name.Equals(otherNode.Name);
        }

        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
    }
    internal class Edge<N>
    {
        N weight;

        internal N Weight
        {
            get { return weight; }
            set { weight = value; }
        }

        internal Edge()
        {
            weight = default;
        }

        internal Edge(N w)
        {
            weight = w;
        }

        public static N ConvertN(string s)
        {
            N result;
            try
            {
                result = (N)Convert.ChangeType(s, typeof(N));
            }
            catch (InvalidCastException)
            {
                throw new Exception("Invalid input");
            }

            return result;
        }
    }
}
