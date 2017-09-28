using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Linq;
using System.Diagnostics;

namespace CodeSeeker
{
    public partial class Form1 : Form
    {
        List<string> _content = new List<string>();
        string[] group_file_name;
        UInt16 list_index = 0;

        /* [1] Init Form first */
        public Form1()
        {
            InitializeComponent();
        }

        /* [1] Form Load */
        private void Form1_Load(object sender, EventArgs e)
        {
            statusLabel.Text = "No file is loaded.";
        }

        /* [2] Load directory event */
        private void button1_Click(object sender, EventArgs e)
        {
            /* Clear all global */
            _content.Clear();
            listBox.Items.Clear();
            list_index = 0;

            /* Private */
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                String folder_name = dialog.SelectedPath;
                MessageBox.Show(folder_name);
            }

        }
        /* [2] Load Button Event */
        private void btSelect_Click(object sender, EventArgs e)
        {
            /* Clear all global */
            _content.Clear();
            listBox.Items.Clear();
            list_index = 0;

            /* Private */
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = true;
           
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                group_file_name = dialog.FileNames;             
            }

            statusLabel.Text = dialog.FileNames.Count() + " files is loaded.";
        }

        /* [2] Listbox Click Event */
        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox.SelectedIndex >= 0)
            {
                txtContent.Text = _content.ElementAt(listBox.SelectedIndex);
            }
        }

        /* [2] Search directory first */
        //private void DirectorySearch()
        //{
        //    try
        //    {
        //        foreach (string d in Directory.GetDirectories(sDir))
        //        {
        //            foreach (string f in Directory.GetFiles(d, sMatch))
        //            {
        //                lstFilesFound.Add(f);
        //            }
        //            DirSearch(d);
        //        }
        //    }
        //    catch (System.Exception excpt)
        //    {
        //        Console.WriteLine(excpt.Message);
        //    }
        //}

        

        /* [2] Search Click Event */
        private void btSearch_Click(object sender, EventArgs e)
        {
            /* Variable */
            string keyword = txtKeyword.Text;

            if (keyword.Length > 0 && group_file_name != null)
            {
                _content.Clear();
                listBox.Items.Clear();
                list_index = 0;

                foreach (string single_file_name in group_file_name)
                {
                    string[] lines = File.ReadAllLines(single_file_name, Encoding.UTF8);
                    UInt32 line_index = 0;

                    foreach (string single_line in lines)
                    {
                        line_index++;
                        if (single_line.Contains(keyword))
                        {
                            listBox.Items.Add(single_file_name + " - Line " + line_index);
                            _content.Add(single_line);
                            list_index++;
                        }
                    }
                }
            }
        }

        
        /* [2] Clear Keyword textbox*/
        private void txtKeyword_DoubleClick(object sender, MouseEventArgs e)
        {
            txtKeyword.Text = null;
        }
        
        /* [2] Open file using software */
        private void listBox_DoubleClick(object sender, EventArgs e)
        {
            string path = group_file_name[listBox.SelectedIndex];
            Process.Start("D:/Sublime Text Build 3126 x64/sublime_text.exe", path);
        }
    }
}
