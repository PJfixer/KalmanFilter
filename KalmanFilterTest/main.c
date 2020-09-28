#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "../src/kalman_StateUpdate/kalman_state_update_eq.h"
#define PI 3.14159265358979323846

//PROTOTYPE
float sinewave(float indice, float Frequency, unsigned long N,double Te);
void PlotIMG(void);
void SignalToLogFile(float *signal,int Nbpoint,double Te, char * title);
double drand ( double low, double high );
//PROTOTYPE

double drand ( double low, double high )
{
    return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}


int main(int argc, char *argv[])
{
int N = 1024;
double Te = 512e-6;
double Fe =  1/Te ;
srand ( time ( NULL));


float noise = 0.0 ;
kalman_datastruct kalman_filter;
StateKalmanFilter_init(&kalman_filter,1.0,1.0,0.01);
    printf("Test d'impression Sinus en C avec GNUPLOT \n");

    float *buffer; //creation pointeur pour buffer signal
    buffer = malloc(N * sizeof(float));
    int i = 0 ;
    for(i = 0; i<N;i++)
    {
	  noise = (float) (drand(-1600.0,1600.0)/50.0);
      buffer[i] = (100 * sinewave(i,12.00,N,Te)) + noise;
	  printf("%f \n",noise);
    }
	
	 float *buffer_kalman; //creation pointeur pour buffer signal
     buffer_kalman = malloc(N * sizeof(float));
	
	
	for(i = 0; i<N;i++)
	{
		buffer_kalman[i] = StateKalmanFilter_updateEstimate(&kalman_filter,buffer[i]);
	}

   SignalToLogFile(buffer,N,Te,"orig.dat");
   SignalToLogFile(buffer_kalman,N,Te,"kalman.dat");
   PlotIMG();



    return 0;
}


float sinewave(float indice, float Frequency, unsigned long N,double Te)
{

	float Factor = Frequency  * 2.0 * PI*Te;
	return sin(Factor  * indice);
}


void PlotIMG(void)
{

    char * commandsForGnuplot[] = {"set title \"SIGNAL \"","set terminal png","set output 'data.png'", "set boxwidth 0.1 relative ","set style fill solid 1.0","plot 'signal.dat' using 1:2 with lines","exit"};
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;

    for (i=0; i < 7; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
    }

}

void SignalToLogFile(float *signal,int Nbpoint,double Te, char * title)
{
    int i = 0 ;
    FILE *f = fopen(title, "w"); if (f == NULL) {
    printf("Erreur ouverture fichier!\n");
    exit(1);
}
 fprintf(stdout,"Creation du fichier .dat \n");

       for (i = 1; i < Nbpoint; i++){
       fprintf(f,"%f %f \n ",Te*i,signal[i]); // ecriture dans brut.txt
      }
fclose(f);

}











