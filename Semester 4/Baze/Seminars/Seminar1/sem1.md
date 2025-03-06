# Seminar 1

>using System;
using System.Data;
using System.Data.SqlClient;
string connString = "" // Aici trebuie connection string-ul pt baza ta de date;
>
>using(SqlConnection conn = new SqlConnection(connString))
{
    conn.Open();
>
>    SqlCommand sqlComm = new SqlCommand("select COUNT(*) FROM Spies", conn);
    Console.WriteLine(sqlComm.ExecuteScalar().ToString());
>
>    sqlComm.CommandText = "select * FROM Spies;";
    SqlDataReader sqlRead = sqlComm.ExecuteReader();
    while (sqlRead.Read())
    {
        Console.WriteLine(sqlRead[2]);
    }
    if (sqlRead != null)
    {
        sqlRead.Close();
    }
    DataSet dataSet = new DataSet();
    SqlDataAdapter sqlAdapt = new SqlDataAdapter("SELECT * FROM SPIES", conn);
    sqlAdapt.Fill(dataSet, "Spies");
    DataTable dataTable = dataSet.Tables["Spies"];
    foreach (DataRow row in dataTable.Rows)
    {
        Console.WriteLine(row[1]);
    }
>
>    SqlCommand deleteCom = new SqlCommand("DELETE FROM SPIES WHERE id = @id", conn);
    deleteCom.Parameters.Add("@id", SqlDbType.Int, 10, "id");
>
>    sqlAdapt.DeleteCommand = deleteCom;
    dataTable.Rows[6].Delete();
    sqlAdapt.Update(dataSet, "Spies");
>
>    DataRow dataRow = dataTable.NewRow();
    dataRow[0] = 10;
    dataRow[1] = "Banu Marius regele tuturor";
    dataRow[2] = "Mosu meu";
    dataRow[3] = 20;
    dataRow[4] = 2.10;
    dataRow[5] = 98;
>
>    SqlCommandBuilder sqlCmmBuilder = new SqlCommandBuilder(sqlAdapt);
>
>    dataTable.Rows.Add(dataRow);
    sqlAdapt.Update(dataSet, "Spies");
    conn.Close();
}

