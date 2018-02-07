using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Linq;
using System.Diagnostics;
using System.Threading.Tasks;

using Simple.Setting;

namespace CodeSeeker
{
    public partial class Form1 : Form
    {
        List<string> group_file_name = new List<string>();   /* store list of all file */

        Setting ST = new Setting();
        FileINFO file_info = new FileINFO();

        bool token = true;
        UInt32 sub_folder = 0;
        UInt64 scanned_file = 0;
        UInt64 collected_file = 0;

        /* [1] Init Form first */
        public Form1()
        {
            InitializeComponent();        
        }

        /* [1] Form Load */
        private void Form1_Load(object sender, EventArgs e)
        {
            ST._corresponding_line = new List<string>();
            ST._time_stamp = new List<DateTime>();
            file_info.name = new List<string>();
            ST.set_file_info(file_info);

            statusLabel.Text = "No file was loaded.";
            statusSearched.Text = "No file was searched.";
            DateTime tmp_date_time = DateTime.Now.Date;
            txt_from_date.Text = tmp_date_time.ToString("MM/dd/yyyy");
            txt_to_date.Text = tmp_date_time.ToString("MM/dd/yyyy");
        }

        /* [2] Load directory event */
        private async void btFolder_Click(object sender, EventArgs e)
        {
            /* Clear all global */
            listBox.Items.Clear();
            collected_file = 0;
            ST.buffer = null;
            group_file_name.Clear();
            statusSearched.Text = "No file was searched.";

            /* Private */
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string folder_name = dialog.SelectedPath;
                txt_destination.Text = folder_name;
                btSearch.Enabled = true;
            }
        }

