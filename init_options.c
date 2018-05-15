/**************
* Function to init option model
* The struct defined for model option are initialized
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/
#include "hydrocuda.h"


void init_modeloptions(){

  // optns.domainModel =  'gridcells';
  // optns.meteoModel  = 'Pp&Ev';
  // optns.istimeblock = 1;
  ini_sget(options.config, "ModelDomain", "support_type", "%s", options.domainModel);
  ini_sget(options.config, "MeteoModel", "forcing_type", "%s",  options.meteoModel);
  char caux[15];
  ini_sget(options.config, "TimeControl", "isblock", "%s", caux);
  options.istimeblock = atoi(caux); //char to int

}
