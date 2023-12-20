#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to represent income and expense transactions
struct Transaction {
    string description;
    double amount;
    string category; // Only for expenses
};

// Structure to store user data
struct UserData {
    string username;
    string password;
    double monthlyIncome;
    double rentAmount;
    double taxesAmount;
    double billsAmount;
    double maxFoodBudget;
    double maxEntertainmentBudget;
    double maxClothesBudget;
    vector<Transaction> incomeTransactions;
    vector<Transaction> expenseTransactions;
};

// Global vectors to store user data
vector<UserData> usersData;

// Function to load user data from a file and populate the UserData structure
bool loadUserData(const string& username, UserData& userData) {
    ifstream file(username + ".txt"); // Save in the same directory as the source code
    if (!file.is_open()) {
        return false; // File doesn't exist
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Username: ") == 0) {
            userData.username = line.substr(10);
        }
        else if (line.find("Password: ") == 0) {
            userData.password = line.substr(10);
        }
        else if (line.find("MonthlyIncome: ") == 0) {
            userData.monthlyIncome = stod(line.substr(15));
        }
        else if (line.find("RentAmount: ") == 0) {
            userData.rentAmount = stod(line.substr(12));
        }
        else if (line.find("TaxesAmount: ") == 0) {
            userData.taxesAmount = stod(line.substr(13));
        }
        else if (line.find("BillsAmount: ") == 0) {
            userData.billsAmount = stod(line.substr(12));
        }
        else if (line.find("MaxFoodBudget: ") == 0) {
            userData.maxFoodBudget = stod(line.substr(15));
        }
        else if (line.find("MaxEntertainmentBudget: ") == 0) {
            userData.maxEntertainmentBudget = stod(line.substr(23));
        }
        else if (line.find("MaxClothesBudget: ") == 0) {
            userData.maxClothesBudget = stod(line.substr(17));
        }
        else if (line == "IncomeTransactions:") {
            while (getline(file, line) && !line.empty()) {
                string description = line;
                getline(file, line);
                double amount = stod(line);
                userData.incomeTransactions.push_back({ description, amount });
            }
        }
        else if (line == "ExpenseTransactions:") {
            while (getline(file, line) && !line.empty()) {
                string category = line;
                while (getline(file, line) && !line.empty()) {
                    string description = line;
                    getline(file, line);
                    double amount = stod(line);
                    userData.expenseTransactions.push_back({ description, amount, category });
                }
            }
        }
    }

    file.close();
    return true;
}

// Function to save user data to a file
void saveUserData(const string& username, const UserData& userData) {
    ofstream file(username + ".txt"); // Save in the same directory as the source code
    if (!file.is_open()) {
        cout << "Error: Cannot save user data.\n";
        return;
    }

    file << "Username: " << userData.username << endl;
    file << "Password: " << userData.password << endl;
    file << "MonthlyIncome: " << userData.monthlyIncome << endl;
    file << "RentAmount: " << userData.rentAmount << endl;
    file << "TaxesAmount: " << userData.taxesAmount << endl;
    file << "BillsAmount: " << userData.billsAmount << endl;
    file << "MaxFoodBudget: " << userData.maxFoodBudget << endl;
    file << "MaxEntertainmentBudget: " << userData.maxEntertainmentBudget << endl;
    file << "MaxClothesBudget: " << userData.maxClothesBudget << endl;

    file << "IncomeTransactions:" << endl;
    for (const auto& income : userData.incomeTransactions) {
        file << income.description << endl;
        file << income.amount << endl;
    }

    file << "ExpenseTransactions:" << endl;
    for (const auto& expense : userData.expenseTransactions) {
        file << expense.category << endl;
        file << expense.description << endl;
        file << expense.amount << endl;
    }

    file.close();
}

