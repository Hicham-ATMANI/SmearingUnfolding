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
#include "TROOT.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TSystem.h"
#include "TDirectory.h"
#include "Math/QuantFuncMathCore.h"
#include "TUUID.h"

void ew() {

// ******************* pT du lepton - TRUE  ****************************


   double_t z[100];
   double_t zp[100];
   double_t y[100];


           TH1F * h1 = new TH1F("h1","pt",72,30,100);
           TH1F * h2 = new TH1F("h2","pt",72,30,100);
           TH1F * h3 = new TH1F("h3","pt",72,30,100);



	 ifstream monFl("DataReco.txt");  //Ouverture d'un fichier en lecture
	   if(monFl)
	        {
	        double nomb;
                for( int j=1; j <= 72 ; j++){
                monFl >> nomb; //Lit un nombre ?|  virgule depuis le fichier
                z[j] = nomb;
	        gRandom->SetSeed();
	        zp[j]=gRandom->Poisson(z[j]);
	 // 	cout<<z[j]<<"    		  "<<zp[j]<<endl;
                cout<<zp[j]<<endl;
                h1->SetBinContent(j,z[j]);
                h3->SetBinContent(j,zp[j]);
                }} 

        //      cout<<"************************"<<endl;


	ifstream monFla("DataTrue.txt");  //Ouverture d'un fichier en lecture
   	 if(monFla)
	        {
	        double nomba;
                for( int j=1; j <= 72 ; j++){
                monFla>> nomba; //Lit un nombre ?|  virgule depuis le fichier
                y[j]=nomba;
                cout<<sqrt(zp[j])<<endl;
                h2->SetBinContent(j,y[j]);
                }}

	TLegend *legendxa=new TLegend(0.12,0.7,0.4,0.87);
        legendxa->AddEntry(h1,"Spectre reconstruite","lpe");
        legendxa->AddEntry(h3,"Spectre avec fluctuations","lpe");


h1->SetLineColor(4);
//h2->Draw();
h1->Draw();
h3->SetLineColor(2);
h3->Draw("same");
legendxa->Draw("same");

h1->SetLineColor(4);
h2->SetLineColor(2);
//h2->SetOptStat(0); 
//legendxa->Draw("same");
//h1->GetXaxis()->SetTitle("u_{ #parallel }  [GeV]");
//  #perp  #parallel*/

}            
