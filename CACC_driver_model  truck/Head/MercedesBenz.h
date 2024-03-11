//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: MercedesBenz.h
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
#ifndef RTW_HEADER_MercedesBenz_h_
#define RTW_HEADER_MercedesBenz_h_
#include <stddef.h>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <math.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

// Model Code Variants

// Macros for accessing real-time model data structure
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#define MercedesBenz_M                 (rtM)

// Forward declaration for rtModel
typedef struct tag_RTM RT_MODEL;

// Block signals and states (default storage) for system '<Root>'
typedef struct {
  real_T TmpSignalConversionAtIntegrator[3];
  real_T DiscreteTimeIntegrator1_DSTATE[3];// '<S10>/Discrete-Time Integrator1'
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay_RWORK;              // '<S2>/Transport Delay'

  real_T vx_ms1;                       // '<S19>/Discrete-Time Integrator'
  real_T Abs;                          // '<S3>/Abs'
  real_T DeltaWheel_rad;               // '<S3>/SteerRatio'
  real_T Integrator;                   // '<S39>/Integrator'
  real_T LookupTable;                  // '<S52>/Lookup Table'
  real_T LookupTable_n;                // '<S62>/Lookup Table'
  real_T Gain1;                        // '<S22>/Gain1'
  real_T sign;                         // '<S23>/Sign'
  real_T UnitDelay;                    // '<S31>/Unit Delay'
  real_T Switch1;                      // '<S31>/Switch1'
  real_T Switch;                       // '<S25>/Switch'
  real_T ddYawAngle_rads2;             // '<S20>/Gain1'
  real_T dvy_ms2;                      // '<S20>/Sum1'
  real_T Integrator_f;                 // '<S41>/Integrator'
  real_T Integrator_k;                 // '<S42>/Integrator'
  real_T Inertia;                      // '<S21>/Inertia'
  real_T Mass;                         // '<S21>/Mass'
  real_T Integrator_c;                 // '<S45>/Integrator'
  real_T RollRate_rads2;               // '<S21>/Jxx_roll = M*L^2'
  real_T Merge;                        // '<S5>/Merge'
  real_T TransmissionGearratios;       // '<S80>/Transmission Gear ratios'
  real_T Gain1_a;                      // '<S2>/Gain1'
  real_T Gain3;                        // '<S2>/Gain3'
  real_T Delay;                        // '<S2>/Delay'
  real_T Sum;                          // '<S130>/Sum'
  real_T Sum_m;                        // '<S178>/Sum'
  real_T Sum_l;                        // '<S226>/Sum'
  real_T rpm;                          // '<S4>/rad|sec2rpm'
  real_T Product_d;                    // '<S80>/Product'
  real_T Merge_n;                      // '<S80>/Merge'
  real_T DriveTorque_Nm;               // '<S3>/FinalDriveRatio '
  real_T Linl;                         // '<S14>/Linl'
  real_T Linl1;                        // '<S14>/Linl1'
  real_T Linl_p;                       // '<S17>/Linl'
  real_T Linl1_o;                      // '<S17>/Linl1'
  real_T Product_g;                    // '<S79>/Product'
  real_T rads2;                        // '<S4>/engine + impeller inertia'
  real_T Gearlimitation;               // '<S9>/Gear limitation'
  real_T DataTypeConversion1;          // '<S9>/Data Type Conversion1'
  real_T DataTypeConversion;           // '<S68>/Data Type Conversion'
  real_T Merge_h;                      // '<S68>/Merge'
  real_T Gain;                         // '<S2>/Gain'
  real_T y;                            // '<S2>/MATLAB Function'
  real_T AlphaRear;                    // '<S64>/AlphaRear'
  real_T AlphaFront;                   // '<S54>/AlphaFront'
  real_T DiscreteTimeIntegrator_DSTATE;// '<S19>/Discrete-Time Integrator'
  real_T UD_DSTATE;                    // '<S76>/UD'
  real_T UnitDelay_DSTATE;             // '<S31>/Unit Delay'
  real_T Delay_DSTATE;                 // '<S2>/Delay'
  real_T Integrator_DSTATE;            // '<S121>/Integrator'
  real_T Filter_DSTATE;                // '<S116>/Filter'
  real_T Integrator_DSTATE_a;          // '<S169>/Integrator'
  real_T Filter_DSTATE_o;              // '<S164>/Filter'
  real_T Integrator_DSTATE_e;          // '<S217>/Integrator'
  real_T Filter_DSTATE_d;              // '<S212>/Filter'
  real_T DiscreteTimeIntegrator_DSTATE_b;// '<S4>/Discrete-Time Integrator'
  real_T Shift_Uptime_DSTATE;          // '<S9>/Shift_Up time'
  real_T Shift_Downtime_DSTATE;        // '<S9>/Shift_Down time'
  real_T DelayInput1_DSTATE;           // '<S72>/Delay Input1'
  real_T Memory1_PreviousInput;        // '<S25>/Memory1'
  real_T Memory_PreviousInput;         // '<S25>/Memory'
  real_T Memory2_PreviousInput;        // '<S25>/Memory2'
  real_T ICgear1_PreviousInput;        // '<S9>/IC, gear = 1'
  real_T Memory_PreviousInput_c;       // '<S9>/Memory'
  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              // '<S2>/Transport Delay'

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              // '<S2>/Transport Delay'

  int8_T DiscreteTimeIntegrator_PrevRese;// '<S19>/Discrete-Time Integrator'
  int8_T reverseneutralnormalgear_Active;// '<S9>/reverse//neutral//normal gear' 
  int8_T If_ActiveSubsystem;           // '<S5>/If'
  int8_T If_ActiveSubsystem_j;         // '<S80>/If'
  int8_T If_ActiveSubsystem_l;         // '<S68>/If'
  uint8_T Uk1;                         // '<S32>/Delay Input1'
  uint8_T Compare_d;                   // '<S34>/Compare'
  uint8_T Uk1_f;                       // '<S33>/Delay Input1'
  uint8_T Compare_i;                   // '<S35>/Compare'
  uint8_T DelayInput1_DSTATE_g;        // '<S32>/Delay Input1'
  uint8_T DelayInput1_DSTATE_o;        // '<S33>/Delay Input1'
  uint8_T DiscreteTimeIntegrator_IC_LOADI;// '<S19>/Discrete-Time Integrator'
  boolean_T Compare_n;                 // '<S48>/Compare'
  boolean_T Compare_e;                 // '<S36>/Compare'
  boolean_T Compare_g;                 // '<S58>/Compare'
  boolean_T LogicalOperator4;          // '<S25>/Logical Operator4'
  boolean_T RelationalOperator1;       // '<S9>/Relational Operator1'
  boolean_T Uk1_p;                     // '<S67>/Delay Input1'
  boolean_T RelationalOperator;        // '<S9>/Relational Operator'
  boolean_T Uk1_g;                     // '<S75>/Delay Input1'
  boolean_T DelayInput1_DSTATE_a;      // '<S67>/Delay Input1'
  boolean_T DelayInput1_DSTATE_ao;     // '<S75>/Delay Input1'
  boolean_T EnabledSubsystem_MODE;     // '<S57>/Enabled Subsystem'
  boolean_T EnabledSubsystem_MODE_k;   // '<S47>/Enabled Subsystem'
} DW;

