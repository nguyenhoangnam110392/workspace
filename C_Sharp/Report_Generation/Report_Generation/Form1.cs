using System;
using System.Windows.Forms;
using System.IO;
using Simple.FileManager;
using System.Xml;

namespace Report_Generation
{
    public partial class Form1 : Form
    {
        FileManagerClass fm = new FileManagerClass();

        public Form1()
        {
            InitializeComponent();
            LoadConfig();
            LoadFile("report.xml");
            LoadDataToTextBox();
        }

        private void LoadConfig()
        {
            cb_status.SelectedIndex = 1;
        }
        
        private void LoadFile(String path)
        {
            if (!File.Exists(path))
            {
                MessageBox.Show("Error was occured when loading file", "Notification", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                fm.load_file_content(path);
            }
        }

        private void LoadDataToTextBox()
        {
            txt_header.Text = fm.buffer[fm.header];
            txt_task.Text = fm.buffer[fm.task];
            txt_objective.Text = fm.buffer[fm.objective];
            txt_start.Text = fm.buffer[fm.start];
            txt_deadline.Text = fm.buffer[fm.deadline];
            cb_status.SelectedIndex = int.Parse(fm.buffer[fm.status]);
            txt_process.Text = fm.buffer[fm.process];
            //MessageBox.Show(fm.today_process, "Notification", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btGen_Click(object sender, EventArgs e)
        {
            String content = null;
            content += "Email to: Luc Ton <luc.ton@banvien.com.vn>;Khoa Ta <khoa.ta@banvien.com.vn>;\r\n";
            content += @"CC: Trung Hoang <trung.hoang@banvien.com.vn>;TIEN Nguyen Huu <tien.nguyen@banvien.com.vn>;
                         Linh Clayton <linh.clayton@banvien.com.vn>;Vien Nguyen <vien.nguyen@banvien.com>;
                         linda.tran@banvien.com <linda.tran@banvien.com>;THANG Nguyen Ba <thang.nguyen@banvien.com.vn>;
                         Tu Pham <tu.pham@banvien.com.vn>;Phu Truong Ngoc <phu.truong@banvien.com.vn>;" + "\r\n";
            content += "Title: [BV] [MCAL] Daily Report - Report " + DateTime.Now.ToString("dd/MM/yyyy") + " - Nguyen Hoang Nam\r\n\r\n";
            content += "[Daily report]\r\n";
            content += "=========================\r\n";
            content += txt_header.Text + "\r\n";
            content += "=========================\r\n\r\n";
            content += "[Activities]\r\n";
            content += "=========================\r\n";
            content += "1.[Today Task]                   :" + txt_task.Text + "\r\n";
            content += "            Objective            :" + txt_objective.Text + "\r\n";
            content += "            Start day            :" + txt_start.Text + "\r\n";
            content += "            Deadline             :" + txt_deadline.Text + "\r\n";
            content += "            Status               :" + cb_status.SelectedIndex + "\r\n";
            content += "            Process              :" + txt_process.Text + "\r\n";
            content += "            Detail               :" + "\r\n";
            content += "            >>>>>>>>>> Issue/Risk:" + "\r\n";
            content += "            >>>>>>>>> Measurement:" + "\r\n";

            content += "================================\r\n";
            content += "[Comment/Request/Proposal/Other]\r\n";
            content += "================================";

            String path = txt_output_path.Text;
            System.IO.File.WriteAllText(path, content);

            XmlDocument doc = new XmlDocument();
            string xmlData = "<CONTENT></CONTENT>";
            doc.Load(new StringReader(xmlData));

            // Create a new element and add it to the document.
            XmlElement element = doc.CreateElement("HEADER");
            element.InnerText = txt_header.Text;
            doc.DocumentElement.AppendChild(element);

            element = doc.CreateElement("TASK");
            element.InnerText = txt_task.Text;
            doc.DocumentElement.AppendChild(element);

            element = doc.CreateElement("OBJECTIVE");
            element.InnerText = txt_objective.Text;
            doc.DocumentElement.AppendChild(element);

            element = doc.CreateElement("START");
            element.InnerText = txt_start.Text;
            doc.DocumentElement.AppendChild(element);

            element = doc.CreateElement("DEADLINE");
            element.InnerText = txt_deadline.Text;
            doc.DocumentElement.AppendChild(element);

            element = doc.CreateElement("STATUS");
            element.InnerText = cb_status.SelectedIndex.ToString();
            doc.DocumentElement.AppendChild(element);

            element = doc.CreateElement("PROCESS");
            element.InnerText = txt_process.Text;
            doc.DocumentElement.AppendChild(element);

            doc.Save("report.xml");

            if (MessageBox.Show("Generation file finished! Located at " + path +"\r\nDo you want to open file and exit program?", "Process", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
            {
                System.Diagnostics.Process.Start("notepad.exe", path);
                Application.Exit();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            String content = null;
            content += "[Daily report]\r\n";
            content += "=========================\r\n";
            content += "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
            content += "=========================\r\n\r\n";
            content += "[Activities]\r\n";
            content += "=========================\r\n";
            content += "1 [Training course]              " + "\r\n\r\n";
            content += "            Output               " + "\r\n\r\n";
            content += "            Start day            " + "\r\n\r\n";
            content += "            Deadline             " + "\r\n\r\n";
            content += "            Status               " + "\r\n\r\n";
            content += "            Process              " + "\r\n\r\n";
            content += "            Detail               " + "\r\n\r\n";
            content += "            Save at              " + "\r\n\r\n";

            LB_Main.Text = content;
        }
    }
}
