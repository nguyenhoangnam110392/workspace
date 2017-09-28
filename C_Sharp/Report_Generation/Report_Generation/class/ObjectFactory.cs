using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Simple.ObjectFactory
{
    class ObjectFactoryClass
    {
        private static Dictionary<Type, List<TypeChosenData>> chosenList = new Dictionary<Type, List<TypeChosenData>>();
        private static Dictionary<Type, List<Type>> RegisteredTypes = new Dictionary<Type, List<Type>>();

        public static void Load()
        {
            // For other Interface
            foreach (var entry in RegisteredTypes.Where(x => x.Key != typeof(IBasicConfiguration)))
            {
                chosenList[entry.Key] = new List<TypeChosenData>();
                foreach (var t in entry.Value)
                {
                    if (CheckConditionType(t, entry.Value, entry.Key))
                    {
                        chosenList[entry.Key].Add(new TypeChosenData(t));
                    }
                }
                // sort by version
                chosenList[entry.Key].Sort(delegate (TypeChosenData t1, TypeChosenData t2)
                {
                    var att1 = (ObjectFactoryAttribute)t1.TypeOf.GetCustomAttribute(typeof(ObjectFactoryAttribute));
                    var att2 = (ObjectFactoryAttribute)t2.TypeOf.GetCustomAttribute(typeof(ObjectFactoryAttribute));
                    return String.Compare(att2.Version, att1.Version);
                });
            }
        }



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
    }
}
