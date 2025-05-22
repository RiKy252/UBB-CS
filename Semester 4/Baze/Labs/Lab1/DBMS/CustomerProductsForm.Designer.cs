namespace DBMS
{
    partial class CustomerProductsForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.checkedListBoxProducts = new System.Windows.Forms.CheckedListBox();
            this.btnAssignProducts = new System.Windows.Forms.Button();
            this.txtCustomerName = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // checkedListBoxProducts
            // 
            this.checkedListBoxProducts.FormattingEnabled = true;
            this.checkedListBoxProducts.Location = new System.Drawing.Point(462, 12);
            this.checkedListBoxProducts.Name = "checkedListBoxProducts";
            this.checkedListBoxProducts.Size = new System.Drawing.Size(400, 599);
            this.checkedListBoxProducts.TabIndex = 1;
            this.checkedListBoxProducts.SelectedIndexChanged += new System.EventHandler(this.checkedListBox1_SelectedIndexChanged);
            // 
            // btnAssignProducts
            // 
            this.btnAssignProducts.Location = new System.Drawing.Point(462, 618);
            this.btnAssignProducts.Name = "btnAssignProducts";
            this.btnAssignProducts.Size = new System.Drawing.Size(400, 23);
            this.btnAssignProducts.TabIndex = 2;
            this.btnAssignProducts.Text = "Assign products";
            this.btnAssignProducts.UseVisualStyleBackColor = true;
            this.btnAssignProducts.Click += new System.EventHandler(this.btnAssignProducts_Click);
            // 
            // txtCustomerName
            // 
            this.txtCustomerName.Location = new System.Drawing.Point(13, 13);
            this.txtCustomerName.Name = "txtCustomerName";
            this.txtCustomerName.Size = new System.Drawing.Size(430, 22);
            this.txtCustomerName.TabIndex = 3;
            // 
            // CustomerProductsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1092, 727);
            this.Controls.Add(this.txtCustomerName);
            this.Controls.Add(this.btnAssignProducts);
            this.Controls.Add(this.checkedListBoxProducts);
            this.Name = "CustomerProductsForm";
            this.Text = "CustomerProductsForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.CheckedListBox checkedListBoxProducts;
        private System.Windows.Forms.Button btnAssignProducts;
        private System.Windows.Forms.TextBox txtCustomerName;
    }
}