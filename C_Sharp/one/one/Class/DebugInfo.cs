using System;
using System.Reflection;
using Test.PersonalAttribute;

namespace Test.DebugInfo
{ 
    //Mot custom attribute BugFix 
    [PersonalAttributeClass(AutoSarVersion = "1.0.1", Device = "X2X", MicroFamily = "*", ModuleName = "*", Platform = "*", Version = "*")]

    public class DeBugInfoClass : PersonalAttributeClass
    {
        private int bugNo;
        private string developer;
        private string lastReview;
        public string message;

        public DeBugInfoClass(int bg, string dev, string d)
        {
            this.BugNo = bg;
            this.developer = dev;
            this.lastReview = d;
        }

        public int BugNo { get; set; }

        public string Developer
        {
            get
            {
                return developer;
            }
        }

        public string LastReview
        {
            get
            {
                return lastReview;
            }
        }

        public string Message
        {
            get
            {
                return message;
            }
            set
            {
                message = value;
            }
        }
    }

}