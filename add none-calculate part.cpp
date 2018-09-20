#include <stdio.h>	
int main(){
		int i,j,t;
		float k[4500] = {0};
		float d[4500] = {0};
		float p[4500] = {0};
		
		FILE *fp;
		FILE *fd;
		if ((fp = fopen("test20.dat", "ab+")) == NULL)
		printf("input wrong!");
		if((fd = fopen("SOILC_FLOAT_1000_Resample1.dat","rb")) == NULL)
		printf("output wrong!");
		
		for (i=0; i<75; ++i){
	
		fwrite(&k[0], sizeof(float),4500, fp);
		}
		
		for (j=0; j<1756; ++j){
		fread(&d[0],sizeof(float),4500,fd);
		fwrite(&d[0],sizeof(float),4500,fp);
		}

		for(t=0;t<419;++t){
		fwrite(&p[0],sizeof(float),4500,fp);
		}
		
		fclose(fp);
		fclose(fd);
		return 0;
}

		
