using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp3
{
    public class Node : IComparable
    {
        private char inf;
        private int freq;
        private int height;
        //public string code;
        private Node left;
        private Node right;

        public Node(char ch, int fr, int ht = 0)
        {
            inf = ch;
            freq = fr;
            height = ht;
            //code = "";
            left = null;
            right = null;
        }

        public Node(char ch, int fr, int ht, Node l, Node r) : this(ch, fr, ht)
        {
            left = l;
            right = r;
        }

        public static Node Concatenation(Node A, Node B)
        {
            Node newNode = new Node(A.inf, A.freq + B.freq, Math.Max(A.height, B.height) + 1, A, B);
            return newNode;
        }

        public int CompareTo(object a)
        {
            Node A = a as Node;
            if (freq != A.freq)
                return freq.CompareTo(A.freq);
            if (height != A.height)
                return height.CompareTo(A.height);
            return inf.CompareTo(A.inf);
        }

        public static void Preorder(Node r) //прямой обход дерева
        {
            if (r != null)
            {
                Console.Write("{0}({1}) |", r.inf, r.freq);
                Preorder(r.left);
                Preorder(r.right);
            }
        }

        public static void FormCode(Node r, string str, ref Dictionary<char, string> codingTable)
        {
            if (r != null)
            {
                FormCode(r.left, str + "0", ref codingTable);
                FormCode(r.right, str + "1", ref codingTable);

                if (r.left == null && r.right == null)
                {
                    //r.code = str.ToString();
                    codingTable.Add(r.inf, str);
                }
            }
        }

    }
}
