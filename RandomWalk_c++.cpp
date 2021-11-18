# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <math.h>
# include <cmath>
# include <time.h>
# include <string.h>
# include <fstream>
# define pi 3.14159265
using namespace std;

//Gloabal Parameters
int Steps;
int nRealizations;
int dimension;
char omni;
char trend;
float slope;
float shifty;
string fhead="walk";
string ftail=".dat";
string path="C:\\Users\\3002shinning\\Documents\\GitHub\\Stochastic_Random_Tools\\Realizations_Cpp\\";

double start_time,end_time;
FILE *output;

class RandomWalk
{   
    public:
        RandomWalk(int steps, int nR, int steps_size, int dim, char Trend)
            : m_steps(steps), m_nR(nR), m_steps_size(steps_size),m_dim(dim),m_Trend(Trend){}
        int Draw();
        int Walk();

    private:
        int m_steps;
        int m_nR;
        int m_steps_size;
        int m_dim;
        char m_Trend;

};


class RandomWalk2D_Omni
{   
    public:
        RandomWalk2D_Omni(int steps, int nR, int steps_size)
            : m_steps(steps), m_nR(nR), m_steps_size(steps_size){}
        int Draw();
        int Walk();

    private:
        int m_steps;
        int m_nR;
        int m_steps_size;

};

int factorial(int x)
{   
    int temp=1;
    for(int i = 1;i<=x;i++)
    {
        temp=temp*i;
    }
    return temp;
}


float fastsin(float x)
{
    return x-pow(x,3)/factorial(3)+pow(x,5)/factorial(5)-pow(x,7)/factorial(7)+pow(x,9)/factorial(9);   
}

float fastcos(float x)
{
    return 1-pow(x,2)/factorial(2)+pow(x,4)/factorial(4)-pow(x,6)/factorial(6)+pow(x,8)/factorial(8);   
}



int RandomWalk::Draw()
{   
    int r;

    if (m_dim==1)
    {
        r=2*rand()/RAND_MAX+0;
    }

    else if(m_dim==2)
    {
        r=4*rand()/RAND_MAX+0;
    }


    return r;
};

int RandomWalk:: Walk()
{
    int x;
    float **x_grid;
    float **y_grid;
    float *tr;
    string s1;
    string filename;
    

    start_time=clock();
    
    // memory allocation
    x_grid=new float*[m_steps];

    for(int i=0;i<m_steps;i++)
    {
        x_grid[i]=new float[m_nR];
    }

    if (m_dim==2)
    {

        y_grid=new float*[m_steps];

        for (int i=0;i<m_steps;i++)
        {
            y_grid[i]=new float[m_nR];
        }
    
    }

    tr=new float[m_steps];

    if (m_Trend=='y')
    {
        for (int i=0;i<m_steps;i++)
        {
            tr[i]=i*slope+shifty;
        }
    }


    
    for (int i=0;i<m_nR;i++)
    {   
        int start_x=0;
        int start_y=0;
        string s1=to_string(i);
        
        filename=path+fhead+s1+ftail;
        
        //ofs.open(filename);
        output= fopen (filename.c_str(), "w");

        for (int j=0;j<m_steps;j++)
        {
            x=Draw();

            if (x==0)
            {
                start_x+=m_steps_size;
            }
            else if (x==1)
            {
                start_x-=m_steps_size;
            }

            else if (x==2)
            {
                start_y+=m_steps_size;
            }

            else if (x==3)
            {
                start_y-=m_steps_size;
            }

            if (m_dim==1)
            {   
                if (m_Trend=='y')
                {
                    x_grid[j][i]=start_x+tr[i];
                } 
                else 
                {
                    x_grid[j][i]=start_x;
                }
                fprintf(output,"%d\t%.3f\n", j, x_grid[j][i]);
                //ofs << j <<"  "<<x_grid[j][i]<<"\n";
            }

            else if (m_dim==2)
            {
                x_grid[j][i]=start_x;
                y_grid[j][i]=start_y;

                //ofs<< j <<"  "<<x_grid[j][i]<<"  "<<y_grid[j][i]<<"\n";
                fprintf(output,"%d\t%.3f\t%.3f\n", j, x_grid[j][i],y_grid[j][i]);
            }

        }
        //ofs.close();
        fclose (output);
    }

    //Dispose the memory

    for (int i=0; i<m_steps;i++)
    {
        delete[] x_grid[i];
    }
    delete[] x_grid;
    
    end_time=clock();


    cout<<"Time:"<<(end_time-start_time)/1000<<" s.\n";

    return 0;
}


int RandomWalk2D_Omni:: Walk()
{   
    
    int x;
    double **x_grid;
    double **y_grid;
    int scale=10;
    string filename;
    float val=pi/180;
    
    
    start_time=clock();
    
    // memory allocation
    x_grid=new double*[m_steps];
    y_grid=new double*[m_steps];

    for(int i=0;i<m_steps;i++)
    {
        x_grid[i]=new double[m_nR];
    }

    for(int i=0;i<m_steps;i++)
    {
        y_grid[i]=new double[m_nR];
    }


    // main loop
    for (int i=0;i<m_nR;i++)
    {   
        float start_x=0;
        float start_y=0;
        string s1=to_string(i);
        

        filename=path+fhead+s1+ftail;

        output= fopen (filename.c_str(), "w");
        

        for (int j=0;j<m_steps;j++)
        {
            //x=Draw();
            x=360*rand()/RAND_MAX+0;

            start_x=start_x+scale*cos(x*val);
            start_y=start_y+scale*sin(x*val);

            x_grid[j][i]=start_x/scale;
            y_grid[j][i]=start_y/scale;
            
            //ofs << j <<"  "<<x_grid[j][i]<<"  "<<y_grid[j][i]<<"\n";
            fprintf(output,"%d\t%.3f\t%.3f\n", j, x_grid[j][i],y_grid[j][i]);
        }

        //ofs.close();
        fclose (output);
    }

    //Dispose the memory

    for (int i=0; i<m_steps;i++)
    {
        delete[] x_grid[i];
    }
    delete[] x_grid;
    
    for (int i=0; i<m_steps;i++)
    {
        delete[] y_grid[i];
    }
    delete[] y_grid;
    

    end_time=clock();


    cout<<"Time:"<<(end_time-start_time)/1000<<" s.\n";

    return 0;
}


int main()
{   
 
    cout << "Please enter the dimension (1 for 1D, 2 for 2D)\n";
    cin >> dimension;

    if (dimension==2)
    {
        cout << "Omnidirection? (y/n)\n";
        cin >> omni;
    }
 
    cout << "Trend? (y/n)\n";
    cin >> trend;

    if (trend=='y')
    {
        cout<<"Enter the slope of linear trend\n";
        cin >> slope;

        cout<<"Enter the shifting of linear trend\n";
        cin >> shifty;
    }

    cout << "Please enter the number of step for walking: "<<"\n";
    cin >> Steps;

    cout << "Please enter the number or realizations: "<<"\n";
    cin >> nRealizations;


    if (omni=='y')
    {
        RandomWalk2D_Omni Case1{Steps,nRealizations,1};

        Case1.Walk();
    }
    
    else 
    {  
        RandomWalk Case1{Steps,nRealizations,1,dimension,trend};
        
        Case1.Walk();
    }



    system("pause");

    return 0;
};