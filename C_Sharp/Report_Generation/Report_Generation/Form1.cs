using System;
using System.Windows.Forms;

using Simple.FileManager;
using Simple.ObjectFactory;
using Simple.Buffer;

namespace Report_Generation
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            LoadFile();
        }
        
        private void LoadFile()
        {
            FileManagerClass fm = ObjectFactoryClass.GetInstance<FileManagerClass>();

            if (fm.load_file(@"D:\report.xml") == false)
            {
                MessageBox.Show("Error occured when loading file.", "Notification", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }

            MessageBox.Show("", "Notification", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        //private void LoadDataToTextBox()
        //{
        //    txt_train_today.Text = cf.today_course;
        //    txt_output_today.Text = cf.today_output;
        //    txt_start_today.Text = cf.today_start;
        //    txt_end_today.Text = cf.today_deadline;
        //    txt_status_today.Text = cf.today_status;
        //    txt_process_today.Text = cf.today_process;

        //    txt_train_next.Text = cf.tm_course;
        //    txt_output_next.Text = cf.tm_output;
        //    txt_start_next.Text = cf.tm_start;
        //    txt_end_next.Text = cf.tm_deadline;
        //    txt_status_next.Text = cf.tm_status;
        //    txt_process_next.Text = cf.tm_process;

        //    MessageBox.Show(cf.today_process, "Notification", MessageBoxButtons.OK, MessageBoxIcon.Information);
        //}

        private void btGen_Click(object sender, EventArgs e)
        {
            String content = "[Daily report]\r\n";
            content += "=========================\r\n";
            content += txt_header.Text + "\r\n";
            content += "=========================\r\n\r\n";
            content += "[Activities]\r\n";
            content += "=========================\r\n";
            content += "1 [Training course]              :" + txt_train_today.Text + "\r\n";
            content += "            Output               :" + txt_output_today.Text + "\r\n";
            content += "            Start day            :" + txt_start_today.Text + "\r\n";
            content += "            Deadline             :" + txt_end_today.Text + "\r\n";
            content += "            Status               :" + txt_status_today.Text + "\r\n";
            content += "            Process              :" + txt_process_today.Text + "\r\n";
            content += "            Detail               :" + "\r\n";
            content += "            >>>>>>>>>> Issue/Risk:" + "\r\n";
            content += "            >>>>>>>>> Measurement:" + "\r\n";

            content += "========================\r\n";
            content += "[Planned activities]\r\n";
            content += "========================\r\n";

            content += "1 [Training course]              :" + txt_train_next.Text + "\r\n";
            content += "            Output               :" + txt_output_next.Text + "\r\n";
            content += "            Start day            :" + txt_start_next.Text + "\r\n";
            content += "            Deadline             :" + txt_end_next.Text + "\r\n";
            content += "            Status               :" + txt_status_next.Text + "\r\n";
            content += "            Process              :" + txt_process_next.Text + "\r\n";
            content += "            Detail               :" + "\r\n";
            content += "            >>>>>>>>>> Issue/Risk:" + "\r\n";
            content += "            >>>>>>>>> Measurement:" + "\r\n";

            content += "================================\r\n";
            content += "[Comment/Request/Proposal/Other]\r\n";
            content += "================================";

            String path = txt_output_path.Text;
            System.IO.File.WriteAllText(path, content);

            if(MessageBox.Show("Generation file finished! Located at " + path +"\r\nDo you want to open file and exit program?", "Process", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
            {
                System.Diagnostics.Process.Start("notepad.exe", path);
                Application.Exit();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            String content = "[Daily report]\r\n";
            content += "=========================\r\n";
            content += "\r\n\r\n";
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
            content += "            >>>>>>>>>> Issue/Risk" + "\r\n\r\n";
            content += "            >>>>>>>>> Measurement" + "\r\n\r\n";

            content += "========================\r\n";
            content += "[Planned activities]\r\n";
            content += "========================\r\n";

            content += "1 [Training course]              " + "\r\n\r\n";
            content += "            Output               " + "\r\n\r\n";
            content += "            Start day            " + "\r\n\r\n";
            content += "            Deadline             " + "\r\n\r\n";
            content += "            Status               " + "\r\n\r\n";
            content += "            Process              " + "\r\n\r\n";
            content += "            Detail               " + "\r\n\r\n";
            content += "            >>>>>>>>>> Issue/Risk" + "\r\n\r\n";
            content += "            >>>>>>>>> Measurement" + "\r\n\r\n";

            content += "================================\r\n";
            content += "[Comment/Request/Proposal/Other]\r\n";
            content += "================================";

            LB_Main.Text = content;
        }
    }
}
