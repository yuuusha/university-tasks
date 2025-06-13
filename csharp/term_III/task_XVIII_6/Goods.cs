using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task18
{
    abstract public class Goods : IComparable<Goods>
    {
        internal int price;
        abstract internal void Show();
        abstract internal bool isExpired(DateTime curDate);

        public int CompareTo(Goods a)
        {
            return this.price - a.price;
        }
    }
}
