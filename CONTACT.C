#include <stdio.h>
#include <string.h>
#include <conio.h>

struct contact {
    char name[30];
    char phone[15];
};

void addContact();
void viewContacts();
void searchContact();
void deleteContact();
void updateContact();

int main() {
    int choice;
    do {
        clrscr();
        puts("=================================");
        puts("   CONTACT MANAGEMENT SYSTEM");
        puts("=================================");
        puts("1. Add Contact");
        puts("2. View All Contacts");
        puts("3. Search Contact");
	puts("4. Delete Contact ");
        puts("5. Update Contact");
        puts("6. Exit");
        printf("Enter choice: ");
        
        fflush(stdin); 
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }
        
        switch(choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: updateContact(); break;
        }
        
	if (choice != 6) {
            puts("\n\nPress any key to return to Menu..."); 
            getch(); 
        }
    } while(choice != 6);
    return 0;
}

void addContact() {
    FILE *fp;
    struct contact c, temp;
    char inputPhone[15];
    int duplicate = 0;

    clrscr();
    while(1) {
        printf("Enter 10-digit Phone: ");
        scanf("%s", inputPhone);
        if (strlen(inputPhone) == 10) break;
        else puts("Error: Must be 10 digits!");
    }

    fp = fopen("contacts.dat", "rb");
    if (fp != NULL) {
        while(fread(&temp, sizeof(struct contact), 1, fp)) {
            if (strcmp(temp.phone, inputPhone) == 0) { 
                duplicate = 1; 
                break; 
            }
        }
        fclose(fp);
    }

    if (duplicate) { 
        puts("\nError: Number already exists!"); 
    } else {
        strcpy(c.phone, inputPhone);
        printf("Enter Name: ");
        fflush(stdin); 
        scanf(" %[^\n]", c.name);
        fp = fopen("contacts.dat", "ab");
        fwrite(&c, sizeof(c), 1, fp);
        fclose(fp);
        puts("\nContact saved!");
    }
}

void viewContacts() {
    FILE *fp = fopen("contacts.dat", "rb");
    struct contact list[100], temp;
    int i, j, count = 0;

    clrscr();
    if (fp == NULL) { 
        puts("\nNo contacts found."); 
        return; 
    }

    while(fread(&list[count], sizeof(struct contact), 1, fp)) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        puts("\nList is empty.");
        return;
    }

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (stricmp(list[j].name, list[j+1].name) > 0) {
                temp = list[j]; 
                list[j] = list[j+1]; 
                list[j+1] = temp;
            }
        }
    }

    printf("TOTAL CONTACTS: %d\n\n", count);
    puts("S.No  NAME                 PHONE");
    puts("--------------------------------------------");
    
    for (i = 0; i < count; i++) {
        printf("%-5d %-20s %-15s\n", i + 1, list[i].name, list[i].phone);
    }
}

void deleteContact() {
    FILE *fp = fopen("contacts.dat", "rb");
    struct contact list[100], temp;
    int i, j, count = 0, delChoice;
    char confirm;

    clrscr();
    if (fp == NULL) { 
        puts("\nNo contacts."); 
        return; 
    }
    
    while(fread(&list[count], sizeof(struct contact), 1, fp)) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        puts("\nList is empty."); 
        return; 
    }

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (stricmp(list[j].name, list[j+1].name) > 0) {
                temp = list[j]; 
                list[j] = list[j+1]; 
                list[j+1] = temp;
            }
        }
    }

    puts("--- DELETE MENU ---");
    for (i = 0; i < count; i++) {
        printf("%d. %-20s %-15s\n", i + 1, list[i].name, list[i].phone);
    }

    printf("\nEnter S.No to delete (0 to cancel): ");
    scanf("%d", &delChoice);

    if (delChoice > 0 && delChoice <= count) {
        printf("Confirm delete %s? (y/n): ", list[delChoice-1].name);
        confirm = getch();
        if (confirm == 'y' || confirm == 'Y') {
            fp = fopen("contacts.dat", "wb");
            for (i = 0; i < count; i++) {
                if (i != (delChoice - 1)) {
                    fwrite(&list[i], sizeof(struct contact), 1, fp);
                }
            }
            fclose(fp);
            puts("\nDeleted successfully!");
        }
    }
}

void searchContact() {
    FILE *fp = fopen("contacts.dat", "rb");
    struct contact c;
    char search[30];
    int found = 0;
    clrscr();
    printf("Enter Name or Number: ");
    scanf("%s", search);
    if (fp != NULL) {
        while(fread(&c, sizeof(struct contact), 1, fp)) {
            if(stricmp(c.name, search) == 0 || strcmp(c.phone, search) == 0) {
                printf("\nFound: %s - %s", c.name, c.phone);
                found = 1;
            }
        }
        fclose(fp);
    }
    if(!found) puts("\nNot found.");
}

void updateContact() {
    FILE *fp = fopen("contacts.dat", "rb+");
    struct contact c;
    char upNum[15];
    int found = 0;
    clrscr();
    printf("Enter Phone Number to update: ");
    scanf("%s", upNum);
    if (fp != NULL) {
        while(fread(&c, sizeof(struct contact), 1, fp)) {
            if(strcmp(c.phone, upNum) == 0) {
                printf("\nCurrent Name: %s", c.name);
                printf("\nEnter New Name: ");
                fflush(stdin);
                scanf(" %[^\n]", c.name);
                fseek(fp, -sizeof(struct contact), SEEK_CUR);
                fwrite(&c, sizeof(struct contact), 1, fp);
                found = 1; 
                puts("\nUpdated!");
                break;
            }
        }
        fclose(fp);
    }
    if(!found) puts("\nNot found.");
}





