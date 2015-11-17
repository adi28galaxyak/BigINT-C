/*
	/****************************************************************************************************
	/****************************************************************************************************

	Name: BigInt 
	Copyright: 2015 - belongs to the Authors.
	Author: ADITYA KUMAR, SURAJ PRAKASH CHOUBEY, DIWAKAR BHARDWAJ (NIT Agartala, CSE Dept.)
	Date: 16/11/15 23:20
	Description: It handles INTEGER overflows in C. Also, Negative modulus are handled.
	
	NOTE: Read Working Manual.txt to use this header file.
	All the features are given in Features.txt
	/****************************************************************************************************
	/****************************************************************************************************
*/

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

#define max(a,b) a>b?a:b
#define MAX 10000

struct bigInt{
    char INT[MAX+5];
    int sign;               /// 1 means positive and -1 means negative
    int extra;              /// if starting character is consisting any sign (+ or -)
};

typedef struct bigInt bigInt;

char *add(char *a, char *b); /// ADDITION
char *sub(char *a, char *b); /// SUBTRACTION
char *mul(char *a, char *b); /// MULTIPLICATION
char *div(char *a, long long divisor);/// DIVISION
char *mod(char *a, char *b); /// MODULUS

char *trimSign(char* a){                                        /// Sign + Unnecessary Zeros are removed
    int i = 0, k = 0, alen = strlen(a);
    char *C = (char *)malloc(alen+6);

    while((a[i]=='+') || (a[i]=='-') || (a[i]=='0')) i++; /// i don't want this garbage
    while(i<alen) C[k++] = a[i++];
    C[k] = '\0';

    if(!k) strcpy(C, "0");

    return C;
}


char* trim(char *a){                                                    /// Unnecessary Zeros are removed
    int i = 0, k = 0, alen = strlen(a), ok = 0; /// ok is to check whether num is 0 or not

    char *C = (char *)malloc(alen+6);
    if(a[i]=='+' || a[i]=='-') C[k++] = a[i], i++; /// ok is not updated since number can be 0
    while(a[i]=='0') i++; /// Removing unnecessary zeros
    while(i<alen) C[k++] = a[i++], ok = 1; /// Number is non zero
    C[k] = '\0';
    if(!ok) C[0] = '0', C[1] = '\0';

    return C;
}


void status(bigInt *a){                                                  /// check 0 - (neither positive nor negative)
    if(a->INT[0]=='+' || a->INT[0]=='-') a->extra = 1;
    else a->extra = 0;
    if(a->INT[0]=='-') a->sign = -1;
    else a->sign = 1;

    char *C = (char *)malloc(strlen(a->INT) + 5);
    strcpy(C, trimSign(a->INT));
    if(C[0]=='0') {                 /// The given number is 0
        a->sign = 0;                /// No sign for 0
        a->extra = 0;               /// no extra bits left
        strcpy(a->INT, C);          /// update the string A with trimmed value 0
    }
    free(C);
}

#define endl printf("\n")

void print(char *a){                                            /// print the value of a.INT
    printf("%s",trim(a));
}

void printSign(bigInt *a){                                      /// print the sign of a.INT
    status(a);
    if(a->sign==1) printf("%c",'+');
    else if(a->sign==-1) printf("%c",'-');
}

void printBigInt(bigInt *a){                                    /// print the value with sign of bigInt
    printSign(a);
    printf("%s",trimSign(a->INT));
}

void scan(bigInt *a){                                           /// Input from User
    scanf("%s",(*a).INT);
    status(a);
}

void eq(char *a, char *b){                                      /// Copies data of b into a
    strcpy(a,b);
}

void eqBigInt(bigInt *a, char *s){                                    /// equate Char *s to bigInt
    strcpy(a->INT,s);
    status(a);
}

char *str(int a){                                                /// Convert int to string
    char *C = (char *)malloc(MAX+5);
    int k = 0, r = a<0?-1:1;
    a = abs(a);
    while(a){
        C[k++] = (a%10)+'0';
        a/=10;
    }
    if(r==-1) C[k++] = '-', C[k] = '\0';
    else C[k] = '\0';
    strrev(C);
    return C;
}

