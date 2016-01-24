using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Projekt_ActiveX
{
    // identyfikator globalnie unikatowy - guid , można wygenerować z Tools > Create GUID
    //InterfaceType - typ interfejsu
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    //guidy muszą być różne
    [Guid("713F2503-8ADB-48C6-87C6-6219029D6599")]
    public interface IMojaKontrolka
    {
        void show();        
    }
}
