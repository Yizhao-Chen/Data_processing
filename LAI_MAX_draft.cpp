#include <stdio.h>


int main(){
	int i,j;
	
	for (year=1980;year<2011;++year){
		sprintf(filename1,"LAI_%d%s",year,".dat");
		sprintf(filename2,"LAI_%d%s",year,".dat");
		sprintf(filename3,"LAI_%d%s",year,".dat");
		sprintf(filename4,"LAI_%d%s",year,".dat");
		sprintf(filename5,"LAI_%d%s",year,".dat");
		sprintf(filename6,"LAI_%d%s",year,".dat");
		sprintf(filename7,"LAI_%d%s",year,".dat");
		sprintf(filename8,"LAI_%d%s",year,".dat");
		sprintf(filename9,"LAI_%d%s",year,".dat");
		sprintf(filename10,"LAI_%d%s",year,".dat");



		if ((infile1=fopen(filename1, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile2=fopen(filename2, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile3=fopen(filename3, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile4=fopen(filename4, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile5=fopen(filename5, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile6=fopen(filename6, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
	    if ((infile7=fopen(filename7, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile8=fopen(filename8, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile9=fopen(filename9, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}
		if ((infile10=fopen(filename10, "rb")) == NULL) {
		   printf("\n Unable to open file <%s>,  exitting program ...\n\n", filename);
		return;
	}


	for (i=0;i<2091;++i){
		
			fread(&LAImax1[0],size=1, ,infile1);
			fread(&LAImax2[0],size=1, ,infile2);
			fread(&LAImax3[0],size=1, ,infile3);
			fread(&LAImax4[0],size=1, ,infile4);
			fread(&LAImax5[0],size=1, ,infile5);
			fread(&LAImax6[0],size=1, ,infile6);
			fread(&LAImax7[0],size=1, ,infile7);
			fread(&LAImax8[0],size=1, ,infile8);
			fread(&LAImax9[0],size=1, ,infile9);
			fread(&LAImax10[0],size=1, ,infile10);
		

			for (w=0;w<    ; ++j){
			asw[1]=LAImax1[w];
			asw[2]=LAImax2[w];
			asw[3]=LAImax3[w];
			asw[4]=LAImax4[w];
			asw[5]=LAImax5[w];
			asw[6]=LAImax6[w];
			asw[7]=LAImax7[w];
			asw[8]=LAImax8[w];
			asw[9]=LAImax9[w];
			asw[10]=LAImax10[w];

			max[w] = asw[1];
			ddd = max[w];
			kkk[w] = 0;
			for (j=2;j<10;++j){
				def = asw[j];
				if (def > ddd){
					ddd = def;
				}
				else{
					ddd = ddd;
				}
			}
			asw[w] = ddd;
		}

	}
	return 0;
}