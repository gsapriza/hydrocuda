/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
*******************/

#include "ini.h"
// General Program Options

typedef struct {
  struct ini_t  *config;
  char  domainModel[8];
  char  meteoModel[5];
  int  istimeblock;
} model_option;

// General Model domain discretization
typedef struct{
  int   ntgt;    // number of unique space domains in case of gridcells = nx*ny
  int   nx;      // number of columns
  int   ny;      // number of rows
  float dx;      // Space discretization x direction
  float dy;      // Space discretization y direction
} model_domain;


// Model time discretization
typedef struct{
    char freq;         // Time frequency
    int nt;            // Total number of time steps
    int start_second;  // second start time
    int start_min;     // minutes start time
    int start_hour;    // hour start time
    int start_day;     // day start time
    int start_month;   // month start time
    int start_year;    // year start time
    int end_second;    // second end time
    int end_min;       // minutes end time
    int end_hour;      // hour end time
    int end_day;       // day end time
    int end_month;     // month end time
    int end_year;      // year end time
    int timestep;      // time step in seconds
    int ntblock;       // number of block time
    int *datetime;   // all dates time
} model_time;

//We define model topology
typedef struct{
  float area; // Area of each grid cell
  int   *ldd;  // Directions
} model_topology;
// Parameter definition for hbv
// Model class acá agregamos lo de las clasess de C++
typedef struct {
    float *field_capacity;
    float *kquick;
} param_hbv;

typedef struct {
  float *soilmoist;
  float *gw1;
  float *gw2;
} state_hbv;

typedef struct {
  float *qsurf; // Surface runoff generation
  float *qintf; // Inferflow runoff generation
  float *qbase; //
} flux_hbv;

typedef struct{
  char units[15];
  char name[20];
  char longname[40];
  float *meteo;
} meteo_info;

typedef struct {
  int    nmeteo;    // Number of meteorological variables to be used
  meteo_info   *info; // Variables id to be initialized
  //float *precip; // Precipitation
  //float *pet; // Potential evapotranspiration
} meteo_forcing;

typedef struct {
  char mids[30]; //ids to get meteo info
} meteo_ids;


void init_modeloptions();
void init_domain();
//Function declaration asociated with meteorological forcing
void init_forcing(meteo_forcing *meteo);
void allocate_forcing(meteo_forcing *meteo);
// void read_forcing_netdf4()
// void update_forcing()
// void free_forcing(*meteo_forcing)
