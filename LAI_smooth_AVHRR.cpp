// smooth.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
 # include <math.h>
 # include <stdio.h> 
 # include <stdlib.h> 
 # include <string.h>
 # include <malloc.h>
 #define N 24 //46   //number of scenes to be smoothed - alter the time.txt file content according to that
 #define MM 2




 #define LAMB 0.5   //0.5
 #define DAYSOFYEAR  365

# define PIXN  10125000//9331200 //10125000//1171968 // SE Asia
 //#define PIXN 49563249
 //#define In_Dir "E:\\LAI_test\\in"         //main input directory
//#define Out_Dir "E:\\LAI_test\\out"   //output directory




typedef struct SplineParamstag
   {
    double x, y, a, b, c, d;
    int xday;
   } SplineParams;
 
 typedef struct BezierPointstag
   {
    double x0, f0, x1, f1, x2, f2, x3, f3;
   } BezierPoints;

 /*__________________________________________*/
 
 
  
 double *NewVector(int nl, int nh) 
   {
    double *v = (double *)malloc((unsigned) (nh - nl + 1) * sizeof(double));
    if (!v)
       fprintf(stderr, "could not allocate memory in NewVector().");
    return (v - nl);
	
   }
 
 /*__________________________________________*/
 
 void FreeVector(double *v, int nl, int nh) 
   {
    nh = nh; /* This is only to show good grace */
    free((char*) (v + nl));
	

   }


 /*__________________________________________*/
  
 int *NewIntVector(int nl, int nh) 
   {
    int *v = (int *)malloc((unsigned) (nh - nl + 1) * sizeof(int));
    if (!v)
       fprintf(stderr, "could not allocate memory in NewIntVector().");
    return (v - nl);
   }
 
 /*__________________________________________*/
 
 void FreeIntVector(int *v, int nl, int nh) 
   {
    nh = nh; /* This is only to show good grace */
    free((char*) (v + nl));
	
	
   }
 /*__________________________________________*/
 
 SplineParams *NewSplineVector(int nl, int nh) 
   {
    SplineParams *s = (SplineParams *)malloc((unsigned) (nh - nl + 1) * sizeof(SplineParams));
    if (!s)
       fprintf(stderr, "could not allocate memory in NewSplineVector().");
    return (s - nl);
	
   }
   
 /*__________________________________________*/
 
 void FreeSplineVector(SplineParams *s, int nl, int nh) 
   {
    nh = nh; /* This is only to show good grace */
    free((char*) (s + nl));
	
   }
 
 /*__________________________________________*/
 
 BezierPoints *NewBezierVector(int nl, int nh) 
   {
    BezierPoints *b = (BezierPoints *)malloc((unsigned) (nh - nl + 1) * 
sizeof(BezierPoints));
    if (!b)
       fprintf(stderr, "could not allocate memory in NewBezierVector().");
    return (b - nl);
	}
   
 /*__________________________________________*/
 
 void FreeBezierVector(BezierPoints *b, int nl, int nh) 
   {
    nh = nh; /* This is only to show good grace */
    free((char*) (b + nl));
		
   }
 
 /*__________________________________________*/

 
 void Quincunx(int n, double *u, double *v, double *w, double *q)
   {
    int j; 
    
    u[-1] = 0;
    u[0] = 0;
    v[0] = 0;
    w[-1] = 0;
    w[0] = 0;
    
    for (j = 1; j <= n - 1; j++)
      {
       u[j] -=  u[j - 2] *  (w[j - 2] * w[j - 2]);
       u[j] -=  u[j - 1] * (v[j - 1] * v[j - 1]);
       v[j] = (v[j] - u[j - 1] * v[j - 1] * w[j - 1]) / u[j];
       w[j] /=  u[j];
      }
      
    q[0] = 0;
    q[-1] = 0;
    
    for (j = 1; j <= n - 1; j++)
       q[j] -= (v[j - 1] * q[j - 1] + w[j - 2] * q[j - 2]);
       
    for (j = 1; j <= n - 1; j++)
       q[j] /=  u[j];
       
    q[n + 1] = 0;
    q[n] = 0;
    
    for (j = n - 1; j >= 1; j--)
       q[j] -= (v[j] * q[j + 1] + w[j] * q[j + 2]);
   } 
 
 /*__________________________________________*/
 
  void SmoothingSpline(SplineParams *S, double *sigma, double lambda, int n)
   {
    double almostZero = 1.0E-6;
    double *h, *r, *f, *p, *q, *u, *v, *w;
    int i, j;
    double mu;

    h = NewVector(0, n);
    r = NewVector(0, n);
    f = NewVector(0, n);
    p = NewVector(0, n);
    q = NewVector(-1, n+1);
    u = NewVector(-1, n);
    v = NewVector(-1, n);
    w = NewVector(-1, n);


    if (lambda < almostZero)
       mu = 0;
    else
       mu = 2 * (1 - lambda) / (3 * lambda);

    h[0] = S[1].x - S[0].x;
    r[0] = 3 / h[0];


    for (i = 1; i <= n - 1; i++)
      {

       h[i] = S[i + 1].x - S[i].x;
       r[i] = 3 / h[i];
       f[i] = -(r[i - 1] + r[i]);
       p[i] = 2 * (S[i + 1].x - S[i - 1].x);
       q[i] = 3 * (S[i + 1].y - S[i].y) / h[i] - 3 * (S[i].y - S[i -1].y) / h[i - 1];
      }


    r[n] = 0;
    f[n] = 0;

    for (i = 1; i <= n - 1; i++)
      {
       u[i] = r[i - 1] * r[i - 1] * sigma[i - 1];
       u[i] += f[i] * (f[i] * sigma[i]);
       u[i] += r[i] * (r[i] * sigma[i + 1]);
       u[i] = mu * u[i] + p[i];
       v[i] = f[i] * r[i] * sigma[i];
       v[i] += r[i] * f[i + 1] * sigma[i + 1];
       v[i] = mu * v[i] + h[i];
       w[i] = mu * r[i] * r[i + 1] * sigma[i + 1];
      }

    Quincunx(n, u, v, w, q);

    S[0].d = S[0].y - mu * r[0] * q[1] * sigma[0];
    S[1].d = f[1] * q[1] + r[1] * q[2];
    S[1].d = S[1].y - mu * S[1].d * sigma[1];
    S[0].a = q[1] / (3 * h[0]);
    S[0].b = 0;
    S[0].c = (S[1].d - S[0].d) / h[0] - q[1] * h[0] / 3;
    r[0] = 0;

    for (j = 1; j <= n - 1; j++)
      {
       S[j].a = (q[j + 1] - q[j]) / (3 * h[j]);
       S[j].b = q[j];
       S[j].c = (q[j] + q[j - 1]) * h[j - 1] + S[j - 1].c;
       S[j].d = r[j - 1] * q[j - 1] + f[j] * q[j] + r[j] * q[j + 1];
       S[j].d = S[j].y - mu * S[j].d * sigma[j];
      }

     S[n].d = S[n].y - lambda * r[n - 1] * q[n - 1]* sigma[n];  //this line is added

    FreeVector(h, 0, n);
    FreeVector(r, 0, n);
    FreeVector(f, 0, n);
    FreeVector(p, 0, n);
    FreeVector(q, -1, n+1);
    FreeVector(u, -1, n);
    FreeVector(v, -1, n);
    FreeVector(w, -1, n);
   }

 
 /*__________________________________________*/
 
 void SplineToBezier(SplineParams *S, BezierPoints *B, int n)
   {
    int i; 
    double h, delt; 
    
    for (i = 0; i <= n - 1; i++)
      { 
       h = S[i + 1].x - S[i].x;
       delt = h / 3;
       B[i].x0 = S[i].x;
       B[i].x1 = B[i].x0 + delt;
       B[i].x2 = B[i].x1 + delt;
       B[i].x3 = B[i].x2 + delt;
       B[i].f0 = S[i].d;
       B[i].f1 = B[i].f0 + S[i].c * h / 3;
       B[i].f2 = B[i].f1 + (S[i].c + S[i].b * h) * h / 3;
       B[i].f3 = B[i].f0 + (S[i].c + (S[i].b + S[i].a * h) * h) * h;
      } 
   } 

