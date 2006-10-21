/*! \file searcher.cpp
@brief �����������ࣨ����ģ�飩
*/

#include "searcher.h"

void Searcher::GetBestmove(Board & cur, PLAYER who)
{
    //�������������ŷ��ִ�����long��ʾ 
    char cmdBest[5], cmdBetter[5], cmdGood[5];
    long lngBest, lngBetter, lngGood;

    //Ϊbest��better��good����ֵ����ֹ������ŷ�С��2�ֶ��������� 
    int count;
    count = MoveMaker::Make(cur, who, allmoves[MAX_SEARCH_DEPTH]);
    if (count != 0)
    {
        lastbest = lastbetter = lastgood = best = better = good = allmoves[MAX_SEARCH_DEPTH][0];
    }
    else
    {
        printf("nobestmove\n");
        fflush(stdout);
        return;
    }
    
    //�����ڿ��ֿ��м���������ڿ��ֿ����Ҳ������Ž��в��������� 
    if (OpenBook::Search(cur, cmdBest))
    {
        if (cur.CanGo(cmdBest))
        {
            printf("bestmove %4s\n", cmdBest);
            fflush(stdout);
            history[who][0] = history[who][1];
            history[who][1] = history[who][2];
            history[who][2] = history[who][3];
            history[who][3] = lngBest;
            return; 
        }  
    }
    
    //��ʼ��������� 
    int lastvalue;
    startTime = time(NULL);
    for (searchDepth = 1; searchDepth <= MAX_SEARCH_DEPTH; searchDepth += 1)
    {
        //�����PVS�㷨
        if ((lastvalue = PVSearch(cur, searchDepth, who, NO_BEST_MOVE, -NO_BEST_MOVE)) != TIME_OVER)
        {
            lastbest = best;
            lastbetter = better;
            lastgood = good;
            
            printf("info depth %d score %d", searchDepth, lastvalue);
//            printf(" pv");
//            int i;
//            char str[5];
//            for (i = searchDepth; i >= 1; i--)
//            {
//                trace[i].Move2Str(str);
//                printf(" %s", str);
//            }
//            for (i = MAX_QUIES_DEPTH; i >= 0; i--)
//            {
//                qstrace[i].Move2Str(str);
//                printf(" %s", str);
//            }
            printf("\n");
            fflush(stdout);
    
            //����ڸ��ٵĲ�����ֱ��ʹ�Է���Ͷ��·���Ͳ������������ˣ�ֱ������һ��
            if (lastvalue >= (- NO_BEST_MOVE - MAX_VALUE_OF_BOARD))
            {
                break;
            }
        }
        else
        {
            break;    
        }
    }   
    
    lastbest.Move2Str(cmdBest);
    lastbetter.Move2Str(cmdBetter);
    lastgood.Move2Str(cmdGood);
    lngBest = *(long *)cmdBest;
    lngBetter = *(long *)cmdBetter;
    lngGood = *(long *)cmdGood;
    if ((history[who][0] == history[who][2]) && (history[who][2] == lngBest))
    {
        if ((history[who][0] == history[who][2]) && (history[who][2] == lngBetter))
        {
            printf("bestmove %4s\n", cmdGood);
            fflush(stdout);
            history[who][0] = history[who][1];
            history[who][1] = history[who][2];
            history[who][2] = history[who][3];
            history[who][3] = lngGood;
        }
        else
        {
            printf("bestmove %4s\n", cmdBetter);
            fflush(stdout);
            history[who][0] = history[who][1];
            history[who][1] = history[who][2];
            history[who][2] = history[who][3];
            history[who][3] = lngBetter;
        }
    }
    else
    {
        printf("bestmove %4s\n", cmdBest);
        fflush(stdout);
        history[who][0] = history[who][1];
        history[who][1] = history[who][2];
        history[who][2] = history[who][3];
        history[who][3] = lngBest;
    }
}

Bool Searcher::GameOver(Board & cur)
{
    return (cur.kingpos[RED] == 0x00 || cur.kingpos[BLACK] == 0x00);
}

