// Program to plot the band structure from CRYSTAL14
// Input file : fort.25 from CRYSTAL14
// Jorge Garza, April, 2017
// M.R-A. Note: First line of fort.25 must be number of valence bands
#include <stdio.h>
#include "funtion.h"

void BS(char filename[100]) {
 int i, j, k, ihferm, nband, i1, i2, i3, j1, j2, j3, path, test, target_vale, target_cond,
     trash_int, num_path, total_points;
 double dum, ef, emin, emax, trash_dble, kini, kpt, etop, ebot;

 int nkp[1000];
 double dispersion[100000], grid_path[1000], dk[100000];
 char trash[10], type[10];

 FILE *in,*on;
 char dat[8]="BS.dat";
 char fileout[100];
 in=fopen(filename,"r");

 fscanf(in,"%d", &target_vale);

 target_cond = target_vale + 1;
 kini = 0.f;
 path = 0;
 i = 0;
 do {
   test = fscanf(in,"%3s", trash);
   if (test != EOF) {
     path++;
     fscanf(in,"%1d%4s%5d%5d%12lf%12lf%12lf", &ihferm, type, &nband, &trash_int, &dum, &trash_dble, &ef);
     nkp[path] = trash_int;
     dk[path] = trash_dble;
     fscanf(in,"%lf %lf", &emin, &emax);
     fscanf(in,"%d %d %d %d %d %d", &i1, &i2, &i3, &j1, &j2, &j3);

     for (k = 1; k <= nband*nkp[path]; k++) {
       i++;
       fscanf(in,"%12lf", &trash_dble);
       dispersion[i] = trash_dble;
     }
     kpt = kini + dk[path]*(nkp[path]-1);
     grid_path[path] = kpt;
     kini = kpt;
   }
 } while(test != EOF);

 sprintf(fileout,"%s%s",filename,dat);
 on=fopen("P1","w");/*recuarda cabiar "P1" por fileout*/

 total_points = i;

 etop = -1e10;
 ebot = 1e10;
 for (j = 1; j <= total_points; j++) {
   k = j - nband*(j/nband);
   if (k == 0) k = nband;
   if (k == target_vale) { 
     if (dispersion[j] > etop) etop = dispersion[j];
   }
   if (k == target_cond) { 
     if (dispersion[j] < ebot) ebot = dispersion[j];
   }
 }

 i = 0;
 for (num_path = 1; num_path <= path; num_path++) {
   if (num_path == 1) kini = 0.f;
   else kini = grid_path[num_path - 1];
   for (j = 1; j <= nkp[num_path]; j++) {
     kpt = kini + dk[num_path]*(j-1);
     fprintf(on,"%f %f", kpt, 0.f);
     for (k = 1; k <= nband; k++) {
       i++;
       fprintf(on,"  %f", (dispersion[i] - etop)*27.211f);
     }
     fprintf(on,"\n");
   }
 } 

 fprintf(on,"I found %d paths: ", path);
 for (i = 1; i <= path; i++) fprintf(on,"%f  ", grid_path[i]);
 fprintf(on,"Ef=%f, ", ef);
 fprintf(on,"Emax=%f, Emin=%f\n", etop, ebot);
 fprintf(on,"Gap=%f\n", (ebot - etop)*27.211f);
 fprintf(on,"\n");
}
