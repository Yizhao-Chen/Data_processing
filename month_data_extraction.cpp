#include <stdio.h>
#include "malloc.h"
#include<stdlib.h>



int main(){
	int i,j,k;
	int year, jday;
	char input1[200],input2[200],output1[200];
	float cal1[5000],cal2[5000],calculate1[5000],calculate2[5000],calculate3[5000];

	FILE *input_1;
	FILE *input_2;
	FILE *output;
	
	for (j=0;j<4500;j++){
	cal1[j]=0;
	cal2[j]=0;
	calculate1[j]=0;
	calculate2[j]=0;
	calculate3[j]=0;
	}

	for (year=1992; year<1999;year++){
		for(jday=1; jday<332;jday=jday+30){
		sprintf(input1,"\\Global_output\\nep\\cnep%d%s%d%s",year,"_",jday,".img");
		sprintf(input2,"\\Global_output\\nep\\cnep%d%s%d%s",year,"_",jday+30,".img");
		sprintf(output1,"\\Global_output\\nep\\month_results\\cnep%d%s%d%s",year,"_",(jday-1)/10,".img");
		
		 if((input_1=fopen(input1,"rb"))==NULL){
        printf("Can not open the file %s\n",input1);   
       exit(0);
	  } 
			
		 if((input_2=fopen(input2,"rb"))==NULL){
        printf("Can not open the file %s\n",input2);   
       exit(0);
	  } 
		 if((output=fopen(output1,"ab+"))==NULL){
        printf("Can not open the file %s\n",output);    
       exit(0);
	  } 
	for (k=0;k<2250;k++){
		 fread(&cal1[0],sizeof(float),4500,input_1); 
		 fread(&cal2[0],sizeof(float),4500,input_2);
		 for(i=0;i<4500;i++){ 
			 calculate1[i]=cal1[i];
			 calculate2[i]=cal2[i];
			 if(cal1[i] == 999.0){
			 cal1[i]=0.0;
			 };
			 calculate3[i] = calculate2[i] - calculate1[i];
		 }
		fwrite(&calculate3[0],sizeof(float),4500,output);
		}
	}
	}
	fclose(input_1);
	fclose(input_2);
	fclose(output);
	return 0;
}
