using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using VacationAppNET.Data;
using VacationAppNET.Models;

namespace VacationAppNET.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class DestinationsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public DestinationsController(ApplicationDbContext context)
        {
            _context = context;
        }

        [HttpGet]
        public async Task<IActionResult> GetDestinations([FromQuery] string? countryFilter, [FromQuery] int page = 1)
        {
            const int pageSize = 8;
            var query = _context.Destinations.AsQueryable();

            if (!string.IsNullOrWhiteSpace(countryFilter))
            {
                query = query.Where(d => d.Country.Contains(countryFilter));
            }

            var totalItems = await query.CountAsync();
            var totalPages = (int)Math.Ceiling(totalItems / (double)pageSize);

            var destinations = await query
                .Skip((page - 1) * pageSize)
                .Take(pageSize)
                .ToListAsync();

            return Ok(new
            {
                destinations,
                page,
                totalPages
            });
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
        public async Task<IActionResult> CreateDestination(Destination destination)
        {
            _context.Destinations.Add(destination);
            await _context.SaveChangesAsync();
            return CreatedAtAction(nameof(GetDestination), new { id = destination.Id }, destination);
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> UpdateDestination(int id, Destination destination)
        {
            if (id != destination.Id)
            {
                return BadRequest();
            }

            _context.Entry(destination).State = EntityState.Modified;
            await _context.SaveChangesAsync();
            return NoContent();
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteDestination(int id)
        {
            var destination = await _context.Destinations.FindAsync(id);
            if (destination == null)
            {
                return NotFound();
            }

            _context.Destinations.Remove(destination);
            await _context.SaveChangesAsync();
            return NoContent();
        }
    }
}
