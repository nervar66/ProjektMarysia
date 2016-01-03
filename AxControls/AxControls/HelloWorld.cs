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
    [Guid("1FC0D50A-4803-4f97-94FB-2F41717F558D")]
    [ProgId("AxControls.HelloWorld")]
    [ComDefaultInterface(typeof(IHelloWorld))]
    public class HelloWorld : UserControl, IHelloWorld, IObjectSafety
    {
        #region IHelloWorld Members

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