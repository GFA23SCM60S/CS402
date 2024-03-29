#include<stdio.h> 
#include<string.h>

void printDB(char *file) { //Option 1: Printing DB
    FILE *fptr; //declaring file pointer
    char name[20], lname[20];
    int sal, id, count = 0;

    fptr = fopen(file, "r"); //Opening file in read mode
    if (fptr == NULL) { 
        printf("Error opening file.\n");
        return;
    }

    printf("\nName\t\t\tSalary\t\tID\n");
    printf("-----------------------------------------------------------\n");

    while (fscanf(fptr,"%d %s %s %d", &id, name , lname, &sal) == 4) {
        printf("%-12s%-12s%-12d%-12d\n", name, lname, sal, id); //indenting to 12 spaces
        count++;
    }
    printf("\n---------------------------------------------------------------\n");
    printf("Number of Employees: %d\n", count);

    fclose(fptr); //closing file
}

void searchID(char *file) { //Option 2: Searching using ID
    FILE *fptr; //File pointer
    int eid, sal, id, check = 0;
    char name[20], lname[20];

    printf("Enter a 6 digit employee ID: ");
    scanf("%d", &eid);

    fptr = fopen(file, "r"); //opening file in read mode
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(fptr,"%d %s %s %d", &id, name, lname, &sal) == 4) {
        if (id == eid) { //comparing id in file with user input
            printf("\nName\t\t\tSalary\t\tID\n");
            printf("-----------------------------------------------------------\n");
            printf("%-12s%-12s%-12d%-12d\n", name, lname, sal, id);
            ++check;
            break; //breaks out of loop once the id matches
        }
    }
    if (check == 0) { //To check if employee wasnt found
        printf("Employee not found!\n");
    }

    fclose(fptr);
}

void searchName(char *file) { //Option 3: Searching using last name
    FILE *fptr; //File pointer
    char ename[20], name[20], lname[20];
    int sal, id, check = 0;

    printf("Enter Employee's last name (no extra spaces): ");
    scanf("%s", ename);

    fptr = fopen(file, "r"); //opening file in read mode
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(fptr,"%d %s %s %d", &id, name, lname, &sal) == 4) {
        if (strcmp(lname, ename) == 0) { // comparing lastname from file with user input
            printf("\nName\t\t\tSalary\t\tID\n"); 
            printf("-----------------------------------------------------------\n");
            printf("%-12s%-12s%-12d%-12d\n", name, lname, sal, id);
            ++check;
            break; // if matched, breaks out of the loop
        }
    }
    if (check == 0) { //if not found
        printf("Employee not found!\n");
    }

    fclose(fptr); //close file
}

void addName(char *file) {
    FILE *fptr; // File Pointer
    int lid, nid, sal;
    char name[20], lname[20];
    int confirm;

    fptr = fopen(file, "r"); // Opening file in read mode
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Find the last ID
    while (fscanf(fptr, "%d %s %s %d", &lid, name, lname, &sal) == 4) {
        nid = lid; // Parsing through the file to find the last ID
    }

    fclose(fptr); // Closing file

    nid++; // Incrementing the new ID from the last ID

    printf("Enter the first name of the employee: ");
    scanf("%s", name);
    printf("Enter the last name of the employee: ");
    scanf("%s", lname);
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &sal);

    printf("Do you want to add the following employee to the DB?\n");
    printf("\t%s %s, salary: %d\n", name, lname, sal);
    printf("Enter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        fptr = fopen(file, "a"); // Reopening file for appending
        if (fptr == NULL) {
            printf("Error opening file.\n");
            return;
        }
        
        fprintf(fptr, "\n%d %s %s %d", nid, name, lname, sal);
        
        fclose(fptr);

        printf("New employee added with ID: %d\n", nid);
    } else {
        printf("Employee addition canceled.\n");
    }
}

void appFlow(char *file) { //Menu for the application 
    int opt, lc = 0;

    while (lc == 0) {
        printf("\nEmployee DB Menu: \n");
        printf("---------------------------------------\n");
        printf("   (1) Print the Database \n");
        printf("   (2) Lookup by ID \n");
        printf("   (3) Lookup by Last Name \n");
        printf("   (4) Add an Employee \n");
        printf("   (5) Quit \n\n");
        printf("Enter your choice: ");
        scanf("%d", &opt);

        switch(opt) {
            case 1:
                printDB(file);
                break;
            case 2:
                searchID(file);
                break;
            case 3:
                searchName(file);
                break;
            case 4:
                addName(file);
                break;
            case 5:
                printf("Exiting the program. \n");
                ++lc;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }
}

void fileNameIp() { //Getting file input
    char *fname[30];
    printf("Please enter the file name: ");
    scanf("%s",fname);
    appFlow(fname);
}

int main() {
    fileNameIp();
    printf("Thank you! \n");
    return 0;
}
