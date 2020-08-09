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

int cov() {


//   TCanvas *c1 = new TCanvas("c1","A Simple Graphzz Example",200,10,700,500);
   Int_t n = 100;
   double x[72];
   double y[72];
   double z[72];
   double cov[72][72];
   double cor[72][72];
   double max = 0;
   int a = 0;
   int k = 1;

   TH2D* HI1=new TH2D("HI1","  ",71,1,72,71,1,72);
   TH2D* HI2=new TH2D("HI2","  ",71,1,72,71,1,72);


   ifstream monFlu("UnfoldedCov.txt");  //Ouverture d'un fichier en lecture
   if(monFlu)
        {
      double nombr;
                for( int i=1; i <= 5184 ; i++){
                if(k>72) k=1;
		monFlu >> nombr; //Lit un nombre ?|  virgule depuis le fichier
		a=int(i/72)+1;
                if(k==72){ a=a-1;}
		if(nombr>max) max= nombr;
          //    cout<<max<<endl;		
		cov[a][k]=nombr;							
		k=k+1; 	     
		}}
	
		for( int i=1; i <= 72 ; i++){
                for( int j=1; j <= 72 ; j++){
                cor[i][j]=cov[i][j]/(sqrt(cov[i][i]*cov[j][j]));
		}}

                for( int i=1; i <= 72 ; i++){
                for( int j=1; j <= 72 ; j++){
		HI2->Fill(i,j,cov[i][j]);
		HI1->Fill(i,j,cor[i][j]);
                cout<<"cor["<<i<<"]["<<j<<"]="<<cor[i][j]<<endl;
		}}

//HI1->GetZaxis()->SetRangeUser(1,-1);
HI1->SetStats(0);
HI1->Draw("colz"); 
return 0;
}
