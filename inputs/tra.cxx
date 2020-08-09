{
//=========Macro generated from canvas: c/c
//=========  (Thu Aug  4 13:27:02 2016) by ROOT version5.34/14
 


   TH1F* UNF  = new TH1F("UNF"," UNFolding  Without smearing ",72,29.5,100.5);
   TH1F* UNFo  = new TH1F("UNFo"," UNFolding with smearing ",72,29.5,100.5);
   TH1F* h_tmT = new TH1F("h_tmT","masse transvrse true",72,29.5,100.5);

   TH1F *MC1_recoil_cut_2 = new TH1F("MC1_recoil_cut_2","recoil",72,29.5,100.5);
   TH1F *MC_recoil_cut = new TH1F("MC_recoil_cut","recoil",72,29.5,100.5);

        double yt[72];
        double xt[72];
        double zt[72];


                         ifstream monFlue("DataTrue.txt");  //Ouverture d'un fichier en lecture
                         if(monFlue)
                         {
                         double nombree;
                                for( int i=1; i <= 72 ; i++){
                                monFlue >> nombree; //Lit un nombre ?|  virgule depuis le fichier 
                                zt[i]=nombree;
				if(i==1 || i==72) nombree=0;
                                MC1_recoil_cut_2->SetBinContent(i,nombree);
 
                               }}



                         ifstream monFlux("DataTrue-0.txt");  //Ouverture d'un fichier en lecture
                         if(monFlux)
                         {
                         double nombr;
                                for( int i=1; i <= 72 ; i++){

                                monFlux >> nombr; //Lit un nombre ?|  virgule depuis le fichier 
                                yt[i]=nombr;

                                if(i==1 || i==72) nombr=0;
			        MC_recoil_cut->SetBinContent(i,nombr);
                                }}



                         ifstream monFlu("DataTrue-1.txt");  //Ouverture d'un fichier en lecture
                         if(monFlu)
                         {
                         double nombre;
                                for( int i=1; i <= 72 ; i++){
                                monFlu >> nombre; //Lit un nombre ?|  virgule depuis le fichier 
                                xt[i]=nombre;

                                if(i==1 || i==72) nombre=0;
                                UNFo->SetBinContent(i,nombre);
                                }}



   TCanvas *c = new TCanvas("canvas", "",1,1,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.16);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.16);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: uplongad
   TPad *uplongad = new TPad("uplongad", "uplongad",0,0.3,1,1);
   uplongad->Draw();
   uplongad->cd();
   uplongad->Range(-10.12658,-27840.4,53.16456,146162.1);
   uplongad->SetFillColor(0);
   uplongad->SetBorderMode(0);
   uplongad->SetBorderSize(2);
   uplongad->SetTickx(1);
   uplongad->SetTicky(1);
   uplongad->SetLeftMargin(0.16);
   uplongad->SetRightMargin(0.065);
   uplongad->SetTopMargin(0.125);
   uplongad->SetBottomMargin(0.01);
   uplongad->SetFrameBorderMode(0);
   uplongad->SetFrameBorderMode(0);
   
   TH1F *Data_recoil_cut_2 = new TH1F("Data_recoil_cut_2","recoil",72,29.5,100.5);
   Data_recoil_cut_2->SetMinimum(0.);
   Data_recoil_cut_2->SetMaximum(0.08);
   Data_recoil_cut_2->SetEntries(2796157);
   Data_recoil_cut_2->SetOption("HIST");
   Data_recoil_cut_2->SetLineWidth(2);
   Data_recoil_cut_2->SetMarkerStyle(20);
   Data_recoil_cut_2->SetMarkerSize(1.4);
   Data_recoil_cut_2->GetXaxis()->SetTitle("p_{T}^{l} [GeV]");
