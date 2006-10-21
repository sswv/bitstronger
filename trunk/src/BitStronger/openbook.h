/*! \file openbook.h
@brief ���ֿ�����ࣨ����ģ�飩
*/

#ifndef OPENBOOK_H
#define OPENBOOK_H

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <vector>
#include "../utility/bool.h"
#include "constant.h"
#include "board.h"

///C++ std�����ռ�
/*!�������������� vector �ࡣ 
*/ 
using namespace std;

///���ֿ���Ŀ�ṹ 
typedef struct BookItem BookItem;

///���湤��·�� 
extern char workpath[256];
///���濪�ֿ���ļ�����·�� 
extern char bookpath[256];

///�Ƿ��Ѿ����أ����ظ����� 
static Bool loadedopen = FALSE;
///���濪�ֿ���ļ�
static FILE * bookfile;

///�ڴ��м�¼���ֿ������ 
static vector<BookItem> * books;

///���ֿ���Ŀ�ṹ 
/*!
�������ֿ���Ŀ��¼һ�������Ӧ�Ķ���ŷ�����long�ʹ洢��㵽�յ��4���ֽڣ��硰h0i2������
*/
struct BookItem
{
    ///����� Zobrist �� 
    HASHNUM zobrist;
    ///��һ�����ֵ�˭�����ˣ� 
    PLAYER player;
    ///�þ����Ӧ�Ķ���ŷ�
    vector<long> * tricks;
};

///���ֿ�����ࣨ����ģ�飩
/*!
���������ڿ��ֻ�һЩ���͵��о�ʱ���Ȳ����в����������������ڿ��ֿ��м������͵�Ӧ���ŷ�������ʹ�����˲��������������ڿ���ʱ��Ϊ�ֲ���С�����������ȫ�ֵķ�չ���߳���Ц�󷽵ľ��������������ҷ����ٳ���������ռ������λ�á�

�������ǵĿ��ֿ����Դ�ǡ�����ٿ�ȫ�顷��վ����¼��8000���ȫ������������ף�ʹ�ø���վ�ṩ��С���������еĿ�����ȡ�������ֵ�Ƶ�ʺ����յ�ʤ������Ȼ��ʹ���Լ���д��С���������ܽ�������ı���ʽ�Ŀ�����ϢתΪ���ǳ���ר�õĶ����Ƹ�ʽ���ֿ��ļ���OpenBook.bin�������ֿ��ļ���ÿ13���ֽ�Ϊһ�Σ��ֱ���8���ֽڱ�ʾ���棨��ϣ��ʾ������1���ֽڱ�ʾ�ֵ�˭���壨0x00Ϊ�죬0x01Ϊ�ڣ���4���ֽڱ�ʾӦ�Ե��ŷ����ô�����ֹλ�õ����������ַ�����ʾ����"h0i2"����
*/
class OpenBook
{
public:
    ///��ʼ�����ֿ� 
    static void InitBook();
    ///������ֿ� 
    static void ClearBook();
    ///�ڿ��ֿ�������ĳһ���棬���ض�Ӧ�ŷ���Ŀ�����ѡ��һ���ŷ�д��str 
    static int Search(const Board & cur, char * str);
};

#endif
