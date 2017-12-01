#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define NUM_WORDS 8

void func12( uint64_t (*out)[12], uint64_t (*in)[12]  ) {

   printf( "%s() out is ", __func__ ); 
   for( int t = 0; t < 12; t++ ) {
      for( int w = 0; w < NUM_WORDS; w++ ) {
         out[w][t] = in[w][t] + 5;
         printf( "%lld ", out[w][t] ); 
      }  
   } 
   printf( "\n" ); 
}

void func4( uint64_t (*out)[4], uint64_t (*in)[4]  ) {

   printf( "%s() out is ", __func__ ); 
   for( int t = 0; t < 4; t++ ) {
      for( int w = 0; w < NUM_WORDS; w++ ) {
         out[w][t] = in[w][t] + 5;
         printf( "%lld ", out[w][t] ); 
      }  
   } 
   printf( "\n\n" ); 
}

int main() {

   uint64_t out12[NUM_WORDS][12];
   uint64_t out4[NUM_WORDS][4];
   uint64_t in12[NUM_WORDS][12];
   uint64_t in4[NUM_WORDS][4];
   
   gsl_rng *rng = gsl_rng_alloc( gsl_rng_taus );
   gsl_rng_set( rng, time( NULL ) );

   printf( "in12 is " ); 
   for( int t = 0; t < 12; t++ ) {
      for( int w = 0; w < NUM_WORDS; w++ ) {
         //in12[w][t] = gsl_rng_get( rng ); 
         in12[w][t] = t*NUM_WORDS + w; 
         printf( "%lld ", in12[w][t] ); 
      } 
   }
   printf( "\n\n" ); 
   printf( "in4 is " ); 
   for( int t = 0; t < 4; t++ ) {
      for( int w = 0; w < NUM_WORDS; w++ ) {
         //in4[w][t] = gsl_rng_get( rng ); 
         in4[w][t] = t*NUM_WORDS + w; 
         printf( "%lld ", in4[w][t] ); 
      } 
   }
   printf( "\n\n" ); 

   func12( out12, in12 );
   printf( "\n\n" ); 
   func4( out4, in4 );

}
