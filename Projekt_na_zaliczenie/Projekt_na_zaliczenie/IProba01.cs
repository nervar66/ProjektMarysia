using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Projekt_na_zaliczenie
{
    [ComVisible(true)] 
    //sprawia, że interfejs jest widoczny dla COM. 
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    //ustala typ interfejsu na Dual
    [Guid("41E85D5D-C57A-4386-B722-4031D0B1E1B7")]
    //określenie GUID – identyfikator obiektow między innymi w systemie Windows lub wszędzie, 
    //gdzie potrzebny jest unikatowy identyfikator.
    public interface IProba01
    {
        string GetText();
    }
}