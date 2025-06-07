using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using VacationAppNET.Data;
using Microsoft.EntityFrameworkCore;
using VacationAppNET.Models;

namespace VacationAppNET.Controllers
{
    [Authorize]
    public class DestinationsMvcController : Controller
    {
        private readonly ApplicationDbContext _context;

        public DestinationsMvcController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            var destinations = await _context.Destinations.ToListAsync();
            return View(destinations);
        }

        public IActionResult Create()
        {
            return View();
        }

        [HttpGet("{id}")]
        public async Task<IActionResult> GetDestination(int id)
        {
            var destination = await _context.Destinations.FindAsync(id);
            if (destination == null)
            {
                return NotFound();
            }
            return Ok(destination);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create(Destination destination)
        {
            if (ModelState.IsValid)
            {
                _context.Add(destination);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(destination);
        }

        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var destination = await _context.Destinations.FindAsync(id);
            if (destination == null)
            {
                return NotFound();
            }
            return View(destination);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, Destination destination)
        {
            if (id != destination.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(destination);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!DestinationExists(destination.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(destination);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Delete(int id)
        {
            var destination = await _context.Destinations.FindAsync(id);
            if (destination != null)
            {
                _context.Destinations.Remove(destination);
                await _context.SaveChangesAsync();
            }
            return RedirectToAction(nameof(Index));
        }

        private bool DestinationExists(int id)
        {
            return _context.Destinations.Any(e => e.Id == id);
        }
    }
} 