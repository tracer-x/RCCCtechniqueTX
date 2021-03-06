#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

// method ids
int m_isPowerOfTwo = 1;
int m_IntMath = 2;
int m_log10 = 3;
int m_checkedSubtract = 4;
int m_checkedMultiply = 5;
int m_log2 = 6;
int m_checkedAdd = 7;
int m_mod_1 = 8;
int m_mod_2 = 9;
int m_factorial_1 = 10;
int m_factorial_2 = 11;
 

int main() {

  int q,i=0;
  klee_make_symbolic(&q, sizeof(int), "q");
  int method_id;
    int this_state;
	klee_make_symbolic(&this_state, sizeof(int), "this_state");
  // variables
          int P1;
        int P2;
        int P3;
        int P4;
        int P5;
        int P6;
        int P7;
        int P8;
        int P9;
        int P10;
        int P11;
        int P12;
        int P13;
        int P14;
        int P15;
        int P16;
        int P17;
 
        int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
        int a11,a12,a13,a14,a15,a16,a17,a18,a19;

        klee_make_symbolic(&P1, sizeof(int), "P1");
        klee_make_symbolic(&P2, sizeof(int), "P2");
        klee_make_symbolic(&P3, sizeof(int), "P3");
        klee_make_symbolic(&P4, sizeof(int), "P4");
        klee_make_symbolic(&P5, sizeof(int), "P5");
        
        klee_make_symbolic(&P6, sizeof(int), "P6");
        klee_make_symbolic(&P7, sizeof(int), "P7");
        klee_make_symbolic(&P8, sizeof(int), "P8");
        klee_make_symbolic(&P9, sizeof(int), "P9");
        
        klee_make_symbolic(&P3, sizeof(int), "P10");
        klee_make_symbolic(&P4, sizeof(int), "P11");
        klee_make_symbolic(&P5, sizeof(int), "P12");
        
        klee_make_symbolic(&P6, sizeof(int), "P13");
        klee_make_symbolic(&P7, sizeof(int), "P14");
        klee_make_symbolic(&P8, sizeof(int), "P15");
        klee_make_symbolic(&P9, sizeof(int), "P16");
        klee_make_symbolic(&P9, sizeof(int), "P17");
        
         klee_make_symbolic(&a1, sizeof(int), "a1");
   klee_make_symbolic(&a2, sizeof(int), "a2");
   klee_make_symbolic(&a3, sizeof(int), "a2");
   klee_make_symbolic(&a4, sizeof(int), "a4");
   klee_make_symbolic(&a5, sizeof(int), "a5");
   
   
   klee_make_symbolic(&a6, sizeof(int), "a6");
   klee_make_symbolic(&a7, sizeof(int), "a7");
   klee_make_symbolic(&a8, sizeof(int), "a8");
   klee_make_symbolic(&a9, sizeof(int), "a9");
   klee_make_symbolic(&a10, sizeof(int), "a10");
   
   klee_make_symbolic(&a11, sizeof(int), "a11");
   klee_make_symbolic(&a12, sizeof(int), "a12");
   klee_make_symbolic(&a13, sizeof(int), "a13");
   klee_make_symbolic(&a14, sizeof(int), "a14");
   klee_make_symbolic(&a15, sizeof(int), "a15");
   
   klee_make_symbolic(&a16, sizeof(int), "a16");
   klee_make_symbolic(&a17, sizeof(int), "a17");
   klee_make_symbolic(&a18, sizeof(int), "a18");
    klee_make_symbolic(&a19, sizeof(int), "a19");

  while (1) {
  
       i++;
   printf("*******SANGHU%d**********",i);

    // parameters
 

 

        
        
    // states
        if (q == 0){      
                
                if((a1)){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }

          break;
        }
        if (q == 1){      
               
                if(a2){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
                
                if(a3){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
                
                if(a4){
                  // assume guard
                  if ( !((P1 >= 0) && (P2 > 0)) ){ 
                    // record method id
                    method_id = 9;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
               
                if(a5){
                  // assume guard
                  if ( (P1 < 0) ){ 
                    // record method id
                    method_id = 10;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }

          break;
        }
        if (q == 2){      
       
                if(a6){
                  // assume guard
                  if ( 1&& ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || 0) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
               
                if(a7){
                  // assume guard
                  if ( 1&& ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || 0)&& ((((P1 & (P1 - 1)) != 0) && (P1 > 0)) || 0) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
               
                if(a8){
                  // assume guard
                  if ( 1&& ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || 0)&& ((((P1 & (P1 - 1)) != 0) && (P1 > 0)) || 0)&& ((((P1 & (P1 - 1)) == 0) && (P1 <= 0)) || 0) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
              
                if(a9){
                  // assume guard
                  if ( 1&& ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || 0)&& ((((P1 & (P1 - 1)) != 0) && (P1 > 0)) || 0)&& ((((P1 & (P1 - 1)) == 0) && (P1 <= 0)) || 0)&& ((((P1 & (P1 - 1)) != 0) && (P1 <= 0)) || 0) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
                
                if(a10){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
                
                if(a11){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
                
                if(a12){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
               
                if(a13){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
                
                if(a14){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
               
                if(a15){
                  // assume guard
                  if ( ((P1 >= 0) && (P2 > 0)) ){ 
                    // record method id
                    method_id = 8;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
               
                if(a16){
                  // assume guard
                  if ( !((P1 >= 0) && (P2 > 0)) ){ 
                    // record method id
                    method_id = 9;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
               
                if(a17){
                  // assume guard
                  if ( (P1 < 0) ){ 
                    // record method id
                    method_id = 10;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  break;
                }
              
                if(a18){
                  // assume guard
                  if ( !(P1 < 0)&& (((P17 < 13) && (P17 >= 0)) || 0) ){ 
                    // record method id
                    method_id = 11;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }
              
                if(a19){
                  // assume guard
                  if ( !(P1 < 0)&& (((P17 < 13) && (P17 >= 0)) || 0)&& (((P17 >= 13) && (P17 >= 0)) || 0) ){ 
                    // record method id
                    method_id = 11;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  break;
                }

          break;
        }
   
break;
  } // end while

 

 ERROR: 
       printf("error"); 
 return 0;
}
