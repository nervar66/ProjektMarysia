using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Projekt_na_zaliczenie
{
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    //wskazuje, że nie jest generowany interfejs klasy dla tej klasy
    [Guid("1FC0D50A-4803-4f97-94FB-2F41717F558D")]
    [ProgId("AxControls.Proba01")]
    //identyfikator "przyjazny dla użytkownika",
    //ktory użyjemy poźniej z JavaScript w chwili wszczęcia kontroli
    [ComDefaultInterface(typeof(IProba01))]
    //ustawia IProba01 jako domyślny interfejs, ktory będzie wystawiony na COM
    public class Proba01 : UserControl, IProba01
    {
        #region IProba01 Members

        public string GetText()
        {
            return "Hello ActiveX World!";
        }

        #endregion

        #region IObjectSafety Members

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

        #endregion
    }
}
