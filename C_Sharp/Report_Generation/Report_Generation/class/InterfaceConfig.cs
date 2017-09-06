/// <summary>
/// Summary description for Class1
/// </summary>

namespace Simple.Config
{
    public interface InterfaceConfig
    {
        string FilePath { get; set; }

        string content_header { get; set; }

        string today_course { get; set; }

        string today_output { get; set; }

        string today_start { get; set; }

        string today_deadline { get; set; }

        string today_status { get; set; }

        string today_process { get; set; }

        string tm_course { get; set; }

        string tm_output { get; set; }

        string tm_start { get; set; }

        string tm_deadline { get; set; }

        string tm_status { get; set; }

        string tm_process { get; set; }
    }
}
