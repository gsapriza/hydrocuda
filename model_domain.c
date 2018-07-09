/**************
* Model domain configurations
*
* Set of basic function to init, set, read of meteorological focing and update
* using c and cuda
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;

void init_domain(){
  // Initialize domain dimensions
  char caux[15];
  
  if (strcmp(options.domainModel,"gridcells") == 0){
    ini_sget(options.config, "ModelDomain", "nx", "%s", caux);
    domain.nx = atoi(caux);
    ini_sget(options.config, "ModelDomain", "ny", "%s", caux);
    domain.ny = atoi(caux);
    ini_sget(options.config, "ModelDomain", "dx", "%s", caux);
    domain.dx = atof(caux);
    ini_sget(options.config, "ModelDomain", "dy", "%s", caux);
    domain.dy = atof(caux);
    domain.ntgt = domain.nx*domain.ny;
  }
}
