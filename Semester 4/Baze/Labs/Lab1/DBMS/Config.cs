using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBMS
{
    using System.Text.Json.Serialization;

    public class Config
    {
        [JsonPropertyName("formTitle")]
        public string FormTitle { get; set; }

        [JsonPropertyName("masterQuery")]
        public string MasterQuery { get; set; }

        [JsonPropertyName("detailQuery")]
        public string DetailQuery { get; set; }

        [JsonPropertyName("idColumn")]
        public string IdColumn { get; set; }

        [JsonPropertyName("insertDetailQuery")]
        public string InsertDetailQuery { get; set; }

        [JsonPropertyName("updateDetailQuery")]
        public string UpdateDetailQuery { get; set; }

        [JsonPropertyName("deleteDetailQuery")]
        public string DeleteDetailQuery { get; set; }

        [JsonPropertyName("masterKeyColumn")]
        public string MasterKeyColumn { get; set; }

        [JsonPropertyName("detailForeignKeyColumn")]
        public string DetailForeignKeyColumn { get; set; }

        [JsonPropertyName("detailColumns")]
        public List<string> DetailColumns { get; set; }

        [JsonPropertyName("fieldLabels")]
        public Dictionary<string, string> FieldLabels { get; set; }

        [JsonPropertyName("requiredFields")]
        public List<string> RequiredFields { get; set; }
    }

}

/*
   {
     "formTitle": "Checkout Counters and Customers",
     "masterQuery": "SELECT * FROM checkoutCounter",
     "detailQuery": "SELECT * FROM customers WHERE checkoutCounterId = @id",
     "idColumn": "customerId",
     "insertDetailQuery": "INSERT INTO customers (customerName, checkoutCounterId, age) VALUES (@customerName, @checkoutCounterId, @age)",
     "updateDetailQuery": "UPDATE customers SET customerName = @customerName, age = @age WHERE customerId = @customerId",
     "deleteDetailQuery": "DELETE FROM customers WHERE customerId = @customerId",
     "masterKeyColumn": "checkoutCounterId",
     "detailForeignKeyColumn": "checkoutCounterId",
     "detailColumns": [
       "customerId",
       "customerName",
       "checkoutCounterId",
       "age"
     ],
     "fieldLabels": {
       "customerName": "Customer Name",
       "age": "Customer Age"
     },
     "requiredFields": [
       "customerName"
     ]
   }
*/
   