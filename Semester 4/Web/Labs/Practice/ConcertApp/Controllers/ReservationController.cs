using ConcertApp.Data;
using ConcertApp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace ConcertApp.Controllers
{
    public class ReservationController : Controller
    {
        private readonly AppDbContext _context;
        private const string SessionKeyName = "Person";
        private const string SessionKeyDate = "Date";
        private const string SessionKeyCity = "City";

        public ReservationController(AppDbContext context)
        {
            _context = context;
        }

        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult BeginReservation(string person, DateTime date, string destinationCity)
        {
            HttpContext.Session.SetString(SessionKeyName, person);
            HttpContext.Session.SetString(SessionKeyDate, date.ToString("yyyy-MM-dd"));
            HttpContext.Session.SetString(SessionKeyCity, destinationCity);
            return RedirectToAction("Flights");
        }

        public async Task<IActionResult> Flights()
        {
            var person = HttpContext.Session.GetString(SessionKeyName);
            if (string.IsNullOrEmpty(person)) return RedirectToAction("Index");

            var date = DateTime.Parse(HttpContext.Session.GetString(SessionKeyDate));
            var city = HttpContext.Session.GetString(SessionKeyCity);

            var flights = await _context.Flights
                .Where(f => f.Date == date && f.DestinationCity == city && f.AvailableSeats > 0)
                .ToListAsync();

            return View(flights);
        }

        public async Task<IActionResult> ReserveFlight(int id)
        {
            var person = HttpContext.Session.GetString(SessionKeyName);
            var flight = await _context.Flights.FindAsync(id);

            if (flight != null && flight.AvailableSeats > 0)
            {
                flight.AvailableSeats--;
                _context.Reservations.Add(new Reservation { Person = person, Type = "Flight", IdReservedResource = id });
                await _context.SaveChangesAsync();
            }

            return RedirectToAction("Flights");
        }

        public async Task<IActionResult> Hotels()
        {
            var person = HttpContext.Session.GetString(SessionKeyName);
            if (string.IsNullOrEmpty(person)) return RedirectToAction("Index");

            var date = DateTime.Parse(HttpContext.Session.GetString(SessionKeyDate));
            var city = HttpContext.Session.GetString(SessionKeyCity);

            var hotels = await _context.Hotels
                .Where(h => h.Date == date && h.City == city && h.AvailableRooms > 0)
                .ToListAsync();

            return View(hotels);
        }

        public async Task<IActionResult> ReserveHotel(int id)
        {
            var person = HttpContext.Session.GetString(SessionKeyName);
            var hotel = await _context.Hotels.FindAsync(id);

            if (hotel != null && hotel.AvailableRooms > 0)
            {
                hotel.AvailableRooms--;
                _context.Reservations.Add(new Reservation { Person = person, Type = "Hotel", IdReservedResource = id });
                await _context.SaveChangesAsync();
            }

            return RedirectToAction("Hotels");
        }

        public async Task<IActionResult> CancelAll()
        {
            var person = HttpContext.Session.GetString(SessionKeyName);
            var reservations = _context.Reservations.Where(r => r.Person == person);
            foreach (var res in reservations)
            {
                if (res.Type == "Flight")
                {
                    var flight = await _context.Flights.FindAsync(res.IdReservedResource);
                    if (flight != null) flight.AvailableSeats++;
                }
                else if (res.Type == "Hotel")
                {
                    var hotel = await _context.Hotels.FindAsync(res.IdReservedResource);
                    if (hotel != null) hotel.AvailableRooms++;
                }
            }

            _context.Reservations.RemoveRange(reservations);
            await _context.SaveChangesAsync();

            return RedirectToAction("Flights");
        }

    }
}
