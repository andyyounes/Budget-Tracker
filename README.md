# Budget Tracker – C++ Console Application

A command-line budget management system built in C++ that allows users to register, log in, input income and expenses, and view their financial summary. Ideal for beginners learning file I/O, structs, and budget planning logic.

---

## 💡 Features

- User registration and login system
- Persistent user data storage in `.txt` files
- Add income and categorize expenses
- Dynamic budget recommendations based on income and fixed costs
- View current balance, income, and total expenses

---

## 🛠️ How to Run

Compile and run the program using a C++ compiler:

```bash
g++ -o budget_tracker budget_tracker.cpp
./budget_tracker
```

🧪 Example Session Output
```bash
Options:
1. Register
2. Log In
3. Exit
Select an option: 1
Enter a username: andy
Enter a password: nd;Yu;1000
Enter your monthly income: $1000
Enter your monthly rent amount: $200
Enter your monthly taxes amount: $200
Enter your monthly bills amount: $100
User registered successfully!

Options:
1. Register
2. Log In
3. Exit
Select an option: 2
Enter your username: andy
Enter your password: nd;Yu;1000
Logged in successfully!

User Menu:
1. Add Income
2. Add Expense
3. Calculate and Display Balance
4. Manage Expenses
5. Logout
Select an option: 1
Enter income description: work
Enter income amount: $1000
Income added successfully!

Select an option: 2
Enter expense description: uni
Enter expense amount: $300
Select expense category: 5 (Bills)
Expense added successfully!

Select an option: 2
Enter expense description: rent
Enter expense amount: $200
Select expense category: 3 (Rent)
Expense added successfully!

Select an option: 2
Enter expense description: dentist
Enter expense amount: $100
Select expense category: 1 (Healthcare)
Expense added successfully!

Select an option: 3
Total Income: $1000.00
Total Expenses: $600.00
Current Balance: $400.00

Select an option: 4
Suggested maximum monthly spending amounts based on your current budget:
Food: $400.00
Entertainment: $300.00
Clothes: $300.00
Do you want to add additional expenses? (yes/no): no

Select an option: 5
Logged out successfully!
```

💾 File Format (user save data)
When a user is created, a .txt file is generated with their data:
```markdown
Username: andy
Password: nd;Yu;1000
MonthlyIncome: 1000
RentAmount: 200
TaxesAmount: 200
BillsAmount: 100
MaxFoodBudget: 400
MaxEntertainmentBudget: 300
MaxClothesBudget: 300
IncomeTransactions:
work
1000
ExpenseTransactions:
Bills
uni
300
Rent
rent
200
Healthcare
dentist
100
```
