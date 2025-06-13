using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public class BinaryTree
    {
        private class Node
        {
            public int inf; 
            public Node left; 
            public Node right; 
                               
            public Node(int nodeInf)
            {
                inf = nodeInf;
                left = null;
                right = null;
            }
            
            public static void Add(ref Node r, int nodeInf)
            {
                if (r == null)
                {
                    r = new Node(nodeInf);
                }
                else
                {
                    
                if (((IComparable)(r.inf)).CompareTo(nodeInf) > 0)
                    {
                        Add(ref r.left, nodeInf);
                    }
                    else
                    {
                        Add(ref r.right, nodeInf);
                    }
                }
            }
            public static void Preorder(Node r) 
            {
                if (r != null)
                {
                    Console.Write("{0} ", r.inf);
                    Preorder(r.left);
                    Preorder(r.right);
                }
            }
            public static void Inorder(Node r) 
            {
                if (r != null)
                {
                    Inorder(r.left);
                    Console.Write("{0} ", r.inf);
                    Inorder(r.right);
                }
            }
            public static void Postorder(Node r)
            {
                if (r != null)
                {
                    Postorder(r.left);
                    Postorder(r.right);
                    Console.Write("{0} ", r.inf);
                }
            }
            
            public static void Search(Node r, object key, out Node item)
            {
                if (r == null)
                {
                    item = null;
                }
                else
                {
                    if (((IComparable)(r.inf)).CompareTo(key) == 0)
                    {
                        item = r;
                    }
                    else
                       
                     {
                        if (((IComparable)(r.inf)).CompareTo(key) > 0)
                        {
                            Search(r.left, key, out item);
                        }
                        else
                        {
                            Search(r.right, key, out item);
                        }
                    }
                }
            }
            
            private static void Del(Node t, ref Node tr)
            {
                if (tr.right != null)
                {
                    Del(t, ref tr.right);
                }
                else
                {
                    t.inf = tr.inf;
                    tr = tr.left;
                }
            }
            public static void Delete(ref Node t, object key)
            {
                if (t == null)
                {
                    throw new Exception("Данное значение в дереве отсутствует");
                }
                else
                {
                    if (((IComparable)(t.inf)).CompareTo(key) > 0)
                    {
                        Delete(ref t.left, key);
                    }
                    else
                    {
                        if (((IComparable)(t.inf)).CompareTo(key) < 0)
                        {
                            Delete(ref t.right, key);
                        }
                        else
                        {
                            if (t.left == null)
                            {
                                t = t.right;
                            }
                            else
                            {
                                
                            if (t.right == null)
                                {
                                    t = t.left;
                                }
                                else
                                {
                                    Del(t, ref t.left);
                                }
                            }
                        }
                    }
                }
            }

            public static bool isExist(Node start, int key)
            {
                Node r;
                Search(start, key, out r);
                return (r != null);
            }
    

            public static void isNodeBalanced(Node r, ref bool flagBalance)
            {
                if (r != null)
                {
                    int height1 = height(r.left);
                    int height2 = height(r.right);
                    //Height(r.left, ref height1);
                    //Height(r.right, ref height2);
                    if (Math.Abs(height2 - height1) <= 1 && flagBalance)
                    {
                        isNodeBalanced(r.left, ref flagBalance);
                        isNodeBalanced(r.right, ref flagBalance);
                    }
                    else
                    {
                        flagBalance = false;
                        //Console.WriteLine(r.inf);
                        //Console.WriteLine("{0}, {1}", height1, height2);
                        return;
                    }
                }
            }

            public static void AddToBalance(Node r, ref int count, Node start)
            {
                if (r != null)
                {
                    int height1 = height(r.left);
                    int height2 = height(r.right);
                    if (Math.Abs(height2 - height1) > 1)
                    {
                        Node temp = r;
                        count++;
                        if (height2 < height1)
                        {
                            while (temp.right != null)
                            {
                                temp = temp.right;
                            }

                            if (isExist(start, temp.inf + 1))
                            {
                                throw new Exception("Can't be balanced");
                            }

                            Add(ref temp, temp.inf + 1);
                            AddToBalance(r, ref count, start);
                        }
                        else
                        {
                            while (temp.left != null)
                            {
                                temp = temp.left;
                            }

                            if (isExist(start, temp.inf - 1))
                            {
                                throw new Exception("Can't be balanced");
                            }

                            Add(ref temp, temp.inf - 1);
                            AddToBalance(r, ref count, start);
                        }
                    }
                    AddToBalance(r.left, ref count, start);
                    AddToBalance(r.right, ref count, start);
                }
            }

            public static int height(Node r)
            {
                if (r == null)
                {
                    return 0;
                }
                return 1 + Math.Max(height(r.left), height(r.right));
            }

        } 
        Node tree; 
                   
        public int Inf
        {
            set { tree.inf = value; }
            get { return tree.inf; }
        }
        public BinaryTree()
        {
            tree = null;
        }
        private BinaryTree(Node r)
        {
            tree = r;
        }
        public void Add(int nodeInf) 
        {
            Node.Add(ref tree, nodeInf);
        }
        
        public void Preorder()
        {
            Node.Preorder(tree);
            Console.WriteLine();
        }
        public void Inorder()
        {
            Node.Inorder(tree);
            Console.WriteLine();
        }
        public void Postorder()
        {
            Node.Postorder(tree);
            Console.WriteLine();
        }
        
        public BinaryTree Search(object key)
        {
            Node r;
            Node.Search(tree, key, out r);
            BinaryTree t = new BinaryTree(r);
            return t;
        }
        //удаление ключевого узла в дереве
        public void Delete(object key)
        {
            Node.Delete(ref tree, key);
        }

        public int Height()
        {
            return Node.height(tree);
        }

        public bool isTreeBalanced()
        {
            bool flagBalance = true;
            Node.isNodeBalanced(tree, ref flagBalance);
            return flagBalance;
        }

        public int AddToBalance()
        {
            int count = 0;
            Node.AddToBalance(tree, ref count, tree);
            return count;
        }
        
        public bool isExist(int key)
        {
            return Node.isExist(tree, key);
        }

    }
}
