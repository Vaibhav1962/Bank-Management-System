This is a comprehensive C program that simulates a basic banking system with two distinct portals: an **Employee Portal** and a **Customer Portal**. The system is designed to facilitate banking operations such as account creation, deposits, withdrawals, transfers, balance checking, and transaction history review.

### Program Structure Overview:

1. **Employee Portal**: 
   - The employee has control over managing accounts within the system. They can create new accounts, remove existing ones, and update details such as the account holder's name. Employees are also responsible for performing actions such as deposits, withdrawals, and fund transfers between accounts.
   
2. **Customer Portal**: 
   - The customer portal allows customers to manage their own accounts. They can create an account, deposit or withdraw money, transfer funds between accounts, check their account balance, and view their transaction history.

### Key Features:

1. **Account Management**:
   - The employee portal enables account creation, deletion, and updates. Accounts are tracked using arrays, where information such as account numbers, holder names, account types, and balances are stored.
   
2. **Authentication**:
   - Both employees and customers are authenticated before they can access the portal functionalities. Employees authenticate using predefined credentials (`admin/admin123`), while customers use passwords specific to their accounts.

3. **Deposits and Withdrawals**:
   - The system allows both employees and customers to deposit and withdraw funds. Transaction types (such as "Deposit" or "Withdrawal") are recorded and stored in a transaction history, which can be retrieved for each account.

4. **Fund Transfers**:
   - Both portals support fund transfers between accounts. In the employee portal, employees can transfer funds between any two accounts. In the customer portal, customers can transfer funds between their own accounts after authentication.

5. **Balance Checking**:
   - Users can check their account balances in both portals. Employees can check the balance of any account, while customers can check their own balance after authentication.

6. **Transaction History**:
   - The program keeps a log of each transaction (deposit, withdrawal, or transfer) for each account. Customers can view the transaction history for their own accounts, whereas employees can view transaction histories for any account.

### Detailed Function Descriptions:

#### **Employee Portal Functions**:
1. **`createAccount()`**:
   - This function allows an employee to create a new account by entering details such as the account number, holder's name, and account type. The account balance is initialized to zero, and a new account is added to the system's record.
   
2. **`authenticateEmployee()`**:
   - This function handles employee authentication using hardcoded credentials (`admin/admin123`). Upon successful authentication, the employee is granted access to the system.

3. **`deposit()` and `withdraw()`**:
   - These functions allow employees to deposit or withdraw money from any account. Each transaction is logged with its type and amount in the account’s transaction history.

4. **`transfer()`**:
   - This function facilitates fund transfers between two accounts. It ensures that the sender has sufficient balance before deducting the amount from the sender and crediting it to the receiver's account. Transaction histories are updated accordingly.

5. **`checkBalance()` and `displayAccountDetails()`**:
   - These functions allow employees to view account balances and detailed account information, including the transaction history.

6. **`displayAllAccounts()`**:
   - This function prints a summary of all accounts in the system, including their balances and transaction histories.

7. **`removeAccount()` and `updateAccount()`**:
   - These functions allow employees to remove an account from the system or update the account holder's name. Removal shifts all other accounts up in the array to prevent gaps.

#### **Customer Portal Functions**:
1. **`createCustomerAccount()`**:
   - This function allows a customer to create a new account. Customers enter their name and a password, and the system assigns them a unique account number. The account balance is initialized to zero.

2. **`authenticateCustomer()`**:
   - This function handles customer authentication by checking the entered password against the stored password for the account.

3. **`depositCustomer()` and `withdrawCustomer()`**:
   - Customers can deposit or withdraw funds after providing their account number and authentication details. Transaction records are updated for each action.

4. **`checkCustomerBalance()`**:
   - This function allows customers to check their current account balance after authentication.

5. **`viewTransactionHistory()`**:
   - Customers can view the history of all transactions performed on their account. The system records each transaction type (deposit, withdrawal, or transfer) and the amount.

6. **`transferCustomer()`**:
   - Customers can transfer funds between their own accounts after authentication and ensuring sufficient balance.

### Program Flow:

1. **Main Menu**:
   - When the program is run, the user is prompted to choose between the Employee Portal and Customer Portal.
   
2. **Employee Portal**:
   - After logging in, the employee is presented with a menu of options to manage accounts, perform transactions, and view details.
   
3. **Customer Portal**:
   - Customers are prompted with a similar menu, but they must authenticate their account using their password before they can perform transactions or view their details.

4. **Exit**:
   - Users can exit both portals or the entire program at any time by choosing the exit option.

### Design Considerations:
- **Data Storage**: Data is stored in arrays, and the maximum number of accounts and transactions is defined by constants (`MAX_ACCOUNTS_EMP`, `MAX_TRANSACTIONS_EMP`, etc.). This ensures that the program is lightweight and can handle a limited number of accounts and transactions.
- **Security**: Basic authentication is implemented for both employees and customers, ensuring that only authorized users can access sensitive operations like transactions and balance checking.
- **Scalability**: While the program supports a limited number of accounts and transactions, it could be expanded to use dynamic data structures (such as linked lists or databases) for larger-scale implementations.

### Conclusion:
This C program is an excellent simulation of a simple banking system, demonstrating key concepts in programming such as arrays, authentication, user input/output, and transaction management. The employee and customer portals provide distinct functionalities suitable for their respective roles, and the program ensures data consistency through structured functions and logical flow control.
