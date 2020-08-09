#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <string.h>
#include <stdint.h>


using namespace std;

int  TraMW() {
double x[30704];
double y[30704];
double xl[30704];
double yl[30704];
double yx[40];
double COV[70][70];
double RePonsei[152][202];
double REP[152][202];
double REPL[102][102];
double Mig[152][202];
double Migr[152][202];
double MigL[102][102];
double VEC[202];
double VECL[102];
double nrvb[152];
double ntvb[202];
double esr[152];
double sum = 0;
double som = 0;
	
int a = 0     ;
int k = 1     ;

TH2D* HI1=new TH2D("HI1","  ",70,-0.5,69.5,70,-0.5,69.5);
TH2D* HIL=new TH2D("HIL","  ",152,-0.5,151.5,202,-0.5,201.5);
TH1F* HI2=new TH1F("HI2","  ",100,0,100);
TH1F* h1m=new TH1F("h1m","  ",150,0.5,150.5);
TH1F* h2m=new TH1F("h2m","  ",200,-0.5,201.5);


//****************************** masse transverse *********************************************


                         ifstream monFluxa("DataTrue_ap.txt");  //Ouverture d'un fichier en lecture
                         if(monFluxa)
                         {
                         double nombra;
                                for( int i=0; i < 70 ; i++){
                                monFluxa >> nombra; //Lit un nombre ?|  virgule depuis le fichier 
                                x[i]=nombra;
                                }}


		ifstream monFlu("UnfoldedCov.txt");  //Ouverture d'un fichier en lecture
    	        if(monFlu)
                {
                double_t nombr;
                for( int i=1; i <= 4900 ; i++){
                if(k > 70) k=1;
                monFlu >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                a=int(i/70)+1;
                if(k == 70){ a=a-1;}
                COV[a][k]=nombr;
                k=k+1;
                }}


		cout<<sum<<endl;								
		// La matrice de Migration *********************************************************************
		int i = 0;                     
		for(int j=1; j <= 70 ; j++){
                for(int k=1; k <= 70 ; k++){	
                cout<<"cov["<<j<<"]["<<k<<"]="<<COV[j][k]<<endl;
		HI1->Fill(j,k,COV[j][k]);
		}
		COV[j][j]=COV[j][j]+x[j];
                cout<<"cov["<<j<<"]["<<j<<"]="<<COV[j][j]<<endl;
		}


		for(int j=1 ; j <= 70 ; j++){
                for(int k=1 ; k <= 70 ; k++){

                std::ofstream fichierz("UnfoldedCov2.txt",ios::app);
                                                if( fichierz.is_open() )
                                                {
                                                fichierz <<COV[j][k]<< std::endl;
                                                }

                fichierz.close();
                }}






//HI1->Draw("Colz");
//HIL->Draw("Colz");
//HIL->Draw("colz");
HI1->SetStats(0);
HI1->Draw("colz");
HI1->GetZaxis()->SetRangeUser(-13000, 8000);
//h2m->Draw();
//h1m->Draw("same");
return 0;


}