void SplineToPoints(SplineParams *S, double *L, int n)
 {
    for(int i=0;i<N-1;i++){
        L[S[i].xday-1]=S[i].d;
        double u=(S[i+1].x-S[i].x)/(S[i+1].xday-S[i].xday);
        for(int j=S[i].xday+1;j<=S[i+1].xday;j++){
            double di=(j-S[i].xday)*u;
            L[j-1]=S[i].a*(di*di*di)+S[i].b*(di*di)+S[i].c*di+S[i].d;
        }
    }
    
}

/*	 int i;
	 double u,dx,daysbetween;
	 int daycounter=4;
	 for(i=0;i<=n-1;i++){
		 dx=S[i+1].x-S[i].x;
		 daysbetween=dx*8;
		 L[daycounter-1]=S[i].d;
		 
		 
		 daycounter++;
		
		 for (u=1.; u<daysbetween-0.1; u++){
			 L[daycounter-1]=S[i].a*(u*u*u/512.)+S[i].b*(u*u/64.)+S[i].c*u/8.+S[i].d;
			 
			 daycounter++;
			 if((i==n-1)&&(u+1.>daysbetween-.1)&&(u+1.<daysbetween+.1)){
				u++;
				L[daycounter-1]=S[i].a*(u*u*u/512.)+S[i].b*(u*u/64.)+S[i].c*u/8.+S[i].d;
				
			 }

			 
		 }
		 
	 }
	 

	 //fclose(fl);
 }*/
 double max(double *array,int n1,int n, int&Imax){
	 double maxvalue=-99999;
	 for(int i=n1;i<=n;i++){
		 if (array[i]>maxvalue){
			 maxvalue=array[i];
			 Imax=i;
		 }

	 }
	 return maxvalue;
 }
 double min( double *array, int n1,int n,int&Imin)
 {
	 double minvalue=99999;
	 for(int i=n1;i<=n;i++){
		 if(array[i]<minvalue){
			 minvalue=array[i];
			 Imin=i;
		 }
	 }
	 return minvalue;
 }
 void newsigma(double *sigma,double *y1, int *x,int n){
    int i;
    double *ddyshort,*dy1,*ddy1;
    ddyshort=NewVector(0,n);
    dy1=NewVector(0,DAYSOFYEAR-1);
    ddy1=NewVector(0,DAYSOFYEAR-1);
    //for(i=0;i<3;i++){
        //y1[i]=y1[3];}
    //y1[364]=y1[363];
	for(i=355;i<DAYSOFYEAR;i++){
		y1[i]=y1[354];
	}
    for(i=1;i<DAYSOFYEAR;i++){
        dy1[i]=y1[i]-y1[i-1];
        
//printf("%f\t",dy1[i]);
    }
   // printf("END\n");
    dy1[0]=dy1[1];
    for(i=1;i<DAYSOFYEAR;i++){
        ddy1[i]=dy1[i]-dy1[i-1];

       // printf("%f\t",ddy1[i]);

    }
    ddy1[0]=ddy1[1];
    int dumb=0;
    int &nothing=dumb;
    double maxddy1=max(ddy1,0,DAYSOFYEAR-1,nothing);
    //double qmaxddy1=maxddy1/10;
    //printf("QQQQQQQQQQQQQQQQQQQQQQQ%f\n",qmaxddy1);
    for(i=0;i<=n;i++){
        sigma[i]=1;
    }
    for(i=0;i<=n;i++){
        if(dy1[(int)x[i]]>0){
            if(ddy1[(int)x[i]]<0){
                sigma[i]=0.75;
                //printf("NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n");
            }
            else {
                sigma[i]=1-pow((ddy1[x[i]]/maxddy1),1./2.5);
                if (sigma[i]>0.75) sigma[i]=0.75;
            }
            /*if((ddy1[(int)x[i]]<=qmaxddy1)&&(ddy1[(int)x[i]]>=0)){
            sigma[i]=0.6;
            //printf("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY\n");
            }
            else if((ddy1[(int)x[i]]>2*qmaxddy1)&&(ddy1[(int)x[i]]<=3*qmaxddy1)){
            sigma[i]=0.3;
            }
            else if(ddy1[(int)x[i]]>3*qmaxddy1){
                sigma[i]=0.01;
            }*/
 
        }

    }
//     for(i=0;i<=n;i++){
        // printf("%f\t",sigma[i]);
//     }
    FreeVector(ddyshort,0,n);
    FreeVector(dy1,0,DAYSOFYEAR-1);
    FreeVector(ddy1,0,DAYSOFYEAR-1);

}


