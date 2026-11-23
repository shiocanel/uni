# SOCIAL NETWORK - LAB 6

## DESCRIPTION

This is a Java console application for managing users and friendships. It continues the previous laboratory project and includes PostgreSQL persistence through JDBC, as well as in-memory and file-based storage.

Lab 6 adds database paging on top of the Lab 5 implementation. When `repository.type=DATABASE`, users and the friends of a selected user are retrieved in pages. The page size is read from `config.properties`. The `MEMORY` and `FILE` implementations keep their original behaviour and display complete lists.

The application is designed around repository interfaces. `SocialNetworkService` contains the application logic and does not contain SQL. `RepositoryFactory` selects the concrete repository implementations based on the configuration.

## FEATURES

1. Display all users. In `DATABASE` mode, users are displayed page by page.
2. Add a user with first name, last name and optional profile information.
3. Delete a user and all friendships connected to that user.
4. Add a friendship between two existing users.
5. Remove a friendship.
6. Display all friendships.
7. Display the number of communities.
8. Display the most sociable community.
9. Display all communities.
10. Display the friends of a selected user. In `DATABASE` mode, the friends are displayed page by page.

In the paged screens, use:

- `n` to move to the next page;
- `p` to move to the previous page;
- `q` to return to the main menu.

The UI displays the current page, the total number of pages and the total number of matching elements. Page numbers shown to the user start at 1, while the paging API uses zero-based page numbers internally.

## PROJECT STRUCTURE

- `domain.model` contains the `User`, `Friendship`, `FriendshipId`, `Community` and `Entity` classes. These represent the application's domain entities and values.
- `validation` contains validation rules for users and friendships.
- `repository` contains repository contracts, the generic repository implementation, the repository factory and the paging repository interfaces.
- `repository.memory` contains repositories that store data in memory.
- `repository.file` contains repositories that read and write text files.
- `repository.database` contains the JDBC repositories and common JDBC connection/error-handling support.
- `service` contains the application logic, user/friendship operations and community calculations. It also exposes paging operations to the UI without containing SQL.
- `ui` contains the console menu, user input handling, page navigation and display logic.
- `exception` contains application exceptions.
- `util.paging` contains the `Pageable` request object and the generic `Page<E>` result object.
- `sql` contains the PostgreSQL scripts used to create the database and tables.

## DATABASE

The PostgreSQL database is named `socialnetwork`.

The `users` table contains an identity-generated ID, first name and last name. The project also stores the optional email, birth date and description fields in additional columns. The `friendships` table contains the two user IDs and the date when the friendship was created.

The `friendships` table has a composite primary key made from `id1` and `id2`. Both columns reference `users(id)`, and the `CHECK` constraint requires `id1` to be smaller than `id2`. `FriendshipId` normalizes the two IDs into the same order.

The project explicitly deletes a user's friendships in `SocialNetworkService` before deleting the user. This approach is used instead of `ON DELETE CASCADE` so the same service-level deletion logic also works with `FILE` and `MEMORY` storage. The foreign keys still prevent invalid references in the database.

## JDBC

`UserDbRepository` and `FriendshipDbRepository` implement repository operations using JDBC. Connections are obtained with `DriverManager.getConnection(url, user, password)`. `Connection`, `PreparedStatement` and `ResultSet` resources are managed with try-with-resources.

SQL values are passed through `PreparedStatement` parameters and are not concatenated into SQL strings. For example, text such as `'); DROP TABLE users; --` is treated as a normal name rather than executable SQL.

When a user is added in `DATABASE` mode, the application does not generate the ID. PostgreSQL generates it through the identity column, and `UserDbRepository` retrieves it using `RETURNING id`. The saved `User` object returned to the service contains that generated ID.

Repository `update` operations return an `Optional` containing the updated entity or `Optional.empty()` when no row with the specified ID exists. Delete operations return the deleted entity in an `Optional`, or `Optional.empty()` when the ID does not exist. Null arguments are rejected with `IllegalArgumentException`, and validation is performed before save and update.

SQL exceptions are converted into `RepositoryException` messages. Connection errors and database constraint violations are reported by the console UI without printing a stack trace.

## PAGING - LAB 6

Paging is enabled only when `repository.type=DATABASE`.

### Paging model

