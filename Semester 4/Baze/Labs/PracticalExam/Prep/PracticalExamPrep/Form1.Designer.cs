namespace PracticalExamPrep
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
            dgvUsers = new DataGridView();
            dgvPosts = new DataGridView();
            addButton = new Button();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            poDateTextBox = new TextBox();
            poTextTextBox = new TextBox();
            noOfSharesTextBox = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dgvUsers).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dgvPosts).BeginInit();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(12, 12);
            button1.Name = "button1";
            button1.Size = new Size(841, 42);
            button1.TabIndex = 0;
            button1.Text = "CONNECT";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // dgvUsers
            // 
            dgvUsers.AllowUserToAddRows = false;
            dgvUsers.AllowUserToDeleteRows = false;
            dgvUsers.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvUsers.Location = new Point(12, 69);
            dgvUsers.Name = "dgvUsers";
            dgvUsers.ReadOnly = true;
            dgvUsers.RowHeadersWidth = 51;
            dgvUsers.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvUsers.Size = new Size(841, 247);
            dgvUsers.TabIndex = 1;
            dgvUsers.SelectionChanged += dgvUsers_selectionChanged;
            dgvPosts.UserDeletingRow += dgvPosts_UserDeletingRow;
            dgvPosts.CellValueChanged += dgvPosts_CellValueChanged;
            // 
            // dgvPosts
            // 
            dgvPosts.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvPosts.Location = new Point(12, 371);
            dgvPosts.Name = "dgvPosts";
            dgvPosts.RowHeadersWidth = 51;
            dgvPosts.Size = new Size(841, 306);
            dgvPosts.TabIndex = 2;
            // 
            // addButton
            // 
            addButton.Location = new Point(12, 323);
            addButton.Name = "addButton";
            addButton.Size = new Size(841, 42);
            addButton.TabIndex = 11;
            addButton.Text = "ADD POST";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(893, 69);
            label1.Name = "label1";
            label1.Size = new Size(57, 20);
            label1.TabIndex = 12;
            label1.Text = "PoDate";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(893, 138);
            label2.Name = "label2";
            label2.Size = new Size(52, 20);
            label2.TabIndex = 13;
            label2.Text = "PoText";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(893, 211);
            label3.Name = "label3";
            label3.Size = new Size(88, 20);
            label3.TabIndex = 14;
            label3.Text = "NoOfShares";
            // 
            // poDateTextBox
            // 
            poDateTextBox.Location = new Point(968, 66);
            poDateTextBox.Name = "poDateTextBox";
            poDateTextBox.Size = new Size(369, 27);
            poDateTextBox.TabIndex = 15;
            // 
            // poTextTextBox
            // 
            poTextTextBox.Location = new Point(968, 131);
            poTextTextBox.Name = "poTextTextBox";
            poTextTextBox.Size = new Size(369, 27);
            poTextTextBox.TabIndex = 16;
            // 
            // noOfSharesTextBox
            // 
            noOfSharesTextBox.Location = new Point(987, 208);
            noOfSharesTextBox.Name = "noOfSharesTextBox";
            noOfSharesTextBox.Size = new Size(350, 27);
            noOfSharesTextBox.TabIndex = 17;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1373, 714);
            Controls.Add(noOfSharesTextBox);
            Controls.Add(poTextTextBox);
            Controls.Add(poDateTextBox);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(addButton);
            Controls.Add(dgvPosts);
            Controls.Add(dgvUsers);
            Controls.Add(button1);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dgvUsers).EndInit();
            ((System.ComponentModel.ISupportInitialize)dgvPosts).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        private void DgvPosts_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            throw new NotImplementedException();
        }

        #endregion

        private Button button1;
        private DataGridView dgvUsers;
        private DataGridView dgvPosts;
        private Button addButton;
        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox poDateTextBox;
        private TextBox poTextTextBox;
        private TextBox noOfSharesTextBox;
    }
}
