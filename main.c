#include <stdio.h>
#include "contact.h"

#define RESET   "\x1B[0m"
#define BOLD    "\x1B[1m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

int main() {
    int choice;
    AddressBook addressBook;    //Declaring the varaible addressBook with data types of AddressBook (structure)
    initialize(&addressBook);    // Initialize the address book

    do {
        printf(BOLD CYAN "\n------------------------------------------\n");
        printf("   Hi Buddy 👋  WELCOME TO ADDRESS BOOK     \n");
        printf("------------------------------------------\n" RESET);
        printf("Address Book Menu:\n");
        printf("1. Create contact 🆕\n");
        printf("2. Search contact 🔎\n");
        printf("3. Edit contact 📝\n");
        printf("4. Delete contact 🗑️\n");
        printf("5. List all contacts 📑\n");
    	printf("6. Save contacts 💾\n"); 
        printf("7.  Exit 🛑\n");
        printf(CYAN "------------------------------------------\n" RESET);
        printf(BOLD "Enter your choice: " RESET);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);          //Function calls
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf(RED "Exiting the Addressbook ➡️  .....\n" RESET);
                printf(GREEN "Have a good day 😊 ...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice. Please try again ❗ \n" RESET);
        }
    } while (choice != 7);

    return 0;
}
