using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using Server.Domain.Model.Entity;
using Server.Domain.Model.Value;

namespace Server.Persistance.Contexts
{
    public class AppDbContext : DbContext
    {

        public DbSet<DeviceEntity> deviceEntities { get; set; }

        public AppDbContext (DbContextOptions options) : base (options) {}

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseNpgsql(@"Host=localhost;Database=smartDb;Username=postgres;Password=qwertyui");
        }

        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);

            builder.Entity<DeviceEntity>().ToTable("DEVICE");
            builder.Entity<DeviceEntity>().HasKey(e => e.id);
            builder.Entity<DeviceEntity>().Property(e => e.id).ValueGeneratedOnAdd();
            builder.Entity<DeviceEntity>().Property(e => e.type).HasColumnName("TYPE").IsRequired();
            builder.Entity<DeviceEntity>().Property(e => e.ipAddress).HasColumnName("IP").IsRequired();
            builder.Entity<DeviceEntity>().Property(e => e.macAddress).HasColumnName("MAC").IsRequired();
            builder.Entity<DeviceEntity>().OwnsOne(e => e.version).Property(p => p.major).HasColumnName("MAJOR_VERSION").HasDefaultValue(0);
            builder.Entity<DeviceEntity>().OwnsOne(e => e.version).Property(p => p.minor).HasColumnName("MINOR_VERSION").HasDefaultValue(0);
            builder.Entity<DeviceEntity>().OwnsOne(e => e.version).Property(p => p.patch).HasColumnName("PATCH_VERSION").HasDefaultValue(0);

            builder.Entity<DeviceEntity>(e => {
                e.HasData( new DeviceEntity {id = 1, macAddress="12-12-12-12-12-12", ipAddress="192.168.0.1" });
                e.OwnsOne(p => p.version).HasData(new { major = 1, minor = 0, patch = 0, DeviceEntityid = 1});
            });

        }
    }
}