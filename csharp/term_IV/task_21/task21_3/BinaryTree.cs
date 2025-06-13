using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{

    public class BinaryTree
    {
        public class Node
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

            public static void AddLeft(ref Node r, int max, int min)
            {
                if (r == null)
                {
                    
                    r = new Node(mid(max, min+2));
                }
                else
                {

                    if (r.inf > max)
                    {
                        AddLeft(ref r.left, max, min);
                    }
                    else
                    {
                        
                        AddLeft(ref r.right, max, r.inf);
                    }
                }
            }

            public static void AddRight(ref Node r, int min, int max)
            {
                if (r == null)
                {
                    
                    r = new Node(mid(max, min));
                }
                else
                {

                    if (r.inf > min)
                    {
                        
                        AddRight(ref r.left, min, r.inf);
                    }
                    else
                    {
                        AddRight(ref r.right, min, max);
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

            public static int mid(int max, int min)
            {
                return (max + min) / 2;
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

            public static void DisbalancedToList(Node r, ref Queue<Node> queue)
            {
                if (r != null)
                {
                    int height1 = height(r.left);
                    int height2 = height(r.right);
                    //Height(r.left, ref height1);
                    //Height(r.right, ref height2);
                    if (Math.Abs(height2 - height1) > 1)
                    {
                        queue.Enqueue(r);
                    }
                    DisbalancedToList(r.left, ref queue);
                    DisbalancedToList(r.right, ref queue);
                }
            }

            public static void AddToBalancePrimary(Node r, Node start)
            {
                int maxValue = 2* max(start);
                int minValue = min(start);
                minValue *= minValue < 0 ? 2: -2;
                if (r != null)
                {
                    int heightl = height(r.left);
                    int heightr = height(r.right);
                    if (Math.Abs(heightr - heightl) > 1)
                    {
                        Node temp = r;
                        if (heightr < heightl)
                        {
                            while (temp.right != null)
                            {
                                temp = temp.right;
                            }
                            AddRight(ref start, temp.inf + 1, 2*maxValue);
                        }
                        else
                        {
                            while (temp.left != null)
                            {
                                temp = temp.left;
                            }
                            AddLeft(ref start, temp.inf - 1, 2*minValue);
                        }
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

                            Add(ref temp, temp.inf + height1);
                            AddToBalance(r, ref count, start);
                        }
                        else
                        {
                            while (temp.left != null)
                            {
                                temp = temp.left;
                            }

                            Add(ref temp, temp.inf - height2);
                            AddToBalance(r, ref count, start);
                        }
                    }
                    AddToBalance(r.left, ref count, start);
                    AddToBalance(r.right, ref count, start);
                }
            }

            public static int max(Node r) 
            {
                while (r.right != null)
                {
                   r = r.right;
                }
                return r.inf;
            }

            public static int min(Node r)
            {
                while (r.left != null)
                {
                    r = r.left;
                }
                return r.inf;
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
        public Node tree; 
                   
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

        public void DisbalancedToList(ref Queue<Node> queue) 
        {
            Node.DisbalancedToList(tree, ref queue);
        }


        public void BalancedWithAdds(int n) 
        {
            int k = n;
            Queue<BinaryTree.Node> queue = new Queue<BinaryTree.Node>();
            DisbalancedToList(ref queue);
            if (n < queue.Count)
            {
                Console.WriteLine("Can't be balanced with {0} additions", n);
                return;
            }
            while (!isTreeBalanced())
            {
                while (queue.Count != 0)
                {
                    BinaryTree.Node.AddToBalancePrimary(queue.Dequeue(), tree);
                    k--;
                    if (k < 0) 
                    {
                        Console.WriteLine("Can't be balanced with {0} additions", n);
                        return;
                    }
                }
                DisbalancedToList(ref queue);
            }
            Preorder();
            Console.WriteLine("Is tree balanced? {0}", isTreeBalanced());
        }

        public int max()
        {
            return Node.max(tree);
        }

        public int min()
        {
            return Node.min(tree);
        }
    }
}
