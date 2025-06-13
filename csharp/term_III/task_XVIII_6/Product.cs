using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task18
{
    class Product : Goods
    {

        internal string name;
        internal DateTime prodDate;
        internal TimeSpan timeOfLife;

        //public Product()
        //{
        //    name = "";
        //    price = 0;
        //    prodDate = new DateTime();
        //    timeOfLife = new TimeSpan();
        //}

        public Product(string s)
        {
            string[] ss = s.Split('|');
            string[] subss = ss[2].Split('/');

            name = ss[0];
            price = Convert.ToInt32(ss[1]);
            prodDate = new DateTime(Convert.ToInt32(subss[0]), Convert.ToInt32(subss[1]), Convert.ToInt32(subss[2]));
            timeOfLife = new TimeSpan(Convert.ToInt32(ss[3]), 0, 0, 0);
        }

        internal override void Show()
        {
            Console.WriteLine("Name: {0}, Price: {1}, Production date: {2}, Time of life: {3}", name, price, prodDate.ToString("yyyy/MM/dd"), timeOfLife.Days); 
        }

        internal override bool isExpired(DateTime curDate)
        {
            return prodDate.Add(timeOfLife) < curDate;
        }
    }
}
