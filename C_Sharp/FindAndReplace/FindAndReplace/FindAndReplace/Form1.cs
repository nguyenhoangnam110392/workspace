using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using Aspose.Words;
using System.Threading.Tasks;

namespace FindAndReplace
{
    public partial class Form1 : Form
    {
        List<string> group_file_name = new List<string>();

        public Form1()
        {
            InitializeComponent();
        }
        
        /***********************************************************************
         * Name : Form1_Load
         * Description : Load setting when start-up
         **********************************************************************/
        private void Form1_Load(object sender, EventArgs e)
        {
            new Aspose.Words.License().SetLicense(LicenseHelper.License.LStream);
        }
        
        /***********************************************************************
         * Name : bt_add_file_Click
         * Description : Add file to list box
         **********************************************************************/
        private void bt_add_file_Click(object sender, EventArgs e)
        {
            /* Private */
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = true;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                foreach (string file in dialog.FileNames)
                {
                    list_file.Items.Add(file);
                }
            }
        }

        /***********************************************************************
         * Name : bt_list_item_remove_Click
         * Description : Remove file from list box
         **********************************************************************/
        private void bt_list_item_remove_Click(object sender, EventArgs e)
        {
            CheckedListBox.CheckedItemCollection checked_list = list_file.CheckedItems;
            int checked_list_count = checked_list.Count;
            for (int i=0; i < checked_list_count; i++)
            {
                list_file.Items.Remove(list_file.CheckedItems[0]);
            }
        }

        /***********************************************************************
         * Name : bt_Run_Click
         * Description : Start replace
         **********************************************************************/
        private async void bt_Run_Click(object sender, EventArgs e)
        {
            string text_find = txt_find.Text.ToString();
            string text_replace = txt_replace.Text.ToString();

            for (int i = 0; i < list_file.Items.Count; i++)
            {
                string file_path = list_file.Items[i].ToString();

                /* Read input files and replace */
                Document doc_input = new Document(file_path);
                string input = doc_input.ToTxt();
                string output = input.Replace(text_find, text_replace);

                /* Put text into stream */
                MemoryStream stream = new MemoryStream();
                StreamWriter writer = new StreamWriter(stream);
                writer.Write(output);
                writer.Flush();
                stream.Position = 0;

                /* Save as */
                Document doc_output = new Document(stream);
                string file_name = Path.GetFileName(file_path);
                string save_path = null;

                if (rd_save_as.Checked)          { save_path = txt_save.Text.ToString() + @"\" + file_name; }
                else if(rd_over_write.Checked)   { save_path = file_path;                                   }
                else                             { save_path = file_path.Replace(".doc", "_replaced.doc");  }
                doc_output.Save(save_path);
                list_file.SetItemChecked(i, true);

                await Task.Delay(2);
                label_status.Text = "Replaced " + i + " files";
            }
            label_status.Text = "Done.";
        }

        /***********************************************************************
         * Name : rd_save_as_CheckedChanged
         * Description : radio button check
         **********************************************************************/
        private void rd_save_as_CheckedChanged(object sender, EventArgs e)
        {
            txt_save.Enabled = true;
        }

        /***********************************************************************
         * Name : rd_over_write_CheckedChanged
         * Description : radio button check
         **********************************************************************/
        private void rd_over_write_CheckedChanged(object sender, EventArgs e)
        {
            txt_save.Enabled = false;
        }

        /***********************************************************************
         * Name : rd_default_CheckedChanged
         * Description : radio button check
         **********************************************************************/
        private void rd_default_CheckedChanged(object sender, EventArgs e)
        {
            txt_save.Enabled = false;
        }

        /***********************************************************************
         * Name : txt_find_TextChanged
         * Description : Enable/Disable button Run if text box != null
         **********************************************************************/
        private void txt_find_TextChanged(object sender, EventArgs e)
        {
            if(txt_find.Text.Length > 0)
            {
                bt_Run.Enabled = true;
            }
            else
            {
                bt_Run.Enabled = false;
            }
        }
    }
}
