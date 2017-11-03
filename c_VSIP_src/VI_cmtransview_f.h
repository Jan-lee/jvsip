/* Created RJudd October 6, 2000 */
/* SPAWARSYSCEN                  */
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
/* $Id: VI_cmtransview_f.h,v 2.1 2003/03/08 14:54:14 judd Exp $ */

#ifndef _VI_CMTRANSVIEW_F_H
#define _VI_CMTRANSVIEW_F_H

#include"vsip.h"
#include"vsip_cmviewattributes_f.h"

static
vsip_cmview_f*
VI_cmtransview_f(
  const vsip_cmview_f* v, 
  vsip_cmview_f * a) {
    *a = *v;
    a->row_stride = v->col_stride;
    a->col_stride = v->row_stride;
    a->row_length = v->col_length;
    a->col_length = v->row_length;
    return a;
}
#endif /* _VI_CMTRANSVIEW_F_H */