// Continuous states (default storage)
typedef struct {
  real_T Integrator_CSTATE;            // '<S49>/Integrator'
  real_T Integrator_CSTATE_l;          // '<S37>/Integrator'
  real_T Integrator_CSTATE_c;          // '<S39>/Integrator'
  real_T Integrator_CSTATE_d;          // '<S50>/Integrator'
  real_T Integrator_CSTATE_b;          // '<S60>/Integrator'
  real_T Integrator_CSTATE_n;          // '<S59>/Integrator'
  real_T Torsionaldamping_CSTATE;      // '<S24>/Torsional damping'
  real_T Integrator_CSTATE_f;          // '<S38>/Integrator'
  real_T Integrator_CSTATE_a;          // '<S41>/Integrator'
  real_T Integrator_CSTATE_lg;         // '<S42>/Integrator'
  real_T Integrator_CSTATE_i;          // '<S43>/Integrator'
  real_T Integrator_CSTATE_as;         // '<S44>/Integrator'
  real_T Integrator_CSTATE_o;          // '<S40>/Integrator'
  real_T Integrator_CSTATE_l1;         // '<S45>/Integrator'
  real_T Integrator_CSTATE_dc[3];      // '<S55>/Integrator'
  real_T TransferFcn_CSTATE;           // '<S4>/Transfer Fcn'
  real_T TransferFcn_CSTATE_f;         // '<S2>/Transfer Fcn'
} X;

// State derivatives (default storage)
typedef struct {
  real_T Integrator_CSTATE;            // '<S49>/Integrator'
  real_T Integrator_CSTATE_l;          // '<S37>/Integrator'
  real_T Integrator_CSTATE_c;          // '<S39>/Integrator'
  real_T Integrator_CSTATE_d;          // '<S50>/Integrator'
  real_T Integrator_CSTATE_b;          // '<S60>/Integrator'
  real_T Integrator_CSTATE_n;          // '<S59>/Integrator'
  real_T Torsionaldamping_CSTATE;      // '<S24>/Torsional damping'
  real_T Integrator_CSTATE_f;          // '<S38>/Integrator'
  real_T Integrator_CSTATE_a;          // '<S41>/Integrator'
  real_T Integrator_CSTATE_lg;         // '<S42>/Integrator'
  real_T Integrator_CSTATE_i;          // '<S43>/Integrator'
  real_T Integrator_CSTATE_as;         // '<S44>/Integrator'
  real_T Integrator_CSTATE_o;          // '<S40>/Integrator'
  real_T Integrator_CSTATE_l1;         // '<S45>/Integrator'
  real_T Integrator_CSTATE_dc[3];      // '<S55>/Integrator'
  real_T TransferFcn_CSTATE;           // '<S4>/Transfer Fcn'
  real_T TransferFcn_CSTATE_f;         // '<S2>/Transfer Fcn'
} XDot;

