using System;
using Test.DebugInfo;

namespace Test.Rectangle
{
    class RectangleClass
    {
        [DeBugInfoClass(55, "Tran Nam", "2/8/2016", Message = "Kieu tra ve khong hop le")]
        public double tinhDienTich()
        {
            return 0;
        }
        [DeBugInfoClass(56, "Minh Chinh", "19/10/2016", Message = "This is the last one")]
        public void Display()
        {

        }
    }
}
