using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using StocksHomepage.Models;
using StocksHomepage.ViewModels;
using System.Windows;

namespace StocksHomepage
{
    public sealed partial class MainWindow : Window
    {
        public MainWindow()
        {
            this.InitializeComponent();
        }

        private void FavoriteButton_Click(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;
            var stock = button?.CommandParameter as Stock;
            // the line below does not work 
            (DataContext as MainViewModel)?.ToggleFavorite(stock);
        }
    }
}