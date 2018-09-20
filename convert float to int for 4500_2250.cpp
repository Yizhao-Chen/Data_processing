#include <stdio.h>


int main(){
		int k;
		int j;
		int i;
		short g[10000] = {0};
		float d[10000] = {0};

		FILE *fp;
		FILE *fd;

		if ((fp = fopen("total1986_361.img", "ab+")) == NULL)
		printf("input wrong!");
		if((fd = fopen("test1.dat","ab+")) == NULL)
		printf("output wrong!");

		for (j=0; j<2250; ++j){
		fread(&d[0],sizeof(float),4500,fp);
		for (i=0; i<4500; ++i){
			g[i] = (int)d[i];
			printf("%d\n", g[i]);
			}
		fwrite(&g[0],sizeof(short),4500,fd);
		}

		fclose(fp);
		fclose(fd);
		return 0;
}
