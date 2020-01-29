using System.Linq.Expressions;
using System;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace Server.Domain.Repositories {
    public interface IBaseRepository<TEntity>
    {
        Task<List<TEntity>> GetWithRawSql(string query, params object[] parameters);

        IEnumerable<TEntity> Get(Expression<Func<TEntity, bool>> filter);

        TEntity GetByID(object id);

        void InsertAsync(TEntity entity);

        void Insert(TEntity entity);
        
        void DeleteAsync(int id);

        void Delete(TEntity entityToDelete);

        void Update(TEntity entityToUpdate);

        void Save();

        void SaveAsync();
    }
}