// Function to find a user by username
UserData* findUserData(const string& username) {
    for (auto& user : usersData) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

// Function to add income entries
void addIncome(UserData& userData) {
    Transaction income;
    cout << "Enter income description: ";
    cin >> income.description;
    cout << "Enter income amount: $";
    cin >> income.amount;

    userData.incomeTransactions.push_back(income);
    cout << "Income added successfully!" << endl;
}

// Function to add expense entries
void addExpense(UserData& userData) {
    Transaction expense;
    cout << "Enter expense description: ";
    cin >> expense.description;
    cout << "Enter expense amount: $";
    cin >> expense.amount;

    cout << "Select expense category:\n";
    cout << "1. Healthcare\n2. Food\n3. Rent\n4. Taxes\n5. Bills\n6. Other\n";
    int categoryChoice;
    cin >> categoryChoice;

    switch (categoryChoice) {
    case 1:
        expense.category = "Healthcare";
        break;
    case 2:
        expense.category = "Food";
        break;
    case 3:
        expense.category = "Rent";
        break;
    case 4:
        expense.category = "Taxes";
        break;
    case 5:
        expense.category = "Bills";
        break;
    case 6:
        cout << "Enter custom category: ";
        cin.ignore(); // Clear the newline character from the previous input
        getline(cin, expense.category);
        break;
    default:
        cout << "Invalid category choice. Using 'Other'.\n";
        expense.category = "Other";
    }

    userData.expenseTransactions.push_back(expense);
    cout << "Expense added successfully!" << endl;
}

// Function to calculate and display the current balance
void calculateAndDisplayBalance(const UserData& userData) {
    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    for (const auto& income : userData.incomeTransactions) {
        totalIncome += income.amount;
    }

    for (const auto& expense : userData.expenseTransactions) {
        totalExpenses += expense.amount;
    }

    double balance = totalIncome - totalExpenses;

    cout << "Total Income: $" << fixed << setprecision(2) << totalIncome << endl;
    cout << "Total Expenses: $" << fixed << setprecision(2) << totalExpenses << endl;
    cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
}

// Function to manage expenses
void manageExpenses(UserData& userData) {
    cout << "Suggested maximum monthly spending amounts based on your current budget:\n";
    cout << "Food: $" << fixed << setprecision(2) << userData.maxFoodBudget << endl;
    cout << "Entertainment: $" << fixed << setprecision(2) << userData.maxEntertainmentBudget << endl;
    cout << "Clothes: $" << fixed << setprecision(2) << userData.maxClothesBudget << endl;

    cout << "Do you want to add additional expenses? (yes/no): ";
    string addExpensesChoice;
    cin >> addExpensesChoice;

    if (addExpensesChoice == "yes") {
        double totalAdditionalExpenses = 0.0;

        while (true) {
            Transaction expense;
            cout << "Enter additional expense description (or 'done' to finish): ";
            cin >> expense.description;

            if (expense.description == "done") {
                break;
            }

            cout << "Enter additional expense amount: $";
            cin >> expense.amount;

            cout << "Select expense category:\n";
            cout << "1. Healthcare\n2. Food\n3. Rent\n4. Taxes\n5. Bills\n6. Other\n";
            int categoryChoice;
            cin >> categoryChoice;

            switch (categoryChoice) {
            case 1:
                expense.category = "Healthcare";
                break;
            case 2:
                expense.category = "Food";
                break;
            case 3:
                expense.category = "Rent";
                break;
            case 4:
                expense.category = "Taxes";
                break;
            case 5:
                expense.category = "Bills";
                break;
            case 6:
                cout << "Enter custom category: ";
                cin.ignore(); // Clear the newline character from the previous input
                getline(cin, expense.category);
                break;
            default:
                cout << "Invalid category choice. Using 'Other'.\n";
                expense.category = "Other";
            }

            userData.expenseTransactions.push_back(expense);
            totalAdditionalExpenses += expense.amount;
        }

        // Update the budget based on additional expenses
        double remainingIncome = userData.monthlyIncome - userData.rentAmount - userData.taxesAmount - userData.billsAmount - totalAdditionalExpenses;

        userData.maxFoodBudget = remainingIncome * 0.4; // 40% of remaining income
        userData.maxEntertainmentBudget = remainingIncome * 0.3; // 30% of remaining income
        userData.maxClothesBudget = remainingIncome * 0.3; // 30% of remaining income

        cout << "Updated suggested maximum monthly spending amounts:\n";
        cout << "Food: $" << fixed << setprecision(2) << userData.maxFoodBudget << endl;
        cout << "Entertainment: $" << fixed << setprecision(2) << userData.maxEntertainmentBudget << endl;
        cout << "Clothes: $" << fixed << setprecision(2) << userData.maxClothesBudget << endl;
    }
}

// Function to register a new user
void registerUser() {
    UserData newUser;
    cout << "Enter a username: ";
    cin >> newUser.username;
    cout << "Enter a password: ";
    cin >> newUser.password;
    cout << "Enter your monthly income: $";
    cin >> newUser.monthlyIncome;
    cout << "Enter your monthly rent amount: $";
    cin >> newUser.rentAmount;
    cout << "Enter your monthly taxes amount: $";
    cin >> newUser.taxesAmount;
    cout << "Enter your monthly bills amount: $";
    cin >> newUser.billsAmount;

    newUser.maxFoodBudget = newUser.monthlyIncome * 0.4; // 40% of income
    newUser.maxEntertainmentBudget = newUser.monthlyIncome * 0.3; // 30% of income
    newUser.maxClothesBudget = newUser.monthlyIncome * 0.3; // 30% of income

    usersData.push_back(newUser);

    saveUserData(newUser.username, newUser);

    cout << "User registered successfully!" << endl;
}

// Function to log in
UserData* login() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (auto& user : usersData) {
        if (user.username == username && user.password == password) {
            return &user; // User found, return user data
        }
    }

    return nullptr; // User not found
}

int main() {
    while (true) {
        cout << "Options:\n";
        cout << "1. Register\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
        {
            UserData* currentUser = login();
            if (currentUser) {
                cout << "Logged in successfully!\n";

                while (true) {
                    cout << "\nUser Menu:\n";
                    cout << "1. Add Income\n";
                    cout << "2. Add Expense\n";
                    cout << "3. Calculate and Display Balance\n";
                    cout << "4. Manage Expenses\n";
                    cout << "5. Logout\n";
                    cout << "Select an option: ";

                    int userChoice;
                    cin >> userChoice;

                    switch (userChoice) {
                    case 1:
                        addIncome(*currentUser);
                        break;
                    case 2:
                        addExpense(*currentUser);
                        break;
                    case 3:
                        calculateAndDisplayBalance(*currentUser);
                        break;
                    case 4:
                        manageExpenses(*currentUser);
                        break;
                    case 5:
                        // Save user data before logging out
                        saveUserData(currentUser->username, *currentUser);
                        cout << "Logged out successfully!\n";
                        break;
                    default:
                        cout << "Invalid option. Try again.\n";
                    }

                    if (userChoice == 5) {
                        break;
                    }
                }
            }
            else {
                cout << "Login failed. Username or password is incorrect.\n";
            }
        }
        break;
        case 3:
            return 0; // Exit the program
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}
