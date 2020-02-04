using Microsoft.EntityFrameworkCore.Migrations;

namespace server.Migrations
{
    public partial class addIsNewToDeviceEntity : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<bool>(
                name: "IS_NEW",
                table: "DEVICE",
                nullable: false,
                defaultValue: false);

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1,
                column: "MAJOR_VERSION",
                value: 1);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "IS_NEW",
                table: "DEVICE");

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1,
                column: "MAJOR_VERSION",
                value: 1);
        }
    }
}
