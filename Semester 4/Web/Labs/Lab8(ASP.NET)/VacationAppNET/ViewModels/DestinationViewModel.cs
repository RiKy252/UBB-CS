using VacationAppNET.Models;

namespace VacationAppNET.ViewModels
{
    public class DestinationViewModel
    {
        public List<Destination> Destinations { get; set; } = new();
        public string Filter { get; set; } = "";
        public int CurrentPage { get; set; } = 1;
        public int TotalPages { get; set; } = 1;
    }
}
