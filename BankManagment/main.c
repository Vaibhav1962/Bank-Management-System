#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Employee Portal Constants and Functions
#define MAX_ACCOUNTS_EMP 100
#define MAX_TRANSACTIONS_EMP 100
#define MAX_TRANSACTION_TYPES_EMP 50
#define USERNAME "admin"
#define PASSWORD "admin123"

int account_numbers[MAX_ACCOUNTS_EMP];
char account_names[MAX_ACCOUNTS_EMP][50];
char account_types[MAX_ACCOUNTS_EMP][20];
double account_balances[MAX_ACCOUNTS_EMP];
double transactions[MAX_ACCOUNTS_EMP][MAX_TRANSACTIONS_EMP];
char transaction_types[MAX_ACCOUNTS_EMP][MAX_TRANSACTIONS_EMP][MAX_TRANSACTION_TYPES_EMP];
int transaction_counts[MAX_ACCOUNTS_EMP];
int numAccounts = 0;

// Customer Portal Constants and Functions
#define MAX_ACCOUNTS_CUST 10
#define MAX_TRANSACTIONS_CUST 50
#define PASSWORD_LENGTH_CUST 20

int accountNumbers[MAX_ACCOUNTS_CUST];
char accountHolders[MAX_ACCOUNTS_CUST][50];
double accountBalances[MAX_ACCOUNTS_CUST];
char accountPasswords[MAX_ACCOUNTS_CUST][PASSWORD_LENGTH_CUST];
int transactionsAccountNumbers[MAX_TRANSACTIONS_CUST];
char transactionsTypes[MAX_TRANSACTIONS_CUST];
double transactionsAmounts[MAX_TRANSACTIONS_CUST];
int accountCount = 0;
int transactionCount = 0;

// Employee Portal Function Prototypes
int findAccount(int accNumber);
void displayAccountDetails(int index);
int createAccount();
int authenticateEmployee();
void deposit(int accNumber, double amount);
int withdraw(int accNumber, double amount);
void transfer(int senderAccNumber, int receiverAccNumber, double amount);
void checkBalance(int accNumber);
void displayAllAccounts();
void removeAccount(int accNumber);
void updateAccount(int accNumber);

// Customer Portal Function Prototypes
void createCustomerAccount();
int authenticateCustomer(int accountIndex);
void displayCustomerAccountDetails(int accountIndex);
void depositCustomer();
void withdrawCustomer();
void checkCustomerBalance();
void viewTransactionHistory();
void transferCustomer();

// Employee Portal Function Definitions

int findAccount(int accNumber) {
    for (int i = 0; i < numAccounts; i++) {
        if (account_numbers[i] == accNumber) {
            return i;
        }
    }
    return -1;
}

void displayAccountDetails(int index) {
    printf("Account Number: %d\n", account_numbers[index]);
    printf("Account Holder: %s\n", account_names[index]);
    printf("Account Type: %s\n", account_types[index]);
    printf("Balance: $%.2f\n", account_balances[index]);
    printf("Transaction History:\n");
    for (int i = 0; i < transaction_counts[index]; i++) {
        printf("Transaction %d: Type - %s, Amount - $%.2f\n", i + 1, transaction_types[index][i], transactions[index][i]);
    }
    printf("-------------------------------------------\n");
}

int createAccount(){
    if (numAccounts >= MAX_ACCOUNTS_EMP) {
        printf("Cannot create more accounts. Limit reached.\n");
        return 0;
    }
    printf("Enter Account Number: ");
    scanf("%d", &account_numbers[numAccounts]);

    if (findAccount(account_numbers[numAccounts]) != -1) {
        printf("Account number already exists. Try again with a different number.\n");
        return 0;
    }

    printf("Enter Account Holder's Name: \n");
    scanf("%s", account_names[numAccounts]);

    printf("Enter Account Type (e.g., Savings, Checking): ");
    scanf("%s", account_types[numAccounts]);

    account_balances[numAccounts] = 0.0;
    transaction_counts[numAccounts] = 0;

    numAccounts++;
    printf("Account created successfully.\n");

    return 1;
}

// Authentication function
int authenticateEmployee() {
    char username[50], password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Authentication successful.\n");
        return 1;
    } else {
        printf("Invalid credentials. Access denied.\n");
        return 0;
    }
}


