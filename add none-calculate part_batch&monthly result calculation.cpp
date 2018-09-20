#include <stdio.h>	
int main(){
		int i,j,t,l;
		int year,month,jday,jday1;
		char filename[255];
		char filename1[255];
		char filename2[255];
		short k[4500] = {0};
		short d[4500] = {0};
		short p[4500] = {0};
		short m[4500] = {0};
		
		FILE *fp;
		FILE *infile;
		FILE *infile1;
	
	//chen: for SoilC processing
	//	if ((fp = fopen("test20.dat", "ab+")) == NULL)
	//	printf("what the fuck!");
	//	if((fd = fopen("SOILC_FLOAT_1000_Resample1.dat","rb")) == NULL)
	//	printf("you mother fucker!!!");
		



		for (year=1982; year<2009; ++year){
			for (jday = 1; jday<362; ++jday){
				if(jday<=1){                                                           //Chen: do nothing for day1
			/*	sprintf(filename, "G:\\Global_output_5_5_1982_2008_new\\npp\\cnpp%d%s%d%s",year,"_",jday,".img");
				sprintf(filename1,"G:\\Global_output_5_5_1982_2008_new\\npp\\cnpp%d%s%d%s",year,"_",jday,"_comp.img");
				if ((infile=fopen(filename, "rb")) == NULL) {
						printf("\n Unable to open file <%s>,  exitting program ...\n\n",filename);
						}
				if ((fp=fopen(filename1, "ab+")) == NULL) {
						printf("\n Unable to open file <%s>,  exitting program ...\n\n",filename1);

						/*================for none-calculated part add====================*/			
										//	for (i=0; i<400; ++i){
	
										//	fwrite(&k[0], sizeof(short),4500, fp);
										//	}	
						/*================for none-calculated part add====================*/	
		
					/*	for (j=0; j<2250; ++j){
								fread(&d[0],sizeof(short),4500,infile);
								fwrite(&m[0],sizeof(short),4500,fp);
						}

						//	for(t=0;t<419;++t){
						//	fwrite(&p[0],sizeof(float),4500,fp);
						//	}
		
						fclose(infile);
						fclose(fp);
						*/
						t= t+1;
						}
						
				
				else if(jday==31||jday==61||jday==91||jday==121||jday==151||jday==181||jday==211||jday==241||jday==271||jday==301||jday==331||jday==361){
					jday1 = jday -30;
					month = int(jday/30);
				
				sprintf(filename, "I:\\TES_summary_1982_2008\\npp\\cnpp%d%s%d%s",year,"_",jday,"_comp.img");
				
				sprintf(filename1,"I:\\TES_summary_1982_2008\\npp\\cnpp%d%s%d%s",year,"_",jday1,"_comp.img");

				sprintf(filename2,"I:\\TES_summary_1982_2008\\npp\\monthly_npp\\cnpp%d%s%d%s",year,"_",month,".img");
				if ((infile=fopen(filename, "rb")) == NULL) {
						printf("\n Unable to open file <%s>,  exitting program ...\n\n",filename);
						}
				if ((infile1=fopen(filename1, "rb")) == NULL) {
						printf("\n Unable to open file <%s>,  exitting program ...\n\n",filename1);
						}
				if ((fp=fopen(filename2, "ab+")) == NULL) {
						printf("\n Unable to open file <%s>,  exitting program ...\n\n",filename2);
						}
						/*================for none-calculated part add====================*/			
										//	for (i=0; i<400; ++i){
	
										//	fwrite(&k[0], sizeof(short),4500, fp);
										//	}	
						/*================for none-calculated part add====================*/	
		
						for (j=0; j<2250; ++j){
								fread(&d[0],sizeof(short),4500,infile);
								fread(&k[0],sizeof(short),4500,infile1);
								for(l=0; l<4500; ++l){
									m[l] = d[l] - k[l];
								}
								fwrite(&m[0],sizeof(short),4500,fp);
						}

						//	for(t=0;t<419;++t){
						//	fwrite(&p[0],sizeof(float),4500,fp);
						//	}
						fclose(infile);
						fclose(fp);
			}
			else{
			t = t+1;
		}
				
			
			
			
		
/*================for none-calculated part add====================*/			
	//	for (i=0; i<400; ++i){
	
	//	fwrite(&k[0], sizeof(short),4500, fp);
	//	}	
/*================for none-calculated part add====================*/	
		
//		for (j=0; j<2250; ++j){
//				fread(&d[0],sizeof(short),4500,infile);
//				fwrite(&m[0],sizeof(short),4500,fp);
//		}

	//	for(t=0;t<419;++t){
	//	fwrite(&p[0],sizeof(float),4500,fp);
	//	}
		
//		fclose(infile);
//		fclose(fp);
		
		
			}   //day
		}	    //year
		
		return 0;
}