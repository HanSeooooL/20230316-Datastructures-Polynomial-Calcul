//
//  Calcul.c
//  20230316 Datastructures 3
//
//  Created by 한설 on 2023/03/19.
//

#include <stdio.h>
#include "Calcul.h"



void math(Polynomial *poly, int *i) //다항식 계산할때 쓰는 톨게이트 함수.
{
    int C, Pl, Plu, j, t = 5;
    double x, y;
    int S = 1;
    if (t > 0) {
        while (S != 0)  //S가 0과 같지 않을 때 반복한다.
        {
            printf("\n\t입력된 모든 다항식 \n\n ");
            for(j = 0; j < *i; j++) //입력된 모든 다항식 출력
            {
                printf_poly(*(&poly[j]), j);
            }
            printf("다항식을 더하시려면 1 곱하시려면 2 x에 숫자를 대입해 결과값을 출력하시려면 3 그만두시려면 0을 입력해주세요. (%d번 남음, 대입계산은 횟수에서 제외)", t);
            scanf("%d", &C);
            if(C == 0)  //그만둘게용 0
                break;
            
            else if (C == 1)    //더할게용 1
            {
                printf("더할 다항식 2개를 입력해주세요 ex) 1 2 ");
                scanf("%d %d", &Pl, &Plu);
                
                printf("\t");
                printf_poly(*(&poly[Pl]), Pl);
                printf("+\t");
                printf_poly(*(&poly[Plu]), Plu);
                printf("\n");
                
                *(poly + *i) = add_poly(*(&poly[Pl]), *(&poly[Plu]));
                printf_poly(*(&poly[*i]), *i); //현재 저장된 마지막 다항식 다음 다항식에 저장
                *i = *i + 1;
                
                t = t - 1;
            }
            
            else if (C == 2)    //곱할게용 2
            {
                printf("곱할 다항식 2개를 입력해주세요 ex) 1 2 ");
                scanf("%d %d", &Pl, &Plu);
                
                printf("\t");
                printf_poly(*(&poly[Pl]), Pl);
                printf("*\t");
                printf_poly(*(&poly[Plu]), Plu);
                printf("\n");
                
                *(poly + *i) = mul_poly(*(&poly[Pl]), *(&poly[Plu]));
                printf_poly(*(&poly[*i]), *i);
                *i = *i + 1;
                
                t = t - 1;
            }
            else if (C == 3)
            {
                printf("대입할 다항식을 선택해주세요 ");
                scanf("%d", &Pl);
                printf("대입할 숫자(정수)를 입력해주세요 ");
                scanf("%lf", &x);
                
                y = cal_poly(*(&poly[Pl]), x);
                
                printf("계산값은 %lf \n", y);
                
            }
            
            else    //C != 0, 1, 2, 3
            {
                printf("잘못입력하셨습니다. 다시 입력해주세요. \n");
            }
        }
    }
}


Polynomial add_poly(Polynomial a, Polynomial b) //다항식 덧셈함수
{
    int i;
    Polynomial p;
    if (a.degree > b.degree )   //b다항식보다 a다항식의 최고차수가 더 높을 때
    {
        p = a;  //p다항식에 a다항식 복사
        for(i = 0; i <= b.degree; i++) //i가 b의 최고차항과 같아질때까지
        {
            p.coef[i + (p.degree - b.degree)] += b.coef[i];
            //최고차항이 먼저 저장되어있는 이 프로그램의 coef배열 특성을 고려하여 p.coef에는 i에 최고차항의 차를 더한다.
        }
    }
    else    //아닐 경우
    {
        p = b;  //p다항식에 b다항식 복사
        for ( i = 0; i <=a.degree ; i++)
            //최고차항이 먼저 저장되어있는 이 프로그램의 coef배열 특성을 고려하여 p.coef에는 i에 최고차항의 차를 더한다.
            p.coef[i +(p.degree - a.degree )] += a.coef[i];
    }
    return p;
}


Polynomial mul_poly(Polynomial a, Polynomial b) //다항식 곱셈함수
{
    Polynomial res; //결과값 저장 구조체
    int i, j;
    
    res.degree = a.degree + b.degree;   //res의 최고차수는 a와 b 각각의 최고차수를 서로 더한 것과 같다.
    
    for(i = 0; i <= res.degree; i++) //res.coef배열 초기화
    {
        res.coef[i] = 0;
    }
    
    for(i = 0; i <= a.degree; i++)
    {
        for(j = 0; j <= b.degree; j++)
        {
            res.coef[i + j] += a.coef[i] * b.coef[j]; //a의 i항의 계수와 b의 j항의 계수를 서로 곱하고 res의 i+j항에 더한다.
        }
    }
    
    return res;
}

double cal_poly(Polynomial a, double x) //다항식 대입함수
{
    double y = 0, xt;
    int i, j = 0;
    while(a.degree >= 0)    //degree가 0 이상일때 작동
    {
        xt = 1;
        for(i = 0; i < a.degree; i++)   //차수만큼 x를 곱한 값을 저장 (다항식에 x를 대입)
            xt = xt * x;
        xt = xt * a.coef[j];    //계수를 곱함
        y = y + xt; //곱한 값을 더한다.
        j = j + 1;  //다음 칸으로 이동
        a.degree = a.degree - 1;    //다음 차수로 이동
    }
    return y;   //다 더한 값 출력
}