int Searcher::PVSearch(Board & cur, int depth, PLAYER who, int alpha, int beta)
{
    int i, j;
    //�����ŷ����� 
    int count;
    //�Ե�ǰ�ŷ����ɵľ����ֵ����ǰ����ѹ�ֵ 
    int value, bestvalue;
    bestvalue = NO_BEST_MOVE;
    
    //�ù�ϣ����ʷ�����¼��ֹ�߳�ѭ������ 
    hashlink[depth] = cur.zobrist;
    for (j = searchDepth; j > depth; j--)
    {
        if (hashlink[j] == hashlink[depth])  
        {
            return NO_BEST_MOVE;
        }
    }
    
    if (time(NULL) - startTime > LONGEST_SEARCH_TIME)
    {
        return TIME_OVER;    
    }
    if (GameOver(cur))
    {
        return Evaluation::Eval(cur, who);
    }
    
    //�������û����в��� 
//    value = Hashnum::SearchTT(cur.zobrist, searchDepth, depth, who, alpha, beta);
//    if (value != NOT_IN_TT)
//    {
//        return value;    
//    }
    
    if (depth == 0)
    {
        value = QuiesSearch(cur, MAX_QUIES_DEPTH, who, alpha, beta);
        //Hashnum::SaveTT(cur.zobrist, searchDepth, depth, who, EXACT, value);
        return value;
    }
    count = MoveMaker::Make(cur, who, allmoves[depth]);
    if (count == 0)
    {
        return NO_BEST_MOVE;
    }
    
    //���ĳ���ŷ�����һ�ε�������ã�������һ�ε��������ȼ��� 
    if (depth == searchDepth && searchDepth > 1)
    {
        for (i = 1; i < count; i++)
        {
            if (allmoves[depth][i].from == lastbest.from && allmoves[depth][i].to == lastbest.to)
            {
                allmoves[depth][i] = allmoves[depth][0];
                allmoves[depth][0] = lastbest;
                break;
            }
        }
    }

    cur.AddMovement(allmoves[depth][0]);
    bestvalue = -PVSearch(cur, depth - 1, (PLAYER)1 - who, -beta, -alpha);
    cur.DelMovement(allmoves[depth][0]);
    if (depth == searchDepth)
    {
        good = better;
        better = best;
        best = allmoves[depth][0];
    }
        
    for (i = 1; i < count; i++)
    {
        if (time(NULL) - startTime > LONGEST_SEARCH_TIME)
        {
            return TIME_OVER;    
        }
        if (bestvalue < beta)
        {
            if (bestvalue > alpha)
            {
                alpha = bestvalue;     
            }
            cur.AddMovement(allmoves[depth][i]);
            value = -PVSearch(cur, depth - 1, (PLAYER)1 - who, -alpha - 1, -alpha);  
            if (value > alpha && value < beta)
            {
                bestvalue = -PVSearch(cur, depth - 1, (PLAYER)1 - who, -beta, -value);  
                if (depth == searchDepth)
                {
                    good = better;
                    better = best;
                    best = allmoves[depth][i];
                } 
            }
            else if (value > bestvalue)
            { 
                bestvalue = value;
                if (depth == searchDepth)
                {
                    good = better;
                    better = best;
                    best = allmoves[depth][i];
                }
            }
            cur.DelMovement(allmoves[depth][i]);   
        }
    }
    
    //Hashnum::SaveTT(cur.zobrist, searchDepth, depth, who, EXACT, bestvalue);

    return bestvalue;
}

int Searcher::QuiesSearch(Board & cur, int depth, PLAYER who, int alpha, int beta)
{
    int i, j;
    //�����ŷ����� 
    int count;
    //�Ե�ǰ�ŷ����ɵľ����ֵ����ǰ����ѹ�ֵ 
    int value;
    
    //�ù�ϣ����ʷ�����¼��ֹ�߳�ѭ������ 
    qshashlink[depth] = cur.zobrist;
    for (j = searchDepth; j > 0; j--)
    {
        if (hashlink[j] == qshashlink[depth])  
        {
            return NO_BEST_MOVE;
        }
    }
    for (j = MAX_QUIES_DEPTH; j > depth; j--)
    {
        if (qshashlink[j] == qshashlink[depth])  
        {
            return NO_BEST_MOVE;
        }
    }
    
    if (GameOver(cur) || depth == 0)
    {
        return Evaluation::Eval(cur, who);
    }
    value = Evaluation::Eval(cur, who);
    if (value >= beta) 
    {
        return beta; 
    }
    if (value > alpha) 
    {
        alpha = value; 
    }
    count = MoveMaker::Make(cur, who, qsmoves[depth]);
    if (count == 0)
    {
        return NO_BEST_MOVE;
    }
    for (i = 0; i < count; i++)
    {
        //ֻ�Լ�ֵ��������������� 
        if (qsmoves[depth][i].ate == R_KING || 
            qsmoves[depth][i].ate == B_KING || 
            qsmoves[depth][i].ate == R_KNIGHT || 
            qsmoves[depth][i].ate == B_KNIGHT || 
            qsmoves[depth][i].ate == R_ROOK || 
            qsmoves[depth][i].ate == B_ROOK || 
            qsmoves[depth][i].ate == R_CANNON || 
            qsmoves[depth][i].ate == B_CANNON
        )
        {
            cur.AddMovement(qsmoves[depth][i]);
            value = -QuiesSearch(cur, depth - 1, (PLAYER)1 - who, -beta, -alpha);
            cur.DelMovement(qsmoves[depth][i]);
            if (value >= beta) 
            {   
                return beta; 
            }
            if (value > alpha) 
            {
                alpha = value; 
            }
        }
    }
    return alpha;
}
