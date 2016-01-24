#region Using directives
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using System.Reflection;
using System.Security.Permissions;
#endregion

namespace Projekt_ActiveX_Łukasik
{
    [Guid("FCF17FB6-3293-4462-BDF4-DA12EC092A51")]
    public interface AxCSActiveXCtrl
    {
        #region Właściwości

        bool Visible { get; set; }          // Typical control property
        bool Enabled { get; set; }          // Typical control property
        int ForeColor { get; set; }         // Typical control property
        int BackColor { get; set; }         // Typical control property
        float FloatProperty { get; set; }   // Custom property

        #endregion

        #region Metody

        void Refresh();                     // Typical control method
        string HelloWorld();                // Custom method

        #endregion
    }

    [Guid("1CF448D3-EE0D-4326-BAB7-00C0C3E09B0E")]
    [InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface AxCSActiveXCtrlEvents
    {
        #region Zdarzenia

        // Must explicitly define DISPID for each event, otherwise, the 
        // callback address cannot be found when the event is fired.
        [DispId(1)]
        void Click();
        [DispId(2)]
        void FloatPropertyChanging(float NewValue, ref bool Cancel);

        #endregion
    }

    [ProgId("ProjektActiveX.MojaKontrolka")]
    [ClassInterface(ClassInterfaceType.None)]
    [ComSourceInterfaces(typeof(AxCSActiveXCtrlEvents))] 
    [Guid("A927C9B3-4D3B-47C2-8AFE-4A7F39EB6AA5")]
    public partial class CSActiveXCtrl : UserControl , AxCSActiveXCtrl
    {
        #region Rejestracja kontrolki ActiveX

        // These routines perform the additional COM registration needed by 
        // ActiveX controls

        [EditorBrowsable(EditorBrowsableState.Never)]
        [ComRegisterFunction()]
        public static void Register(Type t)
        {
            try
            {
                ActiveXCtrlHelper.RegasmRegisterControl(t);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message); // Log the error
                throw;  // Re-throw the exception
            }
        }

        [EditorBrowsable(EditorBrowsableState.Never)]
        [ComUnregisterFunction()]
        public static void Unregister(Type t)
        {
            try
            {
                ActiveXCtrlHelper.RegasmUnregisterControl(t);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message); // Log the error
                throw; // Re-throw the exception
            }
        }

        #endregion

        #region Inicjalizacja

        public CSActiveXCtrl()
        {
            InitializeComponent();
            
            // These functions are used to handle Tab-stops for the ActiveX 
            // control (including its child controls) when the control is 
            // hosted in a container.
            this.LostFocus += new EventHandler(CSActiveXCtrl_LostFocus);
            this.ControlAdded += new ControlEventHandler(
                CSActiveXCtrl_ControlAdded);

            // Raise custom Load event
            this.OnCreateControl();
        }

        // This event will hook up the necessary handlers
        void CSActiveXCtrl_ControlAdded(object sender, ControlEventArgs e)
        {
            // Register tab handler and focus-related event handlers for 
            // the control and its child controls.
            ActiveXCtrlHelper.WireUpHandlers(e.Control, ValidationHandler);
        }

        // Ensures that the Validating and Validated events fire properly
        internal void ValidationHandler(object sender, System.EventArgs e)
        {
            if (this.ContainsFocus) return;

            this.OnLeave(e); // Raise Leave event

            if (this.CausesValidation)
            {
                CancelEventArgs validationArgs = new CancelEventArgs();
                this.OnValidating(validationArgs);

                if (validationArgs.Cancel && this.ActiveControl != null)
                    this.ActiveControl.Focus();
                else
                    this.OnValidated(e); // Raise Validated event
            }
        }

        [SecurityPermission(SecurityAction.LinkDemand,
            Flags = SecurityPermissionFlag.UnmanagedCode)]
        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            const int WM_SETFOCUS = 0x7;
            const int WM_PARENTNOTIFY = 0x210;
            const int WM_DESTROY = 0x2;
            const int WM_LBUTTONDOWN = 0x201;
            const int WM_RBUTTONDOWN = 0x204;

            if (m.Msg == WM_SETFOCUS)
            {
                // Raise Enter event
                this.OnEnter(System.EventArgs.Empty);
            }
            else if (m.Msg == WM_PARENTNOTIFY && (
                m.WParam.ToInt32() == WM_LBUTTONDOWN ||
                m.WParam.ToInt32() == WM_RBUTTONDOWN))
            {
                if (!this.ContainsFocus)
                {
                    // Raise Enter event
                    this.OnEnter(System.EventArgs.Empty);
                }
            }
            else if (m.Msg == WM_DESTROY &&
                !this.IsDisposed && !this.Disposing)
            {
                // Used to ensure the cleanup of the control
                this.Dispose();
            }

            base.WndProc(ref m);
        }

        // Ensures that tabbing across the container and the .NET controls
        // works as expected
        void CSActiveXCtrl_LostFocus(object sender, EventArgs e)
        {
            ActiveXCtrlHelper.HandleFocus(this);
        }

        #endregion

        #region Właściwości

        public new int ForeColor
        {
            get { return ActiveXCtrlHelper.GetOleColorFromColor(base.ForeColor); }
            set { base.ForeColor = ActiveXCtrlHelper.GetColorFromOleColor(value); }
        }

        public new int BackColor
        {
            get { return ActiveXCtrlHelper.GetOleColorFromColor(base.BackColor); }
            set { base.BackColor = ActiveXCtrlHelper.GetColorFromOleColor(value); }
        }

        private float fField = 0;

        /// <summary>
        /// A custom property with both get and set accessor methods.
        /// </summary>
        public float FloatProperty
        {
            get { return this.fField; }
            set
            {
                bool cancel = false;
                // Raise the event FloatPropertyChanging
                if (null != FloatPropertyChanging)
                    FloatPropertyChanging(value, ref cancel);
                if (!cancel)
                {
                    this.fField = value;
                }
            }
        }

        #endregion
        
        #region Metody

        public string HelloWorld()
        {
            return "HelloWorld";
        }

        #endregion
        
        #region Zdarzenia

        // This section shows the examples of exposing a control's events.
        // Typically, you just need to
        // 1) Declare the event as you want it.
        // 2) Raise the event in the appropriate control event.

        [ComVisible(false)]
        public delegate void ClickEventHandler();
        public new event ClickEventHandler Click = null;
        void CSActiveXCtrl_Click(object sender, EventArgs e)
        {
            if (null != Click) Click(); // Raise the new Click event.
        }

        [ComVisible(false)]
        public delegate void FloatPropertyChangingEventHandler(float NewValue, ref bool Cancel);
        public event FloatPropertyChangingEventHandler FloatPropertyChanging = null;

        #endregion
    }

}
