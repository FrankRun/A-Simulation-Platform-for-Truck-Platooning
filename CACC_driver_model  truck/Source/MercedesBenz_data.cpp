//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: MercedesBenz_data.cpp
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

// Constant parameters (default storage)
const ConstP rtConstP = {
  // Expression: [0 35 45 100]
  //  Referenced by: '<S16>/Lookup Table'

  { 0.0, 35.0, 45.0, 100.0 },

  // Expression: [1 1 0.2 0.2]
  //  Referenced by: '<S16>/Lookup Table'

  { 1.0, 1.0, 0.2, 0.2 },

  // Expression: [p.speedratio 1]
  //  Referenced by: '<S79>/TorqueRatio'

  { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.81, 0.82, 0.83, 0.84, 0.85,
    0.86, 0.87, 0.88, 0.89, 0.9, 0.92, 0.94, 1.0 },

  // Expression: [p.Torqueratio 0]
  //  Referenced by: '<S79>/TorqueRatio'

  { 2.0, 1.8, 1.65, 1.5, 1.4, 1.282, 1.2045, 1.127, 1.048, 1.04, 1.0305, 1.0215,
    1.014, 1.006, 1.001, 1.001, 1.0005, 0.999, 0.9995, 1.0005, 1.001, 0.0 },

  // Pooled Parameter (Expression: [0.01    1])
  //  Referenced by:
  //    '<S52>/Lookup Table'
  //    '<S62>/Lookup Table'

  { 0.01, 1.0 },

  // Expression: p.tr_in
  //  Referenced by: '<S80>/Transmission Gear ratios'

  { -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 },

  // Expression: p.tr_out
  //  Referenced by: '<S80>/Transmission Gear ratios'

  { 14.93, 0.0, 14.93, 11.64, 9.02, 7.04, 5.64, 4.4, 3.39, 2.65, 2.05, 1.6, 1.28,
    1.0 },

  // Expression: p.speedratio
  //  Referenced by: '<S79>/FactorK'

  { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.81, 0.82, 0.83, 0.84, 0.85,
    0.86, 0.87, 0.88, 0.89, 0.9, 0.92, 0.94 },

  // Expression: p.Kfactor*p.Kcorr
  //  Referenced by: '<S79>/FactorK'

  { 6.6640761699999995, 6.6640761699999995, 6.60761146, 6.60761146,
    6.6640761699999995, 6.8335242299999992, 7.059437, 7.3982791899999993,
    7.90656944, 7.9630341499999995, 8.07596357, 8.13242828, 8.24541163,
    8.35834105, 8.52778911, 8.69718324, 8.92309601, 9.20547349,
    9.6008343199999988, 10.44796676, 11.85980023 },

  // Expression: [-5:0.1:5]*p.m/4
  //  Referenced by: '<S11>/Viscous coupling'

  { -8937.5, -8758.75, -8580.0, -8401.25, -8222.5, -8043.75, -7865.0000000000009,
    -7686.25, -7507.5, -7328.7499999999991, -7150.0, -6971.25, -6792.5, -6613.75,
    -6434.9999999999991, -6256.25, -6077.5, -5898.75, -5720.0,
    -5541.2499999999991, -5362.5, -5183.75, -5005.0, -4826.2499999999991,
    -4647.4999999999991, -4468.75, -4290.0, -4111.25, -3932.4999999999995,
    -3753.7499999999995, -3575.0, -3396.25, -3217.4999999999995,
    -3038.7499999999995, -2859.9999999999995, -2681.25, -2502.5,
    -2323.7499999999995, -2144.9999999999995, -1966.2499999999993, -1787.5,
    -1608.7499999999991, -1429.9999999999998, -1251.2500000000002,
    -1072.4999999999993, -893.75, -714.99999999999909, -536.24999999999966,
    -357.49999999999875, -178.74999999999937, 0.0, 178.74999999999937,
    357.49999999999875, 536.24999999999966, 714.99999999999909, 893.75,
    1072.4999999999993, 1251.2500000000002, 1429.9999999999998,
    1608.7499999999991, 1787.5, 1966.2499999999993, 2144.9999999999995,
    2323.7499999999995, 2502.5, 2681.25, 2859.9999999999995, 3038.7499999999995,
    3217.4999999999995, 3396.25, 3575.0, 3753.7499999999995, 3932.4999999999995,
    4111.25, 4290.0, 4468.75, 4647.4999999999991, 4826.2499999999991, 5005.0,
    5183.75, 5362.5, 5541.2499999999991, 5720.0, 5898.75, 6077.5, 6256.25,
    6434.9999999999991, 6613.75, 6792.5, 6971.25, 7150.0, 7328.7499999999991,
    7507.5, 7686.25, 7865.0000000000009, 8043.75, 8222.5, 8401.25, 8580.0,
    8758.75, 8937.5 },

  // Expression: p.m/4*tanh([-5:0.1:5])
  //  Referenced by: '<S11>/Viscous coupling'

  { -1787.3377026193887, -1787.301771524116, -1787.2578861651093,
    -1787.2042859283051, -1787.1388206317797, -1787.0588643908491,
    -1786.9612104699363, -1786.8419429397557, -1786.6962800464159,
    -1786.5183830919377, -1786.3011232835822, -1786.0357973851749,
    -1785.7117810421905, -1785.3161062900222, -1784.8329469190339,
    -1784.2429919800177, -1783.5226836825243, -1782.6432911772165,
    -1781.5697861383765, -1780.2594796091466, -1778.6603722150307,
    -1776.7091616391672, -1774.3288423595163, -1771.4258234496351,
    -1767.8864814344647, -1763.5730579456817, -1758.3188081274534,
    -1751.9223083258171, -1744.1408449312196, -1734.6828366965487,
    -1723.1992993855226, -1709.2744564033337, -1692.4157479627047,
    -1672.0437137030394, -1647.4825410015674, -1617.9525033901987,
    -1582.5660711615442, -1540.330147272535, -1490.1576100342274,
    -1430.8920013971253, -1361.3495537709296, -1280.3824429807557,
    -1186.9657268537799, -1080.30740159693, -959.97610100898771,
    -826.03441860226735, -679.15877003121363, -520.72129475721852,
    -352.80838490201472, -178.1565403921079, 0.0, 178.1565403921079,
    352.80838490201472, 520.72129475721852, 679.15877003121363,
    826.03441860226735, 959.97610100898771, 1080.30740159693, 1186.9657268537799,
    1280.3824429807557, 1361.3495537709296, 1430.8920013971253,
    1490.1576100342274, 1540.330147272535, 1582.5660711615442,
    1617.9525033901987, 1647.4825410015674, 1672.0437137030394,
    1692.4157479627047, 1709.2744564033337, 1723.1992993855226,
    1734.6828366965487, 1744.1408449312196, 1751.9223083258171,
    1758.3188081274534, 1763.5730579456817, 1767.8864814344647,
    1771.4258234496351, 1774.3288423595163, 1776.7091616391672,
    1778.6603722150307, 1780.2594796091466, 1781.5697861383765,
    1782.6432911772165, 1783.5226836825243, 1784.2429919800177,
    1784.8329469190339, 1785.3161062900222, 1785.7117810421905,
    1786.0357973851749, 1786.3011232835822, 1786.5183830919377,
    1786.6962800464159, 1786.8419429397557, 1786.9612104699363,
    1787.0588643908491, 1787.1388206317797, 1787.2042859283051,
    1787.2578861651093, 1787.301771524116, 1787.3377026193887 },

  // Expression: p.thvec
  //  Referenced by: '<S4>/EngineTorque'

  { 0.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 },

  // Expression: p.nevec
  //  Referenced by: '<S4>/EngineTorque'

  { 700.0, 800.0, 1000.0, 1025.0, 1050.0, 1075.0, 1100.0, 1125.0, 1250.0, 1375.0,
    1500.0, 1625.0, 1750.0, 1875.0, 2000.0, 2300.0 },

  // Expression: p.emap
  //  Referenced by: '<S4>/EngineTorque'

  { -40.0, 621.0, 689.0, 756.0, 982.0, 1262.0, 1487.0, 1739.0, 1964.0, 2244.0,
    -44.0, 628.0, 699.0, 770.0, 1006.0, 1283.0, 1519.0, 1777.0, 2013.0, 2290.0,
    -54.0, 643.0, 721.0, 798.0, 1055.0, 1325.0, 1583.0, 1853.0, 2111.0, 2380.0,
    -55.0, 645.0, 723.0, 801.0, 1061.0, 1331.0, 1591.0, 1863.0, 2123.0, 2392.0,
    -56.0, 646.0, 725.0, 803.0, 1065.0, 1333.0, 1595.0, 1868.0, 2130.0, 2399.0,
    -58.0, 645.0, 724.0, 803.0, 1066.0, 1333.0, 1596.0, 1869.0, 2132.0, 2398.0,
    -59.0, 644.0, 723.0, 803.0, 1066.0, 1332.0, 1596.0, 1869.0, 2133.0, 2398.0,
    -60.0, 643.0, 722.0, 802.0, 1066.0, 1330.0, 1595.0, 1868.0, 2132.0, 2396.0,
    -63.0, 635.0, 713.0, 792.0, 1053.0, 1314.0, 1575.0, 1844.0, 2105.0, 2366.0,
    -66.0, 256.0, 513.0, 778.0, 1034.0, 1291.0, 1547.0, 1813.0, 2069.0, 2326.0,
    -72.0, 251.0, 503.0, 762.0, 1014.0, 1265.0, 1517.0, 1776.0, 2028.0, 2279.0,
    -77.0, 247.0, 487.0, 734.0, 973.0, 1221.0, 1460.0, 1708.0, 1947.0, 2194.0,
    -83.0, 224.0, 456.0, 681.0, 913.0, 1137.0, 1369.0, 1594.0, 1826.0, 2050.0,
    -88.0, 211.0, 422.0, 634.0, 845.0, 1056.0, 1267.0, 1478.0, 1690.0, 1901.0,
    -95.0, 180.0, 345.0, 525.0, 705.0, 870.0, 1050.0, 1230.0, 1395.0, 1575.0,
    -112.0, 105.0, 159.0, 264.0, 369.0, 424.0, 527.0, 634.0, 688.0, 793.0 },

  // Pooled Parameter (Mixed Expressions)
  //  Referenced by:
  //    '<S9>/interp_down'
  //    '<S9>/interp_up'

  { 0.0, 25.0, 35.0, 50.0, 90.0, 100.0 },

  // Expression: p.downtab
  //  Referenced by: '<S9>/interp_down'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.362343, 6.362343, 6.362343, 6.362343,
    6.362343, 6.362343, 8.160634, 8.160634, 8.160634, 8.160634, 8.160634,
    8.160634, 10.5310173, 10.5310173, 10.5310173, 10.5310173, 10.5310173,
    10.5310173, 13.4928656, 13.4928656, 13.4928656, 13.4928656, 13.4928656,
    13.4928656, 16.84216, 16.84216, 16.84216, 16.84216, 16.84216, 16.84216,
    21.5885849, 21.5885849, 21.5885849, 21.5885849, 21.5885849, 21.5885849,
    28.0205822, 28.0205822, 28.0205822, 28.0205822, 28.0205822, 28.0205822,
    35.8452, 35.8452, 35.8452, 35.8452, 35.8452, 35.8452, 46.3364754, 46.3364754,
    46.3364754, 46.3364754, 46.3364754, 46.3364754, 59.36861, 59.36861, 59.36861,
    59.36861, 59.36861, 59.36861, 74.21076, 74.21076, 74.21076, 74.21076,
    74.21076, 74.21076 },

  // Expression: p.uptab
  //  Referenced by: '<S9>/interp_up'

  { 8.675921, 8.675921, 8.675921, 8.675921, 8.675921, 8.675921, 11.1281366,
    11.1281366, 11.1281366, 11.1281366, 11.1281366, 11.1281366, 14.3604784,
    14.3604784, 14.3604784, 14.3604784, 14.3604784, 14.3604784, 18.3993626,
    18.3993626, 18.3993626, 18.3993626, 18.3993626, 18.3993626, 22.96658,
    22.96658, 22.96658, 22.96658, 22.96658, 22.96658, 29.43898, 29.43898,
    29.43898, 29.43898, 29.43898, 29.43898, 38.2098846, 38.2098846, 38.2098846,
    38.2098846, 38.2098846, 38.2098846, 48.879818, 48.879818, 48.879818,
    48.879818, 48.879818, 48.879818, 63.1861038, 63.1861038, 63.1861038,
    63.1861038, 63.1861038, 63.1861038, 80.9572, 80.9572, 80.9572, 80.9572,
    80.9572, 80.9572, 101.196495, 101.196495, 101.196495, 101.196495, 101.196495,
    101.196495, 300.0, 300.0, 300.0, 300.0, 300.0, 300.0 }
};

//
// File trailer for generated code.
//
// [EOF]
//