SOCIAL NETWORK - LAB 5

DESCRIPTION

This is a Java console application for managing users and friendships. It continues the previous lab project and adds PostgreSQL storage using JDBC. The application can still use in-memory or file storage. The storage type is selected from config.properties.

FEATURES

1. Display all users.
2. Add a user with first name, last name and optional profile information.
3. Delete a user and all friendships connected to that user.
4. Add a friendship between two existing users.
5. Remove a friendship.
6. Display all friendships.
7. Display the number of communities.
8. Display all communities.
9. Display the most sociable community.

PROJECT STRUCTURE

domain.model contains the User, Friendship, FriendshipId, Community and Entity classes.
validation contains validation rules for users and friendships.
repository contains the repository interfaces and the generic in-memory implementation.
repository.memory contains repositories that store data in memory.
repository.file contains repositories that read and write text files.
repository.database contains the JDBC repositories and common JDBC support.
service contains the application logic and community calculations.
ui contains the console menu.
exception contains application exceptions.
sql contains the PostgreSQL scripts used to create the database and tables.

DATABASE

The PostgreSQL database is named socialnetwork.

The users table contains an identity-generated ID, first name and last name. The project already has optional email, birth date and description fields, so these are stored in additional columns. The friendships table contains the two user IDs and the date when the friendship was created.

The friendships table has a composite primary key made from id1 and id2. Both columns reference users(id), and the CHECK constraint requires id1 to be smaller than id2. FriendshipId normalizes the two IDs in the same order.

The project uses explicit deletion of friendships in SocialNetworkService before deleting a user. I chose this approach instead of ON DELETE CASCADE because the same service logic also works with FILE and MEMORY storage. The foreign keys still prevent invalid references in the database.

JDBC

UserDbRepository and FriendshipDbRepository implement the repository operations using JDBC. Connections are obtained with DriverManager.getConnection(url, user, password). Connection, PreparedStatement and ResultSet are handled with try-with-resources.

All SQL values are passed through PreparedStatement parameters. They are not concatenated into SQL strings. This also means that text such as '); DROP TABLE users; -- is stored as a normal name instead of being executed as SQL.

When a user is added in DATABASE mode, the application does not generate the ID. PostgreSQL generates it through the identity column, and UserDbRepository reads it using RETURNING id. The saved User object returned to the service contains that generated ID.

The repository update method returns Optional.empty() when no row with the given ID exists. The delete method returns the deleted entity in an Optional, or Optional.empty() when the ID does not exist. Null arguments are rejected with IllegalArgumentException. Validation is performed before save and update.

Foreign key violations, other database constraint violations and connection errors are converted into RepositoryException messages. The console UI displays these messages without printing a stack trace.

CONFIGURATION

The application reads src/main/resources/config.properties.

The repository.type property accepts:
- DATABASE
- FILE
- MEMORY

For PostgreSQL, db.url, db.user and db.password must be set. The default URL is jdbc:postgresql://localhost:5432/socialnetwork.

config.example.properties is a template. The local config.properties file contains the actual connection settings and is ignored by Git. Do not commit a real database password.

For FILE storage, file.users and file.friendships contain the paths to the text files. MEMORY storage keeps the data only while the application is running.

POSTGRESQL SETUP

1. Make sure the PostgreSQL server is installed and running. IntelliJ's Database tool window is only a client for connecting to the server; it does not replace the PostgreSQL server.
2. In IntelliJ, open the Database tool window and add a PostgreSQL data source.
3. Use localhost as the host and 5432 as the port. Enter the PostgreSQL username and password. Download the JDBC driver when IntelliJ asks for it, then test the connection.
4. Open a query console connected to the default postgres database and run sql/01_create_database.sql. If socialnetwork already exists, do not run the CREATE DATABASE statement again.
5. Create or select a data source connected to the socialnetwork database.
6. Open sql/02_create_tables.sql in a query console connected to socialnetwork and run it.
7. Copy config.example.properties to config.properties if config.properties does not exist.
8. Set db.user and db.password to the credentials of your local PostgreSQL server.
9. Keep repository.type=DATABASE.

RUNNING THE APPLICATION

Open the project in IntelliJ IDEA using the build.gradle.kts file. Wait for Gradle to sync and download the PostgreSQL JDBC driver. Run the Main class or use the Gradle run task.

The project targets Java 8 source compatibility. Gradle itself requires a supported JDK to run.

To test persistence, add users and friendships, stop the application and start it again. The data should still be present in PostgreSQL.

To test the other storage options, change repository.type in config.properties to FILE or MEMORY and restart the application.

DEMONSTRATION CHECKLIST

1. Add, display, update through the repository and delete records, then verify the rows in pgAdmin or IntelliJ Database.
2. Add a user and verify that PostgreSQL assigns the ID.
3. Restart the application and check that the data is still present.
4. Change repository.type and show that the selected storage changes.
5. Stop the PostgreSQL server and verify that the application displays a readable connection error.
6. Add a name containing '); DROP TABLE users; -- and verify that it is stored as text and the users table still exists.

COMMUNITY CALCULATION

The network is treated as an undirected graph. Users are vertices and friendships are edges. SocialNetworkService uses Union-Find to find connected components. Users without friends are also included as communities with one member.

The diameter of a community is the largest shortest-path distance between two members. BFS is used to calculate shortest-path distances. The most sociable community is selected by diameter, then by number of members, and finally by the smallest user ID.

JAVA FEATURES

The project uses Java 8 features such as functional interfaces, lambda expressions, method references, Predicate, Function, Optional, Stream API and collectors. File repositories use Files.lines and Files.write. AbstractFileRepository keeps the common file operations using the Template Method design pattern.
