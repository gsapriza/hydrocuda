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

// Initialize parameter, states and flows
void init_psf(model_vars modelvars){
  
  char caux[15]; // Auxiliar to read integer
  if (options.hydroModel == "HBV"){
//     modelvars.nparams = 10;
//     modelvars.nstates = 3;
//     modelvars.nflows = 9;
    modelvars.nvars = 22; // HBV: 10 params + 3 states + 9 flow
    // For loading variables options
    aux_ids *var_ids = (aux_ids*) malloc(modelvars.nvars * sizeof(aux_ids));
    // Parameters
    strcpy(var_ids[0].ids,"icf");   // Infiltration
    strcpy(var_ids[1].ids,"fc");    // Feild capacity
    strcpy(var_ids[2].ids,"beta");  // Seepage
    strcpy(var_ids[3].ids,"lp");    // Real Evapotranspiration factor
    strcpy(var_ids[4].ids,"perc");  // Maxumim percolation
    strcpy(var_ids[5].ids,"cflx");  // Maximum capillar flux
    strcpy(var_ids[6].ids,"uzl");   // Upper zone limit
    strcpy(var_ids[7].ids,"kq");    // Quickflow constant
    strcpy(var_ids[8].ids,"ki");    // Interflow constant
    strcpy(var_ids[9].ids,"klz");   // Lower zone constant
    // State variables
    strcpy(var_ids[10].ids,"sm");   // Soil moisture
    strcpy(var_ids[11].ids,"vlz");  // Lower zone volume
    strcpy(var_ids[12].ids,"vuz");  // Upper zone volume
    // Internal flows
    strcpy(var_ids[13].ids,"qin");  // In flow
    strcpy(var_ids[14].ids,"etr");  // Real Evapotranspiration
    strcpy(var_ids[15].ids,"qdr");  // Drainage flow
    strcpy(var_ids[16].ids,"inet"); // Net in flow
    strcpy(var_ids[17].ids,"sp");   // Seepage flow
    strcpy(var_ids[18].ids,"qcf");  // Captllar flow
    strcpy(var_ids[19].ids,"qq");   // Quick flow
    strcpy(var_ids[20].ids,"qi");   // Inter flow
    strcpy(var_ids[21].ids,"qlz");  // Base flow
  }
  else if (options.hydroModel == "Temez"){
    modelvars.nvars = 12; // Temez: 3 params + 2 states + 7 flows
  }
  // Auxiliar
  aux_ids *var_ids_aux = (aux_ids*) malloc(forcing.nmeteo * sizeof(aux_ids));
  // Allocate vars_info
  modelvars.info = (vars_info*) malloc(modelvars.nvars * sizeof(vars_info));
  for (int i = 0; i < modelvars.nvars; i++){
    // Fill auxiliar
    strcpy(var_ids_aux[i].ids,met_ids[i].ids);
    // Read variables
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_units"), "%s", modelvars.info[i].units);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_name"), "%s", modelvars.info[i].name);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_longname"), "%s", modelvars.info[i].longname);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
  }
  
}

void allocate_psf(model_vars modelvars){
//   // Flows have different shape than parameters and states
//   int nflows;
//   if (options.hydroModel == "HBV"){
//     nflows = 1;
//   }
//   else if (options.hydroModel == "Temez"){
//     nflowz = 2;
//   }
  // Allocate parametes, state and flows matrix
  for (int i = 0; i < modelvars.nvars; i++){
    modelvars.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt);
  }
  
}

void free_psf(model_vars modelvars){
  // Free parameters, states and flows
  for (int i = 0; i < modelvars.nvars; i++){
    free(modelvars.info[i].vars);
  }
  
}
