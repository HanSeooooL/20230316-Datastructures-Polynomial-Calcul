//
//  main.c
//  20230316 Datastructures 3
//  다항식 입력 출력 및 덧셈과 곱셈
//  Created by 한설 on 2023/03/16.
//

#include <stdio.h>
#include <time.h>
#define MAX_DEGREE 101

typedef struct {    //Polynomial 구조체 정의
    int degree;     //최고차수
    float coef[MAX_DEGREE];     //차수를 배열로 설정하고 각각의 칸에 계수 입력
} Polynomial;

void maincode(void);    //maincode 함수 예열
Polynomial read_poly(void); //다항식 입력함수 예열
void printf_poly(Polynomial p, int number); //다항식 출력함수 예열
void math(Polynomial *poly, int *i);    //다항식 계산함수 예열
Polynomial add_poly(Polynomial a, Polynomial b);    //다항식 덧셈함수 예열
Polynomial mul_poly(Polynomial a, Polynomial b);    //다항식 곱셈함수 예열

int main() {
    
    int a;
    maincode();
    return 0;
}


void maincode(void)
{
    int i, l, Q, n;
    printf("몇개의 다항식을 입력하시겠습니까? ");
    scanf("%d", &l);
    Polynomial P[l];
    for(i = 0; i < l; i++)
    {
        P[i] = read_poly();
        printf_poly(P[i], i);
    }
    
    while (i == 0) {
        printf("입력된 다항식이 1개입니다. 계산을 위해서는 다항식을 더 입력하셔야 합니다. \n");
        printf("더 입력하시려면 1 이대로 프로그램을 끝내시려면 0 ");
        scanf("%d", &Q);
        if (Q == 1)
        {
            printf("몇개의 다항식을 더 입력하시겠습니까? ");
            scanf("%d", &n);
            l += n;
            for (; i < l; i++)
            {
                P[i] = read_poly();
                printf_poly(P[i], i);
            }
        }
        else if (Q == 0)
        {
            break;
        }
        else
        {
            printf("잘못 입력하셨습니다. 다시 입력해주세요. \n");
        }
    }
    
    if (i > 0)
        math(P, &i);
    else
        printf("계산할 다항식이 부족해 프로그램을 종료합니다. ");
}


void printf_poly(Polynomial p, int number)  //Polynomial 구조체형태와 정수형 number를 매개변수로 하는 다항식을 출력해주는 함수.
{
    int i;
    printf("\t%d : ", number);  //다항식 번호 출력
    for(i = 0; i < p.degree; i++)
    {
        if (p.coef[i] != 0) //계수가 0인 항은 출력하지 못하게끔 조정
            printf("%5.1f x^%d + ", p.coef[i], p.degree - i);
    }
    printf("%4.1f\n", p.coef[p.degree] );
}



Polynomial read_poly(void)  //다항식을 구조체로 입력하는 함수.
{
    int i;
    Polynomial p;
    printf("다항식의 최고 차수를 입력하시오 (최대 100) : ");
    scanf("%d", &p.degree); //degree에 다항식의 최고 차수 입력
    printf("각 항의 계수를 입력하시오 (총 %d개) \n", p.degree + 1);
    for( i = 0; i <= p.degree; i++) //0차 항부터 degree의 값과 같은 차수의 항까지 순차적으로 입력
        scanf("%f", p.coef + i);
    for (i = p.degree ; i >= 0; i--)    //최고차항에 0이 입력되어있을 시 degree값을 하나 줄이기 (곱셈을 위해 필요)
    {
        if (p.coef[i] == 0)
        {
            p.degree = p.degree - 1;
        }
        else
            break;
    }
    return p;
}


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