- `Pageable(pageNumber, pageSize)` describes the requested page. `pageNumber` is zero-based and cannot be negative. `pageSize` must be strictly positive. The object calculates the SQL offset as `pageNumber * pageSize` using a `long` value.
- `Page<E>(elementsOnPage, totalNumberOfElements)` contains the elements returned for the requested page and the total number of matching elements across all pages. It exposes the elements as an unmodifiable list.
- `Page<E>` calculates the total number of pages. When the total number of matching elements is zero, the total number of pages is zero.
- `PagingRepository<ID, E>` extends `Repository<ID, E>` and adds `findAllOnPage(Pageable pageable)` for paged retrieval of entities.
- `FriendshipPagingRepository` adds the specialised `findFriendsOnPage(userId, pageable)` operation, which returns the users who are friends with the selected user.

A negative page number or a non-positive page size causes `IllegalArgumentException`. A valid request for a page beyond the last page returns an empty page while preserving the total number of matching elements.

### Paging users

`UserDbRepository` implements `PagingRepository<Long, User>`. It retrieves a page with:

```sql
SELECT id, first_name, last_name, email, birth_date, description
FROM users
ORDER BY id
LIMIT ? OFFSET ?;
```

It also executes `COUNT(*)` to obtain the total number of users. Both operations use the same JDBC connection. Paging is performed by PostgreSQL, so the application does not load the complete users table into Java just to display one page.

### Paging a user's friends

`FriendshipDbRepository` implements `FriendshipPagingRepository`. It retrieves the selected user's friends as `User` objects using one SQL statement with a `JOIN` between `friendships` and `users`, the condition `id1 = ? OR id2 = ?`, and SQL-level `LIMIT` and `OFFSET` paging.

The statement uses common table expressions to calculate the total number of friends and select the requested page. The count is preserved even when the requested page has no rows or the user has no friends. This allows the application to distinguish an empty result from a page that is out of range while retaining the correct total count.

### User interface behaviour

- Menu option 1 displays users. It uses database paging in `DATABASE` mode and displays the complete list in `FILE` and `MEMORY` modes.
- Menu option 10 asks for a user ID and displays that user's friends. It uses database paging in `DATABASE` mode and displays the complete friend list in `FILE` and `MEMORY` modes.
- Menu option 6 continues to display all friendship relationships, as in Lab 5.
- The UI handles navigation and printing only. SQL statements remain inside the database repository classes.

For an empty collection, the UI displays `Pagina 0 din 0`. For a page with elements, it displays `Pagina x din y` and the total element count.

## CONFIGURATION

The application reads `src/main/resources/config.properties`.

The `repository.type` property accepts:

- `DATABASE`
- `FILE`
- `MEMORY`

For PostgreSQL, `db.url`, `db.user` and `db.password` must be set. The default URL is `jdbc:postgresql://localhost:5432/socialnetwork`.

For database paging, add the following property:

```properties
paging.page-size=5
```

The value must be a positive integer. The property is required only when `repository.type=DATABASE`; the factory does not enable or load paging for `FILE` and `MEMORY` storage.

`config.example.properties` is a template. The local `config.properties` file contains the actual connection settings and must be ignored by Git. Do not commit a real database password.

For `FILE` storage, `file.users` and `file.friendships` contain the paths to the text files. `MEMORY` storage keeps the data only while the application is running.

## POSTGRESQL SETUP

1. Make sure the PostgreSQL server is installed and running. IntelliJ's Database tool window is only a client for connecting to the server; it does not replace the PostgreSQL server.
2. In IntelliJ, open the Database tool window and add a PostgreSQL data source.
3. Use `localhost` as the host and `5432` as the port. Enter the PostgreSQL username and password. Download the JDBC driver when IntelliJ asks for it, then test the connection.
4. Open a query console connected to the default `postgres` database and run `sql/01_create_database.sql`. If `socialnetwork` already exists, do not run the `CREATE DATABASE` statement again.
5. Create or select a data source connected to the `socialnetwork` database.
6. Open `sql/02_create_tables.sql` in a query console connected to `socialnetwork` and run it.
7. Copy `config.example.properties` to `config.properties` if `config.properties` does not exist.
8. Set `db.user` and `db.password` to the credentials of your local PostgreSQL server.
9. Set `repository.type=DATABASE` and add `paging.page-size=5` (or another positive integer).

## RUNNING THE APPLICATION

Open the project in IntelliJ IDEA using the `build.gradle.kts` file. Wait for Gradle to sync and download the PostgreSQL JDBC driver. Run the `Main` class or use the Gradle `run` task.

The project targets Java 8 source compatibility. Gradle itself requires a supported JDK to run.

To test persistence, add users and friendships, stop the application and start it again. The data should still be present in PostgreSQL.

To test the other storage options, change `repository.type` in `config.properties` to `FILE` or `MEMORY` and restart the application. Paging is not used in these two modes.

## DEMONSTRATION CHECKLIST

### Lab 5

