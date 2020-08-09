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
double ReP[152][202];
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
double norm =655012; 

TH2D* HI1=new TH2D("HI1","  ",72,-0.5,71.5,72,-0.5,71.5);
TH2D* HIL=new TH2D("HIL","  ",152,-0.5,151.5,202,-0.5,201.5);
TH1F* HI2=new TH1F("HI2","  ",100,0,100);
TH1F* h1m=new TH1F("h1m","  ",150,0.5,150.5);
TH1F* h2m=new TH1F("h2m","  ",200,-0.5,201.5);


//****************************** masse transverse *********************************************

			 ifstream monFlux("Migration.txt");  //Ouverture d'un fichier en lecture
			 if(monFlux)
       			 {
        		 double nombr;
                		for( int i=0; i < 5184 ; i++){
				monFlux >> nombr; //Lit un nombre ?|  virgule depuis le fichier 
				y[i]=nombr; 
				sum=sum+y[i];
				}}

		cout<<sum<<endl;								
		// La matrice de Migration *********************************************************************
		int i = 0;                     
		for(int j=0; j <= 71 ; j++){
                for(int k=0; k <= 71 ; k++){	
		Mig[j][k]=y[i];
		i=i+1;		
	        HI1->Fill(j,k,Mig[j][k]);
		}}

		cout<<sum<<endl;


		//--------------Calcule direct-------------

                for(int k = 0; k <= 71 ; k++){
	        for (int j = 0; j <= 71; j++){
		VEC[k]=Mig[j][k]+VEC[k];}
		//cout<<"VEC["<<k<<"]="<<VEC[k]<<endl;}
                }
              
	        for (int j = 0; j <= 71; j++){
                for(int k = 0; k <= 71 ; k++){
                if(VEC[k]!=0) {REP[j][k]=Mig[j][k]/VEC[k];
/*		std::ofstream fichierzq("Response.txt",ios::app);
                                                if( fichierzq.is_open() )
                                                {
                                                fichierzq <<REP[j][k]<< std::endl;
                                                }
                fichierzq.close();
*/
		}}}
		
//		for(int k=0; k<=201; k++){
//		cout<<"REP["<<2<<"]["<<k<<"]="<<REP[2][k]<<endl;                  
//		}


                for(int j=0 ; j <= 71 ; j++){
                for(int k=0 ; k <= 71 ; k++){
                nrvb[j]=nrvb[j]+Mig[j][k];}
		cout<<nrvb[j]<<endl;
		h1m->SetBinContent(j,nrvb[j]);
		
		std::ofstream fichierz("DataReco.txt",ios::app);
                                                if( fichierz.is_open() )
                                                {
                                                fichierz <<nrvb[j]<< std::endl;
                      		                }
              
	        fichierz.close();
		
		}



                for(int k=0 ; k <= 71 ; k++){
                for(int j=0 ; j <= 71 ; j++){
                ntvb[k]=ntvb[k]+Mig[j][k];}
		cout<<ntvb[k]<<endl;
		h2m->SetBinContent(k,ntvb[k]);
		
		std::ofstream fichierza("DataTrue.txt",ios::app);
                                                if( fichierza.is_open() )
                                                {
                                                fichierza <<ntvb[k]<< std::endl;
                                                }
                fichierza.close();
		
		}
	

                for(int j=0 ; j <= 71 ; j++){
                for(int k=0 ; k <= 71 ; k++){
                esr[j]=REP[j][k]*ntvb[k]+esr[j];}
		}
						
                for(int j=0 ; j<=71 ; j++){
		cout<<"reco["<<j<<"]="<<esr[j]<<"  calculé directemnt = " <<nrvb[j] <<endl;}
		







//HI1->Draw("Colz");
//HIL->Draw("Colz");
//HIL->Draw("colz");

HI1->Draw("colz");
//h2m->Draw();
//h1m->Draw("same");
return 0;


}


