/*PROJECT NAME: ADDRESSBOOK 
DATE:28/12/25
DESCRIPTION: Creation of addressbook model using C program includes Addition,deletion,searching,edit,and list of the contacts. */
#include "addressbook.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
	pull_file_data(&addressBook,"database.csv");
    addressBook.ir_size = 0;

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Add/Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");

	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		add_contact(&addressBook);
		break;
	    case 2:
		search_contact(&addressBook);
		break;
	    case 3:
		edit_contact(&addressBook);
		break;
	    case 4:
		delete_contact(&addressBook);
		break;
	    case 5:
		list_contacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
		push_data_to_file(&addressBook,"database.csv");
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}

