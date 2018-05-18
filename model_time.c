/**************
* HydroCuda model - model_time
*
* Set of basic function to init, set, read of timing options
* using c and cuda
****************/

#include <stdio.h>
#include <stdlib.h>
#include "hydrocuda.h"

extern model_option options;
extern model_domain domain;
extern model_time modeltime;

void init_times(){
  
  char caux[10]; // Auxiliar to load time options
  ini_sget(options.config, "TimeControl", "freq", "%s", modeltime.freq);
  ini_sget(options.config, "TimeControl", "nt", "%s", caux);
  modeltime.nt = atoi(caux);
  ini_sget(options.config, "TimeControl", "start_second", "%s", caux);
  modeltime.start_second = atoi(caux);
  ini_sget(options.config, "TimeControl", "start_min", "%s", caux);
  modeltime.start_min = atoi(caux);
  ini_sget(options.config, "TimeControl", "start_hour", "%s", caux);
  modeltime.start_hour = atoi(caux);
  ini_sget(options.config, "TimeControl", "start_day", "%s", caux);
  modeltime.start_day = atoi(caux);
  ini_sget(options.config, "TimeControl", "start_month", "%s", caux);
  modeltime.start_month = atoi(caux);
  ini_sget(options.config, "TimeControl", "start_year", "%s", caux);
  modeltime.start_year = atoi(caux);
  ini_sget(options.config, "TimeControl", "end_second", "%s", caux);
  modeltime.end_second = atoi(caux);
  ini_sget(options.config, "TimeControl", "end_min", "%s", caux);
  modeltime.end_min = atoi(caux);
  ini_sget(options.config, "TimeControl", "end_hour", "%s", caux);
  modeltime.end_hour = atoi(caux);
  ini_sget(options.config, "TimeControl", "end_day", "%s", caux);
  modeltime.end_day = atoi(caux);
  ini_sget(options.config, "TimeControl", "end_month", "%s", caux);
  modeltime.end_month = atoi(caux);
  ini_sget(options.config, "TimeControl", "end_year", "%s", caux);
  modeltime.end_year = atoi(caux);
  ini_sget(options.config, "TimeControl", "timestep", "%s", caux);
  modeltime.timestep = atoi(caux);
  //modeltime.ntblock = (12-n_estates*4*nx*ny)/(n_inflows*4*nx*ny);
}
