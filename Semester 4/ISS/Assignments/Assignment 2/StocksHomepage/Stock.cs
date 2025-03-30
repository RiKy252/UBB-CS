using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace StocksHomepage.Models
{
    public class Stock : INotifyPropertyChanged
    {
        private string _symbol;
        private string _name;
        private string _price;
        private string _change;
        private bool _isFavorite;

        public string Symbol { get => _symbol; set { _symbol = value; OnPropertyChanged(); } }
        public string Name { get => _name; set { _name = value; OnPropertyChanged(); } }
        public string Price { get => _price; set { _price = value; OnPropertyChanged(); } }
        public string Change { get => _change; set { _change = value; OnPropertyChanged(); } }
        public bool IsFavorite { get => _isFavorite; set { _isFavorite = value; OnPropertyChanged(); } }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}