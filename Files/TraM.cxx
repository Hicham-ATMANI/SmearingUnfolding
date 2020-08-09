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

int  TraM() {


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
double norm = 655012;

TH2D* HI1=new TH2D("HI1","  ",152,-0.5,151.5,202,-0.5,201.5);
TH2D* HIL=new TH2D("HIL","  ",152,-0.5,151.5,202,-0.5,201.5);
TH1F* HI2=new TH1F("HI2","  ",100,0,100);
TH1F* h1m=new TH1F("h1m","  ",152,-0.5,151.5);
TH1F* h2m=new TH1F("h2m","  ",202,-0.5,201.5);


//****************************** masse transverse *********************************************

			 ifstream monFlux("Detmat.txt");  //Ouverture d'un fichier en lecture
			 if(monFlux)
       			 {
        		 double nombr;
                		for( int i=0; i < 30704 ; i++){
				monFlux >> nombr; //Lit un nombre ?|  virgule depuis le fichier 
				y[i]=nombr; }}

			 ifstream monFlu("Reponse.txt");  //Ouverture d'un fichier en lecture
			 if(monFlu)
        		 {
        		 double nombre;
                		for( int i=0; i < 30704 ; i++){
                                monFlu >> nombre; //Lit un nombre ?|  virgule depuis le fichier 
                                x[i]=nombre; }}
	
		
										
		// La matrice de Migration *********************************************************************
		int i = 0;                     
		for(int j=0; j <= 151 ; j++){
                for(int k=0; k <= 201 ; k++){	
		Mig[j][k]=y[i]/norm;
		i=i+1;								
         	HI1->Fill(j,k,Mig[j][k]);	 
		//		cout<<"Mig["<<j<<"]["<<k<<"]="<<Mig[j][k]<<endl;
	        }}





		// La matrice de Reponse *********************************************************************
 		i = 0;
                for(int j=0; j <= 151 ; j++){
                for(int k=0; k <= 201 ; k++){
                ReP[j][k]=x[i];
                i=i+1;
		//              cout<< "ReP["<<j<<"]["<<k<<"]="<<ReP[j][k]<<endl;}}
		}}				                         		


		//--------------Calcule direct-------------

                for(int k = 0; k <= 201 ; k++){
	        for (int j = 0; j <= 151; j++){
		VEC[k]=Mig[j][k]+VEC[k];}
		//cout<<"VEC["<<k<<"]="<<VEC[k]<<endl;}
                }


                               
	        for (int j = 0; j <= 151; j++){
                for(int k = 0; k <= 201 ; k++){
                if(VEC[k]!=0) {REP[j][k]=Mig[j][k]/VEC[k];}}}
		
		for(int k=0; k<=201; k++){
		//cout<<"REP["<<20<<"]["<<k<<"]="<<REP[20][k]<<endl;                  
		}


                for(int j=0; j <= 151 ; j++){
                for(int k =0; k <= 201 ; k++){
                nrvb[j]=nrvb[j]+Mig[j][k]*norm;}
		h1m->SetBinContent(j+1,nrvb[j]);	         
  //              cout<<nrvb[j]<<endl;
		std::ofstream fichierz("DataReco.txt",ios::app);
                                                if( fichierz.is_open() )
                                                {
                                                fichierz <<nrvb[j]<< std::endl;
                      		                }
                fichierz.close();
		}



                for(int k=0; k <= 201 ; k++){
                for(int j=0; j <= 151 ; j++){
                ntvb[k]=ntvb[k]+Mig[j][k]*norm;}
		h2m->SetBinContent(k+1,ntvb[k]);
		cout<<ntvb[k]<<endl;
		std::ofstream fichierza("DataTrue.txt",ios::app);
                                                if( fichierza.is_open() )
                                                {
                                                fichierza <<ntvb[k]<< std::endl;
                                                }
                fichierza.close();
		}
	

                for(int j=0 ; j <= 151 ; j++){
                for(int k=0 ; k <= 201 ; k++){
                esr[j]=ReP[j][k]*ntvb[k]+esr[j];}
		}
						
                for(int j=0 ; j<=151 ; j++){
		cout<<"reco["<<j<<"]="<<esr[j]<<"  calculé directemnt = " <<nrvb[j] <<endl;}








/*

		double nombrx = 0;
		ifstream monFluxx("Unfolded.txt");  //Ouverture d'un fichier en lecture
                         if(monFluxx)
                         {
                         double nombrx;
                                for( int i=0; i < 40 ; i++){
                                monFluxx >> nombrx; //Lit un nombre ?|  virgule depuis le fichier 
                                yx[i]=nombrx;
	
				for(l=0; l<yx[i];l++){
				h1m->Fill(yx[i]);		
				 }}}

		







// ******************************  calcule des �lements  *********************************************
		ifstream monFluxl("Migration.txt");  //Ouverture d'un fichier en lecture
                         if(monFluxl)
                         {
                         double nombrl;
                                for( int i=0;i < 30000 ; i++){
                                monFluxl >> nombrl; //Lit un nombre ?|  virgule depuis le fichier 
                                yl[i]=nombrl; }}



		
                // La matrice de Migration *********************************************************************
                i = 0;
                for(int j=0; j < 150 ; j++){
                for(int k=0; k < 200 ; k++){
                MigL[j][k]=yl[i]/norm;
                i=i+1;
//     		HIL->Fill(j,k,MigL[j][k]);
//		cout<<"MigL["<<j<<"]["<<k<<"]="<<MigL[j][k]<<endl;
		}}                                                                                                                                

		
		 //--------------Calcule direct-------------
		 for(int k=0; k<=101; k++){
		 for (int j = 0; j <= 101; j++){
		 VECL[k]=MigL[j][k]+VECL[k];
//		 cout<<"VECL["<<k<<"]="<<VECL[k]<<endl;
		 }}             
		            

		 for(int j = 0; j <= 101 ; j++){
                 for (int k = 0; k <= 101; k++){
                 if(VECL[k]!=0){REPL[j][k]=MigL[j][k]/VECL[k];}
		 HIL->Fill(j,k,REPL[j][k]);
//		 cout<< "RePL["<<j<<"]["<<k<<"]="<<REPL[j][k]<<endl;
		 }}
		

  		for(int j=0; j < 150 ; j++){
                for(int k =0; k < 200 ; k++){
		nrvb[j]=nrvb[j]+MigL[j][k]*norm;}

		 std::ofstream fichierza("DataReco.txt",ios::app);
                                                if( fichierza.is_open() )
                                                {
                                                fichierza <<nrvb[j]<< std::endl;
                                                }
                fichierza.close();

		cout<<"nrvb["<<j<<"]="<<nrvb[j]<<endl;}
		 
             
		for(int k=0; k < 200 ; k++){
                for(int j=0; j < 150 ; j++){
		ntvb[k]=ntvb[k]+MigL[j][k]*norm;}
		
		std::ofstream fichierz("DataTrue.txt",ios::app);
                                                if( fichierz.is_open() )
                                                {
                                                fichierz <<ntvb[k]<< std::endl;
                                                }
                fichierz.close();	
		
		cout<<"ntvb["<<k<<"]="<<ntvb[k]<<endl;}
                

		for(int j=0 ; j <= 150 ; j++){
                for(int k=0 ; k <= 200 ; k++){
                esr[j]=REPL[j][k]*ntvb[k];}
                }
                                                
                for(int j=0 ; j<=101 ; j++){
			//                cout<<"reco["<<j<<"]="<<esr[j]<<"  calculé directem = " <<nrvb[j] <<endl;
		}
*/	
		// ***************************************************************************	
/*		double fun = 0;		
		double landa = 1;
		double delu = 0;
	
                 for (int j = 0; j <= 101; j++){
                 for(int k=0; k<=101; k++){
		 Double_t error = h->GetBinError(bin);

		 fun=erf(delu/(sqrt(2)*landa*error))
		 MigL[j][k]=MigL[j][k]+REPL[j][k]*
                 }}
		






 /                                                                                               
// Reponse and Migration Matrix verification  ********************************************************
		
		//-------------------Migration
		for(int j=0; j <= 151 ; j++){
                for(int k =0; k <= 201 ; k++){
		nrvb[j]=nrvb[j]+Mig[j][k];
		}}

		for(int k=0; k <= 201 ; k++){
                for(int j=0; j <= 151 ; j++){
                ntvb[k]=ntvb[k]+Mig[j][k];
                }} 


		som= 0;		
		for(int j=0;j<=151;j++){
//		cout<< "nrvb["<<j<<"]="<<nrvb[j]<<endl;
		som=som+nrvb[j];}
		cout<<som<<endl;

             	som= 0;
		for(int j=0;j<=201;j++){
//              cout<< "ntvb["<<j<<"]="<<ntvb[j]<<endl;
		som=som+ntvb[j];}
                cout<<som<<endl;




		//-------------------Reponse				 		
		for(int j=0;j<=151;j++){
                       for(int k =0; k <= 201 ; k++){
  	  	 	 esr[j]=ReP[j][k]*ntvb[k];}}

		for(int j=0;j<=151;j++){
                cout<<"reco["<<j<<"]="<<esr[j]<<"  calculé directement " <<nrvb[j] <<endl;
		HI->Fill(esr[j]);
		}
*/




//HI1->Draw("Colz");
//HIL->Draw("Colz");
//HIL->Draw("colz");

//HIL->Draw("colz");
//h1m->Draw();
h2m->Draw();
return 0;


}


