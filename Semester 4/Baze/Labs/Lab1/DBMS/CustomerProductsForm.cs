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

namespace DBMS
{
    public partial class CustomerProductsForm: Form
    {
        private string connectionString = @"Data Source=RIKY\SQLEXPRESS;Initial Catalog=Supermarket;Integrated Security=True;TrustServerCertificate=True";

        public CustomerProductsForm()
        {
            InitializeComponent();
            LoadProducts();
        }

        private void LoadProducts()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                SqlCommand cmd = new SqlCommand("SELECT productId, name FROM products", conn);
                SqlDataReader reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    checkedListBoxProducts.Items.Add(new ComboBoxItem
                    {
                        Text = reader["name"].ToString(),
                        Value = reader["productId"]
                    });
                }

                conn.Close();
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void btnAssignProducts_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtCustomerName.Text))
            {
                MessageBox.Show("Please enter a customer name.");
                return;
            }

            List<int> productIds = new List<int>();
            foreach (var item in checkedListBoxProducts.CheckedItems)
            {
                productIds.Add((int)((ComboBoxItem)item).Value);
            }

            string productIdList = string.Join(",", productIds);

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                SqlCommand cmd = new SqlCommand("AddCustomerWithProducts", conn);
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@CustomerName", txtCustomerName.Text.Trim());
                cmd.Parameters.AddWithValue("@ProductIds", productIdList);
                cmd.ExecuteNonQuery();
                conn.Close();
            }

            MessageBox.Show("Customer added with products (valid ones only).");
        }

    }
    public class ComboBoxItem
    {
        public string Text { get; set; }
        public object Value { get; set; }

        public override string ToString()
        {
            return Text;
        }
    }
}