//   Data_recoil_cut_2->GetXaxis()->SetRange(0,25);
   Data_recoil_cut_2->GetXaxis()->SetLabelFont(42);
   Data_recoil_cut_2->GetXaxis()->SetLabelSize(0.07);
   Data_recoil_cut_2->GetXaxis()->SetTitleSize(0.08);
   Data_recoil_cut_2->GetXaxis()->SetTitleOffset(1.4);
   Data_recoil_cut_2->GetXaxis()->SetTitleFont(42);
//   Data_recoil_cut_2->GetYaxis()->SetTitle("Events / 2 GeV");
   Data_recoil_cut_2->GetYaxis()->SetLabelFont(42);
   Data_recoil_cut_2->GetYaxis()->SetLabelSize(0.07);
   Data_recoil_cut_2->GetYaxis()->SetTitleSize(0.08);
   Data_recoil_cut_2->GetYaxis()->SetTitleOffset(0.9);
   Data_recoil_cut_2->GetYaxis()->SetTitleFont(42);
   Data_recoil_cut_2->GetZaxis()->SetLabelFont(42);
   Data_recoil_cut_2->GetZaxis()->SetLabelSize(0.07);
   Data_recoil_cut_2->GetZaxis()->SetTitleSize(0.08);
   Data_recoil_cut_2->GetXaxis()->SetTitle("p_{T}^{l} [GeV]");
   Data_recoil_cut_2->Draw("P");

  

//   MC1_recoil_cut_2 = (TH1F*)h->Get("h_tmT");
   MC1_recoil_cut_2->Sumw2();
   MC1_recoil_cut_2->Scale(1./MC1_recoil_cut_2->Integral()); 

   MC1_recoil_cut_2->SetEntries(2796157);
   MC1_recoil_cut_2->SetOption("HIST");
   Int_t ci;   // for color index setting
   ci = kAzure+7;
   MC1_recoil_cut_2->SetFillColor(ci);
   MC1_recoil_cut_2->SetLineWidth(2);
   ci = kAzure+7;
   MC1_recoil_cut_2->SetMarkerColor(ci);
   MC1_recoil_cut_2->SetMarkerStyle(22);
   MC1_recoil_cut_2->SetMarkerSize(1.4);
   MC1_recoil_cut_2->GetXaxis()->SetTitle(" u [GeV]");
//   MC1_recoil_cut_2->GetXaxis()->SetRange(0,25);
   MC1_recoil_cut_2->GetXaxis()->SetLabelFont(42);
   MC1_recoil_cut_2->GetXaxis()->SetLabelSize(0.07);
   MC1_recoil_cut_2->GetXaxis()->SetTitleSize(0.08);
   MC1_recoil_cut_2->GetXaxis()->SetTitleOffset(1.4);
   MC1_recoil_cut_2->GetXaxis()->SetTitleFont(42);
   MC1_recoil_cut_2->GetYaxis()->SetLabelFont(42);
   MC1_recoil_cut_2->GetYaxis()->SetLabelSize(0.07);
   MC1_recoil_cut_2->GetYaxis()->SetTitleSize(0.08);
   MC1_recoil_cut_2->GetYaxis()->SetTitleOffset(0.9);
   MC1_recoil_cut_2->GetYaxis()->SetTitleFont(42);
   MC1_recoil_cut_2->GetZaxis()->SetLabelFont(42);
   MC1_recoil_cut_2->GetZaxis()->SetLabelSize(0.07);
   MC1_recoil_cut_2->GetZaxis()->SetTitleSize(0.08);
   MC1_recoil_cut_2->GetXaxis()->SetTitle("p_{T}^{l} [GeV]");
   MC1_recoil_cut_2->Draw("hist same");
 


//  TFile* hh = new TFile("output.root");
//   TH1F *MC_recoil_cut = new TH1F("MC_recoil_cut","recoil",100,0,150);

