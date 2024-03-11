//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: MercedesBenz.cpp
//
// Code generated for Simulink model 'MercedesBenz'.
//
// Model version                  : 1.36
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Feb  9 23:14:40 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "MercedesBenz.h"
#define NumBitsPerChar                 8U

// Private macros used by the generated code to access rtModel
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern real_T rt_powd_snf(real_T u0, real_T u1);
static void LookUpEven_real_T_real_T(real_T *pY, const real_T *pYData, real_T u,
  real_T valueLo, uint32_T iHi, real_T uSpacing);
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  // tMinusDelay = currentSimTime - delay
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
  ;
static void BINARYSEARCH_real_T(uint32_T *piLeft, uint32_T *piRght, real_T u,
  const real_T *pData, uint32_T iHi);

// private model entry point functions
extern void MercedesBenz_derivatives();

//===========*
//  Constants *
// ===========
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

//
//  UNUSED_PARAMETER(x)
//    Used to specify that a function parameter (argument) is required but not
//    accessed by the function body.

#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   // do nothing
# else

//
//  This is the semi-ANSI standard way of indicating that an
//  unused function parameter is required.

#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

extern "C" {

#ifndef INTERP
# define INTERP(x,x1,x2,y1,y2)         ( (y1)+(((y2) - (y1))/((x2) - (x1)))*((x)-(x1)) )
#endif

#ifndef ZEROTECHNIQUE
#define ZEROTECHNIQUE

  typedef enum {
    NORMAL_INTERP,
    AVERAGE_VALUE,
    MIDDLE_VALUE
  } ZeroTechnique;

#endif

  static int_T rt_GetLookupIndex(const real_T *x, int_T xlen, real_T u) ;
}                                      // extern "C"
  extern "C"
{
  static real_T rt_Lookup(const real_T *x, int_T xlen, real_T u, const real_T *y);
}                                      // extern "C"

extern "C" {
  static real_T rt_Lookup2D_Normal (const real_T *xVals, const int_T numX,
    const real_T *yVals, const int_T numY,
    const real_T *zVals,
    const real_T x, const real_T y);
}                                      // extern "C"
  extern "C"
{
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}

