using System;
using System.Reflection;
using Test.Rectangle;
using Test.DebugInfo;

namespace one
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Reflection trong C#");
            Console.WriteLine("------------------------------------");

            Type type = typeof(RectangleClass);

            //lap qua cac attribtue cua lop Rectangle
            foreach (Object attributes in type.GetCustomAttributes(false))
            {
                DeBugInfoClass dbi = (DeBugInfoClass)attributes;
                if (null != dbi)
                {
                    Console.WriteLine("Bug no: {0}", dbi.BugNo);
                    Console.WriteLine("Developer: {0}", dbi.Developer);
                    Console.WriteLine("Last Reviewed: {0}", dbi.LastReview);
                    Console.WriteLine("Remarks: {0}", dbi.Message);
                    
                }
            }
            
            //lap qua cac method attribtue
            foreach (MethodInfo m in type.GetMethods())
            {
                foreach (Attribute a in m.GetCustomAttributes(true))
                {

                    try
                    {
                        DeBugInfoClass dbi = (DeBugInfoClass)a;
                        if (null != dbi)
                        {
                            Console.WriteLine("Bug no: {0}, for Method: {1}", dbi.BugNo, m.Name);
                            Console.WriteLine("Developer: {0}", dbi.Developer);
                            Console.WriteLine("Last Reviewed: {0}", dbi.LastReview);
                            Console.WriteLine("Remarks: {0}", dbi.Message);
                        }
                    }
                    catch(Exception e)
                    {

                    }     
                }
            }

            Console.ReadLine();
            Console.ReadKey();
        }
    }
}