/*****************************************************************************
*           Change Log
*  Date     | Change
*-----------+-----------------------------------------------------------------
* 27-Apr-08 | Created change log
* 27-Apr-08 | REQ #007: Added #pragma once
*****************************************************************************/

#pragma once                                                        // REQ #007

class KERNINFO {
   public:
        // Constructors
        KERNINFO(CDC * dc);
        ~KERNINFO();

        // Data
        int count;
        LPKERNINGPAIR pairs;

        // Methods
        LPKERNINGPAIR findPair(UINT first, UINT second);
               };


