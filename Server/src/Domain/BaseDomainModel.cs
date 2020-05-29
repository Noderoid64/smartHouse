using System;

using Server.Domain.Entity;
using Server.Infrastructure.Persistance;

namespace Server.Domain {
    public abstract class BaseDomainModel <TEntity> where TEntity : class, new () {
        protected TEntity entity;

        public BaseDomainModel (TEntity entity) {
            if (entity != null)
            this.entity = entity;
            else {
                throw new Exception("Try to create domain model without entity");
            }
        }

        public void Persist(BaseRepository<TEntity> repository) {
            repository.Update(entity);
            repository.Save();
        }
    }
}