/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
*  1-May-08 | REQ #033: Created
*  8-May-08 | REQ #042: Unicode conversion
*****************************************************************************/
#pragma once                                                        // REQ #033
                                                                    // REQ #033
void ShowDCState(LPCTSTR where, CDC & dc);                          // REQ #033
#define _HERE3(x) _T(#x)                                            // REQ #033// REQ #042
#define _HERE2(x) _HERE3(x)                                         // REQ #033
#define _HERE(x) (_T(__FILE__) _T("(") _HERE2(__LINE__) _T("): ") _T(__FUNCTION__) x)// REQ #033

