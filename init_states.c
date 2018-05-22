/**************
* HydroCuda model - model_time
*
* Set of basic function to init, set, read of states options
* using c and cuda
****************/

#include <stdio.h>
#include <stdlib.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

void init_states(model_vars modelvars){
  
  char caux[15]; //auxiliar to read integer
  if (options.hydroModel == "HBV"){
    modelvars.nstates = 3;
  }
  for ()
    ini_sget(options.config, "MeteoModel", "init_states", "%s", caux);
    params_states.init_states = atoi(caux);
  }
  
}
