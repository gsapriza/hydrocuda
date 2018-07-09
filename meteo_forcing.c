/**************
* meteo_forcing
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
extern model_time modeltime;

void init_forcing(model_vars forcing){
  
  aux_ids *met_ids;
  if (strcmp(options.meteoModel, "Pp&Etp") == 0){
    forcing.nvars = 2; // Precip and pet
    // For loading forcing options
    met_ids = (aux_ids*) malloc(forcing.nvars * sizeof(aux_ids));
    strcpy(met_ids[0].ids,"pp"); // Precipitation
    strcpy(met_ids[1].ids,"etp"); // Potential evotranspiration
  }
  else if (strcmp(options.meteoModel, "Pp&Penman") == 0){
    forcing.nvars = 8; // Precip and variables to Penman pet calc
    met_ids = (aux_ids*) malloc(forcing.nvars * sizeof(aux_ids));
    int vtipe[modelvars.nvars];
  }
  // Allocate auxiliar
  aux_ids *met_ids_aux = (aux_ids*) malloc(forcing.nvars * sizeof(aux_ids));
  // Allocate meteo_info
  forcing.info = (vars_info*) malloc(forcing.nvars * sizeof(vars_info));
  for (int i = 0; i < forcing.nvars; i++){
    // Fill auxiliar
    strcpy(met_ids_aux[i].ids,met_ids[i].ids);
    // Read variables
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_units"), "%s", forcing.info[i].units);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_location"), "%s", forcing.info[i].location);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    // Variable known declaration
    strcpy(forcing.info[i].name,met_ids_aux[i].ids);
    forcing.info[i].indx = i;
    forcing.info[i].tipe = 4;
  }
}

void allocate_forcing(model_vars forcing){
  // Allocation and setting to zero
  // We shoud distingush between ntime block allocating,
  // All time steps or in each time step
  
  for (int i = 0; i < forcing.nvars; i++){
    forcing.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt * modeltime.nt);
  }
}

// void read_forcing(model_vars forcing){
//   // Read netvariables from location, setting default value if it's NULL
//   if (strcmp(forcing.info[i].location, "") == 0 ){
//     //set default value
//   }
//   else {
//     //read netcdf
//   }
// }

// void update_forcing(){
//
// }

void free_forcing(model_vars forcing){
  
  for (int i = 0; i < forcing.nvars; i++){
    free(forcing.info[i].vars);
  }

}
