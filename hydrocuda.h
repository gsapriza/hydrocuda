/**************
* HydroCuda model
*
* Set of hydrologic models to simulate the hydrological model response
* using c and cuda
***************/

#include "ini.h"

// General Program Options
typedef struct {
  struct ini_t *config;         // Configuration to read options
  char          hydroModel[10]; // Hydrological model
  char          domainModel[10]; // Basin discretization
  char          meteoModel[10];  // Time series options
  int           istimeblock;    // 1 if divide time in block, 0 if not
} model_option;

// General Model domain discretization
typedef struct{
  int   ntgt;    // Number of unique space domains in case of gridcells = nx*ny
  int   nx;      // Number of columns
  int   ny;      // Number of rows
  float dx;      // Space discretization x direction
  float dy;      // Space discretization y direction
} model_domain;

// Model time discretization
typedef struct{
    char freq[1];       // Time frequency
    int  nt;            // Total number of time steps
    int  start_second;  // second start time
    int  start_min;     // minutes start time
    int  start_hour;    // hour start time
    int  start_day;     // day start time
    int  start_month;   // month start time
    int  start_year;    // year start time
    int  end_second;    // second end time
    int  end_min;       // minutes end time
    int  end_hour;      // hour end time
    int  end_day;       // day end time
    int  end_month;     // month end time
    int  end_year;      // year end time
    int  timestep;      // time step in seconds
    int  ntblock;       // number of block time
    int *datetime;      // all dates time
} model_time;

//We define model topology
typedef struct{
  float  area; // Area of each grid cell
  int   *ldd;  // Directions
} model_topology;

// Parameter definition for hbv
typedef struct{
  char   units[15];      // Time series units
  char   name[20];       // Name of time series
  int    indx;           // Variable index
  int    tipe;           // 1=Flux, 2=Param, 3=StateVariable, 4=forcing
  int    timetipe;       // 1=cte or only one time, 2=ntblock times, 3=all times
  char   location[250];  // Location of time series data
  float *vars;           // Time series
} vars_info;

typedef struct {
//   int        nparam;  // Number of parameters
//   int        nstates; // Number of states variables
//   int        nflows;  // Number of flows
  int        nvars; // Number of variables (parameters, states and flows)
  vars_info *info;  // Variables id to be initialized
} model_vars;

// Auxiliar structures
typedef struct {
  char ids[30]; //ids to get meteo info
} aux_ids;

// Function declaration
// Init
void init_modeloptions();
void init_domain();
void init_times();

// HBV Model
void init_hbv();
void allocate_hbv();
void free_hbv();
void read_hbv_netcdf();
void update_hbv();
void compute_hbv();
void compute_hbv_cuda();

// Meteorological forcing
void init_forcing();
void allocate_forcing();
void read_forcing_netcdf();
void update_forcing();
void free_forcing();

// Auxiliar
int getindx();
int read_netcdf();
float max();
float min();
