#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {             //contact Structure Definition 
    char name[50];
    char phone[20];
    char email[50];
} Contact;              //Structure name

typedef struct {                //AddressBook Structure Definition
    Contact contacts[100];   //declaring the varaible of data type Contact structure inside the AdresssBook structure
    int contactCount;
} AddressBook;

//Functions Declarations for function definitions in contact.c
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);   //, int sortCriteria
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
