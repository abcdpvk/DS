#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n;
struct suff
{
    int index;
    char *suff;
};

struct suff *suffes;

void sort()
{
    for(int i=0; i<n-1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(strcmp(suffes[j].suff,suffes[j+1].suff) > 0)
            {
                int index;
                char *txt;

                index  = suffes[j].index;
                txt = suffes[j].suff;

                suffes[j].index = suffes[j+1].index;
                suffes[j].suff = suffes[j+1].suff;

                suffes[j+1].index = index;
                suffes[j+1].suff = txt;

            }
        }
    }
}

void suff_ARRAY(char *txt)
{
    for (int i = 0; i < n; i++)
    {
        suffes[i].index = i;
        suffes[i].suff = (txt+i);
    }
    sort();
}

void SEARCH(char *patt, char *txt)
{
    int m = strlen(patt);
    int l=0, r = n-1;

    while(l <= r)
    {
        int mid = l + (r-l) /2;
        int res = strncmp(patt,txt + suffes[mid].index,m);
        if(res == 0)
        {
            printf("\nPattern found at index: %d", suffes[mid].index);
            return;
        }
        if (res < 0)
            r = mid - 1;
        else
            l = mid + 1;

    }
   printf("\nPattern not found\n");
}
void PRINT_ARRAY()
{
    for(int i=0; i<n; i++)
    {
        printf("%s - %d\n", suffes[i].suff, suffes[i].index);
    }
}
void main()
{
    char txt[500], pattern[500];
    printf("\n\n********* Suffix ARRAYS *********\n\n");
    printf("Enter a string :: ");
    scanf ("%[^\n]%*c", txt);
    printf("Enter pattern :: ");
    scanf ("%[^\n]%*c", pattern);
    n = strlen(txt);
    suffes = (struct suff*)malloc(n*sizeof(struct suff));
    suff_ARRAY(txt);
    printf("\n\nSuffes along with indexes :: \n");
    PRINT_ARRAY();
    SEARCH(pattern, txt);
    printf("\n\n");
}
