using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
 
namespace AxControls
{
    [ComVisible(true)]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    [Guid("25A70C0C-D69B-1267-2052-4031D0B1E1B7")]
    public interface IPogoda
    {     
        string pobierz_dane_pogodowe();
    }
}