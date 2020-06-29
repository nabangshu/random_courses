#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<time.h>
int mai[10000],a[5000],b[5000], c[10000];
int num=0,left,right,j=0;
char buffer[1000000];
void merge(int arr[], int l, int m, int r)
{
    int i, j2, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j2 = 0; j2 < n2; j2++)
        R[j2] = arr[m + 1+ j2];
    i = 0;
    j2 = 0;
    k = l;
    while (i < n1 && j2 < n2)
    {
        if (L[i] <= R[j2])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j2];
            j2++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j2 < n2)
    {
        arr[k] = R[j2];
        j2++;
        k++;
    }
}
 
 void mergeSort(int arr[], int l, int r)
{
   if (l < r)
   {
      int m = l+(r-l)/2; 
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
   }
}

void *sort0(void *argp)
{
   mergeSort(a,0,left-1);
   return NULL;
}

void *sort1(void *argp)
	{
		mergeSort(b,0,j-1);
		return NULL;
	}
void *merge_sorted(void *argp)
	{
		int i=0,j2=0,k=0;
		while (i<left && j2 <j)
    	{
        	if (a[i] < b[j2])
            	c[k++] = a[i++];
        	else
            	c[k++] = b[j2++];
    	}
    	while (i < left)
        	c[k++] = a[i++];
    	while (j2 < j)
        	c[k++] = b[j2++];
        return NULL;
	}
int main(int argc, char *argv[])
{
	clock_t start,end;
	double tem;
	double time_used;
	FILE *fptr, *fptr2;
	int i;
	char *pch;
	fptr = fopen(argv[1], "r");
	fptr2= fopen(argv[2], "a");
	int flag1,flag2;
	pthread_t tid1,tid2,tid3;
	start=clock();
	while (EOF != fscanf(fptr, "%[^\n]\n", buffer))
		{
			pch=strtok(buffer," ");
			while (pch != NULL)
  				{
    				mai[num++]=(int)atoi(pch);
					pch = strtok (NULL, " ");
  				}
  	left=((num%2)==0)?(num/2):((num+1)/2);
  	right=left;
  	for (i=0;i<left;++i)
			a[i]=mai[i];
	
	for(i=right;i<num;++i)
			b[j++]=mai[i]; 
    
    	pthread_create(&tid1, NULL, sort0, NULL);
    	pthread_create(&tid2, NULL, sort1, NULL);
    
   		pthread_join(tid1,NULL);
    	pthread_join(tid2,NULL);
  		pthread_create(&tid3, NULL, merge_sorted, NULL);
    	pthread_join(tid3,NULL);	
   //int i;
    	for(i=0;i<num;++i)
    		fprintf(fptr2,"%d ",c[i]);
    	fprintf(fptr2,"\n");
  		num=0;j=0;
	}
	end=clock();
    fclose(fptr);
    fclose(fptr2);
    time_used =printf( "Time used:\n%f",(((double) (end - start)) / CLOCKS_PER_SEC));
    return 0;
}
