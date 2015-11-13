namespace light_test_app
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
			this.funnelGroupBox = new System.Windows.Forms.GroupBox();
			this.updateButton = new System.Windows.Forms.Button();
			this.autoUpdateCheckBox = new System.Windows.Forms.CheckBox();
			this.label6 = new System.Windows.Forms.Label();
			this.paletteComboBox = new System.Windows.Forms.ComboBox();
			this.label5 = new System.Windows.Forms.Label();
			this.patternComboBox = new System.Windows.Forms.ComboBox();
			this.label4 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.dimTrackBar = new System.Windows.Forms.TrackBar();
			this.blueTrackBar = new System.Windows.Forms.TrackBar();
			this.greenTrackBar = new System.Windows.Forms.TrackBar();
			this.redTrackBar = new System.Windows.Forms.TrackBar();
			this.funnelColorPictureBox = new System.Windows.Forms.PictureBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.funnelGroupBox.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dimTrackBar)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.blueTrackBar)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.greenTrackBar)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.redTrackBar)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.funnelColorPictureBox)).BeginInit();
			this.SuspendLayout();
			// 
			// funnelGroupBox
			// 
			this.funnelGroupBox.Controls.Add(this.updateButton);
			this.funnelGroupBox.Controls.Add(this.autoUpdateCheckBox);
			this.funnelGroupBox.Controls.Add(this.label6);
			this.funnelGroupBox.Controls.Add(this.paletteComboBox);
			this.funnelGroupBox.Controls.Add(this.label5);
			this.funnelGroupBox.Controls.Add(this.patternComboBox);
			this.funnelGroupBox.Controls.Add(this.label4);
			this.funnelGroupBox.Controls.Add(this.label3);
			this.funnelGroupBox.Controls.Add(this.label2);
			this.funnelGroupBox.Controls.Add(this.label1);
			this.funnelGroupBox.Controls.Add(this.dimTrackBar);
			this.funnelGroupBox.Controls.Add(this.blueTrackBar);
			this.funnelGroupBox.Controls.Add(this.greenTrackBar);
			this.funnelGroupBox.Controls.Add(this.redTrackBar);
			this.funnelGroupBox.Controls.Add(this.funnelColorPictureBox);
			this.funnelGroupBox.Location = new System.Drawing.Point(12, 12);
			this.funnelGroupBox.Name = "funnelGroupBox";
			this.funnelGroupBox.Size = new System.Drawing.Size(343, 333);
			this.funnelGroupBox.TabIndex = 0;
			this.funnelGroupBox.TabStop = false;
			this.funnelGroupBox.Text = "Skorsten";
			// 
			// updateButton
			// 
			this.updateButton.Location = new System.Drawing.Point(237, 187);
			this.updateButton.Name = "updateButton";
			this.updateButton.Size = new System.Drawing.Size(75, 23);
			this.updateButton.TabIndex = 13;
			this.updateButton.Text = "Update";
			this.updateButton.UseVisualStyleBackColor = true;
			// 
			// autoUpdateCheckBox
			// 
			this.autoUpdateCheckBox.AutoSize = true;
			this.autoUpdateCheckBox.Location = new System.Drawing.Point(237, 161);
			this.autoUpdateCheckBox.Name = "autoUpdateCheckBox";
			this.autoUpdateCheckBox.Size = new System.Drawing.Size(86, 17);
			this.autoUpdateCheckBox.TabIndex = 12;
			this.autoUpdateCheckBox.Text = "Auto Update";
			this.autoUpdateCheckBox.UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(16, 192);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(40, 13);
			this.label6.TabIndex = 11;
			this.label6.Text = "Palette";
			// 
			// paletteComboBox
			// 
			this.paletteComboBox.FormattingEnabled = true;
			this.paletteComboBox.Items.AddRange(new object[] {
            "None",
            "Palette 1",
            "Palette 2",
            "Palette 3",
            "Palette 4",
            "Palette 5"});
			this.paletteComboBox.Location = new System.Drawing.Point(84, 189);
			this.paletteComboBox.Name = "paletteComboBox";
			this.paletteComboBox.Size = new System.Drawing.Size(100, 21);
			this.paletteComboBox.TabIndex = 10;
			this.paletteComboBox.SelectedIndexChanged += new System.EventHandler(this.paletteComboBox_SelectedIndexChanged);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(16, 165);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(41, 13);
			this.label5.TabIndex = 9;
			this.label5.Text = "Pattern";
			// 
			// patternComboBox
			// 
			this.patternComboBox.FormattingEnabled = true;
			this.patternComboBox.Items.AddRange(new object[] {
            "Static",
            "Dim",
            "Random"});
			this.patternComboBox.Location = new System.Drawing.Point(84, 162);
			this.patternComboBox.Name = "patternComboBox";
			this.patternComboBox.Size = new System.Drawing.Size(100, 21);
			this.patternComboBox.TabIndex = 8;
			this.patternComboBox.SelectedIndexChanged += new System.EventHandler(this.patternComboBox_SelectedIndexChanged);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label4.Location = new System.Drawing.Point(289, 21);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(28, 13);
			this.label4.TabIndex = 7;
			this.label4.Text = "Dim";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label3.Location = new System.Drawing.Point(251, 21);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(15, 13);
			this.label3.TabIndex = 6;
			this.label3.Text = "B";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(202, 21);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(16, 13);
			this.label2.TabIndex = 5;
			this.label2.Text = "G";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(147, 21);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(16, 13);
			this.label1.TabIndex = 1;
			this.label1.Text = "R";
			// 
			// dimTrackBar
			// 
			this.dimTrackBar.Location = new System.Drawing.Point(292, 37);
			this.dimTrackBar.Maximum = 255;
			this.dimTrackBar.Name = "dimTrackBar";
			this.dimTrackBar.Orientation = System.Windows.Forms.Orientation.Vertical;
			this.dimTrackBar.Size = new System.Drawing.Size(45, 104);
			this.dimTrackBar.TabIndex = 4;
			this.dimTrackBar.Scroll += new System.EventHandler(this.dimTrackBar_Scroll);
			// 
			// blueTrackBar
			// 
			this.blueTrackBar.Location = new System.Drawing.Point(241, 37);
			this.blueTrackBar.Maximum = 255;
			this.blueTrackBar.Name = "blueTrackBar";
			this.blueTrackBar.Orientation = System.Windows.Forms.Orientation.Vertical;
			this.blueTrackBar.Size = new System.Drawing.Size(45, 104);
			this.blueTrackBar.TabIndex = 3;
			this.blueTrackBar.Scroll += new System.EventHandler(this.blueTrackBar_Scroll);
			// 
			// greenTrackBar
			// 
			this.greenTrackBar.Location = new System.Drawing.Point(190, 37);
			this.greenTrackBar.Maximum = 255;
			this.greenTrackBar.Name = "greenTrackBar";
			this.greenTrackBar.Orientation = System.Windows.Forms.Orientation.Vertical;
			this.greenTrackBar.Size = new System.Drawing.Size(45, 104);
			this.greenTrackBar.TabIndex = 2;
			this.greenTrackBar.Scroll += new System.EventHandler(this.greenTrackBar_Scroll);
			// 
			// redTrackBar
			// 
			this.redTrackBar.Location = new System.Drawing.Point(139, 37);
			this.redTrackBar.Maximum = 255;
			this.redTrackBar.Name = "redTrackBar";
			this.redTrackBar.Orientation = System.Windows.Forms.Orientation.Vertical;
			this.redTrackBar.Size = new System.Drawing.Size(45, 104);
			this.redTrackBar.TabIndex = 1;
			this.redTrackBar.Scroll += new System.EventHandler(this.redTrackBar_Scroll);
			// 
			// funnelColorPictureBox
			// 
			this.funnelColorPictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.funnelColorPictureBox.Location = new System.Drawing.Point(19, 37);
			this.funnelColorPictureBox.Name = "funnelColorPictureBox";
			this.funnelColorPictureBox.Size = new System.Drawing.Size(108, 104);
			this.funnelColorPictureBox.TabIndex = 1;
			this.funnelColorPictureBox.TabStop = false;
			// 
			// groupBox1
			// 
			this.groupBox1.Location = new System.Drawing.Point(876, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(371, 241);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Paletter";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1259, 667);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.funnelGroupBox);
			this.Name = "Form1";
			this.Text = "Form1";
			this.funnelGroupBox.ResumeLayout(false);
			this.funnelGroupBox.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.dimTrackBar)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.blueTrackBar)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.greenTrackBar)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.redTrackBar)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.funnelColorPictureBox)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox funnelGroupBox;
		private System.Windows.Forms.PictureBox funnelColorPictureBox;
		private System.Windows.Forms.TrackBar redTrackBar;
		private System.Windows.Forms.TrackBar blueTrackBar;
		private System.Windows.Forms.TrackBar greenTrackBar;
		private System.Windows.Forms.TrackBar dimTrackBar;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.ComboBox patternComboBox;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.ComboBox paletteComboBox;
		private System.Windows.Forms.Button updateButton;
		private System.Windows.Forms.CheckBox autoUpdateCheckBox;
		private System.Windows.Forms.GroupBox groupBox1;
	}
}

