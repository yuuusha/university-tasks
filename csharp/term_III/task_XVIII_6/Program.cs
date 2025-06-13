using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace Task18
{
    class Program
    {
        static public DateTime curDate = DateTime.Now;
        static public char[] separators = { '\n' };

        static void Main(string[] args)
        {
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp3/ConsoleApp3/input18.txt", Encoding.GetEncoding(1251)))
            {
                string[] s = IN.ReadToEnd().Split(separators, StringSplitOptions.RemoveEmptyEntries);

                List<Product> listOfProds = new List<Product>();

                foreach (string x in s)
                {
                    listOfProds.Add(new Product(x));
                }

                Console.WriteLine("The list of products:");
                foreach (Product x in listOfProds)
                {
                    x.Show();
                }

                Console.WriteLine("\nThe following items are expired:");
                foreach (Product x in listOfProds)
                {
                    if (x.isExpired(curDate))
                    {
                        x.Show();
                    }
                }


                Console.WriteLine("\n-----------------\nSorted list by price:");
                listOfProds.Sort();
                foreach (Product x in listOfProds)
                {
                    x.Show();
                }


                Set setOfProds = new Set("My Set", listOfProds);

                Console.WriteLine("\n------------------\nThe set of products:");
                setOfProds.Show();

                Console.WriteLine("Is this set expired? " + setOfProds.isExpired(curDate));

            }

            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp3/ConsoleApp3/input18batch.txt", Encoding.GetEncoding(1251)))
            {
                string[] s = IN.ReadToEnd().Split(separators, StringSplitOptions.RemoveEmptyEntries);

                List<Batch> listOfBatches = new List<Batch>();

                foreach (string x in s)
                {
                    listOfBatches.Add(new Batch(x));
                }

                Console.WriteLine("\n------------------\nThe list of batches:");
                foreach (Batch x in listOfBatches)
                {
                    x.Show();
                }

                Console.WriteLine("\nThe following items are expired:");
                foreach (Batch x in listOfBatches)
                {
                    if (x.isExpired(curDate))
                    {
                        x.Show();
                    }
                }
            }
        }
    }
}
