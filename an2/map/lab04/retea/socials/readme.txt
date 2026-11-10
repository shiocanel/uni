# SOCIAL NETWORK

## DESCRIPTION

This is a Java project for managing a social network. The application runs in the console and allows users and friendships between them to be managed. Based on these friendships, the application calculates the communities in the network and identifies the most sociable community.

## FEATURES

1. Display all users.
2. Add a user with a first name, last name, email address, birth date and description. Additional profile information is optional.
3. Delete a user together with all their associated friendships.
4. Add a friendship between two existing users.
5. Delete a friendship.
6. Display all friendships.
7. Calculate the number of communities.
8. Display all communities.
9. Display the most sociable community.

Users can be searched by first name, last name or full name. The search is case-insensitive. If the entered name matches multiple users, the application asks for a more specific name.

## PROJECT STRUCTURE

The project is divided into several packages, each having a separate role.

1. `domain.model` contains the classes `User`, `Friendship`, `FriendshipId`, `Community` and `Entity`. These classes represent the data used by the application.
2. `validation` contains the validation rules for users and friendships.
3. `repository` contains the interfaces and the generic implementation for accessing data.
4. `repository.memory` contains the repositories that store data in memory.
5. `repository.file` contains the repositories that read and write data to files.
6. `repository.database` contains the classes prepared for the database version. The JDBC implementation will be added in a later lab.
7. `service` contains the application logic, operations for users and friendships, and community calculations.
8. `ui` contains the menu and console interaction with the user.
9. `exception` contains the exceptions used for application errors.

`Main` is the entry point of the application. It loads the configuration, creates the repositories and starts the console interface.

## DATA STORAGE

The storage type is selected in the `config.properties` file using the `repository.type` property. Three options are available:

1. `MEMORY` stores data only in memory. The data is lost when the application is closed.
2. `FILE` reads and saves data in text files. The `file.users` and `file.friendships` properties are used for this option.
3. `DATABASE` is prepared as a structure, but the JDBC operations are not implemented in this lab. The classes in `repository.database` throw `UnsupportedOperationException` because the database implementation is reserved for the next lab. The `db.url`, `db.user` and `db.password` properties are provided for configuration.

## FILE FORMATS

The users file accepts lines with either 3 or 6 fields, separated by semicolons. The 3-field format contains the ID, first name and last name. The 6-field format contains the ID, first name, last name, email, birth date and description. When saving, users are written using all 6 fields.

The friendships file uses 3 fields: the first user ID, the second user ID and the friendship date. The date is saved in year-month-day format, followed by the hour and minute.

If a file does not exist, the repository treats it as empty. Invalid lines are ignored and reported in the console together with the line number and the reason for the error.

## VALIDATION

For users, the application checks that the ID is positive, the first and last names are not empty, the names have valid lengths, the email address is valid, the birth date has the correct format and the description contains valid content. The birth date is also checked using an additional rule added with a lambda in `Main`. This rule checks whether the date is valid and is not in the future.

For friendships, the application checks whether both users exist and prevents a friendship from being created between a user and themselves. The application also prevents the same friendship from being added more than once.

## JAVA 8 FEATURES

The project uses features introduced in Java 8.

1. `ValidationStrategy` is a functional interface and has a default `andThen` method for combining validators.
2. `Repository` has a `findAll` method that accepts a `Predicate`, allowing entities to be filtered.
3. `UserCriteria` contains search criteria for users. These criteria can be combined using `and`, `or` and `negate`.
4. `RepositoryFactory` uses two maps with `Function` for creating user and friendship repositories, without using a switch to select the storage type.
5. `AbstractFileRepository` keeps the common reading and writing logic. `UserFileRepository` and `FriendshipFileRepository` implement the conversion between file lines and objects. The Template Method design pattern is used.
6. Collection operations use the Stream API, including `filter`, `map`, `flatMap`, `distinct`, `sorted`, `count`, `max`, `anyMatch`, `allMatch`, `noneMatch` and `collect`.
7. Collectors such as `toList`, `toSet`, `groupingBy`, `counting` and `joining` are used to build collections.
8. `Comparator.comparing` and `thenComparing` are used for sorting.
9. The project uses lambda expressions and method references, including references to static methods, methods of specific objects, methods of arbitrary objects of a particular type and constructors.
10. `Optional` is used for results that may be missing, for example when searching by ID or finding the most sociable community.
11. `Files.lines` and `Files.write` are used for file operations. Reading uses try-with-resources to close the stream automatically.

## COMMUNITY CALCULATION

The network is treated as an undirected graph. Each user represents a node, and each friendship represents an edge. The `getCommunities` method uses the Union-Find data structure to group users into connected components. Communities containing only one user are also included, even if that user has no friends.

The diameter of a community is the largest shortest-path distance between any two of its members. BFS traversal is used to calculate these distances. The most sociable community is selected based on its diameter and then the number of members. If there is still a tie, the community with the smallest minimum ID is selected.

## RUNNING THE APPLICATION

The project can be opened in IntelliJ IDEA as a Java project. A JDK compatible with Java 8 is required. The `config.properties` file must be located in `src/main/resources` and must contain at least the `repository.type` property, together with the properties required by the selected storage type.

To start the application, run the `Main` class. The console menu will appear, and operations can be selected by entering the corresponding number.

The project uses only the standard Java library and does not require external libraries.