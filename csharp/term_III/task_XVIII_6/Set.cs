using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task18
{
    class Set: Goods
    {
        string name;
        List<Product> listOfProds;

        public Set(string s, List<Product> list)
        {
            name = s;
            listOfProds = new List<Product>(list);
            foreach (Product x in list)
            {
                price += x.price;
            }
        }

        internal override void Show()
        {
            Console.WriteLine("Name: {0}, Price: {1}", name, price);
            Console.WriteLine("{");
            foreach (Product x in listOfProds)
            {
                Console.Write("\t");
                x.Show();
            }
            Console.WriteLine("}");
        }

        internal override bool isExpired(DateTime curDate)
        {
            foreach (Product x in listOfProds)
            {
                if (x.isExpired(curDate))
                    return true;
            }
            return false;
        }
    }
}
