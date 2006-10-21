/*! \file movemaker.cpp
@brief �ŷ������ࣨ����ģ�飩
*/

#include "movemaker.h"

int MoveMaker::Make(Board & cur, PLAYER who, Movement move[])
{
    int i;
    Bool next;
    BDPOINT index, tar, leg;
    int kind = 0;
    Bool chk;
    
    for (i = 0; i < 8; i++)
    {
        cur.numOfMove[i] = 0;
    }
    
    //�������� 
    for (index = 0x33; index <= 0xcb; index++)
    {
        if (cur.position[index] == NONE || cur.position[index] == OUT)
        {
            continue;    
        }
        //��ͬ���ӣ��ò�ͬ�ķ��������ܿ��ٵ��ҵ����е��ŷ� 
        switch (cur.position[index])
        {
            //����ڷ��㷨һ�£� 
            //���λ��ģ�巨 
            case R_KNIGHT:
            case B_KNIGHT:
                if (who == GetColor(cur.position[index]))
                {
					for(i = 0; i < 8; i++)
					{
						tar = index + cnKnightMoveTab[i];
						leg = index + cnHorseLegTab[i];
						if (((who == BLACK) ? IsRedOrNone(cur.position[tar]) : IsBlackOrNone(cur.position[tar])) && cur.position[leg] == NONE)
						{
							if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[4])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                        }
					}
                }
                break; 
            //������ڷ��㷨һ�£� 
            //�ĸ�����ֱ�ѭ���ҿ����ŷ� 
            case R_ROOK:
            case B_ROOK:
                if (who == GetColor(cur.position[index]))
                {
                    for (tar = index - 0x10; tar > 0x30; tar -= 0x10)
                    {
						if(cur.position[tar] != NONE)
						{
                            if (GetColor(cur.position[tar]) != who)
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
							break;							
						} 
						else
						{
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
						}
                    }
                    for (tar = index + 0x10; tar < 0xd0; tar += 0x10)
                    {
						if(cur.position[tar] != NONE)
						{
                            if (GetColor(cur.position[tar]) != who)
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
							break;							
						} 
						else
						{
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
						}
                    }
                    for (tar = index - 0x01; (tar & 0x0f) > 0x02; tar -= 0x01)
                    {
						if(cur.position[tar] != NONE)
						{
                            if (GetColor(cur.position[tar]) != who)
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
							break;							
						} 
						else
						{
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
						}
                    }
                    for (tar = index + 0x01; (tar & 0x0f) < 0x0c; tar += 0x01)
                    {
						if(cur.position[tar] != NONE)
						{
                            if (GetColor(cur.position[tar]) != who)
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
							break;							
						} 
						else
						{
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[5])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
						}
                    }
                }
                break; 
            //�ڣ���ڷ��㷨һ�£� 
            //�ĸ�����ֱ�ѭ���ҿ����ŷ����Գ��Ӻͷǳ����ŷ��ֱ��ж� 
            case R_CANNON:
            case B_CANNON:
                if (who == GetColor(cur.position[index]))
                {
                    for (next = FALSE, tar = index - 0x10; tar > 0x30; tar -= 0x10)
                    {
                        if ((next == FALSE) && (cur.position[tar] == NONE))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            continue;
                        }
                        if ((next == FALSE) && (cur.position[tar] != NONE))
                        {
                            next = TRUE;
                            continue;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsRed(cur.position[tar]) : IsBlack(cur.position[tar])))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            break;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsBlack(cur.position[tar]) : IsRed(cur.position[tar])))
                        {
                            break;
                        }
                    }
                    for (next = FALSE, tar = index + 0x10; tar < 0xd0; tar += 0x10)
                    {
                        if ((next == FALSE) && (cur.position[tar] == NONE))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            continue;
                        }
                        if ((next == FALSE) && (cur.position[tar] != NONE))
                        {
                            next = TRUE;
                            continue;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsRed(cur.position[tar]) : IsBlack(cur.position[tar])))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            break;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsBlack(cur.position[tar]) : IsRed(cur.position[tar])))
                        {
                            break;
                        }
                    }
                    for (next = FALSE, tar = index - 0x01; (tar & 0x0f) > 0x02; tar -= 0x01)
                    {
                        if ((next == FALSE) && (cur.position[tar] == NONE))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            continue;
                        }
                        if ((next == FALSE) && (cur.position[tar] != NONE))
                        {
                            next = TRUE;
                            continue;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsRed(cur.position[tar]) : IsBlack(cur.position[tar])))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            break;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsBlack(cur.position[tar]) : IsRed(cur.position[tar])))
                        {
                            break;
                        }
                    }
                    for (next = FALSE, tar = index + 0x01; (tar & 0x0f) < 0x0c; tar += 0x01)
                    {
                        if ((next == FALSE) && (cur.position[tar] == NONE))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            continue;
                        }
                        if ((next == FALSE) && (cur.position[tar] != NONE))
                        {
                            next = TRUE;
                            continue;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsRed(cur.position[tar]) : IsBlack(cur.position[tar])))
                        {
                            if (PreAdd(cur, who, index, tar, chk))
                            {
                                Movement mv(index, tar, cur.position[tar], chk);
                                move[kind++] = mv;
								(cur.numOfMove[6])++;
                                if (kind >= SEARCH_WIDTH)
                                {
                                    return kind;
                                }
                            }
                            break;
                        }
                        if ((next == TRUE) && ((who == BLACK) ? IsBlack(cur.position[tar]) : IsRed(cur.position[tar])))
                        {
                            break;
                        }
                    }
                }
                break;
            default:
                //�������Ӻ�ڷ��㷨��ͬ���Գƣ����ֱ��� 
                //�췽 
                if (who == RED)
                {
                    switch (cur.position[index])
                    {
                        //˧
                        //���λ��ģ�巨 
                        case R_KING:
                            for(i = 0; i < 4; i++)
							{
								tar = index + cnKINGMOVETAB[i];
								if (IsBlackOrNone(cur.position[tar]))
								{
									//�ж�˧����Ƿ���Ź�
									if (!((tar & 0x0f) < 0x06 || (tar & 0x0f) > 0x08 || ((tar & 0xf0) >> 4) < 0x0a || ((tar & 0xf0) >> 4) > 0x0c))
									if(PreAdd(cur, who, index, tar, chk))
									{
										Movement mv(index, tar, cur.position[tar], chk);
                                        move[kind++] = mv;
										(cur.numOfMove[1])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
                                    }
                                }
                            }
                            break;  
                        //��
                        //����λ�����ޣ�ֱ��ö�� 
                        //ͨ��((pnt - index) & 0x01)��żУ�飬�ж�Ŀ��λ�ÿ����� 
                        case R_ADVISOR:
                            for (i = 0; i < 5; i++)
                            {
                                tar = R_ADVISOR_POSITION[i];
                                if (IsBlackOrNone(cur.position[tar]) && ((tar - index) & 0x01))
                                {
                                    if (PreAdd(cur, who, index, tar, chk))
                                    {
                                        Movement mv(index, tar, cur.position[tar], chk);
                                        move[kind++] = mv;
										(cur.numOfMove[2])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
                                    }
                                }
                            }
                            break;
                        //��
                        //����λ�����ޣ�ֱ��ö�� 
                        case R_BISHOP:
                            for (i = 0; i < 7; i++)
							{
								tar = R_BISHOP_POSITION[i];
                                if (IsBlackOrNone(cur.position[tar]))
                                {
									//�ж�Ŀ��λ�õĿ�����
									if ((((tar & 0x0f) - (index & 0x0f)) == 0x02) || (((index & 0x0f) - (tar & 0x0f)) == 0x02))
                                    if (cur.position[(tar + index) >> 1] == NONE) //�ж������Ƿ���
									if (PreAdd(cur, who, index, tar, chk))
                                    {
                                        Movement mv(index, tar, cur.position[tar], chk);
                                        move[kind++] = mv;
										(cur.numOfMove[3])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
                                    }
                                }
                            }
                            break; 
                        //��
                        //���λ��ģ�巨 
                        case R_PAWN:
							if (index & 0x80)
							{
								tar = index - 0x10;
								if (IsBlackOrNone(cur.position[tar]))
								{
									if (PreAdd(cur, who, index, tar, chk))
									{
										Movement mv(index, tar, cur.position[tar], chk);
										move[kind++] = mv;
										(cur.numOfMove[7])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
									}
								}
							}
							else
							{
								for(i = 0; i < 3; i++)
								{
									tar = index + R_PawnMoveTab[i];
									if(IsBlackOrNone(cur.position[tar]))
									{
										if (PreAdd(cur, who, index, tar, chk))
										{
											Movement mv(index, tar, cur.position[tar], chk);
											move[kind++] = mv;
										    (cur.numOfMove[7])++;
                                            if (kind >= SEARCH_WIDTH)
                                            {
                                                return kind;
                                            }
										}
									}
								}
							}
                            break; 
                    }
                }
                //�ڷ� 
                else
                {
                    switch (cur.position[index])
                    {
                        //��
                        //���λ��ģ�巨 
                        case B_KING:
                            for(i = 0; i < 4; i++)
							{
								tar = index + cnKINGMOVETAB[i];
								if (IsRedOrNone(cur.position[tar]))
								{
									//�жϽ�����Ƿ���Ź�
									if (!((tar & 0x0f) < 0x06 || (tar & 0x0f) > 0x08 || ((tar & 0xf0) >> 4) < 0x03 || ((tar & 0xf0) >> 4) > 0x05))
									if (PreAdd(cur, who, index, tar, chk))
									{
										Movement mv(index, tar, cur.position[tar], chk);
                                        move[kind++] = mv;
										(cur.numOfMove[1])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
                                    }
                                }
                            }
                            break;  
                        //ʿ
                        //����λ�����ޣ�ֱ��ö�� 
                        //ͨ��((pnt - index) & 0x01)��żУ�飬�ж�Ŀ��λ�ÿ����� 
                        case B_ADVISOR:
                            for (i = 0; i < 5; i++)
                            {
                                tar = B_ADVISOR_POSITION[i];
                                if (IsRedOrNone(cur.position[tar]) && ((tar - index) & 0x01))
                                {
                                    if (PreAdd(cur, who, index, tar, chk))
                                    {
                                        Movement mv(index, tar, cur.position[tar], chk);
                                        move[kind++] = mv;
										(cur.numOfMove[2])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
                                    }
                                }
                            }
                            break;
                        //��
                        //����λ�����ޣ�ֱ��ö�� 
                        case B_BISHOP:
                            for (i = 0; i < 7; i++)
							{
								tar = B_BISHOP_POSITION[i];
                                if (IsRedOrNone(cur.position[tar]))
                                {
									//�ж�Ŀ��λ�õĿ�����
									if ((((tar & 0x0f) - (index & 0x0f)) == 0x02) || (((index & 0x0f) - (tar & 0x0f)) == 0x02))
                                    if (cur.position[(tar + index) >> 1] == NONE) //�ж������Ƿ���
									if (PreAdd(cur, who, index, tar, chk))
                                    {
                                        Movement mv(index, tar, cur.position[tar], chk);
                                        move[kind++] = mv;
										(cur.numOfMove[3])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
                                    }
                                }
                            }
                            break; 
                        //��
                        //���λ��ģ�巨 
                        case B_PAWN:
							if (!(index & 0x80))
							{
								tar = index + 0x10;
								if (IsRedOrNone(cur.position[tar]))
								{
									if (PreAdd(cur, who, index, tar, chk))
									{
										Movement mv(index, tar, cur.position[tar], chk);
										move[kind++] = mv;
										(cur.numOfMove[7])++;
                                        if (kind >= SEARCH_WIDTH)
                                        {
                                            return kind;
                                        }
									}
								}
							}
							else
							{
								for(i = 0; i < 3; i++)
								{
									tar = index + B_PawnMoveTab[i];
									if(IsRedOrNone(cur.position[tar]))
									{
										if (PreAdd(cur, who, index, tar, chk))
										{
											Movement mv(index, tar, cur.position[tar], chk);
											move[kind++] = mv;
											(cur.numOfMove[7])++;
                                            if (kind >= SEARCH_WIDTH)
                                            {
                                                return kind;
                                            }
										}
									}
								}
							}
                            break; 
                    }
                }
                break;
        }
    }
    return kind;
}

