using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Graph
{
    internal class Program
    {
        static void Start()
        {
            Console.WriteLine("0. Exit");
            Console.WriteLine("1. Create empty graph");
            Console.WriteLine("2. Upload graph from the file");
        }
        static void Menu(string wtype, string type)
        {
            Console.WriteLine();
            Console.WriteLine("0. Exit");
            Console.WriteLine("1. Add node");
            Console.WriteLine("2. Add edge");
            Console.WriteLine("3. Delete node");
            Console.WriteLine("4. Delete edge");
            Console.WriteLine("5. Save graph");
            if (wtype == "w")
            {
                Console.WriteLine("6. Update weight");
            }
            if (type == "o")
            {
                Console.WriteLine("7. Get indegree of node");
            }
            
        }
        static void Press()
        {
            Console.WriteLine("Press any key to continue...");
            Console.ReadLine();
        }
        
        static void Main(string[] args)
        {
            bool isOn = true;
            IGraph<string, int> gr = CGraph<string, int>.Create();

            Start();
            int n = int.Parse(Console.ReadLine());
            try
            {
                switch (n)
                {
                    case 0:
                        {
                            isOn = false;
                            break;
                        }
                    case 1:
                        {
                            Console.WriteLine("Input graph type");
                            string[] type = Console.ReadLine().Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                            gr = CGraph<string, int>.Create(type);
                            break;
                        }
                    case 2:
                        {
                            Console.WriteLine("Input file path");
                            string path = Console.ReadLine();
                            if (File.Exists(path))
                            {
                                gr = CGraph<string, int>.Create(path);
                            }
                            else
                            {
                                throw new Exception("Invalid input");
                            }
                            break;
                        }
                    default:
                        {
                            throw new Exception("Invalid input");
                        }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                Press();
                isOn = false;
            }

            while (isOn)
            {
                Console.Clear();
                gr.Print();
                Menu(gr.getWType(), gr.getType());
                n = int.Parse(Console.ReadLine());

                switch (n)
                {
                    case 1:
                        {
                            Console.WriteLine("Input node name \t Z - undo");
                            string name = Console.ReadLine();
                            if (name == "z" || name == "Z") { break; }
                            try
                            {
                                gr.AddNode(name);
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e.Message);
                                Press();
                            }
                            break;
                        }
                    case 2:
                        {
                            Console.WriteLine("Input node names \t Z - undo");
                            string name1 = Console.ReadLine();
                            if (name1 == "z" || name1 == "Z") { break; }
                            string name2 = Console.ReadLine();
                            if (name2 == "z" || name2 == "Z") { break; }
                            int weight = 0;
                            if (gr.getWType() == "w")
                            {
                                Console.WriteLine("Input weight");
                                weight = int.Parse(Console.ReadLine());
                            }

                            try
                            {
                                if (gr.getWType() == "w" && gr.getType() == "o")
                                {
                                    wOrgraph<string, int> tmp = (wOrgraph<string, int>)gr;
                                    tmp.AddEdge(name1, name2, weight);
                                }
                                else if (gr.getWType() == "w" && gr.getType() == "n")
                                {
                                    wGraph<string, int> tmp = (wGraph<string, int>)gr;
                                    tmp.AddEdge(name1, name2, weight);
                                }
                                else                                
                                {
                                    gr.AddEdge(name1, name2);
                                }
                            }
                            catch (Exception ex) 
                            { 
                                Console.WriteLine(ex.Message);
                                Press();
                            }

                            break;
                        }
                    case 3:
                        {
                            Console.WriteLine("Input node name \t Z - undo");
                            string name = Console.ReadLine();
                            if (name == "z" || name == "Z") { break; }
                            try
                            {
                                gr.DeleteNode(name);
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e.Message);
                                Press();
                            }
                            break;
                        }
                    case 4:
                        {
                            Console.WriteLine("Input node names \t Z - undo");
                            string name1 = Console.ReadLine();
                            if (name1 == "z" || name1 == "Z") { break; }
                            string name2 = Console.ReadLine();
                            if (name2 == "z" || name2 == "Z") { break; }

                            try
                            {
                                gr.DeleteEdge(name1, name2);
                            }
                            catch (Exception ex)
                            {
                                Console.WriteLine(ex.Message);
                                Press();
                            }
                            break;
                        }
                    case 5:
                        {
                            Console.WriteLine("Input file path \t Z - undo");
                            string name = Console.ReadLine();
                            if (name == "z" || name == "Z") { break; }
                            try
                            {
                                gr.Save(name);
                            }
                            catch (Exception ex) 
                            {
                                Console.WriteLine(ex.Message);
                                Press();
                            }
                            break;
                        }
                    case 6:
                        {
                            try
                            {
                                if (gr.getWType() == "w")
                                {
                                    Console.WriteLine("Input node names \t Z - undo");
                                    string name1 = Console.ReadLine();
                                    if (name1 == "z" || name1 == "Z") { break; }
                                    string name2 = Console.ReadLine();
                                    if (name2 == "z" || name2 == "Z") { break; }
                                    Console.WriteLine("Input new weight");
                                    int weight = int.Parse(Console.ReadLine());

                                    if (gr.getType() == "o")
                                    {
                                        wOrgraph<string, int> tmp = (wOrgraph<string, int>)gr;

                                        try
                                        {
                                            tmp.OverwriteWeight(name1, name2, weight);
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                            Press();
                                        }
                                    }
                                    else
                                    {
                                        wGraph<string, int> tmp = (wGraph<string, int>)gr;

                                        try
                                        {
                                            tmp.OverwriteWeight(name1, name2, weight);
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                            Press();
                                        }
                                    }
                                }
                                else
                                {
                                    throw new Exception("Invalid mode");
                                }
                            }
                            catch (Exception ex)
                            {
                                Console.WriteLine(ex.Message);
                                Press();
                            }
                            break;
                        }
                    case 7:
                        {
                            try
                            {
                                if (gr.getType() == "o")
                                {
                                    Console.WriteLine("Input node name");
                                    string name = Console.ReadLine();
                                    if (name == "z" || name == "Z") { break; }

                                    if (gr.getWType() == "w")
                                    {
                                        wOrgraph<string, int> tmp = (wOrgraph<string, int>)gr;
                                        try
                                        {
                                            Console.WriteLine(tmp.InDegree(name));
                                            Press();
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                            Press();
                                        }

                                    }
                                    else if (gr.getWType() == "n") 
                                    {
                                        Orgraph<string, int> tmp = (Orgraph<string, int>)gr;
                                        try
                                        {
                                            Console.WriteLine(tmp.InDegree(name));
                                            Press();
                                        }
                                        catch (Exception ex)
                                        {
                                            Console.WriteLine(ex.Message);
                                            Press();
                                        }
                                    }
                                }
                                else
                                {
                                    throw new Exception("Invalid mode");
                                }
                            }
                            catch (Exception ex)
                            {
                                Console.WriteLine(ex.Message);
                                Press();
                            }
                            break;
                        }
                    case 0:
                        {
                            isOn = false;
                            break;
                        }
                    default:
                        {
                            throw new Exception("Invalid mode");
                        }
                }
            }
        }
    }
}
