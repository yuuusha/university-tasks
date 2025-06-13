using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace Task
{
    class Program
    {
        class date
        {
            DateTime newDate;

            public date()
            {
                newDate = new DateTime(2010, 1, 1);
            }
            public date(int year, int month, int day)
            {
                newDate = new DateTime(year, month, day);
            }
            public date(DateTime a)
            {
                newDate = a;
            }

            public DateTime nextDate()
            {
                return newDate.AddDays(1);
            }
            public DateTime prevDate()
            {
                return newDate.AddDays(-1);
            }

            public DateTime CurDate
            {
                get
                {
                    return newDate;
                }
                set
                {
                    newDate = value;
                }
            }

            public int tillEnd()
            {
                int day = newDate.Day;
                int month = newDate.Month;
                if (month == 4 || month == 6 || month == 9 || month == 11)
                    return 30 - day;
                else if (month == 2 && this.IsLeap)
                    return 29 - day;
                else if (month == 2 && !this.IsLeap)
                    return 28 - day;
                else
                    return 31 - day;
            }

            public bool IsLeap
            {
                get
                {
                    return (((newDate.Year % 4 == 0) && (newDate.Year % 100 != 0)) || (newDate.Year % 400 == 0));
                }
            }

            public date this[int i]
            {
                get
                {
                    date a = new date(newDate.AddDays(i));
                    return a;
                }
            }

            public static bool operator !(date x)
            {
                return (x.tillEnd() != 0);
            }

            public static bool operator true(date x)
            {
                return (x.CurDate.DayOfYear == 1);
            }
            public static bool operator false(date x)
            {
                return (x.CurDate.DayOfYear != 1);
            }
            public static bool operator &(date x, date y)
            {
                return (x.newDate == y.newDate);
            }

        }

        static void Main(string[] args)
        {
            date a = new date(); //конструктор по умолчанию: a = 01.01.2010;
            date b = new date(2022, 11, 22); //b = 22.11.2022

            Console.WriteLine("a = " + a.CurDate); //демонстрация работы свойства CurDate
            Console.WriteLine("b = " + b.CurDate);

            Console.WriteLine("\nThe day after b = " + b.nextDate());
            Console.WriteLine("The day before b = " + b.prevDate());
            Console.WriteLine("Days till to the end after b = " + b.tillEnd());

            a.CurDate = new DateTime(2022, 11, 22);
            Console.WriteLine("\nNew a = " + a.CurDate);
            Console.WriteLine("Is a leap? " + a.IsLeap);

            Console.WriteLine("\nFourth day before a = " + a[-4].CurDate);
            Console.WriteLine("Third day after a = " + a[3].CurDate);

            Console.WriteLine("\nIsn't a end of the month? " + !a);

            if (a)
                Console.WriteLine("a is start of the year");
            else
                Console.WriteLine("a isn't a start of the year");

            if (a & b)
                Console.WriteLine("a and b is equal");
            else
                Console.WriteLine("a and b isn't equal");
        }
    }
}
