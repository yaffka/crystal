// Program to plot the band structure from CRYSTAL14
// Input file : fort.25 from CRYSTAL14
// Jorge Garza, April, 2017
// 
#include <stdio.h>
#include "funtion.h"
void DOS(char filename2[100], double etop_dos[2], int cont[2]) {
 int i, j, k, ihferm, nband, i1, i2, i3, j1, j2, j3, path, test, target_vale, target_cond,
     trash_int, num_path, total_points, nkp;
 double dum, ef, emin, emax, trash_dble, kini, kpt, etop, ebot, dk;
 double dos[100000], grid_path[1000];
 char trash[10], type[10], out[100], dat[8]=".dat";
 FILE *input, *output;

 etop=etop_dos[1];
 sprintf(out,"%s%s",filename2,dat);
 input=fopen(filename2,"r");
 output=fopen(out,"w");

 target_cond = target_vale + 1;
 i = 0;
 num_path = 0;
 do {
   test = fscanf(input,"%3s", trash);
   //cont[1]++;//help in gnu.c 
   if (test != EOF) {
     num_path++;
     fscanf(input,"%1d%4s%5d%5d%12lf%12lf%12lf", &ihferm, type, &nband, &trash_int, &dum, &trash_dble, &ef);
     nkp = trash_int;
     dk = trash_dble;
     fscanf(input,"%lf %lf", &emin, &emax);
     fscanf(input,"%d %d %d %d %d %d", &i1, &i2, &i3, &j1, &j2, &j3);

     for (k = 1; k <= nkp; k++) {
       i++;
       fscanf(input,"%12lf", &trash_dble);
       dos[i] = trash_dble; 
     }
   }
 } while(test != EOF);
 cont[1]=num_path;
//printf("%d\n",cont[1]);
 total_points = i;
 kini = emax;

 for (j = 1; j <= nkp; j++) {
   kpt = kini + dk*(j-1);
   fprintf(output,"%f  ", (kpt - etop)*27.211f);
   for (k = 1; k <=num_path; k++) fprintf(output,"   %10.6f", dos[j + (k - 1)*nkp]/27.211f);
   fprintf(output,"\n");
 }

}

