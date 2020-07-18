#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funtion"

void vector(){
     float posA[3], posB[3], posC[3];
     float diffAB[3], diffAC[3], NormAB, NormAC;
     float unitAB[3], unitAC[3];
/*
posA[0]=-4.840; posA[1]=-4.209; posA[2]=1.403;
posB[0]=-4.088; posB[1]=-3.665; posB[2]=1.716;
posC[0]=-7.073; posC[1]=-4.009; posC[2]=1.116;
*/

scanf("%f %f %f",&posA[0],&posA[1],&posA[2]);
scanf("%f %f %f",&posB[0],&posB[1],&posB[2]);
scanf("%f %f %f",&posC[0],&posC[1],&posC[2]);

printf("posiciones iniciales\n%lf %lf %lf\n",posA[0], posA[1], posA[2]);
printf("%lf %lf %lf\n",posB[0], posB[1], posB[2]);
printf("%lf %lf %lf\n",posC[0], posC[1], posC[2]);

diffAB[0]=posB[0]-posA[0];  diffAB[1]=posB[1]-posA[1]; diffAB[2]=posB[2]-posA[2];
NormAB=sqrt(pow(diffAB[0],2.f)+pow(diffAB[1],2.f)+pow(diffAB[2],2.f));
unitAB[0]=diffAB[0]/NormAB; unitAB[1]=diffAB[1]/NormAB; unitAB[2]=diffAB[2]/NormAB;

//printf("diffAB:%lf %lf %lf\n",diffAB[0], diffAB[1], diffAB[2]);
printf("vector unitAB:%lf, %lf, %lf.\n",unitAB[0],unitAB[1], unitAB[2]);

diffAC[0]=posC[0]-posA[0];  diffAC[1]=posC[1]-posA[1]; diffAC[2]=posC[2]-posA[2];
NormAC=sqrt(pow(diffAC[0],2.f)+pow(diffAC[1],2.f)+pow(diffAC[2],2.f));
unitAC[0]=diffAC[0]/NormAC; unitAC[1]=diffAC[1]/NormAC; unitAC[2]=diffAC[2]/NormAC;

//printf("diffAC:%lf %lf %lf\n",diffAC[0], diffAC[1], diffAC[2]);
printf("Vector unitAC:%lf, %lf, %lf.\n",unitAC[0],unitAC[1], unitAC[2]);
     int    in;
     double ux, uy, uz, uxn, uyn, uzn;
     float  ABxAC[3],NormABC;
     
ABxAC[0]=unitAB[1]*unitAC[2]-unitAC[1]*unitAB[2];
ABxAC[1]=-unitAB[0]*unitAC[2]+unitAC[0]*unitAB[2];
ABxAC[2]=unitAB[0]*unitAC[1]-unitAC[0]*unitAB[1];
NormABC=sqrt(pow(ABxAC[0],2.f)+pow(ABxAC[1],2.f)+pow(ABxAC[2],2.f));
printf("ABxAC:%lf %lf %lf\n",ABxAC[0],ABxAC[1],ABxAC[2]);

uxn=0;
uyn=0;
uzn=0;
do{
	in++;
  ux=(-unitAB[1]*uyn-unitAB[2]*uzn)/unitAB[0];
  uy=sqrt(1-pow(uxn,2.f)-pow(uzn,2.f));
  uz=(-(ABxAC[0]/NormABC)*uxn-(ABxAC[1]/NormABC)*uyn)/(ABxAC[2]/NormABC);
  uxn=ux;
  uyn=uy;
  uzn=uz;
}	
while(in<10000);
printf("Vector perpendicular al vector unitAB:%lf, %lf, %lf\n",ux, uy, uz);
      double C1, C2;
//condiciones  
C1=(ux*unitAB[0]+uy*unitAB[1]+uz*unitAB[2]);
printf("Condicion 1:%E\n",C1);
//printf("%lf %lf %lf",ABxAC[0],ABxAC[1],ABxAC[2]);
//printf("%lf, %lf, %lf",ux, uy, uz);
C2=(ux*ABxAC[0]+uy*ABxAC[1]+uz*ABxAC[2]);
printf("Condicion 2 :%E***\n",C2);

      double width=4;
      float vecAbajo[3],vecArriba[3] ,vecDiagonal[3];

vecAbajo[0]=posA[0]-width*(-ux)-width*unitAB[0];     
vecAbajo[1]=posA[1]-width*(-uy)-width*unitAB[1];     
vecAbajo[2]=posA[2]-width*(-uz)-width*unitAB[2];     
printf("vectores para CRYSTAL\n%lf %lf %lf\n",vecAbajo[0],vecAbajo[1],vecAbajo[2]);

vecArriba[0]=posA[0]-width*(-ux)+width*unitAB[0];     
vecArriba[1]=posA[1]-width*(-uy)+width*unitAB[1];     
vecArriba[2]=posA[2]-width*(-uz)+width*unitAB[2];     
printf("%lf %lf %lf\n",vecArriba[0],vecArriba[1],vecArriba[2]);

vecDiagonal[0]=posA[0]+width*(-ux)+width*unitAB[0];     
vecDiagonal[1]=posA[1]+width*(-uy)+width*unitAB[1];     
vecDiagonal[2]=posA[2]+width*(-uz)+width*unitAB[2];     
printf("%lf %lf %lf\n",vecDiagonal[0],vecDiagonal[1],vecDiagonal[2]);

        double diff1[3], diff2[3];
 
diff1[0]=vecAbajo[0]-vecArriba[0];    
diff1[1]=vecAbajo[1]-vecArriba[1];    
diff1[2]=vecAbajo[2]-vecArriba[2];    
printf("diff1:%lf %lf %lf\n",diff1[0],diff1[1],diff1[2]);

diff2[0]=vecDiagonal[0]-vecArriba[0];    
diff2[1]=vecDiagonal[1]-vecArriba[1];    
diff2[2]=vecDiagonal[2]-vecArriba[2];    
printf("diff2: %lf %lf %lf\n",diff2[0],diff2[1],diff2[2]);

       double Norm_d1, Norm_d2,PP12;

Norm_d1=sqrt(pow(diff1[0],2.f)+pow(diff1[1],2.f)+pow(diff1[2],2.f));      
Norm_d2=sqrt(pow(diff2[0],2.f)+pow(diff2[1],2.f)+pow(diff2[2],2.f));      
PP12=(diff1[0]*diff2[0]+diff1[1]*diff2[1]+diff1[2]*diff2[2])/(Norm_d1*Norm_d2);
printf("diff1.diff2/(Norm[diff1]Norm[diff2]):%E***\n",PP12);

       double P1x2[3];
P1x2[0]=diff1[1]*diff2[2]-diff2[1]*diff1[2];
P1x2[1]=-diff1[0]*diff2[2]+diff2[0]*diff1[2];
P1x2[2]=diff1[0]*diff2[1]-diff2[0]*diff1[1];
printf("perpendicular\n%lf %lf %lf\n",P1x2[0],P1x2[1],P1x2[2]);
  
       double Pdiff2;

Pdiff2=P1x2[0]*diff2[0]-P1x2[1]*diff2[1]+P1x2[2]*diff2[2];
printf("perperndicular.diff2\n %E***\n",Pdiff2);

       double testA[3], testB[3], testC[3];

testA[0]=posA[0]-vecArriba[0];      
testA[1]=posA[1]-vecArriba[1];      
testA[2]=posA[2]-vecArriba[2];      
printf("testA=%lf %lf %lf\n",testA[0], testA[1], testA[2]);
testB[0]=posB[0]-vecArriba[0];      
testB[1]=posB[1]-vecArriba[1];      
testB[2]=posB[2]-vecArriba[2];      
printf("testB=%lf %lf %lf\n",testB[0], testB[1], testB[2]);

testC[0]=posC[0]-vecArriba[0];      
testC[1]=posC[1]-vecArriba[1];      
testC[2]=posC[2]-vecArriba[2];      
printf("testC=%lf %lf %lf\n",testC[0], testC[1], testC[2]);

      double tBPP;

tBPP=testB[0]*P1x2[0]+testB[1]*P1x2[1]+testB[2]*P1x2[2];
printf("testB.perpendicular=%E***\n",tBPP);

}
