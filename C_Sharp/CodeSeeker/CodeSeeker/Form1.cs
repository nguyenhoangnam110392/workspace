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
        UInt64 count_file = 0;

        Setting setting = new Setting();
        FileINFO file_info = new FileINFO();

        bool token = true;
        UInt32 sub_folder = 0;

        /* [1] Init Form first */
        public Form1()
        {
            InitializeComponent();        
        }

        /* [1] Form Load */
        private void Form1_Load(object sender, EventArgs e)
        {
            setting._corresponding_line = new List<string>();
            setting._time_stamp = new List<DateTime>();
            file_info.name = new List<string>();
            setting.set_file_info(file_info);

            statusLabel.Text = "No file was loaded.";
            statusSearched.Text = "No file was searched.";
        }

        /* [2] Load directory event */
        private async void btFolder_Click(object sender, EventArgs e)
        {
            /* Clear all global */
            setting._corresponding_line.Clear();
            listBox.Items.Clear();
            count_file = 0;
            setting.buffer = null;
            group_file_name.Clear();
            statusSearched.Text = "No file was searched.";

            /* Private */
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (dialog.ShowDialog() == DialogResult.OK && (setting.chkHeader_checked | setting.chkSource_checked | setting.chkLastest_checked))
            {
                string folder_name = dialog.SelectedPath;           
                SubDir(folder_name, token);
                btSearch.Enabled = true;
            }
            
        }

        /* [2] Sub dir first */
        private async void SubDir(string directory, bool token)
        {
            if (token==false) { return; }
            try
            {
                foreach (string d in Directory.GetDirectories(directory))
                {
                    var ext = new List<string>();  /* List of extension */

                    if (setting.chkSource_checked)
                    {
                        ext.Add(".c");
                    }

                    if (setting.chkHeader_checked)
                    {
                        ext.Add(".h");                     
                    }

                    if (setting.chkLastest_checked)
                    {
                        ext.Clear();
                        ext.Add(".c");
                        ext.Add(".h");
                        ext.Add(".exe");
                    }

                    foreach (string f in Directory.GetFiles(d).Where(s => ext.Contains(Path.GetExtension(s))))
                    {
                        group_file_name.Add(f); /* Add files name in list */
                        count_file++;
                    }

                    sub_folder++;
                    SubDir(d, token);
                    statusLabel.Text = count_file + " files was loaded. Sub folder :" + sub_folder;
                    await Task.Delay(10);
                }
            }
            catch (System.Exception except)
            {
                sub_folder--;
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
            if (listBox.SelectedIndex >= 0 && !setting.chkLastest_checked)
            {
                txtContent.Text = setting._corresponding_line.ElementAt(listBox.SelectedIndex);
            }
        }

        
        /* [2] Search Click Event */
        private async void btSearch_Click(object sender, EventArgs e)
        {
            /* Variable */
            setting.keyword = txtKeyword.Text;
            bool flag_compare = false;

            /* Toggle button *//* Already clicked */
            if (setting.clicked_BTSearch == true){ 
                setting.clicked_BTSearch = false;
                setting.enable_load = false;
                btSearch.Text = "Search";
            }
            else  /* Not yet */
            {
                /* Reset */
                setting._corresponding_line.Clear();
                listBox.Items.Clear();
                setting.count_searched = 0;
                listBox.Items.Clear();
                

                setting.clicked_BTSearch = true;
                setting.enable_load = true;
                btSearch.Text = "Stop";
            }

            
            if (setting.keyword.Length > 0 && group_file_name.Count > 0)
            {
                foreach (string file in group_file_name.ToList())
                {
                    setting.line_index = 0;

                    /* If match keyword is selected */
                    if (setting.enable_load && !setting.chkLastest_checked)
                    {
                        await Task.Run(() =>
                        {
                            load_data(file);
                        });

                        /* scan for keyword match */
                        setting.scan_content_file(file, this);
                    }
                    else if (setting.enable_load && setting.chkLastest_checked) /* Lastest files is selected */
                    {
                        setting.scan_for_time_stamp(file);                                            
                    }                    
                }
                /* add file in list to listbox */
                List<DateTime> main_list = setting._time_stamp.OrderBy(x => x.Year).ToList();

                /* Remove older year */
                for(int i=main_list.Count-1; i>=0; i--)
                {
                    if (main_list[i].Year != DateTime.Now.Year)
                    {
                        main_list.RemoveAt(i);
                    }
                }

                /* Sort by day */
                main_list = main_list.OrderBy(x => x.Day).ToList();
                int latest_day = main_list[0].Day;
                /* Remove older date */
                for (int i = main_list.Count-1; i>=0; i--)
                {
                    if(main_list[i].Day != latest_day)
                    {
                        main_list.RemoveAt(i);
                    }
                }

                /* Sort by time */
                main_list = main_list.OrderBy(x => x.TimeOfDay).ToList();

                for (int i = main_list.Count - 1; i >= 0; i--)
                {
                    update_listBox(file_info.name[i] + ". Date " + main_list[i].ToString("HH:mm:ss - dd/MM/yyyy"));                      
                    await Task.Delay(10);
                }
                
                
            }      
        }

        public void load_data(string file_name)
        {
            FileStream fs = new FileStream(file_name, FileMode.Open, FileAccess.Read);
            UInt32 count_line = 0;

            /* Read all file into buffer */
            setting.buffer = File.ReadAllLines(file_name, Encoding.Default);      
        }

        /* Update object in graphic main files */
        public void update_statusSearched()
        {
            statusSearched.Text = setting.count_searched + " files was searched.";
        }

        public void update_listBox(String data)
        {
            listBox.Items.Add(data);
        }

        /* [2] Clear Keyword textbox*/
        private void txtKeyword_DoubleClick(object sender, MouseEventArgs e)
        {
            txtKeyword.Text = null;
        }

        /* Start function */
        private void listBox_DoubleClick(object sender, EventArgs e)
        {
            string list_item = listBox.GetItemText(listBox.SelectedItem);
            int str_index = list_item.IndexOf(" - Line");
            string path = list_item.Remove(str_index, list_item.Length - str_index);
            
            Process.Start(path);
        }

        /* Start function */
        private void chkSource_CheckedChanged(object sender, EventArgs e)
        {
            setting.chkSource_checked = (!setting.chkSource_checked) ? true : false;
        }

        /* Start function */
        private void chkHeader_CheckedChanged(object sender, EventArgs e)
        {
            setting.chkHeader_checked = (!setting.chkHeader_checked) ? true : false;
        }

        /* Start function */
        private void chkLastest_CheckedChanged(object sender, EventArgs e)
        {
            setting.chkLastest_checked = (!setting.chkLastest_checked) ? true : false;
        }       
    }
}
