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
            this.txt_train_today = new System.Windows.Forms.TextBox();
            this.txt_output_today = new System.Windows.Forms.TextBox();
            this.txt_start_today = new System.Windows.Forms.TextBox();
            this.txt_end_today = new System.Windows.Forms.TextBox();
            this.txt_train_next = new System.Windows.Forms.TextBox();
            this.txt_output_next = new System.Windows.Forms.TextBox();
            this.txt_start_next = new System.Windows.Forms.TextBox();
            this.txt_end_next = new System.Windows.Forms.TextBox();
            this.txt_status_next = new System.Windows.Forms.TextBox();
            this.txt_process_next = new System.Windows.Forms.TextBox();
            this.txt_status_today = new System.Windows.Forms.TextBox();
            this.txt_process_today = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txt_output_path = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btGen
            // 
            this.btGen.Location = new System.Drawing.Point(251, 603);
            this.btGen.Name = "btGen";
            this.btGen.Size = new System.Drawing.Size(504, 60);
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
            this.txt_header.Name = "txt_header";
            this.txt_header.Size = new System.Drawing.Size(740, 20);
            this.txt_header.TabIndex = 9;
            // 
            // txt_train_today
            // 
            this.txt_train_today.Location = new System.Drawing.Point(108, 113);
            this.txt_train_today.Name = "txt_train_today";
            this.txt_train_today.Size = new System.Drawing.Size(647, 20);
            this.txt_train_today.TabIndex = 10;
            // 
            // txt_output_today
            // 
            this.txt_output_today.Location = new System.Drawing.Point(108, 139);
            this.txt_output_today.Name = "txt_output_today";
            this.txt_output_today.Size = new System.Drawing.Size(647, 20);
            this.txt_output_today.TabIndex = 11;
            // 
            // txt_start_today
            // 
            this.txt_start_today.Location = new System.Drawing.Point(108, 165);
            this.txt_start_today.Name = "txt_start_today";
            this.txt_start_today.Size = new System.Drawing.Size(647, 20);
            this.txt_start_today.TabIndex = 12;
            // 
            // txt_end_today
            // 
            this.txt_end_today.Location = new System.Drawing.Point(108, 191);
            this.txt_end_today.Name = "txt_end_today";
            this.txt_end_today.Size = new System.Drawing.Size(647, 20);
            this.txt_end_today.TabIndex = 13;
            // 
            // txt_train_next
            // 
            this.txt_train_next.Location = new System.Drawing.Point(108, 387);
            this.txt_train_next.Name = "txt_train_next";
            this.txt_train_next.Size = new System.Drawing.Size(647, 20);
            this.txt_train_next.TabIndex = 14;
            // 
            // txt_output_next
            // 
            this.txt_output_next.Location = new System.Drawing.Point(108, 413);
            this.txt_output_next.Name = "txt_output_next";
            this.txt_output_next.Size = new System.Drawing.Size(647, 20);
            this.txt_output_next.TabIndex = 15;
            // 
            // txt_start_next
            // 
            this.txt_start_next.Location = new System.Drawing.Point(108, 439);
            this.txt_start_next.Name = "txt_start_next";
            this.txt_start_next.Size = new System.Drawing.Size(647, 20);
            this.txt_start_next.TabIndex = 16;
            // 
            // txt_end_next
            // 
            this.txt_end_next.Location = new System.Drawing.Point(108, 465);
            this.txt_end_next.Name = "txt_end_next";
            this.txt_end_next.Size = new System.Drawing.Size(647, 20);
            this.txt_end_next.TabIndex = 17;
            // 
            // txt_status_next
            // 
            this.txt_status_next.Location = new System.Drawing.Point(108, 491);
            this.txt_status_next.Name = "txt_status_next";
            this.txt_status_next.Size = new System.Drawing.Size(647, 20);
            this.txt_status_next.TabIndex = 18;
            // 
            // txt_process_next
            // 
            this.txt_process_next.Location = new System.Drawing.Point(108, 517);
            this.txt_process_next.Name = "txt_process_next";
            this.txt_process_next.Size = new System.Drawing.Size(647, 20);
            this.txt_process_next.TabIndex = 19;
            // 
            // txt_status_today
            // 
            this.txt_status_today.Location = new System.Drawing.Point(108, 217);
            this.txt_status_today.Name = "txt_status_today";
            this.txt_status_today.Size = new System.Drawing.Size(647, 20);
            this.txt_status_today.TabIndex = 20;
            // 
            // txt_process_today
            // 
            this.txt_process_today.Location = new System.Drawing.Point(108, 243);
            this.txt_process_today.Name = "txt_process_today";
            this.txt_process_today.Size = new System.Drawing.Size(647, 20);
            this.txt_process_today.TabIndex = 21;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(248, 563);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 22;
            this.label1.Text = "Save at";
            // 
            // txt_output_path
            // 
            this.txt_output_path.Location = new System.Drawing.Point(298, 560);
            this.txt_output_path.Name = "txt_output_path";
            this.txt_output_path.Size = new System.Drawing.Size(457, 20);
            this.txt_output_path.TabIndex = 23;
            this.txt_output_path.Text = "D:/output.txt";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(789, 675);
            this.Controls.Add(this.txt_output_path);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_process_today);
            this.Controls.Add(this.txt_status_today);
            this.Controls.Add(this.txt_process_next);
            this.Controls.Add(this.txt_status_next);
            this.Controls.Add(this.txt_end_next);
            this.Controls.Add(this.txt_start_next);
            this.Controls.Add(this.txt_output_next);
            this.Controls.Add(this.txt_train_next);
            this.Controls.Add(this.txt_end_today);
            this.Controls.Add(this.txt_start_today);
            this.Controls.Add(this.txt_output_today);
            this.Controls.Add(this.txt_train_today);
            this.Controls.Add(this.txt_header);
            this.Controls.Add(this.LB_Main);
            this.Controls.Add(this.btGen);
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
        private System.Windows.Forms.TextBox txt_train_today;
        private System.Windows.Forms.TextBox txt_output_today;
        private System.Windows.Forms.TextBox txt_start_today;
        private System.Windows.Forms.TextBox txt_end_today;
        private System.Windows.Forms.TextBox txt_train_next;
        private System.Windows.Forms.TextBox txt_output_next;
        private System.Windows.Forms.TextBox txt_start_next;
        private System.Windows.Forms.TextBox txt_end_next;
        private System.Windows.Forms.TextBox txt_status_next;
        private System.Windows.Forms.TextBox txt_process_next;
        private System.Windows.Forms.TextBox txt_status_today;
        private System.Windows.Forms.TextBox txt_process_today;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txt_output_path;
    }
}

