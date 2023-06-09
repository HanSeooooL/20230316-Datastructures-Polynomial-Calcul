//
//  main.c
//  20230316 Datastructures 3
//  다항식 입력 출력 및 덧셈과 곱셈
//  Created by 한설 on 2023/03/16.
//


#include <stdio.h>
#include <time.h>
#include "Calcul.h"


int main() {
    
    maincode();
    return 0;
}

void maincode(void)
{
    int i, l, t, Q, n;
    printf("몇개의 다항식을 입력하시겠습니까? (최대 10개)");  //입력받을 다항식 개수 입력
    scanf("%d", &l);
    t = l + 5;  //다항식을 계산해서 저장할 칸 여유분 확보
    Polynomial P[t];
    for(i = 0; i < l; i++)
    {
        P[i] = read_poly();
        printf_poly(P[i], i);
    }
    
    while (i == 1) {
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
                printf("%5.1fx^%d + ", p.coef[i], p.degree - i);
            }
            else    //X^0항 출력
            {
                printf("%5.1f", p.coef[i]);
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
    for( i = 0; i <= p.degree; i++) //degree값과 같은 차수의 항부터 0차수의 항까지 순차적으로 입력
    {
        scanf("%f", p.coef + i);    //p.coef + i --> &(p.coef[i])
    }
    
    while (1)
    {
        if (p.coef[0] == 0)
        {
            for (i = 0; i < p.degree; i++)
            {
                p.coef[i] = p.coef[i + 1];  //칸을 왼쪽으로 한칸씩 옮기기(최고차항이 배열의 0칸에 저장되어 있으므로.)
            }
            p.degree -= 1;
        }
        else if (p.coef[0] != 0)
            break;
    }
    return p;
}
