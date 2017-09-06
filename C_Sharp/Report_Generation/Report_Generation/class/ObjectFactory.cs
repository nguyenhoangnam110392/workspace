using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

/// <summary>
/// Summary description for Class1
/// </summary>
namespace Simple.ObjectFactory
{
    class ObjectFactoryClass
    {
        private class TypeChosenData
        {
            public Object Intance { get; set; } = null;

            public Type TypeOf { get; set; } = null;

            public TypeChosenData(Type typeOf, object intance = null)
            {
                Intance = intance;
                TypeOf = typeOf;
            }
        }

        private static Dictionary<Type, List<TypeChosenData>> chosenList = new Dictionary<Type, List<TypeChosenData>>();

        public static T GetInstance<T>() where T : class
        {
            Type t = typeof(T);
            if (chosenList.Keys.Contains(t) && chosenList[t].Count > 0)
            {
                if (chosenList[t].First().Intance == null)
                {
                    chosenList[t].First().Intance = CreateInstance(chosenList[t].First().TypeOf);
                }
                return (T)chosenList[t].First().Intance;
            }
            else
            {
                Console.WriteLine("Get {0} failed, exit", t);
                Environment.Exit(1);
                return null;
            }
        }

        private static Object CreateInstance(Type t)
        {
            Object ret = null;
            var getInstance = t.GetField("Instance", BindingFlags.Public | BindingFlags.Static);
            if (getInstance != null)
            {
                ret = getInstance.GetValue(null);
            }
            else
            {
                Console.WriteLine("{0} does not have Instance member", t);
                Environment.Exit(1);
            }
            return ret;
        }
    }
}
