/*! \file ucci.cpp
@brief UCCIͨѶģ�飨�������ṩ����ѭGPL��ɣ�

����������Ϣ���Ƴ� ������ѧ��ѧϵ���滯ѧʵ���� E-mail��webmaster at elephantbase dot net 
*/

// ucci.h/ucci.cpp - Source Code for ElephantEye, Part I

#include <stdio.h>
#include <string.h>
#include "../utility/idle.h"
#include "../utility/pipe.h"
#include "ucci.h"  

static int ReadDigit(char *&lpLinePtr, int nMaxValue) {
  int nRetValue;
  nRetValue = 0;
  for (; ; ) {
    if (*lpLinePtr >= '0' && *lpLinePtr <= '9') {
      nRetValue *= 10;
      nRetValue += *lpLinePtr - '0';
      lpLinePtr ++;
      if (nRetValue > nMaxValue) {
        nRetValue = nMaxValue;
      }
    } else {
      break;
    }
  }
  return nRetValue;
}

/* UCCIָ�����ģ��������UCCIָ���������ɡ�
 *
 * ���е�һ��������"BootLine()"��򵥣�ֻ������������������ĵ�һ��ָ��
 * ����"ucci"ʱ�ͷ���"UCCI_COMM_UCCI"������һ�ɷ���"UCCI_COMM_NONE"
 * ǰ�������������ȴ��Ƿ������룬���û��������ִ�д���ָ��"Idle()"
 * ��������������("BusyLine()"��ֻ��������˼��ʱ)����û������ʱֱ�ӷ���"UCCI_COMM_NONE"
 */
static PipeStruct pipeStdHandle;

UcciCommEnum BootLine(void) {
  char szLineStr[LINE_INPUT_MAX_CHAR];
  pipeStdHandle.Open();
  while (!pipeStdHandle.LineInput(szLineStr)) {
    Idle();
  }
  if (strcmp(szLineStr, "ucci") == 0) {
    return UCCI_COMM_UCCI;
  } else {
    return UCCI_COMM_NONE;
  }
}

static long dwCoordList[256];

