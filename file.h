/*
       Name : Cibisakkaravarthi k
       Date : 16-aug-2024 : time 23:20 
Description : file.h file for AddressBook project. Macros and functions are abstracted here for saving and loading informations for contacts.
*/
#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
