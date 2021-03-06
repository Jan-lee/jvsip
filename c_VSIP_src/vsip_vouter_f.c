/* Created RJudd March 12, 1998 */
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
/* $Id: vsip_vouter_f.c,v 2.0 2003/02/22 15:19:16 judd Exp $ */
/* April 21, 1998 1,2 to row,col */
/* Modified RJudd Feb 14, 1999 */
/* to fix cmbind */
/* Removed Development Mode RJudd Sept 00 */

#include"vsip.h"
#include"vsip_mviewattributes_f.h"
#include"vsip_vviewattributes_f.h"

void (vsip_vouter_f)(
  vsip_scalar_f alpha,
  const vsip_vview_f* a,
  const vsip_vview_f* b,
  const vsip_mview_f* R) {	/* R_ij = a_i*b_j	*/
  {
     /* register */ vsip_length n = a->length,
                                m = b->length;
     vsip_scalar_f  *a_p = a->block->array + a->offset * a->block->rstride; 
     vsip_length i,j;
     vsip_stride Rrst = R->row_stride * R->block->rstride,
                 bst  = b->stride * b->block->rstride,
                 ast  = a->stride * a->block->rstride;
     vsip_offset bo  = b->offset * b->block->rstride,
                 Ro  = R->offset * R->block->rstride,
                 Rco = R->col_stride * R->block->rstride;
     for(i=0; i<n; i++){
         vsip_scalar_f *R_p = R->block->array + Ro + i * Rco,
                       *b_p = b->block->array + bo;
         vsip_scalar_f temp = *a_p * alpha;
         for(j=0; j<m; j++){
             *R_p = temp * *b_p;
              R_p += Rrst; b_p += bst;
         }
         a_p += ast;
     }
  }
  return;
}

