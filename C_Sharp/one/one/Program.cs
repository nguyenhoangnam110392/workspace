using System;

using Simple.CustomAttribute;
using Simple.InputData;
using System.Reflection;

namespace one
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Reflection trong C#");
            Console.WriteLine("------------------------------------");

            InputDataClass id = new InputDataClass();
            id.Info();

            Type type = typeof(InputDataClass);
            PropertyInfo[] properties = type.GetProperties();
            foreach (Object attributes in properties)
            {
                CustomAttributeClass dbi = (CustomAttributeClass)attributes;
                if (null != dbi)
                {
                    Console.WriteLine("Name: {0}", dbi.Name);
                    Console.WriteLine("Number: {0}", dbi.Number);         
                }
            }

            Console.ReadKey();
        }
    }
}