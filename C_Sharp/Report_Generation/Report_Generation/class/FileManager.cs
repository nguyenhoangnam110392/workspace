using System;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Linq;
using System.Windows.Forms;

using Simple.Config;

/// <summary>
/// Summary description for Class1
/// </summary>
namespace Simple.FileManager
{ 
    class FileManagerClass
    {
        public static Boolean load_file(String path)
        {
            ConfigClass cf = new ConfigClass();
            if (File.Exists(path))
            {
                try
                {
                    XDocument doc = XDocument.Load(path);

                    cf.content_header = get_xml_content(doc, "HEADER");

                    cf.today_course = get_xml_content(doc, "TODAY-COURSE");
                    cf.today_output = get_xml_content(doc, "TODAY-OUTPUT");
                    cf.today_start = get_xml_content(doc, "TODAY-START");
                    cf.today_deadline = get_xml_content(doc, "TODAY-DEADLINE");
                    cf.today_status = get_xml_content(doc, "TODAY-STATUS");
                    cf.today_process = get_xml_content(doc, "TODAY-PROCESS");

                    cf.tm_course = get_xml_content(doc, "TM-COURSE");
                    cf.tm_output = get_xml_content(doc, "TM-OUTPUT");
                    cf.tm_start = get_xml_content(doc, "TM-START");
                    cf.tm_deadline = get_xml_content(doc, "TM-DEADLINE");
                    cf.tm_status = get_xml_content(doc, "TM-STATUS");
                    cf.tm_process = get_xml_content(doc, "TM-PROCESS");
                }
                catch(XmlException x)
                {
                    MessageBox.Show("Error code {0}" + x, "Notification", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }
            return true;
        }

        public static String get_xml_content(XDocument doc, string match_word)
        {
            string value = string.Empty;
            match_word = match_word.ToUpper();
            XElement element =
                doc.Descendants().Where(x => x.Name.LocalName.Equals(match_word, StringComparison.OrdinalIgnoreCase)).FirstOrDefault();
            if (element != null)
            {
                value = element.Value.ToString();
            }
            return value;
        }
    }
}
