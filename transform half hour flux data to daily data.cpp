#include <stdio.h>



int main(void){
		 

			int i,j,k,l;
		
			float a[100]/*,b[100],c[100]*/;
			float aa/*,bb,cc*/;

	
			FILE *fa;
			FILE *f;


			if((fa = fopen("data2.dat","ab+")) == NULL)
				printf("input wrong");
	
			if((f = fopen("daily_data_output2.dat","ab+")) == NULL)
				printf("output wrong");
			
			fprintf(f,"\n\n");
		
			

			for (k=0; k<=366;++k){
				aa = 0;
		
			//	bb = 0;
			//	cc = 0;
				for (i=0; i<=100;++i){
				a[i] = 0;
			//	b[i] = 0;
			//	c[i] = 0;
			}
		
				//for(k=0;k<j;++k)
				//	fscanf(fa,"%*[^\n]%*c"); 
			//	for(l=0;l<j;++l)
			//		fscanf(ha,"%*[^\n]%*c");    //ÌøÐÐ¹¦ÄÜ
				
				for (j=0; j<48; ++j){	
				fscanf(fa,"%f",&a[j]/*, &b[j], &c[j]*/);
				
				aa = aa + a[j];
			//	bb = bb + b[j];
			//	cc = cc + c[j];
		
				
			}
				fprintf(f,"%f\n", aa/*, bb,cc*/);

			}
		
				
		
					return 0;
			}
	