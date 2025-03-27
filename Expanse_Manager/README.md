# Expense Manager

A C-based command-line application for managing personal expenses with multi-user support, administrative capabilities, and date tracking.

## Table of Contents
- [Getting Started](#getting-started)
- [User Guide](#user-guide)
- [Admin Guide](#admin-guide)
- [Features](#features)

## Getting Started

### Compilation
To compile the program, use the following command in your terminal:
```bash
gcc main.c user.c account.c expenses.c appmenu.c login.c signup.c filehandler.c admin.c -o expense_manager
```

### Running the Program
After compilation, run the program using:
```bash
./expense_manager
```

## User Guide

### Main Menu Options
1. **Signup** - Create a new user account
2. **Login** - Access existing user account
3. **Admin Login** - Access administrative features
4. **Exit** - Save and exit the program

### User Operations
After logging in, users can:
1. **Add Account**
   - Create a new account with initial balance
   - One account per user

2. **Add Expense**
   - Add new expenses with title and amount
   - Enter expense date (DD MM YYYY format)
   - System validates date input
   - System checks for sufficient balance

3. **List Expenses**
   - View all recorded expenses
   - Shows expense date, title, and amount
   - Expenses displayed in chronological order

4. **Check Balance**
   - View current account balance

5. **Add Balance**
   - Add more money to account

6. **Logout**
   - Return to main menu

## Admin Guide

### Admin Login Credentials
- Username: `admin`
- Password: `admin123`

### Admin Features
1. **View All Users**
   - Lists all registered users
   - Shows user count
   - Displays names and email addresses

2. **View Specific User Details**
   - Search user by email
   - Shows user's personal information
   - Displays account details and expenses with dates

3. **View All Expenses**
   - Lists expenses for all users with dates
   - Shows per-user totals
   - Displays grand total across all users

4. **View Expenses by Date Range**
   - Enter start date (DD MM YYYY)
   - Enter end date (DD MM YYYY)
   - Shows expenses within specified date range
   - Displays per-user totals for date range
   - Shows summary statistics:
     * Total expenses in range
     * Number of expenses
     * Average expense amount
   - Date validation included

5. **View Total Expense Statistics**
   - Total number of users
   - Number of users with expenses
   - Total expenses across all users
   - Average expense per user
   - User with highest expenses

## Features

### User Management
- Multi-user support
- Secure login system
- Persistent data storage

### Account Management
- Single account per user
- Balance tracking
- Expense recording
- Balance validation

### Data Persistence
- User data saved automatically
- Expenses stored per user
- Data loaded on startup
- Auto-save on important operations

### Administrative Tools
- Secure admin access
- Comprehensive user monitoring
- Expense tracking and statistics
- Detailed user information access

### Security Features
- Password protection
- Separate user accounts
- Protected admin access
- Data integrity checks

### Date Management
- Date tracking for all expenses
- Date range filtering
- Date validation
- Chronological expense listing
- Date-based expense analysis
- Support for expenses from year 2000 onwards

## Data Storage
The program maintains data persistence through:
- `users.dat` - Stores user account information
- `expenses_[email].dat` - Stores expenses for each user

## Data Format

### Expense Entry Format
- Title: Description of expense
- Amount: Cost in floating-point format
- Date: DD MM YYYY format
- Valid date ranges:
  * Day: 1-31
  * Month: 1-12
  * Year: 2000 onwards

## Tips
- Enter dates in DD MM YYYY format (e.g., 15 03 2024)
- Invalid dates will be rejected
- Date range queries show summary statistics
- Expenses are automatically sorted by date
- Use date ranges to track periodic spending

## Notes
- All data is automatically saved after important operations
- Keep your email and password safe
- Admin credentials should be changed in production
- Regular backups of .dat files recommended 