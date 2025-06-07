namespace DBMS
{
    partial class Form1
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
            this.allCategories = new System.Windows.Forms.DataGridView();
            this.productsGrid = new System.Windows.Forms.DataGridView();
            this.btnAddProduct = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.btnCustomerProducts = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.allCategories)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.productsGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // allCategories
            // 
            this.allCategories.AllowUserToAddRows = false;
            this.allCategories.AllowUserToDeleteRows = false;
            this.allCategories.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.allCategories.Location = new System.Drawing.Point(12, 12);
            this.allCategories.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.allCategories.Name = "allCategories";
            this.allCategories.ReadOnly = true;
            this.allCategories.RowHeadersWidth = 51;
            this.allCategories.RowTemplate.Height = 24;
            this.allCategories.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.allCategories.Size = new System.Drawing.Size(341, 380);
            this.allCategories.TabIndex = 1;
            this.allCategories.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.allCategories_CellContentClick);
            // 
            // productsGrid
            // 
            this.productsGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.productsGrid.Location = new System.Drawing.Point(373, 12);
            this.productsGrid.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.productsGrid.Name = "productsGrid";
            this.productsGrid.RowHeadersWidth = 51;
            this.productsGrid.RowTemplate.Height = 24;
            this.productsGrid.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.productsGrid.Size = new System.Drawing.Size(1108, 380);
            this.productsGrid.TabIndex = 3;
            // 
            // btnAddProduct
            // 
            this.btnAddProduct.Location = new System.Drawing.Point(373, 690);
            this.btnAddProduct.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnAddProduct.Name = "btnAddProduct";
            this.btnAddProduct.Size = new System.Drawing.Size(1108, 28);
            this.btnAddProduct.TabIndex = 4;
            this.btnAddProduct.Text = "Add";
            this.btnAddProduct.UseVisualStyleBackColor = true;
            this.btnAddProduct.Click += new System.EventHandler(this.btnAddProduct_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(16, 690);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(337, 28);
            this.button2.TabIndex = 5;
            this.button2.Text = "Test database";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // btnCustomerProducts
            // 
            this.btnCustomerProducts.Location = new System.Drawing.Point(16, 660);
            this.btnCustomerProducts.Name = "btnCustomerProducts";
            this.btnCustomerProducts.Size = new System.Drawing.Size(337, 23);
            this.btnCustomerProducts.TabIndex = 6;
            this.btnCustomerProducts.Text = "Manage Customer-Products";
            this.btnCustomerProducts.UseVisualStyleBackColor = true;
            this.btnCustomerProducts.Click += new System.EventHandler(this.btnCustomerProducts_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1496, 734);
            this.Controls.Add(this.btnCustomerProducts);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.btnAddProduct);
            this.Controls.Add(this.productsGrid);
            this.Controls.Add(this.allCategories);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.allCategories)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.productsGrid)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.DataGridView allCategories;
        private System.Windows.Forms.DataGridView productsGrid;
        private System.Windows.Forms.Button btnAddProduct;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button btnCustomerProducts;
    }
}
