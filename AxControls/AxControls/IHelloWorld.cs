using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
 
namespace AxControls
{
    [ComVisible(true)]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    [Guid("41E85D5D-C57A-4386-B722-4031D0B1E1B7")]
    public interface IHelloWorld
    {
        string GetText();
    }
}