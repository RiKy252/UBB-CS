using System.Collections.ObjectModel;
using System.Linq;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using StocksHomepage.Models;
using StocksHomepage.Services;

namespace StocksHomepage.ViewModels
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private ObservableCollection<Stock> _allStocks;
        private ObservableCollection<Stock> _favoriteStocks;
        private string _searchQuery;

        public ObservableCollection<Stock> AllStocks { get => _allStocks; set { _allStocks = value; OnPropertyChanged(); } }
        public ObservableCollection<Stock> FavoriteStocks { get => _favoriteStocks; set { _favoriteStocks = value; OnPropertyChanged(); } }
        public string SearchQuery { get => _searchQuery; set { _searchQuery = value; OnPropertyChanged(); FilterStocks(); } }

        public MainViewModel()
        {
            var service = new StockService();
            AllStocks = service.LoadStocks();
            FavoriteStocks = new ObservableCollection<Stock>(AllStocks.Where(s => s.IsFavorite));
        }

        public void ToggleFavorite(Stock stock)
        {
            stock.IsFavorite = !stock.IsFavorite;
            if (stock.IsFavorite)
            {
                FavoriteStocks.Add(stock);
                AllStocks.Remove(stock);
            }
            else
            {
                AllStocks.Add(stock);
                FavoriteStocks.Remove(stock);
            }
        }

        public void FilterStocks()
        {
            var query = SearchQuery?.ToLower() ?? "";
            AllStocks = new ObservableCollection<Stock>(AllStocks.Where(s => s.Name.ToLower().Contains(query) || s.Symbol.ToLower().Contains(query)));
            FavoriteStocks = new ObservableCollection<Stock>(FavoriteStocks.Where(s => s.Name.ToLower().Contains(query) || s.Symbol.ToLower().Contains(query)));
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}