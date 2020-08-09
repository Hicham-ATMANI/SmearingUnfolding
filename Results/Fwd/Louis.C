#include <cmath>
#include <iostream>
#include "TRandom.h"
#include "TGraphErrors.h"
#include <TError.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TFitter.h>
#include <TF1.h>
#include <TStyle.h>
#include <TVector.h>
#include <TGraph.h>
#include "TUnfoldDensity.h"

#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"

#endif

using namespace std;

const Double_t cutdummy= -99999.0;

//---------------------------------------------------
Double_t bifurgaus(Double_t *x, Double_t *par)
//---------------------------------------------------
{
  Double_t bg;
  if (x[0]>par[2]) {
    bg = par[3]*exp(-(x[0]-par[2])*(x[0]-par[2])/2/par[0]/par[0]);
  }
  else {
    bg = par[3]*exp(-(x[0]-par[2])*(x[0]-par[2])/2/par[1]/par[1]);
  }
  return bg;
}


void Louis()
{

  cout << "==================================== TRAIN =====================================" << endl;

  RooUnfoldResponse response (40, -15.0, 18.0);
  double rnd;
  int Nthrows=10000000;
  TF1 *sig = new TF1("bifurgaus",bifurgaus,-20,20,4);
  sig->SetParameters(0.5,3.,5.,1.);
  sig->SetParNames("sigma1","sigma2","mean","norm");
  float x,y,z,t;
  for (int it=0;it!=Nthrows;it++) {
    x = sig->GetRandom(-15.,18.)+gRandom->Gaus(0.,0.5);

    /// Now smear
    y = gRandom->Gaus(0.,4.);
    
    if (x!=cutdummy)
      response.Fill (x+y, x);
    else
      response.Miss (x);
  }

  cout << "==================================== TEST =====================================" << endl;
  TH1D* hTrue= new TH1D ("true", "Test Truth",    40,-15,18);
  TH1D* hMeas= new TH1D ("meas", "Test Measured", 40,-15,18);
  // Test with a Gaussian, mean 0 and width 2.
  for (Int_t i=0; i<100000; i++) {
    Double_t xt = sig->GetRandom(-15.,18.)+gRandom->Gaus(0.,0.5);
    Double_t yt = xt+gRandom->Gaus(0.,4.);
    hTrue->Fill(xt);
    if (x!=cutdummy) hMeas->Fill(yt);
  }

    cout << "==================================== UNFOLD ===================================" << endl;
  RooUnfoldBayes   unfold (&response, hMeas, 4);    // OR
  //RooUnfoldSvd     unfold (&response, hMeas, 20);   // OR
  //RooUnfoldTUnfold unfold (&response, hMeas);
  
  TH1D* hReco= (TH1D*) unfold.Hreco();
  
  unfold.PrintTable (cout, hTrue);
  
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetLineWidth(1.);
  gStyle->SetCanvasDefH(596);
  gStyle->SetCanvasDefW(596);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPalette(1);
  gStyle->SetOptStat();
  
  c0 = new TCanvas("c0", "", 0, 0, 800, 550);
  hTrue->SetLineColor(1);
  hTrue->Draw("SAME");
  hMeas->SetMarkerSize(25.);
  hReco->SetMarkerSize(25.);
  hMeas->Draw("epSAME");
  hReco->Draw("epsame");

}

#ifndef __CINT__
int main () { Louis(); return 0; }  // Main program when run stand-alone
#endif

