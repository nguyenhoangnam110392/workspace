namespace CodeSeeker
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
            this.btSelect = new System.Windows.Forms.Button();
            this.txtKeyword = new System.Windows.Forms.TextBox();
            this.listBox = new System.Windows.Forms.ListBox();
            this.txtContent = new System.Windows.Forms.TextBox();
            this.btSearch = new System.Windows.Forms.Button();
            this.statusPanel = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusSearched = new System.Windows.Forms.ToolStripStatusLabel();
            this.btFolder = new System.Windows.Forms.Button();
            this.chkSource = new System.Windows.Forms.CheckBox();
            this.chkHeader = new System.Windows.Forms.CheckBox();
            this.chkLastest = new System.Windows.Forms.CheckBox();
            this.statusPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // btSelect
            // 
            this.btSelect.Image = ((System.Drawing.Image)(resources.GetObject("btSelect.Image")));
            this.btSelect.Location = new System.Drawing.Point(22, 12);
            this.btSelect.Name = "btSelect";
            this.btSelect.Size = new System.Drawing.Size(58, 30);
            this.btSelect.TabIndex = 0;
            this.btSelect.UseVisualStyleBackColor = true;
            this.btSelect.Click += new System.EventHandler(this.btSelect_Click);
            // 
            // txtKeyword
            // 
            this.txtKeyword.Location = new System.Drawing.Point(261, 12);
            this.txtKeyword.Multiline = true;
            this.txtKeyword.Name = "txtKeyword";
            this.txtKeyword.Size = new System.Drawing.Size(880, 63);
            this.txtKeyword.TabIndex = 1;
            this.txtKeyword.Text = "COPYRIGHT";
            this.txtKeyword.MouseClick += new System.Windows.Forms.MouseEventHandler(this.txtKeyword_DoubleClick);
            // 
            // listBox
            // 
            this.listBox.FormattingEnabled = true;
            this.listBox.Location = new System.Drawing.Point(22, 86);
            this.listBox.Name = "listBox";
            this.listBox.Size = new System.Drawing.Size(1119, 251);
            this.listBox.TabIndex = 3;
            this.listBox.SelectedIndexChanged += new System.EventHandler(this.listBox_SelectedIndexChanged);
            this.listBox.DoubleClick += new System.EventHandler(this.listBox_DoubleClick);
            // 
            // txtContent
            // 
            this.txtContent.Location = new System.Drawing.Point(22, 343);
            this.txtContent.Multiline = true;
            this.txtContent.Name = "txtContent";
            this.txtContent.Size = new System.Drawing.Size(1119, 137);
            this.txtContent.TabIndex = 4;
            // 
            // btSearch
            // 
            this.btSearch.Enabled = false;
            this.btSearch.Location = new System.Drawing.Point(22, 48);
            this.btSearch.Name = "btSearch";
            this.btSearch.Size = new System.Drawing.Size(123, 30);
            this.btSearch.TabIndex = 5;
            this.btSearch.Text = "Search";
            this.btSearch.UseVisualStyleBackColor = true;
            this.btSearch.Click += new System.EventHandler(this.btSearch_Click);
            // 
            // statusPanel
            // 
            this.statusPanel.BackColor = System.Drawing.Color.White;
            this.statusPanel.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel,
            this.statusSearched});
            this.statusPanel.Location = new System.Drawing.Point(0, 495);
            this.statusPanel.Name = "statusPanel";
            this.statusPanel.Size = new System.Drawing.Size(1162, 22);
            this.statusPanel.TabIndex = 6;
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // statusSearched
            // 
            this.statusSearched.Name = "statusSearched";
            this.statusSearched.Size = new System.Drawing.Size(55, 17);
            this.statusSearched.Text = "Searched";
            // 
            // btFolder
            // 
            this.btFolder.Image = ((System.Drawing.Image)(resources.GetObject("btFolder.Image")));
            this.btFolder.Location = new System.Drawing.Point(86, 12);
            this.btFolder.Name = "btFolder";
            this.btFolder.Size = new System.Drawing.Size(58, 30);
            this.btFolder.TabIndex = 7;
            this.btFolder.UseVisualStyleBackColor = true;
            this.btFolder.Click += new System.EventHandler(this.btFolder_Click);
            // 
            // chkSource
            // 
            this.chkSource.AutoSize = true;
            this.chkSource.Location = new System.Drawing.Point(174, 12);
            this.chkSource.Name = "chkSource";
            this.chkSource.Size = new System.Drawing.Size(76, 17);
            this.chkSource.TabIndex = 8;
            this.chkSource.Text = "Source *.c";
            this.chkSource.UseVisualStyleBackColor = true;
            this.chkSource.CheckedChanged += new System.EventHandler(this.chkSource_CheckedChanged);
            // 
            // chkHeader
            // 
            this.chkHeader.AutoSize = true;
            this.chkHeader.Location = new System.Drawing.Point(174, 35);
            this.chkHeader.Name = "chkHeader";
            this.chkHeader.Size = new System.Drawing.Size(77, 17);
            this.chkHeader.TabIndex = 9;
            this.chkHeader.Text = "Header *.h";
            this.chkHeader.UseVisualStyleBackColor = true;
            this.chkHeader.CheckedChanged += new System.EventHandler(this.chkHeader_CheckedChanged);
            // 
            // chkLastest
            // 
            this.chkLastest.AutoSize = true;
            this.chkLastest.Location = new System.Drawing.Point(174, 58);
            this.chkLastest.Name = "chkLastest";
            this.chkLastest.Size = new System.Drawing.Size(81, 17);
            this.chkLastest.TabIndex = 10;
            this.chkLastest.Text = "Lastest files";
            this.chkLastest.UseVisualStyleBackColor = true;
            this.chkLastest.CheckedChanged += new System.EventHandler(this.chkLastest_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1162, 517);
            this.Controls.Add(this.chkLastest);
            this.Controls.Add(this.chkHeader);
            this.Controls.Add(this.chkSource);
            this.Controls.Add(this.btFolder);
            this.Controls.Add(this.statusPanel);
            this.Controls.Add(this.btSearch);
            this.Controls.Add(this.txtContent);
            this.Controls.Add(this.listBox);
            this.Controls.Add(this.txtKeyword);
            this.Controls.Add(this.btSelect);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "CodeSeeker";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.statusPanel.ResumeLayout(false);
            this.statusPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btSelect;
        private System.Windows.Forms.TextBox txtKeyword;
        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.TextBox txtContent;
        private System.Windows.Forms.Button btSearch;
        private System.Windows.Forms.StatusStrip statusPanel;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.Button btFolder;
        private System.Windows.Forms.ToolStripStatusLabel statusSearched;
        private System.Windows.Forms.CheckBox chkSource;
        private System.Windows.Forms.CheckBox chkHeader;
        private System.Windows.Forms.CheckBox chkLastest;
    }
}

