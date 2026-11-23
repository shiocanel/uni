# Social Network Application

## Description

This is a Java console application that simulates a social network. It allows users to manage users and friendships, and analyze the communities formed in the network.

## Features

- Add and remove users
- Add and remove friendships
- Display all users and friendships
- Count the communities in the network
- Find the most sociable community
- Validate users and friendships
- Store data in CSV files

## Technologies

- Java
- Object-oriented programming
- CSV file storage

## Project Structure

- `domain.model` – contains the main entities, such as users, friendships and communities
- `domain.service` – contains the community analysis algorithm
- `repository` – defines the data access interfaces
- `repository.file` – implements CSV file storage
- `validation` – validates users and friendships
- `service` – handles the application's main operations
- `ui` – provides the console menu
- `exception` – contains custom exceptions

## How to Run

Run the `Main` class from your IDE.

The application stores its data in the `data` directory, using the `users.csv` and `friendships.csv` files.

## Usage

Follow the menu displayed in the console to manage users and friendships or analyze the social network.