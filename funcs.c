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

float_t distance_two_stars(star_t star1, star_t star2){
  
  float_t position_star_1 = sqrt(star1.position.x*star1.position.x + star1.position.y*star1.position.y + star1.position.z*star1.position.z);
  float_t position_star_2 = sqrt(star2.position.x*star2.position.x + star2.position.y*star2.position.y + star2.position.z*star2.position.z);
  
  if( position_star_1 > position_star_2)
    return position_star_1 - position_star_2;
  else 
    return position_star_2 - position_star_1;
}

float_t float_rand_a_b (float_t a, float_t b){
    return ( (float_t)rand()/(float_t)RAND_MAX ) * (b-a) + a;
}

void create_random_array(star_t * stars, int size)
{

  srand(time(NULL));

  int i;
  for(i= 0; i<size; i++) {
    stars[i].index        = rand()%10;
    stars[i].spectralType = spectralTypeArray[rand()%9];
    stars[i].subType      = rand()%10;
    sprintf(stars[i].designation, "%c%d.%d", stars[i].spectralType, stars[i].subType, stars[i].index);
    stars[i].magnitude    = float_rand_a_b(-10, 20);
    stars[i].position.x   = float_rand_a_b(-1e5, 1e5);
    stars[i].position.y   = float_rand_a_b(-1e5, 1e5);
    stars[i].position.z   = float_rand_a_b(-3e3, 3e3);

  }
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
  for(i = 0; i<n; i++) {
    //printf("%d ",array[i].index);
    //printf("spectral Type %d ",array[i].spectralType);
    //printf("%d ",array[i].subType);
    //printf("%f ",array[i].magnitude);
    printf("designation %d %s \n", i, array[i].designation);
    //printf("distance %f\n", distance_two_stars(array[i]));    
    //printf("position x %d %f \n", i, array[i].position.x);
    //printf("position y %d %f \n", i, array[i].position.y);
    //printf("position z %d %f \n", i, array[i].position.z);
    printf("\n");
  }
}


float_t starfunc(star_t a, star_t b)
{
  unsigned short x = a.subType;
  unsigned short y = b.subType;
  return sqrt(x + y + x*y/0.6);
}


void swap_star(star_t* array, int i, int j) {

  int l;
  star_t tmp;

  tmp.index = array[i].index;
  array[i].index = array[j].index;
  array[j].index = tmp.index;

  tmp.spectralType = array[i].spectralType;
  array[i].spectralType = array[j].spectralType;
  array[j].spectralType = tmp.spectralType;

  tmp.subType = array[i].subType;
  array[i].subType = array[j].subType;
  array[j].subType = tmp.subType;

  tmp.index = array[i].magnitude;
  array[i].magnitude = array[j].magnitude;
  array[j].magnitude = tmp.magnitude;

  for(l=0; l<9; l++) {
    tmp.designation[l] = array[i].designation[l];
    array[i].designation[l] = array[j].designation[l];
    array[j].designation[l] = tmp.designation[l];
  }
  
  tmp.position.x = array[i].position.x;
  array[i].position.x = array[j].position.x;
  array[j].position.x = tmp.position.x;

  tmp.position.y = array[i].position.y;
  array[i].position.y = array[j].position.y;
  array[j].position.y = tmp.position.y;

  tmp.position.z = array[i].position.z;
  array[i].position.z = array[j].position.z;
  array[j].position.z = tmp.position.z;
}

void sort(star_t* array, int n) 
{
  int i, j;
  star_t* tmp;
  star_t origin;
  origin.position.x = 0.00;
  origin.position.y = 0.00;
  origin.position.z = 0.00;

  for(i= 0; i<n; i++) {
    for(j= i +1; j<n; j++) {
      if(distance_two_stars(array[i], origin) < distance_two_stars(array[j], origin)) {
        swap_star(array, i, j);        
      }  
    }
  }
}

void fill_matrix(star_t * array, float_t **matrix, int size)
{
  int i, j;
  
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++) {
      matrix[i][j] = distance_two_stars(array[i], array[j]) + starfunc(array[i], array[j]); 
      //matrix[i][j] = 0.00;    
    }
  }
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
