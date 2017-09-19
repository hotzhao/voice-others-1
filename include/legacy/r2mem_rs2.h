//
//  r2mem_rs2.h
//  r2ad2
//
//  Created by hadoop on 4/19/17.
//  Copyright © 2017 hadoop. All rights reserved.
//

#ifndef __r2ad2__r2mem_rs2__
#define __r2ad2__r2mem_rs2__

#include "zrsapi.h"
#include "r2math.h"

// rs应该是resample的缩写
class r2mem_rs2
{
public:
  r2mem_rs2(int iMicNum, int iSampleRate, r2_mic_info* pMicInfo_Rs, bool bDelay);
public:
  ~r2mem_rs2(void);
  
public:
  int reset();

  // 输入：
  //		pData_Out，二维数组[mic count][sample count]
  //		iLen_Out = 采样点个数
  int process(float** pData_In, int iLen_In, float**& pData_Out, int& iLen_Out);
  
public:
  
  int m_iMicNum ;
  r2_mic_info* m_pMicInfo_Rs ;
  
  // 48k/s -> 16k/s
  r2_rs_htask m_hRs_48_16 ;
  
  float** m_pData_Tmp ;

  int m_iLen_Out_Total ;
  float ** m_pData_Out ;
  
  bool m_bDelay ;
  // 48k/s -> 96k/s ?
  r2_rs_htask m_hRs_48_96 ;
  
  
};


#endif /* __r2ad2__r2mem_rs2__ */
