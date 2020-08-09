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

int rel() {

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


   TFile* h = new TFile("output.root");
   TH1F * h1 = new TH1F("h1","pt",72,30,100);
   h1 = (TH1F*)h->Get("h_tmT_ap");

   TH1F * h2 = new TH1F("h2","pt",72,30,100);
   h2 = (TH1F*)h->Get("h_tmT");		

             
           for(int i=1; i<=72;i++){
	   z[i]= h1->GetBinContent(i);   
	   y[i]= h2->GetBinContent(i);
	   val=(z[i]-y[i])/y[i];
           h_tmTU->SetBinContent(i,val);
	   cout<<"    true =  "<<y[i]<<"    avec_poid =  "<<z[i]<<"  relative_error = "<<abs(val*y[i])<<endl;
	   } 


 ifstream monFluz("Unfolded_err.txt");  //Ouverture d'un fichier en lecture
   if(monFluz)
        {double nombrz;
                for( int j=1; j <= 72 ; j++){
                monFluz >> nombrz; //Lit un nombre ?|  virgule depuis le fichier
                if(j==1 || j==72) nombrz=0;
                h_tmTR->SetBinContent(j,nombrz/z[j]);
                }}



          TLegend *legendxaa=new TLegend(0.12,0.6,0.49,0.75);
   	  legendxaa->SetFillStyle(1001);
   	  legendxaa->SetLineColor(1);
   	  legendxaa->SetLineStyle(1);
   	  legendxaa->SetTextFont(42);
	  legendxaa->AddEntry(h_tmTU,"Variation d'Error Relative Pour #delta m=100MeV","lpe");
          legendxaa->AddEntry(h_tmTR,"Error stat d'unfolding","lpe");
/*
          legendxaa->AddEntry(h2,"spectre nominal","lpe");

	  h_tmTR->SetStats(0);

	  h_tmTR->SetLineColor(kRed);
          h_tmTR->GetXaxis()->SetTitle("M_{W}^{T} [GeV]");
          h_tmTR->GetYaxis()->SetTitle("Erreur relative");
	  h_tmTR->GetYaxis()->SetNdivisions(505);
          h_tmTR->GetYaxis()->SetTitleSize(20);
          h_tmTR->GetYaxis()->SetTitleFont(43);
          h_tmTR->GetYaxis()->SetTitleOffset(1);
          h_tmTR->GetYaxis()->SetLabelFont(43);
          h_tmTR->GetYaxis()->SetLabelSize(15);
*/
h_tmTU->SetTitle("");
h_tmTU->SetStats(0);
h_tmTU->SetLineColor(2);
h_tmTU->Draw("same");

h_tmTR->SetTitle("Error stat d'unfolding");
h_tmTR->Draw("same");

//h1->Draw("same");
//h1->Draw();
//h_tmTR->Draw("same");
//h_tmTR->SetTitle("variation");
//h_tmTRm->Draw("same");
legendxaa->Draw("same");

return 0;
}   
