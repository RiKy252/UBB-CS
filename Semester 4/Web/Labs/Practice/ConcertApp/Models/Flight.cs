namespace ConcertApp.Models
{
    public class Flight
    {
        public int FlightId { get; set; }
        public DateTime Date { get; set; }
        public string DestinationCity { get; set; }
        public int AvailableSeats { get; set; }
    }

}
