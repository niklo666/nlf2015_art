using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace light_test_app
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void funnelColorButton_Click(object sender, EventArgs e)
		{
			ColorDialog dlg = new ColorDialog();

			DialogResult result = dlg.ShowDialog();

			if (result == System.Windows.Forms.DialogResult.OK)
			{
				funnelColorPictureBox.BackColor = dlg.Color;
			}
		}

		private void update_color()
		{
			int dimmed_red = 0;
			int dimmed_green = 0;
			int dimmed_blue = 0;

			if (dimTrackBar.Value > 0)
			{
				dimmed_red		= (int)((redTrackBar.Value)*(dimTrackBar.Value/255.0));
				dimmed_green = (int)(( greenTrackBar.Value)*(dimTrackBar.Value / 255.0));
				dimmed_blue = (int)((blueTrackBar.Value)*(dimTrackBar.Value / 255.0));
			}
			try
			{
				funnelColorPictureBox.BackColor = Color.FromArgb(dimmed_red, dimmed_green, dimmed_blue);
			}
			catch (Exception e)
			{ 
			}
		}

		private void redTrackBar_Scroll(object sender, EventArgs e)
		{
			update_color();
		}

		private void greenTrackBar_Scroll(object sender, EventArgs e)
		{
			update_color();
		}

		private void blueTrackBar_Scroll(object sender, EventArgs e)
		{
			update_color();
		}

		private void dimTrackBar_Scroll(object sender, EventArgs e)
		{
			update_color();
		}

		private void patternComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch (patternComboBox.SelectedText)
			{ 
				case "Static":
					break;
				case "Dimmer":
					break;
				case "Random":
					break;
			}
		}

		private void paletteComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (paletteComboBox.SelectedText == "None")
			{
				funnelColorPictureBox.Enabled = true;
				redTrackBar.Enabled = true;
				greenTrackBar.Enabled = true;
				blueTrackBar.Enabled = true;

				patternComboBox.Text = "Static";
			}
			else 
			{
				funnelColorPictureBox.Enabled = false;
				redTrackBar.Enabled = false;
				greenTrackBar.Enabled = false;
				blueTrackBar.Enabled = false;
				patternComboBox.Text = "Random";
			}
			
		}

	


	}
}
