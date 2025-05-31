using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace VacationAppNET.Migrations
{
    /// <inheritdoc />
    public partial class UpdateDb : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "Price",
                table: "Destinations",
                newName: "Cost_per_day");

            migrationBuilder.RenameColumn(
                name: "ImageUrl",
                table: "Destinations",
                newName: "TouristAttractions");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "TouristAttractions",
                table: "Destinations",
                newName: "ImageUrl");

            migrationBuilder.RenameColumn(
                name: "Cost_per_day",
                table: "Destinations",
                newName: "Price");
        }
    }
}
