# User Management System

This project is a console-based user management system written in C++. It allows users to create accounts, login, follow/unfollow other users, and manage followers and following lists. The system also supports blocking users and account deletion. User data is saved to files to persist between sessions.

## Features

- **Create Account**: Users can create new accounts with a username, password, name, email, and account privacy setting.
- **Login**: Users can login to their accounts using their username and password.
- **Search Account**: Users can search for other accounts.
- **Follow/Unfollow User**: Users can follow and unfollow other users.
- **View Following/Followers**: Users can view their following and followers lists.
- **Delete Account**: Users can delete their accounts.
- **Block User**: Users can block other users.
- **View Blocked Users**: Users can view their blocked users list.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- C++11 standard or later

### Usage

1. **Main Menu**
   - 1: Create a new account
   - 2: Login to an account
   - 3: Exit

2. **Control Panel (after login)**
   - 1: Search Account
   - 2: Follow User
   - 3: Unfollow User
   - 4: View Following
   - 5: View Followers
   - 6: Delete Account
   - 7: Block User
   - 8: View Blocked Users
   - 9: Back

## File Structure

- `main.cpp`: Main source code file containing all function definitions and main program logic.
- `users.txt`: File where user data is saved for persistence.

## Acknowledgements

- Inspired by basic social media functionalities for educational purposes.
