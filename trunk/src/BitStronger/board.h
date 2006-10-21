/*! \file board.h
@brief ���̱�ʾ��
*/

#ifndef BOARD_H
#define BOARD_H

#include <string.h>
#include "../utility/bool.h"
#include "constant.h"
#include "movement.h"
#include "hashnum.h"

///���̱�ʾ��
/*!
��������㷨��Ч����ʵ�ֵķ��㣬���ǲ��õ���Ŀǰ���е���һ��"16��16���̱�ʾ��"����ʵ��ʱΪ���㷽�㣬�ó���Ϊ256��һά�����ʾ�������ַ����Ĵ洢ԭ����9��10�Ķ�ά����һ�£�������16��16������м�һ���ʾ���̡��������ĺô���һ�����С������������ֱ�Ϊ0x10��0x01�������ø���λ�����ʾ���̵ı仯������9��10�Ķ�ά���������˳�9��10�������öࣻ��һ������ΧһȦ"�ڱ�"���Ա���ʹ�ô����߽�������⣬�Զ���ֹ�����߳����̱߽硣

�������̱�ʾ����ֻ��"�������"��"��һ�����ֵ�˭�����ˣ�"�Ǳ�Ҫ��Ϣ��������ݳ�Աȫ����Ϊ�˷�������ģ��Ŀ��ټ�������á������¼����˧��λ�ÿ������ŷ�����ģ���п��ٵ�֪ĳһ�ŷ��Ƿ���ɽ�˧���棻��¼��ǰ�����Zobrist���������̵Ĺ�ϣ��ʾ�������ڿ��ֿ��п��ټ�����һ���档
*/
class Board
{
public:
    /*----------��Ա����----------*/
    ///��һ�����ֵ�˭�����ˣ� 
    PLAYER player;
    ///����һ���������ӿ��е��߷���Ŀ
    /*!��һ��Ԫ�������壬����İ����Ӵ���˳�����У��ڷ�Ҳ�Ǿ���ֵ1~7 
       ����ִ�� MoveMaker::Make �������� 
    */
    int numOfMove[8];
    ///�������
    /*!ʹ��16*16��ʾ�������ڿ��������ŷ���ͬʱ��ֹ�����߳����̱߽硣 
       �ο���http://www.elephantbase.net/computer/eleeye_struct.htm
    */
    CHESSMAN position[256];
    ///��ǰ����� Zobrist �� 
    HASHNUM zobrist;
    ///��ǰ�������Ӹ����������ж��ǿ��֣��о֣��о�
    int numOfChess;
    ///��¼����˧��λ�� 
    BDPOINT kingpos[2];
    ///��¼�õ��˾������һ���ŷ� 
    /*!ֻ��ִ�� Board::AddMovement ֮�������壬�Ҳ����� Board::DelMovement ���ݡ�
    */
    Movement lastmove;
    ///˫��û�г��ӵ����岽������غ����� 
    int non_eat_steps;
    ///��ǰ�Ļغ���
    int bouts;
    /*----------��Ա����----------*/
    ///Ĭ�Ϲ��캯�������ݲ�ʹ�� 
    Board();
    ///��FEN���������̵Ĺ��캯��
    Board(const char * fen, int nMoveNum, long * lpdwCoordList);
    ///��FEN����������
    /*!FEN������μ���http://www.elephantbase.net/protocol/cchess_fen.htm
    */ 
    void FromFen(const char * fen, int nMoveNum, long * lpdwCoordList);
    ///���һ���ŷ���ı����
    void AddMovement(const Movement & move); 
    ///ɾ��һ���ŷ���ı����
    void DelMovement(const Movement & move); 
    ///��֤һ��4�ֽ��ŷ��ִ����硰h0i2�������ڱ������Ƿ����
    /*!ֻ��֤��ֹ�����ӺϷ��ԣ�����֤���Ϸ��ԡ�
       �����ʽ�μ���http://www.elephantbase.net/protocol/cchess_move.htm�� 
    */
    Bool CanGo(const char * str); 
private:
    /*----------˽�к���----------*/
    ///������� 
    void ClearBoard();
};

#endif
