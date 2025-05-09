using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.Json;
using System.IO;

namespace DBMS
{
    public partial class Form1 : Form
    {
        private string connectionString = @"Data Source=RIKY\SQLEXPRESS;Initial Catalog=Supermarket;Integrated Security=True;TrustServerCertificate=True";
        private Config config;
        private Dictionary<string, TextBox> inputFields = new Dictionary<string, TextBox>();
        private Dictionary<string, Label> inputLabels = new Dictionary<string, Label>();

        public Form1()
        {
            InitializeComponent();
            LoadConfig();
            SetupForm();
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void LoadConfig()
        {
            try
            {
                string configJson = File.ReadAllText("C:\\Users\\bolog\\Documents\\Facultate\\UBB-CS\\Semester 4\\Baze\\Labs\\Lab1\\DBMS\\config.json");
                config = JsonSerializer.Deserialize<Config>(configJson);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error loading config: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void SetupForm()
        {
            if (config == null) return;

            // Set form title
            this.Text = config.FormTitle;

            // Setup master grid
            allCategories.SelectionChanged += allCategories_selectionChanged;
            allCategories.AllowUserToAddRows = false;
            allCategories.AllowUserToDeleteRows = false;
            allCategories.ReadOnly = true;
            allCategories.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            // Setup detail grid
            productsGrid.UserDeletingRow += productsGrid_UserDeletingRow;
            productsGrid.CellValueChanged += productsGrid_CellValueChanged;

            // Create dynamic input fields
            CreateInputFields();

            // Load initial data
            LoadMasterData();
        }

        private void CreateInputFields()
        {
            int yOffset = 350; 
            int labelX = 280;
            int textBoxX = 380;
            int width = 500;
            int height = 25;
            int spacing = 30;

            foreach (var column in config.DetailColumns)
            {
                if (column == config.IdColumn || column == config.MasterKeyColumn || column == config.DetailForeignKeyColumn)
                    continue;

                // Create label
                Label label = new Label();
                label.AutoSize = true;
                label.Location = new Point(labelX, yOffset);
                label.Text = config.FieldLabels.ContainsKey(column) ? config.FieldLabels[column] : column;
                this.Controls.Add(label);
                inputLabels[column] = label;

                // Create textbox
                TextBox textBox = new TextBox();
                textBox.Location = new Point(textBoxX, yOffset);
                textBox.Size = new Size(width, height);
                textBox.Name = column + "TextBox";
                this.Controls.Add(textBox);
                inputFields[column] = textBox;

                yOffset += spacing;
            }
        }

        private void LoadMasterData()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                SqlCommand cmd = new SqlCommand(config.MasterQuery, conn);
                SqlDataAdapter da = new SqlDataAdapter(cmd);
                DataSet ds = new DataSet();
                da.Fill(ds);
                allCategories.DataSource = ds.Tables[0];
                conn.Close();
            }
        }

        private void allCategories_selectionChanged(object sender, EventArgs e)
        {
            if (allCategories.CurrentRow == null) return;

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                SqlCommand cmd = new SqlCommand(config.DetailQuery, conn);
                cmd.Parameters.AddWithValue("@id", allCategories.CurrentRow.Cells[config.MasterKeyColumn].Value);

                SqlDataAdapter da = new SqlDataAdapter(cmd);
                DataSet ds = new DataSet();
                da.Fill(ds);
                productsGrid.DataSource = ds.Tables[0];

                // Make key columns readonly
                productsGrid.Columns[config.IdColumn].ReadOnly = true;
                productsGrid.Columns[config.MasterKeyColumn].ReadOnly = true;
                productsGrid.Columns[config.DetailForeignKeyColumn].ReadOnly = true;

                conn.Close();
            }
        }

        private void productsGrid_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand(config.DeleteDetailQuery, conn);

                // Dynamically get the ID column and its value
                string idColumn = config.IdColumn;
                object idValue = e.Row.Cells[idColumn].Value;

                cmd.Parameters.AddWithValue("@" + idColumn, idValue);

                conn.Open();
                cmd.ExecuteNonQuery();
                conn.Close();
            }
        }


        private void productsGrid_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (productsGrid.Rows[e.RowIndex].IsNewRow) return;

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand(config.UpdateDetailQuery, conn);

                foreach (DataGridViewCell cell in productsGrid.Rows[e.RowIndex].Cells)
                {
                    string paramName = "@" + cell.OwningColumn.Name;
                    cmd.Parameters.AddWithValue(paramName, cell.Value ?? DBNull.Value);
                }

                conn.Open();
                cmd.ExecuteNonQuery();
                conn.Close();
            }
        }

        private void btnAddProduct_Click(object sender, EventArgs e)
        {
            if (allCategories.CurrentRow == null) return;

            // Validate required fields
            foreach (var requiredField in config.RequiredFields)
            {
                if (string.IsNullOrWhiteSpace(inputFields[requiredField].Text))
                {
                    MessageBox.Show($"Please fill in the required field: {config.FieldLabels[requiredField]}", 
                        "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                SqlCommand cmd = new SqlCommand(config.InsertDetailQuery, conn);

                // Add parameters for all detail columns
                foreach (var column in config.DetailColumns)
                {
                    if (column == config.IdColumn) continue; 
                    if (column == config.DetailForeignKeyColumn)
                    {
                        cmd.Parameters.AddWithValue("@" + column, allCategories.CurrentRow.Cells[config.MasterKeyColumn].Value);
                    }
                    else if (inputFields.ContainsKey(column))
                    {
                        cmd.Parameters.AddWithValue("@" + column, inputFields[column].Text);
                    }
                }

                cmd.ExecuteNonQuery();
                conn.Close();
            }

            // Clear input fields
            foreach (var textBox in inputFields.Values)
            {
                textBox.Clear();
            }

            // Refresh the detail grid
            allCategories_selectionChanged(null, null);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnection cn = new SqlConnection(connectionString);
                if (cn.State == System.Data.ConnectionState.Closed)
                    cn.Open();
                MessageBox.Show("Test connection succeeded.", "Message", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnection cn = new SqlConnection(connectionString);
                if (cn.State == System.Data.ConnectionState.Closed)
                    cn.Open();
                MessageBox.Show("Test connection succeeded.", "Message", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}