// State disabled
typedef struct {
  boolean_T Integrator_CSTATE;         // '<S49>/Integrator'
  boolean_T Integrator_CSTATE_l;       // '<S37>/Integrator'
  boolean_T Integrator_CSTATE_c;       // '<S39>/Integrator'
  boolean_T Integrator_CSTATE_d;       // '<S50>/Integrator'
  boolean_T Integrator_CSTATE_b;       // '<S60>/Integrator'
  boolean_T Integrator_CSTATE_n;       // '<S59>/Integrator'
  boolean_T Torsionaldamping_CSTATE;   // '<S24>/Torsional damping'
  boolean_T Integrator_CSTATE_f;       // '<S38>/Integrator'
  boolean_T Integrator_CSTATE_a;       // '<S41>/Integrator'
  boolean_T Integrator_CSTATE_lg;      // '<S42>/Integrator'
  boolean_T Integrator_CSTATE_i;       // '<S43>/Integrator'
  boolean_T Integrator_CSTATE_as;      // '<S44>/Integrator'
  boolean_T Integrator_CSTATE_o;       // '<S40>/Integrator'
  boolean_T Integrator_CSTATE_l1;      // '<S45>/Integrator'
  boolean_T Integrator_CSTATE_dc[3];   // '<S55>/Integrator'
  boolean_T TransferFcn_CSTATE;        // '<S4>/Transfer Fcn'
  boolean_T TransferFcn_CSTATE_f;      // '<S2>/Transfer Fcn'
} XDis;

// Zero-crossing (trigger) state
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     // '<S49>/Integrator'
  ZCSigState Integrator_Reset_ZCE_h;   // '<S37>/Integrator'
  ZCSigState Integrator_Reset_ZCE_f;   // '<S39>/Integrator'
  ZCSigState Integrator_Reset_ZCE_e;   // '<S50>/Integrator'
  ZCSigState Integrator_Reset_ZCE_j;   // '<S60>/Integrator'
  ZCSigState Integrator_Reset_ZCE_a;   // '<S59>/Integrator'
} PrevZCX;

#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
typedef struct {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
} ODE3_IntgData;

#endif

// Constant parameters (default storage)
typedef struct {
  // Expression: [0 35 45 100]
  //  Referenced by: '<S16>/Lookup Table'

  real_T LookupTable_XData[4];

  // Expression: [1 1 0.2 0.2]
  //  Referenced by: '<S16>/Lookup Table'

  real_T LookupTable_YData[4];

  // Expression: [p.speedratio 1]
  //  Referenced by: '<S79>/TorqueRatio'

  real_T TorqueRatio_XData[22];

  // Expression: [p.Torqueratio 0]
  //  Referenced by: '<S79>/TorqueRatio'

  real_T TorqueRatio_YData[22];

  // Pooled Parameter (Expression: [0.01    1])
  //  Referenced by:
  //    '<S52>/Lookup Table'
  //    '<S62>/Lookup Table'

  real_T pooled12[2];

  // Expression: p.tr_in
  //  Referenced by: '<S80>/Transmission Gear ratios'

  real_T TransmissionGearratios_XData[14];

  // Expression: p.tr_out
  //  Referenced by: '<S80>/Transmission Gear ratios'

  real_T TransmissionGearratios_YData[14];

  // Expression: p.speedratio
  //  Referenced by: '<S79>/FactorK'

  real_T FactorK_XData[21];

  // Expression: p.Kfactor*p.Kcorr
  //  Referenced by: '<S79>/FactorK'

  real_T FactorK_YData[21];

  // Expression: [-5:0.1:5]*p.m/4
  //  Referenced by: '<S11>/Viscous coupling'

  real_T Viscouscoupling_XData[101];

  // Expression: p.m/4*tanh([-5:0.1:5])
  //  Referenced by: '<S11>/Viscous coupling'

  real_T Viscouscoupling_YData[101];

  // Expression: p.thvec
  //  Referenced by: '<S4>/EngineTorque'

  real_T EngineTorque_RowIdx[10];

  // Expression: p.nevec
  //  Referenced by: '<S4>/EngineTorque'

  real_T EngineTorque_ColIdx[16];

  // Expression: p.emap
  //  Referenced by: '<S4>/EngineTorque'

  real_T EngineTorque_Table[160];

  // Pooled Parameter (Mixed Expressions)
  //  Referenced by:
  //    '<S9>/interp_down'
  //    '<S9>/interp_up'

  real_T pooled24[6];

  // Expression: p.downtab
  //  Referenced by: '<S9>/interp_down'

  real_T interp_down_Table[72];

  // Expression: p.uptab
  //  Referenced by: '<S9>/interp_up'

  real_T interp_up_Table[72];
} ConstP;

