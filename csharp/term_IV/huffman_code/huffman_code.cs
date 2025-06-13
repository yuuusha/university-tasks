using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace ConsoleApp3
{

    class Program
    {

        public static Dictionary<char, string> codingTable = new Dictionary<char, string>();

        public static Dictionary<char, string> getCodingTable(string s)
        {
            Dictionary<char, int> alphabet = new Dictionary<char, int>();

            foreach (char x in s)
            {
                if (alphabet.ContainsKey(x))
                    alphabet[x] += 1;
                else
                    alphabet.Add(x, 1);
            }

            SortedSet<Node> set = new SortedSet<Node>();

            foreach (var x in alphabet)
            {
                set.Add(new Node(x.Key, x.Value, 0));
            }

            var setEnumerator = set.GetEnumerator();
            Node a, b;

            while (set.Count > 1)
            {
                setEnumerator.MoveNext();
                a = setEnumerator.Current;
                setEnumerator.MoveNext();
                b = setEnumerator.Current;
                Node tmp = Node.Concatenation(a, b);
                set.Remove(a);
                set.Remove(b);
                set.Add(tmp);
                setEnumerator = set.GetEnumerator();
            }

            setEnumerator.MoveNext();
            Node root = setEnumerator.Current;

            /*Dictionary<char, string>*/ codingTable = new Dictionary<char, string>();
            string ss = "";
            Node.FormCode(root, ss, ref codingTable);

            return codingTable;
        }

        public static StringBuilder getCodeString(string s, Dictionary<char, string> codingTable)
        {
            StringBuilder output_s = new StringBuilder();

            output_s.Append(Convert.ToString(codingTable.Count, 2).PadLeft(8, '0'));

            foreach (var x in codingTable)
            {
                output_s.Append(Convert.ToString(x.Key, 2).PadLeft(16, '0'));
                output_s.Append(Convert.ToString(x.Value.Length, 2).PadLeft(4, '0'));
                output_s.Append(x.Value);
            }

            foreach (var x in s)
            {
                output_s.Append(codingTable[x]);
            }

            int nulls = (8 - (output_s.Length + 3) % 8) != 8 ? (8 - (output_s.Length + 3) % 8) : 0;
            string null_s = "";
            output_s.Insert(0, Convert.ToString(nulls, 2).PadLeft(3, '0'));
            output_s.Append(null_s.PadLeft(nulls, '0'));

            return output_s;
        }

        public static void TxtToBin()
        {
            string input_s;

            using (StreamReader IN = new StreamReader("input_h.txt", Encoding.GetEncoding(1251)))
            {
                input_s = IN.ReadToEnd();
            }

            /*Dictionary<char, string>*/ codingTable = getCodingTable(input_s);

            //foreach (var x in codingTable) 
            //{
            //    Console.WriteLine("{0}:{1}", x.Key, x.Value);
            //}

            StringBuilder output_s = getCodeString(input_s, codingTable);

            //Console.WriteLine(output_s);

            using (BinaryWriter OUT = new BinaryWriter(File.Open("output_h.bin", FileMode.Create)))
            {
                for (int i = 0; i < output_s.Length; i += 8)
                {
                    OUT.Write(Convert.ToByte(output_s.ToString(i, 8), 2));
                }
            }
        }

        public static void BinToTxt()
        {
            StringBuilder input_b = new StringBuilder();
            byte bytes;

            using (BinaryReader IN = new BinaryReader(File.OpenRead("output_h.bin"), Encoding.ASCII))
            {
                while (IN.PeekChar() > -1)
                {
                    bytes = IN.ReadByte();
                    input_b.Append(Convert.ToString(bytes, 2).PadLeft(8, '0'));
                }
            }

            int nulls = Convert.ToInt32(input_b.ToString(0, 3), 2);
            input_b.Length -= nulls;

            int alphaPower = Convert.ToInt32(input_b.ToString(3, 8), 2);

            Dictionary<string, char> decodingTable = new Dictionary<string, char>();

            char ch;
            int chLength;
            string code;

            int iter = 11;

            for (int i = 0; i < alphaPower; i++)
            {
                ch = (char)Convert.ToInt32(input_b.ToString(iter, 16), 2);
                iter += 16;
                chLength = Convert.ToInt32(input_b.ToString(iter, 4), 2);
                iter += 4;
                code = input_b.ToString(iter, chLength);
                iter += chLength;
                decodingTable.Add(code, ch);
            }

            StringBuilder decoderString = new StringBuilder();
            StringBuilder output_b = new StringBuilder();


            while (iter < input_b.Length)
            {
                while (!decodingTable.ContainsKey(decoderString.ToString()))
                {
                    decoderString.Append(input_b[iter]);
                    iter++;
                }

                output_b.Append(decodingTable[decoderString.ToString()]);
                decoderString.Clear();

            }

            using (StreamWriter OUT = new StreamWriter("output_h.txt", false))
            {
                OUT.Write(output_b);
            }
        }

        static void Main(string[] args)
        {

            Console.WriteLine("0. Закодировать и сжать файл\n1. Раскодировать ранее сжатый файл");
            int mode = Convert.ToInt32(Console.ReadLine());
            Console.Clear();
            switch (mode) 
            {
                case 0:
                    {
                        TxtToBin();
                        var fileIN = new FileInfo("input_h.txt").Length;
                        var fileOUT = new FileInfo("output_h.bin").Length;
                        Console.WriteLine("Кодирование прошло успешно.\nРазмер исходного файла: {0} байт.\nРазмер сжатого файла: {1} байт.", fileIN, fileOUT);
                        Console.WriteLine("2. Просмотреть коды символов в алфавите\n3. Выйти из программы");
                        mode = Convert.ToInt32(Console.ReadLine());
                        switch (mode) 
                        {
                            case 2:
                                {
                                    Console.Clear();
                                    Console.WriteLine("Количество символов в алфавите: ", codingTable.Count);
                                    foreach (var x in codingTable)
                                    {
                                        Console.WriteLine("{0}: {1}", x.Key, x.Value);
                                    }
                                    break;
                                }
                            default:
                                {
                                    return;
                                }
                        }
                        break;
                    }
                case 1:
                    {
                        //var fileIN = new FileInfo("output_h.bin").Length;
                        //var fileOUT = new FileInfo("output_h.txt").Length;
                        BinToTxt();
                        Console.WriteLine("Декодирование прошло успешно.\nВы можете просмотреть полученное сообщение в файле");
                        //Console.WriteLine("Размер исходного файла: {0} байт.\nРазмер декодированного файла: {1} байт.", fileIN, fileOUT);
                        break;
                    }
                default: Console.WriteLine("Error: mode isn't exist"); break;
            }
        }
    }
}
