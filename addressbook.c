#include "addressbook.h"

void pull_file_data(struct AddressBook * addressBook,char * file_name)
{
    FILE *fp=fopen(file_name,"r");
    int i=0;
    addressBook->contactCount =0;
    fseek(fp,0,SEEK_END);
    if(ftell(fp)!=0){
        rewind(fp);
        while(!feof(fp)){
            fscanf(fp, " %[^,], %[^,], %[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].mobno,addressBook->contacts[i].email);
            i++;
        }
    }
    addressBook->contactCount=i;
    fclose(fp);
}

void push_data_to_file(struct AddressBook * addressBook,char *file_name)
{
    FILE *fp=fopen(file_name,"w");
    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fp,"%s, %s, %s\n",addressBook->contacts[i].name,addressBook->contacts[i].mobno,addressBook->contacts[i].email);
    }
}

void add_contact(struct AddressBook *addressBook)               //adding of contact details like name,mobile no,email.
{
    char name[50];
    char mobno[11];
    char email[30];
    printf("Enter the name: ");
    scanf(" %[^\n]",name);


    L1:
    printf("Enter the mobile number: ");
    scanf(" %s",mobno);
    if(!mob_verify(mobno)){                                     //calling of mobile verification function.
        printf("Invalid mob no please enter valid no ! \n");
        goto L1;
    }


    L2:
    printf("Enter the email:");
    scanf(" %s",email);
    if(!email_verify(email)){                                      //calling of email verification function.
        printf("Invalid email id please enter valid email ! \n");
        goto L2;
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);             //adding name,mobilenumber,email and increasing contact count.
    strcpy(addressBook->contacts[addressBook->contactCount].mobno,mobno);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount++;
    push_data_to_file(addressBook,"database.csv");                                  // pushing the entered data to the database file by calling oush_data_to_file function.
}
void search_contact(struct AddressBook *addressBook)
{
    L3:
    printf("\nSearch Contact Book Menu:\n");                                    //searching of contact by presenting 3 options.
	printf("1. Search contact by name:\n");
	printf("2. Search contact by mobile number: \n");
	printf("3. Search contact by email:\n");
	printf("4. Exit \n");
    int option;
    scanf("%d",&option);
    
    switch(option)
    {
        case 1:
            char name[50];
            printf("enter name: ");
            scanf("%s",name);
            search_name(addressBook ,name);
            goto L3;
            break;
        case 2:
            char mobno[11];
            printf("Enter mobno:");
            scanf("  %s",mobno);
            if(mob_verify(mobno)){
                search_mobile(addressBook,mobno);
                goto L3;
            }
            else{
                printf("invalid mobile number");
            }
            break;
        case 3:
            char email[50];
            printf("enter email:");
            scanf("  %s",email);
            if(email_verify(email)){
                search_email(addressBook,email);
                goto L3;
            }
            else{
                printf("invalid email id!");
            }  
            break;
    }

    /* if( addressBook->ir_size == 0 )
	printf("Contact not found\n");
    else
    {
	// Print the searched contacts
    } */

}
void edit_contact(struct AddressBook *addressBook)              //function for editing the contact.
{
    search_contact(addressBook);                                //for editing ,first searching of contact is needed.
    if(addressBook->ir_size==0){
        return;
    }
    int i=1;
    if(addressBook->ir_size>1){
        printf("Enter the index of contact that you want to edit: ");           //editing the contact by name or mobile number or email.
        scanf("%d",&i);
    }
    
    L:
    printf("Name: %s, ",addressBook->contacts[addressBook->index_record[i-1]].name);
    printf("Mobile no: %s, ",addressBook->contacts[addressBook->index_record[i-1]].mobno);
    printf("Email: %s\n",addressBook->contacts[addressBook->index_record[i-1]].email);
    printf("1. Edit name\n2. Edit phone\n3. Edit email\n4. Exit\n");
    int c;
    scanf("%d",&c);
    switch(c){
        case 1:
        {
            char new_name[20];                              //editng contact name
            N:
            printf("Enter the name : ");
            scanf("%s",new_name);
            if(!(strcmp(addressBook->contacts[addressBook->index_record[i-1]].name,new_name))){
                printf("Name is same as previous one!\n");
                goto N;
            }
            strcpy(addressBook->contacts[addressBook->index_record[i-1]].name,new_name);
            goto L;
            break;
        }
       case 2:
       {
            char new_phone[20];                     //editing the mobile number
            l:
            printf("Enter the phone : ");
            scanf("%s",new_phone);
            if(!(mob_verify(new_phone))){
             printf("Invalid Number!\n");
             goto l;
            }
            if(!(strcmp(addressBook->contacts[addressBook->index_record[i-1]].mobno,new_phone))){
                printf("Phone is same as previous one!\n");
                goto l;
            }
            strcpy(addressBook->contacts[addressBook->index_record[i-1]].mobno,new_phone);
            goto L;
            break;
       }
       case 3:
       {
            char new_email[20];                             //new email id of a contact
            lm:
            printf("Enter the email : ");
            scanf("%s",new_email);
            if(!(email_verify(new_email))){
             printf("Invalid Email!!\n");
             goto L;
            }
            if(!(strcmp(addressBook->contacts[addressBook->index_record[i-1]].email,new_email))){   //comparing the new email is existed already within addressbook or not!
                printf("Email is same as previous one!\n");
                goto L;
            }
            strcpy(addressBook->contacts[addressBook->index_record[i-1]].email,new_email);
            goto L;
            break;
       }
       case 4:
       {
        return;
        break;
       }
       default:
       {
        printf("Invalid Option\n");
        break;
       }


    }
}
void delete_contact(struct AddressBook *addressBook)
{
    search_contact(addressBook);                        //if ir_size i.e no contact are present in book it will return.
    if(addressBook->ir_size==0){
        return;
    }
    int i=1;
    if(addressBook->ir_size>1){                         // if ir-szie>1 then index of contact is taken from user.
        printf("Enter the index of contact that you want to delete: ");
        scanf("%d",&i);
    }
    char ch;
    printf("Do you want to delete this contact y/n: ");         // making sure he/she wantedd to delete
    scanf(" %c",&ch);
    if(ch=='y'){
        for(int j=addressBook->index_record[i-1];j<addressBook->contactCount-1;j++){            //if yes from addressbook contact will be deletd and then contacts in down move up index
            addressBook->contacts[j]=addressBook->contacts[j+1];
        }
        addressBook->contactCount--; 
    }
    else{
        return;
    }
    printf("Your Contact is successfully deleted\n");
}
void list_contacts(struct AddressBook *addressBook)     //list of contacts
{
    if(addressBook->contactCount==0){          
        printf("no data found");
        return;
    }

    FILE *fp = fopen("database.csv", "r");
    if (fp == NULL) {
        printf("Unable to open ");
        return;
    }
    else
    {
        for(int i=0;i<addressBook->contactCount;i++){           //loop runs till the contact count ,prints the name,email,mobno of each contact
            printf("Name   : %s\n", addressBook->contacts[i].name);
            printf("Mobno   : %s\n", addressBook->contacts[i].mobno);
            printf("email  : %s\n", addressBook->contacts[i].email);
        }
    }
    fclose(fp);
}

