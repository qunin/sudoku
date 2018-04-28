#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include<string.h> 
using namespace std;
int sdk[9][9];
bool valid(int sudoku[][9],int m,int n)
{
	int tmp=sudoku[m][n];
	int i,j;
	for(i=0;i<9;i++)
	{
		if (i!= m&&sudoku[i][n]==tmp)
			return false;
	}
	for (j=0;j<9;j++)
	{
		if (j!=n&&sudoku[m][j]==tmp)
			return false;
	}
	for (i=m/3*3; i<m/3*3+3; i++)
	{
		for (j=n/3*3;j<n/3*3+3; j++)
		{
			if((i!=m||j!=n)&&sudoku[i][j]==tmp)
				return false;
		}
	}
	return true;
}
//构造数组并输出 
void create_sudoku(int sudoku[][9])
{
	int i,j;
	int k=1;
	while(1)
	{
		i=k/9;
		j=k%9;
		while(1)
		{
			sudoku[i][j]++;
			if (sudoku[i][j]==10)
			{
				sudoku[i][j]=0;
				if(k>1)k--;
				break;
			}
			else if(valid(sudoku,i,j))
			{
				k++;
				break;
			}
		}
		if (k==81)
		{
			for(i=0;i<9;i++)
			{
				for(j=0;j<9;j++)
					cout<<sudoku[i][j]<<' ';
				cout<<endl;
			}
			break;
		}
	}
}
int Num(char str[])
{
	int i,num=0,len=0;
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(isdigit(str[i])==0)
		return -2;
		else continue ;//-2表示非数字 
	}
	if(len>8)
	return -1;//-1表示数字太大 
	for(i=0;i<len;i++)
	{
		num=num*10+(str[i]-'0');
	}
	return num;
}
bool Judge1(int x, int y, int n)  
{  
    int i;  
    for(i=0;i<9;i++)  
    {  
        //判断 列  
        if((sdk[i][y]==n) && (i!=x))  
            return false;  
        //判断 行  
        if((sdk[x][i]==n) && (i!=y))  
            return false;  
    }  
   
    return true;  
}  
   
//判断填在空白位置的数字在九宫格之内是否符合要求  
bool Judge2(int x, int y, int n)  
{  
    int xx,yy,i,j;  
    xx=x/3;  
    yy=y/3;  
    for(i=xx*3;i<xx*3+3;i++)  
        for(j=yy*3;j<yy*3+3;j++)  
            if(sdk[i][j]==n)  
                if(i==x && j==y)  
                    continue;  
                else  
                    return false;  
    return true;  
}  
   
//填充空白数组  
bool Fill(int m)  
{  
    int n,x,y;  
    x=m/9;  
    y=m%9;  
    if (m>=81)  
        return true;  
    if (sdk[x][y]==0)  
    {  
        for(n=1;n<=9;n++)  
        {  
            sdk[x][y]=n;  
            if(Judge1(x,y,n)&&Judge2(x,y,n))  
                if(Fill(m+1))  
                    return true;  
            sdk[x][y]=0;  
   
        }  
    }  
    else  
        return Fill(m+1);  
   
    return false;  
}  
   
int Solve(FILE *fp)//fp读入的txt 
{
	int i,j,k;
	int imp;
	FILE *output;
	output=fopen("sudoku.txt","w");//文件名改 
	while(fscanf(fp,"%d",&imp)!=EOF)
	{
		sdk[0][0]=imp;
		for(j=1;j<9;j++)
		fscanf(fp,"%d",&sdk[0][j]);
		for(i=1;i<9;i++)
		{
			for(j=0;j<9;j++)
			fscanf(fp,"%d",&sdk[i][j]);
		} 
        if(Fill(0))  
        {  
            for(i=0;i<9;i++)  
            {  
                for(j=0;j<9;j++)  
                    fprintf(output,"%d ",sdk[i][j]);
				fprintf(output,"\n"); 
            }  
            fprintf(output,"\n");
        } 
		
		
	}
	fclose(fp);
		fclose(output);
	return 0;
} 
int main(int argc, char *argv[])
{
	if(strcmp("-c",argv[1])==0)
	{
		int num=Num(argv[2]);
		{
			if(num==-2)
			{
				printf("\nInput is non-numeric!\n");
			}
			else if(num==-1)
			{
				printf("\nInput is too large!\n");
			}
			else
			 {
				freopen("sudoku.txt","w",stdout);
	            int i, t;
	            int sudoku[9][9]={0};
	            sudoku[0][0]=6;
	            srand((unsigned)time(0));
	            for(i=1;i<=9;i++)
	            {
		            t=rand()%81;
		            if(t==0)
		       {
			         ++t;
		        }
		        sudoku[t/9][t%9]=i;
	          }
	         for(i=0;i<num;i++)
	         {
		         create_sudoku(sudoku);
		          printf("\n");
	}
			}
		}
		return 0; 
	}
	else if(strcmp("-s",argv[1])==0)
	{
		FILE *fp;
		fp=fopen(argv[2],"r");
		if(fp==NULL)
		printf("\nFail to open file!\n");
		else Solve(fp);
	}
	else printf("\n Input Error\n");
	return 0;
} 