UcciCommEnum IdleLine(UcciCommStruct &ucsCommand, Bool bDebug) {
  char szLineStr[LINE_INPUT_MAX_CHAR];
  int i;
  char *lpLineChar;
  UcciCommEnum uceReturnValue;

  while (!pipeStdHandle.LineInput(szLineStr)) {
    Idle();
  }
  lpLineChar = szLineStr;
  if (bDebug) {
    printf("info string %s\n", lpLineChar);
    fflush(stdout);
  }
  // "IdleLine()"����ӵ�UCCIָ����������������UCCIָ����������ͣ�������

  // 1. "isready"ָ��
  if (strcmp(lpLineChar, "isready") == 0) {
    return UCCI_COMM_ISREADY;

  // 2. "setoption <option> [<arguments>]"ָ��
  } else if (strncmp(lpLineChar, "setoption ", 10) == 0) {
    lpLineChar += 10;

    // (i) "batch"ѡ��
    if (strncmp(lpLineChar, "batch ", 6) == 0) {
      lpLineChar += 6;
      ucsCommand.Option.uoType = UCCI_OPTION_BATCH;
      if (strncmp(lpLineChar, "on", 2) == 0) {
        ucsCommand.Option.Value.bCheck = TRUE;
      } else if (strncmp(lpLineChar, "true", 4) == 0) {
        ucsCommand.Option.Value.bCheck = TRUE;
      } else {
        ucsCommand.Option.Value.bCheck = FALSE;
      } // ����"batch"ѡ��Ĭ���ǹرյģ�����ֻ���趨"on"��"true"ʱ�Ŵ򿪣���ͬ

    // (ii) "debug"ѡ��
    } else if (strncmp(lpLineChar, "debug ", 6) == 0) {
      lpLineChar += 6;
      ucsCommand.Option.uoType = UCCI_OPTION_DEBUG;
      if (strncmp(lpLineChar, "on", 2) == 0) {
        ucsCommand.Option.Value.bCheck = TRUE;
      } else if (strncmp(lpLineChar, "true", 4) == 0) {
        ucsCommand.Option.Value.bCheck = TRUE;
      } else {
        ucsCommand.Option.Value.bCheck = FALSE;
      }

    // (iii) "usemillisec"ѡ��
    } else if (strncmp(lpLineChar, "usemillisec ", 12) == 0) {
      lpLineChar += 12;
      ucsCommand.Option.uoType = UCCI_OPTION_USEMILLISEC;
      if (strncmp(lpLineChar, "on", 2) == 0) {
        ucsCommand.Option.Value.bCheck = TRUE;
      } else if (strncmp(lpLineChar, "true", 4) == 0) {
        ucsCommand.Option.Value.bCheck = TRUE;
      } else {
        ucsCommand.Option.Value.bCheck = FALSE;
      }

    // (iv) "bookfiles"ѡ��
    } else if (strncmp(lpLineChar, "bookfiles ", 10) == 0) {
      ucsCommand.Option.uoType = UCCI_OPTION_BOOKFILES;
      ucsCommand.Option.Value.szString = lpLineChar + 10;

    // (v) "hashsize"ѡ��
    } else if (strncmp(lpLineChar, "hashsize ", 9) == 0) {
      lpLineChar += 9;
      ucsCommand.Option.uoType = UCCI_OPTION_HASHSIZE;
      ucsCommand.Option.Value.nSpin = ReadDigit(lpLineChar, 1024);

    // (vi) "threads"ѡ��
    } else if (strncmp(lpLineChar, "threads ", 8) == 0) {
      lpLineChar += 8;
      ucsCommand.Option.uoType = UCCI_OPTION_THREADS;
      ucsCommand.Option.Value.nSpin = ReadDigit(lpLineChar, 32);

    // (vii) "drawmoves"ѡ��
    } else if (strncmp(lpLineChar, "drawmoves ", 10) == 0) {
      lpLineChar += 10;
      ucsCommand.Option.uoType = UCCI_OPTION_DRAWMOVES;
      ucsCommand.Option.Value.nSpin = ReadDigit(lpLineChar, 200);

    // (viii) "repetition"ѡ��
    } else if (strncmp(lpLineChar, "repetition ", 11) == 0) {
      lpLineChar += 11;
      ucsCommand.Option.uoType = UCCI_OPTION_REPETITION;
      if (strncmp(lpLineChar, "alwaysdraw", 10) == 0) {
        ucsCommand.Option.Value.urRepet = UCCI_REPET_ALWAYSDRAW;
      } else if (strncmp(lpLineChar, "checkban", 8) == 0) {
        ucsCommand.Option.Value.urRepet = UCCI_REPET_CHECKBAN;
      } else if (strncmp(lpLineChar, "asianrule", 9) == 0) {
        ucsCommand.Option.Value.urRepet = UCCI_REPET_ASIANRULE;
      } else if (strncmp(lpLineChar, "chineserule", 11) == 0) {
        ucsCommand.Option.Value.urRepet = UCCI_REPET_CHINESERULE;
      } else {
        ucsCommand.Option.Value.urRepet = UCCI_REPET_CHINESERULE;
      }

    // (ix) "pruning"ѡ��
    } else if (strncmp(lpLineChar, "pruning ", 8) == 0) {
      lpLineChar += 8;
      ucsCommand.Option.uoType = UCCI_OPTION_PRUNING;
      if (strncmp(lpLineChar, "none", 4) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_NONE;
      } else if (strncmp(lpLineChar, "small", 5) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_SMALL;
      } else if (strncmp(lpLineChar, "medium", 6) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_MEDIUM;
      } else if (strncmp(lpLineChar, "large", 5) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_LARGE;
      } else {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_LARGE;
      }

    // (x) "knowledge"ѡ��
    } else if (strncmp(lpLineChar, "knowledge ", 10) == 0) {
      lpLineChar += 10;
      ucsCommand.Option.uoType = UCCI_OPTION_KNOWLEDGE;
      if (strncmp(lpLineChar, "none", 4) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_NONE;
      } else if (strncmp(lpLineChar, "small", 5) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_SMALL;
      } else if (strncmp(lpLineChar, "medium", 6) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_MEDIUM;
      } else if (strncmp(lpLineChar, "large", 5) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_LARGE;
      } else {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_LARGE;
      }

    // (xi) "selectivity"ѡ��
    } else if (strncmp(lpLineChar, "selectivity ", 12) == 0) {
      lpLineChar += 12;
      ucsCommand.Option.uoType = UCCI_OPTION_SELECTIVITY;
      if (strncmp(lpLineChar, "none", 4) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_NONE;
      } else if (strncmp(lpLineChar, "small", 5) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_SMALL;
      } else if (strncmp(lpLineChar, "medium", 6) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_MEDIUM;
      } else if (strncmp(lpLineChar, "large", 5) == 0) {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_LARGE;
      } else {
        ucsCommand.Option.Value.ugGrade = UCCI_GRADE_NONE;
      }

    // (xii) "style"ѡ��
    } else if (strncmp(lpLineChar, "style ", 6) == 0) {
      lpLineChar += 6;
      ucsCommand.Option.uoType = UCCI_OPTION_STYLE;
      if (strncmp(lpLineChar, "solid", 5) == 0) {
        ucsCommand.Option.Value.usStyle = UCCI_STYLE_SOLID;
      } else if (strncmp(lpLineChar, "normal", 6) == 0) {
        ucsCommand.Option.Value.usStyle = UCCI_STYLE_NORMAL;
      } else if (strncmp(lpLineChar, "risky", 5) == 0) {
        ucsCommand.Option.Value.usStyle = UCCI_STYLE_RISKY;
      } else {
        ucsCommand.Option.Value.usStyle = UCCI_STYLE_NORMAL;
      }

    // (xiii) "loadbook"ѡ��
    } else if (strncmp(lpLineChar, "loadbook", 8) == 0) {
      ucsCommand.Option.uoType = UCCI_OPTION_LOADBOOK;

    // (xiv) �޷�ʶ���ѡ�����������
    } else {
      ucsCommand.Option.uoType = UCCI_OPTION_NONE;
    }
    return UCCI_COMM_SETOPTION;

  // 3. "position {<special_position> | fen <fen_string>} [moves <move_list>]"ָ��
  } else if (strncmp(lpLineChar, "position ", 9) == 0) {            
    lpLineChar += 9;
    // �����ж��Ƿ����������(����涨��5��)������������ֱ��ת���ɶ�Ӧ��FEN��
    if (strncmp(lpLineChar, "startpos", 8) == 0) {
      ucsCommand.Position.szFenStr = "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1";
    } else if (strncmp(lpLineChar, "midgamepos", 10) == 0) {
      ucsCommand.Position.szFenStr = "2bakab1r/6r2/1cn4c1/p1p1p3p/9/2P3p2/PC2P1n1P/2N1B1NC1/R4R3/3AKAB2 w - - 0 1";
    } else if (strncmp(lpLineChar, "checkmatepos", 12) == 0) {
      ucsCommand.Position.szFenStr = "4kar2/4a2rn/4bc3/RN1c5/2bC5/9/4p4/9/4p4/3p1K3 w - - 0 1";
    } else if (strncmp(lpLineChar, "zugzwangpos", 11) == 0) {
      ucsCommand.Position.szFenStr = "3k5/4PP3/4r4/3P5/9/9/9/9/9/5K3 w - - 0 1";
    } else if (strncmp(lpLineChar, "endgamepos", 10) == 0) {
      ucsCommand.Position.szFenStr = "4k4/4a4/4P4/9/9/9/9/4B4/9/4K4 w - - 0 1";
    // Ȼ���ж��Ƿ�ָ����FEN��
    } else if (strncmp(lpLineChar, "fen ", 4) == 0) {
      ucsCommand.Position.szFenStr = lpLineChar + 4;
    // ������߶����ǣ�����������
    } else {
      return UCCI_COMM_NONE;
    }
    // Ȼ��Ѱ���Ƿ�ָ���˺����ŷ������Ƿ���"moves"�ؼ���
    lpLineChar = strstr(lpLineChar, " moves ");
    ucsCommand.Position.nMoveNum = 0;
    if (lpLineChar != NULL) {
      lpLineChar += 7;
      ucsCommand.Position.nMoveNum = ((strlen(lpLineChar) + 1) / 5); // ��ʾ��"moves"�����ÿ���ŷ�����4���ַ���1���ո�
      for (i = 0; i < ucsCommand.Position.nMoveNum; i ++) {
        dwCoordList[i] = *(long *) lpLineChar; // 4���ַ���ת��Ϊһ��"long"���洢�ʹ�����������
        lpLineChar += 5;
      }
      ucsCommand.Position.lpdwCoordList = dwCoordList;
    }
    return UCCI_COMM_POSITION;

  // 4. "banmoves <move_list>"ָ�����������"position ... moves ..."��һ����
  } else if (strncmp(lpLineChar, "banmoves ", 9) == 0) {
    lpLineChar += 9;
    ucsCommand.BanMoves.nMoveNum = ((strlen(lpLineChar) + 1) / 5);
    for (i = 0; i < ucsCommand.Position.nMoveNum; i ++) {
      dwCoordList[i] = *(long *) lpLineChar;
      lpLineChar += 5;
    }
    ucsCommand.BanMoves.lpdwCoordList = dwCoordList;
    return UCCI_COMM_BANMOVES;

  // 5. "go [ponder] {infinite | depth <depth> | time <time> [movestogo <moves_to_go> | increment <inc_time>]}"ָ��
  } else if (strncmp(lpLineChar, "go ", 3) == 0) {
    lpLineChar += 3;
    // �����жϵ�����"go"����"go ponder"����Ϊ���߽��ͳɲ�ͬ��ָ��
    if (strncmp(lpLineChar, "ponder ", 7) == 0) {
      lpLineChar += 7;
      uceReturnValue = UCCI_COMM_GOPONDER;
    } else {
      uceReturnValue = UCCI_COMM_GO;
    }
    // Ȼ���жϵ����ǹ̶���Ȼ����趨ʱ��
    if (strncmp(lpLineChar, "time ", 5) == 0) {
      lpLineChar += 5;
      ucsCommand.Search.DepthTime.nTime = ReadDigit(lpLineChar, 36000);
      // ������趨ʱ�ޣ���Ҫ�ж���ʱ���ƻ��Ǽ�ʱ��
      if (strncmp(lpLineChar, " movestogo ", 11) == 0) {
        lpLineChar += 11;
        ucsCommand.Search.utMode = UCCI_TIME_MOVE;
        ucsCommand.Search.TimeMode.nMovesToGo = ReadDigit(lpLineChar, 100);
        if (ucsCommand.Search.TimeMode.nMovesToGo < 1) {
          ucsCommand.Search.TimeMode.nMovesToGo = 1;
        }
      } else if (strncmp(lpLineChar, " increment ", 11) == 0) {
        lpLineChar += 11;
        ucsCommand.Search.utMode = UCCI_TIME_INC;
        ucsCommand.Search.TimeMode.nIncrement = ReadDigit(lpLineChar, 600);
      // ���û��˵����ʱ���ƻ��Ǽ�ʱ�ƣ����趨Ϊ������1��ʱ����
      } else {
        ucsCommand.Search.utMode = UCCI_TIME_MOVE;
        ucsCommand.Search.TimeMode.nMovesToGo = 1;
      }
    } else if (strncmp(lpLineChar, "depth ", 6) == 0) {
      lpLineChar += 6;
      ucsCommand.Search.utMode = UCCI_TIME_DEPTH;
      ucsCommand.Search.DepthTime.nDepth = ReadDigit(lpLineChar, UCCI_MAX_DEPTH - 1);
    // ���û��˵���ǹ̶���Ȼ����趨ʱ�ޣ��͹̶����Ϊ"UCCI_MAX_DEPTH"
    } else {
      ucsCommand.Search.utMode = UCCI_TIME_DEPTH;
      ucsCommand.Search.DepthTime.nDepth = UCCI_MAX_DEPTH - 1;
    }
    return uceReturnValue;

  // 5. "stop"ָ��
  } else if (strcmp(lpLineChar, "stop") == 0) {
    return UCCI_COMM_STOP;

  // 6. "quit"ָ��
  } else if (strcmp(lpLineChar, "quit") == 0) {
    return UCCI_COMM_QUIT;

  // 7. �޷�ʶ���ָ��
  } else {
    return UCCI_COMM_NONE;
  }
}

UcciCommEnum BusyLine(Bool bDebug) {
  char szLineStr[LINE_INPUT_MAX_CHAR];
  if (pipeStdHandle.LineInput(szLineStr)) {
    if (bDebug) {
      printf("info string %s\n", szLineStr);
      fflush(stdout);
    }
    // "BusyLine"ֻ�ܽ���"isready"��"ponderhit"��"stop"������ָ��
    if (strcmp(szLineStr, "isready") == 0) {
      return UCCI_COMM_ISREADY;
    } else if (strcmp(szLineStr, "ponderhit") == 0) {
      return UCCI_COMM_PONDERHIT;
    } else if (strcmp(szLineStr, "stop") == 0) {
      return UCCI_COMM_STOP;
    } else {
      return UCCI_COMM_NONE;
    }
  } else {
    return UCCI_COMM_NONE;
  }
}
