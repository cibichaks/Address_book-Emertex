/*
       Name : 
       Date : 16-aug-2024 : time 23:20 
Description : contact.c file of AddressBook project the main working functions are declared here
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
#define DUPE_SIZE 20
static void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


void listContacts(AddressBook *addressBook) 
{
    
    printf("  %-20s %-15s %-30s\n", "Name", "PhoneNo", "Email");
    printf("------------------------------------------\n");

    for(int i = 0; i < addressBook->contactCount; i++){
        printf("%-2d | %-18s %-13s %-28s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }	
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
	printf("Enter your name :");
	fflush(stdout);
	fgets(addressBook->contacts[addressBook->contactCount].name,30,stdin);
	trim_newline(addressBook->contacts[addressBook->contactCount].name);
	printf("Enter your 10 digit mobile number : ");
	while(1){				
		int flag=0;
		fgets(addressBook -> contacts[addressBook -> contactCount].phone,20,stdin);
		trim_newline(addressBook -> contacts[addressBook -> contactCount].phone);
		int len = strlen(addressBook -> contacts[addressBook -> contactCount].phone);
		if( len < 10 || len > 10 ){
			printf("Entered the number is less then 10 or greater than 10 digits Enter the valid number : ");
			continue;//validation for 10 digit
		}
		for(int i=0 ; addressBook -> contacts[addressBook -> contactCount].phone[i] != '\0' ; i++){
			if(isdigit(addressBook -> contacts[addressBook -> contactCount].phone[i]) == 0){
			printf("Phone num contain non-digit charecter, Enter a valid number:");
			flag=1;
			break;
			}

		}
		if (flag == 1){
			continue;
		}
		for(int i=0;i<addressBook->contactCount;i++){
			if(strcmp(addressBook -> contacts[addressBook -> contactCount].phone,addressBook -> contacts[i].phone) == 0){
				printf("you entered already exixting contact number re enter :");
				flag=2;
				break;
		}
		}
		if(flag==2){
			continue;
		}
		break;
	}
	// Email getting and validation
	printf("Enter the valid Email : ");
	while(1){
		int flag=0;
		fgets(addressBook -> contacts[addressBook -> contactCount].email,50,stdin);
		trim_newline(addressBook -> contacts[addressBook -> contactCount].email);
		if(strchr(addressBook -> contacts[addressBook -> contactCount].email,'@') == NULL){
			printf("your Email donsn't have @ charecter enter again:");
			continue;
		}	
		if (strstr(addressBook -> contacts[addressBook -> contactCount].email, ".com") == NULL) {
            		printf("Your Email doesn't contain .com. Enter again: ");
            		continue;
       		}
		for(int i=0;i<addressBook->contactCount;i++){
			if(strcmp(addressBook -> contacts[addressBook -> contactCount].email,addressBook -> contacts[i].email) == 0){
				printf("you entered mail already exixting contact mail re Enter :");
				flag=2;
				break;
		}
		} 
		if(flag==2){
			continue;
		}
		
		break;
	}
	addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    // Define the logic for search /
	printf("1. Search by name\n");
	printf("2. Search by Email\n");
        printf("3. Search by PhoneNo\n");
        printf("Enter your choice: ");

	int choice;
	char Sname[30];
	scanf("%d",&choice);
	getchar();
	if(choice == 1){
			char Sname[30];
			printf("Enter your name :");
			fflush(stdout);
			fgets(Sname,sizeof(Sname),stdin);
			trim_newline(Sname);
			int flag =0;
			for(int i=0;i<addressBook -> contactCount;i++){
				
				if(strcmp(Sname,addressBook->contacts[i].name) == 0){
					printf("your contact was found! here is the information\n\n");
					printf("Name = %s ------- Phone number = %s ------- Emailid = %s", Sname,addressBook->contacts[i].phone,addressBook->contacts[i].email);
					flag=1;
				}
			}
			if(flag==0){
				printf("contact was not found");
			}
	}			
		else if(choice == 2){
			int  flag;
			char Smail[30];
			printf("Enter your Email  :");
			fflush(stdout);
			fgets(Smail,sizeof(Smail),stdin);
			trim_newline(Smail);
			for(int i=0;i<addressBook -> contactCount;i++){
				if(strcmp(Smail,addressBook->contacts[i].email) == 0){
					flag=1;
					printf("your contact was found! here is the information\n\n");
					printf("Name = %s -------- Phone number = %s -------- Emailid = %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(flag==0){
				printf("contact was not found");
			}

		}
		else if (choice == 3) {
			int flag;
			char Snum[30];
			printf("Enter your Phone number  :");
			fflush(stdout);
			fgets(Snum,sizeof(Snum),stdin);
			trim_newline(Snum);
			for(int i=0;i<addressBook -> contactCount;i++){
				if(strcmp(Snum,addressBook->contacts[i].phone) == 0){
					flag=1;
					printf("your contact was found! here is the information\n\n");
					printf("Name = %s -------- Phone number = %s -------- Emailid = %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(flag==0){
				printf("contact was not found");
			}

		}
		else{
			printf("Entered wrong choice");
			return;
	}
}

static char *duplicate_name(char* Dname,AddressBook *addressBook){
	AddressBook dupe_list[DUPE_SIZE];
	dupe_list->contactCount=0;
	int index=0;
	for(int i=0;i<addressBook->contactCount;i++){
		if(strcmp(Dname,addressBook->contacts[i].name)==0){
			strcpy(dupe_list->contacts[dupe_list->contactCount].name,addressBook->contacts[i].name);
            strcpy(dupe_list->contacts[dupe_list->contactCount].phone,addressBook->contacts[i].phone);
	                strcpy(dupe_list->contacts[dupe_list->contactCount].email,addressBook->contacts[i].email);
			printf("index -> %d) %s %s %s \n",index++,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
			dupe_list->contactCount++;
		}
	}
	printf("you have a duplicate contact name so enter the index position :");
	scanf("%d",&index);
	getchar();
	for(int i=0;i<addressBook->contactCount;i++){
		if (strcmp(dupe_list->contacts[index].phone,addressBook->contacts[i].phone)==0){
			char * unique = (addressBook->contacts[i].phone);
			return unique;
		}
	}
}
void editContact(AddressBook *addressBook)
{
	printf("1. Edit a name\n");
	printf("2. Edit a phone\n");
        printf("3. Edit a email\n");
        printf("Enter your choice: ");
	int choice ;
	scanf("%d",&choice);
	getchar();
	if(choice == 1){
			printf("Enter the name of the contact that u want to edit : ");
			char Ename[20];
			fflush(stdout);
			fgets(Ename,sizeof(Ename),stdin);
			trim_newline(Ename);
			int i,count=0;
			for(int j=0;j<addressBook -> contactCount;j++){
				if(strcmp(Ename,addressBook->contacts[j].name) == 0){
					count++;
					i=j;
				        if (count>1){
						break;
					}
				}
	}
			if(count==1){
				printf("Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				printf("your contact was found! Enter the new name : ");
				char Nname[30];
				fflush(stdout);
				fgets(Nname,sizeof(Nname),stdin);
				trim_newline(Nname);
				strcpy(addressBook->contacts[i].name,Nname);
				printf("Here is your Edited Information\n");
				printf("Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			if (count >1){
				char *unique=duplicate_name(Ename,addressBook);
				for(int i=0;i<addressBook->contactCount;i++){
					if(strcmp(unique,addressBook->contacts[i].phone)==0){
						printf("Enter  the new name :");
						char Nname[30];
						fflush(stdout);
						fgets(Nname,sizeof(Nname),stdin);
						trim_newline(Nname);
						strcpy(addressBook->contacts[i].name,Nname);
						printf("Here is your Edited Information\n");
						printf("Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						break;
					}
				}

						
	}
	}
	else if(choice == 2){
			printf("Enter the number of the contact that u want to edit : ");
			char Enumb[20];
			fflush(stdout);
			fgets(Enumb,sizeof(Enumb),stdin);
			trim_newline(Enumb);
			int flag=0;
			for(int i=0;i<addressBook -> contactCount;i++){
				if(strcmp(Enumb,addressBook->contacts[i].phone) == 0){
					printf("Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

					printf("your contact was found! Enter the new number : ");
					char Nnumb[30];
					while(1){				
						int flag=0;
						fgets(Nnumb,sizeof(Nnumb),stdin);
						trim_newline(Nnumb);
						int len = strlen(Nnumb);
						if( len < 10 || len > 10 ){
							printf("Entered the number is less then 10 or greater than 10 digits Enter the valid number : ");
							continue;//validation for 10 digit
						}
						for(int i=0 ; Nnumb[i] != '\0' ; i++){
						if(isdigit(Nnumb[i]) == 0){
							printf("Phone num contain non-digit charecter, Enter a valid number:");
							flag=1;
							break;
						}
						}
						if (flag == 1){
							continue;
						}	
						break;
					}		
					strcpy(addressBook->contacts[i].phone,Nnumb);
					printf("Here is your Edited Information\n");
					printf("Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
					flag=1;	
					break;
				}
			}
			if(flag==0){
				printf("your contact not in the list\n");

			
			}
	}

else if(choice == 3){
    printf("Enter the email of the contact that you want to edit: ");
    char Eemail[20];
    fflush(stdout);
    fgets(Eemail, sizeof(Eemail), stdin);
    trim_newline(Eemail); 
    fflush(stdout);

    int found = 0;  
    for(int i = 0; i < addressBook->contactCount; i++){
        if(strcmp(Eemail, addressBook->contacts[i].email) == 0){
            printf("Name = %s------Phone number = %s------Emailid = %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("Your contact was found! Enter the new email: ");
            char Nemail[30];
            while(1){
                fflush(stdout);
                fgets(Nemail, sizeof(Nemail), stdin);
                trim_newline(Nemail); 

                if(strchr(Nemail, '@') == NULL){
                    printf("Your Email doesn't have @ character. Enter again: ");
                    continue;
                }    
                if(strstr(Nemail, ".com") == NULL) {
                    printf("Your Email doesn't contain .com. Enter again: ");
                    continue;
                }

                break;
            }
            strcpy(addressBook->contacts[i].email, Nemail);
            printf("Here is your Edited Information\n");
            printf("Name = %s------Phone number = %s------Emailid = %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);            
            found = 1; 
            break;
        }
    }
    
    if (!found) {
        printf("No contact found with the given email.\n");
    }
}


	else{
			printf("Invalid choice was Entered");
	}
}

void deleteContact(AddressBook *addressBook)
{

	/* Define the logic for deletecontact */
	printf("1 for delete a contact by name\n");
	printf("2 for delete a contact by phone number\n");
        printf("3 for delete a contact by email\n");
        printf("Enter your choice: ");
	int choice ;
	fflush(stdout);
	scanf("%d",&choice);
	getchar();
		