// External inputs (root inport signals with default storage)
typedef struct {
  real_T self_acceleration;            // '<Root>/self_acceleration'
  real_T initial_speed;                // '<Root>/initial_speed'
} ExtU;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T output_location;              // '<Root>/output_location'
  real_T output_speed;                 // '<Root>/output_speed'
  real_T output_acceleration;          // '<Root>/output_acceleration'
} ExtY;

// Real-time Model Data Structure
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[19];
  real_T odeF[3][19];
  ODE3_IntgData intgData;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

// Constant parameters (default storage)
extern const ConstP rtConstP;
extern "C" {
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  extern "C"
{
  static real_T rtGetNaN(void);
  static real32_T rtGetNaNF(void);
}                                      // extern "C"

extern "C" {
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  static void rt_InitInfAndNaN(size_t realSize);
  static boolean_T rtIsInf(real_T value);
  static boolean_T rtIsInfF(real32_T value);
  static boolean_T rtIsNaN(real_T value);
  static boolean_T rtIsNaNF(real32_T value);
  typedef struct {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  } BigEndianIEEEDouble;

  typedef struct {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  } LittleEndianIEEEDouble;

  typedef struct {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  } IEEESingle;
}                                      // extern "C"
  // Class declaration for model MercedesBenz
  class MercedesBenzModelClass
{
  // public data and function members
 public:
  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  MercedesBenzModelClass();

  // Destructor
  ~MercedesBenzModelClass();

  // Real-Time Model get method
  RT_MODEL * getRTM();

  // private data and function members
 private:
  // Block signals and states
  DW rtDW;
  X rtX;                               // Block continuous states
  PrevZCX rtPrevZCX;                   // Triggered events

  // Real-Time Model
  RT_MODEL rtM;

  // private member function(s) for subsystem '<Root>'
  int32_T bsearch(const real_T x[10], real_T xi);

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void MercedesBenz_derivatives();
}

;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S46>/Derivative' : Unused code path elimination
//  Block '<S21>/Multiport Switch1' : Unused code path elimination
//  Block '<S3>/Gain' : Unused code path elimination
//  Block '<S3>/Product' : Unused code path elimination
//  Block '<S3>/to_kW' : Unused code path elimination
//  Block '<S4>/Gain' : Unused code path elimination
//  Block '<S4>/Product' : Unused code path elimination
//  Block '<S4>/to_kW' : Unused code path elimination
//  Block '<S1>/Gain' : Unused code path elimination
//  Block '<S6>/Gain' : Unused code path elimination
//  Block '<S7>/Gain' : Unused code path elimination
//  Block '<S8>/Data Type Duplicate' : Unused code path elimination
//  Block '<S8>/Data Type Propagation' : Unused code path elimination
//  Block '<S76>/Data Type Duplicate' : Unused code path elimination
//  Block '<S77>/Data Type Duplicate' : Unused code path elimination
//  Block '<S78>/Data Type Duplicate' : Unused code path elimination
//  Block '<S2>/Gain4' : Eliminated nontunable gain of 1
//  Block '<S2>/Gain5' : Eliminated nontunable gain of 1
//  Block '<S14>/Constant' : Unused code path elimination
//  Block '<S14>/Constant1' : Unused code path elimination
//  Block '<S14>/alg.loop' : Unused code path elimination
//  Block '<S17>/Constant1' : Unused code path elimination
//  Block '<S17>/Constant2' : Unused code path elimination
//  Block '<S17>/alg.loop' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'MercedesBenz'
//  '<S1>'   : 'MercedesBenz/Dynamics_Simple'
//  '<S2>'   : 'MercedesBenz/low-level'
//  '<S3>'   : 'MercedesBenz/Dynamics_Simple/Chassis'
//  '<S4>'   : 'MercedesBenz/Dynamics_Simple/Engine'
//  '<S5>'   : 'MercedesBenz/Dynamics_Simple/Gear: Auto Manual'
//  '<S6>'   : 'MercedesBenz/Dynamics_Simple/Radians to Degrees'
//  '<S7>'   : 'MercedesBenz/Dynamics_Simple/Radians to Degrees1'
//  '<S8>'   : 'MercedesBenz/Dynamics_Simple/Saturation Dynamic'
//  '<S9>'   : 'MercedesBenz/Dynamics_Simple/ShiftLogic'
//  '<S10>'  : 'MercedesBenz/Dynamics_Simple/Stateupdate'
//  '<S11>'  : 'MercedesBenz/Dynamics_Simple/Transmission'
//  '<S12>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]'
//  '<S13>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Degrees to Radians'
//  '<S14>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre'
//  '<S15>'  : 'MercedesBenz/Dynamics_Simple/Chassis/MuxDynState'
//  '<S16>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Power Assisted Steering'
//  '<S17>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre'
//  '<S18>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Fyi --> Fy // Mz'
//  '<S19>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion'
//  '<S20>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Y & Yaw_Motion'
//  '<S21>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion'
//  '<S22>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Air&RoadResistance'
//  '<S23>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/BrakeSystem'
//  '<S24>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Configurable Subsystem1'
//  '<S25>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection'
//  '<S26>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/Compare To Zero'
//  '<S27>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/Compare To Zero1'
//  '<S28>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/Compare To Zero2'
//  '<S29>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/Compare To Zero3'
//  '<S30>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/Configurable Subsystem'
//  '<S31>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/SR-Memory'
//  '<S32>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/SR-Memory/Detect Rise Positive'
//  '<S33>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/SR-Memory/Detect Rise Positive1'
//  '<S34>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/SR-Memory/Detect Rise Positive/Positive'
//  '<S35>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/X_Motion/Max RPM and zero- velocity detection/SR-Memory/Detect Rise Positive1/Positive'
//  '<S36>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Y & Yaw_Motion/Compare To Zero'
//  '<S37>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Y & Yaw_Motion/Configurable Subsystem'
//  '<S38>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Y & Yaw_Motion/Configurable Subsystem1'
//  '<S39>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Y & Yaw_Motion/Configurable Subsystem2'
//  '<S40>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem'
//  '<S41>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem1'
//  '<S42>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem2'
//  '<S43>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem3'
//  '<S44>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem4'
//  '<S45>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem5'
//  '<S46>'  : 'MercedesBenz/Dynamics_Simple/Chassis/Bicycle_model_[XYZ]/Z, Pitch_Motion & Roll_Motion/Configurable Subsystem9'
//  '<S47>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/AlphaFront'
//  '<S48>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/Compare To Zero'
//  '<S49>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/Configurable Subsystem'
//  '<S50>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/Configurable Subsystem1'
//  '<S51>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/If MC'
//  '<S52>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/Prevent_instability_at_low_Vx'
//  '<S53>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/AlphaFront/Compare To Constant'
//  '<S54>'  : 'MercedesBenz/Dynamics_Simple/Chassis/FrontTyre/AlphaFront/Enabled Subsystem'
//  '<S55>'  : 'MercedesBenz/Dynamics_Simple/Chassis/MuxDynState/Configurable Subsystem1'
//  '<S56>'  : 'MercedesBenz/Dynamics_Simple/Chassis/MuxDynState/Transformation_BODY2GLOBAL'
//  '<S57>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/AlphaRear'
//  '<S58>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/Compare To Zero'
//  '<S59>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/Configurable Subsystem'
//  '<S60>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/Configurable Subsystem1'
//  '<S61>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/If MC'
//  '<S62>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/Prevent_instability_at_low_Vx'
//  '<S63>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/AlphaRear/Compare To Constant'
//  '<S64>'  : 'MercedesBenz/Dynamics_Simple/Chassis/RearTyre/AlphaRear/Enabled Subsystem'
//  '<S65>'  : 'MercedesBenz/Dynamics_Simple/Gear: Auto Manual/If Action Subsystem'
//  '<S66>'  : 'MercedesBenz/Dynamics_Simple/Gear: Auto Manual/If Action Subsystem1'
//  '<S67>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/Detect Increase1'
//  '<S68>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/Detect Increase'
//  '<S69>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/If Action Neutral'
//  '<S70>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/If Action Normal'
//  '<S71>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/If Action Reverse'
//  '<S72>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/Detect Increase/Detect Increase'
//  '<S73>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/Detect Increase/If V0 higher of the from 2->3 shifting velocity'
//  '<S74>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/Detect Increase/Other'
//  '<S75>'  : 'MercedesBenz/Dynamics_Simple/ShiftLogic/Detect Increase/Other/Detect Increase'
//  '<S76>'  : 'MercedesBenz/Dynamics_Simple/Stateupdate/Discrete Derivative'
//  '<S77>'  : 'MercedesBenz/Dynamics_Simple/Stateupdate/Discrete Derivative1'
//  '<S78>'  : 'MercedesBenz/Dynamics_Simple/Stateupdate/Discrete Derivative2'
//  '<S79>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Torque_Converter'
//  '<S80>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Transmission_Ratio'
//  '<S81>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Torque_Converter/Compare To Constant'
//  '<S82>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Torque_Converter/Compare To Zero'
//  '<S83>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Transmission_Ratio/If Action Neutral'
//  '<S84>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Transmission_Ratio/If Action Normal'
//  '<S85>'  : 'MercedesBenz/Dynamics_Simple/Transmission/Transmission_Ratio/If Action Reverse'
//  '<S86>'  : 'MercedesBenz/low-level/MATLAB Function'
//  '<S87>'  : 'MercedesBenz/low-level/PID Controller'
//  '<S88>'  : 'MercedesBenz/low-level/PID Controller1'
//  '<S89>'  : 'MercedesBenz/low-level/PID Controller2'
//  '<S90>'  : 'MercedesBenz/low-level/PID Controller/Anti-windup'
//  '<S91>'  : 'MercedesBenz/low-level/PID Controller/D Gain'
//  '<S92>'  : 'MercedesBenz/low-level/PID Controller/Filter'
//  '<S93>'  : 'MercedesBenz/low-level/PID Controller/Filter ICs'
//  '<S94>'  : 'MercedesBenz/low-level/PID Controller/I Gain'
//  '<S95>'  : 'MercedesBenz/low-level/PID Controller/Ideal P Gain'
//  '<S96>'  : 'MercedesBenz/low-level/PID Controller/Ideal P Gain Fdbk'
//  '<S97>'  : 'MercedesBenz/low-level/PID Controller/Integrator'
//  '<S98>'  : 'MercedesBenz/low-level/PID Controller/Integrator ICs'
//  '<S99>'  : 'MercedesBenz/low-level/PID Controller/N Copy'
//  '<S100>' : 'MercedesBenz/low-level/PID Controller/N Gain'
//  '<S101>' : 'MercedesBenz/low-level/PID Controller/P Copy'
//  '<S102>' : 'MercedesBenz/low-level/PID Controller/Parallel P Gain'
//  '<S103>' : 'MercedesBenz/low-level/PID Controller/Reset Signal'
//  '<S104>' : 'MercedesBenz/low-level/PID Controller/Saturation'
//  '<S105>' : 'MercedesBenz/low-level/PID Controller/Saturation Fdbk'
//  '<S106>' : 'MercedesBenz/low-level/PID Controller/Sum'
//  '<S107>' : 'MercedesBenz/low-level/PID Controller/Sum Fdbk'
//  '<S108>' : 'MercedesBenz/low-level/PID Controller/Tracking Mode'
//  '<S109>' : 'MercedesBenz/low-level/PID Controller/Tracking Mode Sum'
//  '<S110>' : 'MercedesBenz/low-level/PID Controller/Tsamp - Integral'
//  '<S111>' : 'MercedesBenz/low-level/PID Controller/Tsamp - Ngain'
//  '<S112>' : 'MercedesBenz/low-level/PID Controller/postSat Signal'
//  '<S113>' : 'MercedesBenz/low-level/PID Controller/preSat Signal'
//  '<S114>' : 'MercedesBenz/low-level/PID Controller/Anti-windup/Passthrough'
//  '<S115>' : 'MercedesBenz/low-level/PID Controller/D Gain/Internal Parameters'
//  '<S116>' : 'MercedesBenz/low-level/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S117>' : 'MercedesBenz/low-level/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S118>' : 'MercedesBenz/low-level/PID Controller/I Gain/Internal Parameters'
//  '<S119>' : 'MercedesBenz/low-level/PID Controller/Ideal P Gain/Passthrough'
//  '<S120>' : 'MercedesBenz/low-level/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S121>' : 'MercedesBenz/low-level/PID Controller/Integrator/Discrete'
//  '<S122>' : 'MercedesBenz/low-level/PID Controller/Integrator ICs/Internal IC'
//  '<S123>' : 'MercedesBenz/low-level/PID Controller/N Copy/Disabled'
//  '<S124>' : 'MercedesBenz/low-level/PID Controller/N Gain/Internal Parameters'
//  '<S125>' : 'MercedesBenz/low-level/PID Controller/P Copy/Disabled'
//  '<S126>' : 'MercedesBenz/low-level/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S127>' : 'MercedesBenz/low-level/PID Controller/Reset Signal/Disabled'
//  '<S128>' : 'MercedesBenz/low-level/PID Controller/Saturation/Passthrough'
//  '<S129>' : 'MercedesBenz/low-level/PID Controller/Saturation Fdbk/Disabled'
//  '<S130>' : 'MercedesBenz/low-level/PID Controller/Sum/Sum_PID'
//  '<S131>' : 'MercedesBenz/low-level/PID Controller/Sum Fdbk/Disabled'
//  '<S132>' : 'MercedesBenz/low-level/PID Controller/Tracking Mode/Disabled'
//  '<S133>' : 'MercedesBenz/low-level/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S134>' : 'MercedesBenz/low-level/PID Controller/Tsamp - Integral/Passthrough'
//  '<S135>' : 'MercedesBenz/low-level/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S136>' : 'MercedesBenz/low-level/PID Controller/postSat Signal/Forward_Path'
//  '<S137>' : 'MercedesBenz/low-level/PID Controller/preSat Signal/Forward_Path'
//  '<S138>' : 'MercedesBenz/low-level/PID Controller1/Anti-windup'
//  '<S139>' : 'MercedesBenz/low-level/PID Controller1/D Gain'
//  '<S140>' : 'MercedesBenz/low-level/PID Controller1/Filter'
//  '<S141>' : 'MercedesBenz/low-level/PID Controller1/Filter ICs'
//  '<S142>' : 'MercedesBenz/low-level/PID Controller1/I Gain'
//  '<S143>' : 'MercedesBenz/low-level/PID Controller1/Ideal P Gain'
//  '<S144>' : 'MercedesBenz/low-level/PID Controller1/Ideal P Gain Fdbk'
//  '<S145>' : 'MercedesBenz/low-level/PID Controller1/Integrator'
//  '<S146>' : 'MercedesBenz/low-level/PID Controller1/Integrator ICs'
//  '<S147>' : 'MercedesBenz/low-level/PID Controller1/N Copy'
//  '<S148>' : 'MercedesBenz/low-level/PID Controller1/N Gain'
//  '<S149>' : 'MercedesBenz/low-level/PID Controller1/P Copy'
//  '<S150>' : 'MercedesBenz/low-level/PID Controller1/Parallel P Gain'
//  '<S151>' : 'MercedesBenz/low-level/PID Controller1/Reset Signal'
//  '<S152>' : 'MercedesBenz/low-level/PID Controller1/Saturation'
//  '<S153>' : 'MercedesBenz/low-level/PID Controller1/Saturation Fdbk'
//  '<S154>' : 'MercedesBenz/low-level/PID Controller1/Sum'
//  '<S155>' : 'MercedesBenz/low-level/PID Controller1/Sum Fdbk'
//  '<S156>' : 'MercedesBenz/low-level/PID Controller1/Tracking Mode'
//  '<S157>' : 'MercedesBenz/low-level/PID Controller1/Tracking Mode Sum'
//  '<S158>' : 'MercedesBenz/low-level/PID Controller1/Tsamp - Integral'
//  '<S159>' : 'MercedesBenz/low-level/PID Controller1/Tsamp - Ngain'
//  '<S160>' : 'MercedesBenz/low-level/PID Controller1/postSat Signal'
//  '<S161>' : 'MercedesBenz/low-level/PID Controller1/preSat Signal'
//  '<S162>' : 'MercedesBenz/low-level/PID Controller1/Anti-windup/Passthrough'
//  '<S163>' : 'MercedesBenz/low-level/PID Controller1/D Gain/Internal Parameters'
//  '<S164>' : 'MercedesBenz/low-level/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S165>' : 'MercedesBenz/low-level/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S166>' : 'MercedesBenz/low-level/PID Controller1/I Gain/Internal Parameters'
//  '<S167>' : 'MercedesBenz/low-level/PID Controller1/Ideal P Gain/Passthrough'
//  '<S168>' : 'MercedesBenz/low-level/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S169>' : 'MercedesBenz/low-level/PID Controller1/Integrator/Discrete'
//  '<S170>' : 'MercedesBenz/low-level/PID Controller1/Integrator ICs/Internal IC'
//  '<S171>' : 'MercedesBenz/low-level/PID Controller1/N Copy/Disabled'
//  '<S172>' : 'MercedesBenz/low-level/PID Controller1/N Gain/Internal Parameters'
//  '<S173>' : 'MercedesBenz/low-level/PID Controller1/P Copy/Disabled'
//  '<S174>' : 'MercedesBenz/low-level/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S175>' : 'MercedesBenz/low-level/PID Controller1/Reset Signal/Disabled'
//  '<S176>' : 'MercedesBenz/low-level/PID Controller1/Saturation/Passthrough'
//  '<S177>' : 'MercedesBenz/low-level/PID Controller1/Saturation Fdbk/Disabled'
//  '<S178>' : 'MercedesBenz/low-level/PID Controller1/Sum/Sum_PID'
//  '<S179>' : 'MercedesBenz/low-level/PID Controller1/Sum Fdbk/Disabled'
//  '<S180>' : 'MercedesBenz/low-level/PID Controller1/Tracking Mode/Disabled'
//  '<S181>' : 'MercedesBenz/low-level/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S182>' : 'MercedesBenz/low-level/PID Controller1/Tsamp - Integral/Passthrough'
//  '<S183>' : 'MercedesBenz/low-level/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S184>' : 'MercedesBenz/low-level/PID Controller1/postSat Signal/Forward_Path'
//  '<S185>' : 'MercedesBenz/low-level/PID Controller1/preSat Signal/Forward_Path'
//  '<S186>' : 'MercedesBenz/low-level/PID Controller2/Anti-windup'
//  '<S187>' : 'MercedesBenz/low-level/PID Controller2/D Gain'
//  '<S188>' : 'MercedesBenz/low-level/PID Controller2/Filter'
//  '<S189>' : 'MercedesBenz/low-level/PID Controller2/Filter ICs'
//  '<S190>' : 'MercedesBenz/low-level/PID Controller2/I Gain'
//  '<S191>' : 'MercedesBenz/low-level/PID Controller2/Ideal P Gain'
//  '<S192>' : 'MercedesBenz/low-level/PID Controller2/Ideal P Gain Fdbk'
//  '<S193>' : 'MercedesBenz/low-level/PID Controller2/Integrator'
//  '<S194>' : 'MercedesBenz/low-level/PID Controller2/Integrator ICs'
//  '<S195>' : 'MercedesBenz/low-level/PID Controller2/N Copy'
//  '<S196>' : 'MercedesBenz/low-level/PID Controller2/N Gain'
//  '<S197>' : 'MercedesBenz/low-level/PID Controller2/P Copy'
//  '<S198>' : 'MercedesBenz/low-level/PID Controller2/Parallel P Gain'
//  '<S199>' : 'MercedesBenz/low-level/PID Controller2/Reset Signal'
//  '<S200>' : 'MercedesBenz/low-level/PID Controller2/Saturation'
//  '<S201>' : 'MercedesBenz/low-level/PID Controller2/Saturation Fdbk'
//  '<S202>' : 'MercedesBenz/low-level/PID Controller2/Sum'
//  '<S203>' : 'MercedesBenz/low-level/PID Controller2/Sum Fdbk'
//  '<S204>' : 'MercedesBenz/low-level/PID Controller2/Tracking Mode'
//  '<S205>' : 'MercedesBenz/low-level/PID Controller2/Tracking Mode Sum'
//  '<S206>' : 'MercedesBenz/low-level/PID Controller2/Tsamp - Integral'
//  '<S207>' : 'MercedesBenz/low-level/PID Controller2/Tsamp - Ngain'
//  '<S208>' : 'MercedesBenz/low-level/PID Controller2/postSat Signal'
//  '<S209>' : 'MercedesBenz/low-level/PID Controller2/preSat Signal'
//  '<S210>' : 'MercedesBenz/low-level/PID Controller2/Anti-windup/Passthrough'
//  '<S211>' : 'MercedesBenz/low-level/PID Controller2/D Gain/Internal Parameters'
//  '<S212>' : 'MercedesBenz/low-level/PID Controller2/Filter/Disc. Forward Euler Filter'
//  '<S213>' : 'MercedesBenz/low-level/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S214>' : 'MercedesBenz/low-level/PID Controller2/I Gain/Internal Parameters'
//  '<S215>' : 'MercedesBenz/low-level/PID Controller2/Ideal P Gain/Passthrough'
//  '<S216>' : 'MercedesBenz/low-level/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S217>' : 'MercedesBenz/low-level/PID Controller2/Integrator/Discrete'
//  '<S218>' : 'MercedesBenz/low-level/PID Controller2/Integrator ICs/Internal IC'
//  '<S219>' : 'MercedesBenz/low-level/PID Controller2/N Copy/Disabled'
//  '<S220>' : 'MercedesBenz/low-level/PID Controller2/N Gain/Internal Parameters'
//  '<S221>' : 'MercedesBenz/low-level/PID Controller2/P Copy/Disabled'
//  '<S222>' : 'MercedesBenz/low-level/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S223>' : 'MercedesBenz/low-level/PID Controller2/Reset Signal/Disabled'
//  '<S224>' : 'MercedesBenz/low-level/PID Controller2/Saturation/Passthrough'
//  '<S225>' : 'MercedesBenz/low-level/PID Controller2/Saturation Fdbk/Disabled'
//  '<S226>' : 'MercedesBenz/low-level/PID Controller2/Sum/Sum_PID'
//  '<S227>' : 'MercedesBenz/low-level/PID Controller2/Sum Fdbk/Disabled'
//  '<S228>' : 'MercedesBenz/low-level/PID Controller2/Tracking Mode/Disabled'
//  '<S229>' : 'MercedesBenz/low-level/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S230>' : 'MercedesBenz/low-level/PID Controller2/Tsamp - Integral/Passthrough'
//  '<S231>' : 'MercedesBenz/low-level/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S232>' : 'MercedesBenz/low-level/PID Controller2/postSat Signal/Forward_Path'
//  '<S233>' : 'MercedesBenz/low-level/PID Controller2/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_MercedesBenz_h_

//
// File trailer for generated code.
//
// [EOF]
//
