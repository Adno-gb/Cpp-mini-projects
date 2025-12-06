using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tjribat
{
    public partial class Form2 : Form
    {
        string userChoice = "";
        public Form2()
        {
            InitializeComponent();
            
        }

        

        public void Form2_Load(object sender, EventArgs e)
        {
        
        }

   

        private void lbl1_Click(object sender, EventArgs e)
        {
            
        }

        private void button3_Click(object sender, EventArgs e)
        {

this.Close();
        }

        private void btn1_Click(object sender, EventArgs e)
        {
            Form1 frm = new Form1(userChoice);
            this.Hide();
            frm.ShowDialog();
            this.Show();
        }

        private void btn2_Click(object sender, EventArgs e)
        {
            Form3 frm = new Form3();

            this.Hide();
            if (frm.ShowDialog() == DialogResult.OK)
            {
               
                userChoice = frm.SelectedTag;

             
            }
            this.Show();
        }

        




    }


}
