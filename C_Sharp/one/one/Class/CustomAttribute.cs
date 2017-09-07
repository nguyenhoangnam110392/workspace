using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Simple.CustomAttribute
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Constructor, AllowMultiple = true)]

    class CustomAttributeClass : Attribute
    {
        public CustomAttributeClass(int number, string name)
        {
            this.Number = number;
            this.Name = name;
        }

        public int Number { get; set; } = 0;

        public string Name { get; set; } = String.Empty;
    }
}
