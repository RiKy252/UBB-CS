namespace PracticalExam
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            button1 = new Button();
            dgvCustomers = new DataGridView();
            dgvOrders = new DataGridView();
            addButton = new Button();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            productIdTextBox = new TextBox();
            quantityTextBox = new TextBox();
            totalPriceTextBox = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dgvCustomers).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dgvOrders).BeginInit();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(12, 12);
            button1.Name = "button1";
            button1.Size = new Size(682, 46);
            button1.TabIndex = 0;
            button1.Text = "Connect";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // dgvCustomers
            // 
            dgvCustomers.AllowUserToAddRows = false;
            dgvCustomers.AllowUserToDeleteRows = false;
            dgvCustomers.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvCustomers.Location = new Point(12, 64);
            dgvCustomers.Name = "dgvCustomers";
            dgvCustomers.ReadOnly = true;
            dgvCustomers.RowHeadersWidth = 51;
            dgvCustomers.Size = new Size(682, 278);
            dgvCustomers.TabIndex = 1;
            dgvCustomers.SelectionChanged += dgvCustomers_selectionChanged;
            dgvOrders.UserDeletingRow += dgvOrders_UserDeletingRow;
            dgvOrders.CellValueChanged += dgvOrders_CellValueChanged;
            // 
            // dgvOrders
            // 
            dgvOrders.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvOrders.Location = new Point(12, 388);
            dgvOrders.Name = "dgvOrders";
            dgvOrders.RowHeadersWidth = 51;
            dgvOrders.Size = new Size(682, 278);
            dgvOrders.TabIndex = 2;
            // 
            // addButton
            // 
            addButton.Location = new Point(709, 313);
            addButton.Name = "addButton";
            addButton.Size = new Size(622, 29);
            addButton.TabIndex = 3;
            addButton.Text = "Add order";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(737, 73);
            label1.Name = "label1";
            label1.Size = new Size(77, 20);
            label1.TabIndex = 4;
            label1.Text = "Product Id";
            label1.Click += label1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(737, 129);
            label2.Name = "label2";
            label2.Size = new Size(65, 20);
            label2.TabIndex = 5;
            label2.Text = "Quantity";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(737, 188);
            label3.Name = "label3";
            label3.Size = new Size(78, 20);
            label3.TabIndex = 6;
            label3.Text = "Total Price";
            // 
            // productIdTextBox
            // 
            productIdTextBox.Location = new Point(838, 70);
            productIdTextBox.Name = "productIdTextBox";
            productIdTextBox.Size = new Size(476, 27);
            productIdTextBox.TabIndex = 7;
            // 
            // quantityTextBox
            // 
            quantityTextBox.Location = new Point(838, 129);
            quantityTextBox.Name = "quantityTextBox";
            quantityTextBox.Size = new Size(476, 27);
            quantityTextBox.TabIndex = 8;
            // 
            // totalPriceTextBox
            // 
            totalPriceTextBox.Location = new Point(838, 188);
            totalPriceTextBox.Name = "totalPriceTextBox";
            totalPriceTextBox.Size = new Size(476, 27);
            totalPriceTextBox.TabIndex = 9;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1343, 706);
            Controls.Add(totalPriceTextBox);
            Controls.Add(quantityTextBox);
            Controls.Add(productIdTextBox);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(addButton);
            Controls.Add(dgvOrders);
            Controls.Add(dgvCustomers);
            Controls.Add(button1);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dgvCustomers).EndInit();
            ((System.ComponentModel.ISupportInitialize)dgvOrders).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private DataGridView dgvCustomers;
        private DataGridView dgvOrders;
        private Button addButton;
        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox productIdTextBox;
        private TextBox quantityTextBox;
        private TextBox totalPriceTextBox;
    }
}
