/* Created by RJudd January 7, 1999 */
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
/* $Id: VI_ccfftmip_d_def.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */

#include"VI_fftm_building_blocks_d.h"

void vsip_ccfftmip_d(const vsip_fftm_d *Offt,
                    const vsip_cmview_d *y)
{  
   vsip_fftm_d Nfft = *Offt;
   vsip_fftm_d *fftm = &Nfft;
   VI_ccfftmip_d(fftm,y);
}
