#include <stdio.h>
#include <malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct climatedata
	{
	int long pix;
    short tmax;
	short tmin;
	short rehum;
	short srad;
	short precip;
  };
int main(){
	struct climatedata *sdat; 
	char  outfnpp_name[255];


	long i, year, jday;
	FILE  *outfilenpp;

	unsigned short aaa[5000];
	unsigned short *outputprep;
	long *outputtemp;

	char outf_name[255];

	outputprep = (unsigned short *)malloc(10*4500*sizeof(unsigned short));
	outputtemp = (long *)malloc(10*4500*sizeof(long));
	
	
	


	
	char name_tmax[255];              //�ļ����� Maxmium Temperature, daily, 16s bit 
    char tmaxf[200]; 
    FILE *f_tmax;  /* Climate data, Feng, June, 2003*/
   	long ptr;
    int pix;
	unsigned short climatedata[30000];
	
	long bbb[5000], ccc[5000];

	sdat=(struct climatedata*)malloc(10*4500*sizeof(struct climatedata));



	for (i = 0; i < 2250; ++i){                                                               //��ѭ��
			
		for (year = 1982; year <= 1986; ++year){                                //��ѭ��

			for(pix=0; pix<4500; pix++) {
			aaa[pix] = 0;
			bbb[pix] = 0;
			ccc[pix] = 0;
	}
		
			for (jday=1; jday<=365; jday=jday++) {                                         //��ѭ��
				if(jday<10)	  sprintf(tmaxf,"\\Global_Input\\Prinston_2012_11\\M%d%s%d%s%d%s",year,"\\Md",year,"00",jday,".dat");
else if(jday>=10 && jday<100) sprintf(tmaxf,"\\Global_Input\\Prinston_2012_11\\M%d%s%d%s%d%s",year,"\\Md",year,"0",jday,".dat"); 
else if (jday>=100)           sprintf(tmaxf,"\\Global_Input\\Prinston_2012_11\\M%d%s%d%d%s",year,"\\Md",year,jday,".dat");


        if((f_tmax=fopen(tmaxf,"rb"))==NULL){
        printf("Can not open the file %s\n",name_tmax);    //��name_tmax�ļ��д�tmax
		}
       


      
ptr=(unsigned long)i* 4500 * sizeof(short)*5; //org   


fseek(f_tmax, ptr,SEEK_SET);        
//=================================================================================================/
fread(&climatedata[0],sizeof(short),4500,f_tmax);               //����
for(pix=0;pix<4500;pix++) sdat[pix].srad=climatedata[pix];   

fread(&climatedata[0],sizeof(short),4500,f_tmax);              //��ˮ����λ��0.1mm. 
for(pix=0;pix<4500;pix++) sdat[pix].precip=climatedata[pix];     
 
fread(&climatedata[0],sizeof(short),4500,f_tmax);   
for(pix=0;pix<4500;pix++) sdat[pix].rehum=climatedata[pix];   //���ʪ��
 
fread(&climatedata[0],sizeof(short),4500,f_tmax);             //�������
for(pix=0;pix<4500;pix++) sdat[pix].tmax=climatedata[pix];   
 
fread(&climatedata[0],sizeof(short),4500,f_tmax);             //�������  
for(pix=0;pix<4500;pix++) sdat[pix].tmin=climatedata[pix];   



		
fclose(f_tmax);




for(pix=0; pix<4500; pix++) {                            //��Ԫѭ��
							
							aaa[pix] = aaa[pix] + (unsigned short)sdat[pix].precip;
							bbb[pix] = bbb[pix] + (long)sdat[pix].tmax;
							
						


										}											//��Ԫѭ������
							}    //��ѭ��
		
	for(pix=0; pix<4500; pix++) { 
	             outputprep[pix]=aaa[pix]; //signed short ǿ�ư�Npp��Ϊ����������
	}					  
				  sprintf(outfnpp_name,"\\Global_output_pt\\prep\\prep%d.img",year);      ///////sprintf ����"cnpp90_%d.img"+j

                         
				  if ((outfilenpp=fopen(outfnpp_name, "a+b"))== NULL)
				  {
				  printf("\n Unable to open file <%s>,  exitting program ...\n\n", outf_name);
                  exit(0);
				  }
				   fwrite(&outputprep[0],sizeof(unsigned short),4500,outfilenpp);
                      fclose(outfilenpp);   
				

					  		
	for(pix=0; pix<4500; pix++) { 
	             outputtemp[pix]=(long)bbb[pix]; //signed short ǿ�ư�Npp��Ϊ����������
				 
	}
				  sprintf(outfnpp_name,"\\Global_output_pt\\temp\\temp%d.img",year);  

                         
				  if ((outfilenpp=fopen(outfnpp_name, "a+b"))== NULL)
				  {
				  printf("\n Unable to open file <%s>,  exitting program ...\n\n", outf_name);
                  exit(0);
				  }
				   fwrite(&outputtemp[0],sizeof(long),4500,outfilenpp);
                      fclose(outfilenpp);    
	
	
					}	   // ��ѭ��
			

		
				}     //��ѭ��
		return 0;
			}