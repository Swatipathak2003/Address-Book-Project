#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        // printf("7. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice)==0){
            char buffer[100];
            scanf("%s",buffer);
        }
        
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
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
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}

//Author: swati Pathak
//Project: Address Book
/* Address Book is a project in which we are trying to implement the contact list system available in our phone. 
    we have created a structure datatype of contact which contains data like user name,phone number & email Id.
    in order to access this data inside one variable like in phone all contact is in contact app,just the same
    way all the contact is stored in addressbook variable which contains array of contact structure to store
    100 contacts.using the function such as create contact,edit contact,search contact,delete contact,list
    contact and save and exit we have given user the access to contact stored we are storing all the contact
    data in file so that if we run the program again we can have access to previous stored contact.so when we
    run the program all the contact available in file is initialized into the contact array first.here we 
    understood about how a structure data type can store multiple data of different datatypes inside one 
    variable  and we can access and modify them
*/