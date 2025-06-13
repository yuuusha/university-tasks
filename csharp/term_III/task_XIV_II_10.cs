using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Task
{
    class Program
    {
        struct Student : IComparable<Student>
        {
            string name, surname, patr;
            int year, group;
            public int sec;

            public Student(string[] fullname)
            {
                name = fullname[0];
                surname = fullname[1];
                patr = fullname[2];
                year = Convert.ToInt32(fullname[3]);
                group = Convert.ToInt32(fullname[4]);
                sec = Convert.ToInt32(fullname[5]);
            }

            public int CompareTo(Student a)
            {
                if (this.sec == a.sec)
                    return 0;
                else if (this.sec > a.sec)
                    return 1;
                else
                    return -1;
            }

            public void Show()
            {
                using (StreamWriter OUT = new StreamWriter("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/output.txt", true))
                {
                    OUT.WriteLine(name + " " + surname + " " + patr + " " + year + " " + group + " " + sec);
                }
            }
        }

        static void Main(string[] args)
        {
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input.txt", Encoding.GetEncoding(1251)))
            {
                    List<Student> mass = new List<Student>();
                    int n = Convert.ToInt32(IN.ReadLine());
                    string[] s;

                    for (int i = 0; i < n; i++)
                    {
                        s = IN.ReadLine().Split();
                        mass.Add(new Student(s));
                    }

                    mass.Sort();

                    int k = 3;
                    int j = 0;
                    while (k > 0 && j < n)
                    {
                        mass[j].Show();

                        if (j < n - 1)
                            if (mass[j + 1].sec != mass[j].sec)
                                k--;

                        j++;
                    }
                
            }
        }
    }
}
