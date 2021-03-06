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
/* $Id: vsip_vdestroy_li.c,v 2.0 2003/02/22 15:19:12 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_li.h"

vsip_block_li* (vsip_vdestroy_li)(
  vsip_vview_li* v) {
   vsip_block_li* b = (vsip_block_li*)NULL;
   if(v != (vsip_vview_li*)NULL){
      b = v->block;
      v->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free((void*)v);
   }
   return b;
}
