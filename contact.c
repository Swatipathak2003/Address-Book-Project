#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"
int arr[100]={0};
int idx=0;
int validateUserName(char*);
int validatePhoneNumber(char*);
int uniquephone(char*,AddressBook*);
int validateEmailId(char*);
int uniqueEmail(char*,AddressBook*);
void searchByName(AddressBook*);
void searchByPhone(AddressBook*);
void searchByEmail(AddressBook*);
void updateName(AddressBook*,int);
void updatePhone(AddressBook*,int);
void updateEmail(AddressBook*,int);


void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("+------------+----------------------+-----------------+--------------------------------+\n");
    printf("| %-10s | %-20s | %-15s | %-30s |\n","Serial","Name","Phone","Email");
    printf("+------------+----------------------+-----------------+--------------------------------+\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("| %-10d | %-20s | %-15s | %-30s |\n",i+1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
            printf("+------------+----------------------+-----------------+--------------------------------+\n");
    }    
    // printf("------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{   
	/* Define the logic to create a Contacts */

    //check if contact count is less than 100 that is memory not full.
    if(addressBook->contactCount==100){
        printf("Memory Full!\n");
        return;
    }

    //1. Read User Name
    int limit1=3;//setting limit
    char Name[50];//creating temp variable
    printf("You have %d attempts!\n",limit1);
    while(limit1){//checking for attemps left or not
        printf("Enter the Name of user: ");
        scanf(" %[^\n]",Name);
        if(validateUserName(Name)){//checking for validation
            break;
        }
        else{//if not valid decrease the limit
            limit1--;
            printf("Attempts left: %d\n",limit1);
        }
    }
    if(limit1==0){//if no attempt left print message
        printf("You have finished your attempt!\n");
        return;
    }
    
    //2. Read Phone Number
    int limit2=3;
    char phone[20];
    printf("You have %d attempts!\n",limit2);
    while(limit2){
        // printf("You have %d attempts available!\n",limit2);
        printf("Enter Phone Number: ");
        scanf(" %[^\n]",phone);
        if(validatePhoneNumber(phone)){//check for validation
            if(uniquephone(phone,addressBook)){//checking for uniqueness
                break;
            }
            else{
               limit2--;//if not unique reduce the limit 
               printf("Attempts left: %d\n",limit2);
            }
        }
        else{
            limit2--;//if not valid decrement the limit
            printf("Attempts left: %d\n",limit2);
        }
    }
    if(limit2==0){
        //if no attempt left print message
        printf("You have finished your attempt!\n");
        return;
    }

    //3. Read Email Id:

    int limit3=3;
    char Email[50];
    printf("You have %d attempts!\n",limit3);
    while(limit3){
        // printf("You have %d attempts available!\n",limit3);
        printf("Enter Emial Id: ");
        scanf(" %[^\n]",Email);
        if(validateEmailId(Email)){
            if(uniqueEmail(Email,addressBook)){
                break;
            }
            else{
                limit3--;//if not unique decrement the limit
                printf("Attempts left: %d\n",limit3);
            }
        }
        else{
            limit3--;//if not valid decrement the limit
            printf("Attempts left: %d\n",limit3);
        }
    }
    if(limit3==0){
        //if no attempt left print message
        printf("You have finished your attempt!\n");
        return;
    }
    //4. if all data is valid store in contact list
    strcpy(addressBook->contacts[addressBook->contactCount].name,Name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,Email);
    addressBook->contactCount++;   
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int sel;
    printf("Search Method: \n");
    printf("1.Search By Name.\n");
    printf("2.Search by Phone.\n");
    printf("3.Search by Email ID.\n");
    printf("Select the search method: ");
    if(scanf("%d",&sel)!=1){//asking user for selecting the method of search
        printf("Invalid input!\n");
        //if anything other than integer is entered store it in buffer in order to overcome infinite loop 
        char buffer[100];
        gets(buffer);
        return;
    }

    //Search by Name:
    if(sel==1){
        searchByName(addressBook);
    }
    //search by phone number:
    else if(sel==2){
        searchByPhone(addressBook);
    }
    //search by Email:
    else if(sel==3){
        searchByEmail(addressBook);
    }
    else{
        printf("Undefined Input!");
        return;
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    //step1. call search function;
    searchContact(addressBook);
    if(idx==0){
        return;
    }
    //step2. read serial number user want to edit
    int s=0;
    int l=3;
    printf("You have %d attempts\n",l);
    printf("Enter the serial number you want to Update\n");
    printf("Note: serial number can be in range 1 to %d\n",idx);
    while(l){//check for attempts left or not
        printf("Enter the serial number: ");
        scanf("%d",&s);
        if(s<=0||s>idx){//if serial number is not within given range decrement count and reask the user
            printf("Pls Enter correct serial number!\n");
            l--;
            printf("Attempts left: %d\n",l);
        }
        else{
            break;
        }
    }
    if(l==0){
        printf("Incorrect Serial Number!\n");
        return;
    }
    //step 3. select the data user want to update
    int sel;
    printf("Select Data To Update:\n");
    printf("1.Edit name.\n");
    printf("2.Edit Phone Number.\n");
    printf("3.Edit Email ID.\n");
    printf("4.Exit.\n");
    printf("Select the data you want to update: ");
    // scanf("%d",&sel);
    if(scanf("%d",&sel)!=1){
        printf("Invalid input!\n");
          //if anything other than integer is entered store it in buffer in order to overcome infinite loop 
        char buffer[100];
        gets(buffer);
        return;
    }
    //step4. validate and update the data.
    switch(sel){
        case 1:
            updateName(addressBook,s);//call update name function
            break;
        case 2:
            updatePhone(addressBook,s);//call updatephone function
            break;
        case 3:
            updateEmail(addressBook,s);//call updateemail function
            break;
        case 4:
            printf("Exiting Edit Contact!\n");//exiting if user dont want to edit anymore
            break;
        default:
            printf("Invalid Edit Field!\n");//if invalid edit field is entered
            break;
    }
    return;
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    //1.search the contact to delete
    searchContact(addressBook);
    if(idx==0){
        return;
    }
    //2. select which contact to delete from list of serached contacts
    int s;
    int limit=3;
    printf("You have %d attempts\n",limit);
    while(limit){
        printf("Enter the serial no. of the contact you want to delete: ");
        scanf("%d",&s);
        if(s<=0 || s>idx){//check if user has entered serial number within given range
            printf("Pls Enter correct serial number.\n");
            limit--;
            printf("Attempts left: %d\n",limit);
        }
        else{
            break;
        }
    }
    if(limit==0){
        printf("Invalid access to contact!\n");
        return;

    }
    //3.delete contact 
    for(int i=arr[s-1];i<addressBook->contactCount-1;i++){
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    //4.updating contact count by decrementing by 1;
    addressBook->contactCount--;
    printf("Contact was Successfully Deleted!\n");
}

//validation Function: 

int validateUserName(char* name){
    int len=strlen(name);
    //1. check if all char are alphabets
    while(*name){
        if((*name>=65 && *name<=90) || (*name>=97&&*name<=122) || *name==' '){
            name++;
        }
        else{
            printf("Enter valid User Name!\n");
            return 0;
        }
    }
    return 1;
}

int validatePhoneNumber(char* phone){
    //1. check the len is 10
    int len=strlen(phone);
    if(len>10){
        printf("Pls Enter 10 digit number!\n");
        return 0;
    }
    //2. check all char are numeric
    int i=0;
    while(phone[i]){
        if(phone[i]<48 || phone[i]>57){
            printf("Phone Number can only be in digits!\n");
            return 0;
        }
        i++;
    }
    //3.number starts with 6,7,8,9 only as most indian number starts with this
    if(*phone!='6' && *phone!='7' && *phone!='8' && *phone!='9'){
        printf("Number is invalid!\n");
        return 0;
    }
    return 1;
}

int uniquephone(char* phone,AddressBook* addressBook){
    //4. checking if phone number already exist.
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(phone,addressBook->contacts[i].phone)==0){
            printf("Phone Number Already Exist!\n");
            return 0;
        }
    }
    return 1;
}

