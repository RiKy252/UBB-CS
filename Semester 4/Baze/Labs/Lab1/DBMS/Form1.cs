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
                }

                conn.Close();
            }
        }

    }
}