extern "C" {
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf = 0.0;
    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf = 0.0;
    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}
  extern "C"
{
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetNaN(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan = 0.0;
    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetNaNF(void)
  {
    IEEESingle nanF = { { 0 } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}

extern "C" {
  //
  // Routine to get the index of the input from a table using binary or
  // interpolation search.
  //
  // Inputs:
  //   *x   : Pointer to table, x[0] ....x[xlen-1]
  //   xlen : Number of values in xtable
  //   u    : input value to look up
  //
  // Output:
  //   idx  : the index into the table such that:
  //         if u is negative
  //            x[idx] <= u < x[idx+1]
  //         else
  //            x[idx] < u <= x[idx+1]
  //
  // Interpolation Search: If the table contains a large number of nearly
  // uniformly spaced entries, i.e., x[n] vs n is linear then the index
  // corresponding to the input can be found in one shot using the linear
  // interpolation formula. Therefore if you have a look-up table block with
  // many data points, using interpolation search might speed up the code.
  // Compile the generated code with the following flag:
  //
  //            make_rtw OPTS=-DDOINTERPSEARCH
  //
  // to enable interpolation search.
  //
  static int_T rt_GetLookupIndex(const real_T *x, int_T xlen, real_T u)
  {
    int_T idx = 0;
    int_T bottom = 0;
    int_T top = xlen-1;
    int_T retValue = 0;
    boolean_T returnStatus = 0U;

#ifdef DOINTERPSEARCH

    real_T offset = 0;

#endif

    //
    //  Deal with the extreme cases first:
    //    if u <= x[bottom] then return idx = bottom
    //    if u >= x[top]    then return idx = top-1

    if (u <= x[bottom]) {
      retValue = bottom;
      returnStatus = 1U;
    } else if (u >= x[top]) {
      retValue = top-1;
      returnStatus = 1U;
    } else {
      // else required to ensure safe programming, even *
      //  if it's expected that it will never be reached
    }

    if (returnStatus == 0U) {
      if (u < 0) {
        // For negative input find index such that: x[idx] <= u < x[idx+1]
        for (;;) {

#ifdef DOINTERPSEARCH

          offset = (u-x[bottom])/(x[top]-x[bottom]);
          idx = bottom + (int_T)((top-bottom)*(offset-DBL_EPSILON));

#else

          idx = (bottom + top)/2;

#endif

          if (u < x[idx]) {
            top = idx - 1;
          } else if (u >= x[idx+1]) {
            bottom = idx + 1;
          } else {
            // we have x[idx] <= u < x[idx+1], return idx
            retValue = idx;
            break;
          }
        }
      } else {
        // For non-negative input find index such that: x[idx] < u <= x[idx+1]
        for (;;) {

#ifdef DOINTERPSEARCH

          offset = (u-x[bottom])/(x[top]-x[bottom]);
          idx = bottom + (int_T)((top-bottom)*(offset-DBL_EPSILON));

#else

          idx = (bottom + top)/2;

#endif

          if (u <= x[idx]) {
            top = idx - 1;
          } else if (u > x[idx+1]) {
            bottom = idx + 1;
          } else {
            // we have x[idx] < u <= x[idx+1], return idx
            retValue = idx;
            break;
          }
        }
      }
    }

    return retValue;
  }
}                                      // extern "C"
  extern "C"
{
  // 1D lookup routine for data type of real_T.
  static real_T rt_Lookup(const real_T *x, int_T xlen, real_T u, const real_T *y)
  {
    int_T idx = rt_GetLookupIndex(x, xlen, u);
    real_T num = y[idx+1] - y[idx];
    real_T den = x[idx+1] - x[idx];

    // Due to the way the binary search is implemented
    // in rt_look.c (rt_GetLookupIndex), den cannot be
    // 0.  Equivalently, m cannot be inf or nan.
    real_T m = num/den;
    return (y[idx] + (m * (u - x[idx])));
  }
}                                      // extern "C"

extern "C" {
  // 2D normal lookup routine for data type of real_T.
  static real_T rt_Lookup2D_Normal(const real_T *xVals, const int_T numX,
    const real_T *yVals, const int_T numY,
    const real_T *zVals,
    const real_T x, const real_T y)
  {
    int_T xIdx, yIdx;
    real_T ylo, yhi;
    real_T Zx0yhi, Zx0ylo, xlo, xhi;
    real_T corner1, corner2;
    xIdx = rt_GetLookupIndex(xVals,numX,x);
    xlo = xVals[xIdx];
    xhi = xVals[xIdx+1];
    yIdx = rt_GetLookupIndex(yVals,numY,y);
    ylo = yVals[yIdx];
    yhi = yVals[yIdx+1];
    corner1 = *(zVals + xIdx + (numX * yIdx));
    corner2 = *(zVals + (xIdx+1) + (numX * yIdx));
    Zx0ylo = INTERP(x, xlo, xhi, corner1, corner2);
    corner1 = *(zVals + xIdx + (numX * (yIdx+1)));
    corner2 = *(zVals + (xIdx+1) + (numX*(yIdx+1)));
    Zx0yhi = INTERP(x, xlo, xhi, corner1, corner2);
    return (INTERP(y,ylo,yhi,Zx0ylo,Zx0yhi));
  }
}                                      // extern "C"
  extern "C"
{
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  static void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  static boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  static boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  static boolean_T rtIsNaN(real_T value)
  {
    boolean_T result = (boolean_T) 0;
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  // Test if single-precision value is not a number
  static boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}

// Lookup 1D UtilityLookUpEven_real_T_real_T
static void LookUpEven_real_T_real_T(real_T *pY, const real_T *pYData, real_T u,
  real_T valueLo, uint32_T iHi, real_T uSpacing)
{
  if (u <= valueLo ) {
    (*pY) = (*pYData);
  } else {
    real_T uAdjusted = u - valueLo;
    real_T tmpIdxLeft = uAdjusted / uSpacing;
    uint32_T iLeft = (uint32_T)tmpIdxLeft;
    if ((tmpIdxLeft >= 4294967296.0) || (iLeft >= iHi) ) {
      (*pY) = pYData[iHi];
    } else {
      {
        real_T lambda;

        {
          real_T num = (real_T)uAdjusted - ( iLeft * uSpacing );
          lambda = num / uSpacing;
        }

        {
          real_T yLeftCast;
          real_T yRghtCast;
          yLeftCast = pYData[iLeft];
          yRghtCast = pYData[((iLeft)+1)];
          yLeftCast += lambda * ( yRghtCast - yLeftCast );
          (*pY) = yLeftCast;
        }
      }
    }
  }
}

//
// Time delay interpolation routine
//
// The linear interpolation is performed using the formula:
//
//          (t2 - tMinusDelay)         (tMinusDelay - t1)
// u(t)  =  ----------------- * u1  +  ------------------- * u2
//              (t2 - t1)                  (t2 - t1)
//
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  // tMinusDelay = currentSimTime - delay
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  //
  //  If there is only one data point in the buffer, this data point must be
  //  the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
  //  guess if initial output as well

  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  //
  //  If tMinusDelay is less than zero, should output initial value

  if (tMinusDelay <= tStart)
    return initOutput;

  // For fixed buffer extrapolation:
  //  if tMinusDelay is small than the time at oldestIdx, if discrete, output
  //  tailptr value,  else use tailptr and tailptr+1 value to extrapolate
  //  It is also for fixed buffer. Note: The same condition can happen for transport delay block where
  //  use tStart and and t[tail] other than using t[tail] and t[tail+1].
  //  See below

  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        //
        //  Use Lagrange's interpolation formula.  Exact outputs at t1, t2.

        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  //
  //  When block does not have direct feedthrough, we use the table of
  //  values to extrapolate off the end of the table for delays that are less
  //  than 0 (less then step size).  This is not completely accurate.  The
  //  chain of events is as follows for a given time t.  Major output - look
  //  in table.  Update - add entry to table.  Now, if we call the output at
  //  time t again, there is a new entry in the table. For very small delays,
  //  this means that we will have a different answer from the previous call
  //  to the output fcn at the same time t.  The following code prevents this
  //  from happening.

  if (minorStepAndTAtLastMajorOutput) {
    // pretend that the new entry has not been added to table
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    // Look forward starting at last index
    while (tBuf[i] < tMinusDelay) {
      // May occur if the delay is less than step-size - extrapolate
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;// move through buffer
    }
  } else {
    //
    //  Look backwards starting at last index which can happen when the
    //  delay time increases.

    while (tBuf[i] >= tMinusDelay) {
      //
      //  Due to the entry condition at top of function, we
      //  should never hit the end.

      i = (i > 0) ? i-1 : (bufSz-1);   // move through buffer
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    //
    //  tempEps = 128 * eps;
    //  localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;

    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * std::abs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      //
      //  Use Lagrange's interpolation formula.  Exact outputs at t1, t2.

      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

// Lookup Binary Search Utility BINARYSEARCH_real_T
static void BINARYSEARCH_real_T(uint32_T *piLeft, uint32_T *piRght, real_T u,
  const real_T *pData, uint32_T iHi)
{
  // Find the location of current input value in the data table.
  *piLeft = 0U;
  *piRght = iHi;
  if (u <= pData[0] ) {
    // Less than or equal to the smallest point in the table.
    *piRght = 0U;
  } else if (u >= pData[iHi] ) {
    // Greater than or equal to the largest point in the table.
    *piLeft = iHi;
  } else {
    uint32_T i;

    // Do a binary search.
    while (( *piRght - *piLeft ) > 1U ) {
      // Get the average of the left and right indices using to Floor rounding.
      i = (*piLeft + *piRght) >> 1;

      // Move either the right index or the left index so that
      //  LeftDataPoint <= CurrentValue < RightDataPoint
      if (u < pData[i] ) {
        *piRght = i;
      } else {
        *piLeft = i;
      }
    }
  }
}

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void MercedesBenzModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 19;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  MercedesBenz_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  MercedesBenz_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  MercedesBenz_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S2>/MATLAB Function'
int32_T MercedesBenzModelClass::bsearch(const real_T x[10], real_T xi)
{
  int32_T n;
  int32_T low_ip1;
  int32_T high_i;
  int32_T mid_i;
  n = 1;
  low_ip1 = 2;
  high_i = 10;
  while (high_i > low_ip1) {
    mid_i = (n + high_i) >> 1;
    if (xi >= x[mid_i - 1]) {
      n = mid_i;
      low_ip1 = mid_i + 1;
    } else {
      high_i = mid_i;
    }
  }

  return n;
}

// Model step function
void MercedesBenzModelClass::step()
{
  // local block i/o variables
  real_T rtb_interp_down;
  real_T rtb_interp_up;
  real_T rtb_TransferFcn;
  real_T rtb_DotProduct2;
  real_T rtb_vx;
  real_T rtb_TSamp;
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_o;
  real_T rtb_FilterCoefficient_d;
  real_T rtb_GearNr_;
  real_T rtb_IntegralGain;
  real_T rtb_IntegralGain_f;
  real_T rtb_IntegralGain_j;
  real_T A1[10];
  real_T Z[10];
  int32_T n;
  int32_T low_i;
  int32_T low_ip1;
  int32_T high_i;
  int32_T mid_i;
  static const real_T Yq[10] = { 0.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0,
    90.0, 100.0 };

  real_T rtb_Fcn16;
  real_T rtb_Fcn15;
  real_T rtb_Divide_k;
  real_T rtb_TransferFcn_o;
  real_T rtb_DotProduct;
  real_T rtb_TransmissionOut_rpm;
  real_T rtb_SpeedRatio;
  real_T rtb_Quotient;
  real_T rtb_Switch_m;
  real_T rtb_Filter_a;
  real_T rtb_DotProduct1;
  real_T rtb_Integrator_n;
  real_T rtb_Torsionaldamping;
  boolean_T rtb_ManualSwitch1;
  boolean_T rtb_LogicalOperator1;
  int8_T rtAction;
  real_T rtb_Merge;
  real_T rtb_Integrator;
  real_T rtb_Integrator_h5;
  real_T Product;
  static const real_T Yq_0[10] = { 0.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0,
    90.0, 100.0 };

  static const int8_T b[10] = { 0, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

  static const int16_T X_0[16] = { 700, 800, 1000, 1025, 1050, 1075, 1100, 1125,
    1250, 1375, 1500, 1625, 1750, 1875, 2000, 2300 };

  static const int16_T V[160] = { -40, 621, 689, 756, 982, 1262, 1487, 1739,
    1964, 2244, -44, 628, 699, 770, 1006, 1283, 1519, 1777, 2013, 2290, -54, 643,
    721, 798, 1055, 1325, 1583, 1853, 2111, 2380, -55, 645, 723, 801, 1061, 1331,
    1591, 1863, 2123, 2392, -56, 646, 725, 803, 1065, 1333, 1595, 1868, 2130,
    2399, -58, 645, 724, 803, 1066, 1333, 1596, 1869, 2132, 2398, -59, 644, 723,
    803, 1066, 1332, 1596, 1869, 2133, 2398, -60, 643, 722, 802, 1066, 1330,
    1595, 1868, 2132, 2396, -63, 635, 713, 792, 1053, 1314, 1575, 1844, 2105,
    2366, -66, 256, 513, 778, 1034, 1291, 1547, 1813, 2069, 2326, -72, 251, 503,
    762, 1014, 1265, 1517, 1776, 2028, 2279, -77, 247, 487, 734, 973, 1221, 1460,
    1708, 1947, 2194, -83, 224, 456, 681, 913, 1137, 1369, 1594, 1826, 2050, -88,
    211, 422, 634, 845, 1056, 1267, 1478, 1690, 1901, -95, 180, 345, 525, 705,
    870, 1050, 1230, 1395, 1575, -112, 105, 159, 264, 369, 424, 527, 634, 688,
    793 };

  int32_T exitg1;
  if (rtmIsMajorTimeStep((&rtM))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&rtM))) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  // Product: '<S25>/Product' incorporates:
  //   Inport: '<Root>/initial_speed'
  //   Step: '<S30>/Step'

  Product = static_cast<real_T>((&rtM)->Timing.t[0] < 0.0001) *
    rtU.initial_speed;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Outport: '<Root>/output_location' incorporates:
    //   DiscreteIntegrator: '<S10>/Discrete-Time Integrator1'
    //   Sum: '<S10>/Sum3'

    rtY.output_location = rtDW.DiscreteTimeIntegrator1_DSTATE[0] + 150.0;

    // Memory: '<S25>/Memory1'
    rtb_vx = rtDW.Memory1_PreviousInput;

    // DiscreteIntegrator: '<S19>/Discrete-Time Integrator'
    if (rtDW.DiscreteTimeIntegrator_IC_LOADI != 0) {
      rtDW.DiscreteTimeIntegrator_DSTATE = Product;
    }

    if ((rtb_vx != 0.0) || (rtDW.DiscreteTimeIntegrator_PrevRese != 0)) {
      rtDW.DiscreteTimeIntegrator_DSTATE = Product;
    }

    rtDW.vx_ms1 = rtDW.DiscreteTimeIntegrator_DSTATE;

    // End of DiscreteIntegrator: '<S19>/Discrete-Time Integrator'

    // Fcn: '<Root>/Fcn1'
    rtb_Filter_a = rtDW.vx_ms1;

    // Outport: '<Root>/output_speed' incorporates:
    //   Fcn: '<Root>/Fcn1'

    rtY.output_speed = rtDW.vx_ms1;

    // SampleTimeMath: '<S76>/TSamp'
    //
    //  About '<S76>/TSamp':
    //   y = u * K where K = 1 / ( w * Ts )

    rtb_TSamp = rtDW.vx_ms1 * 10.0;

    // Outport: '<Root>/output_acceleration' incorporates:
    //   Fcn: '<Root>/Fcn2'
    //   Sum: '<S76>/Diff'
    //   UnitDelay: '<S76>/UD'
    //
    //  Block description for '<S76>/Diff':
    //
    //   Add in CPU
    //
    //  Block description for '<S76>/UD':
    //
    //   Store in Global RAM

    rtY.output_acceleration = rtb_TSamp - rtDW.UD_DSTATE;

    // Abs: '<S3>/Abs'
    rtDW.Abs = std::abs(rtDW.vx_ms1);

    // Signum: '<S16>/Sign'
    if (rtDW.vx_ms1 < 0.0) {
      rtb_TransferFcn_o = -1.0;
    } else if (rtDW.vx_ms1 > 0.0) {
      rtb_TransferFcn_o = 1.0;
    } else if (rtDW.vx_ms1 == 0.0) {
      rtb_TransferFcn_o = 0.0;
    } else {
      rtb_TransferFcn_o = (rtNaN);
    }

    // End of Signum: '<S16>/Sign'

    // Gain: '<S3>/SteerRatio' incorporates:
    //   Gain: '<S13>/Gain1'
    //   Lookup: '<S16>/Lookup Table'
    //   MultiPortSwitch: '<S16>/Multiport Switch'
    //   Product: '<S16>/Product'

    rtDW.DeltaWheel_rad = rtb_TransferFcn_o * rt_Lookup
      (rtConstP.LookupTable_XData, 4, rtDW.vx_ms1, rtConstP.LookupTable_YData) *
      0.0 * 0.017453292519943295 * 0.04;

    // RelationalOperator: '<S48>/Compare' incorporates:
    //   Constant: '<S48>/Constant'

    rtDW.Compare_n = (rtDW.Abs == 0.0);
  }

  // Integrator: '<S49>/Integrator'
  // Limited  Integrator
  if (rtmIsMajorTimeStep((&rtM))) {
    rtb_ManualSwitch1 = (((rtPrevZCX.Integrator_Reset_ZCE == 1) !=
                          static_cast<int32_T>(rtDW.Compare_n)) &&
                         (rtPrevZCX.Integrator_Reset_ZCE != 3));
    rtPrevZCX.Integrator_Reset_ZCE = rtDW.Compare_n;

    // evaluate zero-crossings and the level of the reset signal
    if (rtb_ManualSwitch1 || rtDW.Compare_n) {
      rtX.Integrator_CSTATE = 0.0;
    }
  }

  if (rtX.Integrator_CSTATE >= 1.0) {
    if (rtX.Integrator_CSTATE > 1.0) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&rtM)->solverInfo, true);
    }

    rtX.Integrator_CSTATE = 1.0;
  } else {
    if (rtX.Integrator_CSTATE <= -1.0) {
      if (rtX.Integrator_CSTATE < -1.0) {
        rtsiSetBlockStateForSolverChangedAtMajorStep(&(&rtM)->solverInfo, true);
      }

      rtX.Integrator_CSTATE = -1.0;
    }
  }

  rtb_Fcn16 = rtX.Integrator_CSTATE;
  if (rtmIsMajorTimeStep((&rtM))) {
    // RelationalOperator: '<S36>/Compare' incorporates:
    //   Constant: '<S36>/Constant'

    rtDW.Compare_e = (rtDW.Abs == 0.0);
  }

  // Integrator: '<S37>/Integrator' incorporates:
  //   Integrator: '<S39>/Integrator'

  if (rtmIsMajorTimeStep((&rtM))) {
    rtb_ManualSwitch1 = (((rtPrevZCX.Integrator_Reset_ZCE_h == 1) !=
                          static_cast<int32_T>(rtDW.Compare_e)) &&
                         (rtPrevZCX.Integrator_Reset_ZCE_h != 3));
    rtPrevZCX.Integrator_Reset_ZCE_h = rtDW.Compare_e;

    // evaluate zero-crossings and the level of the reset signal
    if (rtb_ManualSwitch1 || rtDW.Compare_e) {
      rtX.Integrator_CSTATE_l = 0.0;
    }

    rtb_ManualSwitch1 = (((rtPrevZCX.Integrator_Reset_ZCE_f == 1) !=
                          static_cast<int32_T>(rtDW.Compare_e)) &&
                         (rtPrevZCX.Integrator_Reset_ZCE_f != 3));
    rtPrevZCX.Integrator_Reset_ZCE_f = rtDW.Compare_e;

    // evaluate zero-crossings and the level of the reset signal
    if (rtb_ManualSwitch1 || rtDW.Compare_e) {
      rtX.Integrator_CSTATE_c = 0.0;
    }
  }

  rtb_Integrator = rtX.Integrator_CSTATE_l;

  // Integrator: '<S39>/Integrator'
  rtDW.Integrator = rtX.Integrator_CSTATE_c;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Outputs for Enabled SubSystem: '<S47>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S54>/Enable'

    if (rtmIsMajorTimeStep((&rtM))) {
      // RelationalOperator: '<S53>/Compare' incorporates:
      //   Abs: '<S47>/Abs'
      //   Constant: '<S53>/Constant'

      if (std::abs(rtDW.Abs) > 0.0) {
        rtDW.EnabledSubsystem_MODE_k = true;
      } else {
        if (rtDW.EnabledSubsystem_MODE_k) {
          // Disable for Outport: '<S54>/Alpha'
          rtDW.AlphaFront = 0.0;
          rtDW.EnabledSubsystem_MODE_k = false;
        }
      }

      // End of RelationalOperator: '<S53>/Compare'
    }

    // End of Outputs for SubSystem: '<S47>/Enabled Subsystem'
  }

  // Outputs for Enabled SubSystem: '<S47>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S54>/Enable'

  if (rtDW.EnabledSubsystem_MODE_k) {
    // Fcn: '<S54>/AlphaFront' incorporates:
    //   Integrator: '<S37>/Integrator'

    rtDW.AlphaFront = -std::atan((rtDW.Integrator * 0.87000000000000011 +
      rtX.Integrator_CSTATE_l) / rtDW.Abs);
  }

  // End of Outputs for SubSystem: '<S47>/Enabled Subsystem'
  if (rtmIsMajorTimeStep((&rtM))) {
    // Lookup: '<S52>/Lookup Table'
    //
    //  About '<S52>/Lookup Table':
    //  Input0  Data Type:  Floating Point real_T
    //  Output0 Data Type:  Floating Point real_T
    //  Lookup Method: Linear_Endpoint
    //
    //  XData is inlined and evenly spaced, so the algorithm only needs
    //  the value of the first element, the last element, and the spacing.
    //  For efficiency, XData is excluded from the generated code.
    //  YData parameter uses the same data type and scaling as Output0

    LookUpEven_real_T_real_T( &(rtDW.LookupTable), rtConstP.pooled12, rtDW.Abs,
      0.0, 1U, 2.5);
  }

  // Product: '<S52>/Divide' incorporates:
  //   Sum: '<S14>/Sum'

  rtb_Fcn15 = (rtDW.AlphaFront + rtDW.DeltaWheel_rad) * rtDW.LookupTable;

  // Integrator: '<S50>/Integrator'
  if (rtmIsMajorTimeStep((&rtM))) {
    rtb_ManualSwitch1 = (((rtPrevZCX.Integrator_Reset_ZCE_e == 1) !=
                          static_cast<int32_T>(rtDW.Compare_n)) &&
                         (rtPrevZCX.Integrator_Reset_ZCE_e != 3));
    rtPrevZCX.Integrator_Reset_ZCE_e = rtDW.Compare_n;

    // evaluate zero-crossings and the level of the reset signal
    if (rtb_ManualSwitch1 || rtDW.Compare_n) {
      rtX.Integrator_CSTATE_d = 0.0;
    }
  }

  rtb_DotProduct1 = rtX.Integrator_CSTATE_d;

  // Sum: '<S14>/Sum1' incorporates:
  //   Gain: '<S14>/K_gamma_front'
  //   Gain: '<S14>/front_tyre'
  //   Integrator: '<S49>/Integrator'
  //   Integrator: '<S50>/Integrator'
  //   Product: '<S14>/Product'

  rtb_DotProduct = 0.0 * rtX.Integrator_CSTATE_d * 0.0 + 305920.0 *
    rtX.Integrator_CSTATE;
  if (rtmIsMajorTimeStep((&rtM))) {
    // RelationalOperator: '<S58>/Compare' incorporates:
    //   Constant: '<S58>/Constant'

    rtDW.Compare_g = (rtDW.Abs == 0.0);
  }

  // Integrator: '<S60>/Integrator'
  // Limited  Integrator
  if (rtmIsMajorTimeStep((&rtM))) {
    rtb_ManualSwitch1 = (((rtPrevZCX.Integrator_Reset_ZCE_j == 1) !=
                          static_cast<int32_T>(rtDW.Compare_g)) &&
                         (rtPrevZCX.Integrator_Reset_ZCE_j != 3));
    rtPrevZCX.Integrator_Reset_ZCE_j = rtDW.Compare_g;

    // evaluate zero-crossings and the level of the reset signal
    if (rtb_ManualSwitch1 || rtDW.Compare_g) {
      rtX.Integrator_CSTATE_b = 0.0;
    }
  }

  if (rtX.Integrator_CSTATE_b >= 1.0) {
    if (rtX.Integrator_CSTATE_b > 1.0) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&rtM)->solverInfo, true);
    }

    rtX.Integrator_CSTATE_b = 1.0;
  } else {
    if (rtX.Integrator_CSTATE_b <= -1.0) {
      if (rtX.Integrator_CSTATE_b < -1.0) {
        rtsiSetBlockStateForSolverChangedAtMajorStep(&(&rtM)->solverInfo, true);
      }

      rtX.Integrator_CSTATE_b = -1.0;
    }
  }

  rtb_Integrator_h5 = rtX.Integrator_CSTATE_b;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Outputs for Enabled SubSystem: '<S57>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S64>/Enable'

    if (rtmIsMajorTimeStep((&rtM))) {
      // RelationalOperator: '<S63>/Compare' incorporates:
      //   Abs: '<S57>/Abs'
      //   Constant: '<S63>/Constant'

      if (std::abs(rtDW.Abs) > 0.0) {
        rtDW.EnabledSubsystem_MODE = true;
      } else {
        if (rtDW.EnabledSubsystem_MODE) {
          // Disable for Outport: '<S64>/Alpha'
          rtDW.AlphaRear = 0.0;
          rtDW.EnabledSubsystem_MODE = false;
        }
      }

      // End of RelationalOperator: '<S63>/Compare'
    }

    // End of Outputs for SubSystem: '<S57>/Enabled Subsystem'
  }

  // Outputs for Enabled SubSystem: '<S57>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S64>/Enable'

  if (rtDW.EnabledSubsystem_MODE) {
    // Fcn: '<S64>/AlphaRear'
    rtDW.AlphaRear = -std::atan((rtb_Integrator - rtDW.Integrator * 2.83) /
      rtDW.Abs);
  }

  // End of Outputs for SubSystem: '<S57>/Enabled Subsystem'
  if (rtmIsMajorTimeStep((&rtM))) {
    // Lookup: '<S62>/Lookup Table'
    //
    //  About '<S62>/Lookup Table':
    //  Input0  Data Type:  Floating Point real_T
    //  Output0 Data Type:  Floating Point real_T
    //  Lookup Method: Linear_Endpoint
    //
    //  XData is inlined and evenly spaced, so the algorithm only needs
    //  the value of the first element, the last element, and the spacing.
    //  For efficiency, XData is excluded from the generated code.
    //  YData parameter uses the same data type and scaling as Output0

    LookUpEven_real_T_real_T( &(rtDW.LookupTable_n), rtConstP.pooled12, rtDW.Abs,
      0.0, 1U, 2.5);
  }

  // Product: '<S62>/Divide'
  rtb_Divide_k = rtDW.AlphaRear * rtDW.LookupTable_n;

  // Integrator: '<S59>/Integrator'
  if (rtmIsMajorTimeStep((&rtM))) {
    rtb_ManualSwitch1 = (((rtPrevZCX.Integrator_Reset_ZCE_a == 1) !=
                          static_cast<int32_T>(rtDW.Compare_g)) &&
                         (rtPrevZCX.Integrator_Reset_ZCE_a != 3));
    rtPrevZCX.Integrator_Reset_ZCE_a = rtDW.Compare_g;

    // evaluate zero-crossings and the level of the reset signal
    if (rtb_ManualSwitch1 || rtDW.Compare_g) {
      rtX.Integrator_CSTATE_n = 0.0;
    }
  }

  rtb_Integrator_n = rtX.Integrator_CSTATE_n;

  // Switch: '<S17>/Switch2' incorporates:
  //   Integrator: '<S59>/Integrator'

  rtb_DotProduct2 = rtX.Integrator_CSTATE_n;

  // Sum: '<S17>/Sum1' incorporates:
  //   Gain: '<S17>/K_gamma_rear'
  //   Gain: '<S17>/rear_tyre'
  //   Integrator: '<S60>/Integrator'
  //   Product: '<S17>/Product'

  rtb_DotProduct2 = 0.0 * rtb_DotProduct2 * 0.0 + 113902.0 *
    rtX.Integrator_CSTATE_b;

  // Fcn: '<S18>/Fy' incorporates:
  //   Fcn: '<S18>/Mz'

  rtb_TransferFcn_o = std::cos(rtDW.DeltaWheel_rad);
  Product = rtb_DotProduct * rtb_TransferFcn_o + rtb_DotProduct2;

  // Fcn: '<S18>/Mz'
  rtb_TransferFcn_o = rtb_DotProduct * 0.87000000000000011 * rtb_TransferFcn_o -
    rtb_DotProduct2 * 2.83;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Gain: '<S22>/[ms-1] 2 [rads-1]'
    rtb_Torsionaldamping = 1.9379844961240309 * rtDW.vx_ms1;

    // Saturate: '<S22>/Saturation1'
    if (rtb_Torsionaldamping > 0.33333333333333331) {
      rtb_Torsionaldamping = 0.33333333333333331;
    } else {
      if (rtb_Torsionaldamping < -0.33333333333333331) {
        rtb_Torsionaldamping = -0.33333333333333331;
      }
    }

    // End of Saturate: '<S22>/Saturation1'

    // Signum: '<S22>/Sign'
    if (rtb_Torsionaldamping < 0.0) {
      rtb_DotProduct = -1.0;
    } else if (rtb_Torsionaldamping > 0.0) {
      rtb_DotProduct = 1.0;
    } else if (rtb_Torsionaldamping == 0.0) {
      rtb_DotProduct = 0.0;
    } else {
      rtb_DotProduct = (rtNaN);
    }

    // End of Signum: '<S22>/Sign'

    // Gain: '<S22>/Gain1' incorporates:
    //   Fcn: '<S22>/Road & Aerodyn Resistances'
    //   Gain: '<S22>/Gain'
    //   Product: '<S22>/signed load1'

    rtDW.Gain1 = (1.7086912174079996 * rt_powd_snf(rtDW.vx_ms1, 2.0) +
                  361.9301319102309) * 1.9379844961240309 * rtb_DotProduct * 0.0;
  }

  // TransportDelay: '<S2>/Transport Delay'
  {
    real_T **uBuffer = (real_T**)&rtDW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&rtDW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = (&rtM)->Timing.t[0];
    real_T tMinusDelay = simTime - 0.3;
    rtb_DotProduct2 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      rtDW.TransportDelay_IWORK.CircularBufSize,
      &rtDW.TransportDelay_IWORK.Last,
      rtDW.TransportDelay_IWORK.Tail,
      rtDW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  // Saturate: '<S23>/Saturation'
  if (rtb_DotProduct2 > 150.0) {
    rtb_DotProduct2 = 150.0;
  } else {
    if (rtb_DotProduct2 < 0.0) {
      rtb_DotProduct2 = 0.0;
    }
  }

  // End of Saturate: '<S23>/Saturation'

  // Gain: '<S23>/braking Q factor'
  rtb_DotProduct = 241.28676000000002 * rtb_DotProduct2;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Gain: '<S23>/[ms-1] 2 [rads-1]'
    rtb_Torsionaldamping = 1.9379844961240309 * rtDW.vx_ms1;

    // Saturate: '<S23>/Saturation1'
    if (rtb_Torsionaldamping > 0.33333333333333331) {
      rtb_Torsionaldamping = 0.33333333333333331;
    } else {
      if (rtb_Torsionaldamping < -0.33333333333333331) {
        rtb_Torsionaldamping = -0.33333333333333331;
      }
    }

    // End of Saturate: '<S23>/Saturation1'

    // Signum: '<S23>/Sign'
    if (rtb_Torsionaldamping < 0.0) {
      rtDW.sign = -1.0;
    } else if (rtb_Torsionaldamping > 0.0) {
      rtDW.sign = 1.0;
    } else if (rtb_Torsionaldamping == 0.0) {
      rtDW.sign = 0.0;
    } else {
      rtDW.sign = (rtNaN);
    }

    // End of Signum: '<S23>/Sign'

    // Logic: '<S25>/Logical Operator4' incorporates:
    //   Constant: '<S26>/Constant'
    //   Constant: '<S27>/Constant'
    //   Constant: '<S28>/Constant'
    //   Constant: '<S29>/Constant'
    //   Logic: '<S25>/Logical Operator'
    //   Logic: '<S25>/Logical Operator3'
    //   Memory: '<S25>/Memory'
    //   Memory: '<S25>/Memory2'
    //   RelationalOperator: '<S26>/Compare'
    //   RelationalOperator: '<S27>/Compare'
    //   RelationalOperator: '<S28>/Compare'
    //   RelationalOperator: '<S29>/Compare'

    rtDW.LogicalOperator4 = (((rtDW.vx_ms1 <= 0.0) && (rtDW.Memory_PreviousInput
      >= 0.0)) || ((rtDW.vx_ms1 >= 0.0) && (rtDW.Memory2_PreviousInput <= 0.0)));
  }

  // TransferFcn: '<S24>/Torsional damping'
  rtb_Torsionaldamping = 10.0 * rtX.Torsionaldamping_CSTATE;

  // Abs: '<S25>/Abs'
  rtb_DotProduct2 = std::abs(rtb_Torsionaldamping);

  // RelationalOperator: '<S25>/Relational Operator' incorporates:
  //   Abs: '<S25>/Abs1'

  rtb_ManualSwitch1 = (rtb_DotProduct2 < std::abs(rtb_DotProduct));

  // Logic: '<S25>/Logical Operator1'
  rtb_LogicalOperator1 = (rtDW.LogicalOperator4 && rtb_ManualSwitch1);

  // Logic: '<S25>/Logical Operator2'
  rtb_ManualSwitch1 = !rtb_ManualSwitch1;
  if (rtmIsMajorTimeStep((&rtM))) {
    // UnitDelay: '<S32>/Delay Input1'
    //
    //  Block description for '<S32>/Delay Input1':
    //
    //   Store in Global RAM

    rtDW.Uk1 = rtDW.DelayInput1_DSTATE_g;

    // UnitDelay: '<S33>/Delay Input1'
    //
    //  Block description for '<S33>/Delay Input1':
    //
    //   Store in Global RAM

    rtDW.Uk1_f = rtDW.DelayInput1_DSTATE_o;
  }

  // RelationalOperator: '<S34>/Compare'
  rtDW.Compare_d = rtb_LogicalOperator1;

  // RelationalOperator: '<S35>/Compare'
  rtDW.Compare_i = rtb_ManualSwitch1;
  if (rtmIsMajorTimeStep((&rtM))) {
    // UnitDelay: '<S31>/Unit Delay'
    rtDW.UnitDelay = rtDW.UnitDelay_DSTATE;
  }

  // Switch: '<S31>/Switch1' incorporates:
  //   Constant: '<S31>/Constant'
  //   ManualSwitch: '<S31>/Manual Switch'
  //   ManualSwitch: '<S31>/Manual Switch1'
  //   RelationalOperator: '<S32>/FixPt Relational Operator'
  //   RelationalOperator: '<S33>/FixPt Relational Operator'
  //   Switch: '<S31>/Switch'

  if (rtDW.Compare_i > rtDW.Uk1_f) {
    rtDW.Switch1 = 0.0;
  } else if (rtDW.Compare_d > rtDW.Uk1) {
    // Switch: '<S31>/Switch' incorporates:
    //   Constant: '<S25>/Constant'

    rtDW.Switch1 = 1.0;
  } else {
    rtDW.Switch1 = rtDW.UnitDelay;
  }

  // End of Switch: '<S31>/Switch1'

  // Switch: '<S25>/Switch' incorporates:
  //   Constant: '<S25>/Constant1'
  //   Constant: '<S25>/ax is 0'
  //   Gain: '<S19>/Gain'
  //   Gain: '<S19>/Inertia'
  //   Gain: '<S23>/Gain'
  //   Product: '<S23>/signed load1'
  //   Sum: '<S19>/Sum'
  //   Sum: '<S19>/Sum2'
  //   Sum: '<S25>/Sum'

  if (1.0 - rtDW.Switch1 != 0.0) {
    rtDW.Switch = ((1.9379844961240309 * rtb_Torsionaldamping - rtDW.Gain1) -
                   1.9379844961240309 * rtb_DotProduct * rtDW.sign) *
      0.00013986013986013986;
  } else {
    rtDW.Switch = 0.0;
  }

  // End of Switch: '<S25>/Switch'

  // Integrator: '<S38>/Integrator'
  rtb_DotProduct2 = rtX.Integrator_CSTATE_f;

  // Gain: '<S20>/Gain'
  rtb_Torsionaldamping = 0.00013986013986013986 * Product;

  // Gain: '<S20>/Gain1'
  rtDW.ddYawAngle_rads2 = 4.2349553212213612E-5 * rtb_TransferFcn_o;

  // Sum: '<S20>/Sum1' incorporates:
  //   Fcn: '<S20>/Fcn1'

  rtDW.dvy_ms2 = rtb_Torsionaldamping - rtDW.Abs * rtDW.Integrator;

  // Integrator: '<S41>/Integrator'
  rtDW.Integrator_f = rtX.Integrator_CSTATE_a;

  // Integrator: '<S42>/Integrator'
  rtDW.Integrator_k = rtX.Integrator_CSTATE_lg;

  // Sum: '<S21>/Sum4' incorporates:
  //   Fcn: '<S21>/Fcn'
  //   Fcn: '<S21>/Fcn1'
  //   Gain: '<S21>/DampRateFront'
  //   Gain: '<S21>/SpringStiffnessFront'
  //   Integrator: '<S43>/Integrator'
  //   Integrator: '<S44>/Integrator'

  rtb_TransferFcn_o = (rtX.Integrator_CSTATE_as - 0.87000000000000011 *
                       rtX.Integrator_CSTATE_i) * 597350.0 + (rtDW.Integrator_f
    - 0.87000000000000011 * rtDW.Integrator_k) * 6338.0;

  // Sum: '<S21>/Sum5' incorporates:
  //   Fcn: '<S21>/Fcn2'
  //   Fcn: '<S21>/Fcn3'
  //   Gain: '<S21>/DampRateRear'
  //   Gain: '<S21>/SpringStiffnessRear'
  //   Integrator: '<S43>/Integrator'
  //   Integrator: '<S44>/Integrator'

  Product = (2.83 * rtX.Integrator_CSTATE_i + rtX.Integrator_CSTATE_as) *
    1.9431E+6 + (2.83 * rtDW.Integrator_k + rtDW.Integrator_f) * 20617.0;

  // Gain: '<S21>/Inertia' incorporates:
  //   Gain: '<S21>/Inertia2'
  //   Gain: '<S21>/gain'
  //   Gain: '<S21>/gain3'
  //   Sum: '<S21>/Sum'

  rtDW.Inertia = ((0.87000000000000011 * rtb_TransferFcn_o - 5004.999914765358 *
                   rtDW.Switch) - 2.83 * Product) * 4.2349553212213612E-5;

  // Gain: '<S21>/Mass' incorporates:
  //   Sum: '<S21>/Sum1'

  rtDW.Mass = ((0.0 - rtb_TransferFcn_o) - Product) * 0.00013986013986013986;

  // Integrator: '<S40>/Integrator'
  // Limited  Integrator
  if (rtX.Integrator_CSTATE_o >= 0.087266462599716474) {
    if (rtX.Integrator_CSTATE_o > 0.087266462599716474) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&rtM)->solverInfo, true);
    }

    rtX.Integrator_CSTATE_o = 0.087266462599716474;
  } else {
    if (rtX.Integrator_CSTATE_o <= -0.087266462599716474) {
      if (rtX.Integrator_CSTATE_o < -0.087266462599716474) {
        rtsiSetBlockStateForSolverChangedAtMajorStep(&(&rtM)->solverInfo, true);
      }

      rtX.Integrator_CSTATE_o = -0.087266462599716474;
    }
  }

  // Integrator: '<S45>/Integrator'
  rtDW.Integrator_c = rtX.Integrator_CSTATE_l1;

  // Trigonometry: '<S21>/Trigonometric Function' incorporates:
  //   Integrator: '<S40>/Integrator'
  //   Trigonometry: '<S21>/Trigonometric Function3'

  Product = std::cos(rtX.Integrator_CSTATE_o);

  // Fcn: '<S21>/Jxx_roll = M*L^2' incorporates:
  //   Constant: '<S21>/Constant'
  //   Fcn: '<S21>/C_roll'
  //   Fcn: '<S21>/D_roll'
  //   Fcn: '<S21>/fcn'
  //   Gain: '<S21>/Mass1'
  //   Gain: '<S21>/hcog'
  //   Integrator: '<S40>/Integrator'
  //   Product: '<S21>/Product'
  //   Product: '<S21>/Product1'
  //   Product: '<S21>/Product2'
  //   Sum: '<S21>/Sum2'
  //   Sum: '<S21>/Sum3'
  //   Trigonometry: '<S21>/Trigonometric Function'
  //   Trigonometry: '<S21>/Trigonometric Function1'

  rtDW.RollRate_rads2 = ((((rtb_Torsionaldamping * Product + std::sin
    (rtX.Integrator_CSTATE_o) * 9.81) + rtDW.vx_ms1 * rtDW.Integrator * Product)
    * 7150.0 * 0.699999988079071 - rtX.Integrator_CSTATE_o * 3.0 * 2.54045E+6 /
    2.0 * 4.1371559999999992 / 2.0) - rtDW.Integrator_c * 6.0 * 26955.0 / 2.0 *
    4.1371559999999992 / 2.0) / 3503.4998806715021;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Gain: '<S3>/FinalDriveRatio' incorporates:
    //   Gain: '<S3>/[ms-1 --> rpm]'

    rtb_TransmissionOut_rpm = 18.506388731615736 * rtDW.vx_ms1 * 2.733;

    // If: '<S9>/reverse//neutral//normal gear' incorporates:
    //   Constant: '<S9>/GearNeutral'
    //   Constant: '<S9>/GearReverse'
    //   Inport: '<S69>/In1'
    //   Inport: '<S70>/In1'
    //   Inport: '<S71>/In1'
    //   Memory: '<S9>/IC, gear = 1'

    if (rtmIsMajorTimeStep((&rtM))) {
      rtAction = 2;
      rtDW.reverseneutralnormalgear_Active = 2;
    } else {
      rtAction = rtDW.reverseneutralnormalgear_Active;
    }

    switch (rtAction) {
     case 0:
      // Outputs for IfAction SubSystem: '<S9>/If Action Neutral' incorporates:
      //   ActionPort: '<S69>/Action Port'

      rtb_Merge = 0.0;

      // End of Outputs for SubSystem: '<S9>/If Action Neutral'
      break;

     case 1:
      // Outputs for IfAction SubSystem: '<S9>/If Action Reverse' incorporates:
      //   ActionPort: '<S71>/Action Port'

      rtb_Merge = -1.0;

      // End of Outputs for SubSystem: '<S9>/If Action Reverse'
      break;

     case 2:
      // Outputs for IfAction SubSystem: '<S9>/If Action Normal' incorporates:
      //   ActionPort: '<S70>/Action Port'

      rtb_Merge = rtDW.ICgear1_PreviousInput;

      // End of Outputs for SubSystem: '<S9>/If Action Normal'
      break;
    }

    // End of If: '<S9>/reverse//neutral//normal gear'

    // If: '<S5>/If' incorporates:
    //   Inport: '<S65>/In1'
    //   Inport: '<S66>/In1'

    if (rtmIsMajorTimeStep((&rtM))) {
      rtAction = 0;
      rtDW.If_ActiveSubsystem = 0;
    } else {
      rtAction = rtDW.If_ActiveSubsystem;
    }

    switch (rtAction) {
     case 0:
      // Outputs for IfAction SubSystem: '<S5>/If Action Subsystem' incorporates:
      //   ActionPort: '<S65>/Action Port'

      rtDW.Merge = rtb_Merge;

      // End of Outputs for SubSystem: '<S5>/If Action Subsystem'
      break;

     case 1:
      // Outputs for IfAction SubSystem: '<S5>/If Action Subsystem1' incorporates:
      //   ActionPort: '<S66>/Action Port'

      rtDW.Merge = 0.0;

      // End of Outputs for SubSystem: '<S5>/If Action Subsystem1'
      break;
    }

    // End of If: '<S5>/If'

    // Lookup: '<S80>/Transmission Gear ratios'
    rtDW.TransmissionGearratios = rt_Lookup
      (rtConstP.TransmissionGearratios_XData, 14, rtDW.Merge,
       rtConstP.TransmissionGearratios_YData);

    // Gain: '<S2>/Gain1'
    rtDW.Gain1_a = 5.8785529715762266 * rtDW.TransmissionGearratios;

    // Gain: '<S2>/Gain3' incorporates:
    //   Math: '<S2>/Math Function'

    rtDW.Gain3 = rtb_Filter_a * rtb_Filter_a * 0.0;

    // Delay: '<S2>/Delay'
    rtDW.Delay = rtDW.Delay_DSTATE;
  }

  // Clock: '<S2>/Clock' incorporates:
  //   Clock: '<S2>/Clock1'

  rtb_TransferFcn_o = (&rtM)->Timing.t[0];

  // Switch: '<S2>/Switch' incorporates:
  //   Clock: '<S2>/Clock'
  //   Constant: '<S2>/Constant1'
  //   Outport: '<Root>/output_acceleration'

  if (rtb_TransferFcn_o > 0.2) {
    Product = rtY.output_acceleration;
  } else {
    Product = 0.0;
  }

  // End of Switch: '<S2>/Switch'

  // Sum: '<S2>/Add1'
  rtb_Filter_a = rtDW.Delay - Product;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Gain: '<S124>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S116>/Filter'
    //   Gain: '<S115>/Derivative Gain'
    //   Sum: '<S116>/SumD'

    rtb_FilterCoefficient = (0.0 * rtb_Filter_a - rtDW.Filter_DSTATE) * 100.0;

    // Sum: '<S130>/Sum' incorporates:
    //   DiscreteIntegrator: '<S121>/Integrator'
    //   Gain: '<S126>/Proportional Gain'

    rtDW.Sum = (0.6 * rtb_Filter_a + rtDW.Integrator_DSTATE) +
      rtb_FilterCoefficient;

    // Gain: '<S172>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S164>/Filter'
    //   Gain: '<S163>/Derivative Gain'
    //   Sum: '<S164>/SumD'

    rtb_FilterCoefficient_o = (0.0 * rtb_Filter_a - rtDW.Filter_DSTATE_o) *
      100.0;

    // Sum: '<S178>/Sum' incorporates:
    //   DiscreteIntegrator: '<S169>/Integrator'
    //   Gain: '<S174>/Proportional Gain'

    rtDW.Sum_m = (10.0 * rtb_Filter_a + rtDW.Integrator_DSTATE_a) +
      rtb_FilterCoefficient_o;

    // Gain: '<S220>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S212>/Filter'
    //   Gain: '<S211>/Derivative Gain'
    //   Sum: '<S212>/SumD'

    rtb_FilterCoefficient_d = (0.0 * rtb_Filter_a - rtDW.Filter_DSTATE_d) *
      100.0;

    // Sum: '<S226>/Sum' incorporates:
    //   DiscreteIntegrator: '<S217>/Integrator'
    //   Gain: '<S222>/Proportional Gain'

    rtDW.Sum_l = (0.3 * rtb_Filter_a + rtDW.Integrator_DSTATE_e) +
      rtb_FilterCoefficient_d;
  }

  // Switch: '<S2>/Switch2'
  if (rtDW.Delay > 0.0) {
    // Switch: '<S2>/Switch1'
    if (rtb_TransferFcn_o > 1.75) {
      rtb_TransferFcn_o = rtDW.Sum;
    } else {
      rtb_TransferFcn_o = rtDW.Sum_m;
    }

    // End of Switch: '<S2>/Switch1'
  } else {
    rtb_TransferFcn_o = rtDW.Sum_l;
  }

  // End of Switch: '<S2>/Switch2'

  // Sum: '<S2>/Add2' incorporates:
  //   Inport: '<Root>/self_acceleration'

  Product = rtb_TransferFcn_o + rtU.self_acceleration;

  // MinMax: '<S2>/MinMax'
  if (Product > 0.0) {
    rtb_TransferFcn_o = Product;
  } else {
    rtb_TransferFcn_o = 0.0;
  }

  // End of MinMax: '<S2>/MinMax'

  // Product: '<S2>/Divide1' incorporates:
  //   Constant: '<S2>/mass'
  //   Product: '<S2>/Divide'
  //   Sum: '<S2>/Add'

  rtb_Torsionaldamping = (rtb_TransferFcn_o * 7150.0 + rtDW.Gain3) * (1.0 /
    rtDW.Gain1_a);

  // Product: '<S1>/Divide'
  rtb_DotProduct = rtb_Torsionaldamping * rtDW.TransmissionGearratios;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Switch: '<S79>/Switch' incorporates:
    //   Constant: '<S79>/Constant'
    //   Constant: '<S79>/Constant1'
    //   Constant: '<S82>/Constant'
    //   RelationalOperator: '<S82>/Compare'

    if (rtDW.Merge != 0.0) {
      rtb_Switch_m = 1.0;
    } else {
      rtb_Switch_m = 0.02;
    }

    // End of Switch: '<S79>/Switch'

    // Gain: '<S4>/rad|sec2rpm' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    rtDW.rpm = 9.5492965855137211 * rtDW.DiscreteTimeIntegrator_DSTATE_b;

    // Product: '<S79>/SpeedRatio' incorporates:
    //   Abs: '<S80>/Ensure positive TransmissionRPM'
    //   Product: '<S80>/Product1'

    rtb_SpeedRatio = std::abs(rtDW.TransmissionGearratios *
      rtb_TransmissionOut_rpm) / rtDW.rpm;

    // Fcn: '<S79>/Impeller' incorporates:
    //   Gain: '<S79>/rpm2rads-1'
    //   Lookup: '<S79>/FactorK'
    //   Product: '<S79>/Quotient'

    rtb_Quotient = rt_powd_snf(0.10471975511965977 * rtDW.rpm / rt_Lookup
      (rtConstP.FactorK_XData, 21, rtb_SpeedRatio, rtConstP.FactorK_YData), 2.0);

    // Switch: '<S79>/Switch1' incorporates:
    //   Constant: '<S79>/Constant2'
    //   Constant: '<S81>/Constant'
    //   Fcn: '<S79>/Impeller'
    //   Gain: '<S79>/Drag'
    //   Lookup: '<S79>/TorqueRatio'
    //   Product: '<S79>/Turbine'
    //   RelationalOperator: '<S81>/Compare'
    //   Sum: '<S79>/Sum'

    if (rtb_SpeedRatio <= 1.0) {
      rtb_SpeedRatio = rtb_Quotient * rt_Lookup(rtConstP.TorqueRatio_XData, 22,
        rtb_SpeedRatio, rtConstP.TorqueRatio_YData);
    } else {
      rtb_SpeedRatio = -(rtb_SpeedRatio - 1.0);
    }

    // End of Switch: '<S79>/Switch1'

    // Product: '<S80>/Product' incorporates:
    //   Lookup: '<S11>/Viscous coupling'
    //   Product: '<S79>/Product1'

    rtDW.Product_d = rt_Lookup(rtConstP.Viscouscoupling_XData, 101, rtb_Switch_m
      * rtb_SpeedRatio, rtConstP.Viscouscoupling_YData) *
      rtDW.TransmissionGearratios;
  }

  // If: '<S80>/If' incorporates:
  //   Constant: '<S80>/OutputTorque = 0'
  //   Inport: '<S83>/In1'
  //   Inport: '<S84>/In1'

  if (rtmIsMajorTimeStep((&rtM))) {
    if (rtDW.Merge == 0.0) {
      rtAction = 0;
    } else if (rtDW.Merge == -1.0) {
      rtAction = 1;
    } else {
      rtAction = 2;
    }

    rtDW.If_ActiveSubsystem_j = rtAction;
  } else {
    rtAction = rtDW.If_ActiveSubsystem_j;
  }

  switch (rtAction) {
   case 0:
    // Outputs for IfAction SubSystem: '<S80>/If Action Neutral' incorporates:
    //   ActionPort: '<S83>/Action Port'

    if (rtmIsMajorTimeStep((&rtM))) {
      rtDW.Merge_n = 0.0;
    }

    // End of Outputs for SubSystem: '<S80>/If Action Neutral'
    break;

   case 1:
    // Outputs for IfAction SubSystem: '<S80>/If Action Reverse' incorporates:
    //   ActionPort: '<S85>/Action Port'

    // Gain: '<S85>/Reverse'
    rtDW.Merge_n = -rtDW.Product_d;

    // End of Outputs for SubSystem: '<S80>/If Action Reverse'
    break;

   case 2:
    // Outputs for IfAction SubSystem: '<S80>/If Action Normal' incorporates:
    //   ActionPort: '<S84>/Action Port'

    rtDW.Merge_n = rtDW.Product_d;

    // End of Outputs for SubSystem: '<S80>/If Action Normal'
    break;
  }

  // End of If: '<S80>/If'

  // Switch: '<S8>/Switch2' incorporates:
  //   RelationalOperator: '<S8>/LowerRelop1'

  if (!(rtDW.Merge_n > rtb_DotProduct)) {
    // Switch: '<S8>/Switch' incorporates:
    //   RelationalOperator: '<S8>/UpperRelop'

    if (rtDW.Merge_n < 0.0) {
      rtb_DotProduct = 0.0;
    } else {
      rtb_DotProduct = rtDW.Merge_n;
    }

    // End of Switch: '<S8>/Switch'
  }

  // End of Switch: '<S8>/Switch2'

  // Gain: '<S3>/FinalDriveRatio '
  rtDW.DriveTorque_Nm = 2.733 * rtb_DotProduct;

  // Fcn: '<S14>/Linl'
  rtDW.Linl = (rtb_Fcn15 - rtb_Fcn16) / 0.65 * rtDW.Abs;

  // Fcn: '<S14>/Linl1' incorporates:
  //   Gain: '<S14>/due to sign convention'
  //   Integrator: '<S40>/Integrator'

  rtDW.Linl1 = (-rtX.Integrator_CSTATE_o - rtb_DotProduct1) / 0.65 * rtDW.Abs;

  // SignalConversion generated from: '<S56>/Dot Product'
  rtb_Fcn15 = rtb_Integrator;

  // Fcn: '<S56>/Fcn9' incorporates:
  //   Fcn: '<S56>/Fcn10'
  //   Fcn: '<S56>/Fcn11'
  //   Fcn: '<S56>/Fcn13'
  //   Fcn: '<S56>/Fcn14'

  rtb_Fcn16 = std::cos(rtb_DotProduct2);

  // Fcn: '<S56>/Fcn10' incorporates:
  //   Fcn: '<S56>/Fcn11'
  //   Fcn: '<S56>/Fcn12'
  //   Fcn: '<S56>/Fcn13'
  //   Fcn: '<S56>/Fcn14'

  rtb_Integrator = std::sin(rtb_DotProduct2);

  // Fcn: '<S56>/Fcn17'
  rtb_DotProduct2 = std::cos(0.0) * std::cos(0.0);

  // DotProduct: '<S56>/Dot Product2' incorporates:
  //   Fcn: '<S56>/Fcn15'
  //   Fcn: '<S56>/Fcn16'
  //   SignalConversion generated from: '<S56>/Dot Product2'
  //   SignalConversion generated from: '<S56>/Dot Product'

  rtb_DotProduct2 = (std::cos(0.0) * std::sin(0.0) * rtb_Fcn15 + rtDW.vx_ms1 *
                     -std::sin(0.0)) + rtDW.Integrator_f * rtb_DotProduct2;

  // SignalConversion generated from: '<S55>/Integrator' incorporates:
  //   DotProduct: '<S56>/Dot Product'
  //   DotProduct: '<S56>/Dot Product1'
  //   Fcn: '<S56>/Fcn10'
  //   Fcn: '<S56>/Fcn11'
  //   Fcn: '<S56>/Fcn12'
  //   Fcn: '<S56>/Fcn13'
  //   Fcn: '<S56>/Fcn14'
  //   Fcn: '<S56>/Fcn9'
  //   SignalConversion generated from: '<S56>/Dot Product'

  rtDW.TmpSignalConversionAtIntegrator[0] = ((rtb_Fcn16 * std::sin(0.0) * std::
    sin(0.0) - rtb_Integrator * std::cos(0.0)) * rtb_Fcn15 + rtb_Fcn16 * std::
    cos(0.0) * rtDW.vx_ms1) + (rtb_Fcn16 * std::sin(0.0) * std::cos(0.0) +
    rtb_Integrator * std::sin(0.0)) * rtDW.Integrator_f;
  rtDW.TmpSignalConversionAtIntegrator[1] = ((rtb_Integrator * std::sin(0.0) *
    std::sin(0.0) + rtb_Fcn16 * std::cos(0.0)) * rtb_Fcn15 + rtb_Integrator *
    std::cos(0.0) * rtDW.vx_ms1) + (rtb_Integrator * std::sin(0.0) * std::cos
    (0.0) - rtb_Fcn16 * std::sin(0.0)) * rtDW.Integrator_f;
  rtDW.TmpSignalConversionAtIntegrator[2] = rtb_DotProduct2;

  // Fcn: '<S17>/Linl'
  rtDW.Linl_p = (rtb_Divide_k - rtb_Integrator_h5) / 0.65 * rtDW.Abs;

  // Fcn: '<S17>/Linl1' incorporates:
  //   Gain: '<S17>/due to sign convention'
  //   Integrator: '<S40>/Integrator'

  rtDW.Linl1_o = (-rtX.Integrator_CSTATE_o - rtb_Integrator_n) / 0.65 * rtDW.Abs;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Product: '<S79>/Product'
    rtDW.Product_g = rtb_Switch_m * rtb_Quotient;

    // Sum: '<S9>/Add2' incorporates:
    //   Delay: '<S9>/Shift_Down time'
    //   Delay: '<S9>/Shift_Up time'
    //   Memory: '<S9>/Memory'
    //   Sum: '<S9>/Sum'

    rtb_SpeedRatio = (rtDW.Shift_Uptime_DSTATE - rtDW.Shift_Downtime_DSTATE) +
      rtDW.Memory_PreviousInput_c;
  }

  // Gain: '<S4>/engine + impeller inertia' incorporates:
  //   Lookup2D: '<S4>/EngineTorque'
  //   Sum: '<S4>/Sum'
  //   TransferFcn: '<S4>/Transfer Fcn'

  rtDW.rads2 = (rt_Lookup2D_Normal(rtConstP.EngineTorque_RowIdx, 10,
    rtConstP.EngineTorque_ColIdx, 16, rtConstP.EngineTorque_Table, 10.0 *
    rtX.TransferFcn_CSTATE, rtDW.rpm) - rtDW.Product_g) * 0.038079910952603553;

  // MATLAB Function: '<S2>/MATLAB Function'
  rtb_Switch_m = rtDW.rpm;
  if (rtDW.rpm < 700.0) {
    rtb_Switch_m = 700.0;
  }

  if (rtb_Switch_m > 2300.0) {
    rtb_Switch_m = 2300.0;
  }

  for (high_i = 0; high_i < 10; high_i++) {
    A1[high_i] = rtb_Switch_m;
  }

  for (n = 0; n < 10; n++) {
    if (A1[n] >= 700.0) {
      if (A1[n] <= 2300.0) {
        low_i = 0;
        low_ip1 = 2;
        high_i = 16;
        while (high_i > low_ip1) {
          mid_i = ((low_i + high_i) + 1) >> 1;
          if (A1[n] >= X_0[mid_i - 1]) {
            low_i = mid_i - 1;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }

        low_ip1 = bsearch(Yq_0, static_cast<real_T>(b[n])) - 1;
        if (A1[n] == X_0[low_i]) {
          low_i = 10 * low_i + low_ip1;
          rtb_Switch_m = V[low_i];
          rtb_Quotient = V[low_i + 1];
        } else if (X_0[low_i + 1] == A1[n]) {
          rtb_Switch_m = V[(low_i + 1) * 10 + low_ip1];
          rtb_Quotient = V[((low_i + 1) * 10 + low_ip1) + 1];
        } else {
          rtb_Quotient = (A1[n] - static_cast<real_T>(X_0[low_i])) /
            static_cast<real_T>(X_0[low_i + 1] - X_0[low_i]);
          high_i = (low_i + 1) * 10 + low_ip1;
          mid_i = 10 * low_i + low_ip1;
          if (V[high_i] == V[mid_i]) {
            rtb_Switch_m = V[mid_i];
          } else {
            rtb_Switch_m = static_cast<real_T>(V[high_i]) * rtb_Quotient +
              static_cast<real_T>(V[mid_i]) * (1.0 - rtb_Quotient);
          }

          high_i = ((low_i + 1) * 10 + low_ip1) + 1;
          mid_i++;
          if (V[high_i] == V[mid_i]) {
            rtb_Quotient = V[mid_i];
          } else {
            rtb_Quotient = static_cast<real_T>(V[high_i]) * rtb_Quotient +
              static_cast<real_T>(V[mid_i]) * (1.0 - rtb_Quotient);
          }
        }

        if (b[n] == b[low_ip1]) {
          Z[n] = rtb_Switch_m;
        } else if (rtb_Switch_m == rtb_Quotient) {
          Z[n] = rtb_Switch_m;
        } else {
          high_i = b[low_ip1 + 1];
          if (high_i == b[n]) {
            Z[n] = rtb_Quotient;
          } else {
            rtb_Integrator_h5 = static_cast<real_T>(b[n] - b[low_ip1]) /
              static_cast<real_T>(high_i - b[low_ip1]);
            Z[n] = (1.0 - rtb_Integrator_h5) * rtb_Switch_m + rtb_Integrator_h5 *
              rtb_Quotient;
          }
        }
      } else {
        Z[n] = (rtNaN);
      }
    } else {
      Z[n] = (rtNaN);
    }
  }

  if (rtb_Torsionaldamping > Z[9]) {
    rtDW.y = 100.0;
  } else {
    std::memcpy(&A1[0], &Yq[0], 10U * sizeof(real_T));
    rtDW.y = (rtNaN);
    n = 0;
    do {
      exitg1 = 0;
      if (n < 10) {
        if (rtIsNaN(Z[n])) {
          exitg1 = 1;
        } else {
          n++;
        }
      } else {
        if (Z[1] < Z[0]) {
          for (n = 0; n < 5; n++) {
            rtb_Switch_m = Z[n];
            Z[n] = Z[9 - n];
            Z[9 - n] = rtb_Switch_m;
          }

          for (n = 0; n < 5; n++) {
            rtb_Switch_m = A1[n];
            A1[n] = A1[9 - n];
            A1[9 - n] = rtb_Switch_m;
          }
        }

        if ((!rtIsNaN(rtb_Torsionaldamping)) && (!(rtb_Torsionaldamping > Z[9]))
            && (!(rtb_Torsionaldamping < Z[0]))) {
          n = bsearch(Z, rtb_Torsionaldamping) - 1;
          rtb_Switch_m = (rtb_Torsionaldamping - Z[n]) / (Z[n + 1] - Z[n]);
          if (rtb_Switch_m == 0.0) {
            rtDW.y = A1[n];
          } else if (rtb_Switch_m == 1.0) {
            rtDW.y = A1[n + 1];
          } else {
            rtb_TransferFcn_o = A1[n + 1];
            if (rtb_TransferFcn_o == A1[n]) {
              rtDW.y = A1[n];
            } else {
              rtDW.y = (1.0 - rtb_Switch_m) * A1[n] + rtb_TransferFcn_o *
                rtb_Switch_m;
            }
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  // End of MATLAB Function: '<S2>/MATLAB Function'
  if (rtmIsMajorTimeStep((&rtM))) {
    // Saturate: '<S9>/Gear limitation'
    if (rtb_Merge > 12.0) {
      rtDW.Gearlimitation = 12.0;
    } else if (rtb_Merge < 1.0) {
      rtDW.Gearlimitation = 1.0;
    } else {
      rtDW.Gearlimitation = rtb_Merge;
    }

    // End of Saturate: '<S9>/Gear limitation'
  }

  // Lookup2D: '<S9>/interp_down'
  //
  //  About '<S9>/interp_down':
  //  Input0  Data Type:  Floating Point real_T
  //  Input1  Data Type:  Floating Point real_T
  //  Output0 Data Type:  Floating Point real_T
  //  Lookup Method: Linear_Endpoint
  //
  //  Row Data    parameter uses the same data type and scaling as Input0
  //  Column Data parameter uses the same data type and scaling as Input1
  //  Table Data  parameter uses the same data type and scaling as Output0

  {
    uint32_T iLeftU0, iRghtU0, iLeftU1, iRghtU1;
    BINARYSEARCH_real_T( &(iLeftU0), &(iRghtU0), rtDW.y, rtConstP.pooled24, 5U);

    // Find the location of current input value in the data table.

    if (rtDW.Gearlimitation <= 1.0 ) {
      // Less than or equal to the smallest point in the table.

      iLeftU1 = 0U;
      iRghtU1 = 0U;
    } else if (rtDW.Gearlimitation >= 12.0 ) {
      // Greater than or equal to the largest point in the table.
      iLeftU1 = 11U;
      iRghtU1 = 11U;
    } else {
      iLeftU1 = (uint32_T)( rtDW.Gearlimitation - (1.0) );
      iRghtU1 = iLeftU1 + 1;
    }

    {
      real_T yTemp;
      real_T u1Lambda;
      real_T u0Lambda;
      if (iLeftU1 != iRghtU1 ) {
        {
          real_T num = (real_T)( rtDW.Gearlimitation - (1.0) ) - ( iLeftU1 * 1.0
            );
          u1Lambda = num / 1.0;
        }
      } else {
        u1Lambda = 0.0;
      }

      if ((rtConstP.pooled24[iRghtU0]) > (rtConstP.pooled24[iLeftU0]) ) {
        real_T num;
        real_T den;
        den = (rtConstP.pooled24[iRghtU0]);
        den -= (rtConstP.pooled24[iLeftU0]);
        num = rtDW.y;
        num -= (rtConstP.pooled24[iLeftU0]);
        u0Lambda = num / den;
      } else {
        u0Lambda = 0.0;
      }

      // Interpolate along u1 variable
      //     with the u0 variable locked on the left u0

      {
        real_T yLeftCast;
        real_T yRghtCast;
        yLeftCast = (rtConstP.interp_down_Table[(iLeftU0+6U*iLeftU1)]);
        yRghtCast = (rtConstP.interp_down_Table[(iLeftU0+6U*iRghtU1)]);
        yLeftCast += u1Lambda * ( yRghtCast - yLeftCast );
        rtb_interp_down = yLeftCast;
      }

      // Interpolate along u1 variable
      //     with the u0 variable locked on the right u0

      {
        real_T yLeftCast;
        real_T yRghtCast;
        yLeftCast = (rtConstP.interp_down_Table[(iRghtU0+6U*iLeftU1)]);
        yRghtCast = (rtConstP.interp_down_Table[(iRghtU0+6U*iRghtU1)]);
        yLeftCast += u1Lambda * ( yRghtCast - yLeftCast );
        yTemp = yLeftCast;
      }

      //
      //  Interpolate along u0 variable
      //     with the u1 variable locked on its interpolated value

      {
        real_T yLeftCast;
        real_T yRghtCast;
        yLeftCast = rtb_interp_down;
        yRghtCast = yTemp;
        yLeftCast += u0Lambda * ( yRghtCast - yLeftCast );
        rtb_interp_down = yLeftCast;
      }
    }
  }

  // RelationalOperator: '<S9>/Relational Operator1' incorporates:
  //   Gain: '<S9>/to_ms-1 '
  //   Lookup2D: '<S9>/interp_down'

  rtDW.RelationalOperator1 = (rtDW.vx_ms1 <= 0.27777777777777779 *
    rtb_interp_down);
  if (rtmIsMajorTimeStep((&rtM))) {
    // UnitDelay: '<S67>/Delay Input1'
    //
    //  Block description for '<S67>/Delay Input1':
    //
    //   Store in Global RAM

    rtDW.Uk1_p = rtDW.DelayInput1_DSTATE_a;

    // DataTypeConversion: '<S68>/Data Type Conversion' incorporates:
    //   RelationalOperator: '<S72>/FixPt Relational Operator'
    //   UnitDelay: '<S72>/Delay Input1'
    //
    //  Block description for '<S72>/Delay Input1':
    //
    //   Store in Global RAM

    rtDW.DataTypeConversion = (rtDW.Gearlimitation > rtDW.DelayInput1_DSTATE);
  }

  // DataTypeConversion: '<S9>/Data Type Conversion1' incorporates:
  //   RelationalOperator: '<S67>/FixPt Relational Operator'

  rtDW.DataTypeConversion1 = (static_cast<int32_T>(rtDW.RelationalOperator1) >
    static_cast<int32_T>(rtDW.Uk1_p));

  // Lookup2D: '<S9>/interp_up'
  //
  //  About '<S9>/interp_up':
  //  Input0  Data Type:  Floating Point real_T
  //  Input1  Data Type:  Floating Point real_T
  //  Output0 Data Type:  Floating Point real_T
  //  Lookup Method: Linear_Endpoint
  //
  //  Row Data    parameter uses the same data type and scaling as Input0
  //  Column Data parameter uses the same data type and scaling as Input1
  //  Table Data  parameter uses the same data type and scaling as Output0

  {
    uint32_T iLeftU0, iRghtU0, iLeftU1, iRghtU1;
    BINARYSEARCH_real_T( &(iLeftU0), &(iRghtU0), rtDW.y, rtConstP.pooled24, 5U);

    // Find the location of current input value in the data table.

    if (rtDW.Gearlimitation <= 1.0 ) {
      // Less than or equal to the smallest point in the table.

      iLeftU1 = 0U;
      iRghtU1 = 0U;
    } else if (rtDW.Gearlimitation >= 12.0 ) {
      // Greater than or equal to the largest point in the table.
      iLeftU1 = 11U;
      iRghtU1 = 11U;
    } else {
      iLeftU1 = (uint32_T)( rtDW.Gearlimitation - (1.0) );
      iRghtU1 = iLeftU1 + 1;
    }

    {
      real_T yTemp;
      real_T u1Lambda;
      real_T u0Lambda;
      if (iLeftU1 != iRghtU1 ) {
        {
          real_T num = (real_T)( rtDW.Gearlimitation - (1.0) ) - ( iLeftU1 * 1.0
            );
          u1Lambda = num / 1.0;
        }
      } else {
        u1Lambda = 0.0;
      }

      if ((rtConstP.pooled24[iRghtU0]) > (rtConstP.pooled24[iLeftU0]) ) {
        real_T num;
        real_T den;
        den = (rtConstP.pooled24[iRghtU0]);
        den -= (rtConstP.pooled24[iLeftU0]);
        num = rtDW.y;
        num -= (rtConstP.pooled24[iLeftU0]);
        u0Lambda = num / den;
      } else {
        u0Lambda = 0.0;
      }

      // Interpolate along u1 variable
      //     with the u0 variable locked on the left u0

      {
        real_T yLeftCast;
        real_T yRghtCast;
        yLeftCast = (rtConstP.interp_up_Table[(iLeftU0+6U*iLeftU1)]);
        yRghtCast = (rtConstP.interp_up_Table[(iLeftU0+6U*iRghtU1)]);
        yLeftCast += u1Lambda * ( yRghtCast - yLeftCast );
        rtb_interp_up = yLeftCast;
      }

      // Interpolate along u1 variable
      //     with the u0 variable locked on the right u0

      {
        real_T yLeftCast;
        real_T yRghtCast;
        yLeftCast = (rtConstP.interp_up_Table[(iRghtU0+6U*iLeftU1)]);
        yRghtCast = (rtConstP.interp_up_Table[(iRghtU0+6U*iRghtU1)]);
        yLeftCast += u1Lambda * ( yRghtCast - yLeftCast );
        yTemp = yLeftCast;
      }

      //
      //  Interpolate along u0 variable
      //     with the u1 variable locked on its interpolated value

      {
        real_T yLeftCast;
        real_T yRghtCast;
        yLeftCast = rtb_interp_up;
        yRghtCast = yTemp;
        yLeftCast += u0Lambda * ( yRghtCast - yLeftCast );
        rtb_interp_up = yLeftCast;
      }
    }
  }

  // RelationalOperator: '<S9>/Relational Operator' incorporates:
  //   Gain: '<S9>/to_ms-1'
  //   Lookup2D: '<S9>/interp_up'

  rtDW.RelationalOperator = (rtDW.vx_ms1 >= 0.27777777777777779 * rtb_interp_up);

  // If: '<S68>/If' incorporates:
  //   Constant: '<S68>/Constant'
  //   DataTypeConversion: '<S68>/Data Type Conversion1'
  //   Inport: '<S73>/In1'

  if (rtmIsMajorTimeStep((&rtM))) {
    rtAction = static_cast<int8_T>((!(rtDW.DataTypeConversion == 1.0)) ||
      (!rtDW.RelationalOperator));
    rtDW.If_ActiveSubsystem_l = rtAction;
  } else {
    rtAction = rtDW.If_ActiveSubsystem_l;
  }

  switch (rtAction) {
   case 0:
    // Outputs for IfAction SubSystem: '<S68>/If V0 higher of the from 2->3 shifting velocity' incorporates:
    //   ActionPort: '<S73>/Action Port'

    if (rtmIsMajorTimeStep((&rtM))) {
      rtDW.Merge_h = 1.0;
    }

    // End of Outputs for SubSystem: '<S68>/If V0 higher of the from 2->3 shifting velocity' 
    break;

   case 1:
    // Outputs for IfAction SubSystem: '<S68>/Other' incorporates:
    //   ActionPort: '<S74>/Action Port'

    if (rtmIsMajorTimeStep((&rtM))) {
      // UnitDelay: '<S75>/Delay Input1'
      //
      //  Block description for '<S75>/Delay Input1':
      //
      //   Store in Global RAM

      rtDW.Uk1_g = rtDW.DelayInput1_DSTATE_ao;
    }

    // DataTypeConversion: '<S74>/Data Type Conversion' incorporates:
    //   RelationalOperator: '<S75>/FixPt Relational Operator'

    rtDW.Merge_h = (static_cast<int32_T>(rtDW.RelationalOperator) > static_cast<
                    int32_T>(rtDW.Uk1_g));

    // End of Outputs for SubSystem: '<S68>/Other'
    break;
  }

  // End of If: '<S68>/If'
  if (rtmIsMajorTimeStep((&rtM))) {
    // Saturate: '<S9>/Gear limitation while shifting'
    if (rtb_SpeedRatio > 12.0) {
      rtb_GearNr_ = 12.0;
    } else if (rtb_SpeedRatio < 1.0) {
      rtb_GearNr_ = 1.0;
    } else {
      rtb_GearNr_ = rtb_SpeedRatio;
    }

    // End of Saturate: '<S9>/Gear limitation while shifting'
  }

  // MinMax: '<S2>/MinMax1'
  if ((0.0 < Product) || rtIsNaN(Product)) {
    Product = 0.0;
  }

  // End of MinMax: '<S2>/MinMax1'

  // Gain: '<S2>/Gain'
  rtDW.Gain = -15.3 * Product;
  if (rtmIsMajorTimeStep((&rtM))) {
    // Gain: '<S118>/Integral Gain'
    rtb_IntegralGain = 0.1 * rtb_Filter_a;

    // Gain: '<S166>/Integral Gain'
    rtb_IntegralGain_f = 0.0 * rtb_Filter_a;

    // Gain: '<S214>/Integral Gain'
    rtb_IntegralGain_j = 0.3 * rtb_Filter_a;
  }

  // TransferFcn: '<S2>/Transfer Fcn'
  rtb_TransferFcn = 0.0;
  rtb_TransferFcn += 5.0 * rtX.TransferFcn_CSTATE_f;
  if (rtmIsMajorTimeStep((&rtM))) {
    if (rtmIsMajorTimeStep((&rtM))) {
      // Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator1'
      rtDW.DiscreteTimeIntegrator1_DSTATE[0] += 0.1 * rtDW.vx_ms1;

      // Update for Memory: '<S25>/Memory1'
      rtDW.Memory1_PreviousInput = rtDW.Switch1;

      // Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator'
      rtDW.DiscreteTimeIntegrator_IC_LOADI = 0U;
      rtDW.DiscreteTimeIntegrator_DSTATE += 0.1 * rtDW.Switch;
      if (rtb_vx > 0.0) {
        rtDW.DiscreteTimeIntegrator_PrevRese = 1;
      } else if (rtb_vx < 0.0) {
        rtDW.DiscreteTimeIntegrator_PrevRese = -1;
      } else if (rtb_vx == 0.0) {
        rtDW.DiscreteTimeIntegrator_PrevRese = 0;
      } else {
        rtDW.DiscreteTimeIntegrator_PrevRese = 2;
      }

      // End of Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator'

      // Update for UnitDelay: '<S76>/UD'
      //
      //  Block description for '<S76>/UD':
      //
      //   Store in Global RAM

      rtDW.UD_DSTATE = rtb_TSamp;
    }

    // Update for TransportDelay: '<S2>/Transport Delay'
    {
      real_T **uBuffer = (real_T**)&rtDW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T **tBuffer = (real_T**)&rtDW.TransportDelay_PWORK.TUbufferPtrs[1];
      real_T simTime = (&rtM)->Timing.t[0];
      rtDW.TransportDelay_IWORK.Head = ((rtDW.TransportDelay_IWORK.Head <
        (rtDW.TransportDelay_IWORK.CircularBufSize-1)) ?
        (rtDW.TransportDelay_IWORK.Head+1) : 0);
      if (rtDW.TransportDelay_IWORK.Head == rtDW.TransportDelay_IWORK.Tail) {
        rtDW.TransportDelay_IWORK.Tail = ((rtDW.TransportDelay_IWORK.Tail <
          (rtDW.TransportDelay_IWORK.CircularBufSize-1)) ?
          (rtDW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*tBuffer)[rtDW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[rtDW.TransportDelay_IWORK.Head] = rtb_TransferFcn;
    }

    if (rtmIsMajorTimeStep((&rtM))) {
      // Update for Memory: '<S25>/Memory'
      rtDW.Memory_PreviousInput = rtDW.vx_ms1;

      // Update for Memory: '<S25>/Memory2'
      rtDW.Memory2_PreviousInput = rtDW.vx_ms1;

      // Update for UnitDelay: '<S32>/Delay Input1'
      //
      //  Block description for '<S32>/Delay Input1':
      //
      //   Store in Global RAM

      rtDW.DelayInput1_DSTATE_g = rtDW.Compare_d;

      // Update for UnitDelay: '<S33>/Delay Input1'
      //
      //  Block description for '<S33>/Delay Input1':
      //
      //   Store in Global RAM

      rtDW.DelayInput1_DSTATE_o = rtDW.Compare_i;

      // Update for UnitDelay: '<S31>/Unit Delay'
      rtDW.UnitDelay_DSTATE = rtDW.Switch1;

      // Update for Memory: '<S9>/IC, gear = 1'
      rtDW.ICgear1_PreviousInput = rtb_GearNr_;

      // Update for Delay: '<S2>/Delay' incorporates:
      //   Inport: '<Root>/self_acceleration'

      rtDW.Delay_DSTATE = rtU.self_acceleration;

      // Update for DiscreteIntegrator: '<S121>/Integrator'
      rtDW.Integrator_DSTATE += 0.1 * rtb_IntegralGain;

      // Update for DiscreteIntegrator: '<S116>/Filter'
      rtDW.Filter_DSTATE += 0.1 * rtb_FilterCoefficient;

      // Update for DiscreteIntegrator: '<S169>/Integrator'
      rtDW.Integrator_DSTATE_a += 0.1 * rtb_IntegralGain_f;

      // Update for DiscreteIntegrator: '<S164>/Filter'
      rtDW.Filter_DSTATE_o += 0.1 * rtb_FilterCoefficient_o;

      // Update for DiscreteIntegrator: '<S217>/Integrator'
      rtDW.Integrator_DSTATE_e += 0.1 * rtb_IntegralGain_j;

      // Update for DiscreteIntegrator: '<S212>/Filter'
      rtDW.Filter_DSTATE_d += 0.1 * rtb_FilterCoefficient_d;

      // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
      rtDW.DiscreteTimeIntegrator_DSTATE_b += 0.1 * rtDW.rads2;
      if (rtDW.DiscreteTimeIntegrator_DSTATE_b >= 240.8554367752175) {
        rtDW.DiscreteTimeIntegrator_DSTATE_b = 240.8554367752175;
      } else {
        if (rtDW.DiscreteTimeIntegrator_DSTATE_b <= 73.303828583761842) {
          rtDW.DiscreteTimeIntegrator_DSTATE_b = 73.303828583761842;
        }
      }

      // End of Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

      // Update for Delay: '<S9>/Shift_Up time'
      rtDW.Shift_Uptime_DSTATE = rtDW.Merge_h;

      // Update for Delay: '<S9>/Shift_Down time'
      rtDW.Shift_Downtime_DSTATE = rtDW.DataTypeConversion1;

      // Update for Memory: '<S9>/Memory'
      rtDW.Memory_PreviousInput_c = rtb_GearNr_;

      // Update for UnitDelay: '<S67>/Delay Input1'
      //
      //  Block description for '<S67>/Delay Input1':
      //
      //   Store in Global RAM

      rtDW.DelayInput1_DSTATE_a = rtDW.RelationalOperator1;

      // Update for UnitDelay: '<S72>/Delay Input1'
      //
      //  Block description for '<S72>/Delay Input1':
      //
      //   Store in Global RAM

      rtDW.DelayInput1_DSTATE = rtDW.Gearlimitation;
    }

    // Update for If: '<S68>/If'
    if (rtDW.If_ActiveSubsystem_l == 1) {
      // Update for IfAction SubSystem: '<S68>/Other' incorporates:
      //   ActionPort: '<S74>/Action Port'

      if (rtmIsMajorTimeStep((&rtM))) {
        // Update for UnitDelay: '<S75>/Delay Input1'
        //
        //  Block description for '<S75>/Delay Input1':
        //
        //   Store in Global RAM

        rtDW.DelayInput1_DSTATE_ao = rtDW.RelationalOperator;
      }

      // End of Update for SubSystem: '<S68>/Other'
    }

    // End of Update for If: '<S68>/If'
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep((&rtM))) {
    rt_ertODEUpdateContinuousStates(&(&rtM)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&rtM)->Timing.clockTick0;
    (&rtM)->Timing.t[0] = rtsiGetSolverStopTime(&(&rtM)->solverInfo);

    {
      // Update absolute timer for sample time: [0.1s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.1, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&rtM)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void MercedesBenzModelClass::MercedesBenz_derivatives()
{
  boolean_T lsat;
  boolean_T usat;
  XDot *_rtXdot;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S49>/Integrator'
  lsat = (rtX.Integrator_CSTATE <= -1.0);
  usat = (rtX.Integrator_CSTATE >= 1.0);
  if ((!rtDW.Compare_n) && (((!lsat) && (!usat)) || (lsat && (rtDW.Linl > 0.0)) ||
       (usat && (rtDW.Linl < 0.0)))) {
    _rtXdot->Integrator_CSTATE = rtDW.Linl;
  } else {
    // in saturation or level reset is active
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  // End of Derivatives for Integrator: '<S49>/Integrator'

  // Derivatives for Integrator: '<S37>/Integrator' incorporates:
  //   Integrator: '<S39>/Integrator'

  if (!rtDW.Compare_e) {
    _rtXdot->Integrator_CSTATE_l = rtDW.dvy_ms2;
    _rtXdot->Integrator_CSTATE_c = rtDW.ddYawAngle_rads2;
  } else {
    // level reset is active
    _rtXdot->Integrator_CSTATE_l = 0.0;

    // level reset is active
    _rtXdot->Integrator_CSTATE_c = 0.0;
  }

  // End of Derivatives for Integrator: '<S37>/Integrator'

  // Derivatives for Integrator: '<S50>/Integrator'
  if (!rtDW.Compare_n) {
    _rtXdot->Integrator_CSTATE_d = rtDW.Linl1;
  } else {
    // level reset is active
    _rtXdot->Integrator_CSTATE_d = 0.0;
  }

  // End of Derivatives for Integrator: '<S50>/Integrator'

  // Derivatives for Integrator: '<S60>/Integrator'
  lsat = (rtX.Integrator_CSTATE_b <= -1.0);
  usat = (rtX.Integrator_CSTATE_b >= 1.0);
  if ((!rtDW.Compare_g) && (((!lsat) && (!usat)) || (lsat && (rtDW.Linl_p > 0.0))
       || (usat && (rtDW.Linl_p < 0.0)))) {
    _rtXdot->Integrator_CSTATE_b = rtDW.Linl_p;
  } else {
    // in saturation or level reset is active
    _rtXdot->Integrator_CSTATE_b = 0.0;
  }

  // End of Derivatives for Integrator: '<S60>/Integrator'

  // Derivatives for Integrator: '<S59>/Integrator'
  if (!rtDW.Compare_g) {
    _rtXdot->Integrator_CSTATE_n = rtDW.Linl1_o;
  } else {
    // level reset is active
    _rtXdot->Integrator_CSTATE_n = 0.0;
  }

  // End of Derivatives for Integrator: '<S59>/Integrator'

  // Derivatives for TransferFcn: '<S24>/Torsional damping'
  _rtXdot->Torsionaldamping_CSTATE = 0.0;
  _rtXdot->Torsionaldamping_CSTATE += -10.0 * rtX.Torsionaldamping_CSTATE;
  _rtXdot->Torsionaldamping_CSTATE += rtDW.DriveTorque_Nm;

  // Derivatives for Integrator: '<S38>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.Integrator;

  // Derivatives for Integrator: '<S41>/Integrator'
  _rtXdot->Integrator_CSTATE_a = rtDW.Mass;

  // Derivatives for Integrator: '<S42>/Integrator'
  _rtXdot->Integrator_CSTATE_lg = rtDW.Inertia;

  // Derivatives for Integrator: '<S43>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.Integrator_k;

  // Derivatives for Integrator: '<S44>/Integrator'
  _rtXdot->Integrator_CSTATE_as = rtDW.Integrator_f;

  // Derivatives for Integrator: '<S40>/Integrator'
  lsat = (rtX.Integrator_CSTATE_o <= -0.087266462599716474);
  usat = (rtX.Integrator_CSTATE_o >= 0.087266462599716474);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c > 0.0)) || (usat &&
       (rtDW.Integrator_c < 0.0))) {
    _rtXdot->Integrator_CSTATE_o = rtDW.Integrator_c;
  } else {
    // in saturation
    _rtXdot->Integrator_CSTATE_o = 0.0;
  }

  // End of Derivatives for Integrator: '<S40>/Integrator'

  // Derivatives for Integrator: '<S45>/Integrator'
  _rtXdot->Integrator_CSTATE_l1 = rtDW.RollRate_rads2;

  // Derivatives for Integrator: '<S55>/Integrator'
  _rtXdot->Integrator_CSTATE_dc[0] = rtDW.TmpSignalConversionAtIntegrator[0];
  _rtXdot->Integrator_CSTATE_dc[1] = rtDW.TmpSignalConversionAtIntegrator[1];
  _rtXdot->Integrator_CSTATE_dc[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -10.0 * rtX.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += rtDW.y;

  // Derivatives for TransferFcn: '<S2>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE_f = 0.0;
  _rtXdot->TransferFcn_CSTATE_f += -5.0 * rtX.TransferFcn_CSTATE_f;
  _rtXdot->TransferFcn_CSTATE_f += rtDW.Gain;
}

// Model initialize function
void MercedesBenzModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&rtM)->solverInfo, &(&rtM)->Timing.simTimeStep);
    rtsiSetTPtr(&(&rtM)->solverInfo, &rtmGetTPtr((&rtM)));
    rtsiSetStepSizePtr(&(&rtM)->solverInfo, &(&rtM)->Timing.stepSize0);
    rtsiSetdXPtr(&(&rtM)->solverInfo, &(&rtM)->derivs);
    rtsiSetContStatesPtr(&(&rtM)->solverInfo, (real_T **) &(&rtM)->contStates);
    rtsiSetNumContStatesPtr(&(&rtM)->solverInfo, &(&rtM)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&rtM)->solverInfo, (&rtmGetErrorStatus((&rtM))));
    rtsiSetRTModelPtr(&(&rtM)->solverInfo, (&rtM));
  }

  rtsiSetSimTimeStep(&(&rtM)->solverInfo, MAJOR_TIME_STEP);
  (&rtM)->intgData.y = (&rtM)->odeY;
  (&rtM)->intgData.f[0] = (&rtM)->odeF[0];
  (&rtM)->intgData.f[1] = (&rtM)->odeF[1];
  (&rtM)->intgData.f[2] = (&rtM)->odeF[2];
  (&rtM)->contStates = ((X *) &rtX);
  rtsiSetSolverData(&(&rtM)->solverInfo, static_cast<void *>(&(&rtM)->intgData));
  rtsiSetSolverName(&(&rtM)->solverInfo,"ode3");
  rtmSetTPtr((&rtM), &(&rtM)->Timing.tArray[0]);
  (&rtM)->Timing.stepSize0 = 0.1;

  // Start for TransportDelay: '<S2>/Transport Delay'
  {
    real_T *pBuffer = &rtDW.TransportDelay_RWORK.TUbufferArea[0];
    rtDW.TransportDelay_IWORK.Tail = 0;
    rtDW.TransportDelay_IWORK.Head = 0;
    rtDW.TransportDelay_IWORK.Last = 0;
    rtDW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = (&rtM)->Timing.t[0];
    rtDW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    rtDW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[1024];
  }

  // Start for If: '<S9>/reverse//neutral//normal gear'
  rtDW.reverseneutralnormalgear_Active = -1;

  // Start for If: '<S5>/If'
  rtDW.If_ActiveSubsystem = -1;

  // Start for If: '<S80>/If'
  rtDW.If_ActiveSubsystem_j = -1;

  // Start for If: '<S68>/If'
  rtDW.If_ActiveSubsystem_l = -1;
  rtPrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  rtPrevZCX.Integrator_Reset_ZCE_h = UNINITIALIZED_ZCSIG;
  rtPrevZCX.Integrator_Reset_ZCE_f = UNINITIALIZED_ZCSIG;
  rtPrevZCX.Integrator_Reset_ZCE_e = UNINITIALIZED_ZCSIG;
  rtPrevZCX.Integrator_Reset_ZCE_j = UNINITIALIZED_ZCSIG;
  rtPrevZCX.Integrator_Reset_ZCE_a = UNINITIALIZED_ZCSIG;

  // InitializeConditions for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' 
  rtDW.DiscreteTimeIntegrator_IC_LOADI = 1U;

  // InitializeConditions for Integrator: '<S49>/Integrator'
  rtX.Integrator_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S37>/Integrator'
  rtX.Integrator_CSTATE_l = 0.0;

  // InitializeConditions for Integrator: '<S39>/Integrator'
  rtX.Integrator_CSTATE_c = 0.0;

  // InitializeConditions for Integrator: '<S50>/Integrator'
  rtX.Integrator_CSTATE_d = 0.0;

  // InitializeConditions for Integrator: '<S60>/Integrator'
  rtX.Integrator_CSTATE_b = 0.0;

  // InitializeConditions for Integrator: '<S59>/Integrator'
  rtX.Integrator_CSTATE_n = 0.0;

  // InitializeConditions for TransferFcn: '<S24>/Torsional damping'
  rtX.Torsionaldamping_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S38>/Integrator'
  rtX.Integrator_CSTATE_f = 0.0;

  // InitializeConditions for Integrator: '<S41>/Integrator'
  rtX.Integrator_CSTATE_a = 0.0;

  // InitializeConditions for Integrator: '<S42>/Integrator'
  rtX.Integrator_CSTATE_lg = 0.0;

  // InitializeConditions for Integrator: '<S43>/Integrator'
  rtX.Integrator_CSTATE_i = 0.0;

  // InitializeConditions for Integrator: '<S44>/Integrator'
  rtX.Integrator_CSTATE_as = 0.0;

  // InitializeConditions for Integrator: '<S40>/Integrator'
  rtX.Integrator_CSTATE_o = 0.0;

  // InitializeConditions for Integrator: '<S45>/Integrator'
  rtX.Integrator_CSTATE_l1 = 0.0;

  // InitializeConditions for Memory: '<S9>/IC, gear = 1'
  rtDW.ICgear1_PreviousInput = 1.0;

  // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' 
  rtDW.DiscreteTimeIntegrator_DSTATE_b = 73.303828583761842;

  // InitializeConditions for Integrator: '<S55>/Integrator'
  rtX.Integrator_CSTATE_dc[0] = 0.0;
  rtX.Integrator_CSTATE_dc[1] = 0.0;
  rtX.Integrator_CSTATE_dc[2] = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn'
  rtX.TransferFcn_CSTATE = 0.0;

  // InitializeConditions for UnitDelay: '<S72>/Delay Input1'
  //
  //  Block description for '<S72>/Delay Input1':
  //
  //   Store in Global RAM

  rtDW.DelayInput1_DSTATE = 1.0;

  // InitializeConditions for TransferFcn: '<S2>/Transfer Fcn'
  rtX.TransferFcn_CSTATE_f = 0.0;
}

// Constructor
MercedesBenzModelClass::MercedesBenzModelClass():
  rtU()
  ,rtY()
  ,rtDW()
  ,rtX()
  ,rtPrevZCX()
  ,rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
MercedesBenzModelClass::~MercedesBenzModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL * MercedesBenzModelClass::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
