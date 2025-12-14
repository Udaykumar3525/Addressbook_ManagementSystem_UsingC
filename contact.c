#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"

#define RESET   "\x1B[0m"
#define BOLD    "\x1B[1m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

void listContacts(AddressBook *addressBook) //, int sortCriteria
{
    if (addressBook->contactCount==0)
    {
        printf(RED "No contacts Saved !" RESET);
        return;
    }
    // Sort contacts based on the names - alphabetical order - Using bubble sort
    //Strcasecmp return value(+ve > 0 then str1 comes After str2 alphabetically , else(-ve)  str1 comes Before str2, 0 - Both strings are equal
    for (int i = 0; i < addressBook->contactCount - 1; i++)          //outer loop 
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)    //inner loop to compare names in last
        { 
            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) //compare adjacent names in contact list
            {
                Contact store = addressBook->contacts[j];                          //swap logic
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = store;
            }
        }
    }
    //To print the sorted list of contacts
    printf("\n");
    printf(BOLD YELLOW"                         -> All contacts list <-\n" RESET);
    const char *strline="-----------------------------------------------------------------------------";
    printf(" %s\n",strline);
    printf(BOLD MAGENTA "| %-4s | %-21s | %-14s | %-27s |\n" RESET,"S.NO", "NAME", "PHONE NUMBER", "EMAIL ID" );
    printf(" %s\n",strline);
    for(int i=0;i < addressBook->contactCount;i++)
    {
        //display name , phone number, email
        printf("| %-4d | %-21s | %-14s | %-27s |\n",
               i+1,
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email); 
    }
    printf(" %s\n",strline);
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)       //To Create the contact
{
    if(addressBook->contactCount >= MAX_CONTACTS)    //max contacts that addressbook can hold is 100
    {
        printf("📕 Address book is full!\n");
        return;
    }

    char again;
    do{
        char name[30];
        int res;
        printf(MAGENTA"--------> Creat 🆕 contact <--------\n"RESET);
        printf("Enter the name : ");
        do{                                  //Runs until user enter valid name 
            scanf(" %[^\n]",name);
            res=validation_name(name);    //Validate user entered number is valid or not
            if (res !=1 )               
                printf(RED "⚠️  Error : Incorrect name formate - %s\n" RESET
                    "Enter the correct name : ",name);
        } while (res != 1);         //if name is not valid , loop called again

        char phone_no[20];
        printf("Enter the number : ");
        do{                                   //loop for valid number              
            scanf("%s",phone_no);
            res = validation_number(phone_no);       //validate the user eneterd number
            if (!res)
            {
                printf(RED "⚠️  Error : Incorrect number format - %s\n" RESET,phone_no);
                printf("Enter correct number: ");
                continue;                             //skips the duplicate check
            }

            // Verifies whether the number entered by the user already exists in the book or not
            for(int i=0; i < addressBook->contactCount; i++){                
                if(strcmp(phone_no, addressBook->contacts[i].phone) == 0){     //present
                    printf(RED "Error : %s, This Number already exists!\n" RESET,phone_no);
                    printf("Enter a new number: ");
                    res=0;
                    break;         //stops the for loop for comparing
                }
            }
        } while (res != 1);       // if not a vlid number ,restart loop immediately

        char email[50];
        printf("Enter the email : ");
        do{                                //loop for valid Email
            scanf("%s",email); 
            res=validation_email(email);    //validates the user entered email   
            if (!res)
            {
                printf(RED "⚠️  Error : Incorrect email formate - %s\n" RESET,email);   
                printf("Enter the correct email : ");
                continue;                                 //skips the duplicate check
            }

            // Verifies whether the Email entered by the user already exists in the book or not
            for(int i=0; i < addressBook->contactCount; i++){             
                if(strcmp(email, addressBook->contacts[i].email) == 0){
                    printf(RED "Error : %s,This email already exists!\n" RESET,email);
                    printf("Enter a new email: ");
                    res=0;
                    break;         //stops the for loop for comparing
                }
            }   

        } while (res != 1);

        //storing the all readed data into address book
        int index = addressBook->contactCount;
        Contact *c = &addressBook->contacts[index];             // pointer to that contact for convenience
        // copying the strings name,email,number from local buffers into struct fields
        strcpy(c->name,  name);
        strcpy(c->phone, phone_no);
        strcpy(c->email, email);

        addressBook->contactCount++;    //increasing total contact count
        printf(GREEN "Contact added successfully ✔️ \n" RESET);

        printf(BOLD "Are you really want to exit from Create contact ? (y/n): " RESET);
        getchar();
        scanf("%c",&again);
    }while(again == 'n');
    printf(GREEN "Exiting successfully ➡️  ....\n" RESET);
}

