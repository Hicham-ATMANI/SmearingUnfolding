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

int un() {

   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,30,100);
   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,30,100);


double x[100];
double y[100];
double z[100];
double yy[100];
double xx = 0;

double_t cov[72][72];
double_t covi[72][72];
double unit[72][72];
   int a = 0;
   int k = 1;

// Les donn?es pour #delta(m)=100MeV ****************************************
           TFile* h = new TFile("output.root");
           TH1F * h1 = new TH1F("h1","pt",72,30,100);
           h1 = (TH1F*)h->Get("h_tmT_ap");

                for( int j=1; j <= 72 ; j++){
                x[j]=h1->GetBinContent(j);}

// les données True *********************************************************

           TH1F * h2 = new TH1F("h2","pt",72,30,100);
           h2 = (TH1F*)h->Get("h_tmT");

                for( int j=1; j <= 72 ; j++){
                y[j]=h2->GetBinContent(j);}

//Covariance  matrix ********************************************************
	 
	ifstream monFlu("cov_1.txt");  //Ouverture d'un fichier en lecture
	   if(monFlu)
       		{
      		double_t nombr;
                for( int i=1; i <= 5184 ; i++){
                if(k>72) k=1;
                monFlu >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                a=int(i/72)+1;
                if(k==72){ a=a-1;}
	//	cout<<nombr<<endl;
	//	cout<<"a="<<a<<"             k="<<k<<"    nombr=   "<<nombr<<endl;
	        covi[a][k]=nombr;
  		cout<<"cov["<<a<<"]["<<k<<"]="<<covi[a][k]<<endl;	
                k=k+1;
		}}


                 for( int i=1; i <= 72 ; i++){
		 double sum = 0;
                 for( int j=1; j <= 72 ; j++){
                 sum=covi[i][j]*(y[j]-x[j])+sum;}
		 yy[i]=sum;
		 cout<<yy[i]<<endl;
		 }


		 for( int i=1; i <= 72 ; i++){
		 xx=(y[i]-x[i])*yy[i]+xx;
		 cout<<"    "<<xx<<"          True_poid = " << x[i] << "       True = " <<y[i] <<"     matri = "<<yy[i] <<endl;
		 }



//h_tmTT->Draw();
//h_tmTU->Draw("same");

/*

ifstream monFlue("UnfoldedCov.txt");  //Ouverture d'un fichier en lecture
           if(monFlue)
                {
                double nombre;
                for( int i=1; i <= 5184 ; i++){
                if(k>72) k=1;
                monFlue >> nombre; //Lit un nombre ?|  virgule depuis le fichier
                a=int(i/72)+1;
                if(k==72){ a=a-1;}
                covi[a][k]=nombre;
                k=k+1;
                }}


                 for( int i=1; i <= 72 ; i++){
                 for( int j=1; j <= 72 ; j++){
                 unit[i][j]=0;
                 for( int k=1; k <= 72 ; k++){
                 unit[i][j]=unit[i][j]+cov[i][k]*covi[k][j];
                 }
                 cout<<unit[i][j]<<endl;
                 }}
*/

return 0;
}