        /* [2] Load Button Event */
        private void btSelect_Click(object sender, EventArgs e)
        {          
            /* Private */
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = true;
           
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                foreach(string file in dialog.FileNames)
                {
                    group_file_name.Add(file); /* Add files name in list */
                }          
            }
        }

        /* [2] Listbox Click Event */
        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox.SelectedIndex >= 0 && !ST.chkLastest_checked)
            {
                String tmp_str_info = null;
                String tmp_str_dot = ": ";
                String tmp_str_file_name = listBox.SelectedItem.ToString();
                DateTime tmp_dt_modification = File.GetLastWriteTime(tmp_str_file_name);

                tmp_str_info = "File name" + tmp_str_dot.PadLeft(11, ' ');
                tmp_str_info += Path.GetFileName(tmp_str_file_name) + "\r\n";
                tmp_str_info += "Modification date" + tmp_str_dot.PadLeft(3, ' ');
                tmp_str_info += tmp_dt_modification.ToString();
                txtContent.Text = tmp_str_info;
            }
        }

        
        /* [2] Search Click Event */
        private async void btSearch_Click(object sender, EventArgs e)
        {
            /* Toggle button */
            if (ST.clicked_BTSearch == true)
            {
                ST.clicked_BTSearch = false;
                ST.enable_load = false;
                btSearch.Text = "Search";
            }
            else
            {
                ST._corresponding_line.Clear();
                listBox.Items.Clear();
                ST.count_searched = 0;
                listBox.Items.Clear();

                ST.clicked_BTSearch = true;
                ST.enable_load = true;
                btSearch.Text = "Stop";
            }

            String tmp_dir = txt_destination.Text.ToString();

            DateTime tmp_from_date = Convert.ToDateTime(txt_from_date.Text);
            DateTime tmp_to_date = Convert.ToDateTime(txt_to_date.Text);
            UInt64 tmp_int_count_file = 0;
            String[] tmp_str_ext = new String[100];
            String str_ext = txt_ext.Text.ToString();

            int ext_index = 0;
            int index_of_star = 0;
            int index_of_bookmark = -1;

            while (str_ext.IndexOf("*", index_of_bookmark+1) >= 0)
            {
                index_of_bookmark = index_of_star;
                index_of_star = txt_ext.Text.IndexOf("*", index_of_bookmark+1);
                tmp_str_ext[ext_index++] = str_ext.Substring(index_of_bookmark, 3);      
            }

            await Task.Run(() =>
            {
                for (DateTime index_date = tmp_to_date; tmp_from_date <= index_date.Date; index_date = index_date.AddDays(-1))
                {
                    /* Update status of progress */
                    update_statusLabel("Scanning on " + index_date.Date.ToString("MM/dd/yyyy."));

                    bool skip_scan = false;
                    int index_from = 0;
                    for (int i = 0; i < ext_index; i++)
                    {
                        foreach (string subDir in Directory.GetDirectories(tmp_dir))
                        {
                            foreach (string file in Directory.GetFiles(subDir))
                            {
                                var todayFiles = Directory.GetFiles("path_to_directory")
                                       .Where(x => new FileInfo(x).CreationTime.Date == DateTime.Today.Date);
                            }
                        }

                        var todayFiles = Directory.GetFiles(tmp_dir, tmp_str_ext[i], SearchOption.AllDirectories)
                                .Where(x => new FileInfo(x).LastWriteTime.Date == index_date);
                        if (todayFiles.Count() > 0)
                        {
                            this.Invoke(new MethodInvoker(delegate ()
                            {
                                listBox.Items.Add("================== There are " + todayFiles.Count() + " files at "
                                            + index_date.Date.ToString("MM/dd/yyyy.") + " ===================");
                            }));
                        }

                        foreach (String file_name in todayFiles)
                        {
                            group_file_name.Add(file_name);
                        }

                        this.Invoke(new MethodInvoker(delegate ()
                        {
                            update_statusLabel("There are " + tmp_int_count_file++.ToString() + " files.");
                        }));

                        update_listBox(group_file_name, index_from);
                        index_from = index_from + group_file_name.Count() - 1;
                    } /* End of extension loop */
                }/* End of date time loop */
            });

            /* Reset */
            ST.clicked_BTSearch = false;
            update_statusLabel("Done.");
            btSearch.Text = "Search";

        }/* btSearch_Click */

        /*******************************************************************************
         * Name: load_data
         * Function: Load data from input file and put into buffer in order to read
         * Parameter: None
         * Returns: None
         * Description: None
         ******************************************************************************/
        public void load_data(string file_name)
        {
            FileStream fs = new FileStream(file_name, FileMode.Open, FileAccess.Read);
            UInt32 count_line = 0;

            /* Read all file into buffer */
            ST.buffer = File.ReadAllLines(file_name, Encoding.Default);
        }

        public async void update_statusLabel(String input)
        {
            statusLabel.Text = input;
            await Task.Delay(1);
        }


        /*******************************************************************************
         * Name: update_statusSearched
         * Function: Display status detail
         * Parameter: None
         * Returns: None
         * Description: None
         ******************************************************************************/
        public void update_statusSearched(String input)
        {
            statusSearched.Text = input;
        }

        /*******************************************************************************
         * Name: update_listBox
         * Function: Add item to listbox
         * Parameter: None
         * Returns: None
         * Description: None
         ******************************************************************************/
        public async void update_listBox(List<string> data, int index_from)
        {
            for (int i = index_from; i < data.Count() - 1; i++)
            {
                this.Invoke(new MethodInvoker(delegate ()
                {
                    listBox.Items.Add(data.ElementAt(i));
                }));
                await Task.Delay(1);
            }      
        }

        /*******************************************************************************
         * Name: listBox_DoubleClick
         * Function: Open file when double click on listbox
         * Parameter: None
         * Returns: None
         * Description: None
         ******************************************************************************/
        private void listBox_DoubleClick(object sender, EventArgs e)
        {
            string list_item = listBox.GetItemText(listBox.SelectedItem);
            int str_index = list_item.IndexOf(" - Line");
            string path = list_item.Remove(str_index, list_item.Length - str_index);
            
            Process.Start(path);
        }

        /*******************************************************************************
         * Name: chkSource_CheckedChanged
         * Function: Detect checkbox .c ON or OFF
         * Parameter: None
         * Returns: None
         * Description: None
         ******************************************************************************/
        private void chkSource_CheckedChanged(object sender, EventArgs e)
        {
            ST.chkSource_checked = (!ST.chkSource_checked) ? true : false;
        }

        /*******************************************************************************
         * Name: chkHeader_CheckedChanged
         * Function: Detect checkbox .h ON or OFF
         * Parameter: None
         * Returns: None
         * Description: None
         ******************************************************************************/
        private void chkHeader_CheckedChanged(object sender, EventArgs e)
        {
            ST.chkHeader_checked = (!ST.chkHeader_checked) ? true : false;
        }

        private void selectFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            /* Clear all global */
            listBox.Items.Clear();
            collected_file = 0;
            ST.buffer = null;
            group_file_name.Clear();
            statusSearched.Text = "No file was searched.";

            /* Private */
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string folder_name = dialog.SelectedPath;
                txt_destination.Text = folder_name;
                btSearch.Enabled = true;
            }
        }
    }
}
