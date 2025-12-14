#include <stdio.h>
#include "file.h"

#define RESET   "\x1B[0m"
#define BOLD    "\x1B[1m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"


void saveContactsToFile(AddressBook *addressBook) {      //Function definition for function call in contact.c and 
    FILE* fptr = fopen("contacts.csv", "w");
    if(fptr == NULL){
        printf("Error :Failed to open File !\n");
        return;
    }
    // print Total number of contacts from buffer (stored in structure ) to contacts.csv
    fprintf(fptr, "%d\n", addressBook->contactCount);
    
    // print each contact deatils from buffer (stored in structure ) to file contacts.csv
    for(int i = 0; i <  addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s, %s, %s\n",
            addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email );
    }

    fclose(fptr);
    printf(GREEN "Contacts saved Succssfully 💾✔️  \n" RESET);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE* fptr = fopen("contacts.csv", "r");
    if(fptr == NULL)
    {
        printf("File opening failed\n");
        return;
    }
   
    // read Total number of contacts from contacts.csv
    if (fscanf(fptr, "%d", &(addressBook->contactCount)) != 1)
    addressBook->contactCount = 0;        

    /* fscanf("%d") reads ONLY the number.it does NOT eat the newline after the number.
       To avoid this, we manually consume characters until newline.
       Keep reading characters until we reach '\n'.This removes the leftover newline from the buffer,
       so the next fscanf will begin correctly at the start of the next real line. */
    int ch;
    while ((ch = fgetc(fptr)) != EOF && ch != '\n'); 

    // read each contact deatils from file contacts.csv
    for(int i = 0; i <  addressBook->contactCount; i++) {
        fscanf(fptr, " %[^,], %[^,], %[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf(GREEN "\nContacts Loaded Succssfully ✔️  " RESET);
}
