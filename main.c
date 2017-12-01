#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define BUF_FACTOR 4
#define NUM_WORDS 8

void func12( uint64_t (*out)[12], uint64_t (*in)[12]  ) {

   printf( "%s() out is ", __func__ ); 
   for( int t = 0; t < 12; t++ ) {
      for( int w = 0; w < NUM_WORDS; w++ ) {
         out[w][t] = in[w][t] + 5;
         printf( "%lu ", out[w][t] ); 
      }  
   } 
   printf( "\n" ); 
}

void func4( uint64_t (*out)[4], uint64_t (*in)[4]  ) {

   printf( "%s() out is ", __func__ ); 
   for( int t = 0; t < 4; t++ ) {
      for( int w = 0; w < NUM_WORDS; w++ ) {
         out[w][t] = in[w][t] + 10;
         printf( "%lu ", out[w][t] ); 
      }  
   } 
   printf( "\n\n" ); 
}

int main() {
   uint64_t buf_for_func12[NUM_WORDS*12*BUF_FACTOR];

   uint64_t t_out12[NUM_WORDS][12];
   uint64_t t_out4[NUM_WORDS][4];
   
   uint64_t t_in12[NUM_WORDS][12];
   uint64_t t_in4[NUM_WORDS][4];
   
   gsl_rng *rng = gsl_rng_alloc( gsl_rng_taus );
   gsl_rng_set( rng, time( NULL ) );

   printf( "buf_for_func12 is " ); 
   for( uint64_t i = 0; i < ( NUM_WORDS*12*BUF_FACTOR ); i++ ) {
      buf_for_func12[i] = i;
      printf("%lu ", buf_for_func12[i]);  
   }
   printf( "\n\n" ); 

   int b12_index = 0;
   int func_ratio = 12/4;
   for( int i=0; i < BUF_FACTOR; i++ ) {

      printf( "loop %d t_in12 is ", i ); 
      for( int t = 0; t < 12; t++ ) {
         for( int w = 0; w < NUM_WORDS; w++ ) {
            t_in12[w][t] = buf_for_func12[b12_index++]; 
            printf( "%lu ", t_in12[w][t] );
         } 
      }
      printf( "\n\n" ); 
      
      func12( t_out12, t_in12 );
      printf( "\n\n" ); 

      for(int j=0; j < func_ratio; j++) {
         
         printf( "\tinner loop %d for loop %d t_in4 is ", j, i ); 
         for( int t = 0; t < 4; t++ ) {
            for( int w = 0; w < NUM_WORDS; w++ ) {
               t_in4[w][t] = t_out12[w][j*4 + t]; 
               printf( "%lu ", t_in4[w][t] );
            } 
         }
         printf( "\n\n" );          

         func4( t_out4, t_in4 );
      } // end of for  (int j=0; j < func_ratio; j++) 
   }  // for( int i=0; i < BUF_FACTOR; i++ )

}
