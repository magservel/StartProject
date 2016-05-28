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
    star_t* list2 = list + n1;
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
    for(j=0; j<=i; j++) {
      matrix[i][j] = distance_two_stars(array[i], array[j]) + starfunc(array[i], array[j]); 
    }
  }
  for(i=1; i<size; i++) {
    for(j=i; j<size; j++) {
      matrix[i][j] = matrix[j][i];
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
  //printf("\nmax 1 %f\n", max);
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
/*  int size = mat_size;
//    Fill the four corner
//      up-left
  sum =  abs_a_b(matrix[0][0], matrix[1][0]);
  sum +=  abs_a_b(matrix[0][0], matrix[0][1]);      
  vonNeumann[0][0] = sum/2;

//      up-right
  sum =  abs_a_b(matrix[0][size-1], matrix[1][size-1]);
  sum +=  abs_a_b(matrix[0][size-1], matrix[0][size-2]);      
  vonNeumann[0][size-1] = sum/2;

//      down-left
  sum =  abs_a_b(matrix[size-1][0], matrix[size-2][0]);
  sum +=  abs_a_b(matrix[size-1][0], matrix[size-1][1]);      
  vonNeumann[size-1][0] = sum/2;

//      down-right
  sum =  abs_a_b(matrix[size-1][size-1], matrix[size-2][size-1]);
  sum +=  abs_a_b(matrix[size-1][size-1], matrix[size-1][size-2]);      
  vonNeumann[size-1][size-1] = sum/2;


//    Fill the border
//      up
  cpt=3;  
  //sum=0;  
  i=0;
  for(j=1; j<size-1; j++) {
    sum =  abs_a_b(matrix[i][j], matrix[i][j-1]);
    sum += abs_a_b(matrix[i][j], matrix[i+1][j]);
    sum +=  abs_a_b(matrix[i][j], matrix[i][j+1]);     
    vonNeumann[i][j] = sum/cpt;
  } 
//      down
    i=size-1;
  for(j=1; j<size-1; j++) {
    sum =  abs_a_b(matrix[i][j], matrix[i][j-1]);
    sum += abs_a_b(matrix[i][j], matrix[i-1][j]);
    sum +=  abs_a_b(matrix[i][j], matrix[i][j+1]);     
    vonNeumann[i][j] = sum/cpt;
  } 
//      left
    j=0;
  for(i=1; i<size-1; i++) {
    sum =  abs_a_b(matrix[i][j], matrix[i-1][j]);
    sum += abs_a_b(matrix[i][j], matrix[i][j+1]);
    sum +=  abs_a_b(matrix[i][j], matrix[i+1][j]);     
    vonNeumann[i][j] = sum/cpt;
  } 
//      right
    j=size-1;
  for(i=1; i<size-1; i++) {
    sum =  abs_a_b(matrix[i][j], matrix[i-1][j]);
    sum += abs_a_b(matrix[i][j], matrix[i][j-1]);
    sum +=  abs_a_b(matrix[i][j], matrix[i+1][j]);     
    vonNeumann[i][j] = sum/cpt;
  } 

//    Fill the rest
  cpt = 4;
  for(i=1; i<mat_size - 1; i++) {
    for(j=1; j<mat_size -1 ; j++) {    
      sum = abs_a_b(matrix[i][j], matrix[i-1][j]);     
      sum += abs_a_b(matrix[i][j], matrix[i][j-1]);   
      sum += abs_a_b(matrix[i][j], matrix[i+1][j]);     
      sum += abs_a_b(matrix[i][j], matrix[i][j+1]);
      
      vonNeumann[i][j] = sum/cpt;
    }
  }
*/
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
