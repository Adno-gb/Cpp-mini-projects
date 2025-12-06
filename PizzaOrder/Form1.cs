using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics.Eventing.Reader;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Awl
{
    public partial class Form1 : Form
    {
        int basePrice = 0;   
        int extraPrice = 0;  


        public Form1()
        {
            InitializeComponent();
        }

        private void UpdateExtras()
        {
            extraPrice = 0;

            if (checkBox1.Checked)
                extraPrice += 10;

            if (checkBox2.Checked)
                extraPrice += 10;

            if (checkBox3.Checked)
                extraPrice += 10;

            if (checkBox4.Checked)
                extraPrice += 10;
        }

        private void UpdatePrice()
        {
            UpdateExtras();
            int total = basePrice + extraPrice;
            label10.Text = total.ToString() + " $";
        }



        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
if (radioButton2.Checked)
            {
                label6.Text = "Meduim";

                basePrice = 50;
                UpdatePrice();

            }
        }

   

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
            {
                label6.Text = "Small";
                basePrice = 20;
                UpdatePrice();
            }
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton3.Checked)
            {
                label6.Text = "Larg";
                basePrice = 100;
                UpdatePrice();
            }
        }

        private void radioButton9_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton9.Checked)
            {

                label11.Text = "Thin";
               
            }
        }

        private void radioButton7_CheckedChanged(object sender, EventArgs e)
        {

            if (radioButton7.Checked)
            {

                label11.Text = "Think";

            }


        }

        private void UpdateLabel()
        {
            string text = "";
            
            if (checkBox2.Checked)
            {
                text += "Olives";
               
            }
          
            if (checkBox1.Checked)
            {
                if (text != "") text += " + ";
                text += "Onion";
                
            }
          
            if (checkBox3.Checked)
            {
                if (text != "") text += " + ";
                text += "Tomatoes";
               
            }
          
            if (checkBox4.Checked)
            {
                if (text != "") text += " + ";
                text += "Chees";
              
                
            }

          
            label8.Text = text;
        }



        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            UpdateLabel();
            UpdatePrice();

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            UpdateLabel();
            UpdatePrice();
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            UpdateLabel();
            UpdatePrice();
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            UpdateLabel();
            UpdatePrice();
        }

        private void radioButton8_CheckedChanged(object sender, EventArgs e)
        {
           
            if (radioButton8.Checked)
            {

                label9.Text = "Eat In";
               
            }
        }

        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton6.Checked)
            {

                label9.Text = "Take Out";
               
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Ok Or Cancel", "Confirm", MessageBoxButtons.OKCancel,MessageBoxIcon.Question) == DialogResult.OK)
            {

                MessageBox.Show("Bye");


            }
            

            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            radioButton1.Checked = false;
            radioButton2.Checked = false;
radioButton3.Checked = false;
            radioButton6.Checked = false;
            radioButton7.Checked = false;
            radioButton8.Checked = false;
            radioButton9.Checked = false;
            checkBox1.Checked = false;
            checkBox2.Checked = false;
            checkBox3.Checked = false;
            checkBox4.Checked = false;
            label6.Text = "";
            label8.Text = "";
            label9.Text = "";
            label10.Text = "";
            label11.Text = "";
            basePrice = 0;
            extraPrice = 0;
        }

    }
}