/*__________________________________________*/

 void dataproc(double* rawdata,double* xx, int* xxd,double* finaly,double* dfinaly,double* ddfinaly, double &maxv,int &Imax, int &Idmark1,int &Idmax, int & Idmark2,int &Imidmark, int &Iddmax,double *sigma){
    double lambda; 
    int i,j,jj, n,*yy;//, Iddmax; 
    double *x,*y,maxy,percent;//,ddmaxv;//,*ddfinaly;
    SplineParams  *Sm;
    BezierPoints *B;    
	percent=.05;    
    n = N-1;
	yy=NewIntVector(0,n); 

/*	int IFirst,ILast,IFirstMarker;
	double First, Last;
	IFirstMarker=0;
	for (i=0;i<=n;i++){
		if(rawdata[i]>128) {
			for(j=0; j<DAYSOFYEAR;j++){
				finaly[j]=rawdata[0];
				dfinaly[j+1]=0;
				ddfinaly[j+2]=0;
			}
			maxv=rawdata[0];
			Imax=0;
			Idmark1=0;
			Idmax=0;
			Idmark2=0;
			Imidmark=0;
			Iddmax=0;
			return;
		}
		if((rawdata[i]!=128)&&(IFirstMarker==0)){
			First=rawdata[i];
			IFirst=i;
			IFirstMarker=1;
		}
		if(rawdata[i]!=128){
			Last=rawdata[i];
			ILast=i;
		}
	}
	if((ILast<0)||(ILast>n)){
		for(j=0; j<DAYSOFYEAR;j++){
			finaly[j]=128;
			dfinaly[j+1]=0;
			ddfinaly[j+2]=0;
		}
		maxv=128;
		Imax=0;
		Idmark1=0;
		Idmax=0;
		Idmark2=0;
		Imidmark=0;
		Iddmax=0;
		return;
	}
			
    if((IFirst>0)&&(IFirst<20)){
		for (i=0;i<=IFirst-1;i++){
			rawdata[i]=rawdata[IFirst];
		}
	} else if(IFirst>=20){
		for(j=0; j<DAYSOFYEAR;j++){
			finaly[j]=128;
			dfinaly[j+1]=0;
			ddfinaly[j+2]=0;
		}
		maxv=128;
		Imax=0;
		Idmark1=0;
		Idmax=0;
		Idmark2=0;
		Imidmark=0;
		Iddmax=0;
		return;
	}
	
	if (ILast<n){
		for(i=ILast+1;i<=n;i++){
			rawdata[i]=rawdata[ILast];
		}
	}
	int effectiveN=0; //effective data number
	for (i=0;i<=n;i++){


		if (rawdata[i]!=128){
			effectiveN+=1;
		}
	}*/
	//int oldn=n;
	//n=effectiveN-1;//in order not to change old code
	x = NewVector(0, n);
    y = NewVector(0, n);
	//ddfinaly=NewVector(2,oldn);
	//effectiveN=-1;

	for(i=0;i<=n;i++){
			
//		if(rawdata[i]!=128){
//			effectiveN+=1;
			x[i]=xx[i];
			y[i]=rawdata[i];
		//}
	}


    Sm = NewSplineVector(0, n);
    B = NewBezierVector(0, n); 
	//L = NewVector(1,DAYSOFYEAR);
    
	maxy=0;
	
    for (i = 0; i <= n; i++)
      {
		if ( y[i]>maxy) maxy=y[i];
		Sm[i].x = x[i];
        Sm[i].xday=xxd[i];
   //     printf("%f\t",x[i]);
        Sm[i].y = y[i];
       // sigma[i] = 1;
      }


	lambda=LAMB;
       if ((lambda <= 0) || (lambda > 1))
         printf("\r    lambda must be in (0, 1]\n");
      
    
	 for(i=0;i<MM;i++){
		 SmoothingSpline(Sm, sigma, lambda, n);
		 SplineToBezier(Sm, B, n);
		 if (B[0].f0>maxy) B[0].f0=maxy;
		 if(B[0].f0>Sm[0].y+maxy*percent){
			 Sm[0].y=B[0].f0;
		 }
		 for (j = 0; j <n ; j++){
			 if (B[j].f1>maxy)
		        B[j].f1=maxy;
			 if (B[j].f2>maxy)
		        B[j].f2=maxy;
			 if (B[j].f3>maxy)
		        B[j].f3=maxy;
		 }
		 for (j = 0; j <n ; j++){
			 if(B[j].f3>(Sm[j+1].y+maxy*percent)){
				 yy[j+1]=1;
			 }
		 }
		 if (yy[n]==1){
			 Sm[n].y=B[n-1].f3;
		 }
		 for(j=0; j<n;j++){
			 if (yy[j+1]==1){
				 for(jj=j+2;jj<=n;jj++){
					 if (y[jj]!=1){
						 Sm[j+1].y=(Sm[j].y+Sm[jj].y)*.5;
						 break;
					 }
				 }
			 }
		 }
	 }

	SplineToPoints(Sm,finaly,n);
////////////////////////////////////////////Mar 25
	for(i=0;i<355;i++){
		finaly[i]=(finaly[i]>=0.)?finaly[i]:0.;
	}
	
	//for(i=0; i<3; i++){
		//finaly[i]=finaly[3];
	//}
	
	for(i=355;i<DAYSOFYEAR;i++){
		finaly[i]=finaly[354];
	}

		
	//finaly[0]=B[0].f0;
	/*finaly[0]=(B[0].f0>=0)?B[0].f0:0.;
	int mark=0;
	for(i=1;i<N;i++){
	
			j=mark;
			if((B[j].x3>(i-0.000001))&&(B[j].x3<(i+0.000001))){
			finaly[i]=(B[j].f3>=0)?B[j].f3:0.;
			//finaly[i]=B[j].f3;
			mark+=1;
			}
		
			else {
			finaly[i]=(B[j].f3-finaly[i-1])/(B[j].x3-(i-1))+finaly[i-1];
			finaly[i]=(finaly[i]>=0)?finaly[i]:0.;
			}
		
		
	}*/
///////////////////
	for(i=1;i<DAYSOFYEAR;i++){
		dfinaly[i]=finaly[i]-finaly[i-1];
	}
	for(i=2;i<DAYSOFYEAR;i++){
		ddfinaly[i]=dfinaly[i]-dfinaly[i-1];
	}
	int Imin;

	maxv=max(finaly,0,DAYSOFYEAR-1,Imax);
	
	double minv=min(finaly,Imax,DAYSOFYEAR-1,Imin);
	
	double midv=maxv*.5+minv*.5;
	double distance=9999.9;
	
	for(i=Imax;i<=Imin;i++){
		if((finaly[i]-midv)<distance){
			Imidmark=i;
		}
	}

	
	double dmaxv=max(dfinaly,1,Imax,Idmax);
	double ddmaxv=max(ddfinaly,2,Imax,Iddmax);

	if(Idmax>Imax){
		Idmax=0;
		Idmark1=0;
		Idmark2=0;
		
	}
	
	else{
		for(i=Idmax;i>0;i--){
			if (dfinaly[i]>=0.9*dmaxv){
				Idmark1=i;
			}

		}
		for(i=Idmax;i<=Imax;i++){
			if (dfinaly[i]>=0.9*dmaxv){
				Idmark2=i;
			}
		}
	}
	
	
	
	FreeIntVector(yy,0,n);
	FreeVector(x,0,n);
	FreeVector(y,0,n);
	FreeSplineVector(Sm,0,n);
	FreeBezierVector(B,0,n);
	//FreeVector(sigma,0,n);
	}