int integer(char *a){                                           /// Convert String to INTEGER

    /// TODO: what is the perfect return type of atoi
    return atoi(a);
}

char* ABS(char *a){                                             /// find the absolute value
    return trimSign(a);
}

int cmp(char *A, char *B){                                     /// cmp funtion {a>b , a==b, a<b} return {1, 0, -1}
    int alen = strlen(A), blen = strlen(B);
    char *a = (char *)malloc(alen);
    char *b = (char *)malloc(blen);
    strcpy(a, trim(A));
    strcpy(b, trim(B));
    int asign = a[0]!='-'?1:-1, bsign = b[0]!='-'?1:-1;
    int sta = 0, stb = 0, i, j;

    /// a and b are trimmed before

    if(asign!=bsign) return asign==1?1:-1;

    if(asign==1){ /// both number are positive
        if(a[0]=='+') alen--, sta++;
        if(b[0]=='+') blen--, stb++;

        if(alen>blen) return 1;
        else if(alen==blen){
            for(i = sta, j = stb; i<alen;i++,j++){
                if(a[i]>b[j]) return 1;
                if(a[i]<b[j]) return -1;
            }
            return 0; /// both the numbers are same
        }
        else return -1;
    }

    else{ /// both numbers are negative ... done to avoid confusion
        if(alen>blen) return -1; /// (a>b) in magnitute but both the numbers are negative
        else if(alen==blen){
            for(i = 0, j = 0; i<alen;i++,j++){
                if(a[i]>b[j]) return -1;
                if(a[i]<b[j]) return 1;
            }
            return 0;
        }
        else return 1;
    }
}

char* add(char *a, char *b){                                                /// add two bigInts
    int asign = a[0]=='-'?-1:1, bsign = b[0]=='-'?-1:1;
    int w = 0;

    if(asign != bsign){
        if(asign == 1 && bsign == -1 ){
            return sub(trimSign(a), trimSign(b));   /// trim a and b
        }

        if(asign == -1 && bsign == 1){
                return sub(trimSign(b), trimSign(a));
            }
        }


    char *opa = (char *)malloc(strlen(a)+1);
    char *opb = (char *)malloc(strlen(b)+1);

    strcpy(opa, trimSign(a));
    strcpy(opb, trimSign(b));

    int i, carry = 0, rem, dummy,k=0;
    int alen = strlen(opa), blen = strlen(opb);
    int maxlen = max(alen, blen);

    char *A = (char *)malloc(maxlen+3);
    char *B = (char *)malloc(maxlen+3);

    char *ADD = (char *)malloc(maxlen+3);
    char *C = (char *)malloc(maxlen+3);
    if(asign==-1) ADD[0] = '-', w = 1;

    for(i = alen-1;i>=0;i--) A[k] = opa[i],k++;
    while(k<maxlen) A[k] = '0',k++;
    A[maxlen] = '\0';
    k=0;
    for(i = blen-1;i>=0;i--) B[k] = opb[i],k++;
    while(k<maxlen) B[k] = '0',k++;
    B[maxlen] = '\0';

    free(opa);
    free(opb);

    for(i = 0;i<maxlen;i++){
        dummy = (A[i]-'0') + (B[i]-'0') + carry;
        rem = dummy%10;
        carry = dummy/10;
        C[i] = rem + '0';
    }

    free(A);free(B);
    C[maxlen] = '\0';
    if(carry){
        C[maxlen] = carry + '0';
        C[maxlen + 1] = '\0';
    }
    strrev(C);

    for(i = 0;i<strlen(C);i++) ADD[w++] = C[i];
    free(C);
    ADD[w] = '\0';

    return ADD;
}

