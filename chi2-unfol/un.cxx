#include <iostream>
#include <fstream>
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

int un() {

TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,20,90);
TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,20,90);
TH1F* h_tmTP = new TH1F("h_tmTP"," pt de W   ",72,20,90);
	
double x[100]   ;
double y[100]   ;
double z[100]   ;

double yy[100]  ;
double yy2[100] ;

double xx  = 0  ;
double xx2 = 0  ;	

double_t cov[72][72]    ;
double_t covi[72][72]   ;

double unit[72][72]  ;
int a = 0 ;
int k = 1 ;

// Les datas unfolded du poisson  ****************************************************

   ifstream monFluz("Unfolded.txt");  //Ouverture d'un fichier en lecture
   if(monFluz)
        { 
        double nombr;
                for( int j=1 ; j <= 70 ; j++){
                monFluz >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                y[j]=nombr;
    //          cout<<nombr<<endl;
                h_tmTU->SetBinContent(j,y[j]);
                }}


// les datas True *********************************************************
	
   ifstream monFl("DataTrue_1.txt");  //Ouverture d'un fichier en lecture
        if(monFl)
        {
        double nomb;
                for( int j=1 ; j <= 70 ; j++){
                monFl >> nomb; //Lit un nombre ?|  virgule depuis le fichier
                x[j]=nomb;
    //          cout<<nomb<<endl;
                h_tmTT->SetBinContent(j,x[j]);
                }}

// les datas True avec poids *************************************************

   ifstream monFlt("DataTrue_ap.txt");  //Ouverture d'un fichier en lecture
        if(monFlt)
        {
        double nombe;
                for( int j=1 ; j <= 70 ; j++){
                monFlt >> nombe; //Lit un nombre ?|  virgule depuis le fichier
                z[j]=nombe;
    //          cout<<nombe<<endl;
                h_tmTP->SetBinContent(j,z[j]);
                }}

//  Covariance  matrix *******************************************************
	 
	ifstream monFlu("cov_1.txt");  //Ouverture d'un fichier en lecture
	   if(monFlu)
       		{
      		double_t nombr;
                for( int i=1; i <= 4900 ; i++){
                if(k > 70) k=1;
                monFlu >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                a=int(i/70)+1;
                if(k == 70){ a=a-1;}
	        covi[a][k]=nombr;
   //  		cout<<"cov["<<a<<"]["<<k<<"]="<<covi[a][k]<<endl;  
                k=k+1;
		}}

// calcule de Khi-2 *********************************************************
 
                 for( int i=1 ; i <= 70 ; i++){
		 double sum  = 0;
		 double sum2 = 0;
                 for( int j=1 ; j <= 70 ; j++){
                 sum  = covi[i][j]*(y[j]-x[j])+sum  ;
		 sum2 = covi[i][j]*(y[j]-z[j])+sum2 ;
		 }
		 yy[i] = sum   ;
		 yy2[i] = sum2  ; 		 
		 }


		 for( int i=1; i <= 70 ; i++){
		 xx=(y[i]-x[i])*yy[i]+xx;
		 xx2=(y[i]-z[i])*yy2[i]+xx2;
	         
//		 cout<<"*************** -> "<<y[i]<<"            "<<x[i]<<"               "<<z[i]<<endl;
		 cout<<"vrai = "<<xx<<"		"<<"vrai+poids = "<<xx2<<"		"<<xx2-xx<<endl;
        	 
		 }

TLegend *legendx=new TLegend(0.2,0.5,0.5,0.7);
          legendx->AddEntry(h_tmTT," Spectre True ","lpe");
          legendx->AddEntry(h_tmTU," Spectre Unfolded ","lpe");
          legendx->AddEntry(h_tmTP," Spectre true avec poid ","lpe");

h_tmTT->SetTitle("	");
h_tmTT->Draw();
h_tmTT->SetLineColor(1);
h_tmTU->Draw("same");
h_tmTU->SetLineColor(2);
h_tmTP->Draw("same");
h_tmTP->SetLineColor(4);
legendx->Draw("same");
/*
ifstream monFlue("UnfoldedCov.txt");  //Ouverture d'un fichier en lecture
           if(monFlue)
                {
                double nombre;
                for( int i=1; i <= 4900 ; i++){
                if(k>70) k=1;
                monFlue >> nombre; //Lit un nombre ?|  virgule depuis le fichier
                a=int(i/70)+1;
                if(k==70){ a=a-1;}
                cov[a][k]=nombre;
 //        	cout<<"cov["<<a<<"]["<<k<<"]="<<cov[a][k]<<endl;  
	        k=k+1;
                }}


                 for( int i=1; i <= 70 ; i++){
                 for( int j=1; j <= 70 ; j++){
                 unit[i][j]=0;
                 for( int k=1; k <= 70 ; k++){
                 unit[i][j]=unit[i][j]+cov[i][k]*covi[k][j];
                 }
          //     cout<<unit[i][i]<<endl;
	         }}

	         for( int i=1; i <= 70 ; i++){
             	 cout<<unit[i][i]<<endl;
		 } */


return 0;
}