if(choice == 1){
    printf("Enter the name of the contact that you want to delete: ");
    char Ename[20];
    fflush(stdout);
    fgets(Ename, sizeof(Ename), stdin);
    trim_newline(Ename);
    
    int count = 0;
    int i;

    for(i = 0; i < addressBook->contactCount; i++){
        if(strcmp(Ename, addressBook->contacts[i].name) == 0){
            count++;
        }
    }

    if(count == 1){
        for(i = 0; i < addressBook->contactCount; i++){
            if(strcmp(Ename, addressBook->contacts[i].name) == 0){
                printf("Deleted contact info ----> Name = %s------Phone number = %s------Emailid = %s\n", 
                    addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                
                for(int j = i; j < addressBook->contactCount - 1; j++){
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--; 
                break;
            }
        }
    }
    else if(count > 1){
        char *unique = duplicate_name(Ename, addressBook); 
        
        for(i = 0; i < addressBook->contactCount; i++){
            if(strcmp(unique, addressBook->contacts[i].phone) == 0){
                printf("Deleted contact info ----> Name = %s------Phone number = %s------Emailid = %s\n", 
                    addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                
                for(int j = i; j < addressBook->contactCount - 1; j++){
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;  // Reduce the count after deletion
                break;
            }
        }
    }

    // If no contact is found
    if(count == 0){
        printf("Entered name was not found.\n");
    }
}

		else if (choice == 2){
			printf("Enter the phone number of the contact that u want to delete : ");
			char Ephone[20];
			int flag2=1;
			fflush(stdout);
			fgets(Ephone,sizeof(Ephone),stdin);
			trim_newline(Ephone);
			for(int i=0;i<addressBook -> contactCount;i++){
				if(strcmp(Ephone,addressBook->contacts[i].phone) == 0){
					flag2=0;
					for(int j=i;j<addressBook->contactCount;j++){
						if(j==i){
						printf("Deleted Contact info ---> Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						}
						addressBook->contacts[j]=addressBook->contacts[j+1];
						}
					break;

					}
								}
			
			if (flag2){
				printf("Entered number was not found\n");
			}
			else{
				addressBook->contactCount--;
			}
		}
		else if(choice == 3){
			printf("Enter the Email of the contact that u want to delete : ");
			char Email[40];
			fflush(stdout);
			fgets(Email,sizeof(Email),stdin);
			trim_newline(Email);
			int flag3=1;
			for(int i=0;i<addressBook -> contactCount;i++){
				if(strcmp(Email,addressBook->contacts[i].phone) == 0){
					flag3=0;
					for(int j=i;j<addressBook->contactCount;j++){
						if(j==i){
						printf("Deleted contact info -----> Name = %s------Phone number = %s------Emailid = %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						}
						addressBook->contacts[j]=addressBook->contacts[j+1];
						}
 					break;

					}
								}
			if (flag3){
				printf("Entered email was not found\n");
			}
			else{
				addressBook->contactCount--;
			}


		}
		else{
		printf("invalid option");
	}
 
} 
