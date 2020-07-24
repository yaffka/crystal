#include <stdio.h>
#include <stdlib.h>
#include "funtion.h"

void gnuplot(int option[2], char filename[100],char filename2[100], double grid_path[100000],int path_gnu[2],int cont[2]){
	char out_gn[100], gn[10]=".gplt",dat[8]=".dat",out_pic[10]=".eps";
	char gnuplot_file[100],picture[100],trash[10];
	FILE *on,*in;
        int nband;
switch(option[1]){
  case 1:	
    change(out_gn,filename,gn); //.dat
    on=fopen(out_gn,"w");
    in=fopen(filename,"r");
    fscanf(in,"%3s%1d%4s%5d",trash, &nband,trash, &nband);
    fclose(in);

    fprintf(on,"#!/usr/bin/gnuplot -persist \nset term post enh color eps size 4cm,9cm \n");
    change(picture,filename,out_pic); //.eps
    fprintf(on,"set out '%s' \n",picture);
    fprintf(on,"unset xtics \nunset key \nset ylabel \"Energy (eV)\" \n#set ylabel font \"20\" \nset style line 1 lt 2 lw 1\n");
    if (nband>1){
       fprintf(on,"set xtics(\"K1\" 0.0,");
       for(int j=1;j<path_gnu[2];j++){
           fprintf(on,"\"K%d\" %lf,",j+1,grid_path[j]);
       }
       fprintf(on,")\n");
    }
    fprintf(on,"#print tiks \n#set xtics @tiks \n#set ytics -12., 2.0 \nset mytics 5 \n#unset ytics \nset style line 12 lc rgb 'black' lt 1 lw 2 \nset style line 10 lc rgb 'black' lt -1 lw 1 \nset grid back ls 12 \nset grid noytics \n#file=\"bands.out\"\n");
    change(gnuplot_file,filename,dat);//.dat
    fprintf(on,"file=\"%s\"\n",gnuplot_file);
    if(nband>1){
    fprintf(on,"plot file u 1:2 w l lt 0 lw 2,\\\n");
         for(int i=3;i<(nband+2);i++){
            fprintf(on,"file u 1:%d w l lt -1,\\\n",i);
         }
         fprintf(on,"file u 1:%d w l lt -1\n\n",nband+2);
	fclose(on);
    }
    break;
  case 2:
           /*   opcion 2  activar el puntero */
    //imprime todas las proyecciones menos la total
 if(cont[1]>1){
    for(int j=1;j<cont[1];j++){
        change(out_gn,filename2,gn); //.gplt
        on=fopen(out_gn,"w");
	fprintf(on,"#!/usr/bin/gnuplot -persist \nset term post enh color eps size 4cm,9cm\n");
        change(picture,filename2,out_pic);//.eps
        fprintf(on,"set out '%s' \n",picture);
        fprintf(on,"unset xtics \nunset key \nset ylabel \"Energy (eV)\" \nset ylabel font \"20\" \nset style line 1 lt 2 lw 1\n");
        fprintf(on,"#print tiks \n#set xtics @tiks \n#set ytics -12., 2.0 \nset mytics 5 \n#unset ytics \nset style line 12 lc rgb 'black' lt 1 lw 2 \nset style line 10 lc rgb 'black' lt -1 lw 1 \nset grid back ls 12 \nset grid noytics \n#file=\"bands.out\"\n");
        change(gnuplot_file,filename2,dat);//.dat
        fprintf(on,"file=\"%s\"\n",gnuplot_file);
        fprintf(on,"plot file u %d:1 w l lt -1,\\\n",j+1);
	fclose(on);
    }
 }
        /*impresión de la densidad total y bandas*/
    //DOS
    change(out_gn,filename2,gn);//.gplt
    on=fopen(out_gn,"w");
    fprintf(on,"#!/usr/bin/gnuplot -persist \nset term post enh color eps size 6cm,12cm\n");
    change(picture,filename2,out_pic);//.eps
    fprintf(on,"set out '%s' \n",picture);
    fprintf(on,"unset xtics\nunset key\n#print tiks\n#set xtics @tiks\n#set ytics -12., 2.0\nset mytics 5\n#unset ytics\nset style line 12 lc rgb 'black' lt 1 lw 2\nset style line 10 lc rgb 'black' lt -1 lw 1\nset grid back ls 12\nset grid noytics\n#file=\"bands.out\"\n#set yrange[*:*]\nset multiplot layout 1,2\nunset ytics\n");
    change(gnuplot_file,filename2,dat);//.dat
    fprintf(on,"file=\"%s\"\n",gnuplot_file);
    fprintf(on,"set xtics(\"\"0.0)\nset origin 0.5,0.0\nplot file u %d:1 w l lt -1\n",cont[1]+1);
    //Bands
    fprintf(on,"set origin 0.12,0.0\n");
    change(gnuplot_file,filename,dat);//.dat
    fprintf(on,"file=\"%s\"\n",gnuplot_file);
    fprintf(on,"set ytics\nset ylabel \"Energy (eV)\"\nset ylabel font \"20\"\nset style line 1 lt 2 lw 1\n");
    //escanear en nbandas 
    in=fopen(filename,"r");
    fscanf(in,"%3s%1d%4s%5d",trash, &nband,trash, &nband);
    fclose(in);
    fprintf(on,"set xtics(\"K1\" 0.0,");
    for(int j=1;j<path_gnu[2];j++){
           fprintf(on,"\"K%d\" %lf,",j+1,grid_path[j]);
    }
    fprintf(on,")\n");
    fprintf(on,"plot file u 1:2 w l lt 0 lw 2,\\\n");
    for(int i=3;i<(nband+2);i++){
            fprintf(on,"file u 1:%d w l lt -1,\\\n",i);
    }
    fprintf(on,"file u 1:%d w l lt -1\n",nband+2);
    fprintf(on,"unset multiplot\n");
    fclose(on);
   
    break;  
}    
}