int validateEmailId(char* email){
    int len=strlen(email);
    //1.checking if all the character is lower case or not
    for(int i=0;i<len;i++){
        if(email[i]>=65 && email[i]<=90){
            printf("Pls Enter only Lower Case character!\n");
            return 0;
        }
    }
    //2.checking if email contains multiple @ character
    int count=0;
    for(int i=0;i<len;i++){
        if(email[i]=='@'){
            count++;
        }
        if(count>1){
            printf("Pls Enter Valid Email Id with only one @!\n");
            return 0;
        }
    }
    if(count==0){
        printf("Pls Enter Valid Email Id with @!\n");
        return 0;
    }
    //3.checking if the first char of mail is digit
    if(*email>=48 && *email<=57){
        printf("Email Id Can't start with digit!\n");
        return 0;
    }
    char* ptr=strchr(email,'@');
    //4.checking if the domain id(.com) is there at the end or multiple of them eg. swati@gmail or swati@gmail.com.com or swati@gmail..com
    char* domainId=strchr(ptr,'.');
    if(domainId==NULL || strlen(domainId)!=4){
        printf("Pls Enter valid Domain Id!\n");
        return 0;
    }
    char* dotcom=strstr(ptr,".com");//checking for .com int the domain name
    if(dotcom==NULL){
        printf("Enter valid domain Id with .com!\n");
        return 0;
    }
    //5.checking if the length of the domain name between @ and . is of minimum 5 char eg. gmail and also it only alpabhetic characters eg.swati@123323.com is not valid
    ptr++;//ptr point to the start of domain name which is next char after @
    count=0;
    while(*ptr!='.'){
        if(*ptr<97 || *ptr>122){
            printf("Domain name should only contain alphabets!\n");
            return 0;
        }
        count++;
        ptr++;
    }
    if(count<5){
        printf("Enter valid Domain Name!\n");
        return 0;
    }
 
    return 1;
}
int uniqueEmail(char* email,AddressBook* addressBook){
    //6.checking if email id already exits
        for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(email,addressBook->contacts[i].email)==0){
            printf("Email Id already Exist!\n");
            return 0;
        }
    }
    return 1;
}

