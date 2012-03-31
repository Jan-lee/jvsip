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
/* $Id: crmsub_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
#include"VU_cmprintm_d.include"
#include"VU_mprintm_d.include"
static void crmsub_d(void){
    printf("\n******\nTEST crmsub_d\n");
    {
        vsip_scalar_d data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_d data2_r[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_d data2_i[]= {-1.1, 2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9};
        vsip_scalar_d ans_r[] =  {-0.1, -2.4, -4.7, 1.8, -0.5, -2.8, 3.7, 1.4, -0.9};
        vsip_scalar_d ans_i[] =  {0.1, 0.2, 0.3, -0.1, -0.3, -0.4, 0.8, 0.9, -1.0};
        vsip_cmview_d *m1 = vsip_cmbind_d(
                  vsip_cblockbind_d(data1,NDPTR_d,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *c_m2 = vsip_cmbind_d(
                  vsip_cblockbind_d(data2_r,data2_i,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_d  *m2= vsip_mrealview_d(c_m2);
        vsip_cmview_d *ma = vsip_cmbind_d(
                  vsip_cblockbind_d(ans_r,ans_i,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *m3 = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_d *chk = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d  *chk_r = vsip_mrealview_d(chk);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m1),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(c_m2),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(ma),VSIP_TRUE);
        printf("call vsip_crmsub_d(a,b,c)\n");
        printf("a =\n");VU_cmprintm_d("8.6",m1);
        printf("b =\n");VU_mprintm_d("8.6",m2);
        vsip_crmsub_d(m1,m2,m3);
        printf("c =\n");VU_cmprintm_d("8.6",m3);
        printf("\nright answer =\n"); VU_cmprintm_d("6.4",ma);
        vsip_cmsub_d(ma,m3,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        {
          vsip_mview_d *b = vsip_mrealview_d(m3);
          vsip_mcopy_d_d(m2,b);
          printf(" b,c inplace with <b> realview of <c>\n");
          vsip_crmsub_d(m1,b,m3);
          vsip_cmsub_d(ma,m3,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
          if(fabs(vsip_msumval_d(chk_r)) > .5)
              printf("error\n");
          else
              printf("correct\n");
          vsip_mdestroy_d(b);
        }

        vsip_cmcopy_d_d(m1,m3);
        printf(" a,c inplace\n");
        vsip_crmsub_d(m3,m2,m3);
        vsip_cmsub_d(ma,m3,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_mdestroy_d(m2);
        vsip_cmalldestroy_d(m1); vsip_cmalldestroy_d(c_m2);
        vsip_cmalldestroy_d(m3); vsip_cmalldestroy_d(ma);
        vsip_mdestroy_d(chk_r);    vsip_cmalldestroy_d(chk);
    }                                                       
      
    return;
}
