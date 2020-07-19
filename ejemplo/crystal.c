#include <stdio.h>
#include "funtion.h"

int main(){
	char filename[100], filename2[100];
	int  option;
  scanf("%d",&option);
  switch(option){
	  case 1: /*Band structure(BS) */		 
                  scanf("%s",filename);
		  BS(filename);
		 break;
	  case 2:/*Band structure(BS) and  Density of states(DOS)*/
		 BS(filename);
	//	 DOS(filename2);
		 break;
  }
return 0;
}
