using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.Json;
using System.IO;
using System.Data.SqlClient;

namespace PracticalExamPrep
{
    public partial class Form1 : Form
    {
        private string connectionString = @"Data Source=RIKY\SQLEXPRESS;Initial Catalog=MiniFacebook;Integrated Security=True;TrustServerCertificate=True";
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    MessageBox.Show("Connection to the database was successful!");
                    SqlCommand cmd = new SqlCommand("SELECT * FROM Users", connection);
                    SqlDataAdapter da = new SqlDataAdapter(cmd);
                    DataSet ds = new DataSet();
                    da.Fill(ds);
                    dgvUsers.DataSource = ds.Tables[0];
                    connection.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error connecting to the database: {ex.Message}");
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            if (dgvUsers.CurrentRow == null)
                return;
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("INSERT INTO Posts (Uidd, PoText, PoDate, NoOfShares) VALUES (@Uidd, @PoText, @PoDate, @NoOfShares)", connection);
                cmd.Parameters.AddWithValue("@Uidd", dgvUsers.CurrentRow.Cells["Uidd"].Value);
                cmd.Parameters.AddWithValue("@PoText", poTextTextBox.Text);
                cmd.Parameters.AddWithValue("@PoDate", DateTime.Parse(poDateTextBox.Text));
                cmd.Parameters.AddWithValue("@NoOfShares", int.Parse(noOfSharesTextBox.Text));
                
                connection.Open();
                cmd.ExecuteNonQuery();
                connection.Close();
                
                dgvUsers_selectionChanged(sender, e);
            }
        }

        private void dgvUsers_selectionChanged(object sender, EventArgs e)
        {
            if (dgvUsers.CurrentRow == null)
                return;
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                connection.Open();
                SqlCommand cmd = new SqlCommand("Select * from Posts where Uidd = @Uidd", connection);
                cmd.Parameters.AddWithValue("@Uidd", dgvUsers.CurrentRow.Cells["Uidd"].Value);

                SqlDataAdapter da = new SqlDataAdapter(cmd);
                DataSet ds = new DataSet();
                da.Fill(ds);
                dgvPosts.DataSource = ds.Tables[0];

                dgvPosts.Columns["Poid"].ReadOnly = true;
                dgvPosts.Columns["Uidd"].ReadOnly = true;

                connection.Close();
            }
        }

        private void dgvPosts_UserDeletingRow(object sender, DataGridViewRowCancelEventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("DELETE FROM Posts WHERE Poid = @Poid", connection);
                cmd.Parameters.AddWithValue("@Poid", e.Row.Cells["Poid"].Value);
                connection.Open();
                cmd.ExecuteNonQuery();
                connection.Close();
            }
        }

        private void dgvPosts_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (dgvPosts.Rows[e.RowIndex].IsNewRow)
                return;
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand cmd = new SqlCommand("Update Posts set PoText = @PoText, PoDate = @PoDate, NoOfShares = @NoOfShares where Poid = @Poid", connection);
                foreach (DataGridViewCell cell in dgvPosts.Rows[e.RowIndex].Cells)
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
