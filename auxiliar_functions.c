
/**************
* HydroCuda model
*
* Set of auxiliar functions simulate hydrological models response
* using c and cuda
***************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

// extern model_option options;
// extern model_domain domain;
// extern model_time modeltime;

// Get index of different variables
int getindx(model_vars mv, char *c){
  int i;
  for ( i = 0; i < mv.nvars; i++){
    if (strcmp( c, mv.info[i].name) == 0){
      i = mv.info[i].indx;
      break;
    }
  }
  return i;
}
