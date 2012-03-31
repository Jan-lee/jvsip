/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: cmswap_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
#include"VU_cmprintm_d.include"
static void cmswap_d(void){
   printf("\n*******\nTEST cmswap_d\n\n");
   { vsip_scalar_d data1_r[] = { -1, -2, 3, 4, -5, -6};
     vsip_scalar_d data1_i[] = { 1, 2, -3, -4, 5,   6};
     vsip_scalar_d data2  [] = { 10,20, 11,21, 12,22, 13,23, 14,24, 15,25};
     vsip_cblock_d  *block1 = vsip_cblockbind_d(data1_r,data1_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block2 = vsip_cblockbind_d(data2,NDPTR_d,6,VSIP_MEM_NONE);
     vsip_cmview_d  *a = vsip_cmbind_d(block1,0,2,3,1,2);
     vsip_cmview_d  *b = vsip_cmbind_d(block2,0,2,3,1,2);
     vsip_cmview_d  *a1 = vsip_cmcreate_d(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d  *b1 = vsip_cmcreate_d(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d  *chk = vsip_cmcreate_d(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d   *chk_r = vsip_mrealview_d(chk);
     vsip_cblockadmit_d(block1,VSIP_TRUE);
     vsip_cblockadmit_d(block2,VSIP_TRUE);
     
     vsip_cmcopy_d_d(a,a1);
     vsip_cmcopy_d_d(b,b1);

     printf("matrix a\n");VU_cmprintm_d("8.6",a);
     printf("matrix b\n");VU_cmprintm_d("8.6",b);
     printf("vsip_cmswap_d(a,b)\n");
     vsip_cmswap_d(a,b);
     printf("matrix a\n");VU_cmprintm_d("8.6",a);
     printf("matrix b\n");VU_cmprintm_d("8.6",b);

     vsip_cmsub_d(a,b1,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error in matrix <a>\n");
     else
         printf("<a> correct\n");

     vsip_cmsub_d(b,a1,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error in matrix <b>\n");
     else
         printf("<b> correct\n");

     vsip_cmalldestroy_d(a);
     vsip_cmalldestroy_d(b);
     vsip_cmalldestroy_d(a1);
     vsip_cmalldestroy_d(b1);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
   }
   return;
}
