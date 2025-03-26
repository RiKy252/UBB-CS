using Microsoft.UI;
using Microsoft.UI.Xaml.Media;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StocksHomepage
{
    public class Stock
    {
        public required string Symbol { get; set; }
        public required string Name { get; set; }
        public required string Price { get; set; }
        public required string Change { get; set; }
        public SolidColorBrush ChangeColor
        {
            get => Change.StartsWith("+") ? new SolidColorBrush(Colors.Green) : new SolidColorBrush(Colors.Red);
        }
        public required bool isFavorite { get; set; }
        public string FavoriteStar
        {
            get => isFavorite ? "★" : "☆";
        }
    }
}
