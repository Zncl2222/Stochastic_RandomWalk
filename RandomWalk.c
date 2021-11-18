# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<string.h>
# include<math.h>
# define pi 3.14159265

// Global Parameters
int Steps=1000;
int nRealizations=1;
int Dimension=2;
char number1[5];
char fhead[]="walk";
char ftail[]=".dat";
char path[]="C:\\Users\\3002shinning\\Documents\\GitHub\\Stochastic_Random_Tools\\Realizations_C\\";
char Trend='n';
int step_size=1;
float slope1;
float shifty;


clock_t __cdecl clock(void);

FILE *output;


int OneDim(int step,int nR)
{

    clock_t start, end;  
    double totaltime;
    char fullname[strlen(path)+strlen(ftail)+strlen(fhead)+strlen(number1)];
    float **x_grid = NULL;
    float *trend=NULL;

    x_grid=(float**)malloc(step*sizeof(float*));

    for(int i=0;i<step;i++)
    {
        x_grid[i]=(float*)malloc(nR*sizeof(float));
    }

    trend=(float*)malloc(step*sizeof(float));


    start=clock();
 
    
    // main loop
    for (int i=0; i<nR;i++)
    {   
        
        sprintf(number1,"%d", i);

        memset(fullname,'\0',strlen(path)+strlen(ftail)+strlen(fhead)+strlen(number1));
        strcat(fullname,path);
        strcat(fullname,fhead);
        strcat(fullname,number1);
        strcat(fullname,ftail);

        output= fopen (fullname, "w");


        if (Trend=='y')
        {
            
            for (int i=0;i<step;i++)
            {
                trend[i]=i*slope1+shifty;
            }

        }


        int start_x=0;
        
        for (int j=0; j<step; j++)
        {
            int r=2*rand()/RAND_MAX+0;
            
            if (r==0)
            {
                start_x+=step_size;
            }
            else if (r==1)
            { 
                start_x-=step_size; 
            }


            if (Trend=='y')
            {
                x_grid[j][i]=x_grid[j][i]+trend[j];  
            }
            else
            {
                x_grid[j][i]=start_x;
            }

            fprintf(output,"%d\t%.3f\n", j, x_grid[j][i]);
        }

    
        fclose (output);

    }

    for (int i=0;i<step;i++)
    {
        free(x_grid[i]);
    }

    free(x_grid);

    end=clock();
    totaltime=(double)(end-start)*1e-3;
    printf("1D case finised\n");
    printf("Time:%.4fs\n",totaltime);
    

    return 0;
    

}


int TwoDim(int step,int nR)
{
    clock_t start, end;  
    double totaltime;
    char fullname[strlen(path)+strlen(ftail)+strlen(fhead)+strlen(number1)];
    float **x_grid = NULL;
    float **y_grid = NULL;

    x_grid=(float**)malloc(step*sizeof(float*));

    for(int i=0;i<step;i++)
    {
        x_grid[i]=(float*)malloc(nR*sizeof(float));
    }

    y_grid=(float**)malloc(step*sizeof(float*));

    for(int i=0;i<step;i++)
    {
        y_grid[i]=(float*)malloc(nR*sizeof(float));
    }


    start=clock();
 

    // main loop
    for (int i=0; i<nR;i++)
    {   
        sprintf(number1,"%d", i);

        memset(fullname,'\0',strlen(path)+strlen(ftail)+strlen(fhead)+strlen(number1));
        strcat(fullname,path);
        strcat(fullname,fhead);
        strcat(fullname,number1);
        strcat(fullname,ftail);

        output= fopen (fullname, "w");

        int start_x=0;
        int start_y=0;
        
        for (int j=0; j<step; j++)
        {
            int r=4*rand()/RAND_MAX+0;
            
            if (r==0)
            {
                start_x+=step_size;
            }
            else if (r==1)
            { 
                start_x-=step_size; 
            }
            else if (r==2)
            {
                start_y+=step_size;
            }
            else if (r==3)
            {
                start_y-=step_size;
            }
            
            
            x_grid[j][i]=start_x;
            y_grid[j][i]=start_y;
            

            fprintf(output,"%d\t%d\t%d\n", j, x_grid[j][i],y_grid[j][i]);
        }
     
    
        fclose (output);

    }

    end=clock();
    totaltime=(double)(end-start)*1e-3;
    printf("2D case finised\n");
    printf("Time:%.4fs\n",totaltime);

    return 0;

}



