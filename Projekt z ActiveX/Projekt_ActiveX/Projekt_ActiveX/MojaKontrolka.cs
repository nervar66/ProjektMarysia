using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Drawing;

namespace Projekt_ActiveX
{

    [ClassInterface(ClassInterfaceType.None)]
    //guidy muszą być różne
    [Guid("58ED5856-C818-4923-A7EA-0DF6F4998AFC")]
    [ProgId("Kontrolka.MojaKontrolka")]
    public partial class MojaKontrolka : TextBox, IMojaKontrolka
    {

        public void show()
        {
            Console.WriteLine("I launch scripts for a living.");
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
