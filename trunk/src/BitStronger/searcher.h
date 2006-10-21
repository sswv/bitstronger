/*! \file searcher.h
@brief �����������ࣨ����ģ�飩
*/

#ifndef SERCHER_H
#define SERCHER_H

#include <stdio.h>
#include <time.h>
#include "../utility/bool.h"
#include "constant.h"
#include "board.h"
#include "movement.h"
#include "movemaker.h"
#include "evaluation.h"
#include "openbook.h"
//#include "hashnum.h"

///�������� 
static int searchDepth;

///�����ŷ����� 
static Movement allmoves[MAX_SEARCH_DEPTH + 1][SEARCH_WIDTH];
///��̬�����Ŀ����ŷ����� 
static Movement qsmoves[MAX_QUIES_DEPTH + 1][SEARCH_WIDTH];

///��ǰ����ŷ�
static Movement best; 
///�ϴ���������ŷ�
static Movement lastbest; 
///��ǰ�μ��ŷ�������ǰ��λ������ѭ�����棩
static Movement better;
///�ϴ������μ��ŷ�������ǰ��λ������ѭ�����棩
static Movement lastbetter;
///��ǰ�������ŷ�������ǰ��λ������ѭ�����棩
static Movement good;
///�ϴ������������ŷ�������ǰ��λ������ѭ�����棩
static Movement lastgood;

///������ʼʱ�� 
static time_t startTime;

///��ʷ�ŷ���¼
/*!��¼������ţ�Ҳ���ǿ��ܳ��ֵ�����ѭ���� 
   ��Ϊ�������ѭ������������Ҫ������и����к͡� 
   ��ʼֵ��Ϊ�����ܵ��ŷ�������Կ��ֵ��������⴦�� 
*/
static long history[2][4] = {{0, 1, 2, 3}, {0, 1, 2, 3}};

///��ϣ����ʷ�����¼
static HASHNUM hashlink[MAX_SEARCH_DEPTH];

///��̬�����Ĺ�ϣ����ʷ�����¼
static HASHNUM qshashlink[MAX_QUIES_DEPTH];

///�õ�һ�����վ����·�� 
static Movement trace[MAX_SEARCH_DEPTH];
///��̬�����õ�һ�����վ����·�� 
static Movement qstrace[MAX_QUIES_DEPTH];

///�����������ࣨ����ģ�飩
/*!
�����������ϵ�ÿһ���ڵ㶼����һ�����棬ÿһ��Ľڵ㶼�����丸�ڵ�����п����ŷ��γɵġ���������ż����ڵ�ֱ��ʾ˫���ľ��档����Ҫ���ڶ��Ҷ�ӽڵ�����ѡһ����ѵľ��棬�Ӷ����Ƶ���ǰ���ŷ���Ϊ�Լ���ѡ�� 

���������ٶȿ��������ִ����֦��Principal Variable Search�� 
*/  
class Searcher
{
public:
    ///�õ�һ������ŷ����������� 
    static void GetBestmove(Board & cur, PLAYER who);
    ///�ж�����Ƿ����ʤ�� 
    inline static Bool GameOver(Board & cur);
private:
    ///��PVS������������ŷ� 
    static int PVSearch(Board & cur, int depth, PLAYER who, int alpha, int beta);
    ///��̬���������������������ʹ�ã�������������Ҷ�ӽڵ㴦���ã�
    static int QuiesSearch(Board & cur, int depth, PLAYER who, int alpha, int beta);
};

#endif
