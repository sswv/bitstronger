/*! \file pipe.h
@brief �ܵ�ͨ��ģ�飨�������ṩ����ѭGPL��ɣ�

����������Ϣ���Ƴ� ������ѧ��ѧϵ���滯ѧʵ���� E-mail��webmaster at elephantbase dot net 
*/

#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif
#include "bool.h"

#ifndef PIPE_H
#define PIPE_H

const int LINE_INPUT_MAX_CHAR = 1024;

///�ܵ�ͨ��ģ�飨�������ṩ����ѭGPL��ɣ� 
/*!
��������ֱ��ʹ��UCCI������Ա�ṩ�Ĺܵ�ͨѶģ�飨��ѭGPL��ɣ���

��������ʵ�ֺ͹���˵���μ���http://www.elephantbase.net/protocol/cchess_ucci.htm��
*/
struct PipeStruct {
#ifdef _WIN32
  HANDLE hInput, hOutput;
  BOOL bConsole;
  int nBytesLeft;
#else
  int nInput, nOutput;
#endif
  int nReadEnd;
  char szBuffer[LINE_INPUT_MAX_CHAR];

  void Open(const char *szExecFile = NULL);
  void Close(void) const;
  void ReadInput(void);
  Bool CheckInput(void);
  Bool GetBuffer(char *szLineStr);
  Bool LineInput(char *szLineStr);
  void LineOutput(const char *szLineStr) const;
}; // pipe

#endif
