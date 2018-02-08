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

        /***********************************************************************
         * Name : bt_search_Click
         * Description : Search for files which are match the keyword
         **********************************************************************/
        private void bt_search_Click(object sender, EventArgs e)
        {
            file_walker(txt_path.Text.ToString());
            label_status.Text = "Done.";
        }

        /***********************************************************************
         * Name : file_walker
         * Description : Search file in sub folder
         **********************************************************************/
        private async void file_walker(string folder)
        {
            await Task.Run(() =>
            {
                foreach (string file_path in Directory.GetFiles(folder))
                {
                    file_processing(file_path);
                } /* End of walk through file */

                foreach (string sub_folder in Directory.GetDirectories(folder))
                {
                    file_walker(sub_folder);
                } /* End of walk through folder */
            }); /* End of task */
        }

        /***********************************************************************
         * Name : txt_keyword_TextChanged
         * Description : Enable/Disable bt_search if text box != null
         **********************************************************************/
        private async void file_processing(string file_path)
        {
            string str_keyword = txt_keyword.Text.ToString();
            string file_name = Path.GetFileName(file_path);
            if (file_name.IndexOf(".doc") > 0)
            {
                /* Read input files and replace */
                try
                {
                    Document doc_input = new Document(file_path);
                    string input = doc_input.ToTxt();
                    int index_of_match_keyword = 0;

                    index_of_match_keyword = input.IndexOf(str_keyword);
                    if (index_of_match_keyword > 0)
                    {
                        list_match_file.Items.Add(file_name);
                        group_file_name.Add(file_path);
                        label_status.Text = "Replaced " + group_file_name.Count + " files";
                        await Task.Delay(2);
                    }   
                }
                catch (Exception exception){}        
            } /* End of filter file by extension */
        }

        /***********************************************************************
         * Name : txt_path_TextChanged
         * Description : Enable/Disable bt_search if text box != null
         **********************************************************************/
        private void txt_path_TextChanged(object sender, EventArgs e)
        {
            if((txt_path.Text.Length > 0) && (txt_keyword.Text.Length > 0))
            {
                bt_search.Enabled = true;
            }
            else
            {
                bt_search.Enabled = false;
            }
        }

        /***********************************************************************
         * Name : txt_keyword_TextChanged
         * Description : Enable/Disable bt_search if text box != null
         **********************************************************************/
        private void txt_keyword_TextChanged(object sender, EventArgs e)
        {
            if ((txt_path.Text.Length > 0) && (txt_keyword.Text.Length > 0))
            {
                bt_search.Enabled = true;
            }
            else
            {
                bt_search.Enabled = false;
            }
        }

        /***********************************************************************
         * Name : list_match_file_SelectedIndexChanged
         * Description : Show information of file
         **********************************************************************/
        private void list_match_file_SelectedIndexChanged(object sender, EventArgs e)
        {
            string info = null;
            string file_path = group_file_name[list_match_file.SelectedIndex].Replace(@"\", "/");
            string file_name = Path.GetFileName(file_path);
            DateTime file_modified_date = File.GetLastWriteTime(file_path);

            info = "Path : " + file_path.Replace("/" + file_name, "") + "\r\n"; ;
            info += "File name : " + file_name + "\r\n";
            info += "Modified date: " + file_modified_date.Date.ToString("dd/MM/yyyy");

            txt_info.Text = info;

        }
    }
}
