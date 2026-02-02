#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ANSI Colors */
#define CYAN  "\033[1;36m"
#define GREEN "\033[1;32m"
#define RED   "\033[1;31m"
#define RESET "\033[0m"

struct Expense {
    char date[15];
    char category[20];
    float amount;
};

struct Goal {
    char name[30];
    float target;
    float saved;
};

void clearScreen() {
    system("cls");  // Windows
    // system("clear"); // Linux / macOS
}

/* -------- EXPENSE FUNCTIONS -------- */
void addExpense() {
    FILE *fp;
    struct Expense e;

    fp = fopen("expenses.txt", "a");
    if (!fp) {
        printf(RED "File error!\n" RESET);
        return;
    }

    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", e.date);

    printf("Enter Category: ");
    scanf("%s", e.category);

    printf("Enter Amount: ");
    scanf("%f", &e.amount);

    fprintf(fp, "%s %s %.2f\n", e.date, e.category, e.amount);
    fclose(fp);

    printf(GREEN "\nExpense added successfully!\n" RESET);
}

void viewExpenses() {
    FILE *fp;
    struct Expense e;

    fp = fopen("expenses.txt", "r");
    if (!fp) {
        printf(RED "No expenses found!\n" RESET);
        return;
    }

    printf(CYAN "\nDate\t\tCategory\tAmount\n" RESET);
    printf("----------------------------------------\n");

    while (fscanf(fp, "%s %s %f", e.date, e.category, &e.amount) != EOF) {
        printf("%s\t%s\t\t₹%.2f\n", e.date, e.category, e.amount);
    }

    fclose(fp);
}

/* -------- GOAL FUNCTIONS -------- */
void addGoal() {
    FILE *fp;
    struct Goal g;

    fp = fopen("goals.txt", "a");
    if (!fp) {
        printf(RED "File error!\n" RESET);
        return;
    }

    printf("Enter Goal Name: ");
    scanf("%s", g.name);

    printf("Enter Target Amount: ");
    scanf("%f", &g.target);

    printf("Enter Saved Amount: ");
    scanf("%f", &g.saved);

    fprintf(fp, "%s %.2f %.2f\n", g.name, g.target, g.saved);
    fclose(fp);

    printf(GREEN "\nGoal added successfully!\n" RESET);
}

void viewGoals() {
    FILE *fp;
    struct Goal g;
    float progress;

    fp = fopen("goals.txt", "r");
    if (!fp) {
        printf(RED "No goals found!\n" RESET);
        return;
    }

    printf(CYAN "\nGoal\tTarget\tSaved\tProgress\n" RESET);
    printf("--------------------------------------------\n");

    while (fscanf(fp, "%s %f %f", g.name, &g.target, &g.saved) != EOF) {
        progress = (g.saved / g.target) * 100;
        printf("%s\t₹%.2f\t₹%.2f\t%.1f%%\n",
               g.name, g.target, g.saved, progress);
    }

    fclose(fp);
}

/* -------- MAIN -------- */
int main() {
    int choice;

    do {
        printf(CYAN "\n==== PERSONAL FINANCE TRACKER ====\n" RESET);
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Add Finance Goal\n");
        printf("4. View Finance Goals\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: addGoal(); break;
            case 4: viewGoals(); break;
            case 5: printf(GREEN "Exiting program...\n" RESET); break;
            default: printf(RED "Invalid choice!\n" RESET);
        }

    } while (choice != 5);

    return 0;
}