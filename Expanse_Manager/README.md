# Expense Manager

A C-based command-line application for managing personal expenses with multi-user support, administrative capabilities, and date tracking.

## Table of Contents
- [Getting Started](#getting-started)
- [User Guide](#user-guide)
- [Admin Guide](#admin-guide)
- [Features](#features)
- [Data Organization](#data-organization)

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
   - Lists all registered users in a formatted table
   - Shows user count
   - Displays names and email addresses with proper spacing
   - Clean and organized presentation

2. **View Specific User Details**
   - Search user by email
   - Shows user's personal information in a structured table
   - Displays account details and expenses with proper formatting
   - Clear visual separation of different data sections

3. **View All Expenses**
   - Lists expenses for all users in a well-formatted table
   - Shows per-user totals with clear separation
   - Displays grand total across all users
   - Organized presentation with proper spacing

4. **View Expenses by Date Range**
   - Enter start date (DD MM YYYY)
   - Enter end date (DD MM YYYY)
   - Shows expenses within specified date range in a formatted table
   - Displays per-user totals for date range
   - Shows summary statistics:
     * Total number of expenses in range
     * Total amount of expenses
     * Average expense amount
   - Date validation included:
     * Validates date format
     * Checks for valid dates (including leap years)
     * Ensures start date is before or equal to end date
   - Displays expenses in a clean, formatted table with:
     * User name
     * Expense title
     * Date (DD/MM/YYYY format)
     * Amount
   - Shows "No expenses found" message if no expenses exist in range

5. **View Total Expense Statistics**
   - Total number of users
   - Number of users with expenses
   - Total expenses across all users
   - Average expense per user
   - User with highest expenses
   - All statistics displayed in a clean, formatted table

6. **Clean All User Data**
   - Option to remove all user data and files
   - Useful for system maintenance or testing
   - Removes both user accounts and expense records
   - Cleans up the entire userdata directory

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

### Data Organization
- All user data stored in a dedicated `userdata` directory
- Separate files for user accounts and expenses
- Organized file structure for better management
- Automatic directory creation if not exists

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
- Data cleanup functionality
- Formatted table displays for better readability

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

## Data Organization
The program maintains data in an organized structure:
- `userdata/` directory for all user-related files
- `userdata/users.dat` - Stores user account information
- `userdata/expenses_[email].dat` - Stores expenses for each user

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
- Admin tables provide better readability with proper spacing

## Notes
- All data is automatically saved after important operations
- Keep your email and password safe
- Admin credentials should be changed in production
- Regular backups of userdata directory recommended
- Use the cleanup feature carefully as it removes all user data 