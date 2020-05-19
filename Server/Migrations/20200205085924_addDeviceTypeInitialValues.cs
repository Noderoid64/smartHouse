using Microsoft.EntityFrameworkCore.Migrations;

namespace server.Migrations
{
    public partial class addDeviceTypeInitialValues : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1,
                columns: new[] { "IS_NEW", "MAJOR_VERSION" },
                values: new object[] { true, 1 });

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 2,
                columns: new[] { "IS_NEW", "MAJOR_VERSION", "MINOR_VERSION", "PATCH_VERSION" },
                values: new object[] { true, 1, 4, 13 });

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 3,
                columns: new[] { "IS_NEW", "TYPE", "MAJOR_VERSION", "MINOR_VERSION", "PATCH_VERSION" },
                values: new object[] { false, 2, 2, 1, 5 });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 1,
                columns: new[] { "IS_NEW", "MAJOR_VERSION" },
                values: new object[] { true, 1 });

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 2,
                columns: new[] { "IS_NEW", "MAJOR_VERSION", "MINOR_VERSION", "PATCH_VERSION" },
                values: new object[] { true, 1, 4, 13 });

            migrationBuilder.UpdateData(
                table: "DEVICE",
                keyColumn: "id",
                keyValue: 3,
                columns: new[] { "IS_NEW", "TYPE", "MAJOR_VERSION", "MINOR_VERSION", "PATCH_VERSION" },
                values: new object[] { false, 0, 2, 1, 5 });
        }
    }
}
