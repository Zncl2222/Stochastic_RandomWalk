################# Random Walk (1D or 2D) ########################################################
#
#---------------------------------------------------
#                     Functions
#---------------------------------------------------
#    Probility: Draw number to decide +1 or -1.
#               Probility is 50% for each number.
#
#    Walk     : Random walk main function.
#
#    Plot     : Plot the results.
#
#    Save     : Save all realazations as txt file
#
#    trend    : Linear trend (only for 1D now)
#
#--------------------------------------------------
#                     Parameters
#--------------------------------------------------
#    steps : int
#            Number of walks
#
#    nR    : int
#            Number of realizations
#
#    seed  : int
#            initial random seed number
#
#    y     : float
#            Distance for each steps
#
#    dim   : int
#            Dimension 
#
#    tr    : array [data, slop, constant(shiffiting)]
#
#--------------------------------------------------------------------------------------------
# Notice:
#
# 2D RandomWalk in class "RandomWalk" only walk in x and y two direction.
# 
# If you want to walk in 360 degress direction, please use "RandomWalk2D_omnidirection"
#
###########################################################################################

import numpy as np
import matplotlib.pyplot as plt
import math
import os
import sys

class RandomWalk():
    
    def __init__(self,steps,nR,seed,y,tr=[False,0,0],dim=1):
        self.steps=steps
        self.nR=nR
        self.y=y
        self.seed=seed
        self.dim=dim
        self.tr=tr
        self.__Rx=0
        self.__Ry=0
        
    def Probability(self):
        
        if self.dim==1:
            np.random.seed(self.seed)
            r=np.random.randint(0,2,1)
            return r
        
        elif self.dim==2:
            np.random.seed(self.seed)
            r=np.random.randint(0,4,1)
            return r
        
    
    def Walk(self):
        
        if self.dim==1:   
            Z=np.zeros((self.steps,self.nR))
            for i in range(self.nR): 
                start=0
                for j in range(self.steps):

                    Draw=RandomWalk.Probability(self)

                    if Draw==0:
                        start+=self.y
                    elif Draw==1:
                        start-=self.y
                    self.seed+=1

                    Z[j,i]=start
                    
            if self.tr[0]==True:
                
                Z=RandomWalk.trend(self,Z)
                
            self.__Ry=Z
            
            return Z
        
        elif self.dim==2:
            
            Z=np.zeros((2,self.steps,self.nR))
            
            for i in range(self.nR):
                
                start=np.array([0,0])
                
                for j in range(self.steps):

                    Draw=RandomWalk.Probability(self)

                    if Draw==0:
                        start[0]=start[0]+self.y
                    elif Draw==1:
                        start[1]=start[1]+self.y
                    elif Draw==2:
                        start[0]=start[0]-self.y
                    elif Draw==3:
                        start[1]=start[1]-self.y
                    
                    self.seed+=1
                    Z[0][j,i]=start[0]
                    Z[1][j,i]=start[1]

        self.__Rx=Z[0]
        self.__Ry=Z[1]
        
        return Z
    
    def trend(self,x):
        
        y=np.linspace(0,self.steps,self.steps*1)*self.tr[1]
        
        z=x+self.tr[2]
        
        for i in range(1,self.steps):
            z[i]=z[i]+y[i]
            
        return z
        
        
    def Plot(self):
        
        if self.dim==1:
            
            x=np.linspace(0,self.steps,self.steps)
            
            for i in range(self.nR):
                plt.plot(x,self.__Ry[:,i])
            plt.title("Random walk (1D), nR="+str(self.nR),fontsize="28")
            plt.ylabel("Y", fontsize="28")
            plt.xlabel("Steps",fontsize="28")

                
        elif self.dim==2:
            
            for i in range(self.nR):
                plt.plot(self.__Rx[:,i],self.__Ry[:,i])
            plt.title("Random walk (2D), nR="+str(self.nR),fontsize="28")
            plt.ylabel("Y", fontsize="28")
            plt.xlabel("X",fontsize="28")