void deposit(int accNumber, double amount) {
     int index = findAccount(accNumber);
    if (index != -1) {
        account_balances[index] += amount;
        transactions[index][transaction_counts[index]] = amount;
        printf("Enter Transaction Type: ");
        scanf("%s", transaction_types[index][transaction_counts[index]]);
        transaction_counts[index]++;
        printf("Deposit successful. Updated balance: $%.2f\n", account_balances[index]);
    } else {
        printf("Account not found. Deposit failed.\n");
    }
}

int withdraw(int accNumber, double amount) {
    int index = findAccount(accNumber);
    if (index != -1) {
        if (account_balances[index] >= amount) {
            account_balances[index] -= amount;
            transactions[index][transaction_counts[index]] = -amount; // Negative amount for withdrawals
            printf("Enter Transaction Type: ");
            scanf("%s", transaction_types[index][transaction_counts[index]]);
            transaction_counts[index]++;
            printf("Withdrawal successful. Updated balance: $%.2f\n", account_balances[index]);
        } else {
            printf("Insufficient balance. Withdrawal failed.\n");
        }
    } else {
        printf("Account not found. Withdrawal failed.\n");
    }
    return 0;}

void transfer(int senderAccNumber, int receiverAccNumber, double amount){
    int senderIndex = findAccount(senderAccNumber);
    int receiverIndex = findAccount(receiverAccNumber);

    if (senderIndex != -1 && receiverIndex != -1) {
        if (account_balances[senderIndex] >= amount) {
            account_balances[senderIndex] -= amount;
            transactions[senderIndex][transaction_counts[senderIndex]] = -amount; // Negative amount for transfers
            printf("Enter Transaction Type: ");
            scanf("%s", transaction_types[senderIndex][transaction_counts[senderIndex]]);
            transaction_counts[senderIndex]++;

            account_balances[receiverIndex] += amount;
            transactions[receiverIndex][transaction_counts[receiverIndex]] = amount;
            printf("Enter Transaction Type: ");
            scanf("%s", transaction_types[receiverIndex][transaction_counts[receiverIndex]]);
            transaction_counts[receiverIndex]++;

            printf("Transfer successful.\n");
        } else {
            printf("Insufficient balance. Transfer failed.\n");
        }
    } else {
        printf("Invalid account(s). Transfer failed.\n");
    }}
void checkBalance(int accNumber) {
    int index = findAccount(accNumber);
    if (index != -1) {
        printf("Current Balance for Account %d: $%.2f\n", account_numbers[index], account_balances[index]);
    } else {
        printf("Account not found.\n");
    }}

void displayAllAccounts() {
    printf("All Accounts:\n");
    for (int i = 0; i < numAccounts; i++) {
        displayAccountDetails(i);
    }
}

void removeAccount(int accNumber) {
    int index = findAccount(accNumber);
    if (index != -1) {
        for (int i = index; i < numAccounts - 1; i++) {
            account_numbers[i] = account_numbers[i + 1];
            strcpy(account_names[i], account_names[i + 1]);
            account_balances[i] = account_balances[i + 1];
        }
        numAccounts--;
        printf("Account removed successfully.\n");
    } else {
        printf("Account not found.\n");
    }
}

void updateAccount(int accNumber) {
    int index = findAccount(accNumber);
    if (index != -1) {
        printf("Enter updated Account Holder's Name: ");
        scanf("%s", account_names[index]);
        printf("Account details updated successfully.\n");
    } else {
        printf("Account not found.\n");
    }
}

// Customer Portal Function Definitions

void createCustomerAccount() {
    if (accountCount < MAX_ACCOUNTS_CUST) {
        printf("Enter account holder name: ");
        scanf("%s", accountHolders[accountCount]);

        printf("Enter password: ");
        scanf("%s", accountPasswords[accountCount]);

        accountNumbers[accountCount] = accountCount + 1;
        accountBalances[accountCount] = 0.0;

        printf("Account created successfully. Account number: %d\n", accountNumbers[accountCount]);

        accountCount++;
    } else {
        printf("Maximum number of accounts reached.\n");
    }
}


int authenticateCustomer(int accountIndex) {
    char enteredPassword[PASSWORD_LENGTH_CUST];
    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, accountPasswords[accountIndex]) == 0) {
        return 1; // Authentication successful
    } else {
        printf("Incorrect password. Access denied.\n");
        return 0; // Authentication failed
    }
}

void displayCustomerAccountDetails(int accountIndex) {
    if (authenticateCustomer(accountIndex)) {
        printf("Account Holder: %s\n", accountHolders[accountIndex]);
        printf("Balance: %.2f\n", accountBalances[accountIndex]);
    }
}

