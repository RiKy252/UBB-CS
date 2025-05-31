using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace VacationAppNET.Models
{
    public class Destination
    {
        public int Id { get; set; }

        [Required]
        public string City { get; set; }

        [Required]
        public string Country { get; set; }

        [Required]
        public string Description { get; set; }

        [Required]
        public string TouristAttractions { get; set; }

        [Required]
        [Display(Name = "Cost per Day")]
        public decimal Cost_per_day { get; set; }
    }
}
