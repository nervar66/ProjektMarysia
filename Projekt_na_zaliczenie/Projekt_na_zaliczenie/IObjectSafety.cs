using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Projekt_na_zaliczenie
{
    [ComImport()]
    // IObjectSafety jest interfejsem dziedziczonym,
    //więc musimy go przedefiniować do wykorzystania w manadżerze .NET
    //Odbywa się to za pomocą atrybutu ComImport ()
    [Guid("CB5BDC81-93C1-11CF-8F20-00805F2CD064")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    //określa typ interfejsu COM
    interface IObjectSafety
    {
        [PreserveSig()]
        int GetInterfaceSafetyOptions(ref Guid riid, out int pdwSupportedOptions, out int pdwEnabledOptions);

        [PreserveSig()]
        int SetInterfaceSafetyOptions(ref Guid riid, int dwOptionSetMask, int dwEnabledOptions);
    }
}