//   MC_recoil_cut = (TH1F*)hh->Get("UNF");
 
   MC_recoil_cut->Sumw2();
   MC_recoil_cut->Scale(1./MC_recoil_cut->Integral());  


   MC_recoil_cut->SetEntries(2796157);
   MC_recoil_cut->SetOption("HIST");
   ci = kOrange+10;
   MC_recoil_cut->SetLineColor(ci);
   MC_recoil_cut->SetLineWidth(2);
   ci = kOrange+10;
   MC_recoil_cut->SetMarkerColor(ci);
   MC_recoil_cut->SetMarkerStyle(25);
   MC_recoil_cut->SetMarkerSize(1.4);
   MC_recoil_cut->GetXaxis()->SetTitle(" u [GeV]");
//   MC_recoil_cut->GetXaxis()->SetRange(0,25);
   MC_recoil_cut->GetXaxis()->SetLabelFont(42);
   MC_recoil_cut->GetXaxis()->SetLabelSize(0.07);
   MC_recoil_cut->GetXaxis()->SetTitleSize(0.08);
   MC_recoil_cut->GetXaxis()->SetTitleOffset(1.4);
   MC_recoil_cut->GetXaxis()->SetTitleFont(42);
   MC_recoil_cut->GetYaxis()->SetLabelFont(42);
   MC_recoil_cut->GetYaxis()->SetLabelSize(0.07);
   MC_recoil_cut->GetYaxis()->SetTitleSize(0.08);
   MC_recoil_cut->GetYaxis()->SetTitleOffset(0.9);
   MC_recoil_cut->GetYaxis()->SetTitleFont(42);
   MC_recoil_cut->GetZaxis()->SetLabelFont(42);
   MC_recoil_cut->GetZaxis()->SetLabelSize(0.07);
   MC_recoil_cut->GetZaxis()->SetTitleSize(0.08);
   MC_recoil_cut->GetXaxis()->SetTitle("p_{T}^{l} [GeV]");
   MC_recoil_cut->Draw("hist same");
   
   gPad->RedrawAxis();



   TPaveText *pt = new TPaveText(0.19,0.81,0.3,0.93,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextFont(42);
   pt->SetTextSize(0.045);
   TText *text = pt->AddText(" ");
   text = pt->AddText(" ");
     TLegend *leg = new TLegend(0.25,0.6,0.45,0.85,NULL,"brNDC");
     
   leg->SetBorderSize(0);
   leg->SetTextSize(0.06);
   leg->SetLineColor(10);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Data_recoil_cut_2"," ","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("MC_recoil_cut","m_{T} Unfolded - After Smearing","l");

   ci = kOrange+10;
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("MC1_recoil_cut_2","m_{T} True ","f");

   ci = kAzure+7;
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.4);
   entry->SetTextFont(42);
   leg->Draw();
