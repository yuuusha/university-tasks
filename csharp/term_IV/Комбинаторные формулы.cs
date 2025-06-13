using System;

namespace Комбинаторные_формулы
{
    class Комбинаторика
    {
        public static ulong factor(ulong n)
        {
            if ((n == 0) || (n == 1))
                return 1;
            return n * factor(n - 1);
        }

        public static ulong C(ulong n, ulong k)
        {
            return factor(n) / (factor(k) * factor(n-k));
        }

        public static ulong U(ulong n, ulong k)
        {
            return (ulong)Math.Pow(k, n);
        }

        public static ulong Uz(ulong n, ulong k)
        {
            ulong temp = 0;
            for (ulong i = 0; i <= k-1; i++)
            {
                temp += (ulong)(Math.Pow(-1, i) * C(k, i) * Math.Pow(k - i, n));
            }
            return temp;
        }

        public static ulong T(ulong n, ulong k)
        {
            return C(n + k - 1, k - 1);
        }

        public static ulong Tz(ulong n, ulong k)
        {
            return C(n - 1, k - 1);
        }     
        
        public static ulong V(ulong n, ulong k)
        {
            ulong temp = 0;
            for (ulong i = 1; i <= k; i++)
            {
                temp += Vz(n, i);
            }
            return temp;
        }

        public static ulong Vz(ulong n, ulong k)
        {
            return Uz(n, k) / factor(k);
        }

        public static ulong Wz(ulong n, ulong k)
        {
            if ((n == k) || (n == 1))
                return 1;
            if (k > n)
                return 0;
            if (k == 2)
                return n / (ulong)2;
            return W(n - k, k);
        }

        public static ulong W(ulong n, ulong k)
        {
            if (n == 1)
                return 1;
            ulong temp = 0;
            for (ulong i = 1; i <= k; i++)
            {
                temp += Wz(n, i);
            }
            return temp;
        }
        static void Main(string[] args)
        {
            bool flag = true;

            while (flag)
            {
                Console.WriteLine("Количество шаров:");
                ulong n = ulong.Parse(Console.ReadLine());
                Console.WriteLine("Количество ящиков:");
                ulong k = ulong.Parse(Console.ReadLine());

                Console.WriteLine("1. Шары различны, ящики различны, могут быть пустые      U");
                Console.WriteLine("2. Шары различны, ящики различны, без пустых             U*");
                Console.WriteLine("3. Шары одинаковы, ящики различны, могут быть пустые     Т");
                Console.WriteLine("4. Шары одинаковы, ящики различны, без пустых            Т*");
                Console.WriteLine("5. Шары различны, ящики одинаковы, могут быть пустые     V");
                Console.WriteLine("6. Шары различны, ящики одинаковы, без пустых            V*");
                Console.WriteLine("7. Шары одинаковы, ящики одинаковы, могут быть пустые    W");
                Console.WriteLine("8. Шары одинаковы, ящики одинаковы, без пустых           W*");

                int t = Convert.ToInt32(Console.ReadLine());

                switch (t)
                {
                    case 1:
                        {
                            Console.WriteLine("U({0},{1}) = {2}", n, k, U(n, k));
                            break;
                        }
                    case 2:
                        {
                            Console.WriteLine("U*({0},{1}) = {2}", n, k, Uz(n, k));
                            break;
                        }
                    case 3:
                        {
                            Console.WriteLine("T({0},{1}) = {2}", n, k, T(n, k));
                            break;
                        }
                    case 4:
                        {
                            Console.WriteLine("T*({0},{1}) = {2}", n, k, Tz(n, k));
                            break;
                        }
                    case 5:
                        {
                            Console.WriteLine("V({0},{1}) = {2}", n, k, V(n, k));
                            break;
                        }
                    case 6:
                        {
                            Console.WriteLine("V*({0},{1}) = {2}", n, k, Vz(n, k));
                            break;
                        }
                    case 7:
                        {
                            Console.WriteLine("W({0},{1}) = {2}", n, k, W(n, k));
                            break;
                        }
                    case 8:
                        {
                            Console.WriteLine("W*({0},{1}) = {2}", n, k, Wz(n, k));
                            break;
                        }
                    case 9:
                        {
                            flag = false;
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Режим работы отсутствует");
                            break;
                        }
                }
                Console.WriteLine();
            }
        }
    }
}
