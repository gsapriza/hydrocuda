/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
***************/

#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

// Reaf NetCDF files
void read_netcdf(model_vars modelvars, size_t start, size_t count, float *var){
  
  int nc_id, nc_error, var_id;
  int time_dim = count[0];
  //float var[time_dim][domain.nx][domain.ny];
  nc_error = nc_open(location, NC_NOWRITE, &nc_id);
  nc_error = nc_inq_varid(nc_id, name, &var_id);
  nc_error = nc_get_vara_float(nc_id, var_id, start, count, &var[0][0][0]);
}
