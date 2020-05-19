using Microsoft.EntityFrameworkCore.Migrations;

namespace server.Migrations
{
    public partial class addNewDeviceEntities : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AlterColumn<bool>(
                name: "IS_NEW",
                table: "DEVICE",
                nullable: true,
                defaultValue: true,
                oldClrType: typeof(bool),
                oldType: "boolean",
                oldDefaultValue: false);

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1,
                columns: new[] { "IP", "IS_NEW", "MAC", "MAJOR_VERSION" },
                values: new object[] { "192.168.0.124", true, "12:12:12:12:12:12", 1 });

            migrationBuilder.InsertData(
                table: "DEVICE",
                columns: new[] { "id", "IP", "IS_NEW", "MAC", "TYPE", "MAJOR_VERSION", "MINOR_VERSION", "PATCH_VERSION" },
                values: new object[,]
                {
                    { 3, "192.168.0.126", false, "16:16:16:16:16:16", 0, 2, 1, 5 },
                    { 2, "192.168.0.125", true, "15:15:15:15:15:15", 0, 1, 4, 13 }
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 3);

            migrationBuilder.AlterColumn<bool>(
                name: "IS_NEW",
                table: "DEVICE",
                type: "boolean",
                nullable: false,
                defaultValue: false,
                oldClrType: typeof(bool),
                oldNullable: true,
                oldDefaultValue: true);

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1,
                columns: new[] { "IP", "MAC", "MAJOR_VERSION" },
                values: new object[] { "192.168.0.1", "12-12-12-12-12-12", 1 });
        }
    }
}