1. Add, display, update through the repository and delete records, then verify the rows in pgAdmin or IntelliJ Database.
2. Add a user and verify that PostgreSQL assigns the ID.
3. Restart the application and check that the data is still present.
4. Change `repository.type` and show that the selected storage changes.
5. Stop the PostgreSQL server and verify that the application displays a readable connection error.
6. Add a name containing `'); DROP TABLE users; --` and verify that it is stored as text and the `users` table still exists.

### Lab 6

1. Set `repository.type=DATABASE` and `paging.page-size=5`.
2. Choose menu option 1 and verify the first page, next/previous navigation (`n` and `p`) and the `Pagina x din y` information.
3. Add a user, reopen option 1 and verify that the total element count and number of pages are updated.
4. Delete a user, reopen option 1 and verify that the total element count and number of pages are updated.
5. Choose menu option 10, enter the ID of a user with several friends and navigate through the pages.
6. Choose a user with no friends. The result should be empty and the UI should display `Pagina 0 din 0`.
7. Test a page request beyond the last page. The repository should return an empty list while preserving the correct `totalNumberOfElements`.
8. Change `repository.type` to `MEMORY` and `FILE`. The user list and selected user's friend list should be displayed completely, without paging.
9. Verify that `Pageable(-1, 5)` and `Pageable(0, 0)` throw `IllegalArgumentException`.

## COMMUNITY CALCULATION

The network is treated as an undirected graph. Users are vertices and friendships are edges. `SocialNetworkService` uses Union-Find to find connected components. Users without friends are also included as communities with one member.

The diameter of a community is the largest shortest-path distance between two members. BFS is used to calculate shortest-path distances. The most sociable community is selected by diameter, then by number of members, and finally by the smallest user ID.

## JAVA FEATURES

The project uses Java 8 features such as functional interfaces, lambda expressions, method references, `Predicate`, `Function`, `Optional`, the Stream API and collectors. File repositories use `Files.lines` and `Files.write`. `AbstractFileRepository` keeps common file operations using the Template Method design pattern.

## LAB 6 FILES ADDED OR MODIFIED

The following list describes the source files introduced or changed for paging. Other Lab 5 files remain unchanged.

### New files

- `src/main/java/util/paging/Pageable.java` — represents a page request using a zero-based page number and a positive page size. It validates both values and calculates the SQL `OFFSET`.
- `src/main/java/util/paging/Page.java` — represents the result of a page query. It stores an immutable list of returned elements and the total number of matching elements, and calculates the total page count.
- `src/main/java/repository/PagingRepository.java` — extends the generic `Repository` contract with `findAllOnPage(Pageable)` for repositories that support paging.
- `src/main/java/repository/FriendshipPagingRepository.java` — extends `FriendshipRepository` with `findFriendsOnPage(userId, pageable)`, a specialised operation for retrieving the users connected to one user's friendships.

### Modified files

- `src/main/java/Main.java` — passes the page size obtained from `RepositoryFactory` to `ConsoleUI`. The application still creates the validators, repositories and service as before.
- `src/main/java/repository/RepositoryFactory.java` — reads `paging.page-size` only when the configured repository type is `DATABASE`. It validates that the setting is a positive integer and exposes it through `getPageSize()`.
- `src/main/java/repository/database/UserDbRepository.java` — implements `PagingRepository<Long, User>`. It adds a page query ordered by ID with `LIMIT` and `OFFSET`, plus a `COUNT(*)` query. Both queries execute using the same JDBC connection and the result is wrapped in `Page<User>`.
- `src/main/java/repository/database/FriendshipDbRepository.java` — implements `FriendshipPagingRepository`. It adds one SQL statement that joins friendships to users, finds the other user in each friendship, applies `LIMIT` and `OFFSET` in PostgreSQL and returns the total friend count together with the selected page.
- `src/main/java/service/SocialNetworkService.java` — adds methods to check whether the active repositories support paging, retrieve a page of users and retrieve a page of a user's friends. It also adds the non-paged friend-list method used by `FILE` and `MEMORY`. The service delegates data access to repositories and contains no SQL.
- `src/main/java/ui/ConsoleUI.java` — receives the configured page size, paginates the user list and the selected user's friend list in `DATABASE` mode, handles `n`/`p`/`q` navigation and displays page information. In `FILE` and `MEMORY` modes it keeps the complete-list behaviour. It adds menu option 10 for the friends of a selected user; option 6 still displays all friendship relationships.

No change to `Repository.java`, the user model, the JDBC connection support class or the existing `FILE`/`MEMORY` repository implementations is required for the Lab 6 paging feature.
