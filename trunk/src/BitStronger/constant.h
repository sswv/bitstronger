/*! \file constant.h
@brief ������������ 
*/

#ifndef CONSTANT_H
#define CONSTANT_H

#include "../utility/bool.h"

///�Ƿ�Ϊ���� 
#define IsRed(x) (!((x) & 0xf0) && (x))
///�Ƿ�Ϊ���� 
#define IsBlack(x) (!(~(x) & 0xf0))
///�Ƿ�Ϊ��������ӣ����ںڷ��жϿ����ŷ��� 
#define IsRedOrNone(x) (!((x) & 0xf0))
///�Ƿ�Ϊ��������ӣ����ں췽�жϿ����ŷ��� 
#define IsBlackOrNone(x) (!(~(x) & 0xf0) || !(x))
///�ж��Ǻ��廹�Ǻ���
/*!ע������ֻ��������ʱ�ܷ�����ȷ�����NONE��OUTʱ���ؽ�������塣 
*/ 
#define GetColor(x) (!(~(x) & 0xf0))

///���֣��췽���ڷ��� 
typedef unsigned char PLAYER;
///���� 
typedef unsigned char CHESSMAN;
///�������꣨16*16��ʾ���� 
typedef unsigned char BDPOINT;
///��ϣ����64λ�� 
typedef long long HASHNUM;

///���������ȣ����õ����������˳����ݲ�ʹ�ã�
const int SEARCH_DEPTH = 4; 
///������������ȣ����ڵ���������� 
const int MAX_SEARCH_DEPTH = 16;
///��̬����ʱ�����������������
const int MAX_QUIES_DEPTH = 16;
///ÿ�������ʱ�䣨����ƣ����ڵ���������� 
const int LONGEST_SEARCH_TIME = 5; 

///����ʱÿ����ౣ����ָ��� 
const int SEARCH_WIDTH = 80;
///��ʾ��ǰ�����������������ֵ����ֵӦС���ҷ�ʧȥ�������ӵķ���
const int NO_BEST_MOVE = -20000;
///��ʾÿ������ʱ�䳬ʱ������ֵ�����ڵ��������������ֵӦС���ҷ�ʧȥ�������ӵķ���
const int TIME_OVER = -65432;
///��ʾ��ǰ�������û����в����ڵ�����ֵ����ֵӦС���ҷ�ʧȥ�������ӵķ���
const int NOT_IN_TT = -60000;
///���������������ʧ��˧��һ�����ܵ��������ֵ
const int MAX_VALUE_OF_BOARD = 2000;

///���ֱ��� 
enum Player
{
    RED = 0, BLACK = 1    
};

///���ӱ��롣ע�⣺�� unsigned char ���͵� position ����洢���ӱ��룬
/*!��������Ϊ��8λ�����Ʋ��룬�磺-2 -> 254�� 
   NONE ��ʾ�����ӣ�OUT ��ʾ����֮���λ�á� 
*/
enum Chessman
{
    NONE = 0, OUT = 99,
    R_KING = 1, R_ADVISOR = 2, R_BISHOP = 3, R_KNIGHT = 4, R_ROOK = 5, R_CANNON = 6, R_PAWN = 7, 
    B_KING = 255, B_ADVISOR = 254, B_BISHOP = 253, B_KNIGHT = 252, B_ROOK = 251, B_CANNON = 250, B_PAWN = 249
};

///���Ʊ��루���֣��о֣��о֣� 
enum BoardState
{
    START_STATE = 0, MID_STATE = 1, END_STATE = 2    
};

#endif
