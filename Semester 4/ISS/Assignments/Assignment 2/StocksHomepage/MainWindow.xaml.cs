using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using System.Collections.ObjectModel;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace StocksHomepage
{
    public sealed partial class MainWindow : Window
    {
        private ObservableCollection<Stock> favoriteStocks { get; set; }
        private ObservableCollection<Stock> allStocks { get; set; }
        private ObservableCollection<Stock> allFilteredStocks { get; set; }
        private ObservableCollection<Stock> favoriteFilteredStocks { get; set; }

        public MainWindow()
        {
            this.InitializeComponent();
            this.LoadStocks();
        }

        private void LoadStocks()
        {
            this.favoriteStocks = new ObservableCollection<Stock>
            {
                new Stock { Symbol = "AAPL", Name = "Apple Inc.", Price = "$175.00", Change = "+1.2%", isFavorite = true },
                new Stock { Symbol = "MSFT", Name = "Microsoft Corp.", Price = "$320.00", Change = "-0.8%", isFavorite = true },
                new Stock { Symbol = "NVDA", Name = "NVIDIA Corporation", Price = "$600.00", Change = "+3.1%", isFavorite = true },
                new Stock { Symbol = "TSM", Name = "Taiwan Semiconductor", Price = "$110.00", Change = "+1.5%" , isFavorite = true }
            };

            this.allStocks = new ObservableCollection<Stock>()
            {
                new Stock { Symbol = "GOOGL", Name = "Alphabet Inc.", Price = "$2800.00", Change = "+0.5%", isFavorite = false },
                new Stock { Symbol = "AMZN", Name = "Amazon.com Inc.", Price = "$3500.00", Change = "-1.0%", isFavorite = false },
                new Stock { Symbol = "TSLA", Name = "Tesla Inc.", Price = "$700.00", Change = "+2.3%", isFavorite = false },
                new Stock { Symbol = "META", Name = "Meta Platforms, Inc.", Price = "$340.00", Change = "+0.8%", isFavorite = false },
                new Stock { Symbol = "DIS", Name = "The Walt Disney Company", Price = "$190.00", Change = "-2.0%", isFavorite = false },
                new Stock { Symbol = "NFLX", Name = "Netflix, Inc.", Price = "$500.00", Change = "+2.8%", isFavorite = false },
                new Stock { Symbol = "INTC", Name = "Intel Corporation", Price = "$50.00", Change = "-0.5%", isFavorite = false },
                new Stock { Symbol = "CSCO", Name = "Cisco Systems, Inc.", Price = "$55.00", Change = "+0.2%", isFavorite = false },
                new Stock { Symbol = "QCOM", Name = "QUALCOMM Incorporated", Price = "$150.00", Change = "-0.1%", isFavorite = false },
                new Stock { Symbol = "IBM", Name = "International Business Machines Corporation", Price = "$120.00", Change = "+0.3%", isFavorite = false },
                new Stock { Symbol = "ORCL", Name = "Oracle Corporation", Price = "$80.00", Change = "-0.4%", isFavorite = false },
                new Stock { Symbol = "ADBE", Name = "Adobe Inc.", Price = "$600.00", Change = "+1.0%", isFavorite = false },
                new Stock { Symbol = "CRM", Name = "Salesforce.com, inc.", Price = "$250.00", Change = "-0.3%", isFavorite = false },
                new Stock { Symbol = "NOW", Name = "ServiceNow, Inc.", Price = "$500.00", Change = "+0.7%", isFavorite = false },
                new Stock { Symbol = "SAP", Name = "SAP SE", Price = "$150.00", Change = "-0.2%", isFavorite = false },
                new Stock { Symbol = "UBER", Name = "Uber Technologies, Inc.", Price = "$40.00", Change = "+0.9%", isFavorite = false },
                new Stock { Symbol = "LYFT", Name = "Lyft, Inc.", Price = "$50.00", Change = "-0.6%", isFavorite = false },
                new Stock { Symbol = "ZM", Name = "Zoom Video Communications, Inc.", Price = "$200.00", Change = "+1.2%", isFavorite = false },
                new Stock { Symbol = "DOCU", Name = "DocuSign, Inc.", Price = "$150.00", Change = "-0.8%", isFavorite = false }
            };

            this.allFilteredStocks = new ObservableCollection<Stock>(this.allStocks);
            this.favoriteFilteredStocks = new ObservableCollection<Stock>(this.favoriteStocks);
            FavoritesList.ItemsSource = this.favoriteFilteredStocks;
            StocksList.ItemsSource = this.allFilteredStocks;
        }

        private void FavoriteButton_Click(object sender, RoutedEventArgs e)
        {
            // Get the button that was clicked
            var button = sender as Button;
            if (button != null)
            {
                // Get the stock object using the Tag property (set above in XAML)
                var stock = button.Tag as Stock;
                if (stock != null)
                {
                    if (stock.isFavorite)
                    {
                        // Remove the stock from the favorite list
                        this.favoriteStocks.Remove(stock);
                        this.favoriteFilteredStocks.Remove(stock);
                        stock.isFavorite = false;
                        this.allStocks.Add(stock);
                        this.allFilteredStocks.Add(stock);
                    }
                    else
                    {
                        // Add the stock to the favorite list
                        this.allStocks.Remove(stock);
                        this.allFilteredStocks.Remove(stock);
                        stock.isFavorite = true;
                        this.favoriteStocks.Add(stock);
                        this.favoriteFilteredStocks.Add(stock);
                    }
                }
                FilterStocks();
            }
        }

        private void SearchBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            FilterStocks();
        }

        private void SortDropdown_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            FilterStocks();
        }

        private void FilterStocks()
        {
            var query = SearchBox.Text.ToLower();
            var sortOption = (SortDropdown.SelectedItem as ComboBoxItem)?.Content.ToString();

            var allFiltered = allStocks.Where(stock =>
                stock.Name.ToLower().Contains(query) ||
                stock.Symbol.ToLower().Contains(query)).ToList();

            var favoriteFiltered = favoriteStocks.Where(stock =>
                stock.Name.ToLower().Contains(query) ||
                stock.Symbol.ToLower().Contains(query)).ToList();

            switch (sortOption)
            {
                case "Sort by Name":
                    allFiltered = allFiltered.OrderBy(stock => stock.Name).ToList();
                    favoriteFiltered = favoriteFiltered.OrderBy(stock => stock.Name).ToList();
                    break;
                case "Sort by Price":
                    allFiltered = allFiltered.OrderBy(stock => decimal.Parse(stock.Price.Trim('$'))).ToList();
                    favoriteFiltered = favoriteFiltered.OrderBy(stock => decimal.Parse(stock.Price.Trim('$'))).ToList();
                    break;
                case "Sort by Change":
                    allFiltered = allFiltered.OrderBy(stock => decimal.Parse(stock.Change.Trim('%'))).ToList();
                    favoriteFiltered = favoriteFiltered.OrderBy(stock => decimal.Parse(stock.Change.Trim('%'))).ToList();
                    break;
            }
            favoriteFilteredStocks.Clear();
            allFilteredStocks.Clear();
            foreach (var stock in allFiltered)
            {
                allFilteredStocks.Add(stock);
            }
            foreach (var stock in favoriteFiltered)
            {
                favoriteFilteredStocks.Add(stock);
            }
        }

    }
}
