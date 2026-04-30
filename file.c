#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE* fptr=fopen("contact.txt","w");
    fprintf(fptr,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fptr,"%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
    // printf("Call1");
    FILE* fptr=fopen("contact.txt","r");
    // printf("call2");
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    // printf("%d",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++){
        // printf("call2");
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    // printf("lastcall");
    fclose(fptr);
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
    variable  and we can access and modify them. 
*/