using Microsoft.EntityFrameworkCore.Migrations;

namespace server.Migrations
{
    public partial class ss : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 3);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "DEVICE",
                columns: new[] { "id", "IP", "IS_NEW", "MAC", "TYPE", "MAJOR_VERSION" },
                values: new object[] { 1, "192.168.0.124", true, "12:12:12:12:12:12", 0, 1 });

            migrationBuilder.InsertData(
                table: "DEVICE",
                columns: new[] { "id", "IP", "IS_NEW", "MAC", "TYPE", "MAJOR_VERSION", "MINOR_VERSION", "PATCH_VERSION" },
                values: new object[,]
                {
                    { 2, "192.168.0.125", true, "15:15:15:15:15:15", 0, 1, 4, 13 },
                    { 3, "192.168.0.126", false, "16:16:16:16:16:16", 2, 2, 1, 5 }
                });
        }
    }
}
