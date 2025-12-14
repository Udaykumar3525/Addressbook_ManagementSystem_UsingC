.......................... > Address Book Application (C Project) < .......................

Name : Udaykumar Upputuri
Email : udayupputuri3525@gmail.com

1. Project Description -

This project is a  Address Book application written in C. It allows users to create, search, edit, delete, list, and save contact information. Each contact contains a Name, Phone Number, and Email ID. Contacts are stored in memory during runtime and saved to contacts.csv for future use.

2. Purpose and Advantages

- Demonstrates modular programming using multiple .c and .h files.
- Provides practical experience in C file handling and structured data management.
- Implements CRUD(Create,Read,Update,Delete) operations in a real-world style mini-project.
- Includes input validation for better data consistency.
- Serves as a foundational project for larger systems like phonebooks or student databases.

3. Project File Structure

----------------------------------------------------------------------------------------------------------------
File Name	                 Description
----------------------------------------------------------------------------------------------------------------
1.main.c	                 Entry point; handles menu and user interaction.
2.contact.c	                 mplements core functionalities such as create, search, edit, delete, and list.
3.contact.h	                 Contains structure definitions and declarations for contact-related functions.
4.file.c	                 Handles reading from and writing to contacts.csv.
5.file.h	                 Declares file handling functions.
6.validation.c	             For validation functions.
7.validation.h               Declarations for validation functions.
8.contacts.csv	             Data file storing all contact records.
9.README.md	                 Project documentation.
----------------------------------------------------------------------------------------------------------------

4. Working Flow of the Project

  Program Starts
      ↓
initialize() → loads contacts from contacts.csv
      ↓
Display Menu (Create / Search / Edit / Delete / List / Save & Exit)
      ↓
User selects an option
      ↓
Corresponding function executes   (CRUD - Create,Read,Update,Delete operations)
      ↓
Menu repeats until user chooses "Save & Exit"
      ↓
saveContactsToFile() writes data to contacts.csv
      ↓
Program Ends

5. Function-Level Summary

main.c - main() - Initializes the address book, displays menu, and triggers required operations.

contact.c

initialize() - Loads existing contacts and prepares the AddressBook structure.
createContact() - Accepts user input, validates it, and adds a new contact.
searchContact() - Searches contacts by name, phone number, or email.
editContact() - Locates a contact and updates its fields after validation.
deleteContact() - Removes a contact and shifts remaining entries.
listContacts() - Sorts contacts alphabetically and displays them.

file.c

loadContactsFromFile() - Reads all contacts from contacts.csv into memory.
saveContactsToFile() - Writes current contact list to contacts.csv.

validation.c

validation_name() - 1st letter should me capital , only alphabates (small), if space is there after space can use capital otherwise all letters expect 1st should be small
validation_number() - Number length should be 10, only numeric no other characters(special,alpha)
validation_email() - Ensures correct email and domain structure,atleast one char before @,Should contain only small letters no any other special and capital letters,can use numeric,underscore in middle.

6. How to Compile and Run

Compile - gcc *.c
Run - ./a.out
Program Behavior - Loads existing contacts at startup - Operations are menu-driven - Saves updated contacts before exiting.

7. Overall Overview

The project provides a fully functional Address Book system built using modular C programming.
It separates core logic, file operations, and validation into dedicated modules.
Data persistence is handled through a simple CSV format, and contacts can be viewed, modified, or removed through a clear menu-based interface.

8. Learning Outcomes

Designing and implementing structured data using struct in C
Performing file input/output operations
Organizing code using modular programming
Applying input validation techniques
Developing complete CRUD-based applications
Strengthening debugging and C programming skills

>>>>>>>>>>>>>>>>>>>> Smaple Input and Outputs
Address Book Menu:
1. Create contact 🆕
2. Search contact 🔎
3. Edit contact 📝
4. Delete contact 🗑️
5. List all contacts 📑     
6. Save contacts 💾
7.  Exit 🛑

Enter your choice: 1
--------> Creat 🆕 contact <--------
Enter the name : Kumar
Enter the number : 1234567890
Enter the email : uday@gmail.com
Contact added successfully ✔️
Are you really want to exit from Create contact ? (y/n): y
Exiting successfully ➡️  ....

(Flow of working is same for all, here i am just showing name only operation)

*search by name - If single contact is there shows that contact directly , otherwise Shows the multiple contact with that name and ask the user to enter number or email of the    contact they r searching for , beacuse they are unique
*search by number or email - shows single contact because they are unique

Enter your choice: 2
-------->🔎 Search Contact by <--------
1.Name  2.Phone.no  3.Email.id  4.Exit
Enter the choice : 1
Enter the name to search : Kumar
S.No 23 -> Name - Kumar, phone.no - 1234567890, Email - uday@gmail.com
1 Contact Found ✅ ...
Name  = Kumar
Phone = 1234567890
Email = uday@gmail.com
Are you really want to exit from Search ? (y/n): y
Exiting the search ➡️  ...

*Edit by name - If single contact with that name dierctly ask to edit name otherwise ,Shows the multiple contact with that name and ask the user to enter the index of the contact they r Editing for
*Edit by number or email - shows single contact because they are unique

Enter your choice: 3
-------->📝 Edit Contact by <--------
1.Name  2.Phone.no  3.Email.id  4.Exit
Enter the choice : 1
Enter the name to Edit : Kumar
Index 22 -> Name - Kumar, phone.no - 1234567890, Email - uday@gmail.com
1 Contact Found ✅ ...
Enter the new name: Uppu
Changing Name from Kumar -> Uppu.....Name updated successfully ✔️ 
Are you really want to exit from Edit contact ? (y/n): y
Exiting the Edit ➡️  ....


*Delete by name - if single contact directly delete it otherwise Shows the multiple contact with that name and ask the user to enter the number or email of the contact they r deleting for
*Delete by number or email - shows single contact because they are unique

Enter your choice: 4
--------> 🗑️   Delete Contact by <--------
1.Name  2.Phone.no  3.Email.id  4.Exit
Enter the choice : 1
Enter the name to Delete : Uppu
S.No 23 -> Name - Uppu, phone.no - 1234567890, Email - uday@gmail.com
Contact deleted successfully ✔️ 
Are you really want to exit from Delete contact? (y/n): y
Exiting the delete ➡️  ....

Enter your choice: 5 - it will show the list of contacts in table
Enter your choice: 6 - Save the changes in file
Enter your choice: 7 - Exiting the addressbook

                                                                  Thanking you,
                                                              Udaykumar upputuri.

----------------------------------------> THE END <----------------------------------------