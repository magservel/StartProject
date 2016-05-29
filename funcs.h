/*****
 *  Code for examination project in High Performance Computing and Programming
 * 
 *  funcs.h functions header file
 *
 *  Author: Marcus Holm
 *  Modified by: Elias Rudberg
 *
 **/

#ifndef _FUNCS_H
#define _FUNCS_H

#include <stdlib.h>
#include <time.h>
//#include <math.h>
#include "common.h"



//extern float_t abs_a_b(float_t a, float_t b);//__attribute__((const));
float_t distance_two_stars(star_t star1, star_t star2)__attribute__((const));
float_t distance_origin(star_t star)__attribute__((const));
float_t float_rand_a_b (float_t a, float_t b);


void create_random_array(star_t * array, int size);
void merge_sort(star_t* array, int n);
void print_stars(star_t* array, int n);
void copy_star(star_t* restrict star1, star_t* restrict star2);

void fill_matrix( star_t * restrict array, float_t ** restrict matrix, int size);
void print_matrix(float_t** matrix, int n);

hist_param_t generate_histogram(float_t ** restrict matrix, int * restrict histogram , int mat_size, int hist_size);

void display_histogram(int *histogram, hist_param_t histparams);

#endif
