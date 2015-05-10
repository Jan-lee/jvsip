/* Created RJudd September 18, 2000 */
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
/* $Id: vsip_mcreate_l.c,v 2.0 2003/02/22 15:18:55 judd Exp $ */

#include<vsip.h>
#include"VI_blockcreate_l.h"
#include"VI_blockdestroy_l.h"

vsip_mview_l* (vsip_mcreate_l)(
  vsip_length col_length, 
  vsip_length row_length, 
  vsip_major major, 
  vsip_memory_hint mem_hint) {
   vsip_block_l* b = VI_blockcreate_l(
              (size_t)(col_length * row_length), mem_hint); 
   vsip_mview_l* v = (vsip_mview_l*)NULL;
   if(b != NULL){

      v = (major == VSIP_ROW) ?
        vsip_mbind_l(b, (vsip_offset)0,
           (vsip_stride)row_length, col_length,
           (vsip_stride)1, row_length)
        :
        vsip_mbind_l(b, (vsip_offset)0,
           (vsip_stride)1,col_length,
           (vsip_stride)col_length, row_length);
      
      if(v == (vsip_mview_l*)NULL) VI_blockdestroy_l(b);
   }
   return v;
}
