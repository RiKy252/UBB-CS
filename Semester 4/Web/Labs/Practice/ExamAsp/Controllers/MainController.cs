using ExamAsp.Data;
using ExamAsp.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Threading.Tasks;

namespace ExamAsp.Controllers
{
    public class MainController : Controller
    {
        private readonly AppDbContext _context;
        private const string SessionKeyUsername = "Username";
        private int OrderCount = 0;

        public MainController(AppDbContext context)
        {
            _context = context;
        }

        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> BeginOrder(string username)
        {
            HttpContext.Session.SetString(SessionKeyUsername, username);
            return RedirectToAction("Products");
        }

        public async Task<IActionResult> Products()
        {
            var person = HttpContext.Session.GetString(SessionKeyUsername);
            if (string.IsNullOrEmpty(person)) return RedirectToAction("Index");


            var products = await _context.Products
                .ToListAsync();

            return View(products);
        }

        public async Task<IActionResult> OrderProduct(int id)
        {
            var person = HttpContext.Session.GetString(SessionKeyUsername);
            var product = await _context.Products.FindAsync(id);

            var userList = await _context.Users.Where(x => x.Username == person).ToListAsync();
            var user = userList.First();

            int userId = user.UserId;
            double totalPrice;

            var pName = product.ProductName;
            string[] words = pName.Split('-');
            var category = words[0];

            var orders = _context.OrderItems;
            List<OrderItem> orderArr = new List<OrderItem>();

            foreach (var order in orders)
            {
                orderArr.Add(order);
            }

            int sameCategoriesOrdered = 0;
            var size = orderArr.Count;
            Product prdToCheck;
            
            if (size > 3)
                for (int i = 1; i <= 3; i++)
                {
                    OrderItem lastOrder = orderArr[size - i];
                    prdToCheck = _context.Products.Where(x => x.ProductId == lastOrder.ProductId).FirstOrDefault();
                    if (prdToCheck.ProductName.Contains(category))
                        sameCategoriesOrdered++;
                }

            if (sameCategoriesOrdered == 3)
            {
                Console.WriteLine("3 orders of same cateegory");
                return RedirectToAction("Products");
            }
            else
            {
                if (product != null)
                {
                    if (OrderCount > 3)
                    {
                        totalPrice = product.Price * 1.10;
                    }
                    else
                    {
                        totalPrice = product.Price;
                    }
                    var newOrder = new Order { UserId = userId, TotalPrice = totalPrice };
                    _context.Orders.Add(newOrder);
                    _context.SaveChanges();
                    int orderId = newOrder.OrderId;
                    _context.OrderItems.Add(new OrderItem { OrderId = orderId, ProductId = id });
                    await _context.SaveChangesAsync();
                    OrderCount++;
                }

                return RedirectToAction("Products");
            }
        }

    }
}