char *sub(char *a, char *b){                                                /// Substract two bigInt
    int borrow = 0, i, k=0;
    char asign, bsign;
    int alen = strlen(a), blen = strlen(b);
    int maxlen = max(alen, blen);
    char *A = (char *)malloc(maxlen+5);
    char *B = (char *)malloc(maxlen+5);
    char *C = (char *)malloc(maxlen+5);
    char *tempa = (char *)malloc(maxlen+5);
    char *tempb = (char *)malloc(maxlen+5);
    strcpy(tempa, a);
    strcpy(tempb, b);


    if(a[0] == '-')
        asign = '-';
    else if(a[0] == '+')
        asign = '+';
    else
        asign = '+';
    if(b[0] == '-')
        bsign = '-';
    else if(b[0] == '+')
        bsign = '+';
    else
        bsign = '+';
    if(asign == '+' && bsign == '-'){
        strcpy(C, add(trimSign(a), trimSign(b)));   /// trim a and b
        return trim(C);
    }

    if(asign == '-' && bsign == '+'){
        strcpy(C, add(trimSign(a),trimSign(b)));    /// trim a and b
        int c_size = strlen(C);
        strrev(C);
        C[c_size++] = '-';
        C[c_size] = '\0';
        strrev(C);
        return trim(C);
    }
    if(asign == '-' && bsign == '-'){
        char *temp = (char *)malloc(alen);
        strcpy(temp, a);
        strcpy(a, b);
        strcpy(b, temp);

    }
    int flag = 0;   /// to update the -ve sign  if 1 else 0
                    /// trim a and b and then compare
    strcpy(a, trimSign(a));
    strcpy(b, trimSign(b));

    if(cmp(a, b) == -1){    /// a<b then flag = 1 swap a and b;
        char *temp = (char*)malloc(alen);
        flag = 1;
        strcpy(temp, a);
        strcpy(a, b);
        strcpy(b, temp);

    }
    alen = strlen(a);
    blen = strlen(b);
    maxlen = max(alen, blen);

    /// assign a to A(in reverse) b to B(in reverse)
    for(i = alen-1;i>=0;i--)
        A[k++] = a[i];
    while(k<maxlen)
        A[k++] = '0';
    A[maxlen] = '\0';
    k=0;
    for(i = blen-1;i>=0;i--)
        B[k++] = b[i];
    while(k<maxlen)
        B[k++] = '0';
    B[maxlen] = '\0';

    for(i=0; i<maxlen; ++i){
        int temp = (A[i] - '0' - borrow) - (B[i] - '0');
        if(temp < 0)
            temp += 10, borrow = 1;
        else
            borrow = 0;
        C[i] = temp + '0';

    }
    if(flag)
        C[maxlen] = '-', C[maxlen+1] = '\0';
    else
        C[maxlen] = '\0';
    strrev(C);
    strcpy(a, tempa);
    strcpy(b, tempb);
    return trim(C);
}

char* multiply(char *a, char b){ /// It is called when len(b)==1.
    /// ***(NOTE: IMP) Without sign and extra bits it is passed (trimmed)

    int alen = strlen(a), i, k = 0,pro, carry = 0;
    char *C = (char *)malloc(alen+3);
    char *A = (char *)malloc(alen+3);

    for(i = alen-1;i>=0;i--) A[k] = a[i], k++;
    A[k] = '\0';

    for(i = 0;i<alen;i++){
        pro = (A[i] - '0')*(b - '0') + carry;
        C[i] = pro%10 + '0';
        carry = pro/10;
    }
    free(A);
    C[alen] = '\0';
    if(carry){
        C[alen] = carry + '0';
        C[alen+1] = '\0';
    }
    strrev(C);

    return C;
}
#define MAXLEN 500 /// If increased we get overflow

