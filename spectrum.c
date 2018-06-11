#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_POINTS 13
#define NUM_PARAMETERS 6

double f[NUM_POINTS] = { 1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1. };

void calculate_fs(int n, double *f, double *beta)
{
  register int i;
  double max = 0.0;
  
  f[0]  = beta[0]*39.2;
  f[1]  = beta[0]*21.3 + beta[1]*39.2;
  f[2]  = beta[0]*100. + beta[1]*21.3 + beta[2]*39.2;
  f[3]  = beta[0]*52.1 + beta[1]*100. + beta[2]*21.3 + beta[3]*39.2;
  f[4]  = beta[0]*86.1 + beta[1]*52.1 + beta[2]*100. + beta[3]*21.3 + beta[4]*39.2;
  f[5]  = beta[0]*41.5 + beta[1]*86.1 + beta[2]*52.1 + beta[3]*100. + beta[4]*21.3 + beta[5]*39.2;
  f[6]  = beta[0]*28.1 + beta[1]*41.5 + beta[2]*86.1 + beta[3]*52.1 + beta[4]*100. + beta[5]*21.3;
  f[7]  = beta[0]*11.1 + beta[1]*28.1 + beta[2]*41.5 + beta[3]*86.1 + beta[4]*52.1 + beta[5]*100;
  f[8]  = beta[0]*2.9  + beta[1]*11.1 + beta[2]*28.1 + beta[3]*41.5 + beta[4]*86.1 + beta[5]*52.1;
  f[9]  = beta[0]*0.5  + beta[1]*2.9  + beta[2]*11.1 + beta[3]*28.1 + beta[4]*41.5 + beta[5]*86.1;
  f[10] =                beta[1]*0.5  + beta[2]*2.9  + beta[3]*11.1 + beta[4]*28.1 + beta[5]*41.5;
  f[11] =                               beta[2]*0.5  + beta[3]*2.9  + beta[4]*11.1 + beta[5]*28.1;
  f[12] =                                              beta[3]*0.5  + beta[4]*2.9  + beta[5]*11.1;

  for(i = 0; i < n; i++)
    if(f[i] > max)
      max = f[i];

  for(i = 0; i < n; i++) {
    f[i] /= max / 100.;
  }
    
}


double sum_of_squares(int n, double *y, double *f)
{
  register int i;
  double ret;

  for(i = 0, ret = 0.0; i < n; i++)
    ret += (y[i]-f[i])*(y[i]-f[i]);
    
  return ret;
}

int main(int argc, char *argv[])
{
  double y[NUM_POINTS] = {13.63636364,17.27272727,56.36363636,32.72727273,100,47.27272727,75.45454545,47.27272727,45.45454545,20.90909091,9.090909091,5.454545455,2.727272727};
  double beta[NUM_PARAMETERS] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  int i, j, k, l, m, n;
  double s, min = INFINITY;

  double *f = malloc(NUM_POINTS * sizeof *f);
  
  for(i = 0; i < 10; i++)
	  for(j = 0; j < 10; j++)
		  for(k = 0; k < 10; k++)
			  for(l = 0; l < 10; l++)
				  for(m = 0; m < 10; m++)
					  for(n = 0; n < 10; n++) {
						  beta[0] = n*0.1;
						  beta[1] = m*0.1;
						  beta[2] = l*0.1;
						  beta[3] = k*0.1;
						  beta[4] = j*0.1;
						  beta[5] = i*0.1;
							  
						  calculate_fs(NUM_POINTS, f, beta);
						  s = sum_of_squares(15, y, f);
						  if(s < min) {
							  min = s;
							  printf("Minimum X^2=%f beta=%f %f %f %f %f %f\n", min, beta[0], beta[1], beta[2], beta[3], beta[4], beta[5]);
						  }
					  }

  //printf("%f\n", s);

  free(f);
}
