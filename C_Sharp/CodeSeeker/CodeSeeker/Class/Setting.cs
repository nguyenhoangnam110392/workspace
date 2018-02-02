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

        public bool time_stamp_scan_done { get; set; } = false;
        public List<DateTime> _time_stamp { get; set; } = null;       /* list contains time stamp of files */
        public List<string> _corresponding_line { get; set; } = null; /* list of line correspond to file */

        private UInt16 index = 0;
        public DateTime max_time;

        public int count_searched { get; set; } = 0;                  /* number of searching files */
        public UInt64 line_index { get; set; } = 0;                   /* number of matching line in file */

        public string keyword { get; set; } = null;                   /* keyword for matching */
        public string[] buffer { get; set; } = null;                  /* buffer stores the content of file */
        public int Total_File { get; set; } = 0;                  /* Total number of files in folder and sub-folder */

        public FileINFO file_info;

        public void set_file_info(FileINFO set_fi)
        {
            this.file_info = set_fi;
        }
    }

    class FileINFO
    {
        public List<String> name { get; set; }
        public DateTime[] modify_time { get; set; }
    }
}
