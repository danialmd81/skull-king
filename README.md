# SkullKing

SkullKing is a multiplayer card game implemented in C++ using Qt for the GUI and networking functionalities. The project consists of a client application and a server application.

## Table of Contents

- [Project Structure](#project-structure)
- [Features](#features)
- [GIFs](#gifs)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
<!-- - [License](#license) -->

## Project Structure

```plaintext
SkullKing/
├── Game/
│   ├── client.cpp
│   ├── client.h
│   ├── client.ui
│   ├── game.cpp
│   ├── game.h
│   ├── game.ui
├── LoginClasses/
│   ├── forgotpassword.cpp
│   ├── forgotpassword.h
│   ├── forgotpassword.ui
│   ├── login.cpp
│   ├── login.h
│   ├── login.ui
│   ├── signup.cpp
│   ├── signup.h
│   ├── signup.ui
├── Menu/
│   ├── menu.cpp
│   ├── menu.h
│   ├── menu.ui
├── MyClasses/
│   ├── king.cpp
│   ├── king.h
│   ├── deck.cpp
│   ├── deck.h
├── Resource/
│   ├── Resource.qrc
├── main.cpp
├── SkullKing.pro
SkullKingServer/
├── MyClasses/
│   ├── king.cpp
│   ├── king.h
│   ├── deck.cpp
│   ├── deck.h
├── resource.qrc
├── skullkingserver.cpp
├── skullkingserver.h
├── SkullKingServer.pro
├── skullkingserver.ui
```

## Features

- **Client Application**: Allows users to log in, sign up, and play the SkullKing card game.
- **Server Application**: Manages game sessions, handles client connections, and facilitates game logic.
- **Networking**: Uses Qt's `QTcpServer` and `QTcpSocket` for client-server communication.
- **GUI**: Built with Qt Designer for a rich user interface.

## GIFs

Here are some GIFs showcasing the gameplay and features of SkullKing:

![Login](./Login.gif)
<!-- ![Menu](path/to/menu.gif) -->
![Gameplay](./Game.gif)

## Installation

### Prerequisites

- Qt 5.15 or later
- C++17 compatible compiler
- qmake (included with Qt)

### Building the Project

1. Clone the repository:

    ```sh
    git clone <repository-url>
    cd SkullKing
    ```

2. Open the project in Qt Creator:
    - Open `SkullKing.pro` for the client application.
    - Open `SkullKingServer.pro` for the server application.

3. Build the project using Qt Creator.

## Usage

### Running the Server

1. Navigate to the `SkullKingServer` directory.
2. Run the server application:

    ```sh
    ./SkullKingServer
    ```

### Running the Client

1. Navigate to the `SkullKing` directory.
2. Run the client application:

    ```sh
    ./SkullKing
    ```

3. Use the GUI to log in, sign up, and start playing the game.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Create a new Pull Request.

<!-- ## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. -->