void main()
{
    char in_f_name[200],out_f_name[200],in_f_time[200];
       char monstring[N][8];  //,ystring[25][8];
       //char dates[N][200];
       FILE* in_file[N];
	   FILE* out_file[N];
       FILE* in_time;
       

       int n,*xd;
       double *rawdata,*x;
       double *finaly, *dfinaly,*ddfinaly,*sigma;
       int Imax =100, Idmark1, Idmax = 100, Idmark2,Imidmark, Iddmax; //**********************
       double maxv;
       double sum;
	   char ystring[28][8];
       //int tempnum;
	   int year;
	    int jday;
        
	   int i ;
char v[50];
FILE *f1,*f2;
 
unsigned char v1[200],v0[20];
 int num[15];      
  unsigned char *land;


	   n=N-1; 
       sigma = NewVector(0, n);
       xd=NewIntVector(0,n);
       x=NewVector(0,n);
	   rawdata=NewVector(0,n);
	   finaly=NewVector(0,DAYSOFYEAR-1);
	   dfinaly=NewVector(1,DAYSOFYEAR-1);
	   ddfinaly=NewVector(2,DAYSOFYEAR-1);

land=(unsigned char*) malloc (PIXN *sizeof( unsigned char));

in_time=fopen("Global_8km_landcover.raw","rb");

fread(&land[0],1,PIXN,in_time);
fclose(in_time);





      // sprintf(in_f_time,"%s","zfmtime_MODIS.txt");
   sprintf(in_f_time,"%s","zfmtime.txt"); 
       if((in_time=fopen(in_f_time,"r")) ==NULL )
       {
           printf("cannot open input time file\n");
           exit(0);
       }
	   char temp[20];

               
       for( i=0;i<N;i++){
           fscanf(in_time,"%d\t%s\n",&xd[i],temp);
		   x[i]=atof(temp);
		   //printf("%d\t%f\n",xd[i],x[i]);// for test
       }
       
     	
 for (year=1982;year<=1982;year++){//for (year=2008;year<=2010;year++){
	 
	 if(year%4!=0){
	 num[0]=1;   num[1]=16;    num[2]=32;   num[3]=47;
	 num[4]=60;  num[5]=75;    num[6]=91;   num[7]=106;
	 num[8]=121; num[9]=136;   num[10]=152; num[11]=167;
	 num[12]=182;num[13]=197;  num[14]=213; num[15]=228;
	 num[16]=244;num[17]=259;  num[18]=274; num[19]=289;
	 num[20]=305;num[21]=320;  num[22]=335; num[23]=350;
	 }


	 else{
     num[0]=1;   num[1]=16;    num[2]=32;   num[3]=47;
	 num[4]=60;  num[5]=75;    num[6]=91;   num[7]=106;
	 num[8]=121; num[9]=136;   num[10]=152; num[11]=167;
	 num[12]=182;num[13]=197;  num[14]=213; num[15]=228;
	 num[16]=244;num[17]=259;  num[18]=274; num[19]=289;
	 num[20]=305;num[21]=320;  num[22]=335; num[23]=350;
	 }



       for(i=0;i<N;i++){
           //  jday=i*8+1;

  jday=num[i];

		   	 printf("%d %d\n",year,jday);		 //sprintf(in_f_name,"%s%s%d%s%d%d",In_Dir,"\\LE_SMOOTH",year,"_proc\\Le_RSR_p1",year,jday);
		   /*
    if(jday<10)                   sprintf(in_f_name,"%d%s%d%s",year,"00",jday,"glai.raw");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
	else if(jday>=10 && jday<100) sprintf(in_f_name,"%d%s%d%s",year,"0",jday,"glai.raw");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
    else if(jday>100)             sprintf(in_f_name,"%d%d%s",  year,jday,"glai.raw");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
           */     

 
     if(jday<10)              
		sprintf(in_f_name,"E:\\LAI_test\\in\\%s%d%s%d%s","LAI_",year,"00",jday,".dat");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
	
	else if(jday>=10 && jday<100)
	     sprintf(in_f_name,"E:\\LAI_test\\in\\%s%d%s%d%s","LAI_",year,"0",jday,".dat");   
   
	else if(jday>100)       
	    sprintf(in_f_name,"E:\\LAI_test\\in\\%s%d%d%s","LAI_",year,jday,".dat");  
        							  

        							  
				   if((in_file[i]=fopen(in_f_name,"rb")) ==NULL )
                   {
                       printf("cannot open input file\n");
                       exit(0);
                   }
	   }

     printf("OKKKKKKKKKKK"); 
          
	   for(i=0;i<N;i++){		
         
           //jday=i*8+1;
 jday=num[i];

		   	 printf("%d %d\n",year,jday);	//sprintf(in_f_name,"%s%s%d%s%d%s",In_Dir,"\\Le_SR",year,"00",jday,".dat");	 
			                              //sprintf(out_f_name,"%s%s%d%s%d%s%d",In_Dir,"\\LE_SMOOTH",year,  "_proc_s\\Le_RSR_ps",year,"00",jday);
		   /*
    if(jday<10)                   sprintf(out_f_name,"S_%d%s%d%s",year,"00",jday,"glai.raw");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
	else if(jday>=10 && jday<100) sprintf(out_f_name,"S_%d%s%d%s",year,"0",jday,"glai.raw");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
    else if(jday>100)             sprintf(out_f_name,"S_%d%d%s",  year,jday,"glai.raw");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
             */         
		   
		  
    
	if(jday<10)              
		sprintf(out_f_name,"E:\\LAI_test\\out\\%s%d%s%d%s","LAI_smoothed_",year,"00",jday,".dat");  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.

	else if(jday>=10 && jday<100)
		sprintf(out_f_name,"E:\\LAI_test\\out\\%s%d%s%d%s","LAI_smoothed_",year,"0",jday,".dat");   

	else if(jday>100)       
		sprintf(out_f_name,"E:\\LAI_test\\out\\%s%d%d%s","LAI_smoothed_",year,jday,".dat");  	   
		   
		   
		   
		   if((out_file[i]=fopen(out_f_name,"wb")) ==NULL )
                   {
                       printf("cannot open output file\n");
                       exit(0);
                   }
          
     /////////////////////////////////////////////////////////////
	   }
       

	   for(int pixnumber=0;pixnumber<PIXN;pixnumber++){



            for(i=0; i<N; i++){
                //xd[i]=i*8+3;
                sigma[i]=1;
            }
            sum=0;


           // short abc;
            unsigned char abc;

			for(i=0;i<N;i++){
               // fread(&abc,sizeof(unsigned char ),1,in_file[i]);
		
				 fread(&abc,sizeof(unsigned char ),1,in_file[i]);
				
				 //fscanf(in_file[i],"%d",&abc);
				//if((abc==253)||(abc==254)||(abc==255)) abc=0;
 if(abc==100) rawdata[i]=0;
 else        rawdata[i]=(double)abc;

///				printf("%f\t",rawdata[i]);
                //tempnum=rawdata[i];
                //printf("%f\t",tempnum);
                sum+=rawdata[i];  //printf("\t%f\t",sum);        
			}

 
            if(sum>0.01){

				
                dataproc(rawdata,x,xd, finaly, dfinaly,ddfinaly, maxv, Imax, Idmark1, Idmax, Idmark2, Imidmark,Iddmax,sigma);
				
                newsigma(sigma,finaly,xd,n);
                dataproc(rawdata,x,xd,finaly, dfinaly,ddfinaly, maxv, Imax, Idmark1, Idmax, Idmark2, Imidmark,Iddmax,sigma);

            }
            else{
                for(i=0;i<365;i++){
                    finaly[i]=0.;
                }

            }
           unsigned char abc2;

			for(i=0;i<N;i++){//needed to be modified for 36 days
				//raw2[i]=raw[i];
				//fprintf(out_file[0],"%f\n",finaly[xd[i]-1]);//i to 0, after try change back
                abc2=(unsigned char )finaly[xd[i]-1];
 
                fwrite(&abc2,sizeof(unsigned char),1, out_file[i]);///////////////////////////////////////////////////////////
			}
	   


       
	 
	   }   //end the pixnumber

    

       for(i=0;i<N;i++){
		   fclose(in_file[i]);
       }

	   for(i=0;i<N;i++){
		   fclose(out_file[i]);
       }
 }  //end the year

/*
 printf("\n");
for(i=0;i<46;i++) {
jday=1+i*8;
year=2005;
if(jday<10)                       sprintf(out_f_name,"S_%d%s%d",year,"00",jday);  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
	else if(jday>=10 && jday<100) sprintf(out_f_name,"S_%d%s%d",year,"0",jday);  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
    else if(jday>100)             sprintf(out_f_name,"S_%d%d",  year,jday);  //ch.raw is the name of the input unsmoothed file for one day; for every day there is one separate directory.
f1=fopen(out_f_name,"rb");
fread(&v0[0],1,1,f1);
fclose(f1);
v1[i]=v0[0];
fclose(f1);
printf("%d %d  %d \n",i, v0[0], v1[i]);
}
 
f1=fopen("smoot.txt","wt");
for(i=0;i<46;i++) {
fprintf(f1,"%d\n",v1[i]); 

}
fclose(f1);
*/




	//return 0;
}

