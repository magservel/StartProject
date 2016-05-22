/*****
 *  Code for examination project in High Performance Computing and Programming
 * 
 *  funcs.c functions implementation file
 *
 *  Author: Marcus Holm
 *  Modified by: Elias Rudberg
 *
 **/

#include "funcs.h"

char spectralTypeArray[9] = {'O', 'B', 'A', 'F', 'G', 'K', 'M', 'L', 'T'};

void create_random_array(star_t * stars, int size)
{

  srand(time(NULL));

  int i;
  for(i= 0; i<size; i++) {
    stars[i].index        = rand();
    stars[i].spectralType = spectralTypeArray[rand()%9];
    stars[i].subType      = rand()%10;
    stars[i].designation  = sprintf("%c%d.%d", spectralType, subType, index);
    stars[i].magnitude    = float_rand_a_b(-10, 20);
    stars[i].pos.x        = float_rand_a_b(-1e5, 1e5);
    stars[i].pos.y        = float_rand_a_b(-1e5, 1e5);
    stars[i].pos.z        = float_rand_a_b(-3e3, 3e3);

  }
}

float_t float_rand_a_b (float_t a, float_t b){
    return ( rand()/(float_t)RAND_MAX ) * (b-a) + a
}
/*typedef struct star{
  int index;                   // counting index
  char spectralType;           // random: O, B, A, F, G, K, M, L, T
  unsigned short subType;      // random: 0-9
  float_t magnitude;           // random: (-10, +20)
  char designation[9]; 	       // sprintf("%c%d.%d", spectralType, subType, index)
  struct pos{
    float_t x, y, z;          // x & y random in (-1e5, 1e5), z random in (-3e3, 3e3)
  } position;
} star_t;
*/
void print_stars(star_t* array, int n)
{
  int i;
  printf("\nprint_stars, n = %d:\n", n);
  for(i = 0; i<n; i++)
    printf("%d ",array[i].index);
    //printf("%s ",array[i].spectralType);
    printf("%d ",array[i].subType);
    //printf("%s ",array[i].magnitude);
    //printf("%s ",array[i].designation);
    //printf("%s ",array[i].position);
  printf("\n");
}


float_t starfunc(star_t a, star_t b)
{
  unsigned short x = a.subType;
  unsigned short y = b.subType;
  return (x + y + x*y/0.6);
  //return sqrt(x + y + x*y/0.6);
}


void sort(star_t* array, int n) 
{
  
}

void fill_matrix(star_t * array, float_t **matrix, int size)
{
  
}

void print_matrix(float_t** theMatrix, int n)
{
  int i, j;
  printf("\nprint_matrix, n = %d:\n", n);
  for(i = 0 ; i < n; i++)
    {
      for(j = 0 ; j < n ; j++)
	printf("%.2f " , theMatrix[i][j]);
      putchar('\n');
    }
}

hist_param_t generate_histogram(float_t **matrix, int *histogram, int mat_size, int hist_size)
{
  
}

void display_histogram(int *histogram, hist_param_t histparams)
{
  printf("\ndisplay_histogram:\n");
  int i,j;
  for(i = 0; i < histparams.hist_size && histparams.bin_size*i < histparams.max; i++)
    {
      printf("%11.3e ", histparams.bin_size*i+histparams.min);
    }
  printf("%11.3e\n", histparams.max);
  for(j = 0; j < i; j++)
    {
      printf("%11d ", histogram[j]);
    }
  printf("\n");
}
