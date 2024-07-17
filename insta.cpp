#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct User {
    string username;
    string password;
    string name;
    string email;
    unordered_set<string> followers;
    unordered_set<string> following;
    unordered_set<string> blocked;
    bool isPrivate;
};

// Function declarations
void createAccount(unordered_map<string, User> &users);
bool login(unordered_map<string, User> &users, string &currentUser);
void loadUsers(unordered_map<string, User> &users);
void saveUsers(const unordered_map<string, User> &users);
void searchAccount(const unordered_map<string, User> &users, const string &currentUser);
void followUser(unordered_map<string, User> &users, const string &currentUser);
void unfollowUser(unordered_map<string, User> &users, const string &currentUser);
void viewFollowing(const unordered_map<string, User> &users, const string &currentUser);
void viewFollowers(const unordered_map<string, User> &users, const string &currentUser);
void deleteAccount(unordered_map<string, User> &users, const string &currentUser);
void blockUser(unordered_map<string, User> &users, const string &currentUser);
void viewBlockedUsers(const unordered_map<string, User> &users, const string &currentUser);
void controlPanel(unordered_map<string, User> &users, const string &currentUser);

int main() {
    unordered_map<string, User> users;
    string currentUser;
    int choice;

    // Load existing users from file
    loadUsers(users);

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Create a new account\n";
        cout << "2. Login to an account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount(users);
                break;
            case 2:
                if (login(users, currentUser)) {
                    controlPanel(users, currentUser);
                    currentUser = "";
                }
                break;
            case 3:
                saveUsers(users);
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

// Function definitions

// Create a new account
void createAccount(unordered_map<string, User> &users) {
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;
    cout << "Enter password: ";
    cin >> newUser.password;
    cout << "Enter name: ";
    cin >> newUser.name;
    cout << "Enter email: ";
    cin >> newUser.email;

    cout << "Do you want your account to be private? (1 for yes, 0 for no): ";
    int privacyChoice;
    cin >> privacyChoice;
    newUser.isPrivate = privacyChoice == 1;

    // Save to file
    ofstream outfile(newUser.username + ".txt");
    if (outfile.is_open()) {
        outfile << newUser.username << endl;
        outfile << newUser.password << endl;
        outfile << newUser.name << endl;
        outfile << newUser.email << endl;
        outfile << newUser.isPrivate << endl;
        outfile.close();
    }

    users[newUser.username] = newUser;
    cout << "Account created successfully!" << endl;
}

// Login to an existing account
bool login(unordered_map<string, User> &users, string &currentUser) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username].password == password) {
        cout << "Login successful!" << endl;
        currentUser = username;
        return true;
    } else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}

// Load user data from files at startup
void loadUsers(unordered_map<string, User> &users) {
    ifstream infile("users.txt");
    string username, password, name, email;
    bool isPrivate;

    if (!infile.is_open()) return;

    while (infile >> username >> password >> name >> email >> isPrivate) {
        User user = {username, password, name, email, {}, {}, {}, isPrivate};
        users[username] = user;
    }

    infile.close();
}

// Save user data to files before exiting
void saveUsers(const unordered_map<string, User> &users) {
    ofstream outfile("users.txt");

    if (!outfile.is_open()) return;

    for (const auto &pair : users) {
        const User &user = pair.second;
        outfile << user.username << " " << user.password << " " << user.name << " " << user.email << " " << user.isPrivate << endl;
    }

    outfile.close();
}

// Search for an account
void searchAccount(const unordered_map<string, User> &users, const string &currentUser) {
    string username;
    cout << "Enter username to search: ";
    cin >> username;

    if (users.find(username) != users.end()) {
        const User &user = users.at(username);
        if (user.isPrivate && user.followers.find(currentUser) == user.followers.end()) {
            cout << "The account you are searching for is private." << endl;
        } else {
            cout << "User found: " << user.name << " (" << username << ")" << endl;
        }
    } else {
        cout << "User not found!" << endl;
    }
}

// Follow a user
void followUser(unordered_map<string, User> &users, const string &currentUser) {
    string username;
    cout << "Enter username to follow: ";
    cin >> username;

    if (users.find(username) != users.end() && username != currentUser) {
        users[currentUser].following.insert(username);
        users[username].followers.insert(currentUser);
        cout << "You are now following " << username << endl;
    } else {
        cout << "User not found or you cannot follow yourself!" << endl;
    }
}

// Unfollow a user
void unfollowUser(unordered_map<string, User> &users, const string &currentUser) {
    string username;
    cout << "Enter username to unfollow: ";
    cin >> username;

    if (users[currentUser].following.find(username) != users[currentUser].following.end()) {
        users[currentUser].following.erase(username);
        users[username].followers.erase(currentUser);
        cout << "You have unfollowed " << username << endl;
    } else {
        cout << "You are not following this user!" << endl;
    }
}

// View following list
void viewFollowing(const unordered_map<string, User> &users, const string &currentUser) {
    cout << "You are following: " << endl;
    for (const auto &user : users.at(currentUser).following) {
        cout << user << endl;
    }
}

// View followers list
void viewFollowers(const unordered_map<string, User> &users, const string &currentUser) {
    cout << "Your followers: " << endl;
    for (const auto &user : users.at(currentUser).followers) {
        cout << user << endl;
    }
}

// Delete account
void deleteAccount(unordered_map<string, User> &users, const string &currentUser) {
    // Remove the user from followers and following lists of other users
    for (const auto &follower : users[currentUser].followers) {
        users[follower].following.erase(currentUser);
    }
    for (const auto &following : users[currentUser].following) {
        users[following].followers.erase(currentUser);
    }

    users.erase(currentUser);
    remove((currentUser + ".txt").c_str());
    cout << "Account deleted successfully!" << endl;
}

// Block a user
void blockUser(unordered_map<string, User> &users, const string &currentUser) {
    string username;
    cout << "Enter username to block: ";
    cin >> username;

    if (users.find(username) != users.end() && username != currentUser) {
        users[currentUser].blocked.insert(username);
        cout << "You have blocked " << username << endl;
    } else {
        cout << "User not found or you cannot block yourself!" << endl;
    }
}

// View blocked users
void viewBlockedUsers(const unordered_map<string, User> &users, const string &currentUser) {
    cout << "Blocked users: " << endl;
    for (const auto &user : users.at(currentUser).blocked) {
        cout << user << endl;
    }
}

// Control panel after login
void controlPanel(unordered_map<string, User> &users, const string &currentUser) {
    int choice;
    while (true) {
        cout << "\nControl Panel:\n";
        cout << "1. Search Account\n";
        cout << "2. Follow User\n";
        cout << "3. Unfollow User\n";
        cout << "4. View Following\n";
        cout << "5. View Followers\n";
        cout << "6. Delete Account\n";
        cout << "7. Block User\n";
        cout << "8. View Blocked Users\n";
        cout << "9. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchAccount(users, currentUser);
                break;
            case 2:
                followUser(users, currentUser);
                break;
            case 3:
                unfollowUser(users, currentUser);
                break;
            case 4:
                viewFollowing(users, currentUser);
                break;
            case 5:
                viewFollowers(users, currentUser);
                break;
            case 6:
                deleteAccount(users, currentUser);
                return;
            case 7:
                blockUser(users, currentUser);
                break;
            case 8:
                viewBlockedUsers(users, currentUser);
                break;
            case 9:
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}
