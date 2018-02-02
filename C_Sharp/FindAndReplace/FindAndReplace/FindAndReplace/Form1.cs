using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Office.Interop.Word;

namespace FindAndReplace
{
    public partial class Form1 : Form
    {
        List<string> group_file_name = new List<string>();

        public Form1()
        {
            InitializeComponent();
        }

        private void item_one_Click(object sender, EventArgs e)
        {
            /* Private */
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = true;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                foreach (string file in dialog.FileNames)
                {
                    group_file_name.Add(file);
                }
            }
            Word.Application ap = new Word.Application();
            Document document = ap.Documents.Open(@"E:\ws\workspace\Personal Document\StudyPlan.docx");
        }
    }
}
