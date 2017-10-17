using System;
using System.Collections.Generic;
using System.IO;

using CodeSeeker;

namespace Simple.Setting
{
    class Setting
    {
        public bool clicked_BTSearch { get; set; } = false;
        public bool enable_load { get; set; } = false;
        public bool chkSource_checked { get; set; } = false;
        public bool chkHeader_checked { get; set; } = false;
        public bool chkLastest_checked { get; set; } = false;

        public List<DateTime> _time_stamp { get; set; } = null;         /* list contains time stamp of files */
        public List<string> _corresponding_line { get; set; } = null; /* list of line correspond to file */

        private UInt16 index = 0;
        public DateTime max_time;

        public int count_searched { get; set; } = 0;                  /* number of searching files */
        public UInt64 line_index { get; set; } = 0;                   /* number of matching line in file */

        public string keyword { get; set; } = null;                   /* keyword for matching */
        public string[] buffer { get; set; } = null;                  /* buffer stores the content of file */

        private FileINFO file_info;

        public void set_file_info(FileINFO set_fi)
        {
            this.file_info = set_fi;
        }

        /* Start function */
        public void scan_content_file(String file, Form1 sender)
        {
            count_searched++;
            sender.update_statusSearched();  /*statusSearched.Text = count_searched + " files was searched.";*/

            foreach (string single_line in buffer)
            {
                line_index++;
                if (single_line.Contains(keyword))
                {
                    sender.update_listBox(file + " - Line " + line_index);   /*listBox.Items.Add(file + " - Line " + line_index);*/
                    _corresponding_line.Add(single_line);
                }
            }
            buffer = null;  /* Clear buffer after using */
        }/* End function */

        public void scan_for_time_stamp(String file)
        {
            _time_stamp.Add(File.GetLastWriteTime(file));
            file_info.name.Add(file);
        }
    }

    class FileINFO
    {
        public List<String> name { get; set; }
        public DateTime[] modify_time { get; set; }
    }
}
