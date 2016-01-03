using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing;

namespace AxZaliczenie
{
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    [Guid("1FC0D50A-4803-4f97-94FB-2F41717F558D")]
    [ProgId("AxZaliczenie.PoleTekstowe")]
    [ComDefaultInterface(typeof(IPoleTekstowe))]
    public class PoleTekstowe : TextBox, IObjectSafety
    {
        bool znak = true;

        public enum ObjectSafetyOptions
        {
            INTERFACESAFE_FOR_UNTRUSTED_CALLER = 0x00000001,
            INTERFACESAFE_FOR_UNTRUSTED_DATA = 0x00000002,
            INTERFACE_USES_DISPEX = 0x00000004,
            INTERFACE_USES_SECURITY_MANAGER = 0x00000008
        };

        public int GetInterfaceSafetyOptions(ref Guid riid, out int pdwSupportedOptions, out int pdwEnabledOptions)
        {
            ObjectSafetyOptions m_options = ObjectSafetyOptions.INTERFACESAFE_FOR_UNTRUSTED_CALLER | ObjectSafetyOptions.INTERFACESAFE_FOR_UNTRUSTED_DATA;
            pdwSupportedOptions = (int)m_options;
            pdwEnabledOptions = (int)m_options;
            return 0;
        }

        public int SetInterfaceSafetyOptions(ref Guid riid, int dwOptionSetMask, int dwEnabledOptions)
        {
            return 0;
        }

        private new void KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '-' && this.SelectionStart != 0)
            {
                e.Handled = true;
                znak = false;
            }
            else
            {
                znak = true;
            }

            if (char.IsDigit(e.KeyChar) || e.KeyChar == '-' || e.KeyChar == (char)Keys.Back)
            {
                base.OnKeyPress(e);
            }
            else
            {
                e.Handled = true;
            }
        }

        private new void TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (double.Parse(this.Text) < 0)
                {
                    this.BackColor = Color.FromArgb(220, 20, 60);//jeśli ujemna na czerwono
                }
                else
                {
                    this.BackColor = Color.FromArgb(25, 165, 111);//jeśli dodatnia na zielono
                }
            }
            catch
            {
                this.BackColor = SystemColors.ControlText;
            }
        }

    }
}


