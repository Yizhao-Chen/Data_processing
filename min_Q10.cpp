/*=================Calculate Global Q10 from HWSD and BEPS simulate results======================*/
/* time: 2013.4.18*/


#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int main(){

		int u,w,i;
		int ddd;
		int def;
		int a[10000] = {0};
		int b[10000] = {0};
		int c[10000] = {0};
		int d[10000] = {0};
		int e[10000] = {0};
		int f[10000] = {0};
		int g[10000] = {0};
		int h[10000] = {0};
		int j[10000] = {0};
		int k[10000] = {0};
		int l[10000] = {0};
		int m[10000] = {0};
		int n[10000] = {0};
		int o[10000] = {0};
		int p[10000] = {0};
		int q[10000] = {0};
		int z[10000] = {0};
		int asw[10000];
		int min[10000];
		int minn[10000] = {0};
		int kkk[10000];



		FILE *f1;
		FILE *f2;
		FILE *f3;
		FILE *f4;
		FILE *f5;
		FILE *f6;
		FILE *f7;
		FILE *f8;
		FILE *f9;
		FILE *f10;
		FILE *f11;
		FILE *f12;
		FILE *f13;
		FILE *f14;
		FILE *f15;
		FILE *f16;
		FILE *fz;
		FILE *fy;

		if ((f1 = fopen("minus_1.0.dat", "ab+")) == NULL)
		printf("1");
		if ((f2 = fopen("minus_1.1.dat", "ab+")) == NULL)
		printf("2");
		if((f3 = fopen("minus_1.2.dat","ab+")) == NULL)
		printf("3");
		if((f4 = fopen("minus_1.3.dat","ab+")) == NULL)
		printf("4");
		if((f5 = fopen("minus_1.4.dat","ab+")) == NULL)
		printf("5");
		if((f6 = fopen("minus_1.4.dat","ab+")) == NULL)
		printf("6");
		if((f7 = fopen("minus_1.6.dat","ab+")) == NULL)
		printf("7");
		if((f8 = fopen("minus_1.7.dat","ab+")) == NULL)
		printf("8");
		if((f9 = fopen("minus_1.8.dat","ab+")) == NULL)
		printf("9");
		if((f10 = fopen("minus_1.9.dat","ab+")) == NULL)
		printf("10");
		if((f11 = fopen("minus_2.0.dat","ab+")) == NULL)
		printf("11");
		if((f12 = fopen("minus_2.1.dat","ab+")) == NULL)
		printf("12");
		if((f13 = fopen("minus_2.2.dat","ab+")) == NULL)
		printf("13");
		if((f14 = fopen("minus_2.3.dat","ab+")) == NULL)
		printf("14");
		if((f15 = fopen("minus_2.4.dat","ab+")) == NULL)
		printf("15");
		if((f16 = fopen("minus_2.5.dat","ab+")) == NULL)
		printf("16");
		

		if((fz = fopen("min_Q10.dat", "ab+")) == NULL)
		printf("output1");
		if((fy = fopen("min_Q10_value.dat", "ab+")) == NULL)
		printf("output2");


		for (u=0; u<2250; ++u){
		fread(&a[0],sizeof(float),4500,f1);
		fread(&b[0],sizeof(float),4500,f2);
		fread(&c[0],sizeof(float),4500,f3);
		fread(&d[0],sizeof(float),4500,f4);
		fread(&e[0],sizeof(float),4500,f5);
		fread(&f[0],sizeof(float),4500,f6);
		fread(&g[0],sizeof(float),4500,f7);
		fread(&h[0],sizeof(float),4500,f8);
		fread(&j[0],sizeof(float),4500,f9);
		fread(&k[0],sizeof(float),4500,f10);
		fread(&l[0],sizeof(float),4500,f11);
		fread(&m[0],sizeof(float),4500,f12);
		fread(&n[0],sizeof(float),4500,f13);
		fread(&o[0],sizeof(float),4500,f14);
		fread(&p[0],sizeof(float),4500,f15);
		fread(&q[0],sizeof(float),4500,f16);

		
		for (w=0; w<4500; ++w){
			asw[10]=a[w];
			asw[11]=b[w];
			asw[12]=c[w];
			asw[13]=d[w];
			asw[14]=e[w];
			asw[15]=f[w];
			asw[16]=g[w];
			asw[17]=h[w];
			asw[18]=j[w];
			asw[19]=k[w];
			asw[20]=l[w];
			asw[21]=m[w];
			asw[22]=n[w];
			asw[23]=o[w];
			asw[24]=p[w];
			asw[25]=q[w];

			min[w] = asw[10];
			ddd= min[w];
			kkk[w]=0;
			for (i=10; i<26; ++i){
				kkk[w] = kkk[w]+1;
				def = asw[i];
				if (def < ddd){
					min[w] = def;
					minn[w] = 9+kkk[w];
				}
			}
				
			}
		fwrite(&min, sizeof(int),4500,fy);
		fwrite(&minn,sizeof(int),4500,fz);

		}
	return 0;
}