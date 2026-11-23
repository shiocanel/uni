package util.paging;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Immutable result of a paged repository query.
 *
 * @param <E> type of the elements contained in the page
 */
public final class Page<E> {
    private final List<E> elementsOnPage;
    private final long totalNumberOfElements;

    /**
     * Creates a page containing the selected elements and the total matching element count.
     *
     * @param elementsOnPage elements returned for this page
     * @param totalNumberOfElements total number of matching elements across all pages
     * @throws IllegalArgumentException when the list is null, the total is negative,
     *                                  or the page contains more elements than the total
     */
    public Page(List<E> elementsOnPage, long totalNumberOfElements) {
        if (elementsOnPage == null) {
            throw new IllegalArgumentException("Page elements cannot be null.");
        }
        if (totalNumberOfElements < 0) {
            throw new IllegalArgumentException("Total number of elements cannot be negative.");
        }
        if (elementsOnPage.size() > totalNumberOfElements) {
            throw new IllegalArgumentException("A page cannot contain more elements than the total.");
        }
        this.elementsOnPage = Collections.unmodifiableList(new ArrayList<E>(elementsOnPage));
        this.totalNumberOfElements = totalNumberOfElements;
    }

    /**
     * Returns the elements belonging to this page.
     *
     * @return unmodifiable list of page elements
     */
    public List<E> getElementsOnPage() {
        return elementsOnPage;
    }

    /**
     * Returns the total number of matching elements, not just the current page size.
     *
     * @return total number of elements
     */
    public long getTotalNumberOfElements() {
        return totalNumberOfElements;
    }

    /**
     * Calculates the number of pages for the supplied page size.
     * An empty result has zero pages.
     *
     * @param pageSize number of elements per page
     * @return total number of pages
     * @throws IllegalArgumentException when pageSize is not positive
     */
    public long getTotalNumberOfPages(int pageSize) {
        if (pageSize <= 0) {
            throw new IllegalArgumentException("Page size must be positive.");
        }
        return totalNumberOfElements == 0
                ? 0
                : ((totalNumberOfElements - 1) / pageSize) + 1;
    }

    /**
     * Indicates whether this page contains any elements.
     *
     * @return true when the page is empty
     */
    public boolean isEmpty() {
        return elementsOnPage.isEmpty();
    }
}
