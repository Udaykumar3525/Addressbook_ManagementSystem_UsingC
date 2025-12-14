#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "validation.h"

int validation_name(char *name){     
    if (! (name[0]>='A' && name[0]<='Z'))   //first character must be capital (A - Z)
    return 0;                             //Validation not satisfied - False
    for (int i=1; name[i] != '\0'; i++)
    {
        if (name[i]==' ')     //only after space - the next character should be only capital or as usual a small letter but  no other characters
        {
            if (!(name[i+1]>='A' && name[i+1]<='Z' || name[i+1]>='a' && name[i+1]<='z'))
            return 0;   //if not 
            i++;      //goes to next character
            continue;    //Skips next check
        }

        if ( !(name[i]>='a' && name[i]<='z' || name[i]==' '))   //remaining chrcaters must be small (a-z)
        return 0;
    }
    return 1;    //Validation successful - Satisfied all - Valid Name
}

int validation_number(char *num){
    int i;
    for (i=0; num[i] != '\0'; i++)       //loop runs until it reaches null character - end of string
    {
        if (!(num[i]>='0' && num[i]<='9'))         //only digits - no alpha, special characters
        return 0;                              //non digit 
    }
    return (i==10);   // Number count should be 10 - if 10 True returns 1  , else 0
}

int validation_email(char *mail){
    char sub_string[]="@gmail.com";     //It should be must at the end
    int length=strlen(mail);            //Gives the length of user entered email
    int domain_len=strlen(sub_string);  //Length of domain - @gmail.com
    int local_len=length-domain_len;       //number of characters before @gmail.com or (it also gives domain start index)

    //Email should contain atleast 1 character before @gmail.com
    //it will gives the mail is only ending with @gmail.com not any other extra characters after that
    if ((length<=10) || (strcmp(mail + local_len, sub_string) != 0) || (!(mail[0]>='a' && mail[0]<='z')))   //checks the first character of mail - it must be small
        return 0;
    
    for (int i=1; i<local_len; i++)    //runs until before @gmail.com - check the charcaters are valid until @
    {
        char c=mail[i];
        if ( !(c>='a' && c<='z' || c>='0' && c<='9' || c =='_' ))  //Checks there is no capital and special characters are there or not
        return 0;   
    }

    return 1;      //Validation successful - Satisfied all - Valid email
}