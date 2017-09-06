using System;

namespace Test.PersonalAttribute
{
    public class PersonalAttributeClass : Attribute
    {
        public string ModuleName { get; set; } = String.Empty;

        public string Platform { get; set; } = String.Empty;

        public string MicroFamily { get; set; } = String.Empty;

        public string AutoSarVersion { get; set; } = String.Empty;

        public string Device { get; set; } = String.Empty;

        public string Version { get; set; } = String.Empty;

    }
}
