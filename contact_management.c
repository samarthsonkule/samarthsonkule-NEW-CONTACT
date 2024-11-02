#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LEN 50
#define PHONE_LEN 15
#define EMAIL_LEN 50
#define FILENAME "contacts.txt"

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void loadContacts();
void saveContacts();
void addContact();
void viewContacts();
void editContact();
void deleteContact();

int main() {
    loadContacts();
    int choice;

    do {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                saveContacts();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void loadContacts() {
    FILE *file = fopen(FILENAME, "r");
    if (file) {
        while (fscanf(file, "%49[^,],%14[^,],%49[^\n]\n", 
                      contacts[contactCount].name, 
                      contacts[contactCount].phone, 
                      contacts[contactCount].email) == 3) {
            contactCount++;
        }
        fclose(file);
    }
}

void saveContacts() {
    FILE *file = fopen(FILENAME, "w");
    if (file) {
        for (int i = 0; i < contactCount; i++) {
            fprintf(file, "%s,%s,%s\n", 
                    contacts[i].name, 
                    contacts[i].phone, 
                    contacts[i].email);
        }
        fclose(file);
    }
}

void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }
    printf("Enter name: ");
    fgets(contacts[contactCount].name, NAME_LEN, stdin);
    contacts[contactCount].name[strcspn(contacts[contactCount].name, "\n")] = '\0'; // Remove newline

    printf("Enter phone: ");
    fgets(contacts[contactCount].phone, PHONE_LEN, stdin);
    contacts[contactCount].phone[strcspn(contacts[contactCount].phone, "\n")] = '\0';

    printf("Enter email: ");
    fgets(contacts[contactCount].email, EMAIL_LEN, stdin);
    contacts[contactCount].email[strcspn(contacts[contactCount].email, "\n")] = '\0';

    contactCount++;
    printf("Contact added successfully!\n");
}

void viewContacts() {
    if (contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }
    printf("\nContacts:\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%d. %s, %s, %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void editContact() {
    int index;
    viewContacts();
    printf("Enter the number of the contact to edit: ");
    scanf("%d", &index);
    getchar(); // to consume the newline character

    if (index < 1 || index > contactCount) {
        printf("Invalid contact number.\n");
        return;
    }
    index--; // Adjust index for 0-based array

    printf("Editing contact: %s\n", contacts[index].name);
    printf("Enter new name (or press enter to keep current): ");
    char newName[NAME_LEN];
    fgets(newName, NAME_LEN, stdin);
    if (strcmp(newName, "\n") != 0) {
        newName[strcspn(newName, "\n")] = '\0'; // Remove newline
        strcpy(contacts[index].name, newName);
    }

    printf("Enter new phone (or press enter to keep current): ");
    char newPhone[PHONE_LEN];
    fgets(newPhone, PHONE_LEN, stdin);
    if (strcmp(newPhone, "\n") != 0) {
        newPhone[strcspn(newPhone, "\n")] = '\0';
        strcpy(contacts[index].phone, newPhone);
    }

    printf("Enter new email (or press enter to keep current): ");
    char newEmail[EMAIL_LEN];
    fgets(newEmail, EMAIL_LEN, stdin);
    if (strcmp(newEmail, "\n") != 0) {
        newEmail[strcspn(newEmail, "\n")] = '\0';
        strcpy(contacts[index].email, newEmail);
    }

    printf("Contact updated successfully!\n");
}

void deleteContact() {
    int index;
    viewContacts();
    printf("Enter the number of the contact to delete: ");
    scanf("%d", &index);
    getchar(); // to consume the newline character

    if (index < 1 || index > contactCount) {
        printf("Invalid contact number.\n");
        return;
    }
    index--; // Adjust index for 0-based array

    for (int i = index; i < contactCount - 1; i++) {
        contacts[i] = contacts[i + 1]; // Shift contacts left
    }
    contactCount--;
    printf("Contact deleted successfully!\n");
}
