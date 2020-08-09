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

int xer() {

   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,30,100);
   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,30,100);


double x[100];
double y[100];
double z[100];
double xx = 0;

// Les donn?es pour #delta(m)=100MeV ***************************************

            TFile* h = new TFile("output.root");
            TH1F * h1 = new TH1F("h1","pt",72,30,100);
            h1 = (TH1F*)h->Get("h_mt_rec_ap");

                for( int j=1; j <= 72 ; j++){
                x[j]=h1->GetBinContent(j);
                h_tmTT->SetBinContent(j,x[j]);
                }

// les donn?es Reco ********************************************************

          TH1F * h2 = new TH1F("h2","pt",72,30,100);
           h2 = (TH1F*)h->Get("h_mt_rec");

                for( int j=1; j <= 72 ; j++){
                y[j]=h2->GetBinContent(j);
                h_tmTU->SetBinContent(j,y[j]);
                }


// *************************************************************************
                 for( int j=1; j <= 72 ; j++){
                 xx=xx+pow((x[j]-y[j]),2)/y[j];
                 cout<<"x["<<j<<"]=    "<<x[j]<<"		"<<"y["<<j<<"]=    " <<y[j]<<"		"<<xx<<endl;
                 }

h_tmTT->Draw();
h_tmTT->SetLineColor(2);
h_tmTU->Draw("same");


return 0;
}