int mob_verify(char * mobno)
{
    if ((strlen(mobno)==10) && mobno[0]>'5' && mobno[0]<='9')       //mobno should be length of 10 and also first digit should be between 5 to 10
    {
        int i=1;
        while(mobno){
            if(mobno[i]>='0' && mobno[i]<='9'){                 //all the char should be digits
                i++;
            }
            return 1;
        }  
    }
    else
    {
        return 0;
    }
}

int email_verify(char *email)
{
    int len = strlen(email);

    if (email[0] == '@' || email[0] == ' ' || email[0] == '\t')         //the email should not start with @ or space,tab, if so return 0;error message
        return 0;

    if (len < 11)
        return 0;

    if (strcmp(email + len - 10, "@gmail.com") == 0)            //comparing the last 10 are @gmail.com or not.
        return 1;

    return 0;
}

int search_name(struct AddressBook * addressBook , char *name)
{
   for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(name,addressBook->contacts[i].name)==0){          //comparing the given name and name in adressbook.
            addressBook->index_record[addressBook->ir_size]=i;
            addressBook->ir_size++;
        }
    }

    if( addressBook->ir_size == 0 )
	    printf("Contact not found\n");
    else{
        for(int k=0;k<addressBook->ir_size;k++){                                    //printing whole details from the contact address book with given name.
            printf("name: %s,",addressBook->contacts[addressBook->index_record[k]].name);
            printf("mobno: %s,",addressBook->contacts[addressBook->index_record[k]].mobno);
            printf("email: %s\n",addressBook->contacts[addressBook->index_record[k]].email);
        }
    }
}
void search_mobile(struct AddressBook * addressBook,char *mobno)
{
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(mobno, addressBook->contacts[i].mobno)==0){   //comparing the given mobilenumber and mobilenumber in adressbook.

            printf("name: %s\n", addressBook->contacts[i].name);
            printf("name: %s\n", addressBook->contacts[i].mobno);
            printf("name: %s\n", addressBook->contacts[i].email);
            return;
        }
    }
    printf("Contact not found\n");

}

void search_email(struct AddressBook * addressBook,char *email)
{
    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(email, addressBook->contacts[i].email)==0){   //comparing the given email id and email id  in adressbook and prints whole data of that email id .

            printf("name: %s\n", addressBook->contacts[i].name);
            printf("name: %s\n", addressBook->contacts[i].mobno);
            printf("name: %s\n", addressBook->contacts[i].email);
            return;
        }
    }
    printf("Contact not found\n");
}

