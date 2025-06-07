using System;
using System.Data;
using System.Data.SqlClient;
using System.Runtime.InteropServices.Marshalling;

namespace PracticalExam
{
    public partial class Form1 : Form
    {
        private string connectionString = @"Data Source=RIKY\SQLEXPRESS;Initial Catalog=Altex;Integrated Security=True;TrustServerCertificate=True";
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                MessageBox.Show("Connection to the database was successful!");
                SqlCommand cmd = new SqlCommand("SELECT * FROM Customers", connection);
                SqlDataAdapter da = new SqlDataAdapter(cmd);
                DataSet ds = new DataSet();
                da.Fill(ds);
                dgvCustomers.DataSource = ds.Tables[0];
                connection.Close();
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            if (dgvCustomers.CurrentRow == null)
                return;
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("INSERT INTO Orders (Cid, Pid, Oquantity, Oprice) VALUES (@Cid, @Pid, @Oquantity, @Oprice)", connection);
                cmd.Parameters.AddWithValue("@Cid", dgvCustomers.CurrentRow.Cells["Cid"].Value);
                cmd.Parameters.AddWithValue("@Pid", productIdTextBox.Text);
                cmd.Parameters.AddWithValue("@Oquantity", int.Parse(quantityTextBox.Text));
                cmd.Parameters.AddWithValue("@Oprice", float.Parse(totalPriceTextBox.Text));

                connection.Open();
                cmd.ExecuteNonQuery();
                connection.Close();

                dgvCustomers_selectionChanged(sender, e);
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {
            return;
        }

        private void dgvCustomers_selectionChanged(object sender, EventArgs e)
        {
            if (dgvCustomers.CurrentRow == null)
                return;
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                SqlCommand cmd = new SqlCommand("Select * from Orders where Cid = @Cid", connection);
                cmd.Parameters.AddWithValue("@Cid", dgvCustomers.CurrentRow.Cells["Cid"].Value);

                SqlDataAdapter da = new SqlDataAdapter(cmd);
                DataSet ds = new DataSet();
                da.Fill(ds);
                dgvOrders.DataSource = ds.Tables[0];

                dgvOrders.Columns["Pid"].ReadOnly = true;
                dgvOrders.Columns["Cid"].ReadOnly = true;

                connection.Close();
            }
        }

        private void dgvOrders_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("DELETE FROM Orders WHERE Cid = @Cid AND Pid = @Pid", connection);
                cmd.Parameters.AddWithValue("@Cid", e.Row.Cells["Cid"].Value);
                cmd.Parameters.AddWithValue("@Pid", e.Row.Cells["Pid"].Value);
                connection.Open();
                cmd.ExecuteNonQuery();
                connection.Close();
            }
        }

        private void dgvOrders_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (dgvOrders.Rows[e.RowIndex].IsNewRow)
                return;
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("Update Orders set Oquantity = @Oquantity, Oprice = @Oprice where Cid = @Cid AND Pid = @Pid", connection);
                foreach (DataGridViewCell cell in dgvOrders.Rows[e.RowIndex].Cells)
                {
                    string paramName = "@" + cell.OwningColumn.Name;
                    cmd.Parameters.AddWithValue(paramName, cell.Value ?? DBNull.Value);
                }
                connection.Open();
                cmd.ExecuteNonQuery();
                connection.Close();
            }
        }

    }
}
