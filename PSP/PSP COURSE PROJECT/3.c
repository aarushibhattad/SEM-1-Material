#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------- ANSI COLORS ---------- */
#define CYAN   "\033[1;36m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED    "\033[1;31m"
#define RESET  "\033[0m"

/* ---------- STRUCTURES ---------- */
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

/* ---------- CLEAR SCREEN ---------- */
void clearScreen() {
    system("clear");   // macOS / Linux
}

/* ---------- PIN FUNCTIONS ---------- */
int setupPIN() {
    FILE *fp;
    int pin, confirm;

    fp = fopen("pin.txt", "r");
    if (fp != NULL) {
        fclose(fp);
        return 1;
    }

    printf(CYAN "\n--- SETUP LOGIN PIN ---\n" RESET);
    printf("Create a 4-digit PIN: ");
    scanf("%d", &pin);

    printf("Confirm PIN: ");
    scanf("%d", &confirm);

    if (pin != confirm) {
        printf(RED "PIN mismatch! Restart program.\n" RESET);
        return 0;
    }

    fp = fopen("pin.txt", "w");
    fprintf(fp, "%d", pin);
    fclose(fp);

    printf(GREEN "PIN created successfully!\n" RESET);
    return 1;
}

int verifyPIN() {
    FILE *fp;
    int savedPIN, enteredPIN, attempts = 3;

    fp = fopen("pin.txt", "r");
    if (!fp) {
        printf(RED "PIN file missing!\n" RESET);
        return 0;
    }

    fscanf(fp, "%d", &savedPIN);
    fclose(fp);

    while (attempts > 0) {
        printf("Enter your PIN: ");
        scanf("%d", &enteredPIN);

        if (enteredPIN == savedPIN) {
            printf(GREEN "Login successful!\n" RESET);
            return 1;
        } else {
            attempts--;
            printf(RED "Incorrect PIN. Attempts left: %d\n" RESET, attempts);
        }
    }

    printf(RED "Too many failed attempts. Exiting...\n" RESET);
    return 0;
}

/* ---------- PROGRESS BAR ---------- */
void printProgressBar(float percent) {
    int totalBars = 20;
    int filledBars = (percent / 100.0) * totalBars;

    if (percent > 70)
        printf(GREEN);
    else if (percent >= 40)
        printf(YELLOW);
    else
        printf(RED);

    printf("[");
    for (int i = 0; i < totalBars; i++) {
        if (i < filledBars)
            printf("#");
        else
            printf("-");
    }
    printf("]");
    printf(RESET);
}

/* ---------- EXPENSE FUNCTIONS ---------- */
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

    printf(GREEN "Expense added successfully!\n" RESET);
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
    printf("---------------------------------------------\n");

    while (fscanf(fp, "%s %s %f", e.date, e.category, &e.amount) != EOF) {
        printf("%s\t%s\t\tRs.%.2f\n", e.date, e.category, e.amount);
    }

    fclose(fp);
}

/* ---------- MONTHLY BREAKDOWN ---------- */
void monthlyBreakdown(float monthlyTotal[12]) {
    FILE *fp;
    struct Expense e;
    int month;

    for (int i = 0; i < 12; i++)
        monthlyTotal[i] = 0;

    fp = fopen("expenses.txt", "r");
    if (!fp)
        return;

    while (fscanf(fp, "%s %s %f", e.date, e.category, &e.amount) != EOF) {
        sscanf(e.date, "%*d-%d-%*d", &month);
        if (month >= 1 && month <= 12)
            monthlyTotal[month - 1] += e.amount;
    }
    fclose(fp);
}

/* ---------- GOAL FUNCTIONS ---------- */
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

    printf(GREEN "Goal added successfully!\n" RESET);
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
    printf("------------------------------------------------------------\n");

    while (fscanf(fp, "%s %f %f", g.name, &g.target, &g.saved) != EOF) {
        progress = (g.saved / g.target) * 100;

        printf("%-10s Rs.%.0f Rs.%.0f ", g.name, g.target, g.saved);
        printProgressBar(progress);
        printf(" %.1f%%\n", progress);
    }

    fclose(fp);
}

/* ---------- AUTO REPORT GENERATION ---------- */
void generateReport() {
    FILE *report, *fp;
    struct Expense e;
    struct Goal g;
    float monthlyTotal[12];
    time_t now = time(NULL);

    report = fopen("report.txt", "w");
    if (!report) {
        printf(RED "Unable to generate report!\n" RESET);
        return;
    }

    fprintf(report, "PERSONAL FINANCE REPORT\n");
    fprintf(report, "Generated on: %s\n", ctime(&now));

    /* Expenses */
    fprintf(report, "\n--- EXPENSES ---\n");
    fp = fopen("expenses.txt", "r");
    if (fp) {
        while (fscanf(fp, "%s %s %f", e.date, e.category, &e.amount) != EOF)
            fprintf(report, "%s  %s  %.2f\n", e.date, e.category, e.amount);
        fclose(fp);
    }

    /* Monthly Summary */
    monthlyBreakdown(monthlyTotal);
    fprintf(report, "\n--- MONTHLY SUMMARY ---\n");
    for (int i = 0; i < 12; i++) {
        if (monthlyTotal[i] > 0)
            fprintf(report, "Month %02d : %.2f\n", i + 1, monthlyTotal[i]);
    }

    /* Goals */
    fprintf(report, "\n--- FINANCE GOALS ---\n");
    fp = fopen("goals.txt", "r");
    if (fp) {
        while (fscanf(fp, "%s %f %f", g.name, &g.target, &g.saved) != EOF) {
            float progress = (g.saved / g.target) * 100;
            fprintf(report, "%s  Target: %.2f  Saved: %.2f  Progress: %.1f%%\n",
                    g.name, g.target, g.saved, progress);
        }
        fclose(fp);
    }

    fclose(report);
    printf(GREEN "Report generated successfully (report.txt)\n" RESET);
}

/* ---------- MAIN ---------- */
int main() {
    int choice;

    if (!setupPIN()) return 0;
    if (!verifyPIN()) return 0;

    do {
        printf(CYAN "\n==== PERSONAL FINANCE TRACKER ====\n" RESET);
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Monthly Expense Breakdown\n");
        printf("4. Add Finance Goal\n");
        printf("5. View Finance Goals\n");
        printf("6. Generate Report\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: {
                float monthlyTotal[12];
                monthlyBreakdown(monthlyTotal);
                printf(CYAN "\nMONTHLY EXPENSE SUMMARY\n" RESET);
                for (int i = 0; i < 12; i++)
                    if (monthlyTotal[i] > 0)
                        printf("Month %02d : ₹%.2f\n", i + 1, monthlyTotal[i]);
                break;
            }
            case 4: addGoal(); break;
            case 5: viewGoals(); break;
            case 6: generateReport(); break;
            case 7: printf(GREEN "Exiting program...\n" RESET); break;
            default: printf(RED "Invalid choice!\n" RESET);
        }

    } while (choice != 7);

    return 0;
}