TLatex l1;
l1.SetTextAlign(12);
l1.SetTextSize(0.09);
l1.SetTextFont(72);
l1.SetLineWidth(2);
l1.SetNDC();
//l1.DrawLatex(0.20, 0.8,"ATLAS #sqrt{s} =13 TeV ");
TLatex l2;
l2.SetTextAlign(12);
l2.SetTextSize(0.09);
l2.SetTextFont(42);
l2.SetLineWidth(2);
l2.SetNDC();
//l2.DrawLatex(0.34, 0.885," Internal");
// l2.DrawLatex(0.34, 0.79," Preliminary"); 
/*
TLatex l3;
l3.SetTextSize(0.07);
l3.SetTextFont(42);
l3.SetNDC();
l3.DrawLatex(0.20, 0.7,"#sqrt{s} =13 TeV");
*/
TLine mline;
mline.SetLineWidth(38);
mline.SetLineColor(kWhite);
mline.DrawLineNDC(0.16, 1.00, 0.3, 1.0);
TLatex *tex10 = new TLatex(0.16,0.95,"x 10^{3}");
tex10->SetNDC();
tex10->SetTextFont(42);
tex10->SetTextSize(0.05);
//tex10->Draw();
   
   pt = new TPaveText(0.43,0.81,0.69,0.92,"brNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   pt->SetTextFont(42);
   pt->SetTextSize(0.03);
   text = pt->AddText(" ");
   text = pt->AddText(" ");
   text = pt->AddText(" ");
//   pt->Draw();
   uplongad->Modified();
   c->cd();
  
// ------------>Primitives in pad: lowerPad
   lowerPad = new TPad("lowerPad", "lowerPad",0,0,1,0.3);
   lowerPad->Draw();
   lowerPad->cd();
   lowerPad->Range(-10.12658,0.9297468,53.16456,1.056329);
   lowerPad->SetFillColor(0);
   lowerPad->SetBorderMode(0);
   lowerPad->SetBorderSize(2);
   lowerPad->SetGridx(0);
   lowerPad->SetGridy();
   lowerPad->SetTickx(1);
   lowerPad->SetTicky(1);
   lowerPad->SetLeftMargin(0.16);
   lowerPad->SetRightMargin(0.05);
   lowerPad->SetTopMargin(0.05);
   lowerPad->SetBottomMargin(0.40);
   lowerPad->SetFrameBorderMode(0);
   lowerPad->SetFrameBorderMode(0);
   
  // TH1D *ratio_recoil_cut_2 = new TH1D("ratio_recoil_cut_2","recoil",20,0,100);
//*************


          TH1F *ratio_recoil_cut_2 = (TH1F*)MC_recoil_cut->Clone("ratio_recoil_cut_2");
   	  ratio_recoil_cut_2->Sumw2();
          ratio_recoil_cut_2->SetStats(0);
          ratio_recoil_cut_2->Divide(MC1_recoil_cut_2);

//
   ratio_recoil_cut_2->SetMinimum(0.9);
   ratio_recoil_cut_2->SetMaximum(1.1);
   ratio_recoil_cut_2->SetEntries(704225.2);
   ratio_recoil_cut_2->SetOption("HIST");

   ci = kOrange+10;
   ratio_recoil_cut_2->SetLineColor(ci);
   ratio_recoil_cut_2->SetLineWidth(2);

   ci = kOrange+10;
   ratio_recoil_cut_2->SetMarkerColor(ci);
   ratio_recoil_cut_2->SetMarkerStyle(0);
   ratio_recoil_cut_2->SetMarkerSize(1.2);
//   ratio_recoil_cut_2->GetXaxis()->SetRange(1,25);
   ratio_recoil_cut_2->GetXaxis()->SetLabelFont(42);
   ratio_recoil_cut_2->GetXaxis()->SetLabelSize(0.14);
   ratio_recoil_cut_2->GetXaxis()->SetTitleSize(0.17);
   ratio_recoil_cut_2->GetXaxis()->SetTitleOffset(1.10);
   ratio_recoil_cut_2->GetXaxis()->SetTitleFont(42);
//   ratio_recoil_cut_2->GetYaxis()->SetTitle("Data / Pred.");
   ratio_recoil_cut_2->GetYaxis()->SetNdivisions(507);
   ratio_recoil_cut_2->GetYaxis()->SetLabelFont(42);
   ratio_recoil_cut_2->GetYaxis()->SetLabelSize(0.14);
   ratio_recoil_cut_2->GetYaxis()->SetTitleSize(0.17);
   ratio_recoil_cut_2->GetYaxis()->SetTitleOffset(0.40);
   ratio_recoil_cut_2->GetYaxis()->SetTitleFont(42);
   ratio_recoil_cut_2->GetZaxis()->SetLabelFont(42);
   ratio_recoil_cut_2->SetLineColor(kOrange+10);
   ratio_recoil_cut_2->SetMarkerColor(kOrange+10);
   ratio_recoil_cut_2->GetXaxis()->SetTitle("m_{T} [GeV]");
   ratio_recoil_cut_2->Draw("P");
   
   lowerPad->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
   c->SaveAs("recoil_all_B.pdf");
}
