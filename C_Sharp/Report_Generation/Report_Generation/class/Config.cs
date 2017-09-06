using System;

/// <summary>
/// Summary description for Class1
/// </summary>
namespace Simple.Config
{
    public class ConfigClass : InterfaceConfig
    {
        public string FilePath { get; set; } = String.Empty;

        public string content_header { get; set; } = String.Empty;

        public string today_course { get; set; } = String.Empty;
        public string today_output { get; set; } = String.Empty;
        public string today_start { get; set; } = String.Empty;
        public string today_deadline { get; set; } = String.Empty;
        public string today_status { get; set; } = String.Empty;
        public string today_process { get; set; } = String.Empty;

        public string tm_course { get; set; } = String.Empty;
        public string tm_output { get; set; } = String.Empty;
        public string tm_start { get; set; } = String.Empty;
        public string tm_deadline { get; set; } = String.Empty;
        public string tm_status { get; set; } = String.Empty;
        public string tm_process { get; set; } = String.Empty;
    }
}