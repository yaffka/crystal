#include <stdio.h>
#include <string.h>
#include "funtion.h"

void change(char *p, char *file,char *type)
{
	strcpy(p,file);
	char *end = p + strlen(p);
	while (end > p && *end != '.') --end;
	if (end > p) *end = '\0';
	sprintf(p,"%s%s",p,type);
}
