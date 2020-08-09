#include"TH1F.h"
#include"TPad.h"
#include <TRandom.h>
#include "TRandom.h"
#include "TRandom3.h"
#include "TRandom2.h"
#include "TClass.h"
#include "TUUID.h"
#include <math.h>
#include <iostream>
//#include <MissingETSmearing.h>
using namespace std;
void smear()
{
    int nbin=150; double xmin=-1,xmax=1;
    double l1 = 0.3;
    double l2 = 0.5;


   TRandom3   m_random3;

//*********************************************************************************

    gRandom->SetSeed(); // initialise sur l'horloge (#include <TRandom.h>)
		  
    TRandom3 *t_rand = new TRandom3();
    t_rand->SetSeed(0); 

    TH1D *h=new TH1D("TW","TW",nbin,xmin,xmax);
    TH1D *hw=new TH1D("TW","TW",nbin,xmin,xmax);
    TH1D *hx=new TH1D("TW","TW",nbin,xmin,xmax);
    TH1D *hxx=new TH1D("TW","TW",nbin,xmin,xmax);

    //*********************** Smearing Gaussiand ****************************
    //***********************************************************************
	
	
    for(int i=1;i<=1000000;i++) //tirages
        {

	 gRandom->SetSeed();

	 double x= gRandom->Gaus(0,l1);

	 double xw= gRandom->Gaus(0,l2);	

         double xxx=m_random3.Gaus(x,0.4);

	 hw->Fill(xw);
	 h->Fill(x);
         hxx->Fill(xxx);}

         TLegend *legendxa=new TLegend(0.12,0.7,0.4,0.87);

         legendxa->AddEntry(h," gaussienne with #sigma = #l1 20  ","lpe");
         legendxa->AddEntry(hw,"gaussienne with #sigma = #l2 25  ","lpe");
         legendxa->AddEntry(hxx,"gaussienne with #sigma = 0.3 after smearing  ","lpe");


//********************************************************************************

h->Draw();
//hx->Draw("same");
hw->Draw("same");
hxx->Draw("same");

hw->SetLineColor(2);
hxx->SetLineColor(3);
legendxa->Draw("same");

}
