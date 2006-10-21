/*! \file movement.h
@brief �ŷ���ʾ��
*/

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../utility/bool.h"
#include "constant.h"

///�ŷ���ʾ��
/*!
������¼��һ���ŷ�����㡢�յ㡢����ʲô�ӡ��Ƿ񹹳ɽ����������б�Ҫ��¼���Ե��ӣ���Ϊ�ڲ������������漰�ŷ����ݣ�����ʹһ�������ܹ������ػ�ԭ����һ���档
*/ 
class Movement
{
public:
    /*----------��Ա����----------*/
    ///��ʼλ�ã���16*16��ʾ���� 
    BDPOINT from;
    ///����λ�ã���16*16��ʾ���� 
    BDPOINT to;
    ///���Ե��ӣ��� enum Chessman ��ʾ�� 
    CHESSMAN ate;
    ///�Ƿ񹹳ɽ��� 
    Bool check;
    /*----------��Ա����----------*/
    ///Ĭ�Ϲ��캯�������ݲ�ʹ�� 
    Movement();
    ///ʹ����֪��Ϣ�Ĺ��캯��
    Movement(BDPOINT f, BDPOINT t, CHESSMAN a, Bool c); 
    ///���ŷ�ת���ɽ�����յ��ַ���
    char * Move2Str(char * str);
    ///���ظ�ֵ�����
    Movement & operator = (const Movement & obj); 
};

#endif
