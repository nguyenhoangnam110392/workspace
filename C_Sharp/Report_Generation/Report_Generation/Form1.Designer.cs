namespace Report_Generation
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
            this.btGen = new System.Windows.Forms.Button();
            this.LB_Main = new System.Windows.Forms.Label();
            this.txt_header = new System.Windows.Forms.TextBox();
            this.txt_task = new System.Windows.Forms.TextBox();
            this.txt_start = new System.Windows.Forms.TextBox();
            this.txt_deadline = new System.Windows.Forms.TextBox();
            this.txt_process = new System.Windows.Forms.TextBox();
            this.txt_output_path = new System.Windows.Forms.TextBox();
            this.cb_status = new System.Windows.Forms.ComboBox();
            this.txt_objective = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btGen
            // 
            this.btGen.Cursor = System.Windows.Forms.Cursors.Default;
            this.btGen.Location = new System.Drawing.Point(15, 405);
            this.btGen.Name = "btGen";
            this.btGen.Size = new System.Drawing.Size(740, 60);
            this.btGen.TabIndex = 4;
            this.btGen.Text = "Generate";
            this.btGen.UseVisualStyleBackColor = true;
            this.btGen.Click += new System.EventHandler(this.btGen_Click);
            // 
            // LB_Main
            // 
            this.LB_Main.AutoSize = true;
            this.LB_Main.Location = new System.Drawing.Point(12, 9);
            this.LB_Main.Name = "LB_Main";
            this.LB_Main.Size = new System.Drawing.Size(30, 13);
            this.LB_Main.TabIndex = 8;
            this.LB_Main.Text = "Main";
            // 
            // txt_header
            // 
            this.txt_header.Location = new System.Drawing.Point(15, 40);
            this.txt_header.Multiline = true;
            this.txt_header.Name = "txt_header";
            this.txt_header.Size = new System.Drawing.Size(740, 122);
            this.txt_header.TabIndex = 9;
            // 
            // txt_task
            // 
            this.txt_task.Location = new System.Drawing.Point(108, 213);
            this.txt_task.Name = "txt_task";
            this.txt_task.Size = new System.Drawing.Size(647, 20);
            this.txt_task.TabIndex = 10;
            // 
            // txt_start
            // 
            this.txt_start.Location = new System.Drawing.Point(108, 265);
            this.txt_start.Name = "txt_start";
            this.txt_start.Size = new System.Drawing.Size(647, 20);
            this.txt_start.TabIndex = 12;
            // 
            // txt_deadline
            // 
            this.txt_deadline.Location = new System.Drawing.Point(108, 291);
            this.txt_deadline.Name = "txt_deadline";
            this.txt_deadline.Size = new System.Drawing.Size(647, 20);
            this.txt_deadline.TabIndex = 13;
            // 
            // txt_process
            // 
            this.txt_process.Location = new System.Drawing.Point(108, 343);
            this.txt_process.Name = "txt_process";
            this.txt_process.Size = new System.Drawing.Size(647, 20);
            this.txt_process.TabIndex = 21;
            // 
            // txt_output_path
            // 
            this.txt_output_path.Location = new System.Drawing.Point(108, 369);
            this.txt_output_path.Name = "txt_output_path";
            this.txt_output_path.Size = new System.Drawing.Size(647, 20);
            this.txt_output_path.TabIndex = 23;
            this.txt_output_path.Text = "report.txt";
            // 
            // cb_status
            // 
            this.cb_status.FormattingEnabled = true;
            this.cb_status.Items.AddRange(new object[] {
            "Pending",
            "On Going",
            "Done"});
            this.cb_status.Location = new System.Drawing.Point(108, 316);
            this.cb_status.Name = "cb_status";
            this.cb_status.Size = new System.Drawing.Size(121, 21);
            this.cb_status.TabIndex = 24;
            // 
            // txt_objective
            // 
            this.txt_objective.Location = new System.Drawing.Point(108, 239);
            this.txt_objective.Name = "txt_objective";
            this.txt_objective.Size = new System.Drawing.Size(647, 20);
            this.txt_objective.TabIndex = 25;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(772, 475);
            this.Controls.Add(this.txt_objective);
            this.Controls.Add(this.cb_status);
            this.Controls.Add(this.txt_output_path);
            this.Controls.Add(this.txt_process);
            this.Controls.Add(this.txt_deadline);
            this.Controls.Add(this.txt_start);
            this.Controls.Add(this.txt_task);
            this.Controls.Add(this.txt_header);
            this.Controls.Add(this.LB_Main);
            this.Controls.Add(this.btGen);
            this.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Report Generation";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button btGen;
        private System.Windows.Forms.Label LB_Main;
        private System.Windows.Forms.TextBox txt_header;
        private System.Windows.Forms.TextBox txt_task;
        private System.Windows.Forms.TextBox txt_start;
        private System.Windows.Forms.TextBox txt_deadline;
        private System.Windows.Forms.TextBox txt_process;
        private System.Windows.Forms.TextBox txt_output_path;
        private System.Windows.Forms.ComboBox cb_status;
        private System.Windows.Forms.TextBox txt_objective;
    }
}

