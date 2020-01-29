using System;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using Microsoft.EntityFrameworkCore;

using Server.Domain.Repositories;
using Server.Persistance.Contexts;
using Serilog;
using Serilog.Events;

namespace Server.Persistance.Repositories
{
    public abstract class BaseRepository<TEntity> : IBaseRepository<TEntity> where TEntity : class
    {
        protected AppDbContext context;
        private DbSet<TEntity> dbSet;

        public BaseRepository(AppDbContext context, DbSet<TEntity> dbSet)
        {
            this.context = context;
            this.dbSet = dbSet;
        }

        public virtual Task<List<TEntity>> GetWithRawSql(string query, params object[] parameters)
        {
            return dbSet.FromSqlRaw(query, parameters).ToListAsync();
        }

        public virtual IEnumerable<TEntity> Get(Expression<Func<TEntity, bool>> filter)
        {
            IQueryable<TEntity> query = dbSet;
            return query.Where(filter).ToList();
        }

        public virtual TEntity GetByID(object id)
        {
            return dbSet.Find(id);
        }

        public virtual async void InsertAsync(TEntity entity)
        {
            if (Log.IsEnabled(LogEventLevel.Debug)) {
                Log.Debug("BaseRepository: " + entity.ToString());
            }
            await dbSet.AddAsync(entity);
        }

        public virtual void Insert(TEntity entity) {
            dbSet.Add(entity);
        }

        public virtual async void DeleteAsync(int id)
        {
            Delete(await dbSet.FindAsync(id));
        }

        public virtual void Delete(TEntity entityToDelete)
        {
            if (context.Entry(entityToDelete).State == EntityState.Detached)
            {
                dbSet.Attach(entityToDelete);
            }
            dbSet.Remove(entityToDelete);
        }

        public virtual void Update(TEntity entityToUpdate)
        {
            dbSet.Attach(entityToUpdate);
            context.Entry(entityToUpdate).State = EntityState.Modified;
        }

        public virtual void Save() {
            this.context.SaveChanges();
        }

        public virtual void SaveAsync() {
            this.context.SaveChangesAsync();
        }
    }
}