char* MULKaratsuba(char *a, char *b){
    /// The number that is passed is Trimmed using trim function

    /*
        ABOUT MUL: -> It is implemented using Karastuba Algorithm
        Recursive multiplication using karatsuba
        ref :: https://en.wikipedia.org/wiki/Karatsuba_algorithm
        x = 10^n/2 * a + b
        y = 10^n/2 * c + d
        x * y = 10^n * ac + 10^(n/2) (ad+bc) + bd
        where (ad+bc) = (a+b)(c+d) - ac - bd

        Time Complexity: O(n^(log2(3)))
    */

    long long int w, hw;
    int n;
    int alen = strlen(a), blen = strlen(b), extra = 0;
    int maxlen = max(alen, blen), i, k;
    int lower_bound, upper_bound;

    if(alen==1 || blen==1){ /// This can be ye optimised here and hence less recursion and memory
        if(alen==1) return multiply(b, a[0]);
        else return multiply(a, b[0]);
    }

    char update = 'n';
    char *C = (char *)malloc(MAXLEN+5);
    char *X = (char *)malloc(maxlen+1);

    char *L = (char *)malloc(MAXLEN+5);
    char *R = (char *)malloc(MAXLEN+5);
    char *N = (char *)malloc(MAXLEN+5);

    // simple multiplicatiion without considering sign

    if(alen>blen){ // increase the size of b
        for(i = 0;i<(alen - blen);i++) X[i] = '0';
        for(i = (alen - blen),k = 0;k<blen;i++,k++) X[i] = b[k];
        X[i] = '\0';
        update = 'b';
    }
    if(blen>alen){ // increase the size of a
        for(i = 0;i<(blen - alen);i++) X[i] = '0';
        for(i = (blen - alen),k = 0;k<alen;i++,k++) X[i] = a[k];
        X[i] = '\0';
        update = 'a';
    }
    // size of a and b are equal

    if(maxlen&1) maxlen = maxlen+1, extra++;
    lower_bound = (int)floor(maxlen/2) - extra;
    upper_bound = (int)ceil(maxlen/2) - extra;


    char *A = (char *)malloc(lower_bound+2); /// As you can see below
    char *B = (char *)malloc((maxlen-upper_bound+1)+2);
    char *D = (char *)malloc((maxlen-upper_bound+1)+2);

    if(update == 'n'){ // both are of same length
        for(i = 0;i<lower_bound;i++) A[i] = a[i];
        for(i = upper_bound, k = 0;i<maxlen;i++, k++) B[k] = a[i];
        for(i = 0;i<lower_bound;i++) C[i] = b[i];
        for(i = upper_bound, k = 0;i<maxlen;i++, k++) D[k] = b[i];
    }

    if(update == 'a'){ // char *a was updated and its data was stored in X
        for(i = 0;i<lower_bound;i++) A[i] = X[i];
        for(i = upper_bound, k = 0;i<maxlen;i++, k++) B[k] = X[i];
        for(i = 0;i<lower_bound;i++) C[i] = b[i];
        for(i = upper_bound, k = 0;i<maxlen;i++, k++) D[k] = b[i];
    }
    if (update=='b'){ // char *b was updated and its data was stored in X
        for(i = 0;i<lower_bound;i++) A[i] = a[i];
        for(i = upper_bound, k = 0;i<maxlen;i++, k++) B[k] = a[i];
        for(i = 0;i<lower_bound;i++) C[i] = X[i];
        for(i = upper_bound, k = 0;i<maxlen;i++, k++) D[k] = X[i];
    }

    free(X); /// Removed extra

    A[lower_bound] = '\0';
    B[k] = '\0';
    C[lower_bound] = '\0';
    D[k] = '\0';

    strcpy(L, MULKaratsuba(A, C));
    strcpy(R, MULKaratsuba(A, D));
    strcpy(N, MULKaratsuba(B, D));
    strcpy(R, add(MULKaratsuba(A, D), MULKaratsuba(B, C)));

    free(A); free(B);free(D);

    w = strlen(L), hw = strlen(R);

    for(i = w;i<=w+maxlen-1;i++) L[i] = '0'; /// Equivalent to strcpy(MUL(L, 10**n))
    L[i] = '\0';
    for(i = hw;i<=(hw + (maxlen/2) - 1);i++) R[i] = '0'; /// Equivalent to strcpy(MUL(R, 10**(n/2)))
    R[i] = '\0';

    strcpy(C, add(add(L, R), N));

    return C;
}

char *MULN2(char *a, char *b){
    /// a and b are trimmed also a>=b

    int i = 0, k = 0;
    strrev(a);

    int alen = strlen(a), dlen;
    char *C = (char *)malloc(MAXLEN+5);
    char *del = (char *)malloc(MAXLEN+5);
    char *carry = (char *)malloc(MAXLEN+5);

    carry[0] = '0'; carry[1] = '\0';
    /// each element of b with a
    for(i = 0;i<alen;i++){
        strcpy(del, multiply(b,a[i]));
        strcpy(del, add(del, carry));
        dlen = strlen(del);
        C[k++] = del[dlen-1];
        del[dlen-1] = '\0'; /// reduce length by 1
        strcpy(carry, del);
    }
    strrev(a);
    free(del);
    i = strlen(carry)-1;
    if(i+1>0) {
        while(i>=0) C[k++] = carry[i--];
    }
    free(carry);
    C[k] = '\0';
    strrev(C);
    return C;
}

