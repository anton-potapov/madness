/*
 * libxc.h
 *
 *  Created on: Nov 23, 2008
 *      Author: wsttiger
 */

#ifndef LIBXC_H_
#define LIBXC_H_

//#define WORLD_INSTANTIATE_STATIC_TEMPLATES
#include <mra/mra.h>
#include <world/world.h>
#include "xc.h"
#include "lda.h"

using namespace madness;

//***************************************************************************
static double munge(double r) {
  if (r < 1e-15) r = 2e-15;
  return r;
}
//***************************************************************************

//***************************************************************************
inline static void ldaop(const Key<3>& key, Tensor<double>& t) {
    UNARY_OPTIMIZED_ITERATOR(double, t, double r=munge(2.0* *_p0); double q; double dq1; double dq2;x_rks_s__(&r, &q, &dq1);c_rks_vwn5__(&r, &q, &dq2); *_p0 = dq1+dq2);
}
//***************************************************************************

//***************************************************************************
inline static void ldaeop(const Key<3>& key, Tensor<double>& t) {
    UNARY_OPTIMIZED_ITERATOR(double, t, double r=munge(2.0* *_p0); double q1; double q2; double dq;x_rks_s__(&r, &q1, &dq);c_rks_vwn5__(&r, &q2, &dq); *_p0 = q1+q2);
}
//***************************************************************************

//***************************************************************************
inline static void libxc_ldaop(const Key<3>& key, Tensor<double>& t) {
  XC(lda_type) xc_c_func;
  XC(lda_type) xc_x_func;
  xc_lda_init(&xc_c_func, XC_LDA_C_VWN,XC_UNPOLARIZED);
  xc_lda_x_init(&xc_x_func, XC_UNPOLARIZED, 3, 0);
  UNARY_OPTIMIZED_ITERATOR(double, t, double r=munge(2.0* *_p0); double q; double dq1; double dq2;
                           xc_lda_vxc(&xc_x_func, &r, &q, &dq1); xc_lda_vxc(&xc_c_func, &r, &q, &dq2);
                           *_p0 = dq1+dq2);
}
//***************************************************************************

//***************************************************************************
inline static void libxc_ldaop_sp(const Key<3>& key, Tensor<double>& t, Tensor<double>& a, Tensor<double>& b)
{
//  XC(lda_type) xc_c_func;
//  XC(lda_type) xc_x_func;
//  xc_lda_init(&xc_c_func, XC_LDA_C_VWN,XC_POLARIZED);
//  xc_lda_x_init(&xc_x_func, XC_POLARIZED, 3, 0);
//  TERNARY_OPTIMIZED_ITERATOR(double, t, double, a, double, b, double r[2]; r[0] = munge(*_p1);
//                             r[1] = munge(*_p2); double q[2]; double dq1[2]; double dq2[2];
//                             xc_lda_vxc(&xc_x_func, &r[0], &q[0], &dq1[0]); xc_lda_vxc(&xc_c_func, &r[0], &q[0], &dq2[0]);
//                             *_p0 = dq1[0]+dq2[0]);

    xc_lda_type xc_c_func;
    xc_lda_type xc_x_func;
    xc_lda_init(&xc_c_func, 7, 2);
    xc_lda_x_init(&xc_x_func, 2, 3, 0);
    do
    {
      if (t.iscontiguous() && a.iscontiguous() && b.iscontiguous() && t.size
          == a.size && t.size == b.size)
      {
        print("is contiguous\n\n");
        double* __restrict _p0 = t.ptr();
        double* __restrict _p1 = a.ptr();
        double* __restrict _p2 = b.ptr();
        for (long _j = 0; _j < t.size; _j++, _p0++, _p1++, _p2++)
        {
          double r[2];
          r[0] = munge(2.0 * *_p1);
          r[1] = munge(2.0 * *_p2);
          double q[2];
          double dq1[2];
          double dq2[2];
          xc_lda_vxc(&xc_x_func, &r[0], &q[0], &dq1[0]);
          xc_lda_vxc(&xc_c_func, &r[0], &q[0], &dq2[0]);
          *_p0 = dq1[0] + dq2[0];
        }
      }
      else
      {
        for (TensorIterator<double, double, double> iter = t.ternary_iterator(
            a, b, 1); iter._p0; ++iter)
        {
          long _dimj = iter.dimj;
          double* _p0 = iter._p0;
          double* _p1 = iter._p1;
          double* _p2 = iter._p2;
          long _s0 = iter._s0;
          long _s1 = iter._s1;
          long _s2 = iter._s2;
          for (long _j = 0; _j < _dimj; _j++, _p0 += _s0, _p1 += _s1, _p2
              += _s2)
          {
            double r[2];
            r[0] = munge(2.0 * *_p1);
            r[1] = munge(2.0 * *_p2);
            double q[2];
            double dq1[2];
            double dq2[2];
            xc_lda_vxc(&xc_x_func, &r[0], &q[0], &dq1[0]);
            xc_lda_vxc(&xc_c_func, &r[0], &q[0], &dq2[0]);
            *_p0 = dq1[0] + dq2[0];
          }
        }
      }
    } while (0);
  }
