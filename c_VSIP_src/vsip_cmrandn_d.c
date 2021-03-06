/*
 //  vsip_cmrandn_d.c
 //  jvsipF
 //
 //  Created by RANDALL JUDD on 9/14/13.
 //  Copyright (c) 2013 Independent Consultant. All rights reserved.
 */
/*********************************************************************
 // This code includes no warranty, express or implied, including     /
 // the warranties of merchantability and fitness for a particular    /
 // purpose.                                                          /
 // No person or entity assumes any legal liability or responsibility /
 // for the accuracy, completeness, or usefulness of any information, /
 // apparatus, product, or process disclosed, or represents that      /
 // its use would not infringe privately owned rights.                /
 *********************************************************************/
/*********************************************************************
 // The MIT License (see copyright for jvsip in top level directory)
 // http://opensource.org/licenses/MIT
 **********************************************************************/

#include"VI_cmcolview_d.h"
#include"VI_cmrowview_d.h"
#include"vsip.h"
#include"vsip_cmviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_randobject.h"

static void cvrandn_d(
     vsip_randstate *state,
     const vsip_cvview_d *r)
{
   if(state->type)
   { /* nonportable generator */
      vsip_scalar_ue32 a = state->a,
                      c = state->c,
                      X = state->X;
      vsip_length n = r->length;
      /* register */ vsip_stride rst = r->stride * r->block->cstride;
      vsip_scalar_d *rpr = (r->block->R->array) + r->offset * r->block->cstride;
      vsip_scalar_d *rpi = (r->block->I->array) + r->offset * r->block->cstride;
      while(n-- > 0){
         vsip_scalar_d t2;
         X     = a * X + c;
         *rpr  = (vsip_scalar_d)X/(vsip_scalar_d)4294967296.0;
         X     = a * X + c;
         *rpr += (vsip_scalar_d)X/(vsip_scalar_d)4294967296.0;
         X     = a * X + c;
         *rpr += (vsip_scalar_d)X/(vsip_scalar_d)4294967296.0;
         X     = a * X + c;
         t2    = (vsip_scalar_d)X/(vsip_scalar_d)4294967296.0;
         X     = a * X + c;
         t2   += (vsip_scalar_d)X/(vsip_scalar_d)4294967296.0;
         X     = a * X + c;
         t2   += (vsip_scalar_d)X/(vsip_scalar_d)4294967296.0;
         *rpi = *rpr - t2;
         *rpr = 3 - t2 - *rpr;
         rpr  += rst;
         rpi  += rst;
      }  
      state->X = X;
   } else { /* portable generator */
      vsip_scalar_ue32 itemp;
      vsip_length n = r->length;
      /* register */ vsip_stride rst = r->stride * r->block->cstride;
      vsip_scalar_d *rpr = (r->block->R->array) + r->offset * r->block->cstride;
      vsip_scalar_d *rpi = (r->block->I->array) + r->offset * r->block->cstride;
      while(n-- > 0){
         vsip_scalar_d t2;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         itemp = (itemp>>8) | 0x00000001;
         *rpr  = (vsip_scalar_d)itemp/(vsip_scalar_d)16777216.0;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         itemp = (itemp>>8) | 0x00000001;
         *rpr  += (vsip_scalar_d)itemp/(vsip_scalar_d)16777216.0;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         itemp = (itemp>>8) | 0x00000001;
         *rpr  += (vsip_scalar_d)itemp/(vsip_scalar_d)16777216.0;
         /* end t1 */
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         } 
         itemp = (itemp>>8) | 0x00000001;
         t2  = (vsip_scalar_d)itemp/(vsip_scalar_d)16777216.0;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         } 
         itemp = (itemp>>8) | 0x00000001;
         t2  += (vsip_scalar_d)itemp/(vsip_scalar_d)16777216.0;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         } 
         itemp = (itemp>>8) | 0x00000001;
         t2  += (vsip_scalar_d)itemp/(vsip_scalar_d)16777216.0;
         /* end t2 */
         *rpi = *rpr - t2;
         *rpr = 3 - t2 - *rpr;
         rpr  += rst;
         rpi  += rst;
      }
   }
   return;
}


void vsip_cmrandn_d(
     vsip_randstate *state,
     const vsip_cmview_d *A)
{
   vsip_index i;
   vsip_cvview_d v;
   vsip_length M=A->col_length, N=A->row_length;
   vsip_stride CS=A->col_stride, RS=A->row_stride;
   if (CS < RS){ /* do by column */
       for (i=0; i<N; i++){
            VI_cmcolview_d(A,i,&v);
            cvrandn_d(state,&v);
       }
   } else { /* do by row */
        for (i=0; i<M; i++){
            VI_cmrowview_d(A,i,&v);
            cvrandn_d(state,&v);
       }
    }
}
