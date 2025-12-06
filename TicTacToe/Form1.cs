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
    public partial class Form1 : Form
    {
        stGameStatus GameStatus;
        enPlayer PlayerTurn;

        enum enPlayer
        {
            Player1,
            Player2
        }

        enum enWinner
        {
            Player1,
            Player2,
            Draw,
            GameInProgress
        }

        struct stGameStatus
        {
            public enWinner Winner;
            public bool GameOver;
            public short PlayCount;

        }

        public bool CheckValues(Button btn1, Button btn2, Button btn3)
        {
            if (btn1.Tag.ToString() != "?" && btn1.Tag.ToString() == btn2.Tag.ToString() && btn1.Tag.ToString() == btn3.Tag.ToString())
            {
                btn1.BackColor = Color.Green;
                btn2.BackColor = Color.Green;
                btn3.BackColor = Color.Green;

                if (btn1.Tag.ToString() == "X")
                {
                    GameStatus.Winner = enWinner.Player1;
                    GameStatus.GameOver = true;
                    EndGame();
                    return true;
                }
                else
                {
                    btn1.BackColor = Color.Red;
                    btn2.BackColor = Color.Red;
                    btn3.BackColor = Color.Red;
                    GameStatus.Winner = enWinner.Player2;
                    GameStatus.GameOver = true;
                    EndGame();
                    return true;
                }
            }
            GameStatus.GameOver = false;
            return false;
        }

        void EndGame()
        {
            lbl5.Text = "Game Over";
            switch (GameStatus.Winner)
            {

                case enWinner.Player1:

                    lbl5.Text = "Player 1";
                    lbl5.ForeColor = Color.Green;
                    break;

                case enWinner.Player2:

                    lbl5.Text = "Player 2";
                    lbl5.ForeColor = Color.Red;
                    break;

                default:

                    lbl5.Text = "Draw";
                    break;

            }
            if(lbl5.Text == "Player 1")
            {
            MessageBox.Show("Player1", "Win", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Player2", "Win", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        public void CheckWinner()
        {
            if (CheckValues(button1, btn2, btn3))
                return;
            if (CheckValues(btn4, btn5, btn6))
                return;
            if (CheckValues(btn7, btn8, btn9))
                return;
            if (CheckValues(button1, btn4, btn7))
                return;
            if (CheckValues(btn2, btn5, btn8))
                return;
            if (CheckValues(btn3, btn6, btn9))
                return;
            if (CheckValues(button1, btn5, btn9))
                return;
            if (CheckValues(btn3, btn5, btn7))
                return;
        }

        public void ChangeImage(Button btn)
        {
            if (btn.Tag.ToString() == "?")
            {
                switch (PlayerTurn)
                {
                    case enPlayer.Player1:
                        btn.Image = Resources.X;
                        PlayerTurn = enPlayer.Player2;
                        lbl3.Text = "Player 2";
                        GameStatus.PlayCount++;
                        btn.Tag = "X";
                        CheckWinner();
                        break;
                    case enPlayer.Player2:
                        btn.Image = Resources.O;
                        PlayerTurn = enPlayer.Player1;
                        lbl3.Text = "Player 1";
                        GameStatus.PlayCount++;
                        btn.Tag = "O";
                        CheckWinner();
                        break;
                }
            }
            else
            {
             MessageBox.Show("Wrong Choice", "Worng", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (GameStatus.PlayCount == 9)
            {
                GameStatus.GameOver = true;
                GameStatus.Winner = enWinner.Draw;
                EndGame();
            }
        }

        public Form1( string tagReceived)
        {
            ChangeBackground(tagReceived);
            InitializeComponent();
        }

        private void From1_paint(object sender, PaintEventArgs e)
        {
            Color Whait = Color.White;
            Pen pen = new Pen(Whait);
            pen.Width = 10;
            pen.StartCap = System.Drawing.Drawing2D.LineCap.Round;
            pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
            e.Graphics.DrawLine(pen, 650, 150, 650, 630);
            e.Graphics.DrawLine(pen, 820, 150, 820, 630);
            e.Graphics.DrawLine(pen, 500, 300, 970, 300);
            e.Graphics.DrawLine(pen, 500, 450, 970, 450);
        }
     
        private void ChangeBackground(string tag)
        {
            if (tag == "Space")
            { 
                this.BackgroundImage = Properties.Resources._718WfE_UQ2L__AC_SL1200_;
            }
            else if (tag == "Ice")
            {
                this.BackgroundImage = Properties.Resources.pngtree_frozen_wonderland_a_cinematic_theme_with_ice_snow_and_blue_background_picture_image_7421422;
            }
             else if (tag == "Sea")
            {
                this.BackgroundImage = Properties.Resources.under_the_sea1;
            }
        }
      
        private void From1_load(object sender, EventArgs e)
        {

        }

        private void btn1_Click(object sender, EventArgs e)
        {
            RestartGame();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn2_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn3_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn4_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn5_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn6_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn7_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn8_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void btn9_Click(object sender, EventArgs e)
        {
            ChangeImage((Button)sender);
        }

        private void RestButton(Button btn)
        {
            btn.Image = Resources.question_mark_96;
            btn.Tag = "?";
            btn.BackColor = Color.Transparent;

        }

        private void RestartGame()
        {
            RestButton(button1);
            RestButton(btn2);
            RestButton(btn3);
            RestButton(btn4);
            RestButton(btn5);
            RestButton(btn6);
            RestButton(btn7);
            RestButton(btn8);
            RestButton(btn9);
            PlayerTurn = enPlayer.Player1;
            lbl3.Text = "Player 1";
            GameStatus.PlayCount = 0;
            GameStatus.GameOver = false;
            GameStatus.Winner = enWinner.GameInProgress;
            lbl5.Text = "In Progress";
            lbl5.ForeColor = Color.Yellow;
        }
    }
}