void depositCustomer() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= accountCount) {
        printf("Enter deposit amount: ");
        scanf("%lf", &amount);

        accountBalances[accountNumber - 1] += amount;

        // Record the transaction
        transactionsAccountNumbers[transactionCount] = accountNumber;
        transactionsTypes[transactionCount] = 'D'; // 'D' for Deposit
        transactionsAmounts[transactionCount] = amount;

        printf("Deposit successful. New balance: %.2f\n", accountBalances[accountNumber - 1]);

        transactionCount++;
    } else {
        printf("Invalid account number.\n");
    }
}

void withdrawCustomer() {
    int accountNumber;
    char enteredPassword[PASSWORD_LENGTH_CUST];
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= accountCount) {
        printf("Enter your password: ");
        scanf("%s", enteredPassword);

        if (strcmp(enteredPassword, accountPasswords[accountNumber - 1]) == 0) {
            printf("Enter withdrawal amount: ");
            scanf("%lf", &amount);

            if (amount <= accountBalances[accountNumber - 1]) {
                accountBalances[accountNumber - 1] -= amount;

                // Record the transaction
                transactionsAccountNumbers[transactionCount] = accountNumber;
                transactionsTypes[transactionCount] = 'W'; // 'W' for Withdrawal
                transactionsAmounts[transactionCount] = amount;

                printf("Withdrawal successful. New balance: %.2f\n", accountBalances[accountNumber - 1]);

                transactionCount++;
            } else {
                printf("Insufficient funds.\n");
            }
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } else {
        printf("Invalid account number.\n");
    }
}


void checkCustomerBalance() {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= accountCount) {
        printf("Account Number: %d\n", accountNumbers[accountNumber - 1]);
        printf("Account Holder: %s\n", accountHolders[accountNumber - 1]);
        printf("Balance: $%.2f\n", accountBalances[accountNumber - 1]);
    } else {
        printf("Invalid account number.\n");
    }
}


void viewTransactionHistory() {
    int accountNumber;
    char enteredPassword[PASSWORD_LENGTH_CUST];

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber > 0 && accountNumber <= accountCount) {
        printf("Enter your password: ");
        scanf("%s", enteredPassword);

        if (strcmp(enteredPassword, accountPasswords[accountNumber - 1]) == 0) {
            printf("Transaction History for Account %d:\n", accountNumber);

            for (int i = 0; i < transactionCount; i++) {
                if (transactionsAccountNumbers[i] == accountNumber) {
                    char transactionType = transactionsTypes[i];
                    const char *typeString;

                    switch (transactionType) {
                        case 'D':
                            typeString = "Deposit";
                            break;
                        case 'W':
                            typeString = "Withdrawal";
                            break;
                        case 'T':
                            typeString = "Transfer";
                            break;
                        default:
                            typeString = "Unknown";
                    }

                    printf("%s: %.2f\n", typeString, transactionsAmounts[i]);
                }
            }
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } else {
        printf("Invalid account number.\n");
    }
}


