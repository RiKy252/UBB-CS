using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StocksHomepage
{
    class HomepageService
    {
        // Filter stocks based on search query
        public List<Stock> FilterStocks(List<Stock> stocks, string query)
        {
            return stocks.Where(stock =>
                stock.Name.ToLower().Contains(query.ToLower()) ||
                stock.Symbol.ToLower().Contains(query.ToLower())).ToList();
        }

        // Sort stocks based on the selected option
        public List<Stock> SortStocks(List<Stock> stocks, string sortOption)
        {
            switch (sortOption)
            {
                case "Sort by Name":
                    return stocks.OrderBy(stock => stock.Name).ToList();
                case "Sort by Price":
                    return stocks.OrderBy(stock => decimal.Parse(stock.Price.Trim('$'))).ToList();
                case "Sort by Change":
                    return stocks.OrderBy(stock => decimal.Parse(stock.Change.Trim('%'))).ToList();
                default:
                    return stocks;
            }
        }

        // Add a stock to the favorites list
        public void AddToFavorites(List<Stock> allStocks, List<Stock> favoriteStocks, Stock stock)
        {
            allStocks.Remove(stock);
            favoriteStocks.Add(stock);
            stock.isFavorite = true;
        }

        // Remove a stock from the favorites list
        public void RemoveFromFavorites(List<Stock> allStocks, List<Stock> favoriteStocks, Stock stock)
        {
            favoriteStocks.Remove(stock);
            allStocks.Add(stock);
            stock.isFavorite = false;
        }
    }
}
