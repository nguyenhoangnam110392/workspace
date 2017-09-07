using System;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Linq;
using System.Windows.Forms;

using Simple.Buffer;
using Simple.ObjectFactory;

namespace Simple.FileManager
{
    public class FileManagerClass
    {
        private BufferClass BF = null;

        private FileManagerClass(BufferClass bf)
        {
            this.BF = bf;
        }

        private FileManagerClass() : this(ObjectFactoryClass.GetInstance<BufferClass>())
        { }




        public Boolean load_file(String path)
        {
            BF.Name = "nam";
            if (File.Exists(path))
            {
                try
                {
                    XDocument doc = XDocument.Load(path);

                    //fm.content_header = get_xml_content(doc, "HEADER");

                    //fm.today_course = get_xml_content(doc, "TODAY-COURSE");
                    //fm.today_output = get_xml_content(doc, "TODAY-OUTPUT");
                    //fm.today_start = get_xml_content(doc, "TODAY-START");
                    //fm.today_deadline = get_xml_content(doc, "TODAY-DEADLINE");
                    //fm.today_status = get_xml_content(doc, "TODAY-STATUS");
                    //fm.today_process = get_xml_content(doc, "TODAY-PROCESS");

                    //fm.tm_course = get_xml_content(doc, "TM-COURSE");
                    //fm.tm_output = get_xml_content(doc, "TM-OUTPUT");
                    //fm.tm_start = get_xml_content(doc, "TM-START");
                    //fm.tm_deadline = get_xml_content(doc, "TM-DEADLINE");
                    //fm.tm_status = get_xml_content(doc, "TM-STATUS");
                    //fm.tm_process = get_xml_content(doc, "TM-PROCESS");
                }
                catch(XmlException x)
                {
                    MessageBox.Show("Error code {0}" + x, "Notification", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }

                
                
            }
            return true;
        }

        private String get_xml_content(XDocument doc, string match_word)
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
