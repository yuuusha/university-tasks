using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace Task
{
    class Program
    {
        static void Main(string[] args)
        {
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/f.txt", Encoding.GetEncoding(1251)))
            {
                string line = IN.ReadToEnd();
                StringBuilder s = new StringBuilder(line);

                using (StreamWriter OUT = new StreamWriter("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/g.txt", false))
                {
                    for (int i = 0; i < line.Length; i++)
                    {
                        if (char.IsPunctuation(line[i]))
                        {
                            OUT.Write(line[i]);
                        }
                    }
                }

                string[] c = { ",", ".", "!", ")" };
                foreach (string x in c)
                    s.Replace(x, "");

                using (StreamWriter OUT2 = new StreamWriter("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/h.txt", false))
                {
                    OUT2.Write(s);
                }
            }
        }
    }
}

