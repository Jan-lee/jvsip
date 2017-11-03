/* Created RJudd September 21, 2000 */
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
/* $Id: vsip_cvdestroy_d.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */

#include"vsip.h"
#include"vsip_cvviewattributes_d.h"

vsip_cblock_d* (vsip_cvdestroy_d)(
  vsip_cvview_d* v) {
   vsip_cblock_d* b=(vsip_cblock_d*)NULL;
   if(v != (vsip_cvview_d*)NULL){
      b = v->block;
      v->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free((void*)v);
   }
   return b;
}
