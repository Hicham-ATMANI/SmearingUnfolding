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

int xet() {

   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,30,100);
   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,30,100);


double x[100];
double y[100];
double z[100];
double xx = 0;

// Les donnÃes pour #delta(m)=100MeV ***************************************
	   TFile* h = new TFile("output.root");
           TH1F * h1 = new TH1F("h1","pt",72,30,100);
           h1 = (TH1F*)h->Get("h_tmT_ap");

                for( int j=1; j <= 72 ; j++){
		x[j]=h1->GetBinContent(j);
		h_tmTT->SetBinContent(j,x[j]);
	//	cout<<x[j]<<endl;
		}

// les donnÃes True ********************************************************

           TH1F * h2 = new TH1F("h2","pt",72,30,100);
           h2 = (TH1F*)h->Get("h_tmT");

		for( int j=1; j <= 72 ; j++){
                y[j]=h2->GetBinContent(j);
		z[j]= h2->GetBinError(j); 
	//       cout<<nombr<<endl;
		}


//*************************************************************************
		 for( int j=1; j <= 72 ; j++){
                 xx=xx+pow((y[j]-x[j]),2)/pow(z[j],2);
                 cout<<xx<<endl;
                 }
        
//h_tmTT->Draw();
//h_tmTU->Draw("same");


return 0;
}

