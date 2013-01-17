/* example.i */
 %module svdUtils
 %{
 /* Put header files here or function declarations like below */
#include "/Library/Frameworks/jvsipF.framework/Headers/vsip.h"
#include "./VU_svdUtils.h"
 %}
typedef unsigned long int vsip_scalar_vi;
typedef vsip_scalar_vi vsip_index;
typedef vsip_scalar_vi vsip_length;
typedef vsip_scalar_vi vsip_offset;
typedef long int vsip_stride;
typedef float vsip_scalar_f;
typedef double vsip_scalar_d;
typedef int vsip_scalar_i;
typedef signed int vsip_scalar_bl;
typedef vsip_scalar_bl vsip_bool;
typedef struct { vsip_scalar_vi r,c; } vsip_scalar_mi;
typedef   signed short  int     vsip_scalar_si;
typedef   unsigned      char    vsip_scalar_uc;
typedef   unsigned      int     vsip_scalar_ue32;
typedef struct { vsip_scalar_d  r, i; } vsip_cscalar_d;
typedef struct { vsip_scalar_f  r, i; } vsip_cscalar_f;
typedef struct { vsip_offset  offset; vsip_stride  stride; vsip_length  length; vsip_block_d* block; } vsip_vattr_d;
typedef struct { vsip_offset  offset; vsip_stride  stride; vsip_length  length; vsip_block_f* block; } vsip_vattr_f;
vsip_mview_f* meye_f(vsip_length);
vsip_cmview_f* cmeye_f(vsip_length);
vsip_mview_d* meye_d(vsip_length);
vsip_cmview_d* cmeye_d(vsip_length);
vsip_scalar_f sign_f(vsip_scalar_f);
vsip_cscalar_f csign_f(vsip_cscalar_f);
vsip_scalar_d sign_d(vsip_scalar_d);
vsip_cscalar_d csign_d(vsip_cscalar_d);
int bidiag_f( vsip_mview_f*, vsip_mview_f*, vsip_vview_f*, vsip_vview_f*, vsip_mview_f *);
vsip_scalar_f vnormFro_f(vsip_vview_f*);
vsip_scalar_f vnorm2_f(vsip_vview_f*);
vsip_scalar_f cvnorm2_f(vsip_cvview_f*);
vsip_scalar_d vnormFro_d(vsip_vview_d*);
vsip_scalar_d vnorm2_d(vsip_vview_d*);
vsip_scalar_d cvnorm2_d(vsip_cvview_d*);
vsip_scalar_f mnormFro_f(vsip_mview_f*);
vsip_scalar_d mnormFro_d(vsip_mview_d*);
vsip_scalar_f cvnormFro_f(vsip_cvview_f*);
vsip_scalar_d cvnormFro_d(vsip_cvview_d*);
vsip_scalar_f cmnormFro_f(vsip_cmview_f*);
vsip_scalar_d cmnormFro_d(vsip_cmview_d*);
vsip_scalar_f meig_f(vsip_mview_f*);
vsip_scalar_d meig_d(vsip_mview_d*);
vsip_scalar_f cmeig_f(vsip_cmview_f*);
vsip_scalar_d cmeig_d(vsip_cmview_d*);
vsip_vview_f* houseVector_f(vsip_vview_f*);
vsip_vview_d* houseVector_d(vsip_vview_d*);
vsip_cvview_f* chouseVector_f(vsip_cvview_f*);
vsip_cvview_d* chouseVector_d(vsip_cvview_d*);
void houseProd_f(vsip_vview_f*,vsip_mview_f*);
void prodHouse_f(vsip_mview_f*,vsip_vview_f*);
void chouseProd_f(vsip_cvview_f*,vsip_cmview_f*);
void cprodHouse_f(vsip_cmview_f*,vsip_cvview_f*);
void houseProd_d(vsip_vview_d*,vsip_mview_d*);
void prodHouse_d(vsip_mview_d*,vsip_vview_d*);
void chouseProd_d(vsip_cvview_d*,vsip_cmview_d*);
void cprodHouse_d(vsip_cmview_d*,vsip_cvview_d*);