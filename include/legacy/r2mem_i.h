//
//  r2mem_i.h
//  r2ad
//
//  Created by hadoop on 10/23/15.
//  Copyright (c) 2015 hadoop. All rights reserved.
//

#ifndef __r2ad__r2mem_i__
#define __r2ad__r2mem_i__

#include "r2math.h"

enum r2_in_type{
  r2_in_int_24 = 1 ,
  r2_in_int_32 ,
  r2_in_int_32_10 ,
  r2_in_float_32
};

struct r2_int24 {
  unsigned char m_Internal[3] ;
  
  int toint(){
    if ((m_Internal[2] & 0x80) != 0){
      return  ((m_Internal[0] & 0xff) | (m_Internal[1] & 0xff) << 8 | (m_Internal[2] & 0xff) << 16 | (-1 & 0xff) << 24);
    }else{
      return  ((m_Internal[0] & 0xff) | (m_Internal[1] & 0xff) << 8 | (m_Internal[2] & 0xff) << 16 | (0 & 0xff) << 24);
    }
  }
};

class r2mem_i{
public:
  r2mem_i(int iMicNum, r2_in_type iInType, r2_mic_info* pMicInfo_In);
public:
  ~r2mem_i(void);
  
public:
  int reset();

  // 把输入音频转成浮点类型
  // 每个采样点，多个麦克风的数据按顺序排列。所有采样点，按顺序排列。
  // 对于不同类型的输入，归一化到浮点数时，乘以的系数不同。
  //		r2_in_int_24: 1/4
  //		r2_in_int_32: 1/1024
  //
  // 输出：
  //		pData_Out，二维数组[mic count][sample count]
  //		iLen_Out = sample count
  int process(char* pData_In, int iLen_In, float**& pData_Out, int& iLen_Out);
  
public:
  
  int m_iMicNum ;
  r2_in_type m_iInType ;
  r2_mic_info* m_pMicInfo_In ;
  
  int m_iLen_Out;
  int m_iLen_Out_Total;
  float** m_pData_Out;
  
  
};

#endif /* defined(__r2ad__r2mem_i__) */
