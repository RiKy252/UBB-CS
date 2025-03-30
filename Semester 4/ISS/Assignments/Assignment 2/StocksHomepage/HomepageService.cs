using System.Collections.ObjectModel;
using StocksHomepage.Models;

namespace StocksHomepage.Services
{
    public class StockService
    {
        public ObservableCollection<Stock> LoadStocks()
        {
            return new ObservableCollection<Stock>
            {
                new Stock { Symbol = "AAPL", Name = "Apple Inc.", Price = "$175.00", Change = "+1.2%", IsFavorite = true },
                new Stock { Symbol = "MSFT", Name = "Microsoft Corp.", Price = "$320.00", Change = "-0.8%", IsFavorite = true },
                new Stock { Symbol = "NVDA", Name = "NVIDIA Corporation", Price = "$600.00", Change = "+3.1%", IsFavorite = true },
                new Stock { Symbol = "TSM", Name = "Taiwan Semiconductor", Price = "$110.00", Change = "+1.5%" , IsFavorite = true },
                new Stock { Symbol = "GOOGL", Name = "Alphabet Inc.", Price = "$2800.00", Change = "+0.5%", IsFavorite = false },
                new Stock { Symbol = "AMZN", Name = "Amazon.com Inc.", Price = "$3500.00", Change = "-1.0%", IsFavorite = false },
                new Stock { Symbol = "TSLA", Name = "Tesla Inc.", Price = "$700.00", Change = "+2.3%", IsFavorite = false },
                new Stock { Symbol = "META", Name = "Meta Platforms, Inc.", Price = "$340.00", Change = "+0.8%", IsFavorite = false },
                new Stock { Symbol = "DIS", Name = "The Walt Disney Company", Price = "$190.00", Change = "-2.0%", IsFavorite = false },
                new Stock { Symbol = "NFLX", Name = "Netflix, Inc.", Price = "$500.00", Change = "+2.8%", IsFavorite = false },
                new Stock { Symbol = "INTC", Name = "Intel Corporation", Price = "$50.00", Change = "-0.5%", IsFavorite = false },
                new Stock { Symbol = "CSCO", Name = "Cisco Systems, Inc.", Price = "$55.00", Change = "+0.2%", IsFavorite = false },
                new Stock { Symbol = "QCOM", Name = "QUALCOMM Incorporated", Price = "$150.00", Change = "-0.1%", IsFavorite = false },
                new Stock { Symbol = "IBM", Name = "International Business Machines Corporation", Price = "$120.00", Change = "+0.3%", IsFavorite = false },
                new Stock { Symbol = "ORCL", Name = "Oracle Corporation", Price = "$80.00", Change = "-0.4%", IsFavorite = false },
                new Stock { Symbol = "ADBE", Name = "Adobe Inc.", Price = "$600.00", Change = "+1.0%", IsFavorite = false },
                new Stock { Symbol = "CRM", Name = "Salesforce.com, inc.", Price = "$250.00", Change = "-0.3%", IsFavorite = false },
                new Stock { Symbol = "NOW", Name = "ServiceNow, Inc.", Price = "$500.00", Change = "+0.7%", IsFavorite = false },
                new Stock { Symbol = "SAP", Name = "SAP SE", Price = "$150.00", Change = "-0.2%", IsFavorite = false },
                new Stock { Symbol = "UBER", Name = "Uber Technologies, Inc.", Price = "$40.00", Change = "+0.9%", IsFavorite = false },
                new Stock { Symbol = "LYFT", Name = "Lyft, Inc.", Price = "$50.00", Change = "-0.6%", IsFavorite = false },
                new Stock { Symbol = "ZM", Name = "Zoom Video Communications, Inc.", Price = "$200.00", Change = "+1.2%", IsFavorite = false },
                new Stock { Symbol = "DOCU", Name = "DocuSign, Inc.", Price = "$150.00", Change = "-0.8%", IsFavorite = false }
            };
        }
    }
}