/*! \file hashnum.h
@brief ��ϣ�������ࣨ����ģ�飩
*/

#ifndef HASHNUM_H
#define HASHNUM_H

#include <stdio.h>
#include <stdlib.h>
#include "../utility/bool.h"
#include "constant.h"

///���湤��·�� 
extern char workpath[256];
///���� Zobrist �����ļ�����·�� 
extern char hashpath[256];

///�Ƿ��Ѿ����أ����ظ����� 
static Bool loadedhash = FALSE;

///���� Zobrist �����ļ� 
static FILE * doc;

///Zobrist ����
static HASHNUM hash[14][256];

///�û�����Ŀ���� 
enum EntryType
{
    EXACT, L_BOUND, U_BOUND 
};

///�û�����Ŀ��
/*!���Ѿ��������ľ�������û����Ա��ں�����������������ͬ�ľ���ֱ�ӵ���������ֵ 
*/ 
class TTItem
{
public:
    ///�þ���Ĺ�ϣ��
    /*!�����ù�ϣ���ĺ�20λ��Ϊ�洢�±꣬��Ϊ��ֹ��ͻ�������Ӧ��¼��ϣ��������֮�� 
    */ 
    HASHNUM zobrist;
    ///�þ������ڵĲ���������������� 
    int max_depth; 
    ///�þ������ڵĲ�������� 
    int depth; 
    ///�û�����Ŀ����
    EntryType entry;
    ///��������ֵ 
    int value; 
};

///�û���
/*!�ֱ��¼���˫�����±�Ϊ���� Zobrist ����ĩ20λ�� 
*/ 
static TTItem * TTList[2];

///��ϣ�������ࣨ����ģ�飩 
/*!
�������ǲ��ò����㷨�о����Zobrist��ֵ��ʾ������ÿ������λ��ÿ��λ�õ��������32�����ӡ�90��λ�ã����ų������ܵ�λ�ã���һ��64λ������8���ֽڣ���ʾ��һ���������������ӵ�Zobrist��ֵ֮���Ͷ���Ϊ���־���Ĺ�ϣ��ʾ�����۱������ֹ�ϣ��ʾ����ͻ���ʼ��ͣ����ÿ��ǳ�ͻ����

����Zobrist��ֵ����ͨ����дС����������ɣ����䱣����һ���ļ���Zobrist.bin���У�ÿ8���ֽ�Ϊһ��Zobrist��ֵ����ֵ�ļ����������ʱ�����ڴ棬�Ժ�ʹ��ʱֱ�ӵ��á�
*/
class Hashnum
{
public:
    ///��ʼ�� Zobrist ������û��� 
    static void InitHash();
    ///����û���
    static void ClearHash(); 
    ///�õ�ĳ��������ĳ��λ�ö�Ӧ�� Zobrist �� 
    static HASHNUM GetHash(CHESSMAN chess, BDPOINT point);
    ///���û����в����Ѵ���Ŀ
    static int SearchTT(HASHNUM zobrist, int max_depth, int depth, PLAYER who, int alpha, int beta);
    ///����Ŀ���浽�û���
    static void SaveTT(HASHNUM zobrist, int max_depth, int depth, PLAYER who, EntryType entry, int value);
};

#endif
