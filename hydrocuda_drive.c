/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/

#include <stdio.h>
#include <stdlib.h>
#include "hydrocuda.h"

// Global variables
model_option options;
model_domain domain;
model_time modeltime;

int main (int argc, char *argv[])
{
  // Variable declraration
  model_vars forcing;
  model_vars modelvars;
  
  // Model Initialization
  if (argc < 2){
    printf("Usage : ./a.out <filename>");
    exit(0);
  }
  //  To read .ini files
  options.config = ini_load(argv[1]);
  // Initialize basic model options
  init_modeloptions();
  init_domain();
  init_times();
  
  // Init data series and model
  //if (strcmp(options.hydroModel,"HBV") == 0){
  //  init_hbv(modelvars);
  //  void allocate_hbv(&modelvars);
  //}
  init_hbv(&modelvars);
  init_forcing(&forcing);
  // Allocate information
  allocate_hbv(&modelvars);
  allocate_forcing(&forcing);
  update_hbv(&modelvars);
  // Aca es donde iteramos por bloques llamando a la f
  // evaluate_model()
  for(int itblock = 0; itblock < modeltime.nt, itblock++){
    update_forcing(&forcing, itblock);
    compute_hbv(&modelvars, &forcing);
    // Esta funcion tiene que ser la que se aplica cuda
    //compute_waterbalance();
    //compute_transit();
    // Leemos el siguient bloque de datos temporales
    //update_forcing();
  }
  // Free information
  ini_free(options.config);
  free_forcing(&forcing);
  free_hbv(&modelvars);
  return 0;
}
