package util.paging;

/**
 * Describes a zero-based page request.
 */
public final class Pageable {
    private final int pageNumber;
    private final int pageSize;

    /**
     * Creates a page request.
     *
     * @param pageNumber zero-based page number
     * @param pageSize number of elements requested per page
     * @throws IllegalArgumentException when pageNumber is negative or pageSize is not positive
     */
    public Pageable(int pageNumber, int pageSize) {
        if (pageNumber < 0) {
            throw new IllegalArgumentException("Page number cannot be negative.");
        }
        if (pageSize <= 0) {
            throw new IllegalArgumentException("Page size must be positive.");
        }
        this.pageNumber = pageNumber;
        this.pageSize = pageSize;
    }

    /**
     * Returns the zero-based page number.
     *
     * @return page number
     */
    public int getPageNumber() {
        return pageNumber;
    }

    /**
     * Returns the maximum number of elements requested per page.
     *
     * @return page size
     */
    public int getPageSize() {
        return pageSize;
    }

    /**
     * Calculates the zero-based SQL offset for this page.
     *
     * @return number of rows to skip
     */
    public long getOffset() {
        return (long) pageNumber * pageSize;
    }
}
