#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_t tid[100];	//global

struct data{
int x_1;
int y_1;
int x_2;
int y_2;
int a[10][10];		//I set the max matrix nxm = 10x10
int b[10][10];		//because I set the max number of thread = 100
int row;
int col;
FILE *f;
};

//int mult(int x1,int y1,int x2,int y2,int a[][y1],int b[][y2], int m,int n)
void *mult(void *aa)
{
struct data *tt = (struct data *) aa;
int i,j;
int tmp = 0;

//for(i = 0;i < x2;i++)
	//tmp = tmp + a[m][i] * b[i][n];

for(i = 0;i < ((*tt).x_2);i++)
	tmp = tmp + ((*tt).a[(*tt).row][i]) * ((*tt).b[i][(*tt).col]);

fprintf((*tt).f,"%d ",tmp);

pthread_exit(NULL);		//end the thread
}

int main()
{
printf("please enter the name of input file:");
char filename[20];
scanf("%s",filename);

FILE *fin = fopen(filename,"r");
struct data *save;
save = malloc(sizeof(struct data));

int x1,y1,x2,y2;
fscanf(fin,"%d %d",&x1,&y1);
(*save).x_1 = x1;
(*save).y_1 = y1;

int i,j;

for(j = 0;j < x1;j++)
	for(i = 0;i < y1;i++)
		fscanf(fin,"%d",&((*save).a[j][i]));


fscanf(fin,"%d %d",&x2,&y2);
(*save).x_2 = x2;
(*save).y_2 = y2;

for(j = 0;j < x2;j++)
	for(i = 0;i < y2;i++)
		fscanf(fin,"%d",&((*save).b[j][i]));

//pthread_attr_t attr[100];
int temp = 0;

//void qq;

printf("please the output filename:");
char output[20];
scanf("%s",output);

FILE *fout = fopen(output,"w");

(*save).f = fout;
fprintf(fout,"%d %d\n",x1,y2);

for(i = 0;i < x1;i++){
	for(j = 0;j < y2;j++){
		(*save).row = i;
		(*save).col = j;
		
		//pthread_attr_init(&(attr[temp]));
		pthread_create(&(tid[temp]),NULL,mult,(void *)save);
			//-->>C[i][j] = mult(x1,y1,x2,y2,matrix,matrix2,i,j);
		pthread_join(tid[temp],NULL);
			//if no pthread_join
			//slaver threads什麼也來不及作main thread就結束了
		temp ++;
		
	}
	fprintf(fout,"\n");
}


fclose(fin);
fclose(fout);

return 0;
}
