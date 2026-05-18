#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Account {
public:
    string username;
    string password;
    string email;
    double balance;

    Account() {
        balance = 0;
    }

    Account(string u, string p, string e, double b = 0) {
        username = u;
        password = p;
        email = e;
        balance = b;
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    Bank() {
        loadFromFile();
    }

    void loadFromFile() {
        accounts.clear();
        ifstream file("accounts.txt");

        if (!file.is_open())
            return;

        string username, password, email;
        double balance;

        while (file >> username >> password >> email >> balance) {
            accounts.push_back(Account(username, password, email, balance));
        }

        file.close();
    }

    void saveToFile() {
        ofstream file("accounts.txt");

        for (auto &acc : accounts) {
            file << acc.username << " "
                 << acc.password << " "
                 << acc.email << " "
                 << acc.balance << endl;
        }

        file.close();
    }

    void signUp() {
        string username, password, email;

        cout << "\n=== SIGN UP ===\n";
        cout << "Enter Username: ";
        cin >> username;

        for (auto &acc : accounts) {
            if (acc.username == username) {
                cout << "Username already exists!\n";
                return;
            }
        }

        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Email: ";
        cin >> email;

        accounts.push_back(Account(username, password, email, 0));
        saveToFile();

        cout << "Account created successfully!\n";
    }

    int login() {
        string username, password;

        cout << "\n=== LOGIN ===\n";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        for (int i = 0; i < (int)accounts.size(); i++) {
            if (accounts[i].username == username &&
                accounts[i].password == password) {
                cout << "Login successful!\n";
                return i;
            }
        }

        cout << "Invalid username or password!\n";
        return -1;
    }

    void deposit(int index) {
        double amount;

        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }

        accounts[index].balance += amount;
        saveToFile();

        cout << "Deposit successful!\n";
    }

    void withdraw(int index) {
        double amount;

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }

        if (amount > accounts[index].balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        accounts[index].balance -= amount;
        saveToFile();

        cout << "Withdrawal successful!\n";
    }

    void checkBalance(int index) {
        cout << "Current Balance: Rs. "
             << accounts[index].balance << endl;
    }

    void userMenu(int index) {
        int choice;

        do {
            cout << "\n=== USER MENU ===\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Check Balance\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    deposit(index);
                    break;
                case 2:
                    withdraw(index);
                    break;
                case 3:
                    checkBalance(index);
                    break;
                case 4:
                    cout << "Logged out successfully!\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }

    void mainMenu() {
        int choice;

        do {
            cout << "\n===== BANKING SYSTEM =====\n";
            cout << "1. Sign Up\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    signUp();
                    break;
                case 2: {
                    int index = login();
                    if (index != -1) {
                        userMenu(index);
                    }
                    break;
                }
                case 3:
                    cout << "Thank you for using the Banking System!\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 3);
    }
};

int main() {
    Bank bank;
    bank.mainMenu();
    return 0;
}
