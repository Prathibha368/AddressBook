#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>
#include<string.h>


struct Contact{             //creating a structure with name,mobno,email members
    char name[50];
    char mobno[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[100];
    int contactCount;
    int index_record[100];
    int ir_size;
};
// prototypes of all functions used in the project.
void pull_file_data(struct AddressBook *,char *);
void push_data_to_file(struct AddressBook * ,char *);
void add_contact(struct AddressBook *addressBook);
void search_contact(struct AddressBook *addressBook);
void edit_contact(struct AddressBook *addressBook);
void delete_contact(struct AddressBook *addressBook);
void list_contacts(struct AddressBook *addressBook);
int  mob_verify(char *);
int email_verify(char *);
int search_name(struct AddressBook *addressBook, char *);
void search_mobile(struct AddressBook *addressBook, char *);
void search_email(struct AddressBook *addressBook, char *);
#endif
