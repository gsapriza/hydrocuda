/**************
* HydroCuda model - model HVB
*
* Set of basic function to init, set, read of states options
* using c and cuda
****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

// Initialize parameter, states and flows
void init_hbv(model_vars modelvars){
  
//   char caux[15]; // Auxiliar to read integer

//     modelvars.nparams = 10;
//     modelvars.nstates = 3;
//     modelvars.nflows = 9;
    modelvars.nvars = 22; // HBV: 10 params + 3 states + 9 flow
    // For loading variables options
    aux_ids *var_ids = (aux_ids*) malloc(modelvars.nvars * sizeof(aux_ids));
    int vtipe[modelvars.nvars];
    //tipe variable: 1=Flux, 2=Param, 3=StateVariable
    // Parameters
    strcpy(var_ids[0].ids,"icf");   // Infiltration
    vtipe[0] = 2;
    strcpy(var_ids[1].ids,"fc");    // Feild capacity
    vtipe[1] = 2;
    strcpy(var_ids[2].ids,"beta");  // Seepage
    vtipe[2] = 2;
    strcpy(var_ids[3].ids,"lp");    // Real Evapotranspiration factor
    vtipe[3] = 2;
    strcpy(var_ids[4].ids,"perc");  // Maxumim percolation
    vtipe[4] = 2;
    strcpy(var_ids[5].ids,"cflx");  // Maximum capillar flux
    vtipe[5] = 2;
    strcpy(var_ids[6].ids,"uzl");   // Upper zone limit
    vtipe[6] = 2;
    strcpy(var_ids[7].ids,"kq");    // Quickflow constant
    vtipe[7] = 2;
    strcpy(var_ids[8].ids,"ki");    // Interflow constant
    vtipe[8] = 2;
    strcpy(var_ids[9].ids,"klz");   // Lower zone constant
    vtipe[9] = 2;
    // State variables
    strcpy(var_ids[10].ids,"sm");   // Soil moisture
    vtipe[10] = 3;
    strcpy(var_ids[11].ids,"vlz");  // Lower zone volume
    vtipe[11] = 3;
    strcpy(var_ids[12].ids,"vuz");  // Upper zone volume
    vtipe[12] = 3;
    // Internal flows
    strcpy(var_ids[13].ids,"qin");  // In flow
    vtipe[13] = 1;
    strcpy(var_ids[14].ids,"etr");  // Real Evapotranspiration
    vtipe[14] = 1;
    strcpy(var_ids[15].ids,"qdr");  // Drainage flow
    vtipe[15] = 1;
    strcpy(var_ids[16].ids,"inet"); // Net in flow
    vtipe[16] = 1;
    strcpy(var_ids[17].ids,"sp");   // Seepage flow
    vtipe[17] = 1;
    strcpy(var_ids[18].ids,"qcf");  // Captllar flow
    vtipe[18] = 1;
    strcpy(var_ids[19].ids,"qq");   // Quick flow
    vtipe[19] = 1;
    strcpy(var_ids[20].ids,"qi");   // Inter flow
    vtipe[20] = 1;
    strcpy(var_ids[21].ids,"qlz");  // Base flow
    vtipe[21] = 1;

  // Auxiliar
  aux_ids *var_ids_aux = (aux_ids*) malloc(modelvars.nvars * sizeof(aux_ids));
  // Allocate vars_info
  modelvars.info = (vars_info*) malloc(modelvars.nvars * sizeof(vars_info));
  for (int i = 0; i < modelvars.nvars; i++){
    // Fill auxiliar
    strcpy(var_ids_aux[i].ids,var_ids[i].ids);
    // Read variables
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_units"), "%s", modelvars.info[i].units);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    if (strcmp(modelvars.info[i].units, "") == 0 ){
      strcpy(modelvars.info[i].units, ""); //hacer esto??
    }
    ini_sget(options.config, "HydroModel", strcat(var_ids[i].ids,"_location"), "%s", modelvars.info[i].location);
    strcpy(var_ids[i].ids,var_ids_aux[i].ids);
    // Variable known declaration
    strcpy(modelvars.info[i].name,var_ids_aux[i].ids);
    modelvars.info[i].indx = i;
    modelvars.info[i].tipe = vtipe[i];
  }
}

void allocate_hbv(model_vars modelvars){
  // Allocate parametes, state and flows matrix
  for (int i = 0; i < modelvars.nvars; i++){
    modelvars.info[i].vars = (float*) malloc(sizeof(float) * domain.ntgt);
  }
  
}

// void read_hbv_netcdf(model_vars modelvars){
//   // Read netvariables from location, setting default value if it's NULL
//   if (strcmp(modelvars.info[i].location, "") == 0 ){
//     //set default value
//   }
//   else {
//     //read netcdf
//     int nc_id
//     error = nc_open(file_name, NC_NOWRITE, &nc_id);
//     error = nc_inq(nc_id, &ndims_in, &nvars_in, &ngatts_in, &unlimdimid_in);
//     error = nc_inq_varid(nc_id, LAT_NAME, &lat_varid);
//     error = nc_inq_varid(nc_id, LON_NAME, &lon_varid);
//     error = nc_get_var_float(ncid, lat_varid, &lats_in[0]);
//     error = nc_get_var_float(ncid, lon_varid, &lons_in[0]);
//     error = nc_inq_varid(ncid, PRES_NAME, &pres_varid);
//     error = nc_inq_varid(ncid, TEMP_NAME, &temp_varid);
//     error = nc_get_var_float(ncid, pres_varid, &pres_in[0][0]);
//     error = nc_get_var_float(ncid, temp_varid, &temp_in[0][0]);
//   }
// }

void free_hbv(model_vars modelvars){
  // Free parameters, states and flows
  for (int i = 0; i < modelvars.nvars; i++){
    free(modelvars.info[i].vars);
  }
  
}

void update_param_hbv(model_vars modelvars){
    
}

void compute_hbv(model_vars modelvars, model_vars forcing){
    
}

void compute_hbv_cuda(model_vars modelvars, model_vars forcing){
    
}


