using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tjribat.Properties;

namespace Tjribat
{
    public partial class Form3 : Form
    {
        public string SelectedTag { get; set; }
        public Form3()
        {
           
        InitializeComponent();
            
           
        }

       

       



        private void btn1_Click(object sender, EventArgs e)
        {
            
           





            this.SelectedTag = ((Button)sender).Tag.ToString();

          
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
   


        private void btn2_Click(object sender, EventArgs e)
        {

            this.SelectedTag = ((Button)sender).Tag.ToString();


            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void btn3_Click(object sender, EventArgs e)
        {
            this.SelectedTag = ((Button)sender).Tag.ToString();


            this.DialogResult = DialogResult.OK;
            this.Close();

        }

        private void btn1_MouseHover(object sender, EventArgs e)
        {
            this.BackgroundImage = Properties.Resources._718WfE_UQ2L__AC_SL1200_;
        }

        private void btn2_MouseHover(object sender, EventArgs e)
        {
            this.BackgroundImage = Properties.Resources.pngtree_frozen_wonderland_a_cinematic_theme_with_ice_snow_and_blue_background_picture_image_7421422;
        }

        private void btn3_MouseHover(object sender, EventArgs e)
        {
            this.BackgroundImage = Properties.Resources.under_the_sea1;
        }

       

        private void Form3_MouseEnter(object sender, EventArgs e)
        {
            this.BackgroundImage = Properties.Resources.tic_tac_toe_7737546_1280;
        }

        private void btn4_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }

}
