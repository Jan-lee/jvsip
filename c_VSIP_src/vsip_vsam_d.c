/* Created RJudd December 30, 1997 */
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
/* $Id: vsip_vsam_d.c,v 2.0 2003/02/22 15:19:18 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_d.h"

void (vsip_vsam_d)(
  const vsip_vview_d* a,
  vsip_scalar_d beta,
  const vsip_vview_d* c,
  const vsip_vview_d* r) {
  { 
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride ast = a->stride * a->block->rstride,
                       cst = c->stride * c->block->rstride,
                       rst = r->stride * r->block->rstride;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                  *cp = (c->block->array) + c->offset * c->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    while(n-- > 0){
       *rp = (*ap + beta) * *cp;
        ap += ast;
        cp += cst;
        rp += rst;
    }
  }
}

