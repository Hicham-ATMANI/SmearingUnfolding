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

int corr(){

//   TCanvas *c1 = new TCanvas("c1","A Simple Graphzz Example",200,10,700,500);
   Int_t n = 100;
   double_t x[100];
   double_t y[100];
   double_t z[100];
   double_t w[100];
   double_t yy[100];
   double_t val = 0;

   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,29.5,100.5);
   TH1F* h_tmTR = new TH1F("h_tmTR"," pt de W   ",72,29.5,100.5);
   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,29.5,100.5);
   TH1F* h_tmTRm = new TH1F("h_tmTRm"," pt de W   ",72,29.5,100.5);


   TFile* h = new TFile("recoilResolution.root");

   TH1F * h1 = new TH1F("h1","pt",72,30,100);
   h1 = (TH1F*)h->Get("hdata");	

   TH1F * h2 = new TH1F("h2","pt",72,30,100);
   h2 = (TH1F*)h->Get("hmc");
 
   		for(int j=1;j<=10;j++){
			
			x[j]=h1->GetBinContent(j);
			y[j]=h2->GetBinContent(j);
			cout<<" hdata =  "<<x[j]<<"               "<< "       hmc  =  "<< y[j] <<"                       "<<sqrt(x[j]*x[j]-y[j]*y[j])<<"   "<<endl;
   			}	

return 0;
}
