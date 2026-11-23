package repository;

import domain.model.Entity;
import util.paging.Page;
import util.paging.Pageable;

/** Repository contract for retrieving entities in pages. */
public interface PagingRepository<ID, E extends Entity<ID>> extends Repository<ID, E> {
    /**
     * Retrieves one page of entities and the total number of matching entities.
     *
     * @param pageable zero-based page request
     * @return requested page and total element count
     * @throws IllegalArgumentException when pageable is null or invalid
     * @throws exception.RepositoryException when storage access fails
     */
    Page<E> findAllOnPage(Pageable pageable);
}
