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

int rappC() {

  Int_t n = 100;
  
   double x[72];
   double y[72];
   double z[72];
   double cov[72][72];
   int a = 0;
   int k = 1;

   TH2D* HI1=new TH2D("HI1","  ",71,1,72,71,1,72);
   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,30,100);
   TH1F* h_tmTR = new TH1F("h_tmTR"," pt de W   ",100,0,100);
   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,30,100);

   ifstream monFlu("UnfoldedCov.txt");  //Ouverture d'un fichier en lecture
   if(monFlu)
        {
      double nombr;
                for( int i=1; i <= 5184 ; i++){
                if(k>72) k=1;
                monFlu >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                a=int(i/72)+1;
                if(k==72){ a=a-1;}
                cov[a][k]=nombr;
                k=k+1;
                }}

   ifstream monFlux("Unfolded_err.txt");  //Ouverture d'un fichier en lecture
   if(monFlux)
        {
        double nombre;
                for( int j=1; j <= 72 ; j++){
                monFlux >> nombre; //Lit un nombre ?|  virgule depuis le fichier
                x[j]=nombre;
                cout<<nombre<<endl;
                }}


		for( int i=1; i <= 72 ; i++){
                h_tmTU->SetBinContent(i,sqrt(cov[i][i])/x[i]);
                cout<<"cov["<<i<<"]["<<i<<"]="<<sqrt(cov[i][i])<<endl;
        	}

h_tmTU->SetStats(0);

h_tmTU->SetTitle("rapport err=Marice / err=hist");
h_tmTU->Draw();
return 0;


}
