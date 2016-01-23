using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ProjektActiveXLukasik
{
    class MyTextBox : TextBox
    {
        public MyTextBox() : base()
        {
        }

        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            if (e.KeyChar == '.')
                e.KeyChar = ',';

            if (e.KeyChar == ',' && this.Text.Contains(','))
                e.Handled = true;

            if ((e.KeyChar == '0' || e.KeyChar == ',') && this.SelectionStart == 0)
                e.Handled = true;

            if ((e.KeyChar == '0' || e.KeyChar == ',') && this.SelectionStart == 1 && this.Text.Contains('-'))
                e.Handled = true;

            if (e.KeyChar == '-' && this.SelectionStart != 0)
                e.Handled = true;

            if (char.IsDigit(e.KeyChar) || e.KeyChar == ',' || e.KeyChar == (char)Keys.Back || e.KeyChar == '-')
                base.OnKeyPress(e);
            else
                e.Handled = true;
        }

        protected override void OnTextChanged(EventArgs e)
        {
            if (this.Text.Length == 0)
            {
                BackColor = Color.White;
            }
            else
            {
                if (this.Text.Contains('-'))
                {
                    BackColor = Color.Red;
                }
                else
                {
                    BackColor = Color.Green;
                }
            }
        }
    }
}
