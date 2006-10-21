/*! \file ucci.h
@brief UCCIͨѶģ�飨�������ṩ����ѭGPL��ɣ�

����������Ϣ���Ƴ� ������ѧ��ѧϵ���滯ѧʵ���� E-mail��webmaster at elephantbase dot net 
*/

#ifndef UCCI_H
#define UCCI_H

#include "../utility/bool.h"
const int UCCI_MAX_DEPTH = 32; // UCCI����˼���ļ������

// ��UCCIָ���йؼ����йص�ѡ��
enum UcciOptionEnum {
  UCCI_OPTION_NONE, UCCI_OPTION_BATCH, UCCI_OPTION_DEBUG, UCCI_OPTION_USEMILLISEC, UCCI_OPTION_BOOKFILES, UCCI_OPTION_HASHSIZE, UCCI_OPTION_THREADS, UCCI_OPTION_DRAWMOVES,
  UCCI_OPTION_REPETITION, UCCI_OPTION_PRUNING, UCCI_OPTION_KNOWLEDGE, UCCI_OPTION_SELECTIVITY, UCCI_OPTION_STYLE, UCCI_OPTION_LOADBOOK
}; // uo, ��"setoption"ָ����ѡ��
enum UcciRepetEnum {
  UCCI_REPET_ALWAYSDRAW, UCCI_REPET_CHECKBAN, UCCI_REPET_ASIANRULE, UCCI_REPET_CHINESERULE
}; // ur
enum UcciGradeEnum {
  UCCI_GRADE_NONE, UCCI_GRADE_SMALL, UCCI_GRADE_MEDIUM, UCCI_GRADE_LARGE
}; // ug
enum UcciStyleEnum {
  UCCI_STYLE_SOLID, UCCI_STYLE_NORMAL, UCCI_STYLE_RISKY
}; // us, ѡ��style���趨ֵ
enum UcciTimeEnum {
  UCCI_TIME_DEPTH, UCCI_TIME_MOVE, UCCI_TIME_INC
}; // ut, ��"go"ָ��ָ����ʱ��ģʽ���ֱ��ǹ̶����(�������൱�����Ϊ"c_MaxDepth")��ʱ����(�������ڱ�����ɼ���)�ͼ�ʱ��(ʣ��ʱ����٣������ⲽ��Ӽ���)
enum UcciCommEnum {
  UCCI_COMM_NONE, UCCI_COMM_UCCI, UCCI_COMM_ISREADY, UCCI_COMM_PONDERHIT, UCCI_COMM_STOP, UCCI_COMM_SETOPTION, UCCI_COMM_POSITION, UCCI_COMM_BANMOVES, UCCI_COMM_GO, UCCI_COMM_GOPONDER, UCCI_COMM_QUIT
}; // uce, UCCIָ������

///UCCIͨѶģ�飨�������ṩ����ѭGPL��ɣ� 
/*!
��������ֱ��ʹ��UCCI������Ա�ṩ��ͨ��ͨѶģ�飨��ѭGPL��ɣ���

��������ʵ�ֺ͹���˵���μ���http://www.elephantbase.net/protocol/cchess_ucci.htm��
*/
// UCCIָ����Խ��ͳ������������Ľṹ
union UcciCommStruct {

  /* �ɵõ�������Ϣ��UCCIָ��ֻ������4������
   *
   * 1. "setoption"ָ��ݵ���Ϣ���ʺ���"UCCI_COMM_SETOPTION"ָ������
   *    "setoption"ָ�������趨ѡ����������ܵ�����Ϣ�С�ѡ�����͡��͡�ѡ��ֵ��
   *    ���磬"setoption batch on"��ѡ�����;���"UCCI_OPTION_DEBUG"��ֵ(Value.bCheck)����"TRUE"
   */
  struct {
    UcciOptionEnum uoType;   // ѡ������
    union {                  // ѡ��ֵ
      int nSpin;             // "spin"���͵�ѡ���ֵ
      Bool bCheck;           // "check"���͵�ѡ���ֵ
      UcciRepetEnum urRepet; // "combo"���͵�ѡ��"repetition"��ֵ
      UcciGradeEnum ugGrade; // "combo"���͵�ѡ��"pruning"��"knowledge"��"selectivity"��ֵ
      UcciStyleEnum usStyle; // "combo"���͵�ѡ��"style"��ֵ
      const char *szString;  // "string"���͵�ѡ���ֵ
    } Value;                 // "button"���͵�ѡ��û��ֵ
  } Option;

  /* 2. "position"ָ��ݵ���Ϣ���ʺ���"e_CommPosition"ָ������
   *    "position"ָ���������þ��棬������ʼ������ͬ�����ŷ����ɵľ���
   *    ���磬position startpos moves h2e2 h9g8��FEN������"startpos"�����FEN�����ŷ���(MoveNum)����2
   */
  struct {
    const char *szFenStr; // FEN�����������(��"startpos"��)Ҳ�ɽ���������ת����FEN��
    int nMoveNum;         // �����ŷ���
    long *lpdwCoordList;  // �����ŷ���ָ�����"IdleLine()"�е�һ����̬���飬�����԰�"CoordList"����������
  } Position;

  /* 3. "banmoves"ָ��ݵ���Ϣ���ʺ���"e_CommBanMoves"ָ������
   *    "banmoves"ָ���������ý�ֹ�ŷ������ݽṹʱ������"position"ָ��ĺ����ŷ�����û��FEN��
   */
  struct {
    int nMoveNum;
    long *lpdwCoordList;
  } BanMoves;

  /* 4. "go"ָ��ݵ���Ϣ���ʺ���"e_CommGo"��"e_CommGoPonder"ָ������
   *    "go"ָ��������˼��(����)��ͬʱ�趨˼��ģʽ�����̶���ȡ�ʱ���ƻ��Ǽ�ʱ��
   */
  struct {
    UcciTimeEnum utMode; // ˼��ģʽ
    union {          
      int nDepth, nTime; 
    } DepthTime; // ����ǹ̶���ȣ����ʾ���(��)��������޶�ʱ�䣬���ʾʱ��(��)
    union {
      int nMovesToGo, nIncrement;
    } TimeMode;  // ����Ǽ�ʱ�ƣ����޶�ʱ����Ҫ�߶��ٲ��壬�����ʱ���ƣ����ʾ����ò����޶�ʱ��Ӷ�����
  } Search;
}; // ucs

// ��������������������UCCIָ��������ڲ�ͬ����
UcciCommEnum BootLine(void);                                    // UCCI���������ĵ�һ��ָ�ֻ����"ucci"
UcciCommEnum IdleLine(UcciCommStruct &ucsCommand, Bool bDebug); // �������ʱ����ָ��
UcciCommEnum BusyLine(Bool bDebug);                             // ����˼��ʱ����ָ�ֻ�������"stop"��"ponderhit"
void ExitLine(void);

#endif
