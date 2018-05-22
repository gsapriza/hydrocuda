/**************
* Function to init option model
* The struct defined for model option are initialized
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/

#include <stdlib.h>
#include "hydrocuda.h"

void init_modeloptions(){
  
  extern model_option options; //call options decleared in main
  // optns.model =  'HBV';
  // optns.domainModel =  'gridcells';
  // optns.meteoModel  = 'Pp&Ev';
  // optns.istimeblock = 1;
  ini_sget(options.config, "Model", "model", "%s", options.model);
  ini_sget(options.config, "ModelDomain", "support_type", "%s", options.domainModel);
  ini_sget(options.config, "MeteoModel", "forcing_type", "%s",  options.meteoModel);
  char caux[15]; //auxiliar to read integer
  ini_sget(options.config, "TimeControl", "isblock", "%s", caux);
  options.istimeblock = atoi(caux); //char to int
  
}
