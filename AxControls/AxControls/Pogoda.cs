using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Net;
using System.IO;

namespace AxControls
{
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    [Guid("25A70C0C-D69B-1267-2052-4031D0B1E1B7")]
    [ProgId("AxControls.Pogoda")]
    [ComDefaultInterface(typeof(IPogoda))]
    class Pogoda : UserControl, IPogoda, IObjectSafety
    {       
        #region IPogoda Members

        public string pobierz_dane_pogodowe()
        {
            string url = "http://api.wunderground.com/api/1581cc901bf0ed58/alerts/q/Poland/Czestochowa.json";
            System.Console.WriteLine("Pobieranie danych");
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            System.Console.WriteLine("Zapytanie");
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            System.Console.WriteLine("Odebranie");
            Stream resStream = response.GetResponseStream();
            System.Console.WriteLine("Zapis");
            return "pobrano";
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
