#include <stdio.h>
#include <stdlib.h>
#include "funtion.h"
/*Jorge Garza
 *M.R-A.
 *Y.Z-G. 
 * compiler: $ gcc lectura_bandas_crystal.c gnu.c lectura_dos_crystal.c crystal.c -o crysplot
 * run:  $./crysplot 
 * conditions: make file: "input.crystal" 
 *           input.crystal:include all input files .f25 (or fort.25) in the following order
 *                $ 1 filename.f25 
 *                $ 2 structure_band.f25 DOS.f25
 *                $ 1 ...
 *                $...  
 *    if include the option 1 generate structure bands (only one file)
 *    or include 2 generate density states but remenber include two files
 *    you can include options you want in any order
 * returns two files 
 *      1) filename.f25.dat: this file contains values for plot density states or DOS 
 *      2) filename.f25.glpt:code for plot in gnuplot which return one file
 *      called filename.f25.out (run: $ gnuplot *.out), this file( .glpt) you could  edit 
 *           i) filename.f25.out:this file is a plot of  input file
 * */

int main()
{
	char filename[100], filename2[100];
	int  option[2], path_gnu[2], cont[2];
	double etop_dos[2], grid_path[100000];
	FILE *en;
        en=fopen("crysplot.in","r");
while(!feof(en))
{
	fscanf(en,"%d",&option[1]);
	switch(option[1])
	{
	  case 1: /*Band structure(BS) */		 
		fscanf(en,"%s",filename);
		BS(filename,etop_dos,grid_path,path_gnu);
		gnuplot(option, filename, filename2, grid_path,path_gnu, cont);
		break;
	  case 2:/*Band structure(BS) and  Density of states(DOS)*/
                fscanf(en,"%s %s",filename,filename2);
	        BS(filename,etop_dos,grid_path,path_gnu);
		//gnuplot(option, filename, filename2, grid_path, path_gnu, cont);
	        cont[1]=0;
        	DOS(filename2,etop_dos, cont);
		gnuplot(option, filename, filename2, grid_path, path_gnu, cont); 
		break;
	}
}
        fclose(en);
return 0;
}
