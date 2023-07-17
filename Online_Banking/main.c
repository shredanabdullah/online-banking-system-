#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char phone[50];
    char password[50];
    int balance;
    char accountNum[50];
};

int main() {
    system("color 0b");
    int choice;
    struct user userObj;
    FILE *fp;
    char filename[50];

    char phone[50];
    char password[50];
    char continuee = 'y';

    printf("\n\t\t\t-------------------- Welcome to our Online Banking system --------------------\n");
    printf("\nWhat do you want to do?");
    printf("\n1. Register an account.");
    printf("\n2. Login to your account");
    printf("\n3. Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);
    system("cls");

    if (choice == 1) {
        printf("\nEnter your account number: ");
        scanf("%s", userObj.accountNum);
        printf("\nEnter your phone number: ");
        scanf("%s", userObj.phone);
        printf("\nEnter your new password: ");
        scanf("%s", userObj.password);
        userObj.balance = 0;
        strcpy(filename, userObj.phone);
        strcat(filename, ".txt");

        fp = fopen(filename, "w");
        if (fp != NULL) {
            fprintf(fp, "Account Number: %s\n", userObj.accountNum);
            fprintf(fp, "Phone Number: %s\n", userObj.phone);
            fprintf(fp, "Password: %s\n", userObj.password);
            fprintf(fp, "Balance: %d\n", userObj.balance);
            fclose(fp);
            printf("\nAccount is registered successfully");
            printf("\n\t\t\t-------------------- Thank You! --------------------\n");
        } else {
            printf("\nSomething went wrong. Please try again");
            Beep(600, 300);
        }
    } else if (choice == 2) {
        printf("\nEnter your phone number: ");
        scanf("%s", phone);
        printf("\nEnter your password: ");
        scanf("%s", password);
        strcpy(filename, phone);
        strcat(filename, ".txt");

        fp = fopen(filename, "r+");
        if (fp != NULL) {
            fscanf(fp, "Account Number: %s\n", userObj.accountNum);
            fscanf(fp, "Phone Number: %s\n", userObj.phone);
            fscanf(fp, "Password: %s\n", userObj.password);
            fscanf(fp, "Balance: %d\n", &userObj.balance);
            fseek(fp, -sizeof(int), SEEK_CUR);  // Move the file pointer back to overwrite the balance

            if (strcmp(password, userObj.password) == 0) {
                printf("\nPassword matched");
                while (continuee == 'y' || continuee == 'Y') {
                    system("cls");
                    printf("\nPress 1 to check your balance");
                    printf("\nPress 2 to deposit money");
                    printf("\nPress 3 to withdraw");
                    printf("\nPress 4 to change your password");

                    int option;
                    printf("\nEnter your choice: ");
                    scanf("%d", &option);

                    switch (option) {
                        case 1:
                            printf("\nYour balance is: %d", userObj.balance);
                            break;
                        case 2:
                            printf("\nEnter the amount to deposit: ");
                            int depositAmount;
                            scanf("%d", &depositAmount);
                            userObj.balance += depositAmount;
                            printf("\nDeposit successful. Your new balance is: %d", userObj.balance);
                            break;
                        case 3:
                            printf("\nEnter the amount to withdraw: ");
                            int withdrawAmount;
                            scanf("%d", &withdrawAmount);
                            if (withdrawAmount <= userObj.balance) {
                                userObj.balance -= withdrawAmount;
                                printf("\nWithdrawal successful. Your new balance is: %d", userObj.balance);
                            } else {
                                printf("\nInsufficient funds. Withdrawal canceled.");
                            }
                            break;
                        case 4:
                            printf("\nEnter your new password: ");
                            scanf("%s", userObj.password);
                            printf("\nPassword changed successfully.");
                            break;
                        default:
                            printf("\nInvalid option. Please try again.");
                            break;
                    }

                    fseek(fp, -sizeof(int), SEEK_CUR);  // Move the file pointer back to overwrite the balance
                    fprintf(fp, "Balance: %d\n", userObj.balance);
                    fflush(fp);  // Flush changes to the file
                    fseek(fp, 0, SEEK_END);  // Move the file pointer to the end for future appends

                    printf("\nDo you want to continue? [y/n]: ");
                    scanf(" %c", &continuee);
                }
                 printf("\n\t\t\t-------------------- Thank You! --------------------\n");
            } else {
                printf("\nPassword does not match");
                Beep(600, 300);
            }
            fclose(fp);
        } else {
            printf("\nAccount does not exist");
            Beep(600, 300);
        }
    }

    return 0;
}
