/* Created RJudd January 8, 2013 */
/*********************************************************************
// This code includes                                                 /
// no warranty, express or implied, including the warranties          /
// of merchantability and fitness for a particular purpose.           /
// No person or entity                                                /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
#include"VU_svdUtils.h"


vsip_mview_f *bidiag_f(
    vsip_mview_f *A){
    vsip_length m = vsip_mgetcollength_f(A);
    vsip_length n = vsip_mgetrowlength_f(A);
    vsip_mview_f *B = mclone_f(A);
    vsip_mview_f *Bs= vsip_mcloneview_f(B);
    vsip_vview_f *x=vsip_mcolview_f(B,0);
    vsip_vview_f *v=vclone_f(x);
    vsip_vview_f *vs = vsip_vcloneview_f(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
    /* x=B[i:,i:].colview(0); v=houseVector(x); v/=v[0]*/
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
    /* houseProd(v,B[i:,i:]) */
        houseProd_f(v,Bs);
    /* x[1:]=v[1:] */
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_vputlength_f(v,n-j);
            vsip_vcopy_f_f(row_sv_f(msv_f(B,Bs,i,j),x,0),v);
            houseVector_f(v);
            vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
            prodHouse_f(Bs,v);
            vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
        houseProd_f(v,Bs);
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
    }
    vsip_vdestroy_f(vs); vsip_valldestroy_f(v);
    vsip_vdestroy_f(x); vsip_mdestroy_f(Bs);
    return B;
}
vsip_cmview_f *cbidiag_f(
    vsip_cmview_f *A){
    vsip_length m = vsip_cmgetcollength_f(A);
    vsip_length n = vsip_cmgetrowlength_f(A);
    vsip_cmview_f *B = cmclone_f(A);
    vsip_cmview_f *Bs= vsip_cmcloneview_f(B);
    vsip_cvview_f *x=vsip_cmcolview_f(B,0);
    vsip_cvview_f *v=cvclone_f(x);
    vsip_cvview_f *vs = vsip_cvcloneview_f(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_f(v,n-j);
            vsip_cvcopy_f_f(crow_sv_f(cmsv_f(B,Bs,i,j),x,0),v);
            chouseVector_f(v);vsip_cvconj_f(v,v);
            vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
            cprodHouse_f(Bs,v);
            vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
    }
    vsip_cvdestroy_f(vs); vsip_cvalldestroy_f(v);
    vsip_cvdestroy_f(x); vsip_cmdestroy_f(Bs);
    return B;
}
vsip_mview_d *bidiag_d(vsip_mview_d *A){
    vsip_length m = vsip_mgetcollength_d(A);
    vsip_length n = vsip_mgetrowlength_d(A);
    vsip_mview_d *B = mclone_d(A);
    vsip_mview_d *Bs= vsip_mcloneview_d(B);
    vsip_vview_d *x=vsip_mcolview_d(B,0);
    vsip_vview_d *v=vclone_d(x);
    vsip_vview_d *vs = vsip_vcloneview_d(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
        houseProd_d(v,Bs);
        vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_vputlength_d(v,n-j);
            vsip_vcopy_d_d(row_sv_d(msv_d(B,Bs,i,j),x,0),v);
            houseVector_d(v);
            vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
            prodHouse_d(Bs,v);
            vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
        houseProd_d(v,Bs);
        vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
    }
    vsip_vdestroy_d(vs); vsip_valldestroy_d(v);
    vsip_vdestroy_d(x); vsip_mdestroy_d(Bs);
    return B;
}
vsip_cmview_d *cbidiag_d(
    vsip_cmview_d *A){
    vsip_length m = vsip_cmgetcollength_d(A);
    vsip_length n = vsip_cmgetrowlength_d(A);
    vsip_cmview_d *B = cmclone_d(A);
    vsip_cmview_d *Bs= vsip_cmcloneview_d(B);
    vsip_cvview_d *x=vsip_cmcolview_d(B,0);
    vsip_cvview_d *v=cvclone_d(x);
    vsip_cvview_d *vs = vsip_cvcloneview_d(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
        chouseProd_d(v,Bs);
        vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_d(v,n-j);
            vsip_cvcopy_d_d(crow_sv_d(cmsv_d(B,Bs,i,j),x,0),v);
            chouseVector_d(v);vsip_cvconj_d(v,v);
            vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
            cprodHouse_d(Bs,v);
            vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
        chouseProd_d(v,Bs);
        vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
    }
    vsip_cvdestroy_d(vs); vsip_cvalldestroy_d(v);
    vsip_cvdestroy_d(x); vsip_cmdestroy_d(Bs);
    return B;
}
vsip_mview_f *UmatExtract_f(vsip_mview_f*B){
    vsip_stride i;
    vsip_length m = vsip_mgetcollength_f(B);
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *U=meye_f(m);
    vsip_mview_f *Bs, *Us;
    vsip_vview_f *v;
    vsip_scalar_f t;
    v = vsip_mcolview_f(B,0);
    Bs=vsip_mcloneview_f(B);
    Us=vsip_mcloneview_f(U);
    if (m > n){
        i=n-1;
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    } 
    return U;
}
vsip_cmview_f *cUmatExtract_f(vsip_cmview_f*B){
    vsip_stride i;
    vsip_length m = vsip_cmgetcollength_f(B);
    vsip_length n = vsip_cmgetrowlength_f(B);
    vsip_cmview_f *U=cmeye_f(m);
    vsip_cmview_f *Bs, *Us;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    v = vsip_cmcolview_f(B,0);
    Bs=vsip_cmcloneview_f(B);
    Us=vsip_cmcloneview_f(U);
    if (m > n){
        i=n-1;
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
        chouseProd_f(v,cmsv_f(U,Us,i,i));
        vsip_cvput_f(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
        chouseProd_f(v,cmsv_f(U,Us,i,i));
        vsip_cvput_f(v,0,t);
    } 
    return U;
}
vsip_mview_f *VHmatExtract_f(vsip_mview_f*B){
    vsip_stride i;
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *Bs; 
    vsip_mview_f *V=meye_f(n);
    vsip_mview_f *Vs;
    vsip_vview_f *v;
    vsip_scalar_f t;
    if(n < 3)
        return V;
    v = vsip_mrowview_f(B,0);
    Vs=vsip_mcloneview_f(V);
    Bs=vsip_mcloneview_f(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        row_sv_f(msv_f(B,Bs,i,j),v,0);
        t=vsip_vget_f(v,0);vsip_vput_f(v,0,1.0);
        prodHouse_f(msv_f(V,Vs,j,j),v);
        vsip_vput_f(v,0,t);
    }      
    vsip_vdestroy_f(v);
    vsip_mdestroy_f(Vs);
    vsip_mdestroy_f(Bs);
    return V;
}
vsip_cmview_f *cVHmatExtract_f(vsip_cmview_f*B){
    vsip_stride i;
    vsip_length n = vsip_cmgetrowlength_f(B);
    vsip_cmview_f *Bs; 
    vsip_cmview_f *V=cmeye_f(n);
    vsip_cmview_f *Vs;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    if(n < 3)
        return V;
    v = vsip_cmrowview_f(B,0);
    Vs=vsip_cmcloneview_f(V);
    Bs=vsip_cmcloneview_f(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        crow_sv_f(cmsv_f(B,Bs,i,j),v,0);
        t=vsip_cvget_f(v,0);vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
        cprodHouse_f(cmsv_f(V,Vs,j,j),v);
        vsip_cvput_f(v,0,t);
    }      
    vsip_cvdestroy_f(v);
    vsip_cmdestroy_f(Vs);
    vsip_cmdestroy_f(Bs);
    return V;
}
vsip_mview_d *UmatExtract_d(vsip_mview_d*B){
    vsip_stride i;
    vsip_length m = vsip_mgetcollength_d(B);
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_mview_d *U=meye_d(m);
    vsip_mview_d *Bs, *Us;
    vsip_vview_d *v;
    vsip_scalar_d t;
    v = vsip_mcolview_d(B,0);
    Bs=vsip_mcloneview_d(B);
    Us=vsip_mcloneview_d(U);
    if (m > n){
        i=n-1;
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
        houseProd_d(v,msv_d(U,Us,i,i));
        vsip_vput_d(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
        houseProd_d(v,msv_d(U,Us,i,i));
        vsip_vput_d(v,0,t);
    } 
    return U;
}
vsip_cmview_d *cUmatExtract_d(vsip_cmview_d*B){
    vsip_stride i;
    vsip_length m = vsip_cmgetcollength_d(B);
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cmview_d *U=cmeye_d(m);
    vsip_cmview_d *Bs, *Us;
    vsip_cvview_d *v;
    vsip_cscalar_d t;
    v = vsip_cmcolview_d(B,0);
    Bs=vsip_cmcloneview_d(B);
    Us=vsip_cmcloneview_d(U);
    if (m > n){
        i=n-1;
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        chouseProd_d(v,cmsv_d(U,Us,i,i));
        vsip_cvput_d(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        chouseProd_d(v,cmsv_d(U,Us,i,i));
        vsip_cvput_d(v,0,t);
    } 
    return U;
}
vsip_mview_d *VHmatExtract_d(vsip_mview_d*B){
    vsip_stride i;
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_mview_d *Bs; 
    vsip_mview_d *V=meye_d(n);
    vsip_mview_d *Vs;
    vsip_vview_d *v;
    vsip_scalar_d t;
    if(n < 3)
        return V;
    v = vsip_mrowview_d(B,0);
    Vs=vsip_mcloneview_d(V);
    Bs=vsip_mcloneview_d(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        row_sv_d(msv_d(B,Bs,i,j),v,0);
        t=vsip_vget_d(v,0);vsip_vput_d(v,0,1.0);
        prodHouse_d(msv_d(V,Vs,j,j),v);
        vsip_vput_d(v,0,t);
    }      
    vsip_vdestroy_d(v);
    vsip_mdestroy_d(Vs);
    vsip_mdestroy_d(Bs);
    return V;
}
vsip_cmview_d *cVHmatExtract_d(vsip_cmview_d*B){
    vsip_stride i;
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cmview_d *Bs; 
    vsip_cmview_d *V=cmeye_d(n);
    vsip_cmview_d *Vs;
    vsip_cvview_d *v;
    vsip_cscalar_d t;
    if(n < 3)
        return V;
    v = vsip_cmrowview_d(B,0);
    Vs=vsip_cmcloneview_d(V);
    Bs=vsip_cmcloneview_d(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        crow_sv_d(cmsv_d(B,Bs,i,j),v,0);
        t=vsip_cvget_d(v,0);vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        cprodHouse_d(cmsv_d(V,Vs,j,j),v);
        vsip_cvput_d(v,0,t);
    }      
    vsip_cvdestroy_d(v);
    vsip_cmdestroy_d(Vs);
    vsip_cmdestroy_d(Bs);
    return V;
}

void csvdZeroCheckAndSet_f(vsip_scalar_f e, vsip_cvview_f *b0, vsip_cvview_f *b1){
    vsip_index i;
    vsip_length n = vsip_cvgetlength_f(b1);
    vsip_cscalar_f z = vsip_cmplx_f(0.0,0.0);
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_cmag_f(vsip_cvget_f(b1,i));
        vsip_scalar_f a = e*(vsip_cmag_f(vsip_cvget_f(b0,i))
                        +    vsip_cmag_f(vsip_cvget_f(b0,i+1)));
        if( b < a ) vsip_cvput_f(b1,i,z);
    }
}
void svdZeroCheckAndSet_f(vsip_scalar_f e, vsip_vview_f *b0, vsip_vview_f *b1){
    vsip_index i;
    vsip_length n = vsip_vgetlength_f(b1);
    vsip_scalar_f z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_mag_f(vsip_vget_f(b1,i));
        vsip_scalar_f a = e*(vsip_mag_f(vsip_vget_f(b0,i))
                        +    vsip_mag_f(vsip_vget_f(b0,i+1)));
        if( b < a ) vsip_vput_f(b1,i,z);
    }
}
void csvdZeroCheckAndSet_d(vsip_scalar_d e, vsip_cvview_d *b0, vsip_cvview_d *b1){
    vsip_index i;
    vsip_length n = vsip_cvgetlength_d(b1);
    vsip_cscalar_d z = vsip_cmplx_d(0.0,0.0);
    for(i=0; i<n; i++){
        vsip_scalar_d b = vsip_cmag_d(vsip_cvget_d(b1,i));
        vsip_scalar_d a = e*(vsip_cmag_d(vsip_cvget_d(b0,i))
                        +    vsip_cmag_d(vsip_cvget_d(b0,i+1)));
        if( b < a ) vsip_cvput_d(b1,i,z);
    }
}
void svdZeroCheckAndSet_d(vsip_scalar_d e, vsip_vview_d *b0, vsip_vview_d *b1){
    vsip_index i;
    vsip_length n = vsip_vgetlength_d(b1);
    vsip_scalar_d z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_d b = vsip_mag_d(vsip_vget_d(b1,i));
        vsip_scalar_d a = e*(vsip_mag_d(vsip_vget_d(b0,i))
                        +    vsip_mag_d(vsip_vget_d(b0,i+1)));
        if( b < a ) vsip_vput_d(b1,i,z);
    }
}
void biDiagPhaseToZero_f(
      vsip_mview_f *L,
      vsip_vview_f *d,
      vsip_vview_f *f,
      vsip_mview_f *R,
      vsip_scalar_f eps0)
{
   vsip_length n_d=vsip_vgetlength_f(d);
   vsip_length n_f=vsip_vgetlength_f(f);
   vsip_index i,j;
   vsip_scalar_f ps;
   vsip_scalar_f m;
   vsip_vview_f *l = vsip_mcolview_f(L,0);
   vsip_vview_f *r = vsip_mrowview_f(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_vget_f(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            col_sv_f(L,l,i);vsip_svmul_f(ps,l,l);
            vsip_vput_f(d,i,m);
            if (i < n_f)
                vsip_vput_f(f,i,ps*vsip_vget_f(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_vget_f(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        col_sv_f(L, l, j);vsip_svmul_f(ps,l,l);
        row_sv_f(R,r,j);vsip_svmul_f(ps,r,r);
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * vsip_vget_f(f,j));
    }
    j=n_f;
    i=j-1;
    ps=vsip_vget_f(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    col_sv_f(L, l, j);vsip_svmul_f(ps,l,l);
    row_sv_f(R,r,j);vsip_svmul_f(ps,r,r);
}
void cbiDiagPhaseToZero_f(
      vsip_cmview_f *L,
      vsip_cvview_f *d,
      vsip_cvview_f *f,
      vsip_cmview_f *R,
      vsip_scalar_f eps0)
{
   vsip_length n_d=vsip_cvgetlength_f(d);
   vsip_length n_f=vsip_cvgetlength_f(f);
   vsip_index i,j;
   vsip_cscalar_f ps;
   vsip_scalar_f m;
   vsip_cvview_f *l = vsip_cmcolview_f(L,0);
   vsip_cvview_f *r = vsip_cmrowview_f(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_cvget_f(d,i);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_f(-1.0,0.0);
            else
                ps= vsip_cmplx_f(1.0,0.0);
            m = vsip_mag_f(m); 
        } else {
            m=vsip_cmag_f(ps);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_csvmul_f(ps,l,l);
            vsip_cvput_f(d,i,vsip_cmplx_f(m,0));
            if (i < n_f)
                vsip_cvput_f(f,i,vsip_cjmul_f(vsip_cvget_f(f,i),ps));
        }else{
            vsip_cvput_f(d,i,vsip_cmplx_f(0.0,0.0));
        }
    }
    csvdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_cvget_f(f,i);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_f(-1.0,0.0);
            else
                ps= vsip_cmplx_f(1.0,0.0);
            m = vsip_mag_f(m);
        }else{
            m=vsip_cmag_f(ps);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
        crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
        vsip_cvput_f(f,i,vsip_cmplx_f(m,0));
        vsip_cvput_f(f,j,vsip_cmul_f(vsip_cvget_f(f,j),ps));
    }
    j=n_f;
    i=j-1;
    ps=vsip_cvget_f(f,i);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps=vsip_cmplx_f(-1.0,0.0);
        else
            ps= vsip_cmplx_f(1.0,0.0);
        m = vsip_mag_f(m);
    }else{
        m=vsip_cmag_f(ps);
        ps.r /= m; ps.i/=m;
    }
    vsip_cvput_f(f,i,vsip_cmplx_f(m,0.0));
    ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
    crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
}
void biDiagPhaseToZero_d(
      vsip_mview_d *L,
      vsip_vview_d *d,
      vsip_vview_d *f,
      vsip_mview_d *R,
      vsip_scalar_d eps0)
{
   vsip_length n_d=vsip_vgetlength_d(d);
   vsip_length n_f=vsip_vgetlength_d(f);
   vsip_index i,j;
   vsip_scalar_d ps;
   vsip_scalar_d m;
   vsip_vview_d *l = vsip_mcolview_d(L,0);
   vsip_vview_d *r = vsip_mrowview_d(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_vget_d(d,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        if(m > eps0){
            col_sv_d(L,l,i);vsip_svmul_d(ps,l,l);
            vsip_vput_d(d,i,m);
            if (i < n_d)
                vsip_vput_d(f,i,ps*vsip_vget_d(f,i));
        } else {
            vsip_vput_d(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_vget_d(f,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        col_sv_d(L, l, j);vsip_svmul_d(ps,l,l);
        row_sv_d(R,r,j);vsip_svmul_d(ps,r,r);
        vsip_vput_d(f,i,m);
        vsip_vput_d(f,j,ps * vsip_vget_d(f,j));
    }
    j=n_f;
    i=j-1;
    ps=vsip_vget_d(f,i);
    m=vsip_mag_d(ps);
    ps=sign_d(ps);
    vsip_vput_d(f,i,m);
    col_sv_d(L, l, j);vsip_svmul_d(ps,l,l);
    row_sv_d(R,r,j);vsip_svmul_d(ps,r,r);
}
void cbiDiagPhaseToZero_d(
      vsip_cmview_d *L,
      vsip_cvview_d *d,
      vsip_cvview_d *f,
      vsip_cmview_d *R,
      vsip_scalar_d eps0)
{
   vsip_length n_d=vsip_cvgetlength_d(d);
   vsip_length n_f=vsip_cvgetlength_d(f);
   vsip_index i,j;
   vsip_cscalar_d ps;
   vsip_scalar_d m;
   vsip_cvview_d *l = vsip_cmcolview_d(L,0);
   vsip_cvview_d *r = vsip_cmrowview_d(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_cvget_d(d,i);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_d(-1.0,0.0);
            else
                ps= vsip_cmplx_d(1.0,0.0);
            m = vsip_mag_d(m); 
        } else {
            m=vsip_cmag_d(ps);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_d(L,l,i);vsip_csvmul_d(ps,l,l);
            vsip_cvput_d(d,i,vsip_cmplx_d(m,0));
            if (i < n_f)
                vsip_cvput_d(f,i,vsip_cjmul_d(vsip_cvget_d(f,i),ps));
        }else{
            vsip_cvput_d(d,i,vsip_cmplx_d(0.0,0.0));
        }
    }
    csvdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_cvget_d(f,i);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_d(-1.0,0.0);
            else
                ps= vsip_cmplx_d(1.0,0.0);
            m = vsip_mag_d(m);
        }else{
            m=vsip_cmag_d(ps);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_d(L, l, j);vsip_csvmul_d(vsip_conj_d(ps),l,l);
        crow_sv_d(R,r,j);vsip_csvmul_d(ps,r,r);
        vsip_cvput_d(f,i,vsip_cmplx_d(m,0));
        vsip_cvput_d(f,j,vsip_cmul_d(vsip_cvget_d(f,j),ps));
    }
    j=n_f;
    i=j-1;
    ps=vsip_cvget_d(f,i);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps=vsip_cmplx_d(-1.0,0.0);
        else
            ps= vsip_cmplx_d(1.0,0.0);
        m = vsip_mag_d(m);
    }else{
        m=vsip_cmag_d(ps);
        ps.r /= m; ps.i/=m;
    }
    vsip_cvput_d(f,i,vsip_cmplx_d(m,0.0));
    ccol_sv_d(L, l, j);vsip_csvmul_d(vsip_conj_d(ps),l,l);
    crow_sv_d(R,r,j);vsip_csvmul_d(ps,r,r);
}

svdObj_f svdBidiag_f(vsip_mview_f* A)
{
    svdObj_f retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_f sv = mnormFro_f(A)/(vsip_scalar_f)vsip_mgetrowlength_f(A);
    vsip_mview_f *B=bidiag_f(A); 
    vsip_vview_f *d0=NULL,*f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) d0=vsip_mdiagview_f(B,0); if(!d0) retval.init++;
    if(B) f0=vsip_mdiagview_f(B,1); if(!f0) retval.init++;
    retval.d=vclone_f(d0); if(!retval.d) retval.init++;
    retval.f=vclone_f(f0); if(!retval.f) retval.init++;
    if(B) retval.L=UmatExtract_f(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=VHmatExtract_f(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-7;
    vsip_vdestroy_f(d0);
    vsip_vdestroy_f(f0);
    vsip_malldestroy_f(B);
    biDiagPhaseToZero_f(retval.L,retval.d,retval.f,retval.R,retval.eps0);
    return retval;
}
csvdObj_f csvdBidiag_f(vsip_cmview_f* A)
{
    csvdObj_f retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_f sv = cmnormFro_f(A)/(vsip_scalar_f)vsip_cmgetrowlength_f(A);
    vsip_cmview_f *B=cbidiag_f(A);
    vsip_cvview_f *dc=NULL,*fc=NULL;
    vsip_vview_f *d0=NULL, *f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) dc=vsip_cmdiagview_f(B,0); if(!dc) retval.init++;
    if(dc) d0=vsip_vrealview_f(dc); if(!d0) retval.init++;
    if(B) fc=vsip_cmdiagview_f(B,1); if(!fc) retval.init++;
    if(fc) f0 = vsip_vrealview_f(fc); if(!f0) retval.init++;
    if(B) retval.L=cUmatExtract_f(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=cVHmatExtract_f(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-7;
    cbiDiagPhaseToZero_f(retval.L,dc,fc,retval.R,retval.eps0);
    retval.d=vclone_f(d0); if(!retval.d) retval.init++;
    retval.f=vclone_f(f0); if(!retval.f) retval.init++;
    vsip_vdestroy_f(d0);
    vsip_vdestroy_f(f0);
    vsip_cvdestroy_f(dc);
    vsip_cvdestroy_f(fc);
    vsip_cmalldestroy_f(B);
    return retval;
}
svdObj_d svdBidiag_d(vsip_mview_d* A)
{
    svdObj_d retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_d sv = mnormFro_d(A)/(vsip_scalar_d)vsip_mgetrowlength_d(A);
    vsip_mview_d *B=bidiag_d(A); 
    vsip_vview_d *d0=NULL,*f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) d0=vsip_mdiagview_d(B,0); if(!d0) retval.init++;
    if(B) f0=vsip_mdiagview_d(B,1); if(!f0) retval.init++;
    retval.d=vclone_d(d0); if(!retval.d) retval.init++;
    retval.f=vclone_d(f0); if(!retval.f) retval.init++;
    if(B) retval.L=UmatExtract_d(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=VHmatExtract_d(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-7;
    vsip_vdestroy_d(d0);
    vsip_vdestroy_d(f0);
    vsip_malldestroy_d(B);
    biDiagPhaseToZero_d(retval.L,retval.d,retval.f,retval.R,retval.eps0);
    return retval;
}
csvdObj_d csvdBidiag_d(vsip_cmview_d* A)
{
    csvdObj_d retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_d sv = cmnormFro_d(A)/(vsip_scalar_d)vsip_cmgetrowlength_d(A);
    vsip_cmview_d *B=cbidiag_d(A);
    vsip_cvview_d *dc=NULL,*fc=NULL;
    vsip_vview_d *d0=NULL, *f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) dc=vsip_cmdiagview_d(B,0); if(!dc) retval.init++;
    if(dc) d0=vsip_vrealview_d(dc); if(!d0) retval.init++;
    if(B) fc=vsip_cmdiagview_d(B,1); if(!fc) retval.init++;
    if(fc) f0 = vsip_vrealview_d(fc); if(!f0) retval.init++;
    if(B) retval.L=cUmatExtract_d(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=cVHmatExtract_d(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-7;
    cbiDiagPhaseToZero_d(retval.L,dc,fc,retval.R,retval.eps0);
    retval.d=vclone_d(d0); if(!retval.d) retval.init++;
    retval.f=vclone_d(f0); if(!retval.f) retval.init++;
    vsip_vdestroy_d(d0);
    vsip_vdestroy_d(f0);
    vsip_cvdestroy_d(dc);
    vsip_cvdestroy_d(fc);
    vsip_cmalldestroy_d(B);
    return retval;
}