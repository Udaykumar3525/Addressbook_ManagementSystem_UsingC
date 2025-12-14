#ifndef FILE_H
#define FILE_H

#include "contact.h"

//Functions Declarations for function definitions in file.c
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
