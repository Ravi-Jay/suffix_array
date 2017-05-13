#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*

    This is about the Multiplication algorithm to realize the suffix array.

    maybe this realization is complicated and a little difficult to understand,

    but I will try my best to explain and add annotations as many as possible

    I sincerely hope that can help us to understand it.

    Let's begin now!

*/

const int N = 1000, M = 256;
char s[N];
int sa[N], t[N], t2[N], c[M], n;
int rank[N];

/*
    N is max length of the string we deal with.
    M is the max scale of the chars. Here, we suppose all characters in the program is in ASC table.

    sa: it is the array of ranking. its subscript is the rank number and the content is the subscript of the string we deal with
        eg, s="aba"  suffixes: "aba" "ba" "a"; 'a'<'aba' < 'ba', so sa[1]=2 , subscript 2 represents 'a' and sa[2]=0 ,representing 'aba', sa[3]=1 ('ba')
            and rank[0]=2,rank[1]=3,rank[2]=1; rank is converse.

    t and t2 is temporary array.
    n = the length of s + 1
*/


bool cmp(int *y, int i, int k)// based on the current rank, compare if this part is same as the last one. if so, ranking doesn't end.
{
    return y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k];// base on two keys
}

void build(int m)// m is the max scale of s
{
    int i, *x = t, *y = t2;

    /*
        x is the first key for ranking.
            its subscript is correspond to that of s and its content is the rank

        y is the second key for ranking.
            its subscript is rank and its content is the subscript of s.
    */


    for(i = 0; i < m; i++)
        c[i] = 0;
    for(i = 0; i < n; i++)
    {
        c[x[i] = s[i]]++;
    }
    for(i = 1; i < m; i++)
    {
        c[i] += c[i-1];
    }

/*
    radix sorting
        c is the bucket
        it is the first ranking according to one digit.
*/

    for(i = n-1; i >= 0; i--)
        sa[--c[x[i]]] = i;

    printf("first ranking : sa ");
    for( i=0;i<n;i++)
        printf(" %d ",sa[i]);
    printf("\n\n");

    for(int k = 1, p; k <= n; k<<=1, m=p) {
        p = 0;

        //y: subscript is the rank of second key, calculated by sa

        for(i = n-k; i < n; i++)
            y[p++] = i;      // some digit in the tail of s , they don't have the second key, so their second keys rank forward
        for(i = 0; i < n; i++)// choose the second keys and move them in y
            if(sa[i] >= k)
                y[p++] = sa[i] - k; // minus k. because the second has a distance of k to location of the first key

        printf("k:%d\n",k);
        printf("x[]:");
        for( i=0;i<n;i++)
            printf(" %d ",x[i]);
        printf("\n");
        printf("y[]:");
        for( i=0;i<n;i++)
            printf(" %d ",y[i]);
        printf("\n");


        //x : its content is the rank of every char.
        // we sort them by x and y
        // add them into the bucket in the order of y and then take them out one by one
        // this realize the ranking according to the two keys
        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[y[i]]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];

        printf("sa[]:");
        for(i=0;i<n;i++)
            printf(" %d ",sa[i]);
        printf("\n");



        // y points to the array of x and then update x
        swap(x, y);
        p = 1; x[sa[0]] = 0;//sa[0]is the char '0' we add previously and it is always the first one
        for(i = 1; i < n; i++) {
            x[sa[i]] = cmp(y, i, k) ? p-1 : p++;//if this one is same to the last one, it tells us ranking must continue.
                                                // because the ranks of two suffix at least can not be decided
        }
        // p>=n indicates the ranking is done and everyone has a different rank
        if(p >= n) break;
    }
}

void get_rank()
{
    int k = 0;
    for(int i = 0; i < n; i++) rank[sa[i]] = i;
}

int main()
{
//    scanf("%s", s);
    strcpy(s, "abaab");
    n = strlen(s) + 1;
    int maxi = 0;
    for(int i = 0; i < n; i++) {
        maxi = maxi > s[i] ? maxi : s[i];
    }
    s[n-1] = 0;
    build(maxi+1);
    get_rank();

    printf("The rank is:\n");
    printf("%d", rank[0]);
    for(int i = 1; i < n-1; i++) printf(" %d", rank[i]);
    puts("");

    return 0;
}