Bool MoveMaker::PreAdd(Board & cur, PLAYER who, BDPOINT from, BDPOINT to, Bool & check)
{
    check = FALSE;
    
    int i, flag;
    Bool face = TRUE, suicide = FALSE;
    BDPOINT tar, leg;
    Movement mv(from, to, cur.position[to], check);
    
    cur.AddMovement(mv);
    //����û�н�˧ֱ���������򷵻� FALSE��
    if ((cur.kingpos[BLACK] & 0x0f) == (cur.kingpos[RED] & 0x0f))
    {
        for (i = cur.kingpos[BLACK] + 0x10; i < cur.kingpos[RED]; i += 0x10)
        {
            if (cur.position[i] != NONE)
            {
                face = FALSE;   
                break;
            }
        }
    }
    else
    {
        face = FALSE; 
    }
    
    //��û�������ͽ������򷵻� FALSE��
    //�����ڡ������䣩�Ľ�����ʽ 
    for (flag = 0, tar = cur.kingpos[who] - 0x10; tar > 0x20; tar -= 0x10) //˧ǰ�������� 
    {
        if (cur.position[tar] == NONE) continue;
        else {
            if ((tar == cur.kingpos[who] - 0x10) && (who == RED) && (cur.position[tar] == B_PAWN))
            {
			    suicide = TRUE;
			    goto finish;
            }  //�ж�˧ǰ����һ���Ƿ��ܵ�����в 
            if ((flag == 0) && ((who == BLACK) ? (cur.position[tar] == R_ROOK) : (cur.position[tar] == B_ROOK)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            else if ((flag == 1) && ((who == BLACK) ? (cur.position[tar] == R_CANNON) : (cur.position[tar] == B_CANNON)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            flag++;
        }
        if (flag == 2) break;  //ѭ���������ڶ������Ӻ�ֱ������ 
    }
    for (flag = 0, tar = cur.kingpos[who] + 0x10; tar < 0xd0; tar += 0x10) //˧�󷽣���ǰ�� 
    {
        if (cur.position[tar] == NONE) continue;
        else {
            if ((tar == cur.kingpos[who] + 0x10) && (who == BLACK) && (cur.position[tar] == R_PAWN))
            {
			    suicide = TRUE;
			    goto finish;
            } //�жϽ�ǰ����һ���Ƿ��ܵ�����в 
            if ((flag == 0) && ((who == BLACK) ? (cur.position[tar] == R_ROOK) : (cur.position[tar] == B_ROOK)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            else if ((flag == 1) && ((who == BLACK) ? (cur.position[tar] == R_CANNON) : (cur.position[tar] == B_CANNON)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            flag++;
        }
        if (flag == 2) break;  //ѭ���������ڶ������Ӻ�ֱ������ 
    }
    for (flag = 0, tar = cur.kingpos[who] - 0x01; (tar & 0x0f) > 0x02; tar -= 0x01) //˧�������� 
    {
        if (cur.position[tar] == NONE) continue;
        else {
            if ((tar == cur.kingpos[who] - 0x01) && ((who == BLACK) ? (cur.position[tar] == R_PAWN) : (cur.position[tar] == B_PAWN)))
            {
			    suicide = TRUE;
			    goto finish;
            }  //�ж�˧�������Ƿ��ܵ���(��)����в 
            if ((flag == 0) && ((who == BLACK) ? (cur.position[tar] == R_ROOK) : (cur.position[tar] == B_ROOK)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            else if ((flag == 1) && ((who == BLACK) ? (cur.position[tar] == R_CANNON) : (cur.position[tar] == B_CANNON)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            flag++;
        }
        if (flag == 2) break;  //ѭ���������ڶ������Ӻ�ֱ������ 
    }
    for (flag = 0, tar = cur.kingpos[who] + 0x01; (tar & 0x0f) < 0x0c; tar += 0x01) //˧�������ҷ� 
    {
        if (cur.position[tar] == NONE) continue;
        else {
            if ((tar == cur.kingpos[who] + 0x01) && ((who == BLACK) ? (cur.position[tar] == R_PAWN) : (cur.position[tar] == B_PAWN)))
            {
			    suicide = TRUE;
			    goto finish;
            }  //�ж�˧�������Ƿ��ܵ���(��)����в  
            if ((flag == 0) && ((who == BLACK) ? (cur.position[tar] == R_ROOK) : (cur.position[tar] == B_ROOK))) 
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            else if ((flag == 1) && ((who == BLACK) ? (cur.position[tar] == R_CANNON) : (cur.position[tar] == B_CANNON)))
            {
			    suicide = TRUE;
			    goto finish;
            } //�ж�˧�������Ƿ��ܵ��Է�����в 
            flag++;
        }
        if (flag == 2) break;  //ѭ���������ڶ������Ӻ�ֱ������ 
    }
    //��Ľ�����ʽ 
	for(i = 0; i < 8; i++)
	{
		tar = cur.kingpos[who] + cnKnightMoveTab[i];
		leg = cur.kingpos[who] + cnHorseLegBackTab[i];
		if (((who == BLACK) ? (cur.position[tar] == R_KNIGHT) : (cur.position[tar] == B_KNIGHT)) && cur.position[leg] == NONE)
		{
			suicide = TRUE;
			goto finish;
        }
	}

finish:    
    cur.DelMovement(mv);
    return (!face && !suicide);
}
