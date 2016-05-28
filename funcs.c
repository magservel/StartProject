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

/* Absolute value of the difference between a and b*/
float_t abs_a_b(float_t a, float_t b) {
  if (a - b > 0) return a-b;
  else return b-a;
}

/*Distance between two stars*/
float_t distance_two_stars(star_t star1, star_t star2){
  
  float_t position_star_1 = sqrt(star1.position.x*star1.position.x + star1.position.y*star1.position.y + star1.position.z*star1.position.z);
  float_t position_star_2 = sqrt(star2.position.x*star2.position.x + star2.position.y*star2.position.y + star2.position.z*star2.position.z);
  
  return abs_a_b(position_star_1, position_star_2);
}

/*Distance of a star from the origin*/
float_t distance_origin(star_t star) {

  return sqrt(star.position.x*star.position.x + star.position.y*star.position.y + star.position.z*star.position.z);
}

/*Return a random float number between a and b*/
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
    printf("distance %f\n", distance_origin(array[i]));    
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


/*void swap_star(star_t* array, int i, int j) {

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
}*/

/*void swap_pointers(star_t** star1, star_t** star2) {

  star_t* tmp = (star_t*)malloc(sizeof(star_t));

  tmp = star1;
  star1 = star2;
  star2 = tmp;
}*/

/*void sort(star_t* array, int n) 
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
        //swap_pointers(&(array + i), &(array+j)); 
        //swap_star(array, i, j)     
      }  
    }
  }
}*/

void copy_star(star_t* star1, star_t* star2) {
    star1->index        = star2->index;
    star1->spectralType = star2->spectralType;
    star1->subType      = star2->subType;
    sprintf(star1->designation, "%c%d.%d", star1->spectralType, star1->subType, star1->index);
    star1->magnitude    = star2->magnitude;
    star1->position.x   = star2->position.x ;
    star1->position.y   = star2->position.y;
    star1->position.z   = star2->position.z ;
}

void merge_sort(star_t* array, int n) {
  if(n != 1) {
    int n1 = n / 2;
    int n2 = n - n1;
    // Allocate new lists
    star_t* list = (star_t*)malloc((n1+n2)*sizeof(star_t));
    star_t* list1 = list;
    star_t* list2 = list+ n1;
    int i;
    for(i = 0; i < n1; i++)
      copy_star(list1+i, array+i);
    for(i = 0; i < n2; i++)
      copy_star(list2+i, array+n1+i);
    // Sort list1 and list2
    merge_sort(list1, n1);
    merge_sort(list2, n2);
    // Merge!
    int i1 = 0;
    int i2 = 0;
    i = 0;
    while(i1 < n1 && i2 < n2) {
      if(distance_origin(list1[i1]) < distance_origin(list2[i2])) {
        copy_star(array+i, list1+i1);
        i1++;
      }
      else {
        copy_star(array+i, list2+i2);
        i2++;
      }
      i++;
    }
    while(i1 < n1) {
      copy_star(array+i, list1+i1);
        i1++;
        i++;
    }
    while(i2 < n2) {
      copy_star(array+i, list2+i2);
      i2++;
      i++;
    }
    free(list);
  }
  return;
}

void fill_matrix(star_t * array, float_t **matrix, int size)
{
  int i, j;
  
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++) {
      matrix[i][j] = distance_two_stars(array[i], array[j]) + starfunc(array[i], array[j]); 
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
  int i, j, cpt, sum;
  float_t min = FLT_MAX, max = 0, step;
  printf("\nmax 1 %f\n", max);
  float_t** vonNeumann = (float_t**)malloc(mat_size * sizeof(float_t*));
  for(i=0; i<mat_size; i++) {
    vonNeumann[i] = (float_t*)malloc(mat_size * sizeof(float_t));
  } 
//    Fill vonNeumann matrix
  for(i=0; i<mat_size; i++) {
    for(j=0; j<mat_size; j++) {
      cpt = 0;      
      sum = 0;
      if(i!=0) {
        sum += abs_a_b(matrix[i][j], matrix[i-1][j]);
        cpt++;
      }
      if(j!=0) {
        sum += abs_a_b(matrix[i][j], matrix[i][j-1]);
        cpt++;
      }
      if(i!=(mat_size-1)) {
        sum += abs_a_b(matrix[i][j], matrix[i+1][j]);
        cpt++;
      }
      if(j!=(mat_size-1)) {
        sum += abs_a_b(matrix[i][j], matrix[i][j+1]);
        cpt++;
      }
      vonNeumann[i][j] = sum/cpt;
    }
  }

//    Get min et max
  for(i=0; i<mat_size; i++) {
    for(j=0; j<mat_size; j++) {
      if (matrix[i][j] > max) max = matrix[i][j];
      if (matrix[i][j] < min) min = matrix[i][j];
    }
  }
//    printf("max 2 %f\n", max);
//    printf("int max = %d\n", (int)max);

//    Fill histogram  
  step = (max-min)/hist_size;
//  printf("step %f\n", step);
  for(i=0; i<mat_size; i++) {
    for(j=0; j<mat_size; j++) {
      cpt = (int)((matrix[i][j] - min)/step);
      histogram[cpt]++;
    }
  }
  
  hist_param_t hist_param;
  hist_param.hist_size = hist_size;
  hist_param.min = min;
  hist_param.max = max;
  hist_param.bin_size = step;

  return hist_param;
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
