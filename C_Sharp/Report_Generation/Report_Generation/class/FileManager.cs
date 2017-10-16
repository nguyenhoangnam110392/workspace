using System;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Linq;
using System.Windows.Forms;
using System.Collections.Generic;

namespace Simple.FileManager
{
    public class FileManagerClass
    {
        /* Variables define */
        public List<String> buffer = new List<string>();

        public int header = 0;
        public int task = 1;
        public int objective = 2;
        public int start = 3;
        public int deadline = 4;
        public int status = 5;
        public int process = 6;

        public void load_file_content(String path)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(path);
            XmlNodeList xmlList = doc.SelectNodes("/CONTENT");
            XmlNode nodeList = xmlList[header];

            foreach (XmlNode node in nodeList)
            {
                buffer.Add(node.InnerText);
            }
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
