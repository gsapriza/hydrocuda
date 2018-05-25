
/**************
* HydroCuda model
*
* Set of auxiliar functions simulate hydrological models response
* using c and cuda
***************/

#include <stdio.h>
#include <stdlib.h>
#include "hydrocuda.h"

// extern model_option options;
// extern model_domain domain;
// extern model_time modeltime;

// Initialize parameter, states and flows
void getindx(model_vars mv, char *c){
  for (int i = 0; i < mv.nvars ; i++){
    if (c == mv.name){
      break;
    }
  }
  return i;
}
