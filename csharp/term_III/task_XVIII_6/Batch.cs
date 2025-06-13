using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task18
{
    class Batch: Goods
    {
        Product prod;
        internal int count;

        //public Batch(string s) : base(s)
        //{
        //    string[] ss = s.Split('|');
        //    count = Convert.ToInt32(ss[4]);
        //} 

        public Batch(string s)
        {
            string[] ss = s.Split('|');
            string[] subss = ss[2].Split('/');

            //name = ss[0];
            //prodDate = new DateTime(Convert.ToInt32(subss[0]), Convert.ToInt32(subss[1]), Convert.ToInt32(subss[2]));
            //timeOfLife = new TimeSpan(Convert.ToInt32(ss[3]), 0, 0, 0);
            prod = new Product(s);
            count = Convert.ToInt32(ss[4]);
            price = Convert.ToInt32(ss[1]) * count;
        }

        internal override void Show()
        {
            Console.WriteLine("Name: {0}, Price: {1}, Count: {2}, Production date: {3}, Time of life: {4}", prod.name, price, count, prod.prodDate.ToString("yyyy/MM/dd"), prod.timeOfLife.Days);
        }

        internal override bool isExpired(DateTime curDate)
        {
            return prod.prodDate.Add(prod.timeOfLife) < curDate;
        }
    }
}
