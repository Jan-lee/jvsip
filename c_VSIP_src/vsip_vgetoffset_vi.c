/* Created RJudd September 30, 2000 */
/* SPAWARYSCEN D857                 */
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
/* $Id: vsip_vgetoffset_vi.c,v 2.0 2003/02/22 15:19:14 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_vi.h"

vsip_offset (vsip_vgetoffset_vi)(
  const vsip_vview_vi *v) {
    return v->offset;
}
