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
            this.bt_add_file = new System.Windows.Forms.Button();
            this.list_file = new System.Windows.Forms.CheckedListBox();
            this.bt_list_item_remove = new System.Windows.Forms.Button();
            this.txt_find = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_replace = new System.Windows.Forms.TextBox();
            this.bt_Run = new System.Windows.Forms.Button();
            this.txt_save = new System.Windows.Forms.TextBox();
            this.rd_save_as = new System.Windows.Forms.RadioButton();
            this.rd_over_write = new System.Windows.Forms.RadioButton();
            this.rd_default = new System.Windows.Forms.RadioButton();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.label_status = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // bt_add_file
            // 
            this.bt_add_file.Image = ((System.Drawing.Image)(resources.GetObject("bt_add_file.Image")));
            this.bt_add_file.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_add_file.Location = new System.Drawing.Point(32, 12);
            this.bt_add_file.Name = "bt_add_file";
            this.bt_add_file.Size = new System.Drawing.Size(99, 46);
            this.bt_add_file.TabIndex = 3;
            this.bt_add_file.Text = "Add Files...";
            this.bt_add_file.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_add_file.UseVisualStyleBackColor = true;
            this.bt_add_file.Click += new System.EventHandler(this.bt_add_file_Click);
            // 
            // list_file
            // 
            this.list_file.FormattingEnabled = true;
            this.list_file.Location = new System.Drawing.Point(32, 70);
            this.list_file.Name = "list_file";
            this.list_file.Size = new System.Drawing.Size(645, 214);
            this.list_file.TabIndex = 5;
            // 
            // bt_list_item_remove
            // 
            this.bt_list_item_remove.Image = ((System.Drawing.Image)(resources.GetObject("bt_list_item_remove.Image")));
            this.bt_list_item_remove.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_list_item_remove.Location = new System.Drawing.Point(146, 12);
            this.bt_list_item_remove.Name = "bt_list_item_remove";
            this.bt_list_item_remove.Size = new System.Drawing.Size(163, 46);
            this.bt_list_item_remove.TabIndex = 8;
            this.bt_list_item_remove.Text = "Remove selected items..";
            this.bt_list_item_remove.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_list_item_remove.UseVisualStyleBackColor = true;
            this.bt_list_item_remove.Click += new System.EventHandler(this.bt_list_item_remove_Click);
            // 
            // txt_find
            // 
            this.txt_find.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_find.Location = new System.Drawing.Point(103, 345);
            this.txt_find.Name = "txt_find";
            this.txt_find.Size = new System.Drawing.Size(473, 22);
            this.txt_find.TabIndex = 9;
            this.txt_find.TextChanged += new System.EventHandler(this.txt_find_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(29, 348);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 16);
            this.label1.TabIndex = 10;
            this.label1.Text = "Find";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(29, 381);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 16);
            this.label2.TabIndex = 12;
            this.label2.Text = "Replace";
            // 
            // txt_replace
            // 
            this.txt_replace.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_replace.Location = new System.Drawing.Point(103, 378);
            this.txt_replace.Name = "txt_replace";
            this.txt_replace.Size = new System.Drawing.Size(473, 22);
            this.txt_replace.TabIndex = 11;
            // 
            // bt_Run
            // 
            this.bt_Run.Enabled = false;
            this.bt_Run.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_Run.Image = ((System.Drawing.Image)(resources.GetObject("bt_Run.Image")));
            this.bt_Run.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.bt_Run.Location = new System.Drawing.Point(582, 345);
            this.bt_Run.Name = "bt_Run";
            this.bt_Run.Size = new System.Drawing.Size(95, 55);
            this.bt_Run.TabIndex = 13;
            this.bt_Run.Text = "Run";
            this.bt_Run.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.bt_Run.UseVisualStyleBackColor = true;
            this.bt_Run.Click += new System.EventHandler(this.bt_Run_Click);
            // 
            // txt_save
            // 
            this.txt_save.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_save.Location = new System.Drawing.Point(34, 313);
            this.txt_save.Name = "txt_save";
            this.txt_save.Size = new System.Drawing.Size(643, 22);
            this.txt_save.TabIndex = 14;
            // 
            // rd_save_as
            // 
            this.rd_save_as.AutoSize = true;
            this.rd_save_as.Checked = true;
            this.rd_save_as.Location = new System.Drawing.Point(34, 290);
            this.rd_save_as.Name = "rd_save_as";
            this.rd_save_as.Size = new System.Drawing.Size(65, 17);
            this.rd_save_as.TabIndex = 16;
            this.rd_save_as.TabStop = true;
            this.rd_save_as.Text = "Save As";
            this.rd_save_as.UseVisualStyleBackColor = true;
            this.rd_save_as.CheckedChanged += new System.EventHandler(this.rd_save_as_CheckedChanged);
            // 
            // rd_over_write
            // 
            this.rd_over_write.AutoSize = true;
            this.rd_over_write.Location = new System.Drawing.Point(137, 290);
            this.rd_over_write.Name = "rd_over_write";
            this.rd_over_write.Size = new System.Drawing.Size(70, 17);
            this.rd_over_write.TabIndex = 17;
            this.rd_over_write.Text = "Overwrite";
            this.rd_over_write.UseVisualStyleBackColor = true;
            this.rd_over_write.CheckedChanged += new System.EventHandler(this.rd_over_write_CheckedChanged);
            // 
            // rd_default
            // 
            this.rd_default.AutoSize = true;
            this.rd_default.Location = new System.Drawing.Point(243, 290);
            this.rd_default.Name = "rd_default";
            this.rd_default.Size = new System.Drawing.Size(272, 17);
            this.rd_default.TabIndex = 18;
            this.rd_default.Text = "Save to the same folder, add \"_replaced\" at the end";
            this.rd_default.UseVisualStyleBackColor = true;
            this.rd_default.CheckedChanged += new System.EventHandler(this.rd_default_CheckedChanged);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.label_status});
            this.statusStrip1.Location = new System.Drawing.Point(0, 407);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(700, 22);
            this.statusStrip1.TabIndex = 19;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // label_status
            // 
            this.label_status.Name = "label_status";
            this.label_status.Size = new System.Drawing.Size(42, 17);
            this.label_status.Text = "Ready.";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(700, 429);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.rd_default);
            this.Controls.Add(this.rd_over_write);
            this.Controls.Add(this.rd_save_as);
            this.Controls.Add(this.txt_save);
            this.Controls.Add(this.bt_Run);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txt_replace);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_find);
            this.Controls.Add(this.bt_list_item_remove);
            this.Controls.Add(this.list_file);
            this.Controls.Add(this.bt_add_file);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Find & Replace";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button bt_add_file;
        private System.Windows.Forms.CheckedListBox list_file;
        private System.Windows.Forms.Button bt_list_item_remove;
        private System.Windows.Forms.TextBox txt_find;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_replace;
        private System.Windows.Forms.Button bt_Run;
        private System.Windows.Forms.TextBox txt_save;
        private System.Windows.Forms.RadioButton rd_save_as;
        private System.Windows.Forms.RadioButton rd_over_write;
        private System.Windows.Forms.RadioButton rd_default;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel label_status;
    }
}

