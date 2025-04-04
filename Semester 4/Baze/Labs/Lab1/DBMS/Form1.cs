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
    public partial class Form1: Form
    {
        string connectionString = @"Data Source=RIKY\SQLEXPRESS;Initial Catalog=Supermarket;Integrated Security=True;TrustServerCertificate=True";
        public Form1()
        {
            InitializeComponent();
            allCategories.SelectionChanged += allCategories_selectionChanged;
            productsGrid.UserDeletingRow += productsGrid_UserDeletingRow;
            productsGrid.CellValueChanged += productsGrid_CellValueChanged;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnection cn = new SqlConnection(connectionString);
                if (cn.State == System.Data.ConnectionState.Closed)
                    cn.Open();
                MessageBox.Show("Test connection succeded.", "Message", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void loadAllCategories()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                SqlCommand cmd = new SqlCommand("select * from category", conn);
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet ds = new DataSet();
                daChild.Fill(ds);
                allCategories.DataSource = ds.Tables[0];

                conn.Close();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            loadAllCategories();
        }

        private void productsGrid_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("DELETE FROM products WHERE productId=@id", conn);
                cmd.Parameters.AddWithValue("@id", e.Row.Cells["productId"].Value);

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
                SqlCommand cmd = new SqlCommand(
                    "UPDATE products SET productId=@productId, categoryId=@categoryId, name=@name, expiringDate=@expiringDate, price=@price, shelfId=@shelfId WHERE productId=@productId", conn);

                cmd.Parameters.AddWithValue("@productId", productsGrid.Rows[e.RowIndex].Cells["productId"].Value);
                cmd.Parameters.AddWithValue("@categoryId", productsGrid.Rows[e.RowIndex].Cells["categoryId"].Value);

                cmd.Parameters.AddWithValue("@name", productsGrid.Rows[e.RowIndex].Cells["name"].Value ?? DBNull.Value);
                cmd.Parameters.AddWithValue("@expiringDate", productsGrid.Rows[e.RowIndex].Cells["expiringDate"].Value ?? DBNull.Value);
                cmd.Parameters.AddWithValue("@price", productsGrid.Rows[e.RowIndex].Cells["price"].Value ?? DBNull.Value);
                cmd.Parameters.AddWithValue("@shelfId", productsGrid.Rows[e.RowIndex].Cells["shelfId"].Value ?? DBNull.Value);

                conn.Open();
                cmd.ExecuteNonQuery();
                conn.Close();
            }
        }

        private void btnAddProduct_Click(object sender, EventArgs e)
        {
            if (allCategories.CurrentRow == null) return;

            int categoryId = Convert.ToInt32(allCategories.CurrentRow.Cells["categoryId"].Value);
            int newProductId;
            string name = nameTextBox.Text;
            string shelfId = shelfIdTextBox.Text;
            string price = priceTextBox.Text;
            DateTime expiringDate;
            if (!DateTime.TryParse(expDateTextBox.Text, out expiringDate))
            {
                MessageBox.Show("Please enter a valid date for Expiring Date (e.g., yyyy-MM-dd).", "Invalid Date", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                SqlCommand getMaxId = new SqlCommand("SELECT ISNULL(MAX(productId), 0) + 1 FROM products", conn);
                newProductId = (int)getMaxId.ExecuteScalar();

                SqlCommand cmd = new SqlCommand(
                    "INSERT INTO products (productId, categoryId, name, expiringDate, price, shelfId) " +
                    "VALUES (@productId, @categoryId, @name, @expiringDate, @price, @shelfId)", conn);

                cmd.Parameters.AddWithValue("@productId", newProductId);
                cmd.Parameters.AddWithValue("@categoryId", categoryId);
                cmd.Parameters.AddWithValue("@name", name);
                cmd.Parameters.AddWithValue("@expiringDate", expiringDate);
                cmd.Parameters.AddWithValue("@price", price);
                cmd.Parameters.AddWithValue("@shelfId", shelfId);

                cmd.ExecuteNonQuery();
                conn.Close();
            }

            allCategories_selectionChanged(null, null); // Refresh product list
        }



        private void allCategories_selectionChanged(object sender, EventArgs e)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                if (allCategories.CurrentRow != null)
                {
                    int categoryId = Convert.ToInt32(allCategories.CurrentRow.Cells["categoryId"].Value);
                    SqlCommand cmd = new SqlCommand("select * from products where categoryId=@categoryId", conn);
                    cmd.Parameters.AddWithValue("@categoryId", categoryId);

                    SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                    DataSet dataSet = new DataSet();
                    daChild.Fill(dataSet);
                    productsGrid.DataSource = dataSet.Tables[0];
                    productsGrid.Columns["productId"].ReadOnly = true;
                    productsGrid.Columns["categoryId"].ReadOnly = true;
                }

                conn.Close();
            }
        }

        private void nameTextBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
