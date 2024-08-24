/*
       Name : Cibisakkaravarthi k
       Date : 16-aug-2024 : time 23:20 
Description : file.c file for AddressBook project. saving and writing functions are declared her for contact information */
#include <stdio.h>
#include<string.h>
#include "file.h"
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void saveContactsToFile(AddressBook *addressBook) {
	FILE *fp=fopen("list.csv","w");
	if(fp==NULL){
		printf("WARNING ~ file not loacated\n");
	}
	for(int i=0;i<addressBook->contactCount;i++){
		fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fprintf(fp,"#%d",addressBook->contactCount);
	rewind(fp);
	fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
	FILE *fp=fopen("list.csv","r");
	if(fp == NULL){
		printf("Error : while accessing file name list.csv ");
	}
	char temp[100];
	int i=0;
	while(fgets(temp,sizeof(temp),fp) != NULL){
		if (strlen(temp)==0){
			continue;
		}
		trim_newline(temp);
		char *nptr=strtok(temp,",");
		char *pptr=strtok(NULL,",");
		char *eptr=strtok(NULL,",");
		if (nptr == NULL || pptr == NULL || eptr== NULL){
			continue;
		}
		strcpy(addressBook->contacts[i].name,nptr);
		strcpy(addressBook->contacts[i].phone,pptr);
		strcpy(addressBook->contacts[i].email,eptr);
		
		i++;
		addressBook->contactCount++;
	}
	fclose(fp);
}
