/* Created RJudd September 19, 2000 */
/* SPAWARSYSCEN D857                */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_cmbind_f.c,v 2.0 2003/02/22 15:18:41 judd Exp $ */

#include"vsip.h"
#include"vsip_cmviewattributes_f.h"

vsip_cmview_f* (vsip_cmbind_f)(
  const vsip_cblock_f* b, 
  vsip_offset o,
  vsip_stride c_s, 
  vsip_length c_l, 
  vsip_stride r_s, 
  vsip_length r_l) {
   vsip_cmview_f* v = (vsip_cmview_f*)malloc(sizeof(vsip_cmview_f));
   if(v != (vsip_cmview_f*)NULL){
      v->block = (vsip_cblock_f*)b;
      v->offset = o;
      v->row_stride = r_s;
      v->col_stride = c_s;
      v->row_length = r_l;
      v->col_length = c_l;
      v->markings = VSIP_VALID_STRUCTURE_OBJECT;
   }
   return v;
}
