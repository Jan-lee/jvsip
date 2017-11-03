/* Created RJudd July 27, 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_vcopy_bl_f.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* to include attributes information */
/* Modified RJudd January 1, 1998 */
/* to copy _bl to _f */
/* Removed Development Mode RJudd Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_f.h"
#include"vsip_vviewattributes_bl.h"

void (vsip_vcopy_bl_f)(
  const vsip_vview_bl* a,
  const vsip_vview_f* r) {
  { 
      /* register */ vsip_length n   = r->length;
      /* register */ vsip_stride ast = a->stride,
                                 rst = r->stride * r->block->rstride;
      vsip_scalar_bl *ap = (a->block->array) + a->offset;
      vsip_scalar_f  *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         *rp = (vsip_scalar_f) *ap;
         ap += ast; rp += rst;
      }
   }
}
