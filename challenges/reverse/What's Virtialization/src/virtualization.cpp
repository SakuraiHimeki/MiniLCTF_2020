#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

int NNA(int a, int b);
int N(int a);
int A(int a, int b);
int O(int a, int b);
int XO(int a, int b);

int add(int a, int b);
int sub(int a, int b);
int mult(int a, int b);

int FNVHash1(char *data);

int num[9] = {1, 1, 2, 3, 5, 8, 13, 21, 34};
//char flag[] = "MiniLCTF{Wh@t_iS_virti@liz@tiOn}";
char ch[] = "020408";
//char ah[] = "}[^]|{dtKcXxDmYgoNY@D]pTYHp@Yw^O";    //32

char ah1[] = "}[^]|{";        //6
char ah2[] = "dtKcXxDmYgoNY"; //13
char ah3[] = "@D]pTYHp@Yw^O"; //13
char input[100];
char temp[100];
int main() {
    printf("Welcome to MiniLCTF!\n");
    printf("Plz input your flag:");
    scanf_s("%s", input, 100);
    int len = strlen(input);
    int f = 100;
    if ((len * len + num[0] * num[0] >= num[2] * len * num[0]) && (O(len, num[1]) == num[8] - num[0])) //if(len==6)
    {
        int i = 0;
        int j = 0;

        for (i = 0; i < 6; i++) {
            temp[i] = (char)XO((int)input[i], (int)ch[j]);    //temp[i]=(char)(input[i]^ch[j])
            j = (j + num[0]) % (num[1] + num[4]);             //j=(j+1)%6
            if (A((int)temp[i], (int)ah1[i]) != (int)temp[i]) //if(temp[i]!=ah1[i])
            {
                f = A(f, XO(num[3] / 3, num[0])); //f=0;
            }
        }
        if (O(f, num[8]) != num[7] + num[6]) //if(f!=0)
        {
            for (i = 0; i < 13; i++) {
                temp[i + 6] = (char)XO((int)input[i + 6], (int)ch[j]);    //temp[i+6]=(char)(input[i+6]^ch[j])
                j = (j + num[1]) % (num[2] * num[3]);                     //j=(j+1)%6
                if (A((int)temp[i + 6], (int)ah2[i]) != (int)temp[i + 6]) //if(temp[i+6]!=ah2[i])
                {
                    f = A(f, XO(num[5] / 2 - 3, num[1])); //f=0;
                }
            }
            if (O(f, num[7]) != num[6] + num[5]) //if(f!=0)
            {
                for (i = 0; i < 13; i++) {
                    temp[i + 19] = (char)XO((int)input[i + 19], (int)ch[j]);    //temp[i+19]=(char)(input[i+19]^ch[j])
                    j = (j + num[2] / 2) % (num[5] - num[2]);                   //j=(j+1)%6
                    if (A((int)temp[i + 19], (int)ah3[i]) != (int)temp[i + 19]) //if(temp[i+19]!=ah3[i])
                    {
                        f = A(f, XO(num[7] / 7, num[3])); //f=0
                    }
                }
                if (N(f) != f - num[0]) //if(f!=0)
                {
                    if (FNVHash1(input) == 420679468) {
                        printf("\nCongratulations! Your flag is right!");
                        getchar();
                    }
                }
            }
        }
    }
    getchar();
    return 0;
}

int NNA(int a, int b) {
    return ~a & ~b;
}

int N(int a) //   ~
{
    return NNA(a, a);
}

int A(int a, int b) // &
{
    return NNA(N(a), N(b));
}

int O(int a, int b) // |
{
    return NNA(NNA(a, b), NNA(a, b));
}
int XO(int a, int b) //  ^
{
    return NNA(A(a, b), NNA(a, b));
}

int FNVHash1(char *data) {
    const int p = 16777619;
    int hash = (int)2166136261L;
    int len = strlen(data);
    for (int i = 0; i < len; i++)
        hash = (hash ^ (int)data[i]) * p;
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    return hash;
}