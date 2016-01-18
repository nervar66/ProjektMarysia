namespace Projekt_ActiveX_Łukasik
{
    partial class CSActiveXCtrl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.PoleTekstowe = new MyTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // PoleTekstowe
            // 
            this.PoleTekstowe.Location = new System.Drawing.Point(28, 26);
            this.PoleTekstowe.Name = "PoleTekstowe";
            this.PoleTekstowe.Size = new System.Drawing.Size(123, 20);
            this.PoleTekstowe.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label1.Location = new System.Drawing.Point(25, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Wpisz liczbe";
            // 
            // CSActiveXCtrl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PoleTekstowe);
            this.Name = "CSActiveXCtrl";
            this.Size = new System.Drawing.Size(186, 49);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MyTextBox PoleTekstowe;
        private System.Windows.Forms.Label label1;
    }
}
