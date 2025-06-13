using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input21_1.txt", Encoding.GetEncoding(1251)))
            {
                string s = IN.ReadToEnd();
                string[] num = s.Split();

                BinaryTree MyTree = new BinaryTree();

                for (int i = 0; i < num.Length; i++)
                {
                    MyTree.Add(Convert.ToInt32(num[i]));
                }

                MyTree.Preorder();

                Console.WriteLine(MyTree.OnlyRight());

            }
        }
    }
}
