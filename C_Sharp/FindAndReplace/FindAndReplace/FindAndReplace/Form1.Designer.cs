namespace FindAndReplace
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.label_status = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.list_match_file = new System.Windows.Forms.ListBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txt_path = new System.Windows.Forms.TextBox();
            this.bt_search = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.txt_keyword = new System.Windows.Forms.TextBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.rd_default = new System.Windows.Forms.RadioButton();
            this.rd_over_write = new System.Windows.Forms.RadioButton();
            this.rd_save_as = new System.Windows.Forms.RadioButton();
            this.txt_save = new System.Windows.Forms.TextBox();
            this.bt_Run = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_replace = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txt_find = new System.Windows.Forms.TextBox();
            this.bt_list_item_remove = new System.Windows.Forms.Button();
            this.list_file = new System.Windows.Forms.CheckedListBox();
            this.bt_add_file = new System.Windows.Forms.Button();
            this.txt_info = new System.Windows.Forms.TextBox();
            this.statusStrip1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.label_status});
            this.statusStrip1.Location = new System.Drawing.Point(0, 444);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(693, 22);
            this.statusStrip1.TabIndex = 19;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // label_status
            // 
            this.label_status.Name = "label_status";
            this.label_status.Size = new System.Drawing.Size(42, 17);
            this.label_status.Text = "Ready.";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(672, 428);
            this.tabControl1.TabIndex = 20;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.txt_info);
            this.tabPage2.Controls.Add(this.list_match_file);
            this.tabPage2.Controls.Add(this.label5);
            this.tabPage2.Controls.Add(this.txt_path);
            this.tabPage2.Controls.Add(this.bt_search);
            this.tabPage2.Controls.Add(this.label4);
            this.tabPage2.Controls.Add(this.txt_keyword);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(664, 402);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Find";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // list_match_file
            // 
            this.list_match_file.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.list_match_file.FormattingEnabled = true;
            this.list_match_file.ItemHeight = 15;
            this.list_match_file.Location = new System.Drawing.Point(6, 76);
            this.list_match_file.Name = "list_match_file";
            this.list_match_file.Size = new System.Drawing.Size(649, 229);
            this.list_match_file.TabIndex = 35;
            this.list_match_file.SelectedIndexChanged += new System.EventHandler(this.list_match_file_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(19, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(48, 16);
            this.label5.TabIndex = 34;
            this.label5.Text = "Where";
            // 
            // txt_path
            // 
            this.txt_path.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_path.Location = new System.Drawing.Point(81, 16);
            this.txt_path.Name = "txt_path";
            this.txt_path.Size = new System.Drawing.Size(473, 22);
            this.txt_path.TabIndex = 1;
            this.txt_path.TextChanged += new System.EventHandler(this.txt_path_TextChanged);
            // 
            // bt_search
            // 
            this.bt_search.Enabled = false;
            this.bt_search.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_search.Image = ((System.Drawing.Image)(resources.GetObject("bt_search.Image")));
            this.bt_search.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_search.Location = new System.Drawing.Point(560, 16);
            this.bt_search.Name = "bt_search";
            this.bt_search.Size = new System.Drawing.Size(95, 54);
            this.bt_search.TabIndex = 32;
            this.bt_search.Text = "Search";
            this.bt_search.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_search.UseVisualStyleBackColor = true;
            this.bt_search.Click += new System.EventHandler(this.bt_search_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(33, 51);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(34, 16);
            this.label4.TabIndex = 29;
            this.label4.Text = "Find";
            // 
            // txt_keyword
            // 
            this.txt_keyword.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_keyword.Location = new System.Drawing.Point(81, 48);
            this.txt_keyword.Name = "txt_keyword";
            this.txt_keyword.Size = new System.Drawing.Size(473, 22);
            this.txt_keyword.TabIndex = 2;
            this.txt_keyword.TextChanged += new System.EventHandler(this.txt_keyword_TextChanged);
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.rd_default);
            this.tabPage3.Controls.Add(this.rd_over_write);
            this.tabPage3.Controls.Add(this.rd_save_as);
            this.tabPage3.Controls.Add(this.txt_save);
            this.tabPage3.Controls.Add(this.bt_Run);
            this.tabPage3.Controls.Add(this.label2);
            this.tabPage3.Controls.Add(this.txt_replace);
            this.tabPage3.Controls.Add(this.label1);
            this.tabPage3.Controls.Add(this.txt_find);
            this.tabPage3.Controls.Add(this.bt_list_item_remove);
            this.tabPage3.Controls.Add(this.list_file);
            this.tabPage3.Controls.Add(this.bt_add_file);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(664, 402);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Replace";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // rd_default
            // 
            this.rd_default.AutoSize = true;
            this.rd_default.Location = new System.Drawing.Point(219, 285);
            this.rd_default.Name = "rd_default";
            this.rd_default.Size = new System.Drawing.Size(272, 17);
            this.rd_default.TabIndex = 42;
            this.rd_default.Text = "Save to the same folder, add \"_replaced\" at the end";
            this.rd_default.UseVisualStyleBackColor = true;
            this.rd_default.CheckedChanged += new System.EventHandler(this.rd_default_CheckedChanged);
            // 
            // rd_over_write
            // 
            this.rd_over_write.AutoSize = true;
            this.rd_over_write.Location = new System.Drawing.Point(113, 285);
            this.rd_over_write.Name = "rd_over_write";
            this.rd_over_write.Size = new System.Drawing.Size(70, 17);
            this.rd_over_write.TabIndex = 41;
            this.rd_over_write.Text = "Overwrite";
            this.rd_over_write.UseVisualStyleBackColor = true;
            this.rd_over_write.CheckedChanged += new System.EventHandler(this.rd_over_write_CheckedChanged);
            // 
            // rd_save_as
            // 
            this.rd_save_as.AutoSize = true;
            this.rd_save_as.Checked = true;
            this.rd_save_as.Location = new System.Drawing.Point(10, 285);
            this.rd_save_as.Name = "rd_save_as";
            this.rd_save_as.Size = new System.Drawing.Size(65, 17);
            this.rd_save_as.TabIndex = 40;
            this.rd_save_as.TabStop = true;
            this.rd_save_as.Text = "Save As";
            this.rd_save_as.UseVisualStyleBackColor = true;
            this.rd_save_as.CheckedChanged += new System.EventHandler(this.rd_save_as_CheckedChanged);
            // 
            // txt_save
            // 
            this.txt_save.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_save.Location = new System.Drawing.Point(10, 308);
            this.txt_save.Name = "txt_save";
            this.txt_save.Size = new System.Drawing.Size(643, 22);
            this.txt_save.TabIndex = 3;
            // 
            // bt_Run
            // 
            this.bt_Run.Enabled = false;
            this.bt_Run.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_Run.Image = ((System.Drawing.Image)(resources.GetObject("bt_Run.Image")));
            this.bt_Run.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_Run.Location = new System.Drawing.Point(558, 340);
            this.bt_Run.Name = "bt_Run";
            this.bt_Run.Size = new System.Drawing.Size(95, 55);
            this.bt_Run.TabIndex = 6;
            this.bt_Run.Text = "Run";
            this.bt_Run.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_Run.UseVisualStyleBackColor = true;
            this.bt_Run.Click += new System.EventHandler(this.bt_Run_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(5, 376);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 16);
            this.label2.TabIndex = 37;
            this.label2.Text = "Replace";
            // 
            // txt_replace
            // 
            this.txt_replace.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_replace.Location = new System.Drawing.Point(79, 373);
            this.txt_replace.Name = "txt_replace";
            this.txt_replace.Size = new System.Drawing.Size(473, 22);
            this.txt_replace.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(31, 343);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 16);
            this.label1.TabIndex = 35;
            this.label1.Text = "Find";
            // 
            // txt_find
            // 
            this.txt_find.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_find.Location = new System.Drawing.Point(79, 340);
            this.txt_find.Name = "txt_find";
            this.txt_find.Size = new System.Drawing.Size(473, 22);
            this.txt_find.TabIndex = 4;
            this.txt_find.TextChanged += new System.EventHandler(this.txt_find_TextChanged);
            // 
            // bt_list_item_remove
            // 
            this.bt_list_item_remove.Image = ((System.Drawing.Image)(resources.GetObject("bt_list_item_remove.Image")));
            this.bt_list_item_remove.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_list_item_remove.Location = new System.Drawing.Point(122, 7);
            this.bt_list_item_remove.Name = "bt_list_item_remove";
            this.bt_list_item_remove.Size = new System.Drawing.Size(163, 46);
            this.bt_list_item_remove.TabIndex = 33;
            this.bt_list_item_remove.Text = "Remove selected items..";
            this.bt_list_item_remove.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_list_item_remove.UseVisualStyleBackColor = true;
            this.bt_list_item_remove.Click += new System.EventHandler(this.bt_list_item_remove_Click);
            // 
            // list_file
            // 
            this.list_file.FormattingEnabled = true;
            this.list_file.Location = new System.Drawing.Point(8, 65);
            this.list_file.Name = "list_file";
            this.list_file.Size = new System.Drawing.Size(645, 214);
            this.list_file.TabIndex = 32;
            // 
            // bt_add_file
            // 
            this.bt_add_file.Image = ((System.Drawing.Image)(resources.GetObject("bt_add_file.Image")));
            this.bt_add_file.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_add_file.Location = new System.Drawing.Point(8, 7);
            this.bt_add_file.Name = "bt_add_file";
            this.bt_add_file.Size = new System.Drawing.Size(99, 46);
            this.bt_add_file.TabIndex = 31;
            this.bt_add_file.Text = "Add Files...";
            this.bt_add_file.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_add_file.UseVisualStyleBackColor = true;
            this.bt_add_file.Click += new System.EventHandler(this.bt_add_file_Click);
            // 
            // txt_info
            // 
            this.txt_info.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_info.Location = new System.Drawing.Point(6, 311);
            this.txt_info.Multiline = true;
            this.txt_info.Name = "txt_info";
            this.txt_info.Size = new System.Drawing.Size(649, 85);
            this.txt_info.TabIndex = 36;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(693, 466);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.statusStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Find & Replace";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel label_status;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txt_path;
        private System.Windows.Forms.Button bt_search;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txt_keyword;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.RadioButton rd_default;
        private System.Windows.Forms.RadioButton rd_over_write;
        private System.Windows.Forms.RadioButton rd_save_as;
        private System.Windows.Forms.TextBox txt_save;
        private System.Windows.Forms.Button bt_Run;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_replace;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txt_find;
        private System.Windows.Forms.Button bt_list_item_remove;
        private System.Windows.Forms.CheckedListBox list_file;
        private System.Windows.Forms.Button bt_add_file;
        private System.Windows.Forms.ListBox list_match_file;
        private System.Windows.Forms.TextBox txt_info;
    }
}