//***************************************************************************

////***************************************************************************
//inline static void libxc_ldaeop_sp(const Key<3>& key, Tensor<double>& t) {
//  XC(lda_type) xc_c_func;
//  XC(lda_type) xc_x_func;
//  xc_lda_init(&xc_c_func, XC_LDA_C_VWN,XC_UNPOLARIZED);
//  xc_lda_x_init(&xc_x_func, XC_UNPOLARIZED, 3, 0);
//  UNARY_OPTIMIZED_ITERATOR(double, t, double r=munge(2.0* *_p0); double q1; double q2; double dq; xc_lda_vxc(&xc_x_func, &r, &q1, &dq); xc_lda_vxc(&xc_c_func, &r, &q2, &dq); *_p0 = q1+q2);
//}
////***************************************************************************

//const double THRESH_RHO = 1e-8;
//const double THRESH_GRHO = 1e-20;
//
////***************************************************************************
//inline void wst_munge_grho(int npoint, double *rho, double *grho) {
//    for (int i=0; i<npoint; i++) {
//        if (rho[i]<THRESH_RHO) rho[i] = THRESH_RHO;
//        if ((rho[i] <=THRESH_RHO) ||
//            (grho[i] < THRESH_GRHO)) grho[i] = THRESH_GRHO;
//    }
//}
////***************************************************************************
//
////***************************************************************************
//inline void wst_munge_rho(int npoint, double *rho) {
//    for (int i=0; i<npoint; i++) {
//        if (rho[i]<THRESH_RHO) rho[i] = THRESH_RHO;
//    }
//}
////***************************************************************************
//
////***************************************************************************
//inline void xc_generic_lda(Tensor<double> rho_alpha,           ///< Alpha-spin density at each grid point
//                          Tensor<double> f,                         ///< Value of functional at each grid point
//                          Tensor<double> df_drho,                   ///< Derivative of functional w.r.t. rho_alpha
//                          bool spinpol)
//    {
//    MADNESS_ASSERT(rho_alpha.iscontiguous());
//    MADNESS_ASSERT(f.iscontiguous());
//    MADNESS_ASSERT(df_drho.iscontiguous());
//
//    rho_alpha = rho_alpha.flat();
//    f = f.flat();
//    df_drho = df_drho.flat();
//
//    XC(lda_type) xc_c_func;
//    XC(lda_type) xc_x_func;
//
//    int npt = rho_alpha.dim[0];
//
//    Tensor<double> tf(npt);
//    Tensor<double> tdf_drho(npt);
//    double* rhoptr = rho_alpha.ptr();
//    double* tfptr = tf.ptr();
//    double* tdf_drhoptr = tdf_drho.ptr();
//
//    tf.fill(0.0);
//    tdf_drho.fill(0.0);
//    f.fill(0.0);
//    df_drho.fill(0.0);
//
//    wst_munge_rho(npt, rhoptr);
//
//    xc_lda_init(&xc_c_func, XC_LDA_C_VWN,XC_UNPOLARIZED);
//    for (int i = 0; i < npt; i++)
//    {
//      xc_lda_vxc(&xc_c_func, &rhoptr[i], &tfptr[i], &tdf_drhoptr[i]);
//    }
//
//    f.gaxpy(1.0, tf, 1.0);
//    df_drho.gaxpy(1.0, tdf_drho, 1.0);
//
//    tf.fill(0.0);
//    tdf_drho.fill(0.0);
//
//    xc_lda_x_init(&xc_x_func, XC_UNPOLARIZED, 3, 0);
//    for (int i = 0; i < npt; i++)
//    {
//      xc_lda_vxc(&xc_x_func, &rhoptr[i], &tfptr[i], &tdf_drhoptr[i]);
//    }
//
//    f.gaxpy(1.0, tf, 1.0);
//    df_drho.gaxpy(1.0, tdf_drho, 1.0);
//}
//  //***************************************************************************
//
//  //***************************************************************************
//  template <int NDIM>
// inline void xc_lda_V(const Key<NDIM>& key, Tensor<double>& t)
//  {
//    Tensor<double> enefunc = copy(t);
//    Tensor<double> V = copy(t);
//    ::xc_generic_lda(t, enefunc, V, false);
//    t(___) = V(___);
//  }
//  //***************************************************************************
//
//  //***************************************************************************
//  template <int NDIM>
// inline void xc_lda_ene(const Key<NDIM>& key, Tensor<double>& t)
//  {
//    Tensor<double> V = copy(t);
//    Tensor<double> enefunc = copy(t);
//    ::xc_generic_lda(t, enefunc, V, false);
//    t(___) = enefunc(___);
//  }
//  //***************************************************************************



#endif /* LIBXC_H_ */