void searchContact(AddressBook *addressBook)  //To search for a contact in contact list stored in csv file
{
    char again;
    do{                                    //Loop for another search based on user preference
        int res=0,choice,count=0,index;
        char name[50],number[20],email[30];
        
        printf(MAGENTA "\n-------->🔎 Search Contact by <--------\n" RESET);
        printf("1.Name  2.Phone.no  3.Email.id  4.Exit\n");
        printf("Enter the choice : ");
        scanf("%d",&choice);
            
        switch(choice) 
        {
            case 1:       //Search by name
            {
                printf(YELLOW "Enter the name to search : " RESET);
                do{
                    scanf(" %[^\n]",name);
                    res=validation_name(name);     //check for valid name 
                    if (res)                    //if valid name , excute the next steps
                    {
                        for (int i=0; i<addressBook->contactCount; i++)     
                        {
                            if(strcmp(name, addressBook->contacts[i].name) == 0){     //check the entered name is there or not
                                printf("S.No %d -> Name - %s, phone.no - %s, Email - %s\n",
                                i+1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                                count++;                                            //make us to know multipple contacts are present with that name
                                index=i;                                          //stores the index of that name
                            }
                        }
                        if (count==0)                        //No contact 
                        printf( RED "No contact found with this Name 🔍❌  \n" RESET);

                        else if(count == 1){           //single contact
                            printf(GREEN"1 Contact Found ✅ ...\n"RESET);
                            printf("Name  = %s\n", addressBook->contacts[index].name);
                            printf("Phone = %s\n", addressBook->contacts[index].phone);
                            printf("Email = %s\n", addressBook->contacts[index].email);
                        }
                        else         //multiple contacts with same name
                        {
                            printf(RED "Found %d contacts with same name ❗ \n" RESET,count);
                            printf("Please Try again with number or email to find the contact u r searching for!\n");    //number is unique for every contact
                            break;
                        }
                    }
                    else     //if not a valid name
                    printf(RED "⚠️  Error : Entered name %s is not correct!\n" RESET
                        "Enter the valid name: ",name);
                } while (res != 1);    //for name
                break;               //avoids the fall through (step into next case)
            }
            case 2:    //Search by number
            {
                count=0;
                printf(YELLOW "Enter the number to Search : " RESET);
                do{
                    scanf("%s",number);
                    res=validation_number(number);     //check for valid Number 
                    if (res)                    //if number is valid, excute the next steps
                    {
                        for (int i=0; i<addressBook->contactCount; i++)     
                        {
                            if(strcmp(number, addressBook->contacts[i].phone) == 0){     //check the entered number is there or not
                                printf(GREEN "Contact Found ✅ ...\n" RESET);
                                printf("Name  = %s\n", addressBook->contacts[i].name);
                                printf("Phone = %s\n", addressBook->contacts[i].phone);
                                printf("Email = %s\n", addressBook->contacts[i].email); 
                                count=1;
                            }
                        }
                        if (count==0)                       //No contact 
                        printf(RED "No contact found with this number 🔍❌  \n" RESET);
                    }
                    else     //if not a valid number
                    printf(RED "⚠️  Error : Entered number%s is not correct!\n" RESET
                        "Enter the valid number: ",number);
                } while (res != 1);                                 //Loop runs until user Enter valid number
                break;               //avoids the fall through (step into next case)
            }
            case 3:    //Search by email
            {
                count=0;
                printf(YELLOW "Enter the email to Search : " RESET);
                do{
                scanf("%s",email);
                res=validation_email(email);     //check for valid email
                if (res)                    //if Entered email is valid, excute the next steps
                {
                    for (int i=0; i<addressBook->contactCount; i++)     
                    {
                        if(strcmp(email, addressBook->contacts[i].email) == 0){     //check the entered email is there or not
                            printf(GREEN "Contact Found ✅ ...\n" RESET);
                            printf("Name  = %s\n", addressBook->contacts[i].name);
                            printf("Phone = %s\n", addressBook->contacts[i].phone);
                            printf("Email = %s\n", addressBook->contacts[i].email); 
                            count=1;
                        }
                    }
                    if (count==0)                       //No contact 
                    printf(RED "No contact found with this email 🔍❌  \n" RESET);
                }
                else     //if not a valid email
                printf(RED "⚠️  Error : Entered email %s is not correct!\n" RESET
                    "Enter the valid email: ",email);
                } while (res != 1);                      //Loops runs until user enter valid email
                break;               //avoids the fall through (step into next case)
            }
        }
        printf(BOLD "Are you really want to exit from Search ? (y/n): " RESET);
        getchar();
        scanf("%c",&again);
    }while(again == 'n');       //Loop for Another Search
    printf(GREEN "Exiting the search ➡️  ...\n" RESET);
}

void editContact(AddressBook *addressBook)   //To Edit the contact in contact list stored in csv file
{
    char again='n';
    do {                                      //Loop for another edit based on user preference
        int res=0,choice,count=0,index=0,i;
        char name[50],newname[50];
        char number[20],newnumber[20];
        char email[30],newemail[30];
                                              
        printf(MAGENTA "\n-------->📝 Edit Contact by <--------\n" RESET);
        printf("1.Name  2.Phone.no  3.Email.id  4.Exit\n");
        printf("Enter the choice : ");
        scanf("%d",&choice);
            
        switch(choice)
        {
            case 1:        //Edit by Name
            {
                printf(YELLOW "Enter the name to Edit : " RESET);
                do{
                    scanf(" %[^\n]",name);
                    res=validation_name(name);     //check for valid name 
                    if (res != 1)
                    printf(RED "⚠️  Error : Entered name %s is not correct!\n" RESET
                                "Enter the valid Name: ",name);
                }while (res != 1);                               //Loop for valid Name from user

                //Matching contacts
                for (i=0; i<addressBook->contactCount; i++){
                    if(strcmp(name, addressBook->contacts[i].name) == 0){           //comapring entered name is in list or not
                         printf("Index %d -> Name - %s, phone.no - %s, Email - %s\n",
                                i,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);                  
                        index=i;
                        count++;
                    }
                }
                if (count==0)                   //No contact 
                printf(RED "No contact found With this name 🔍❌  \n" RESET);
                else
                {
                    choice=0;
                    if (count>1)            //More than 1 contact is found with that name 
                    {
                        printf(RED "Found %d Contacts With same name ❗ \n" RESET,count);
                        printf("Enter the index u want to edit: ");
                        scanf("%d",&index);
                    }
                    else
                    printf(GREEN "1 Contact Found ✅ ...\n" RESET);

                    printf("Enter the new name: ");     
                    do{
                        scanf("%s",newname);            //asking user for new name to edit
                        res=validation_name(newname);
                        if (res != 1)
                        printf(RED "⚠️  Error : Entered name %s is not correct!\n" RESET
                            "Enter the valid Name: ",newname);
                    }while (res != 1);
                    strcpy(addressBook->contacts[index].name,newname);      //changing Name
                    printf(GREEN"Changing Name from %s -> %s.....Name updated successfully ✔️ \n"RESET,name,newname);
                }
                break;               //avoids the fall through (step into next case)
            } 
            case 2:   //Edit by number
            {
                printf(YELLOW "Enter the number to Edit : " RESET);
                do{
                scanf("%s",number);
                res=validation_number(number);     //check for valid number
                if (res != 1)
                printf(RED "⚠️  Error : Entered number %s is not correct!\n" RESET
                                    "Enter the valid number: ",number);
                }while (res != 1);       //Runs until user enter the valid number

                //Matching contacts
                for (i=0; i<addressBook->contactCount; i++){                  //Loop for searching number in list
                    if(strcmp(number, addressBook->contacts[i].phone) == 0){       //if the number matches with numbers in list
                        printf(GREEN "Contact Found ✅ ...\n" RESET);
                        printf("S.No %d -> Name - %s, phone.no - %s, Email - %s\n",    //prints the matching contact with that number
                                i+1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                        printf("Enter the new number: ");
                        do{
                            scanf("%s",newnumber);              //Asking user for newnumber to change
                            res=validation_number(newnumber);
                            if (res != 1) {
                                printf(RED "⚠️  Error : %s is not a valid number !\n" RESET
                                            "Enter a valid number : ",newnumber);
                                continue;    //skips the duplicate number checking if enterd number is not valid number
                            }
                            
                            //checks whether the entered new number is already present in list or not 
                            for(int i=0; i < addressBook->contactCount; i++){                
                                if(strcmp(newnumber, addressBook->contacts[i].phone) == 0){                   // matching with list
                                    printf(RED "Error : %s, This Number already exists ❗ \n" RESET,newnumber);
                                    printf("Enter a valid new number: ");
                                    res = 0; 
                                    break;
                                }
                            }
                        }while (res != 1);                                    //Loops Runs until user enter the valid Newnumber to edit
                        strcpy(addressBook->contacts[i].phone,newnumber);          //Changing the old number with new number
                        printf(GREEN "Changing Number %s -> %s ......Number updated successfully ✔️ \n" RESET,number,newnumber);
                        count++;
                    }
                }
                if (count==0)                   //No contact 
                printf(RED "No contact found with this Number 🔍❌  \n" RESET);
                break;               //avoids the fall through (step into next case)
            }
            case 3:       //Edit by Email
            {
                printf(YELLOW "Enter the email to Edit : " RESET);
                do{
                scanf("%s",email);
                res=validation_email(email);     //check for valid number
                if (res != 1)
                printf(RED "⚠️  Error : Entered email %s is not correct!\n" RESET
                                    "Enter the valid email: ",email);
                }while (res != 1);              //Loop runs until user enter valid email

                //Matching contacts
                for (i=0; i<addressBook->contactCount; i++){                  //Loop for searching the email in list
                    if(strcmp(email, addressBook->contacts[i].email) == 0){     //If there is a match then executes the next steps to change it
                        printf(GREEN "Contact Found ✅ ...\n" RESET);
                        printf("S.No %d -> Name - %s, phone.no - %s, Email - %s\n",    //prints the matching contact with that entered email
                                i+1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                        printf("Enter the new email: ");
                        do{
                            scanf("%s",newemail);
                            res=validation_email(newemail);
                            if (res != 1){
                                printf(RED "⚠️  Error : %s is not a valid email !\n" RESET
                                            "Enter the valid Email : ",newemail);
                                continue;
                            }
                            
                            //checks whether the entered new Email is already present in list or not
                            for(int i=0; i < addressBook->contactCount; i++){                
                                if(strcmp(newemail, addressBook->contacts[i].email) == 0){                    //if there is a match
                                    printf(RED "Error : %s, This Email already exists ❗\n" RESET,newemail);
                                    printf("Enter a valid new Email: ");
                                    res = 0; 
                                    break;
                                }
                            }
                        }while (res != 1);                                 //Runs until user enter valid new email 
                        strcpy(addressBook->contacts[i].email,newemail);
                        printf(GREEN "Changing email %s -> %s......email updated successfully ✔️ \n" RESET,email,newemail);
                        count++;
                    }
                }
                if (count==0)                   //No contact 
                printf(RED "No contact found with this email 🔍❌  \n" RESET);
                break;               //avoids the fall through (step into next case)
            } 
        }
        printf(BOLD "Are you really want to exit from Edit contact ? (y/n): " RESET);
        getchar();
        scanf("%c",&again);
    }while(again == 'n');          //Loop for another Edit based on user choice 
    printf(GREEN "Exiting the Edit ➡️  ....\n" RESET);
}

void deleteContact(AddressBook *addressBook)   //To search delete the contact in contact list stored in csv file
{
    char again='n';
    do{
        int choice,res=0,delindex = -1,firstindex = -1,Count=0;
        char email[50],name[50],number[20];
        
        printf(MAGENTA "\n--------> 🗑️   Delete Contact by <--------\n" RESET);
        printf("1.Name  2.Phone.no  3.Email.id  4.Exit\n");
        printf("Enter the choice : ");
        scanf(" %d",&choice);
            
         switch (choice)
        {
            case 1:         //Delete by Name
            {
                printf(YELLOW "Enter the name to Delete : " RESET);
                do
                {
                    scanf(" %[^\n]", name);
                    res = validation_name(name);
                    if (res != 1)
                        printf(RED "⚠️  Error : Entered name %s is invalid !\n" RESET
                                    "Enter valid name again : ", name);
                } while (res != 1);                                     //Loop Runs until User enter the valid name to delete 

                //Show all contacts with that name
                for (int i = 0; i < addressBook->contactCount; i++)     //loop to check the no.of contacts with that name
                {
                    if (strcmp(name, addressBook->contacts[i].name) == 0)   //compares the entered anme with names in list 
                    {
                        printf("S.No %d -> Name - %s, phone.no - %s, Email - %s\n",
                            i+1,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        Count++;
                        firstindex = i;                         //if match stored the index of that contact
                    }
                }

                if (Count == 0){       //No contact
                printf(RED "No contact found with that name 🔍❌  \n" RESET);
                break;
                }

                // if Only one ..> deletes that index directly
                else if (Count == 1)
                delindex = firstindex;

                else    //more than 1 contact founds with that name
                {
                    // if More than one - ask phone number or email to identify
                    printf(RED "More than one contact has this name ❗\n" RESET);
                    printf("Please Try again with phone number or email id to delete the contact \n");
                    break;
                }
                // Delete contact at delIndex (shift left)
                for (int i = delindex; i < addressBook->contactCount - 1; i++)
                addressBook->contacts[i] = addressBook->contacts[i + 1];

                addressBook->contactCount--;     //delete means count will reduce

                printf(GREEN "Contact deleted successfully ✔️ \n" RESET);
                break;
            }
            case 2:              //Delete by number
            {
                printf(YELLOW "Enter phone number to delete : " RESET);
                do
                {
                    scanf("%s", number);  
                    res = validation_number(number);     //Number validation
                    if (res != 1)
                        printf(RED "⚠️ Error : Number is %s Invalid !\n" RESET
                                    "Enter the valid number again : ", number);
                } while (res != 1);            //Loop runs until user enter valid phone number

                // loop to search contact with this phone number
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(number, addressBook->contacts[i].phone) == 0){   //match
                        printf(GREEN "Contact Found ✅ ...\n" RESET);
                        printf("S.No %d -> Name - %s, phone.no - %s, Email - %s\n",   //prints the matching contact with that number
                                i+1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);
                        delindex = i;      //if entered number matches with number in list, stores that index
                        break;
                    }
                }
                if (delindex == -1)    //indexs only +ve , if -ve means no delindex updated before..>no contact
                {
                    printf(RED " No contact found with this number 🔍❌  \n" RESET);
                    break;
                }
                //moving contacts to on step left , bacause u connot delete a item in array , u can just change the indexs 
                for (int i = delindex; i < addressBook->contactCount - 1; i++)
                addressBook->contacts[i] = addressBook->contacts[i + 1];
                
                addressBook->contactCount--;     //decrement

                printf(GREEN "Contact deleted successfully ✔️ \n" RESET);
                break;
            }

            case 3:    //Delete by email
            {
                printf(YELLOW "Enter email to delete : " RESET);
                do
                {
                    scanf("%s", email);
                    res = validation_email(email);     //email validation
                    if (res != 1)
                        printf(RED "⚠️ Error : Enetered email  is %s Invalid !\n" RESET
                                        "Enter the valid email again : ", email);
                } while (res != 1);    //loop runs until user enter valid email

                for (int i = 0; i < addressBook->contactCount; i++)    //loop to find the entered email is in list or not
                {
                    if (strcmp(email, addressBook->contacts[i].email) == 0){  //if matched  
                        printf(GREEN "Contact Found ✅ ...\n" RESET);
                        printf("S.No %d -> Name - %s, phone.no - %s, Email - %s\n",   //prints the matching contact with that email
                                i+1,
                                addressBook->contacts[i].name,
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email);                                      
                        delindex = i;     //stores that contact index to delete
                        break;
                    }
                }

                if (delindex == -1)   //if no index updated means no contact found in liss with user entered email 
                {
                    printf(RED "No contact found with this email 🔍❌  \n" RESET);
                    break;
                }

                //loop to step back...>left
                for (int i = delindex; i < addressBook->contactCount - 1; i++)  
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;   //decrement after delete

                printf(GREEN "Contact deleted successfully ✔️ \n" RESET);
                break;
            }
        }
        printf(BOLD "Are you really want to exit from Delete contact? (y/n): " RESET);
        getchar();
        scanf("%c",&again);
    }while(again == 'n');      //Loop for another deleteion - based on user choice
    printf(GREEN "Exiting the Delete ➡️  ....\n" RESET);
}