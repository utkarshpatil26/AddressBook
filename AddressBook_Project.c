

    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "contacts.dat"
#define MAX_CONTACTS 100

struct Contact
{
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
};

struct Contact contacts[MAX_CONTACTS];
int contactCount = 0;

/* Function declarations */
void loadContacts();
void saveContacts();
void addContact();
void viewContacts();
void searchContact();
void updateContact();
void deleteContact();
void clearInputBuffer();

int main()
{
    int choice;

    loadContacts();

    while (1)
    {
        printf("\n====================================\n");
        printf("        ADDRESS BOOK SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                viewContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                updateContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                saveContacts();
                printf("\nContacts saved successfully.\n");
                printf("Thank you for using Address Book!\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/* Clear input buffer */
void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

/* Load contacts from file */
void loadContacts()
{
    FILE *file;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        return;
    }

    contactCount = fread(
        contacts,
        sizeof(struct Contact),
        MAX_CONTACTS,
        file
    );

    fclose(file);
}

/* Save contacts to file */
void saveContacts()
{
    FILE *file;

    file = fopen(FILE_NAME, "wb");

    if (file == NULL)
    {
        printf("Error: Could not save contacts.\n");
        return;
    }

    fwrite(
        contacts,
        sizeof(struct Contact),
        contactCount,
        file
    );

    fclose(file);
}

/* Add contact */
void addContact()
{
    if (contactCount >= MAX_CONTACTS)
    {
        printf("\nAddress book is full!\n");
        return;
    }

    printf("\n========== ADD CONTACT ==========\n");

    printf("Enter name: ");
    fgets(
        contacts[contactCount].name,
        sizeof(contacts[contactCount].name),
        stdin
    );

    contacts[contactCount].name[
        strcspn(contacts[contactCount].name, "\n")
    ] = '\0';


    printf("Enter phone number: ");
    fgets(
        contacts[contactCount].phone,
        sizeof(contacts[contactCount].phone),
        stdin
    );

    contacts[contactCount].phone[
        strcspn(contacts[contactCount].phone, "\n")
    ] = '\0';


    printf("Enter email: ");
    fgets(
        contacts[contactCount].email,
        sizeof(contacts[contactCount].email),
        stdin
    );

    contacts[contactCount].email[
        strcspn(contacts[contactCount].email, "\n")
    ] = '\0';


    printf("Enter address: ");
    fgets(
        contacts[contactCount].address,
        sizeof(contacts[contactCount].address),
        stdin
    );

    contacts[contactCount].address[
        strcspn(contacts[contactCount].address, "\n")
    ] = '\0';

    contactCount++;

    saveContacts();

    printf("\nContact added successfully!\n");
}

/* View all contacts */
void viewContacts()
{
    int i;

    if (contactCount == 0)
    {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n========== ALL CONTACTS ==========\n");

    for (i = 0; i < contactCount; i++)
    {
        printf("\nContact %d\n", i + 1);
        printf("-----------------------------\n");
        printf("Name    : %s\n", contacts[i].name);
        printf("Phone   : %s\n", contacts[i].phone);
        printf("Email   : %s\n", contacts[i].email);
        printf("Address : %s\n", contacts[i].address);
    }
}

/* Search contact */
void searchContact()
{
    char search[50];
    int i;
    int found = 0;

    if (contactCount == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\nEnter name or phone to search: ");

    fgets(search, sizeof(search), stdin);

    search[strcspn(search, "\n")] = '\0';

    for (i = 0; i < contactCount; i++)
    {
        if (
            strstr(contacts[i].name, search) != NULL ||
            strstr(contacts[i].phone, search) != NULL
        )
        {
            printf("\nContact found!\n");
            printf("-----------------------------\n");
            printf("Name    : %s\n", contacts[i].name);
            printf("Phone   : %s\n", contacts[i].phone);
            printf("Email   : %s\n", contacts[i].email);
            printf("Address : %s\n", contacts[i].address);

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nContact not found.\n");
    }
}

/* Update contact */
void updateContact()
{
    char search[50];
    int i;
    int found = 0;

    if (contactCount == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\nEnter name or phone of contact to update: ");

    fgets(search, sizeof(search), stdin);

    search[strcspn(search, "\n")] = '\0';

    for (i = 0; i < contactCount; i++)
    {
        if (
            strstr(contacts[i].name, search) != NULL ||
            strstr(contacts[i].phone, search) != NULL
        )
        {
            printf("\nContact found.\n");
            printf("Enter new details:\n");

            printf("New name: ");
            fgets(
                contacts[i].name,
                sizeof(contacts[i].name),
                stdin
            );

            contacts[i].name[
                strcspn(contacts[i].name, "\n")
            ] = '\0';


            printf("New phone: ");
            fgets(
                contacts[i].phone,
                sizeof(contacts[i].phone),
                stdin
            );

            contacts[i].phone[
                strcspn(contacts[i].phone, "\n")
            ] = '\0';


            printf("New email: ");
            fgets(
                contacts[i].email,
                sizeof(contacts[i].email),
                stdin
            );

            contacts[i].email[
                strcspn(contacts[i].email, "\n")
            ] = '\0';


            printf("New address: ");
            fgets(
                contacts[i].address,
                sizeof(contacts[i].address),
                stdin
            );

            contacts[i].address[
                strcspn(contacts[i].address, "\n")
            ] = '\0';

            saveContacts();

            printf("\nContact updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nContact not found.\n");
    }
}

/* Delete contact */
void deleteContact()
{
    char search[50];
    int i;
    int j;
    int found = 0;

    if (contactCount == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\nEnter name or phone of contact to delete: ");

    fgets(search, sizeof(search), stdin);

    search[strcspn(search, "\n")] = '\0';

    for (i = 0; i < contactCount; i++)
    {
        if (
            strstr(contacts[i].name, search) != NULL ||
            strstr(contacts[i].phone, search) != NULL
        )
        {
            printf("\nContact found:\n");
            printf("Name  : %s\n", contacts[i].name);
            printf("Phone : %s\n", contacts[i].phone);

            for (j = i; j < contactCount - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }

            contactCount--;

            saveContacts();

            printf("\nContact deleted successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nContact not found.\n");
    }
}