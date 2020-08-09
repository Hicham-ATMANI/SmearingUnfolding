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

int ee() {

 								
//   TCanvas *c1 = new TCanvas("c1","A Simple Graphzz Example",200,10,700,500);
   Int_t n = 100;
   double_t x[100];
   double_t y[100];
   double_t z[100];

   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,30,100);
   TH1F* h_tmTR = new TH1F("h_tmTR"," pt de W   ",100,0,100);
   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,30,100);


   ifstream monFlu("Unfolded.txt");  //Ouverture d'un fichier en lecture
   if(monFlu)
        {
        double nombr;
                for( int j=1; j <= 72 ; j++){
                monFlu >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                y[j]=nombr;
		cout<<nombr<<endl; 
      		h_tmTU->SetBinContent(j,y[j]);
		}}


   ifstream monFl("DataTrue.txt");  //Ouverture d'un fichier en lecture
   if(monFl)
        {
        double nomb;
                for( int j=1; j <= 72 ; j++){
                monFl >> nomb; //Lit un nombre ?|  virgule depuis le fichier
                z[j]=nomb;
         	cout<<nomb<<endl;
	        h_tmTT->SetBinContent(j,z[j]);
                }}


   ifstream monFlux("Unfolded_err.txt");  //Ouverture d'un fichier en lecture
   if(monFlux)
	{
    	double nombre;
		for( int j=1; j <= 72 ; j++){
		monFlux >> nombre; //Lit un nombre à virgule depuis le fichier
		x[j]=nombre;	
		cout<<nombre<<endl;
		h_tmTU->SetBinError(j,x[j]);
		}}

 	  TLegend *legendxaa=new TLegend(0.12,0.6,0.39,0.8);
          legendxaa->AddEntry(h_tmTU,"Spectre Unfolded ","lpe");
          legendxaa->AddEntry(h_tmTT,"Spectre Ture","lpe");

h_tmTU->SetTitle("masse transverse True");
h_tmTU->Draw("e");
h_tmTU->GetXaxis()->SetTitle("X-Axis");
h_tmTU->GetYaxis()->SetTitle("Y-Axis");
h_tmTU->SetLineColor(2);
h_tmTT->SetLineColor(4);
h_tmTU->GetXaxis()->CenterTitle();
h_tmTU->GetYaxis()->CenterTitle();
h_tmTT->Draw("same");
//h_tmTR->Draw("same");
legendxaa->Draw("same");
/*
gr->GetXaxis()->SetTitle("X-Axis");
gr->GetYaxis()->SetTitle("Y-Axis");
gr->GetXaxis()->CenterTitle();
gr->GetYaxis()->CenterTitle();
gr->Draw("ALP");

*/
  return 0;
}
