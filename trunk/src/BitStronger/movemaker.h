/*! \file movemaker.h
@brief �ŷ������ࣨ����ģ�飩
*/

#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include "../utility/bool.h"
#include "constant.h"
#include "board.h"
#include "movement.h"

///�������п���λ��
const BDPOINT R_ADVISOR_POSITION[5] = {0xa6, 0xa8, 0xb7, 0xc6, 0xc8};
///��ʿ���п���λ��
const BDPOINT B_ADVISOR_POSITION[5] = {0x36, 0x38, 0x47, 0x56, 0x58};
///�������п���λ��
const BDPOINT R_BISHOP_POSITION[7] = {0x85, 0x89, 0xa3, 0xa7, 0xab, 0xc5, 0xc9};
///�������п���λ��
const BDPOINT B_BISHOP_POSITION[7] = {0x35, 0x39, 0x53, 0x57, 0x5b, 0x75, 0x79};
///˧���������п��߲�·��������꣩ 
const BDPOINT cnKINGMOVETAB[4] = {0x01, 0xff, 0x10, 0xf0};
///�����п��߲�·��������꣩
const BDPOINT cnKnightMoveTab[8] = {0xdf, 0xe1, 0xee, 0xf2, 0x0e, 0x12, 0x1f, 0x21}; 
///��ԭ��Ϊ��������������� 
const BDPOINT cnHorseLegTab[8] = {0xf0, 0xf0, 0xff, 0x01, 0xff, 0x01, 0x10, 0x10};
///��ԭ��Ϊ��������������� 
const BDPOINT cnHorseLegBackTab[8] = {0xef, 0xf1, 0xef, 0xf1, 0x0f, 0x11, 0x0f, 0x11};
///���Ӻ�����п��߲�·��������꣩ 
const BDPOINT R_PawnMoveTab[3] = {0xf0,0x01,0xff};
///���Ӻ������п��߲�·��������꣩ 
const BDPOINT B_PawnMoveTab[3] = {0x10,0x01,0xff};

///�ŷ������ࣨ����ģ�飩
/*!
����������Ҫͨ��һ�����棬�õ�ָ��һ�����п��е��ŷ����Ա�����������γɵľ��棬�õ�һ������ŷ����ŷ������ɹ����Ǳ����������̣������������г�����������ŷ����б�Ҫ�ų�"�����ͽ�"��"��Ӧ��"��Υ���ŷ���������һ���ŷ���ʾ������顣

������Ѱ�ҷ��������ŷ����棬���ǳ������16��16���̱�ʾ���ڼ��㷽������ƣ��Բ�ͬ�����ӣ��ֱ����Ԥ�ñ�ģ��ƥ�䡢��żУ��ȶ���λ����ķ�����������㷨Ч�ʡ�

�����������ӵĿ���λ�òο�16*16��ʾ��ģ�壺http://www.elephantbase.net/computer/eleeye_struct.htm
*/ 
class MoveMaker
{
public:
    ///�ӵ�ǰ����õ����п����ŷ������ؿ��е��ŷ����� 
    static int Make(Board & cur, PLAYER who, Movement move[]);
private:
    ///�� MoveMaker::Make �ó����е��ŷ��ٴ��жϺ����ԣ��ų������ͽ��Ͳ���Ӧ�����ŷ�
    /*!ͬʱ�ж����޽���������������� check Ϊ TRUE��<-��δ������жϣ� 
    */
    static Bool PreAdd(Board & cur, PLAYER who, BDPOINT from, BDPOINT to, Bool & check);
};

#endif