#########################################################            
#--------------------------------------------------
#                     Parameters
#--------------------------------------------------
#
#      path  : Folder path for saving the txt file
#
########################################################

    def Save(self,path):
        
        if self.dim==1:
            try:
                os.mkdir(path+'RandomWalk_Realizations1D')
            except OSError:
                print('Warning: folder has already exist')
                print('\nAre you sure want to operate. This may overwrite exist data (y/n)')
                a=input()
                if a=='y':
                    print('Operating')
                elif a=='n':
                    sys.exit()
                else:
                    sys.exit()
                
            
            for i in range(self.nR):
                 
                if i<10:
                    number='000'+str(i)
                elif 10<=i<100:
                    number='00'+str(i)
                elif 100<=i<1000:
                    number='0'+str(i)
                elif i>=1000:
                    number=str(i)
                
                np.savetxt(path+'RandomWalk_Realizations1D\\R'+number+'.txt',self.__Ry[:,i])
            
        elif self.dim==2:
            
            try:
                os.mkdir(path+'RandomWalk_Realizations2D')
            except OSError:
                print('Warning: folder has already exist')
                print('\nAre you sure want to operate. This may overwrite exist data (y/n)')
                a=input()
                if a=='y':
                    print('Operating')
                elif a=='n':
                    sys.exit()
                else:
                    sys.exit()
                
                
            Z=np.hstack([self.__Rx,self.__Ry])

            for i in range(self.nR):
                
                if i<10:
                    number='000'+str(i)
                elif 10<=i<100:
                    number='00'+str(i)
                elif 100<=i<1000:
                    number='0'+str(i)
                elif i>=1000:
                    number=str(i)
                
                Z=np.vstack([self.__Rx[:,i],self.__Ry[:,i]]).T
                
                np.savetxt(path+'RandomWalk_Realizations2D\\R'+number+'.txt',Z,fmt='%.4f')
                
                
################# Random Walk (2D with 360 directions) #####################################################
#
#---------------------------------------------------
#                     Functions
#---------------------------------------------------
#    Probility: Draw number to decide +1 or -1.
#               Probility is 50% for each number.
#
#    Walk     : Random walk main function.
#
#    Plot     : Plot the results.
#
#--------------------------------------------------
#                     Parameters
#--------------------------------------------------
#    steps : int
#            Number of walks
#
#    nR    : int
#            Number of realizations
#
#    seed  : int
#            initial random seed number
#
#    y     : int
#            Distance for each steps
#
#----------------------------------------------------
# Notice: 
#
# This propgram will walk in 360 directions
#
###########################################################################################       

class RandomWalk2D_omnidirection():
    
    def __init__(self,steps,nR,seed,y):
        self.steps=steps
        self.nR=nR
        self.seed=seed
        self.y=y
        self.__Rx=0
        self.__Ry=0
        self.__scale=10
        
    def Probability(self):
        return np.random.randint(0,360,1)
    
    def Walk(self):

        Z=np.zeros((2,self.steps,self.nR))
        
        for i in range(self.nR):
            start=np.array([0,0])
            for j in range(self.steps):
        
                Draw=RandomWalk2D_omnidirection.Probability(self)

                start[0]=start[0]+self.__scale*math.cos(Draw/180*np.pi)
                start[1]=start[1]+self.__scale*math.sin(Draw/180*np.pi)
                
                
                Z[0][j,i]=start[0]
                Z[1][j,i]=start[1]
    
        self.__Rx=Z[0]/self.__scale*self.y
        self.__Ry=Z[1]/self.__scale*self.y
        
        return Z/self.__scale*self.y
    
    def Plot(self):
        
        for i in range(self.nR):
            plt.plot(self.__Rx[:,i],self.__Ry[:,i])
        plt.title("Random walk (2D), nR="+str(self.nR),fontsize="28")
        plt.ylabel("Y", fontsize="28")
        plt.xlabel("X",fontsize="28")


#########################################################            
#--------------------------------------------------
#                     Parameters
#--------------------------------------------------
#
#      path  : Folder path for saving the txt file
#
########################################################
    
    def Save(self,path):
        
        try:
            os.mkdir(path+'RandomWalk_Realizations2D_Omni')
        except OSError:
            print('Warning: folder has already exist')
            print('\nAre you sure want to operate. This may overwrite exist data (y/n)')
            a=input()
            if a=='y':
                print('Operating')
            elif a=='n':
                sys.exit()
            else:
                sys.exit()
                
        Z=np.hstack([self.__Rx,self.__Ry])

        for i in range(self.nR):
                
            if i<10:
                number='000'+str(i)
            elif 10<=i<100:
                number='00'+str(i)
            elif 100<=i<1000:
                number='0'+str(i)
            elif i>=1000:
                number=str(i)
                
            Z=np.vstack([self.__Rx[:,i],self.__Ry[:,i]]).T
                
            np.savetxt(path+'RandomWalk_Realizations2D_Omni\\R'+number+'.txt',Z,fmt='%.4f')      