/*! \file idle.h
@brief CPU��ת�������壨�������ṩ����ѭGPL��ɣ�

����������Ϣ���Ƴ� ������ѧ��ѧϵ���滯ѧʵ���� E-mail��webmaster at elephantbase dot net 
*/

#ifndef IDLE_H
#define IDLE_H

#ifdef _WIN32
  #include <windows.h>
  inline void Idle(void) {
    Sleep(1);
  }
#else
  #include <unistd.h>
  inline void Idle(void) {
    usleep(1000);
  }
#endif

#endif
