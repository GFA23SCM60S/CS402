#include<stdio.h> 
#include<string.h>
#include <ctype.h>

void printDB(char *file) { //P1_Option 1: Printing DB
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

void searchID(char *file) { //P1_Option 2: Searching using ID
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

void searchName(char *file) { //P1_Option 3: Searching using last name
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

    while (fscanf(fptr,"%d %s %s %d", &id, name, lname, &sal) == 4) { //Ensures the input matches only 4 columns
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

void addName(char *file) { //P1_Option 4:Adding an employee
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
    while (fscanf(fptr, "%d %s %s %d", &lid, name, lname, &sal) == 4) { //Ensures the input matches only 4 columns
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

int checkID(char *file, int eid){//P2_Menu: To check if eid exists in the txt file
    FILE *fptr;
    int sal, id, check = 0;
    char name[20], lname[20];
    
    // Open the file in read mode with file pointer 1
    fptr = fopen(file, "r");

    if (fptr == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return 0;
    }
    // Checking if the eid is there in the id list
    while (fscanf(fptr, "%d %s %s %d", &id, name, lname, &sal) == 4) {
        if (id == eid) { // comparing id in file with user input
            ++check;
            break; // breaks out of loop once the id matches
        }
    }
    return check;
}

void removeEmp(char *file) { //P2_Option 1: Remove Employee
    // declaring 2 file pointers
    FILE *fptr1, *fptr2;
    int sal, id, check = 0;
    char name[20], lname[20];
    int eid; // Employee id to be removed from DB
    int choice = 0;

    printf("\nEnter the employee id to be removed: ");
    scanf("%d", &eid); // getting input for employee id

    // Open the file in read mode with file pointer 1
    fptr1 = fopen(file, "r");

    if (fptr1 == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Checking if the eid is there in the id list
    while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) {
        if (id == eid) { // comparing id in file with user input
            ++check;
            break; // breaks out of loop once the id matches
        }
    }

    if (check == 0) { // To check if employee wasn't found
        printf("Employee not found!\n");
    } else {
        printf("\nEmployee found. Do you really want to delete the record?\n ");
        printf("\nEnter 0 to cancel. Enter 1 to delete.\n");
        scanf("%d", &choice); // Corrected the missing address-of operator

        if (choice == 0) {
            printf("\nDeletion action cancelled!\n");
            fclose(fptr1);
            return;
        } else {
            // Open a new file in write mode with file pointer 2
            fptr2 = fopen("copy.txt", "w");

            if (fptr2 == NULL) {
                printf("Error: Unable to open file for writing.\n");
                fclose(fptr1);
                return;
            }

            // Read from original file and write to replica file
            rewind(fptr1); // Rewind to beginning of file
            while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) { // reading from filepointer 1
                if (id != eid) { // If id is not the id to be deleted
                    fprintf(fptr2, "%d %s %s %d\n", id, name, lname, sal); // writing to filepointer 2
                }
            }

            // Closing file pointers
            fclose(fptr1);
            fclose(fptr2);

            // Remove the original file
            if (remove(file) != 0) {
                printf("Error: Unable to delete the original file.\n");
                return;
            }

            // Rename the copy file to the original name
            if (rename("copy.txt", file) != 0) {
                printf("Error: Unable to rename the replica file.\n");
                return;
            }
            printf("Employee with ID %d removed successfully.\n", eid);
        }
    }
}

void updateEid(char *file, int eid){ //P2_option 2.1: Update Employee ID
    
    // declaring 2 file pointers
    FILE *fptr1, *fptr2;
    int sal, id, check = 0;
    char name[20], lname[20];
    //int eid; // Employee id to be removed from DB
    int choice = 0;
    int new;

    // Open the file in read mode with file pointer 1
    fptr1 = fopen(file, "r");

    if (fptr1 == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Open a new file in write mode with file pointer 2
            fptr2 = fopen("copy.txt", "w");

            if (fptr2 == NULL) {
                printf("Error: Unable to open file for writing.\n");
                fclose(fptr1);
                return;
            }

    // Checking if the eid is there in the id list
    while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) { 
        if (id == eid) { // comparing id in file with user input
            printf("Enter the new employee ID:\n");
            scanf("%d",&new);
            fprintf(fptr2, "%d %s %s %d\n", new, name, lname, sal); // writing new employee id to filepointer 2
            break; // breaks out of loop once the id matches
        }
        else{
            fprintf(fptr2, "%d %s %s %d\n", id, name, lname, sal); // writing to filepointer 2
        }
    }
    // Closing file pointers
            fclose(fptr1);
            fclose(fptr2);
    // Remove the original file
            if (remove(file) != 0) {
                printf("Error: Unable to delete the original file.\n");
                return;
            }

    // Rename the copy file to the original name
            if (rename("copy.txt", file) != 0) {
                printf("Error: Unable to rename the replica file.\n");
                return;
            }
    printf("Employee with ID %d updated successfully to %d ID.\n", eid,new);
}

void updateFname(char *file, int eid){ //P2_option 2.2: Update Employee First Name
// declaring 2 file pointers
    FILE *fptr1, *fptr2;
    int sal, id, check = 0;
    char name[20], lname[20];
    //int eid; // Employee id to be removed from DB
    int choice = 0;
    char new[20];

    // Open the file in read mode with file pointer 1
    fptr1 = fopen(file, "r");

    if (fptr1 == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Open a new file in write mode with file pointer 2
            fptr2 = fopen("copy.txt", "w");

            if (fptr2 == NULL) {
                printf("Error: Unable to open file for writing.\n");
                fclose(fptr1);
                return;
            }

    // Checking if the eid is there in the id list
    while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) {
        if (id == eid) { // comparing id in file with user input
            printf("Enter the new employee name:\n");
            scanf("%s",new); //i/p from user for new name 
            fprintf(fptr2, "%d %s %s %d\n", id, new, lname, sal); // writing new employee id to filepointer 2
            break; // breaks out of loop once the id matches
        }
        else{
            fprintf(fptr2, "%d %s %s %d\n", id, name, lname, sal); // writing to filepointer 2
        }
    }
    // Closing file pointers
            fclose(fptr1);
            fclose(fptr2);
    // Remove the original file
            if (remove(file) != 0) {
                printf("Error: Unable to delete the original file.\n");
                return;
            }

    // Rename the copy file to the original name
            if (rename("copy.txt", file) != 0) {
                printf("Error: Unable to rename the replica file.\n");
                return;
            }
    printf("Employee with ID %d updated successfully to %s.\n", eid,new);
}

void updateLname(char *file, int eid){ //P2_option 2.3: Update Employee Last Name
// declaring 2 file pointers
    FILE *fptr1, *fptr2;
    int sal, id, check = 0;
    char name[20], lname[20];
    //int eid; // Employee id to be removed from DB
    int choice = 0;
    char new[20];

    // Open the file in read mode with file pointer 1
    fptr1 = fopen(file, "r");

    if (fptr1 == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Open a new file in write mode with file pointer 2
            fptr2 = fopen("copy.txt", "w");

            if (fptr2 == NULL) {
                printf("Error: Unable to open file for writing.\n");
                fclose(fptr1);
                return;
            }

    // Checking if the eid is there in the id list
    while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) {
        if (id == eid) { // comparing id in file with user input
            printf("Enter the new employee last name:\n");
            scanf("%s",new); //i/p from user for new name 
            fprintf(fptr2, "%d %s %s %d\n", id, name, new, sal); // writing new employee id to filepointer 2
            break; // breaks out of loop once the id matches
        }
        else{
            fprintf(fptr2, "%d %s %s %d\n", id, name, lname, sal); // writing to filepointer 2
        }
    }
    // Closing file pointers
            fclose(fptr1);
            fclose(fptr2);
    // Remove the original file
            if (remove(file) != 0) {
                printf("Error: Unable to delete the original file.\n");
                return;
            }

    // Rename the copy file to the original name
            if (rename("copy.txt", file) != 0) {
                printf("Error: Unable to rename the replica file.\n");
                return;
            }
    printf("Employee with ID %d updated successfully to %s.\n", eid,new);
}

void updateEsal(char *file, int eid){ //P2_option 2.4: Update Employee ID
    
    // declaring 2 file pointers
    FILE *fptr1, *fptr2;
    int sal, id, check = 0;
    char name[20], lname[20];
    //int eid; // Employee id to be removed from DB
    int choice = 0;
    int new;

    // Open the file in read mode with file pointer 1
    fptr1 = fopen(file, "r");

    if (fptr1 == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Open a new file in write mode with file pointer 2
            fptr2 = fopen("copy.txt", "w");

            if (fptr2 == NULL) {
                printf("Error: Unable to open file for writing.\n");
                fclose(fptr1);
                return;
            }

    // Checking if the eid is there in the id list
    while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) { 
        if (id == eid) { // comparing id in file with user input
            printf("Enter the new employee Salary:\n");
            scanf("%d",&new);
            fprintf(fptr2, "%d %s %s %d\n", id, name, lname, new); // writing new employee id to filepointer 2
            break; // breaks out of loop once the id matches
        }
        else{
            fprintf(fptr2, "%d %s %s %d\n", id, name, lname, sal); // writing to filepointer 2
        }
    }
    // Closing file pointers
            fclose(fptr1);
            fclose(fptr2);
    // Remove the original file
            if (remove(file) != 0) {
                printf("Error: Unable to delete the original file.\n");
                return;
            }

    // Rename the copy file to the original name
            if (rename("copy.txt", file) != 0) {
                printf("Error: Unable to rename the replica file.\n");
                return;
            }
    printf("Employee with ID %d updated successfully to %d salary.\n", eid,new);
}

void updateAll(char *file, int eid){ //P2_option 2.5: Update Employee ID
    
    // declaring 2 file pointers
    FILE *fptr1, *fptr2;
    int sal, id, check = 0;
    char name[20], lname[20];
    //int eid; // Employee id to be removed from DB
    int choice = 0;
    int newId, newSal;
    char newFname[20], newLname[20];

    // Open the file in read mode with file pointer 1
    fptr1 = fopen(file, "r");

    if (fptr1 == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Open a new file in write mode with file pointer 2
            fptr2 = fopen("copy.txt", "w");

            if (fptr2 == NULL) {
                printf("Error: Unable to open file for writing.\n");
                fclose(fptr1);
                return;
            }

    // Checking if the eid is there in the id list
    while (fscanf(fptr1, "%d %s %s %d", &id, name, lname, &sal) == 4) { 
        if (id == eid) { // comparing id in file with user input
            printf("Enter the new employee ID:\n");
            scanf("%d",&newId);
            printf("Enter the new employee Salary:\n");
            scanf("%d",&newSal);
            printf("Enter the new employee First Name:\n");
            scanf("%s", newFname);
            printf("Enter the new employee Last Name:\n");
            scanf("%s", newLname);
            fprintf(fptr2, "%d %s %s %d\n", newId, newFname, newLname, newSal); // writing new employee id to filepointer 2
            break; // breaks out of loop once the id matches
        }
        else{
            fprintf(fptr2, "%d %s %s %d\n", id, name, lname, sal); // writing to filepointer 2
        }
    }
    // Closing file pointers
            fclose(fptr1);
            fclose(fptr2);
    // Remove the original file
            if (remove(file) != 0) {
                printf("Error: Unable to delete the original file.\n");
                return;
            }

    // Rename the copy file to the original name
            if (rename("copy.txt", file) != 0) {
                printf("Error: Unable to rename the replica file.\n");
                return;
            }
    printf("Employee with ID %d updated successfully to all new values: %d,    %s,  %s  ,%d.\n",eid,newId,newFname,newLname,newSal);
}

void updateEmp(char *file){//P2_option 2: To update an employee information
    FILE *fptr;
    int eid; // Employee ID to be updated
    int option;
    int lc=0; //loop controller

    printf("Enter the Employee ID to be modified\n");
    scanf("%d", &eid);

    int c = checkID(file,eid);
    if(c==0){
        printf("Employee not found\n");
        return;
    }
    else{
        printf("Employee found!\n");
        printf("Which information would you like to update?\nSelect:\n");
        printf("Option 1:Employee ID \nOption 2:Employee First Name \nOption 3:Employee Last Name \nOption 4:Employee Salary \nOption 5: All info\n");
        scanf("%d",&option); //scanning user input
        
        switch (option){
            case 1: 
            updateEid(file,eid);
            break;
            case 2:
            updateFname(file,eid);
            break;
            case 3:        
            updateLname(file,eid);
            break;
            case 4:            
            updateEsal(file,eid);
            break;
            case 5:            
            updateAll(file,eid);
            break;
            default : printf("Entered the wrong option\n"); 
            break;
        }        
    }
}

typedef struct {//P2_option 3: Structure for Employee data
    int id;
    char fname[20];
    char lname[20];
    int sal;
} Employee;

void sort(char *file) { //P2_Option 3: Bubble sort for sorting the records in descending order of the salary
    FILE *fptr;
    fptr = fopen(file, "r+");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Employee emp;
    Employee employees[100]; // Assuming a maximum of 100 employees
    int count = 0;

    // Read employee data into an array
    while (fscanf(fptr, "%d %s %s %d", &emp.id, emp.fname, emp.lname, &emp.sal) == 4) {
        employees[count++] = emp;
    }

    // Sort the array of employees based on salary (using bubble sort for simplicity)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (employees[j].sal < employees[j + 1].sal) {
                // Swap employees[j] and employees[j + 1]
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }

    // Write the sorted data back to the file
    rewind(fptr);
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%d %s %s %d\n", employees[i].id, employees[i].fname, employees[i].lname, employees[i].sal);
    }

    fclose(fptr);
    printf("File sorted successfully.\n");
}

void printMEmp(char *file) {//P2_Option3: Prints 'M' Employees with highest salaries
    FILE *fptr;
    int id, sal;
    char fname[20], lname[20];
    int m, count = 0;

    fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the number of employees you want to print: ");
    scanf("%d", &m);

    while (fscanf(fptr, "%d %s %s %d", &id, fname, lname, &sal) == 4 && count < m) {
        printf("ID: %d, Name: %s %s, Salary: %d\n", id, fname, lname, sal);
        count++;
    }

    if (count < m) {
        printf("\nFile has been fully printed. The count you entered is more than the records that exist in the file.\n");
    }

    fclose(fptr);
}

void toLowerCase(char *s) { //P2_option 4: converts all the letters to lower case
    for (int i = 0; s[i]; i++) {
        s[i] = tolower(s[i]);
    }
}

void checkLnameMatch(char *file) {//P2_option 4: Find all last names matching with user input
    FILE *fptr;
    char name[20], lname[20], lname_search[20]; // Last name to be searched 
    int id, sal,lc=0;

    printf("\nEnter the last name to be looked up: ");
    scanf("%s", lname_search);

    // Convert lname_search to lowercase temporarily to ensure the original file is not changed
    char lname_search_lower[20];
    strcpy(lname_search_lower, lname_search);
    toLowerCase(lname_search_lower);

    // Open the file in read mode with file pointer 1
    fptr = fopen(file, "r");

    if (fptr == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Compare lname in file with user input
    while (fscanf(fptr, "%d %s %s %d", &id, name, lname, &sal) == 4) {
        // Convert lname to lowercase temporarily
        char lname_lower[20];
        strcpy(lname_lower, lname);
        toLowerCase(lname_lower);

        if (strcmp(lname_search_lower, lname_lower) == 0) { //checks for all same last name
            printf("\nEmp ID: %d , Emp Name: %s , Emp Lname: %s , Emp Sal: %d\n", id, name, lname, sal);
            lc++;
        }
    }
    if(lc==0){
        printf("Last Name doesnt match any record in DB.\n");
    }

    fclose(fptr); // Close the file after reading
}

void appFlow_p2(char *file){ //P2_Menu for application
    int opt2;

        sort(file);
        printf("\nPart-2 Menu: \n");
        printf("---------------------------------------\n");
        printf("   (1) Remove an employee \n");
        printf("   (2) Update an employee's information \n");
        printf("   (3) Print the M employees with the highest salaries \n");
        printf("   (4) Find all employees with matching first name \n");
        printf("Enter your choice: ");
        scanf("%d", &opt2);

        switch (opt2){
            case 1:
                removeEmp(file);
                break;
            case 2:
                updateEmp(file);            
                break;
            case 3:
                printMEmp(file);
                break;
            case 4:
                checkLnameMatch(file);
                break;
            default:
                printf("Invalid choice.\n");
        }

}

void appFlow(char *file) { //Menu for the application 
    int opt1, lc1 = 0;

    while (lc1 == 0) {
        printf("\nEmployee DB Menu: \n");
        printf("---------------------------------------\n");
        printf("   (1) Print the Database \n");
        printf("   (2) Lookup by ID \n");
        printf("   (3) Lookup by Last Name \n");
        printf("   (4) Add an Employee \n");
        printf("   (5) Quit \n\n");
        printf("Enter your choice: ");
        scanf("%d", &opt1);

        switch(opt1) {
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
                printf("Exiting the first menu. \n");
                ++lc1;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }
    appFlow_p2(file); //after quitting the menu, to continue with 2nd part of program
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
