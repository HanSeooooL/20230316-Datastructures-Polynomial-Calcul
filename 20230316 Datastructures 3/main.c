//
//  main.c
//  20230316 Datastructures 3
//  다항식 입력 출력 및 덧셈과 곱셈
//  Created by 한설 on 2023/03/16.
//


#include <stdio.h>
#include <time.h>
#include "Calcul.h"

Polynomial read_poly(void); //다항식 입력함수 예열
void printf_poly(Polynomial p, int number); //다항식 출력함수 예열


int main() {
    
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
    for(i = 0; i <= p.degree; i++)
    {
        if(p.coef[i] != 0)
        {
            if (i != p.degree)  //X^0항을 제외한 항 출력
            {
                printf("%.1fx^%d + ", p.coef[i], p.degree - i);
            }
            else    //X^0항 출력
            {
                printf("%.1f", p.coef[i]);
            }
        }
    }
    printf("\n");
    
}



Polynomial read_poly(void)  //다항식을 구조체로 입력하는 함수.
{
    int i;
    Polynomial p;
    printf("다항식의 최고 차수를 입력하시오 (최대 100) : ");
    scanf("%d", &p.degree); //degree에 다항식의 최고 차수 입력
    printf("각 항의 계수를 입력하시오 (총 %d개) \n", p.degree + 1);
    for( i = 0; i <= p.degree; i++) //0차 항부터 degree의 값과 같은 차수의 항까지 순차적으로 입력
    {
        scanf("%f", p.coef + i);    //p.coef + i --> &(p.coef[i])
        printf("%f %d\n", p.coef[i], i);
    }
    for (i = p.degree ; i >= 0; )    //최고차항에 0이 입력되어있을 시 degree값을 하나 줄이기 (곱셈을 위해 필요)
    {
        if (p.coef[p.degree] == 0)
        {
            p.degree = p.degree - 1;
            i = i - 1;
        }
        else
            break;
    }
    return p;
}
