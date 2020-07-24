#include <stdio.h>
#include <string.h>
#include "funtion.h"

//void change(char *, char *);
void change(char *p, char *file,char *type)
{
       //char file[20]="crystal.f25",fileout[100], type='.' ;
       //printf("file: %s\n",file);
	char *end = p + strlen(p);
	while (end > p && *end != '.') --end;
	if (end > p) *end = '\0';
     //   change(strcpy(fileout,file),file);
	sprintf(p,"%5s.dat",p);
	printf("file: %s\n fileout:%s\n",file, p);
}
/*void change(char *p,char *file)
{	char *end = p + strlen(p);
	while (end > p && *end != '.') --end;
	if (end > p) *end = '\0';
}*/
