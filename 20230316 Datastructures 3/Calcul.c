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
    int C, Pl, Plu, j;
    int S = 1;
    
    
    while (S != 0)  //S가 0과 같지 않을 때 반복한다.
    {
        printf("입력된 모든 다항식 \n ");
        for(j = 0; j < *i; j++) //입력된 모든 다항식 출력
        {
            printf_poly(*(&poly[j]), j);
        }
        printf("다항식을 더하시려면 1 곱하시려면 2 그만두시려면 0을 입력해주세요. ");
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
        }
        
        else    //C != 0, 1, 2
        {
            printf("잘못입력하셨습니다. 다시 입력해주세요. \n");
        }
    }
}


Polynomial add_poly(Polynomial a, Polynomial b) //다항식 덧셈함수
{
    Polynomial res; //결과값 저장 구조체
    
    if (a.degree >= b.degree)    //b의 최고차수보다 a의 최고차수가 크거나 같을 때
        res.degree = a.degree;  //res의 최고차수는 a의 최고차수와 같다
    else if (a.degree < b.degree)   //아니면 b의 최고차수보다 a의 최고차수가 작을 때
        res.degree = b.degree;      //res의 최고차수는 b의 최고차수와 같다
    for(int i = 0; i < res.degree; i++) //i가 res의 최고차수보다 적을 때 반복한다. (코드 실행이 끝날 때 i에 1을 더한다)
    {
        res.coef[i] = a.coef[i] + b.coef[i];    //res의 x^i의 계수는 a의 x^i의 계수와 b의 x^i의 계수를 더한 것과 같다.
    }
    
    return res;
}


Polynomial mul_poly(Polynomial a, Polynomial b) //다항식 곱셈함수
{
    Polynomial res; //결과값 저장 구조체
    int i, j;
    
    res.degree = a.degree + b.degree;   //res의 최고차수는 a와 b 각각의 최고차수를 서로 더한 것과 같다.
    
    for(i = 0; i < res.degree; i++) //res.coef배열 초기화
    {
        res.coef[i] = 0;
    }
    
    for(i = 0; i < a.degree; i++)
    {
        for(j = 0; j < b.degree; j++)
        {
            res.coef[i + j] += a.coef[i] * b.coef[j]; //a의 i항의 계수와 b의 j항의 계수를 서로 곱하고 res의 i+j항에 더한다.
        }
    }
    
    
    
    return res;
}