int TwoDim_Omni(int step,int nR)
{
    clock_t start, end;  
    double totaltime;
    char fullname[strlen(path)+strlen(ftail)+strlen(fhead)+strlen(number1)];
    float **x_grid = NULL;
    float **y_grid = NULL;

    x_grid=(float**)malloc(step*sizeof(float*));

    for(int i=0;i<step;i++)
    {
        x_grid[i]=(float*)malloc(nR*sizeof(float));
    }

    y_grid=(float**)malloc(step*sizeof(float*));

    for(int i=0;i<step;i++)
    {
        y_grid[i]=(float*)malloc(nR*sizeof(float));
    }


    start=clock();
 

    // main loop
    for (int i=0; i<nR;i++)
    {   
        sprintf(number1,"%d", i);

        memset(fullname,'\0',strlen(path)+strlen(ftail)+strlen(fhead)+strlen(number1));
        strcat(fullname,path);
        strcat(fullname,fhead);
        strcat(fullname,number1);
        strcat(fullname,ftail);

        output= fopen (fullname, "w");

        float start_x=0;
        float start_y=0;
        int scale=10;
        
        double val = pi/180;


        for (int j=0; j<step; j++)
        {
            int r=360*rand()/RAND_MAX+0;

            start_x=start_x+scale*cos(r*val);
            start_y=start_y+scale*sin(r*val);
  
            x_grid[j][i]=start_x/scale*step_size;
            y_grid[j][i]=start_y/scale*step_size;
            

            fprintf(output,"%d\t%.3f\t%.3f\n", j, x_grid[j][i],y_grid[j][i]);
        }
     
        
        fclose (output);

    }

    end=clock();
    totaltime=(double)(end-start)*1e-3;
    printf("2D_Omni case finised\n");
    printf("Time:%.4fs\n",totaltime);

    return 0;

}


int main(void)
{
    int Dimension;
    char c;
    int Omni;

    printf("How many steps you want to walk? (Please input interger)\n");
    scanf("%d",&Steps);

    printf("How many realizations you want to simulate? (Please input interger)\n");
    scanf(" %d",&nRealizations);

    printf("Select Dimension (Input 1 for 1D, 2 for 2D)\n");
    scanf(" %d",&Dimension);

    printf("Adding Trend?(y/n) (Now only 1D case can use this function)\n");
    scanf(" %c", &Trend);

    if (Dimension==2)
    {
        printf("\n");
        printf("Omnidirection? (y/n)\n");
        scanf(" %c",&c);

        if (c=='n') Omni=0;
        else if (c=='y') Omni=1;
        else Omni=123;
    }

    if (Dimension==1)
    {

        if (Trend=='y')
        {
            printf("Input a value for linear slop. (Float)\n");
            scanf(" %f",&slope1);
            printf("Input a value for shifting. (Float)\n");
            scanf(" %f", &shifty);
        }


        OneDim(Steps,nRealizations);
    }

    

    else if (Dimension==2)
    {
        
        if (Omni==0)
        {
            TwoDim(Steps,nRealizations);
        }

        else if (Omni==1)
        {
            TwoDim_Omni(Steps,nRealizations);
        }

        else {printf("Invalid Input. Program will shut down!"); exit(0);}
    }

    else {printf("Invalid Input. Program will shut down!"); exit(0);}

   system("PAUSE");
   return 0;
}