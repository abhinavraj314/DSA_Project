#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNumber;
    char accHolderName[100];
    float balance;
    struct Account *next;
};

struct Account *head = NULL;

// function to read accounts from file and load them into the linked list
void loadAccounts() {
    FILE *file = fopen("accounts.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            struct Account *newAccount = (struct Account *)malloc(sizeof(struct Account));
            if (fscanf(file, "%d %s %f", &newAccount->accNumber, newAccount->accHolderName, &newAccount->balance) == 3) {
                newAccount->next = head;
                head = newAccount;
            }
        }
        fclose(file);
    } else {
        printf("Failed to open the file.\n");
    }
}

// function to write accounts from the linked list back to the file
void saveAccounts() {
    FILE *file = fopen("accounts.txt", "w");
    if (file != NULL) {
        struct Account *current = head;
        while (current != NULL) {
            fprintf(file, "%d %s %.2f\n", current->accNumber, current->accHolderName, current->balance);
            current = current->next;
        }
        fclose(file);
    } else {
        printf("Failed to open the file.\n");
    }
}

// function to create a new bank account
void createAccount(int accNumber, char *accHolderName, float balance) {
    struct Account *newAccount = (struct Account *)malloc(sizeof(struct Account));
    newAccount->accNumber = accNumber;
    strcpy(newAccount->accHolderName, accHolderName);
    newAccount->balance = balance;
    newAccount->next = head;
    head = newAccount;
    saveAccounts();
    printf("Account created successfully.\n");
}

// function to display all bank accounts
void displayAllAccounts() {
    struct Account *current = head;
    if (current == NULL) {
        printf("No accounts to display.\n");
    } else {
        printf("Account Details:\n");
        while (current != NULL) {
            printf("Account Number: %d\n", current->accNumber);
            printf("Account Holder Name: %s\n", current->accHolderName);
            printf("Balance: %.2f\n\n", current->balance);
            current = current->next;
        }
    }
}

// function to find account by account number
struct Account *findAccount(int accNumber) {
    struct Account *current = head;
    while (current != NULL) {
        if (current->accNumber == accNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}

// function to display a single bank account
void displayAccount(int accNumber) {
    struct Account *account = findAccount(accNumber);
    if (account != NULL) {
        printf("Account Details:\n");
        printf("Account Number: %d\n", account->accNumber);
        printf("Account Holder Name: %s\n", account->accHolderName);
        printf("Balance: %.2f\n", account->balance);
    } else {
        printf("Account not found.\n");
    }
}

// function to deposit money into an account
void deposit(int accNumber, float amount) {
    struct Account *account = findAccount(accNumber);
    if (account != NULL) {
        account->balance += amount;
        saveAccounts();
        printf("Amount deposited successfully.\n");
    } else {
        printf("Account not found.\n");
    }
}

// function to check balance
void checkBalance(int accNumber) {
    struct Account *account = findAccount(accNumber);
    if (account != NULL) {
        printf("Account Balance: %.2f\n", account->balance);
    } else {
        printf("Account not found.\n");
    }
}

// function to withdraw money from an account
void withdraw(int accNumber, float amount) {
    struct Account *account = findAccount(accNumber);
    if (account != NULL) {
        if (account->balance >= amount) {
            account->balance -= amount;
            saveAccounts();
            printf("Amount withdrawn successfully.\n");
        } else {
            printf("Insufficient balance.\n");
        }
    } else {
        printf("Account not found.\n");
    }
}

int main() {
    int choice, accountNumber;
    loadAccounts(); // to load accounts from file

    do {
        printf("\n1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Display a Single Account\n");
        printf("4. Deposit\n");
        printf("5. Check Balance\n");
        printf("6. Withdraw\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    int accNumber;
                    char accHolderName[100];
                    float balance;
                    printf("Enter account number: ");
                    scanf("%d", &accNumber);
                    printf("Enter account holder name: ");
                    scanf("%s", accHolderName);
                    printf("Enter initial balance: ");
                    scanf("%f", &balance);
                    createAccount(accNumber, accHolderName, balance);
                    break;
                }
            case 2:
                displayAllAccounts();
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                displayAccount(accountNumber);
                break;
            case 4:
                {
                    int accNumber;
                    float amount;
                    printf("Enter account number: ");
                    scanf("%d", &accNumber);
                    printf("Enter amount to deposit: ");
                    scanf("%f", &amount);
                    deposit(accNumber, amount);
                    break;
                }
            case 5:
                {
                    int accNumber;
                    printf("Enter account number: ");
                    scanf("%d", &accNumber);
                    checkBalance(accNumber);
                    break;
                }
            case 6:
                {
                    int accNumber;
                    float amount;
                    printf("Enter account number: ");
                    scanf("%d", &accNumber);
                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amount);
                    withdraw(accNumber, amount);
                    break;
                }
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // to free allocated memory
    struct Account *current = head;
    while (current != NULL) {
        struct Account *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
