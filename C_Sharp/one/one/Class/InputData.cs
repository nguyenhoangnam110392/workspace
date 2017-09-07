using Simple.CustomAttribute;
using System;

namespace Simple.InputData
{
    [CustomAttributeClass(100, "Hoang Nam")]
    [CustomAttributeClass(200, "Nhat Huy")]

    class InputDataClass
    {
        public void Info()
        {
            Console.WriteLine("-----------This is Input data class-------------");
        }
    }
}
