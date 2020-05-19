using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using Server.Model.Entity;
using Server.Model.Value;

namespace Server.Persistance.Contexts
{
    public class AppDbContext : DbContext
    {

        public DbSet<DeviceEntity> deviceEntities { get; set; }

        public AppDbContext (DbContextOptions options) : base (options) {}

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseNpgsql(@"Host=localhost;Port=5432;Database=smartDb;Username=postgres;Password=qwertyui");
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
            builder.Entity<DeviceEntity>().Property(e => e.isNew).HasColumnName("IS_NEW");
            builder.Entity<DeviceEntity>().Property(e => e.lastPing).HasColumnName("LAST_PING").IsRequired();
            builder.Entity<DeviceEntity>().OwnsOne(e => e.version).Property(p => p.major).HasColumnName("MAJOR_VERSION").HasDefaultValue(0);
            builder.Entity<DeviceEntity>().OwnsOne(e => e.version).Property(p => p.minor).HasColumnName("MINOR_VERSION").HasDefaultValue(0);
            builder.Entity<DeviceEntity>().OwnsOne(e => e.version).Property(p => p.patch).HasColumnName("PATCH_VERSION").HasDefaultValue(0);

            // builder.Entity<DeviceEntity>(e => {
            //     e.HasData( new DeviceEntity {id = 1, macAddress="12:12:12:12:12:12", ipAddress="192.168.0.124", isNew=true, type = DeviceType.SOCKET });
            //     e.HasData( new DeviceEntity {id = 2, macAddress="15:15:15:15:15:15", ipAddress="192.168.0.125", isNew=true, type = DeviceType.SOCKET });
            //     e.HasData( new DeviceEntity {id = 3, macAddress="16:16:16:16:16:16", ipAddress="192.168.0.126", isNew=false, type = DeviceType.LED });
            //     e.OwnsOne(p => p.version).HasData(new { major = 1, minor = 0, patch = 0, DeviceEntityid = 1});
            //     e.OwnsOne(p => p.version).HasData(new { major = 1, minor = 4, patch = 13, DeviceEntityid = 2});
            //     e.OwnsOne(p => p.version).HasData(new { major = 2, minor = 1, patch = 5, DeviceEntityid = 3});
            // });

        }
    }
}