//searching function:

void searchByName(AddressBook* addressBook){
    char name[50];
    int limit1=3;
    printf("You have %d attempts!\n",limit1);
    while(limit1){
        printf("Enter the name to search contact: ");
        scanf(" %[^\n]", name);
        if(validateUserName(name)){//check if the name user wants to search is valid or not
            int found=0;//flag to check if contact is found or not
            idx=0;
            for(int i=0;i<addressBook->contactCount;i++){
                if(strcmp(name,addressBook->contacts[i].name)==0){//if contact found print it
                    if(idx==0){//to print header once if contact is found as there can be multiple same name
                        printf("+------------+----------------------+-----------------+--------------------------------+\n");
                        printf("| %-10s | %-20s | %-15s | %-30s |\n","Serial","Name","Phone","Email");
                        printf("+------------+----------------------+-----------------+--------------------------------+\n");   
                    }
                    printf("| %-10d | %-20s | %-15s | %-30s |\n",idx+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    printf("+------------+----------------------+-----------------+--------------------------------+\n");                        
                    found=1;//if contact is found turn flag 1;
                    arr[idx]=i;
                    idx++;
                }
            }
            if(!found){//if contact is not found
                printf("Contact Not Found!\n");
            }
            return;
        }
        else{
            printf("Pls Enter valid user name!");
            limit1--;
            printf("Attempts left: %d\n",limit1);
        }
    }
    printf("You have finished your attempt!\n");
    return;
}

void searchByPhone(AddressBook* addressBook){
        char phone[20];
        int limit2=3;
        printf("You have %d attempts!\n",limit2);
        while(limit2){
            printf("Enter the phone number to search contact: ");
            scanf(" %[^\n]",phone);
            if(validatePhoneNumber(phone)){//check if phone number user want to search is valid or not
                idx=0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if(strcmp(phone,addressBook->contacts[i].phone)==0){
                        printf("+------------+----------------------+-----------------+--------------------------------+\n");
                        printf("| %-10s | %-20s | %-15s | %-30s |\n","Serial","Name","Phone","Email");
                        printf("+------------+----------------------+-----------------+--------------------------------+\n");
                        printf("| %-10d | %-20s | %-15s | %-30s |\n",idx+1,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        printf("+------------+----------------------+-----------------+--------------------------------+\n"); 
                        arr[idx]=i;//storing the idx of contact if the contact is found
                        idx++;
                        return;
                        
                    }
                }
                printf("Contact Not Found!\n");
                return;
            }
            else{
                limit2--;
                printf("Attempts left: %d\n",limit2);
            }
        }
        printf("You have finished your attempt!\n");
        return;
}

void searchByEmail(AddressBook* addressBook){
        char Email[50];
        int limit3=3;
        printf("You have %d attempts available!\n",limit3);
        while(limit3){
            printf("Enter the Email Id to search contact: ");
            scanf(" %[^\n]",Email);
            if(validateEmailId(Email)){//check if the email id user wants to search is valid or not
                idx=0;
                for(int i=0;i<addressBook->contactCount;i++){
                    if(strcmp(Email,addressBook->contacts[i].email)==0){
                        printf("+------------+----------------------+-----------------+--------------------------------+\n");
                        printf("| %-10s | %-20s | %-15s | %-30s |\n","Serial","Name","Phone","Email");
                        printf("+------------+----------------------+-----------------+--------------------------------+\n");
                        printf("| %-10d | %-20s | %-15s | %-30s |\n",idx+1,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        printf("+------------+----------------------+-----------------+--------------------------------+\n"); 
                        arr[idx]=i;//storing the idx of contact if the contact is found
                        idx++;
                        return;
                    }
                }
                printf("Contact Not Found!\n");
                return;
            }
            else{
                limit3--;
                printf("Attempts available: %d\n",limit3);
            }
        }
        printf("You have finished your attempt!\n");
        return;
}

//Update function: 
void updateName(AddressBook* addressBook,int s){
        //Read User Name
    int limit1=3;
    char Name[50];
    printf("You have %d attempts!\n",limit1);
    while(limit1){
        printf("Enter the Name of user: ");
        scanf(" %[^\n]",Name);
        if(validateUserName(Name)){
            strcpy(addressBook->contacts[arr[s-1]].name,Name);
            printf("Name is Successfully Updated.\n");
            return;
        }
        else{
            limit1--;
            printf("Attempts available: %d\n",limit1);
        }
    }
    printf("Your attempt is finished!\n");
    return;
}

void updatePhone(AddressBook* addressBook,int s){
    int limit2=3;
    char phone[20];
    printf("You have %d attempts!\n",limit2);
    while(limit2){
        printf("Enter Phone Number: ");
        scanf(" %[^\n]",phone);
        if(validatePhoneNumber(phone)){
            if(uniquephone(phone,addressBook)){
                strcpy(addressBook->contacts[arr[s-1]].phone,phone);
                printf("Phone Number is Successfully Updated.\n");
                return;
            }
            else{
               limit2--;
               printf("Attempts available: %d\n",limit2);
            }
        }
        else{
            limit2--;
            printf("Attempts available: %d\n",limit2);
        }
    }
    printf("your attempt is finished!\n");
    return;   
}

void updateEmail(AddressBook* addressBook,int s){
    // Read Email Id:
    int limit3=3;
    char Email[50];
    printf("You have %d attempts!\n",limit3);
    while(limit3){
        printf("Enter Emial Id: ");
        scanf(" %[^\n]",Email);
        if(validateEmailId(Email)){//check if the email entered by user is valid or not
            if(uniqueEmail(Email,addressBook)){//check if the email entered by user is unique or not
                strcpy(addressBook->contacts[arr[s-1]].email,Email);//arr will have the idx of contact searched
                printf("Email ID is Successfully Updated.\n");
                return;
            }
            else{
                limit3--;
                //if not valid or unque decrement attempts
                printf("Attempts available: %d\n",limit3);
            }
        }
        else{
            limit3--;
            //if not valid or unque decrement attempts
            printf("Attempts available: %d\n",limit3);
        }
    }
    printf("You have finished your attempt!\n");
    return;
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
