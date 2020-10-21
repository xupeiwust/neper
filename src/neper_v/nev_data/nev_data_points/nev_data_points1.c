/* This file is part of the Neper software package. */
/* Copyright (C) 2003-2020, Romain Quey. */
/* See the COPYING file in the top-level directory. */

#include"nev_data_points_.h"

void
nev_data_points (struct SIM Sim, struct POINT *pPoint, struct TESS *pTess,
                        struct NODES *pNodes, struct MESH **pMesh,
                        char *entity, char *attribute, char *datastring,
                        struct DATA *pData)
{
  char *datatype = NULL, *datavalue = NULL;

  ut_print_message (0, 1, "Reading data (%s, %s)...\n", "point", attribute);

  neut_data_datastring_type_value ("points", attribute, datastring, &datatype, &datavalue);

  if (!strcmp (entity, "point"))
  {
    if (!strcmp (attribute, "col"))
      neut_data_fscanf_col (Sim, pTess, pNodes, pMesh, pPoint, "points", "point", 0,
                           (*pPoint).PointQty, datatype, datavalue, pData);

    else if (!strcmp (attribute, "trs"))
      neut_data_fscanf_trs ((*pPoint).PointQty, datatype, datavalue, pData);

    else if (!strcmp (attribute, "rad"))
      neut_data_fscanf_rad ((*pPoint).PointQty, datatype, datavalue, pData);

    else if (!strcmp (attribute, "colscheme"))
      ut_string_string (datastring, &(*pData).ColScheme);

    else if (!strcmp (attribute, "scale"))
      ut_string_string (datastring, &(*pData).Scale);

    else if (!strcmp (attribute, "scaletitle"))
      ut_string_string (datastring, &(*pData).ScaleTitle);

    else if (!strcmp (attribute, "coo"))
      neut_data_fscanf_coo (Sim, "point", (*pPoint).PointQty, datatype, datavalue,
                           pData);

    else if (!strcmp (attribute, "coofact"))
      (*pData).CooFact = atof (datavalue);

    else
      ut_print_exprbug (attribute);
  }

  else if (!strcmp (entity, "pointedge"))
  {
    if (!strcmp (attribute, "col"))
    {
      (*pData).BCol = ut_alloc_1d_int (3);
      ut_array_1d_int_fnscanf_wcard (datavalue, (*pData).BCol, 3, "color", "r");
    }
    else if (!strcmp (attribute, "rad"))
      (*pData).BRad = atof (datavalue);
    else
      ut_print_exprbug (attribute);
  }

  ut_free_1d_char (&datatype);
  ut_free_1d_char (&datavalue);

  return;
}
