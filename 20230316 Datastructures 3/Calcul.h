//
//  Calcul.h
//  20230316 Datastructures 3
//
//  Created by 한설 on 2023/03/19.
//


#define MAX_DEGREE 101

typedef struct {    //Polynomial 구조체 정의
    int degree;     //최고차수
    float coef[MAX_DEGREE];     //차수를 배열로 설정하고 각각의 칸에 계수 입력
} Polynomial;
void math(Polynomial *poly, int *i);    //다항식 계산함수 예열
Polynomial add_poly(Polynomial a, Polynomial b);    //다항식 덧셈함수 예열
Polynomial mul_poly(Polynomial a, Polynomial b);    //다항식 곱셈함수 예열
Polynomial read_poly(void); //다항식 입력함수 예열
void printf_poly(Polynomial p, int number); //다항식 출력함수 예열
void maincode(void);    //maincode 함수 예열
