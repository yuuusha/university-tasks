using System;
using System.Collections.Generic;
using System.Dynamic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    internal class CGraph<T, N>
    {
        public static IGraph<T, N> Create()
        {
            return new Orgraph<T, N>();
        }

        public static IGraph<T, N> Create(string path)
        {
            string[] param;
            using (StreamReader IN = new StreamReader(path))
            {
                param = IN.ReadLine().Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);
            }

            if (param[0] == "o" && param[1] == "n")
            {
                return new Orgraph<T, N>(path);
            }
            else if (param[0] == "o" && param[1] == "w")
            {
                return new wOrgraph<T, N>(path);
            }
            else if (param[0] == "n" && param[1] == "n")
            {
                return new Graph<T, N>(path);
            }
            else if (param[0] == "n" && param[1] == "w")
            {
                return new wGraph<T, N>(path);
            }
            else
            {
                return null;
                throw new Exception("Can not create graph");
            }
        }
        public static IGraph<T, N> Create(string[] param)
        {
            if (param[0] == "o" && param[1] == "n")
            {
                return new Orgraph<T, N>(param);
            }
            else if (param[0] == "o" && param[1] == "w")
            {
                return new wOrgraph<T, N>(param);
            }
            else if (param[0] == "n" && param[1] == "n")
            {
                return new Graph<T, N>(param);
            }
            else if (param[0] == "n" && param[1] == "w")
            {
                return new wGraph<T, N>(param);
            }
            else
            {
                return null;
                throw new Exception("Can not create graph");
            }
        }
    }
}
