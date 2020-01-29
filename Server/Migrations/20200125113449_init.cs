using Microsoft.EntityFrameworkCore.Migrations;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

namespace server.Migrations
{
    public partial class init : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "DEVICE",
                columns: table => new
                {
                    id = table.Column<int>(nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    TYPE = table.Column<int>(nullable: false),
                    MAJOR_VERSION = table.Column<int>(nullable: true, defaultValue: 0),
                    MINOR_VERSION = table.Column<int>(nullable: true, defaultValue: 0),
                    PATCH_VERSION = table.Column<int>(nullable: true, defaultValue: 0),
                    IP = table.Column<string>(nullable: false),
                    MAC = table.Column<string>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_DEVICE", x => x.id);
                });

            migrationBuilder.InsertData(
                table: "DEVICE",
                columns: new[] { "id", "IP", "MAC", "TYPE", "MAJOR_VERSION" },
                values: new object[] { 1, "192.168.0.1", "12-12-12-12-12-12", 0, 1 });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "DEVICE");
        }
    }
}
