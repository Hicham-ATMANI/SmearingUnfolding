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

  void ratioplot() {

// ******************* pT du lepton - TRUE  ****************************

           TH1F * h1 = new TH1F("h1","pt",70,20,90);

	   ifstream monFlux("DataTrue_int.txt");  //Ouverture d'un fichier en lecture
           if(monFlux)
           {
           double nombr;
           for( int i=0; i < 70 ; i++){
           monFlux >> nombr; //Lit un nombre ?|  virgule depuis le fichier 
           h1->SetBinContent(i,nombr);
           }}
	   h1->Sumw2();

           TH1F * h2 = new TH1F("h2","pp",70,20,90);
	   ifstream monFlu("DataTrue_ap.txt");  //Ouverture d'un fichier en lecture
           if(monFlu)
           {
           double nombre;
           for( int i=0; i < 70 ; i++){
           monFlu >> nombre; //Lit un nombre ?|  virgule depuis le fichier 
           h2->SetBinContent(i,nombre);
           }}	
	   h2->Sumw2();

          TLegend *legendx=new TLegend(0.6,0.5,0.87,0.7);
          legendx->AddEntry(h1,"spectre reco initial","lpe");
          legendx->AddEntry(h2,"spectre reco avec poids","lpe");
        //  legendx->SetBordereSize(0); 

          TLine *line = new TLine(20,1,90,1);

          TCanvas *c = new TCanvas("c", "canvas", 800, 800);


          TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
          pad1->SetBottomMargin(0);
          pad1->SetTitle("");
          pad1->Draw();
          pad1->cd();
          h1->SetStats(0);
          h1->GetYaxis()->SetTitle("h1 et h2");
          h1->GetYaxis()->SetLabelSize(0.03);
          h1->Draw();
          h2->Draw("same");
          legendx->Draw("same");

          h1->GetYaxis()->SetNdivisions(505);
          h1->GetYaxis()->SetTitleSize(20);
          h1->GetYaxis()->SetTitleFont(43);
          h1->GetYaxis()->SetTitleOffset(1.55);
          h1->GetYaxis()->SetLabelFont(43);
          h1->GetYaxis()->SetLabelSize(15);
          h1->GetXaxis()->SetTitleSize(20);
          h1->GetXaxis()->SetTitleFont(43);
          h1->GetXaxis()->SetTitleOffset(4.);
          h1->GetXaxis()->SetLabelFont(43);
          h1->GetXaxis()->SetLabelSize(15);


          TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
          axis->SetLabelFont(43);
          axis->SetLabelSize(15);
          axis->Draw();

          c->cd();
          TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
          pad2->SetTopMargin(0);
          pad2->SetBottomMargin(0.2);
          pad2->SetGridx();
          pad2->Draw();
          pad2->cd();

          TH1F *h3 = (TH1F*)h1->Clone("h3");
          h3->SetLineColor(kBlack);
          // *********************
          h3->SetTitle("");
          h3->SetMinimum(0.8);
          h3->SetMaximum(1.2);
          h3->Sumw2();
          h3->SetStats(0);
          h3->Divide(h2);
          h3->SetLineColor(4);
          h3->Draw("ep");
          line->Draw("same");


          h1->SetLineColor(kBlue+1);
          h1->SetLineWidth(2);
          h1->GetYaxis()->SetTitleSize(20);
          h1->GetYaxis()->SetTitleFont(43);


          h2->SetLineColor(kRed);
          h2->SetLineWidth(2);
          h3->GetXaxis()->SetLabelFont(43);


          h3->SetLineColor(4);

          h3->GetYaxis()->SetTitle("ratio h1 / h2 ");
          h3->GetYaxis()->SetNdivisions(505);
          h3->GetYaxis()->SetTitleSize(20);
          h3->GetYaxis()->SetTitleFont(43);
          h3->GetYaxis()->SetTitleOffset(1.55);
          h3->GetYaxis()->SetLabelFont(43);
          h3->GetYaxis()->SetLabelSize(15);
          h3->GetXaxis()->SetTitleSize(20);
          h3->GetXaxis()->SetTitleFont(43);
          h3->GetXaxis()->SetTitleOffset(4.);
          h3->GetXaxis()->SetLabelFont(43);
          h3->GetXaxis()->SetLabelSize(15);
          h3->GetXaxis()->SetTitle("pT of lepton True [GEV]");


}