char *mul(char *a, char *b){                                                    /// multiply two bigInt
    /// We have two multiplication N^2 and N^1.58 methods

    int Debug = 1;
    int asign = a[0]=='-'?-1:1,extra,i,k, bsign = b[0]=='-'?-1:1,ii ,xx = 0;
    if(asign!=bsign) xx = 1;

    char *p = (char *)malloc(strlen(a)+3);
    char *q = (char *)malloc(strlen(b)+3);
    char *C = (char *)malloc(5000);
    strcpy(p, trimSign(a));
    strcpy(q, trimSign(b));

    if(Debug){
        if(cmp(a,b)>=0) eq(C, MULN2(p,q)); /// p>=q
        else eq(C, MULN2(q,p));
    }
    else strcpy(C, MULKaratsuba(p,q));

    free(q);
    k = strlen(C);

    if(xx==1) p[0] = '-';
    i =0;
    while(C[i]=='0') i++;

    for(ii = i, extra = xx;ii<k;ii++,extra++) p[extra] = C[ii];
    if(i==k) p[0] ='0', extra = 1;
    p[extra] = '\0';

    return p;
}

char *MOD(char *a, char *b){                                                /// remainder when two bigInt are divided
    int i;
    int alen = strlen(a);
    char *v = (char *)malloc(alen+5);
    char *A = (char *)malloc(alen+5);
    long long int ans = 0;
    int flag = 0;
    if(b[0]=='-' && a[0]=='-'){
        flag = 1;
        strcpy(A, trimSign(a));
        strcpy(b, trimSign(b));
    }
    else if(b[0] == '-'){
        int a_size = alen;
        strcpy(A, a);
        strrev(A);
        A[a_size++] = '-';
        A[a_size] = '\0';
        strrev(A);
        strcpy(b, trimSign(b));
        flag = 1;
	 }
	 else
        strcpy(A, a);
	 long long int mod = atoi(b);
	 /// negative mod
	if(A[0]=='-'){

            for(i=1; A[i]!='\0'; i++)
                    ans = (ans * 10 + (A[i] - '0')) % mod;  ///mod of any number can not be negative

            if(ans>0)
                ans = mod - ans;
        }
    /// positive mod
	else{
            if(A[0]=='+'){
                for(i=1;A[i]!='\0';i++)
                    ans = (ans * 10 + (A[i] - '0')) % mod;
            }

            else{
                for(i=0;A[i]!='\0';i++)
                    ans = (ans * 10 + (A[i] - '0')) % mod;
                }

    }
	long long int  temp = ans;
	int k = 0;
    v[k++] = (temp % 10) + '0';
    ans /= 10;

	while(ans > 0){
            temp = ans;
            v[k++] = (temp % 10) + '0';
            ans /= 10;
	}
	if(flag)
        v[k++] = '-';
	v[k] = '\0';
	strrev(v);

	return trim(v);
}
char *div(char *dividend, long long divisor){
    int i,j;
    int len = strlen(dividend);
    char *quotient = (char *)malloc(len+5);
    long temp=0;
    if(dividend[0] == '-' && divisor > 0)
        i = 1,j = 0, quotient[j++] = '-';
    else if(dividend[0] == '-' && divisor < 0)
        i = 1,j = 0, divisor = abs(divisor);
    else if(divisor < 0)
        i = 0, j = 0, quotient[j++] = '-', divisor = abs(divisor);
    else
        i = 0, j = 0;

    while(dividend[i]){
            temp = temp*10 + (dividend[i] -48);
            if(temp<divisor){
                    quotient[j++] = 48;
            }
         else{
             quotient[j++] = (temp / divisor) + 48;;
             temp = temp % divisor;

         }
         i++;
    }

    quotient[j] = '\0';
    return quotient;
}

