using System;


namespace Simple.CustomAttribute
{
    [AttributeUsage(AttributeTargets.All | AttributeTargets.All, AllowMultiple = true)]

    class CustomAttributeClass : Attribute
    {
        public CustomAttributeClass(string header, string today_course)
        {
            this.Header = header;
            this.Today_course = today_course;
        }

        public string Header { get; set; } = String.Empty;

        public string Today_course { get; set; } = String.Empty;
    }


}
