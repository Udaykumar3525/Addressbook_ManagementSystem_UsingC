# Address Book Application (C Project)

**Name:** Udaykumar Upputuri  
**Email:** udayupputuri3525@gmail.com  

---

## 1. Project Description

This project is an **Address Book Application** written in the C programming language.  
It allows users to **create, search, edit, delete, list, and save contact information**.

Each contact contains:
- Name
- Phone Number
- Email ID

Contacts are stored in memory during runtime and saved to **contacts.csv** for future use.

---

## 2. Purpose and Advantages

- Demonstrates **modular programming** using multiple `.c` and `.h` files  
- Provides practical experience in **file handling and structured data management**  
- Implements **CRUD operations** (Create, Read, Update, Delete)  
- Includes **input validation** for better data consistency  
- Serves as a base project for systems like phonebooks or student databases  

---

## 3. Project File Structure

```text
main.c            → Entry point; handles menu and user interaction
contact.c         → Core functionalities (create, search, edit, delete, list)
contact.h         → Structure definitions and function declarations
file.c            → Reads from and writes to contacts.csv
file.h            → File handling function declarations
validation.c      → Input validation logic
validation.h      → Validation function declarations
contacts.csv      → Stores all contact records
README.md         → Project documentation

4. Working Flow of the Project
Program Starts
      ↓
initialize() → Loads contacts from contacts.csv
      ↓
Display Menu
(Create / Search / Edit / Delete / List / Save & Exit)
      ↓
User selects an option
      ↓
Corresponding operation executes (CRUD)
      ↓
Menu repeats until user chooses Save & Exit
      ↓
saveContactsToFile() writes data to contacts.csv
      ↓
Program Ends

5. Function-Level Summary
main.c

main()
Initializes the address book, displays the menu, and calls required functions.

contact.c

initialize() – Loads existing contacts into memory

createContact() – Takes user input, validates it, and adds a new contact

searchContact() – Searches contacts by name, phone number, or email

editContact() – Updates contact details after validation

deleteContact() – Deletes a contact and shifts remaining records

listContacts() – Sorts contacts alphabetically and displays them

file.c

loadContactsFromFile() – Reads contacts from contacts.csv into memory

saveContactsToFile() – Writes current contact list to contacts.csv

validation.c

validation_name()

First letter must be capital

Only alphabets allowed

After space, capital letter is allowed

validation_number()

Exactly 10 digits

Only numeric characters allowed

validation_email()

At least one character before @

Only lowercase letters

Numbers and underscore allowed

Valid email domain format

6. How to Compile and Run
Compile
gcc *.c

Run
./a.out

Program Behavior

Loads existing contacts at startup

Menu-driven operations

Saves updated contacts before exiting

7. Sample Input and Output
Address Book Menu
1. Create contact 🆕
2. Search contact 🔎
3. Edit contact 📝
4. Delete contact 🗑️
5. List all contacts 📑
6. Save contacts 💾
7. Exit 🛑

Create Contact
Enter your choice: 1
--------> Create Contact <--------
Enter the name : Kumar
Enter the number : 1234567890
Enter the email : uday@gmail.com
Contact added successfully ✔️
Are you really want to exit from Create contact ? (y/n): y
Exiting successfully...

Search Contact

Search by Name

If only one contact exists → displayed directly

If multiple contacts exist → user selects using phone or email

Search by Phone / Email

Always unique → single contact displayed

Enter your choice: 2
--------> Search Contact <--------
Enter the name to search : Kumar
1 Contact Found ✅
Name  = Kumar
Phone = 1234567890
Email = uday@gmail.com

Edit Contact

Edit by Name

Single contact → directly edit

Multiple contacts → select by index

Edit by Phone / Email

Always unique

Enter your choice: 3
--------> Edit Contact <--------
Enter the name to edit : Kumar
Enter the new name : Uppu
Name updated successfully ✔️

Delete Contact

Delete by Name

Single contact → deleted directly

Multiple contacts → select using phone or email

Delete by Phone / Email

Always unique

Enter your choice: 4
--------> Delete Contact <--------
Enter the name to delete : Uppu
Contact deleted successfully ✔️

Other Options
5 → Displays all contacts in table format
6 → Saves contacts to file
7 → Exits the address book application

8. Overall Overview

This project is a fully functional Address Book Management System developed using modular C programming.
It clearly separates contact management, file handling, and validation logic into independent modules.

Data persistence is achieved using a CSV file, making the application simple, efficient, and easy to extend.

9. Learning Outcomes

Designing structured data using struct in C

Performing file input/output operations

Writing modular and maintainable code

Applying input validation techniques

Developing complete CRUD-based applications

Improving debugging and C programming skills