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

void init_forcing(model_vars *forcing){
  
  aux_ids *met_ids;
  if (strcmp(options.meteoModel, "Pp&Etp") == 0){
    forcing->nvars = 2; // Precip and pet
    // For loading forcing options
    met_ids = (aux_ids*) malloc(forcing->nvars * sizeof(aux_ids));
    strcpy(met_ids[0].ids,"pp"); // Precipitation
    strcpy(met_ids[1].ids,"etp"); // Potential evotranspiration
  }
  else if (strcmp(options.meteoModel, "Pp&Penman") == 0){
    forcing->nvars = 8; // Precip and variables to Penman pet calc
    met_ids = (aux_ids*) malloc(forcing->nvars * sizeof(aux_ids));
  }
  // Allocate auxiliar
  aux_ids *met_ids_aux = (aux_ids*) malloc(forcing->nvars * sizeof(aux_ids));
  // Allocate meteo_info
  forcing->info = (vars_info*) malloc(forcing->nvars * sizeof(vars_info));
  for (int i = 0; i < forcing->nvars; i++){
    // Fill auxiliar
    strcpy(met_ids_aux[i].ids,met_ids[i].ids);
    // Read variables
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_units"), "%s", forcing->info[i].units);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    ini_sget(options.config, "MeteoModel", strcat(met_ids[i].ids,"_location"), "%s", forcing->info[i].location);
    strcpy(met_ids[i].ids,met_ids_aux[i].ids);
    // Variable known declaration
    strcpy(forcing->info[i].name,met_ids_aux[i].ids);
    forcing->info[i].indx = i;
    forcing->info[i].tipe = 4;
  }
}

void allocate_forcing(model_vars *forcing){
  // Allocation and setting to zero
  // We shoud distingush between ntime block allocating,
  // All time steps or in each time step
  
  for (int i = 0; i < forcing->nvars; i++){
    forcing->info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt);
  }
}

void read_forcing_netcdf(model_vars *forcing, size_t *start, size_t *count){
  // Read netcdf variables from location, setting default value if it's NULL
  int error;
  for (int i = 0; i < forcing->nvars; i++){
    if (strcmp(forcing->info[i].location, "") == 0 ){
      // Set default value
      for (int j = 0; j < domain.ntgt; j++){
        forcing->info[i].vars[j] = 0;
      }
    }
    else {
      // Read netcdf
      error = read_netcdf(forcing->info[i].location, forcing->info[i].name, start, count, &forcing->info[i].vars[0]);
      if (error > 0){
        printf("Error reading %s file \n", forcing->info[i].location);
        exit(1);
      }
    }
  }
}

void update_forcing(model_vars *forcing, int i){
  // Puts values into forcing matrixs
  size_t start[] = {i, 0, 0};
  size_t count[] = {1, domain.nx, domain.ny};
  for (int i = 0; i < forcing->nvars; i++){
    read_forcing_netcdf(forcing, start, count);
  }
}

void free_forcing(model_vars *forcing){
  // Free forcing matrixs
  for (int i = 0; i < forcing->nvars; i++){
    free(forcing->info[i].vars);
  }
}
