#include "ncout.h"

int dim_ids[2];  


void ncout_init (const char* cat, const char* fname, int dims, int *nc_idp, int *dim_idsp) {
  
  int len = (strlen(wDOMAIN)+strlen(wRUN)+strlen(cat)+7)* sizeof(char);
  char *dir = malloc(len);

  snprintf(dir, len, "out/%s/%s/%s", wDOMAIN, wRUN, cat);
  
  int len_cmd = len + 10*sizeof(char);
  char *cmd = malloc(len_cmd);
  snprintf(cmd, len_cmd, "mkdir -p %s", dir);
  system(cmd);
  
  len += (strlen(wDOMAIN)+strlen(fname)+strlen(wFRAME)+7)* sizeof(char);
  char *path = malloc(len);
  snprintf(path, len, "%s/%s.%s.%s.nc", dir, wDOMAIN, fname, wFRAME);
  
  nc_error(nc_create(path, 0, nc_idp));  
  
  free (dir);
  free (cmd);
  free (path);
  
 if (dims == (DIM_X | DIM_Y)) {
    nc_error(nc_def_dim(*nc_idp, "y", wNY, &dim_idsp[0]));
    nc_error(nc_def_dim(*nc_idp, "x", wNX, &dim_idsp[1]));
  } else if (dims == (DIM_X | DIM_Y | DIM_Z)) {
    nc_error(nc_def_dim(*nc_idp, "z", wNZ, &dim_idsp[0]));
    nc_error(nc_def_dim(*nc_idp, "y", wNY, &dim_idsp[1]));
    nc_error(nc_def_dim(*nc_idp, "x", wNZ, &dim_idsp[2]));   
  } else {
    fprintf(stdout, "erreur ncout_init\n");
  }
  
}


void ncout_set_global_meta (int nc_id) {
  static char title[]         = "OpenMeteoData WRF-Europe model";
  static char institution[]   = "OpenMeteoData http://openmeteodata.org";
  static char source[]        = "WRF-ARW initialized from NCEP GFS + OMD Post-processing";
  static char history[]       = "";
  static char references[]    = "http://wiki.openmeteodata.org/wiki/OMD_WRF_Europe";
  static char comment[]       = "";
  static char conventions[]   = "CF-1.6";
  static char license[]       = "ODC-By http://opendatacommons.org/licenses/by/summary/";

  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "title", strlen(title), title));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "institution", strlen(institution), institution));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "source", strlen(source), source));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "history", strlen(history), history));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "references", strlen(references), references));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "comment", strlen(comment), comment));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "Conventions", strlen(conventions), conventions));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "license", strlen(license), license));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "run", strlen(wRUN), wRUN));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "run_start", strlen(wRUN_START), wRUN_START));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "domain", strlen(wDOMAIN), wDOMAIN));
  nc_error(nc_put_att_text (nc_id, NC_GLOBAL, "frame", strlen(wFRAME), wFRAME));
}


void ncout_close (int nc_id) {
  nc_error(nc_close(nc_id));
}