void transferCustomer() {
    int fromAccount, toAccount;
    char enteredPassword[PASSWORD_LENGTH_CUST];
    double amount;

    printf("Enter sender's account number: ");
    scanf("%d", &fromAccount);

    printf("Enter recipient's account number: ");
    scanf("%d", &toAccount);

    if (fromAccount > 0 && fromAccount <= accountCount && toAccount > 0 && toAccount <= accountCount) {
        printf("Enter your password: ");
        scanf("%s", enteredPassword);

        if (strcmp(enteredPassword, accountPasswords[fromAccount - 1]) == 0) {
            printf("Enter transfer amount: ");
            scanf("%lf", &amount);

            if (amount <= accountBalances[fromAccount - 1]) {
                accountBalances[fromAccount - 1] -= amount;
                accountBalances[toAccount - 1] += amount;

                // Record the transaction for the sender
                transactionsAccountNumbers[transactionCount] = fromAccount;
                transactionsTypes[transactionCount] = 'T'; // 'T' for Transfer
                transactionsAmounts[transactionCount] = amount;

                transactionCount++;

                // Record the transaction for the recipient
                transactionsAccountNumbers[transactionCount] = toAccount;
                transactionsTypes[transactionCount] = 'T'; // 'T' for Transfer
                transactionsAmounts[transactionCount] = amount;

                transactionCount++;

                printf("Transfer successful. New balance for sender (%d): %.2f\n", fromAccount, accountBalances[fromAccount - 1]);
            } else {
                printf("Insufficient funds for the transfer.\n");
            }
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } else {
        printf("Invalid account number(s).\n");
    }
}

int main()
{
    int choice;
    int employee;
    int customer;
printf("===== State Bank of Jaypee =====\n");
    printf("Choose an option:\n");
    printf("1. Employee Portal\n");
    printf("2. Customer Portal\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int authenticated = 0;
        printf("===== Employee Portal =====\n");
        printf("Please log in to proceed.\n");
        authenticated = authenticateEmployee();

        if (authenticated) {
            do {
                printf("\nEmployee Portal Options\n");
                printf("1. Create Account\n");
                printf("2. Deposit Funds\n");
                printf("3. Withdraw Funds\n");
                printf("4. Transfer Funds\n");
                printf("5. Check Balance\n");
                printf("6. Display Account Details\n");
                printf("7. Display All Accounts\n");
                printf("8. Remove Account\n");
                printf("9. Update Account Details\n");
                printf("10. Exit Employee Portal\n");
                printf("Enter your choice: ");
                scanf("%d", &employee);

                switch (employee){
                    case 1:{
                        createAccount();
                        break;
                    }
                    case 2:{
                        int accNumber;
                        double amount;
                        printf("Enter Account Number: ");
                        scanf("%d", &accNumber);
                        printf("Enter Amount to Deposit: $");
                        scanf("%lf", &amount);
                        deposit(accNumber, amount);
                        break;
                }
                    case 3:{
                     int accNumber;
                     double amount;
                     printf("Enter Account Number: ");
                     scanf("%d", &accNumber);
                     printf("Enter Amount to Withdraw: $");
                     scanf("%lf", &amount);
                     withdraw(accNumber, amount);
                     break;
                }
                    case 4:{
                    int senderAcc, receiverAcc;
                    double amount;
                    printf("Enter Sender Account Number: ");
                    scanf("%d", &senderAcc);
                    printf("Enter Receiver Account Number: ");
                    scanf("%d", &receiverAcc);
                    printf("Enter Amount to Transfer: $");
                    scanf("%lf", &amount);
                    transfer(senderAcc, receiverAcc, amount);
                    break;
                    }
                    case 5:{
                          int accNumber;
                          printf("Enter Account Number: ");
                          scanf("%d", &accNumber);
                          checkBalance(accNumber);
                          break;
                          }
                    case 6:{
                        int accNumber;
                        printf("Enter Account Number: ");
                        scanf("%d", &accNumber);
                        int index = findAccount(accNumber);
                        if (index != -1) {
                            displayAccountDetails(index);
                            }
                        else {
                            printf("Account not found.\n");
                            }
                        break;
                        }
                    case 7:{
                        displayAllAccounts();
                        break;
            }
                    case 8:{int accNumber;
                    printf("Enter Account Number to Remove: ");
                    scanf("%d", &accNumber);
                    removeAccount(accNumber);
                    break;
            }
                    case 9:{int accNumber;
                    printf("Enter Account Number to Update: ");
                    scanf("%d", &accNumber);
                    updateAccount(accNumber);
                    break;
            }
                    case 10:
                        printf("Exiting Employee Portal...\n");
                        break;
                    default:
                        printf("Invalid choice. Please enter a valid option.\n");
                }
            } while (employee != 10);
        } else {
            printf("Exiting Employee Portal... Thank you!\n");
        }
    } else if (choice == 2) {
        do {
            printf("\nCustomer Portal Options\n");
            printf("1. Create Account\n");
            printf("2. Deposit\n");
            printf("3. Withdraw\n");
            printf("4. Check Balance\n");
            printf("5. View Transaction History\n");
            printf("6. Transfer\n");
            printf("7. Exit Customer Portal\n");
            printf("Enter your choice: ");
            scanf("%d", &customer);

            switch (customer) {
                case 1:
                    createCustomerAccount();
                    break;
                case 2:
                     depositCustomer();
                    break;
                case 3:
                    withdrawCustomer();
                    break;
                case 4:
                    checkCustomerBalance();
                    break;
                case 5:
                    viewTransactionHistory();
                    break;
                case 6:
                    transferCustomer();
                    break;
                case 7:
                    printf("Exiting Customer Portal...\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
            }
        } while (choice != 7);
    } else {
        printf("Exiting...\n");
    }

    return 0;
}
