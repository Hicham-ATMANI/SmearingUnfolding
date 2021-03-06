#include<stdio.h>
#include<iostream>
#include<TCanvas.h>
#include "TObject.h"
#include "TMatrixD.h"
#include "TMatrixT.h"
#include "TVectorD.h"
#include "TRandom3.h"
#include "TDatime.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TF1.h"
#include "TLegend.h"
#include "TROOT.h"
using namespace std; 
Double_t Probability( Double_t deviation, Double_t sigma, Double_t lambda ){
   if( lambda < 0.001 ){ return 1.;}
   if( lambda > 1000. ){ return 0.;}
   //return erf( deviation/(sqrt(2)*sigma*lambda) );
   //return 1-exp(-deviation/(sigma*lambda) );
   return 1-exp(-pow(deviation/(sigma*lambda),2) );
   //return 1-exp(-pow(deviation/(sigma*lambda),3) );
   //return 1-exp(-pow(deviation/(sigma*lambda),4) );
   //return pow(deviation/(sigma*lambda),1)/( 1. + pow(deviation/(sigma*lambda),1) );
   //return pow(deviation/(sigma*lambda),2)/( 1. + pow(deviation/(sigma*lambda),2) );
   //return pow(deviation/(sigma*lambda),3)/( 1. + pow(deviation/(sigma*lambda),3) );
   //return pow(deviation/(sigma*lambda),4)/( 1. + pow(deviation/(sigma*lambda),4) );
   //return 1.;
}


Double_t MCnormalizationCoeff(const TVectorD *vd, const TVectorD *errvd, const TVectorD *vRecmc, const Int_t dim, const Double_t estNknownd, const Double_t Nmc, const Double_t lambda, const TVectorD *soustr_ )
{
   Double_t Nknownd = estNknownd;
   for(Int_t i=0; i<dim; i++){
      if( ((*vd)[i] - (*soustr_)[i] >= 0.) && ((*vRecmc)[i]!=0) ){ 
         // The first test shall also be done when computing Nmc & estNknownd
         Double_t ef = Probability( fabs((*vd)[i]- (*soustr_)[i] - estNknownd/Nmc*(*vRecmc)[i]), sqrt( pow((*errvd)[i],2) + pow(estNknownd/Nmc,2)*fabs((*vRecmc)[i]) ),lambda );
         Nknownd += (1-ef)*( (*vd)[i] - (*soustr_)[i] - estNknownd/Nmc*(*vRecmc)[i] );
      }}
   return Nknownd;
}



Double_t MCnormalizationCoeffIter(const TVectorD *vd, const TVectorD *errvd, const TVectorD *vRecmc, const Int_t dim, const Double_t estNknownd, const Double_t Nmc, const TVectorD *soustr_, Double_t lambdaN = 0., Int_t NiterMax = 1, Int_t messAct = 1 ){

   Double_t Nkd = 0., estNknownd_ = estNknownd;
   for(Int_t i=0; i<NiterMax; i++ ){
      Nkd = MCnormalizationCoeff( vd, errvd, vRecmc, dim, estNknownd_, Nmc, lambdaN, soustr_ );
      //cout << i << "  Nmc = " << Nmc << " estNknownd = " << estNknownd_ << " Nkd = " << Nkd << endl;
      if( fabs((estNknownd_ -  Nkd)/Nkd) < 1e-6 ){ break; }
      if( (i >= NiterMax-1) && (messAct != 0)  ){ cout << "WARNING: a number of " << i+1 << " steps were performed for the normalization " << (estNknownd_ -  Nkd)/Nkd << "  " << (estNknownd -  Nkd)/Nkd << endl;}

      estNknownd_ = Nkd;

   }
   return Nkd;
}

/*
normalizationCoeffIter
   
   TVectorD *reco_mcT = new TVectorD(N);
   Double_t estNkd = 0., Nmc=0., Nkd=0.;
   for(Int_t i=0; i<N; i++){

      //(*soustr_)[i] = 0.;

      (*reco_mcT)[i] = 0.;
      for(Int_t j=0; j<N; j++){
         (*reco_mcT)[i] += ((*A)[i][j]);
      }
      if((*b)[i] - (*soustr_)[i] >= 0.){ 
         Nmc += (*reco_mcT)[i]; 
         estNkd += (*b)[i] - (*soustr_)[i];
      }

      if( ((*reco_mcT)[i]) < 0.){
         cout << "found problematic (*reco_mcT)[i] " << (*reco_mcT)[i] << " " << i << " " << (*b)[i] << endl;
         exit(1);
      }
   }

   for(Int_t k=0; k<2; k++){
      Nkd = MCnormalizationCoeffIter( b, errb,reco_mcT, N, estNkd, Nmc, soustr_ );
      
      for(Int_t i=0; i<N; i++){
         if( (*b)[i] - (*soustr_)[i]>0. && (*reco_mcT)[i]!=0. ){
            Double_t ef = Probability(fabs((*b)[i] - (*soustr_)[i] -Nkd/Nmc*(*reco_mcT)[i]), sqrt(pow((*errb)[i],2)+pow(Nkd/Nmc,2)*fabs((*reco_mcT)[i]) ), lambdaS);
            ((*soustr_)[i]) += (1-ef) * ( (*b)[i] - (*soustr_)[i] - (*reco_mcT)[i]/(Nmc/Nkd));
         }
         else{
            ((*soustr_)[i]) += (*b)[i] - (*soustr_)[i] - (*reco_mcT)[i]/(Nmc/Nkd);
         }
      }
      estNkd = Nkd;
   }

   delete reco_mcT;
}
*/

TVectorD* Unfold( const TVectorD *b, const TVectorD *errb, const TMatrixD *A, Int_t dim, const Double_t lambda, TVectorD *soustr_ )
{
   //ComputeSoustrReco( b, errb, A, dim, soustr_ );

   // compute the mc true and reco spectra and normalize them
   TVectorD *reco_mcN = new TVectorD(dim), *true_mcN = new TVectorD(dim), *unf = new TVectorD( dim );
   Double_t estNkd = 0., Nkd = 0. , Nmc = 0.;
   for(Int_t i=0; i<dim; i++ ){
      (*reco_mcN)[i] = 0.;
      (*true_mcN)[i] = 0.;
      for(Int_t j=0; j<dim; j++ ){
         (*reco_mcN)[i] += (*A)[i][j];
         (*true_mcN)[i] += (*A)[j][i];
      }
      if((*b)[i] - (*soustr_)[i] >= 0.){ 
         Nmc += (*reco_mcN)[i]; 
         estNkd += (*b)[i] - (*soustr_)[i];
      }
   }

   Nkd = MCnormalizationCoeffIter( b, errb, reco_mcN, dim, estNkd, Nmc, soustr_ );

   for(Int_t i=0; i<dim; i++ ){
      (*reco_mcN)[i] *= Nkd/Nmc;
      (*true_mcN)[i] *= Nkd/Nmc;
      ((*unf)[i]) = (*true_mcN)[i] + (*soustr_)[i];
   }

   // compute the prob(j|i) matrix
   TMatrixD *prob = new TMatrixD( dim, dim );
   for(Int_t i=0; i<dim; i++){
      Double_t si = 0.;
      for(Int_t j=0; j<dim; j++){
         si += ((*A)[i][j]);
      }
      for(Int_t j=0; j<dim; j++){
         if( si!=0. )
            ((*prob)[i][j]) = ((*A)[i][j])/si;
         else
            ((*prob)[i][j]) = 0.;
      }

      if( ((*reco_mcN)[i]!=0.)&&((*b)[i]-(*soustr_)[i]>0.)/* &&((*b)[i]>0.)*/ ){
         Double_t ef = Probability( fabs((*b)[i]-(*soustr_)[i]-(*reco_mcN)[i]), sqrt( pow((*errb)[i],2) + Nkd/Nmc*fabs((*reco_mcN)[i])), lambda );
         
         for(Int_t j=0; j<dim; j++){
            ((*unf)[j]) += ef * ((*prob)[i][j])*((*b)[i]-(*soustr_)[i]-(*reco_mcN)[i]);
         }
         ((*unf)[i]) += (1-ef) * ((*b)[i]-(*soustr_)[i]-(*reco_mcN)[i]);
      }
      else{
         ((*unf)[i]) += (*b)[i]-(*soustr_)[i]-(*reco_mcN)[i];
      }
   }

   delete reco_mcN; delete true_mcN; delete prob;
   return unf;
}

void ComputeSoustrTrue( const TMatrixD *A, const TVectorD *unfres, const TVectorD *unfresErr, Int_t N, TVectorD *soustr_, Double_t lambdaS ){
   
   TVectorD *true_mcT = new TVectorD(N), *active = new TVectorD(N);
   Double_t estNkd = 0., Nmc=0., NkUR=0.;
   for(Int_t j=0; j<N; j++){

      //(*soustr_)[j] = 0.;
      (*active)[j] = 1.;

      (*true_mcT)[j] = 0.;
      for(Int_t i=0; i<N; i++){
         (*true_mcT)[j] += ((*A)[i][j]);
      }
      if((*unfres)[j] - (*soustr_)[j] >= 0.){
         Nmc += (*true_mcT)[j];
         estNkd += (*unfres)[j] - (*soustr_)[j];
      }

      if( ((*true_mcT)[j]) < 0.){
         cout << "found problematic (*true_mcT)[j] " << (*true_mcT)[j] << " " << j << " " << (*unfres)[j] << endl;
         exit(1);
      }
   }

   for(Int_t k=0; k<2; k++){
      NkUR = MCnormalizationCoeffIter( unfres, unfresErr, true_mcT, N, estNkd, Nmc, soustr_ );

      //cout << "bin 246 " << (*unfres)[246] << " " << (*soustr_)[246] << " " << (*true_mcT)[246]/(Nmc/NkUR) << " " << (*active)[246]<< endl;
      //cout << "bin 247 " << (*unfres)[247] << " " << (*soustr_)[247] << " " << (*true_mcT)[247]/(Nmc/NkUR) << " " << (*active)[247] << endl;
      
      for(Int_t j=0; j<N; j++){
         if( ((*unfres)[j] - (*soustr_)[j]>0.) && ((*true_mcT)[j]!=0.) && ((*active)[j]>0.) ){
            Double_t ef = Probability(fabs((*unfres)[j] /*- (*soustr_)[j]*/ -NkUR/Nmc*(*true_mcT)[j]), sqrt(pow((*unfresErr)[j],2)+pow(NkUR/Nmc,2)*fabs((*true_mcT)[j]) ), lambdaS);
            ((*soustr_)[j]) /*+*/= (1-ef) * ( (*unfres)[j] /*- (*soustr_)[j]*/ - (*true_mcT)[j]/(Nmc/NkUR));
         }
         else{
            ((*soustr_)[j]) /*+*/= (*unfres)[j] /*- (*soustr_)[j]*/ - (*true_mcT)[j]/(Nmc/NkUR);
            (*active)[j] = -1.;
         }
      }
      estNkd = NkUR;
   }

   //cout << "bin 246 " << (*soustr_)[246] << endl;

   delete true_mcT; delete active;
}

void ModifyMatrix( TMatrixD *Am, const TMatrixD *A, const TVectorD *unfres, const TVectorD *unfresErr, Int_t N, const Double_t lambdaM_, TVectorD *soustr_, const Double_t lambdaS_ ){

   // ComputeSoustrTrue( A, unfres, unfresErr, N, soustr_, lambdaS_ );

   TVectorD *true_mcT = new TVectorD(N);
   Double_t estNkd = 0., Nmc=0., NkUR=0.;
   for(Int_t j=0; j<N; j++){
      (*true_mcT)[j] = 0.;
      for(Int_t i=0; i<N; i++){
         (*true_mcT)[j] += ((*A)[i][j]);
         ((*Am)[i][j]) = ((*A)[i][j]);
      }
      if((*unfres)[j] - (*soustr_)[j] >= 0.){
         Nmc += (*true_mcT)[j];
         estNkd += (*unfres)[j] - (*soustr_)[j];
      }

      if( ((*true_mcT)[j]) < 0.){
         cout << "found problematic (*true_mcT)[j] " << (*true_mcT)[j] << " " << j << " " << (*unfres)[j] << endl;
         exit(1);
      }
   }

   NkUR = MCnormalizationCoeffIter( unfres, unfresErr, true_mcT, N, estNkd, Nmc, soustr_ );

   // cout << "bin 246 " << (*unfres)[246] << " " << (*soustr_)[246] << endl;
   // cout << "bin 247 " << (*unfres)[247] << " " << (*soustr_)[247] << endl;
   // cout << "bin 248 " << (*unfres)[248] << " " << (*soustr_)[248] << endl;

   for(Int_t j=0; j<N; j++){
      if( (*unfres)[j] - (*soustr_)[j]>0. && (*true_mcT)[j]!=0. ){
         Double_t ef = Probability(fabs((*unfres)[j] - (*soustr_)[j] -NkUR/Nmc*(*true_mcT)[j]), sqrt(pow((*unfresErr)[j],2)+pow(NkUR/Nmc,2)*fabs((*true_mcT)[j]) ), lambdaM_);
         for(Int_t i=0; i<N; i++){
            ((*Am)[i][j]) += ef * ( ((*unfres)[j] - (*soustr_)[j])*(Nmc/NkUR) - (*true_mcT)[j]) * ((*A)[i][j])/((*true_mcT)[j]);
         }
      }
   }

   delete true_mcT;
}

TVectorD* CalcValRel1v2( const TVectorD *v1, const TVectorD *v2, Int_t N ){
   TVectorD *Vrel = new TVectorD(N);
   for(Int_t i=0; i<N; i++){
      if( (*v2)[i]!=0. ){
         (*Vrel)[i] = ((*v1)[i]) / fabs((*v2)[i]);
      }
      else{
         (*Vrel)[i] = 0.;
      }
   }
   return Vrel;
}

Double_t ComputeChi2RmcD( const TVectorD* data1, const TVectorD* errdata1, const TMatrixD *Am, Int_t N, const TVectorD *soustr_){
   Double_t chi2RD = 0., NmcM = 0., estNkDmcM = 0., NkDmcM;
   TVectorD *siM = new TVectorD(N);
   Int_t i, j;
   for(i=0;i<N;i++){
      (*siM)[i]=0.;
      for(j=0;j<N;j++){
         (*siM)[i] += (*Am)[i][j];
      }
      if((*data1)[i] - (*soustr_)[i] >= 0.){
         NmcM += (*siM)[i];
         estNkDmcM += (*data1)[i] - (*soustr_)[i];
      }
   }
   NkDmcM = MCnormalizationCoeffIter( data1, errdata1, siM, N, estNkDmcM, NmcM, soustr_ );
   for(i=0;i<N;i++){
      if( (*errdata1)[i] != 0. )
         chi2RD += pow((*data1)[i] - (*soustr_)[i] - (*siM)[i]*NkDmcM/NmcM ,2)/(pow((*errdata1)[i],2) + (*siM)[i]*pow(NkDmcM/NmcM,2));// /(N-1);
   }
   delete siM;
   return chi2RD;
}

Double_t Unfold_iterations(const Int_t N, const TVectorD* data1, const TVectorD* errdata1, TMatrixD *A, const Int_t Nsteps, const Double_t lambdaM, const Double_t lambdaU, const TVectorD* unfres1, Int_t &NstepsOpt, Double_t &chi2trueMin, const TVectorD* true_data1, const Double_t lambdaS ){
   // Iterations with modified A 
   Int_t i, j, k;
   TMatrixD *Am = new TMatrixD( N, N );
   TMatrixD *Acp = new TMatrixD( *A );
   TVectorD *unfres_ = new TVectorD( N ), *soustr = new TVectorD( N );
   for( i=0; i<N; i++ ){ 
      (*unfres_)[i] = (*unfres1)[i];
      (*soustr)[i] = 0.;
   }
   Double_t chi2RD, chi2RDmin, chi2true;
   for(k=0; k<Nsteps; k++){
      //ComputeSoustrTrue( Acp, unfres_, errdata1, N, soustr );
      ModifyMatrix( Am, Acp, unfres_, errdata1, N, lambdaM, soustr, lambdaS );
      delete unfres_;
      chi2RD = ComputeChi2RmcD( data1, errdata1, Am, N, soustr);

      // UNFOLDING
      unfres_ = Unfold( data1, errdata1, Am, N, lambdaU, soustr );
      chi2true = 0.;
      for(j=0;j<N;j++){
         if( (*errdata1)[j] != 0. )
            chi2true += pow((*unfres_)[j] /*- (*soustr)[j]*/ - (*true_data1)[j],2)/pow((*errdata1)[j],2);
      }
      if( k== 0 ){
         chi2trueMin = chi2true;
         chi2RDmin = chi2RD;
         NstepsOpt = 1;
      }
      else{
         if(chi2true < chi2trueMin){
            NstepsOpt = k+1;
            chi2trueMin = chi2true;
            if(chi2RD < chi2RDmin){
               chi2RDmin = chi2RD;
            }
         }
      }

      for(i=0;i<N;i++){
         for(j=0;j<N;j++){
            //(*Acp)[i][j] = (*Am)[i][j];
         }
      }
   }

   delete Am;
   delete Acp;
   delete unfres_;
   delete soustr;
   return chi2RDmin;
}



void myunfoldData(){

//..BABAR style from RooLogon.C in workdir -> !!! Changed !!!
TStyle *babarStyle= new TStyle("BABAR","BaBar approved plots style");

// use plain black on white colors
babarStyle->SetFrameBorderMode(0);
babarStyle->SetCanvasBorderMode(0);
babarStyle->SetPadBorderMode(0);
babarStyle->SetPadColor(0);
babarStyle->SetCanvasColor(0);
babarStyle->SetStatColor(0);
//babarStyle->SetFillColor(0);

// set the paper & margin sizes
babarStyle->SetPaperSize(20,26);
babarStyle->SetPadTopMargin(0.05);
babarStyle->SetPadRightMargin(0.05);
babarStyle->SetPadBottomMargin(0.16);
babarStyle->SetPadLeftMargin(0.12);

// use large Times-Roman fonts
babarStyle->SetTextFont(20);
babarStyle->SetTextSize(0.06);
babarStyle->SetLabelFont(20,"x");
babarStyle->SetLabelFont(20,"y");
babarStyle->SetLabelFont(20,"z");
babarStyle->SetLabelSize(0.05,"x");
babarStyle->SetTitleSize(0.07,"x");
babarStyle->SetLabelSize(0.05,"y");
babarStyle->SetTitleSize(0.07,"y");
babarStyle->SetLabelSize(0.05,"z");
babarStyle->SetTitleSize(0.07,"z");

 babarStyle->SetNdivisions(5,"x");
 babarStyle->SetNdivisions(5,"y");

// use bold lines and markers
//babarStyle->SetMarkerStyle(20);
babarStyle->SetHistLineWidth(1.85);
babarStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

// get rid of X error bars and y error bar caps
babarStyle->SetErrorX(0.001);

// do not display any of the standard histogram decorations
babarStyle->SetOptTitle(0);
babarStyle->SetOptStat(0);
babarStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
babarStyle->SetPadTickX(1);
babarStyle->SetPadTickY(1);

gROOT->SetStyle("BABAR"); 
gStyle->SetPalette(1,0); 

   Double_t lambdaL = 1.5;
   Double_t lambdaUmin = 0.; 
   Double_t lambdaMmin = 0.; 
   Double_t lambdaS = 0.; 
   Int_t NstepsOptMin = 10;

   Int_t N=72, i, j; 
   Double_t r;

   TMatrixD *A = new TMatrixD( N, N ), *Am = new TMatrixD( N, N ), *Ax4 = new TMatrixD( N/4, N/4 ), *Amx4 = new TMatrixD( N/4, N/4 ), *Amx4_m_Ax4 = new TMatrixD( N/4, N/4 );
   TVectorD  *data = new TVectorD( N ), *errdata = new TVectorD( N ), *reco_mc = new TVectorD( N ), *true_mc = new TVectorD( N ), *databx10 = new TVectorD(N/10), *true_mcbx10 = new TVectorD(N/10);

   FILE *f;
   f = fopen( "Files/Detmat.txt", "r" );

   // read the detector response matrix
   for( i=0; i<N; i++ ){
      for( j=0; j<N; j++ ){
         ((*A)[j][i]) = 0.;
         (*Ax4)[i/4][j/4] = 0.;
         (*Amx4)[i/4][j/4] = 0.;
      }
   }
   for( i=0; i<N; i++ ){
      for( j=0; j<N; j++ ){
         fscanf( f, "%lf", &r ); // NORMAL position of the elements NOT in LL format
            ((*A)[i][j]) = r;
      }
   }
   fclose( f );

   f = fopen( "Files/DataReco.txt", "r" );
  // read the data
   for( i=0; i<N; i++ ){
      fscanf( f, "%lf", &r );
      ((*data)[i]) = r;
//      (*errdata)[i] =sqrt(r);
   }
   fclose( f );


    f = fopen( "Files/DataReco_err.txt", "r" );
 //   read the data_erro
    for( i=0; i<N; i++ ){
    fscanf( f, "%lf", &r );
    (*errdata)[i] = r;
    }
    fclose( f );	


   TH2D* A_mcH = new TH2D( *A );
   TCanvas *canUnf1 = new TCanvas( "FoldingMatrix_mcN", "FoldingMatrix_mcN", 400, 30, 400, 400 );
   canUnf1->cd();
   //canUnf1->SetLogz();
   A_mcH->Draw( "LEGO" );

   // compute the mc true and reco spectra
   for( i=0; i<N; i++ ){
      (*reco_mc)[i] = 0.;
      (*true_mc)[i] = 0.;
      for( j=0; j<N; j++ ){
         (*reco_mc)[i] += (*A)[i][j];
         (*true_mc)[i] += (*A)[j][i];
         (*Ax4)[i/4][j/4] += ( (*A)[i][j] )/16.;
      }
   }
   TH2D* Ax4_mcH = new TH2D( *Ax4 );
   TCanvas *canUnf1x4 = new TCanvas( "FoldingMatrixx4_mcN", "FoldingMatrixx4_mcN", 400, 30, 400, 400 );
   canUnf1x4->cd();
   canUnf1x4->SetLogz();
   Ax4_mcH->SetXTitle( "True" );
   Ax4_mcH->SetYTitle( "Measured" );
   Ax4_mcH->Draw( "LEGO" );

   // statistics on the data and MC
   Double_t Nunfres = 0.;
   Double_t Nd = 0.;
   Double_t Ntmc = 0.;
   Double_t Nrmc = 0.;
   for( i=0; i<N; i++ ){
      Nd += (*data)[i];
      Ntmc += (*true_mc)[i];
      Nrmc += (*reco_mc)[i];
   }
   cout << "N data = " << Nd << endl;
   cout << "N true MC = " << Ntmc << endl;
   cout << "N reco MC = " << Nrmc << endl;

   TH1D* dataH = new TH1D( *data );
   for( i=0; i<N; i++ ){
      // dataH->SetBinError(i+1,(*errdata)[i]);
   }
   dataH->SetLineColor( 2 );

   TH1D* dataTrueH = new TH1D( *data );
   f = fopen( "Files/DataTrue.txt", "r" );
   // read the data
   for( i=0; i<N; i++ ){
      fscanf( f, "%lf", &r );
      dataTrueH->SetBinContent(i+1,r);}


   fclose( f );

   TH1D* reco_mcH = new TH1D( *reco_mc ); 
   TH1D* true_mcH = new TH1D( *true_mc ); 
   for(i=0;i<N;i++){ 
      reco_mcH->SetBinContent( i+1, reco_mcH->GetBinContent(i+1)*Nd/Nrmc ); reco_mcH->SetBinError( i+1, sqrt(reco_mcH->GetBinContent(i+1))*Nd/Nrmc ); 
      true_mcH->SetBinContent( i+1, true_mcH->GetBinContent(i+1)*Nd/Ntmc ); true_mcH->SetBinError( i+1, sqrt(true_mcH->GetBinContent(i+1))*Nd/Ntmc ); 
   }
   TCanvas *canUnf3 = new TCanvas( "MCspectra", "MCspectra", 400, 30, 400, 400 );
   canUnf3->cd();
   true_mcH->SetLineColor( 4 );
   true_mcH->Draw( "E" );
   reco_mcH->SetLineColor( 2 );
   reco_mcH->Draw( "ESAME" );
   dataH->Draw( "same" );

   TVectorD *dif2 = new TVectorD(N), *dif1 = new TVectorD(N), *dif2bx10 = new TVectorD(N/10), *dif1bx10 = new TVectorD(N/10), *soustr = new TVectorD(N);
   for(i=0;i<N/10;i++){
      (*dif2bx10)[i] = 0.;
      (*dif1bx10)[i] = 0.;
      (*databx10)[i] = 0.;
      (*true_mcbx10)[i] = 0.;
   }
   for(i=0;i<N;i++){
      (*soustr)[i] = 0.;
      (*dif2)[i] = (*data)[i] - ((*reco_mc)[i]) * (Nd/Nrmc);
      (*dif1)[i] = ((*true_mc)[i] - (*reco_mc)[i]) * (Nd/Nrmc);
      (*dif2bx10)[i/10] += (*data)[i] - ((*reco_mc)[i]) * (Nd/Nrmc);
      (*dif1bx10)[i/10] += ((*true_mc)[i] - (*reco_mc)[i]) * (Nd/Nrmc);
      (*databx10)[i/10] += (*data)[i];
      (*true_mcbx10)[i/10] += (*true_mc)[i];
   }
   TH1D* dif1H = new TH1D( *dif1 );
   TH1D* dif2H = new TH1D( *dif2 );
   TH1D* dif1bx10H = new TH1D( *dif1bx10 );
   TH1D* dif2bx10H = new TH1D( *dif2bx10 );
   TVectorD *dif1Rel = CalcValRel1v2( dif1, true_mc, N );
   TVectorD *dif2Rel = CalcValRel1v2( dif2, data, N );
   TVectorD *dif1Relbx10 = CalcValRel1v2( dif1bx10, true_mcbx10, N/10 );
   TVectorD *dif2Relbx10 = CalcValRel1v2( dif2bx10, databx10, N/10 );
   TVectorD *potentialImpIter = new TVectorD(N), *potentialImpIterbx10 = new TVectorD(N/10);
   for(i=0;i<N;i++){
      (*potentialImpIter)[i] = ((*dif1Rel)[i])*(Nrmc/Nd) * ((*dif2Rel)[i]);
   }
   for(i=0;i<N/10;i++){
      (*potentialImpIterbx10)[i] = ((*dif1Relbx10)[i])*(Nrmc/Nd) * ((*dif2Relbx10)[i]);
   }

   Int_t lCw = 1000;
   TCanvas *canPotImp = new TCanvas( "potentialImpIter", "potentialImpIter", 400, 30, lCw, 400);
   canPotImp->cd();
   TH1D *potentialImpIterH = new TH1D( *potentialImpIter );
   potentialImpIterH->Draw();
   TCanvas *canPotImpbx10 = new TCanvas( "potentialImpIterbx10", "potentialImpIterbx10", 400, 30, lCw, 400);
   canPotImpbx10->cd();
   TH1D *potentialImpIterbx10H = new TH1D( *potentialImpIterbx10 );
   potentialImpIterbx10H->Draw();

   TCanvas *canDif1bx10 = new TCanvas( "Dif1bx10", "Dif1bx10", 400, 30, 400, 400);
   canDif1bx10->cd();
   dif2bx10H->SetLineColor( 8 );
   dif2bx10H->Draw( );
   dif1bx10H->SetLineColor( 4 );
   dif1bx10H->Draw( "same" );

   // UNFOLDING 
   //   ModifyMatrix( Am, A, data, errdata, N, lambdaMmin, soustr, lambdaS ); 
   TVectorD* unfres1 = Unfold( data, errdata, A, N, lambdaL, soustr );

   TH1D* unfres1H = new TH1D( *unfres1 );
   /*TCanvas *canUR1 = new TCanvas( "Unfolding1", "Unfolding1", 400, 30, 1000, 400);
   canUR1->cd();
   unfres1H->Draw();
   dataH->Draw( "ESAME" );*/

   TVectorD *UR1_m_data = new TVectorD( N ), *UR1_m_true_mc = new TVectorD( N ), *UR1_m_databx10 = new TVectorD( N/10 ), *UR1_m_true_mcbx10 = new TVectorD( N/10 );   

   //Double_t variance = 0., varianceRD = 0.;
   for(i=0;i<N/10;i++){
      (*UR1_m_databx10)[i] = 0.;
      (*UR1_m_true_mcbx10)[i] = 0.;
   }
   for(i=0;i<N;i++){
      Nunfres += (*unfres1)[i];

      (*UR1_m_data)[i] = (*unfres1)[i] - (*data)[i];
      (*UR1_m_true_mc)[i] = (*unfres1)[i] - ((*true_mc)[i]) * (Nd/Ntmc);
      (*UR1_m_databx10)[i/10] += (*unfres1)[i] - (*data)[i];
      (*UR1_m_true_mcbx10)[i/10] += (*unfres1)[i] - ((*true_mc)[i]) * (Nd/Ntmc);
      //varianceRD += ((*data)[i] - ((*reco_mc)[i]) * (Nd/Nrmc))*((*data)[i] - ((*reco_mc)[i]) * (Nd/Nrmc))/(N-1);
   }
   //cout << "sigma D~Rmc = " << sqrt(varianceRD) << endl;

   cout << "N unfolding result = " << Nunfres << endl;

   TH1D* errdataH = new TH1D( *errdata );
   TH1D* merrdataH = new TH1D( *errdata ); merrdataH->Scale(-1.);
      TCanvas *canTest_1 = new TCanvas( "test_1", "test_1", 400, 30, lCw, 400);
      canTest_1->cd();
      dif1H->Draw();
      dif1H->SetLineStyle( 1 );
      dif1H->SetLineColor( 8 );
      dif2H->Draw("same");
      errdataH->Draw("same"); errdataH->SetLineStyle( 2 );
      merrdataH->Draw("same"); merrdataH->SetLineStyle( 2 );
      Double_t deltaY = 3*0.05 + 0.015;
      TLegend* legend = new TLegend( 1 - canTest_1->GetRightMargin() - 0.2, 1 - canTest_1->GetTopMargin() - deltaY, 
                                     1 - canTest_1->GetRightMargin() - 0.025, 1 - canTest_1->GetTopMargin() - 0.015 );
      legend->SetMargin( 0.4 );
      legend->SetTextSize( 0.05 );
      legend->SetBorderSize(0);
      legend->SetFillColor( 0 );
      legend->Draw("same");
      legend->AddEntry(dif1H,"tMC-r","L");
      legend->AddEntry(dif2H,"d-r","L");
      legend->AddEntry(errdataH,"data errors","L");

   TCanvas *canTest1 = new TCanvas( "test1", "test1", 400, 30, lCw, 400);
   canTest1->cd();
   TH1D* UR1_m_dataH = new TH1D( *UR1_m_data );
   UR1_m_dataH->SetLineColor( 8 );
   TH1D* UR1_m_true_mcH = new TH1D( *UR1_m_true_mc );
   UR1_m_true_mcH->SetLineColor( 4 );
   UR1_m_true_mcH->Draw();
   UR1_m_dataH->Draw("same");	

   TCanvas *canTest1bx10 = new TCanvas( "test1bx10", "test1bx10", 400, 30, 400, 400);
   canTest1bx10->cd();
   TH1D* UR1_m_true_mcbx10H = new TH1D( *UR1_m_true_mcbx10 );
   UR1_m_true_mcbx10H->SetLineColor( 8 );
   UR1_m_true_mcbx10H->Draw( );
   TH1D* UR1_m_databx10H = new TH1D( *UR1_m_databx10 );
   UR1_m_databx10H->Draw( "same" );

   //************************* Iterate ************************************************************************
   TVectorD *unfres2 = new TVectorD( N ), *impIter = new TVectorD( N ), *siM = new TVectorD(N), *dif3 = new TVectorD(N);
   for( i=0; i<N; i++ ){ 
      (*unfres2)[i] = (*unfres1)[i];
   }
   
   for(Int_t k=0; (k<NstepsOptMin); k++){
      ModifyMatrix( Am, A, unfres2, errdata, N, lambdaMmin, soustr, lambdaS );
      Double_t chi2RD = 0.;
      Double_t NmcM = 0., estNkDmcM = Nd, NkDmcM;
      for(i=0;i<N;i++){
         estNkDmcM -= (*soustr)[i];
         (*siM)[i]=0.;
         for(j=0;j<N;j++){
            (*siM)[i] += (*Am)[i][j];
         }
         NmcM += (*siM)[i];
      }
      
      NkDmcM = MCnormalizationCoeffIter( data, errdata, siM, N, estNkDmcM, NmcM, soustr);
      
      for(i=0;i<N;i++){
         (*dif3)[i] = (*data)[i] - (*siM)[i]*NkDmcM/NmcM;
         if( (*errdata)[i] != 0. ){
            chi2RD += pow((*dif3)[i] - (*soustr)[i],2)/(pow((*errdata)[i],2) + (*siM)[i]*pow(NkDmcM/NmcM,2));// /(N-1);
         }
      }

      // UNFOLDING
      delete unfres2;
      
      unfres2 = Unfold( data, errdata, Am, N, lambdaUmin, soustr );
      
       cout << " lambdaMmin = " << lambdaMmin << " lambdaU( " << k << " ) = " << lambdaUmin << " chi2 D~Rmc = " << chi2RD << NkDmcM << endl;

   }

  TH1D* unfres2H = new TH1D( *unfres2 );
   /*TCanvas *canUR2 = new TCanvas( "Unfolding2", "Unfolding2", 400, 30, lCw, 400);
   canUR2->cd();
   unfres2H->Draw();
   dataH->Draw( "ESAME" );*/



   TCanvas *canRDnSteps = new TCanvas( "data-reco Nsteps", "data-reco Nsteps", 400, 30, lCw, 400);
   canRDnSteps->cd();
   dif2H->SetMaximum( 200. ); 
   dif2H->SetMinimum( -200. ); 
   dif2H->SetLineColor( 4 );
   dif2H->Draw();
   TH1D* dif3H = new TH1D( *dif3 );
   dif3H->SetLineColor(8);
   dif3H->SetLineWidth(2);
   dif3H->SetLineStyle(3);
   dif3H->Draw("same");
   TH1D* soustrH = new TH1D( *soustr );
   soustrH->SetLineStyle(4);
   soustrH->SetLineWidth(2);
   soustrH->Draw("same");
   errdataH->SetLineColor(2); merrdataH->SetLineColor(2);
   errdataH->Draw("same"); merrdataH->Draw("same");
   deltaY = 4*0.05 + 0.015;
   TLegend* legendRDnS = new TLegend( 1 - canRDnSteps->GetRightMargin() - 0.2, 1 - canRDnSteps->GetTopMargin() - deltaY, 
                                      1 - canRDnSteps->GetRightMargin() - 0.025, 1 - canRDnSteps->GetTopMargin() - 0.015 );
   legendRDnS->SetMargin( 0.4 );
   legendRDnS->SetTextSize( 0.05 );
   legendRDnS->SetBorderSize(0);
   legendRDnS->SetFillColor( 0 );
   legendRDnS->Draw("same");
   legendRDnS->AddEntry(dif2H,"d-r","L");
   legendRDnS->AddEntry(dif3H,"d-r_{m}","L");
   legendRDnS->AddEntry(soustrH,"B^{u}","L");
   legendRDnS->AddEntry(errdataH,"data errors","L");

        cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;


   TVectorD *dif3Rel = CalcValRel1v2( dif3, data, N );
   TVectorD *soustrRel = CalcValRel1v2( soustr, data, N );
   TVectorD *errdataRel = CalcValRel1v2( errdata, data, N );
   TCanvas *canRDnStepsRel = new TCanvas( "data-reco Nsteps Rel", "data-reco Nsteps Rel", 400, 30, lCw, 400);
   canRDnStepsRel->cd();
   TH1D* dif2RelH = new TH1D( *dif2Rel );
   dif2RelH->SetLineColor( 4 );
   dif2RelH->Draw();
   TH1D* dif3RelH = new TH1D( *dif3Rel );
   dif3RelH->SetLineColor(8);
   dif3RelH->SetLineWidth(2);
   dif3RelH->SetLineStyle(3);
   dif3RelH->Draw("same");
   TH1D* soustrRelH = new TH1D( *soustrRel );
   soustrRelH->SetLineStyle(2);
   soustrRelH->Draw("same");
   TH1D* errdataRelH = new TH1D( *errdataRel );
   TH1D* merrdataRelH = new TH1D( *errdataRel ); merrdataRelH->Scale(-1.);
   errdataRelH->SetLineColor(2); merrdataRelH->SetLineColor(2);
   errdataRelH->Draw("same"); merrdataRelH->Draw("same");
   deltaY = 4*0.05 + 0.015;
   TLegend* legendRDnSRel = new TLegend( 1 - canRDnStepsRel->GetRightMargin() - 0.2, 1 - canRDnStepsRel->GetTopMargin() - deltaY, 
                                         1 - canRDnStepsRel->GetRightMargin() - 0.025, 1 - canRDnStepsRel->GetTopMargin() - 0.015 );
   legendRDnSRel->SetMargin( 0.4 );
   legendRDnSRel->SetTextSize( 0.05 );
   legendRDnSRel->SetBorderSize(0);
   legendRDnSRel->SetFillColor( 0 );
   legendRDnSRel->Draw("same");
   legendRDnSRel->AddEntry(dif2RelH,"(d-r)/|d|","L");
   legendRDnSRel->AddEntry(dif3RelH,"(d-r_{m})/|d|","L");
   legendRDnSRel->AddEntry(soustrRelH,"B^{u}/|d|","L");
   legendRDnSRel->AddEntry(errdataRelH,"(data errors)/|d|","L");


   for( i=0; i<N; i++ ){ 
      (*impIter)[i] = (*unfres2)[i] - (*unfres1)[i];
   }
   TCanvas *canimpIter = new TCanvas( "impIter Nsteps", "impIter Nsteps", 400, 30, lCw, 400);
   canimpIter->cd();
   UR1_m_dataH->SetMaximum( 300. ); 
   UR1_m_dataH->SetMinimum( -300. ); 
   TH1D* impIterH = new TH1D( *impIter );
   impIterH->SetLineWidth(2);
   impIterH->SetLineStyle(3);
   impIterH->Draw();
   UR1_m_dataH->Draw("same");
   errdataH->Draw("same"); merrdataH->Draw("same");
   deltaY = 3*0.05 + 0.015;
   TLegend* legendimpIter = new TLegend( 1 - canimpIter->GetRightMargin() - 0.2, 1 - canimpIter->GetTopMargin() - deltaY, 
                                         1 - canimpIter->GetRightMargin() - 0.025, 1 - canimpIter->GetTopMargin() - 0.015 );
   legendimpIter->SetMargin( 0.4 );
   legendimpIter->SetTextSize( 0.05 );
   legendimpIter->SetBorderSize(0);
   legendimpIter->SetFillColor( 0 );
   legendimpIter->Draw("same");
   legendimpIter->AddEntry(UR1_m_dataH,"u_{1}-d","L");
   legendimpIter->AddEntry(impIterH,"u_{2}-u_{1}","L");
   legendimpIter->AddEntry(errdataH,"data errors","L");

   TVectorD *impIterRel = CalcValRel1v2( impIter, data, N );
   TVectorD *UR1_m_dataRel = CalcValRel1v2( UR1_m_data, data, N );
   TCanvas *canimpIterRel = new TCanvas( "impIter Nsteps Rel", "impIter Nsteps Rel", 400, 30, lCw, 400);
   canimpIterRel->cd();
   TH1D* UR1_m_dataRelH = new TH1D( *UR1_m_dataRel );
   UR1_m_dataRelH->SetLineColor( 8 );
   TH1D* impIterRelH = new TH1D( *impIterRel );
   impIterRelH->SetLineWidth(2);
   impIterRelH->SetLineStyle(3);
   UR1_m_dataRelH->Draw();
   impIterRelH->Draw("same");
   errdataRelH->Draw("same"); merrdataRelH->Draw("same");
   deltaY = 3*0.05 + 0.015;
   TLegend* legendimpIterRel = new TLegend( 1 - canimpIterRel->GetRightMargin() - 0.2, 1 - canimpIterRel->GetTopMargin() - deltaY, 
                                            1 - canimpIterRel->GetRightMargin() - 0.025, 1 - canimpIterRel->GetTopMargin() - 0.015 );
   legendimpIterRel->SetMargin( 0.4 );
   legendimpIterRel->SetTextSize( 0.05 );
   legendimpIterRel->SetBorderSize(0);
   legendimpIterRel->SetFillColor( 0 );
   legendimpIterRel->Draw("same");
   legendimpIterRel->AddEntry(UR1_m_dataRelH,"(u_{1}-d)/|d|","L");
   legendimpIterRel->AddEntry(impIterRelH,"(u_{2}-u_{1})/|d|","L");
   legendimpIterRel->AddEntry(errdataRelH,"(data errors)/|d|","L");
        cout <<"1111 $$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

      TCanvas *canImpIterRel_large = new TCanvas( "ImpIterRel_large", "ImpIterRel_large", 400, 30, lCw, 400);
      canImpIterRel_large->cd();
///****************** j'ai chanagé 40 a 100 ------> aprés 100  a 200	
      Int_t Nlarge = 72;
      TVectorD *impIter_large = new TVectorD( N/Nlarge ), *tot_data = new TVectorD( N/Nlarge ), *err_data1_large = new TVectorD( N/Nlarge );
      for(i=0;i<N/Nlarge;i++){
         (*impIter_large)[i] = 0.;
         (*tot_data)[i] = 0.;
         (*err_data1_large)[i] = 0.;
      }
      for(i=0;i<N;i++){
         (*impIter_large)[i/Nlarge] += (*impIter)[i];
         (*tot_data)[i/Nlarge] += (*data)[i];
         (*err_data1_large)[i/Nlarge] += pow( (*errdata)[i], 2 );
      }
      for(i=0;i<N/Nlarge;i++){
          cout << i << "  " << ((*impIter_large)[i])/((*tot_data)[i]) << endl;
         (*err_data1_large)[i] = sqrt( (*err_data1_large)[i] );
      }
      TVectorD *impIter_largeRel = CalcValRel1v2( impIter_large, tot_data, N/Nlarge );
      TVectorD *err_data1_Rel_large = CalcValRel1v2( err_data1_large, tot_data, N/Nlarge );
      TH1D* err_data1_Rel_largeH = new TH1D( *err_data1_Rel_large );
      TH1D* merr_data1_Rel_largeH = new TH1D( *err_data1_Rel_large ); merr_data1_Rel_largeH->Scale(-1.);
      err_data1_Rel_largeH->SetLineColor(2); merr_data1_Rel_largeH->SetLineColor(2);
      err_data1_Rel_largeH->Draw(); merr_data1_Rel_largeH->Draw( "same" );
      TH1D* impIter_largeRelH = new TH1D( *impIter_largeRel );
      impIter_largeRelH->Draw( "same" );

        cout <<"222 $$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

   TH2D* AmH = new TH2D( *Am );
   TCanvas *canUnfAm = new TCanvas( "FoldingMatrix_modified", "FoldingMatrix_modified", 400, 30, 400, 400 );
   canUnfAm->cd();
   //canUnfAm->SetLogz();
   AmH->Draw( "LEGO" );

   for(i=0;i<N;i++){
      for(j=0;j<N;j++){
         (*Amx4)[i/4][j/4] += ( (*Am)[i][j] )/16.;
      }
   }
   TCanvas *canAmx4 = new TCanvas( "Amx4 Nsteps", "Amx4 Nsteps", 400, 30, 400, 400);
   canAmx4->cd();
   canAmx4->SetLogz();
   TH2D *Amx4H = new TH2D( *Amx4 );
   Amx4H->SetXTitle( "True" );
   Amx4H->SetYTitle( "Measured" );
   Amx4H->Draw( "LEGO" );
        cout <<"33333 $$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

   for(i=0;i<N/4;i++){
      for(j=0;j<N/4;j++){
         (*Amx4_m_Ax4)[i][j] = fabs( (*Amx4)[i][j] - (*Ax4)[i][j] );
      }
   }
   TH2D *Amx4_m_Ax4H = new TH2D( *Amx4_m_Ax4 );
   TCanvas *canUnfAmModif = new TCanvas( "FoldingMatrix_AbsModification", "FoldingMatrix_AbsModification", 400, 30, 400, 400 );

   canUnfAmModif->cd();
   //canUnfAmModif->SetLogz();
   Amx4_m_Ax4H->Draw( "LEGO" );

   //***********************************************************************************************************

   // make toys
   Int_t Ntoy = 1000;
   // TRandom rnd(0);
   // TRandom3* rnd = new TRandom3( (new TDatime())->GetTime() ); 
   TRandom3* rnd = new TRandom3( 155305 ); 
   cout << "Loop with " << Ntoy << " toys." << endl;
   if( Ntoy>0 ){

      TVectorD /**data0toy = new TVectorD( N ), *errdata0toy = new TVectorD( N ),*/ *datatoy = new TVectorD( N ), *errdatatoy = new TVectorD( N ), *soustrtoy = new TVectorD( N );
      TVectorD *impIter_rel_large = new TVectorD( N/Nlarge ), *avtoy1_large = new TVectorD( N/Nlarge ), *avtoy_large = new TVectorD( N/Nlarge );
      TVectorD *avtoy1 = new TVectorD( N ), *avtoy = new TVectorD( N );
      TMatrixD *covtoy1 = new TMatrixD( N, N ), *covtoy = new TMatrixD( N, N ), *corrtoy = new TMatrixD( N, N );
      TMatrixD *mToys1 = new TMatrixD( Ntoy, N ), *mToys = new TMatrixD( Ntoy, N );
      TMatrixD *Atoy = new TMatrixD( N, N );
      TH2D* unfDistribH = new TH2D("UnfDistrib", "UnfDistrib", N, 0., N, 300, 0., 30000.);
      for( i=0; i<N; i++ ){
         (*avtoy1)[i] = 0.;
         (*avtoy)[i] = 0.;
      }
      for( i=0; i<N/Nlarge; i++ ){
         (*avtoy1_large)[i] = 0.;
         (*avtoy_large)[i] = 0.;
      }

      Int_t Nlambda_toyTN = 300; 
      Double_t lambda_toyTNmin = 0., deltaL_toyTN = 0.1;
      TH2D* NormImpDistribH = new TH2D("NormImpDistrib", "NormImpDistrib", Nlambda_toyTN, lambda_toyTNmin, lambda_toyTNmin + Nlambda_toyTN*deltaL_toyTN, 200, -20000., 20000.);
      TH1D *min_toyTNH = new TH1D( "min_toyTNH", "min_toyTNH", Nlambda_toyTN, lambda_toyTNmin, lambda_toyTNmin + Nlambda_toyTN*deltaL_toyTN ), 
           *max_toyTNH = new TH1D( "max_toyTNH", "max_toyTNH", Nlambda_toyTN, lambda_toyTNmin, lambda_toyTNmin + Nlambda_toyTN*deltaL_toyTN ); 
         //*min_toy0TNH = new TH1D( "min_toy0TNH", "min_toy0TNH", Nlambda_toyTN, lambda_toyTNmin, lambda_toyTNmin + Nlambda_toyTN*deltaL_toyTN ), 
         //*max_toy0TNH = new TH1D( "max_toy0TNH", "max_toy0TNH", Nlambda_toyTN, lambda_toyTNmin, lambda_toyTNmin + Nlambda_toyTN*deltaL_toyTN );
      TVectorD *min_toyTN = new TVectorD(Nlambda_toyTN), *max_toyTN = new TVectorD(Nlambda_toyTN);//, *min_toy0TN = new TVectorD(Nlambda_toyTN), *max_toy0TN = new TVectorD(Nlambda_toyTN);
      TVectorD *dif3toy = new TVectorD(N);
      for( int toy=0; toy<Ntoy; toy++ ){
         // generate toy data and matrix
         
         Double_t /*Nd0Toy = 0.,*/ NdToy = 0.;
         for(i=0;i<N;i++){
            //            (*datatoy)[i] = rnd->Gaus((*data)[i], (*errdata)[i]);
            (*datatoy)[i] = rnd->Poisson((*data)[i]);
            (*errdatatoy)[i] = (*errdata)[i];
            NdToy += (*datatoy)[i];
            //(*data0toy)[i] = rnd->Gaus((*data)[i], (*errdata)[i]); // one can add a bias to these data (for normalization test)
            //(*errdata0toy)[i] = (*errdata)[i];
            //Nd0Toy += (*data0toy)[i];
            (*soustrtoy)[i] = 0.;
            for( j=0; j<N; j++ ){
               // *A must not be modified by the iterations !!! (use Am)
               (*Atoy)[i][j] = rnd->Poisson( (*A)[i][j] );
            }
         }

         // UNFOLDING
         TVectorD* unfrestoy = Unfold( datatoy, errdatatoy, Atoy, N, lambdaL, soustrtoy );
         for( i=0; i<N; i++ ){
            (*mToys1)[toy][i] = (*unfrestoy)[i];
            (*avtoy1)[i] += (*unfrestoy)[i]/Ntoy;
            (*avtoy1_large)[i/Nlarge] += (*unfrestoy)[i]/Ntoy;
         }

         // *** it toy ****************************************************************************************************
         for( Int_t k=0; k<NstepsOptMin; k++){
            //ComputeSoustrTrue( Atoy, unfrestoy, errdatatoy, N, soustrtoy );
            ModifyMatrix( Am, Atoy, unfrestoy, errdatatoy, N, lambdaMmin, soustrtoy, lambdaS );
            Double_t chi2RD = 0.;
            Double_t NmcM = 0., estNkDmcM = 0., NkDmcM;
            for(i=0;i<N;i++){
               (*siM)[i]=0.;
               for(j=0;j<N;j++){
                  (*siM)[i] += (*Am)[i][j];
               }
               if((*datatoy)[i] - (*soustrtoy)[i] >= 0.){
                  estNkDmcM += (*datatoy)[i] - (*soustrtoy)[i];
                  NmcM += (*siM)[i];
               }
            }

            NkDmcM = MCnormalizationCoeffIter( datatoy, errdatatoy, siM, N, estNkDmcM, NmcM, soustrtoy );

            for(i=0;i<N;i++){
               (*dif3toy)[i] = (*datatoy)[i] - (*siM)[i]*NkDmcM/NmcM;
               if( (*errdatatoy)[i] != 0. )
                  chi2RD += pow((*dif3toy)[i] - (*soustrtoy)[i],2)/(pow((*errdatatoy)[i],2) + (*siM)[i]*pow(NkDmcM/NmcM,2));// /(N-1);
            }

            // UNFOLDING
            delete unfrestoy;
            unfrestoy = Unfold( datatoy, errdatatoy, Am, N, lambdaUmin, soustrtoy );
         }

         //*****************************************************************************************************************

         for( i=0; i<N; i++ ){
            (*mToys)[toy][i] = (*unfrestoy)[i];
            unfDistribH->Fill( i, (*unfrestoy)[i] );
            (*avtoy)[i] += (*unfrestoy)[i]/Ntoy;
            (*avtoy_large)[i/Nlarge] += (*unfrestoy)[i]/Ntoy;
         }
         delete unfrestoy;

         //************ test parameter lambdaN for normalization by iterations ************************************
         TVectorD *reco_mc_toyTN = new TVectorD(N), *soustr_toyTN = new TVectorD(N);
         Double_t estNkd_toyTN = 0., Nkd_toyTN = 0. , Nmc_toyTN = 0.; //, estNkd0_toyTN = 0., Nkd0_toyTN = 0., Nmc0_toyTN = 0.;
         for(Int_t in = 0; in < N; in++ ){
            (*reco_mc_toyTN)[in] = 0.;
            (*soustr_toyTN)[in] = 0.; // shall be 0 for this test
            for(Int_t jn = 0; jn < N; jn++ ){
               (*reco_mc_toyTN)[in] += (*Atoy)[in][jn];
            }
            if((*datatoy)[in] - (*soustr_toyTN)[in] >= 0.){
               Nmc_toyTN += (*reco_mc_toyTN)[in];
               estNkd_toyTN += (*datatoy)[in] - (*soustr_toyTN)[in];
            }
            /*if((*data0toy)[in] - (*soustr_toyTN)[in] >= 0.){
               Nmc0_toyTN += (*reco_mc_toyTN)[in];
               estNkd0_toyTN += (*data0toy)[in] - (*soustr_toyTN)[in];
            }*/
         }

         Double_t lambda_toyTN = lambda_toyTNmin;
         for(Int_t in = 0; in < Nlambda_toyTN; in++){
            Nkd_toyTN = MCnormalizationCoeffIter( datatoy, errdatatoy, reco_mc_toyTN, N, estNkd_toyTN, Nmc_toyTN, soustr_toyTN, lambda_toyTN, 5, 0 );
            NormImpDistribH->Fill( lambda_toyTN+deltaL_toyTN/2., estNkd_toyTN - Nkd_toyTN );
            //Nkd0_toyTN = MCnormalizationCoeffIter( data0toy, errdata0toy, reco_mc_toyTN, N, estNkd0_toyTN, Nmc0_toyTN, soustr_toyTN, lambda_toyTN, 50, 0 );
            if( toy == 0 ){
               (*min_toyTN)[in] = (estNkd_toyTN - Nkd_toyTN)/estNkd_toyTN;
               (*max_toyTN)[in] = (estNkd_toyTN - Nkd_toyTN)/estNkd_toyTN;
               //(*min_toy0TN)[in] = (estNkd0_toyTN - Nkd0_toyTN)/estNkd0_toyTN;
               //(*max_toy0TN)[in] = (estNkd0_toyTN - Nkd0_toyTN)/estNkd0_toyTN;
            }
            else{
               if( (estNkd_toyTN - Nkd_toyTN)/estNkd_toyTN < (*min_toyTN)[in] ){ (*min_toyTN)[in] = (estNkd_toyTN - Nkd_toyTN)/estNkd_toyTN; }
               if( (estNkd_toyTN - Nkd_toyTN)/estNkd_toyTN > (*max_toyTN)[in] ){ (*max_toyTN)[in] = (estNkd_toyTN - Nkd_toyTN)/estNkd_toyTN; }
               //if( (estNkd0_toyTN - Nkd0_toyTN)/estNkd0_toyTN < (*min_toy0TN)[in] ){ (*min_toy0TN)[in] = (estNkd0_toyTN - Nkd0_toyTN)/estNkd0_toyTN; }
               //if( (estNkd0_toyTN - Nkd0_toyTN)/estNkd0_toyTN > (*max_toy0TN)[in] ){ (*max_toy0TN)[in] = (estNkd0_toyTN - Nkd0_toyTN)/estNkd0_toyTN; }
            }
            lambda_toyTN += deltaL_toyTN;
         }
         delete reco_mc_toyTN; delete soustr_toyTN; 

      }
      for(Int_t in = 0; in < Nlambda_toyTN; in++){
         min_toyTNH->SetBinContent( in+1, (*min_toyTN)[in] );
         max_toyTNH->SetBinContent( in+1, (*max_toyTN)[in] );
         //min_toy0TNH->SetBinContent( in+1, (*min_toy0TN)[in] );
         //max_toy0TNH->SetBinContent( in+1, (*max_toy0TN)[in] );
      }
      delete min_toyTN; delete max_toyTN; //delete min_toy0TN; delete max_toy0TN;

      for( i=0; i<N; i++ ){
         for( j=i; j<N; j++ ){
            (*covtoy1)[i][j] = 0.;
            (*covtoy)[i][j] = 0.;
            for( int toy=0; toy<Ntoy; toy++ ){
               if( (*A)[i][j] != 0. || (*A)[j][i] != 0. || i==j ){
                  (*covtoy1)[i][j] += ( (*mToys1)[toy][i] - (*avtoy1)[i] )*( (*mToys1)[toy][j] - (*avtoy1)[j] )/Ntoy;
               }
               (*covtoy)[i][j] += ( (*mToys)[toy][i] - (*avtoy)[i] )*( (*mToys)[toy][j] - (*avtoy)[j] )/Ntoy;
            }
            (*covtoy1)[j][i] = (*covtoy1)[i][j];
            (*covtoy)[j][i] = (*covtoy)[i][j];
         }
      }
      for( i=0; i<N; i++ ){
         for( j=0; j<N; j++ ){
            if( (*covtoy)[i][i]!=0. && (*covtoy)[j][j]!=0. ){
               (*corrtoy)[i][j] = (*covtoy)[i][j] / sqrt( (*covtoy)[i][i] * (*covtoy)[j][j] ); 
            }
            else{
               (*corrtoy)[i][j] = 0.; 
            }
         }
      } 

      TH1D* avHtoy = new TH1D( *avtoy );
      TH1D *unfErrH = new TH1D( *avtoy ), *unf1ErrH = new TH1D( *avtoy ); //temp content
      for( i=0; i<N; i++ ){
         unfres1H->SetBinError(i+1,sqrt( (*covtoy1)[i][i] ));
         unfres2H->SetBinError(i+1,sqrt( (*covtoy)[i][i] ));
         unf1ErrH->SetBinContent(i+1,sqrt( (*covtoy1)[i][i] ));
         unfErrH->SetBinContent(i+1,sqrt( (*covtoy)[i][i] ));
      }

      TCanvas *canTestUnf = new TCanvas( "TestUnfoldingN", "TestUnfoldingN", 400, 30, lCw, 400 );
      canTestUnf->cd();
      //canToyUnf->SetLogy();
      dataH->Draw( "E" );
      avHtoy->SetLineColor( 8 );
      avHtoy->Draw( );
      unfres2H->Draw( "SAME" );

      TCanvas *canUR1toy = new TCanvas( "Unfolding1toyErr", "Unfolding1toyErr", 400, 30, lCw, 400);
      canUR1toy->cd();
      unfres1H->SetMarkerStyle( 26 ); 
      unfres1H->SetMarkerSize( 0.4 );
      unfres1H->Draw( "e" );
      dataH->Draw( "esame" );
      deltaY = 2*0.05 + 0.015;
      TLegend* legend1 = new TLegend( 1 - canUR1toy->GetRightMargin() - 0.2, 1 - canUR1toy->GetTopMargin() - deltaY, 
                                      1 - canUR1toy->GetRightMargin() - 0.025, 1 - canUR1toy->GetTopMargin() - 0.015 );
      legend1->SetMargin( 0.4 );
      legend1->SetTextSize( 0.05 );
      legend1->SetBorderSize(0);
      legend1->SetFillColor( 0 );
      legend1->Draw("same");
      legend1->AddEntry(dataH,"d","P");
      legend1->AddEntry(unfres1H,"u_{1}","P");

   TCanvas *canToyUnfN = new TCanvas( "UnfoldingNtoyErr", "UnfoldingNtoyErr", 400, 30, lCw, 400);
   canToyUnfN->cd();
   dataTrueH->SetLineColor( 4 );
   unfres2H->SetMarkerStyle( 26 ); 
   unfres2H->SetMarkerSize( 0.4 );
   dataH->Draw( "e" );
   dataTrueH->Draw( "same" );
   unfres2H->Draw( "esame" ) ;

   deltaY = 2*0.05 + 0.015;
   TLegend* legendN1 = new TLegend( 1 - canToyUnfN->GetRightMargin() - 0.2, 1 - canToyUnfN->GetTopMargin() - deltaY, 
                                    1 - canToyUnfN->GetRightMargin() - 0.025, 1 - canToyUnfN->GetTopMargin() - 0.015 );
   legendN1->SetMargin( 0.4 );
   legendN1->SetTextSize( 0.05 );
   legendN1->SetBorderSize(0);
   legendN1->SetFillColor( 0 );
   legendN1->Draw("same");
   legendN1->AddEntry(dataH,"d","P");
   legendN1->AddEntry(unfres2H,"u_{n}","P");

      TCanvas *corToyUnf1_ = new TCanvas( "corToysUnfolding1_", "corToysUnfolding1_", 400, 30, 400, 400 );
      corToyUnf1_->cd();
      corToyUnf1_->SetLogz();
      TH2D *cov1H = new TH2D( *covtoy1 );
      cov1H->Draw( "colz" );

      
      f = fopen( "Results/UnfoldedCov.txt", "w" );
      for( i=0; i<N; i++ ){
        for( j=0; j<N; j++ ){
          fprintf( f, "%lf \n", (*covtoy)[i][j] );
        }
      }
      fclose( f );
      

      f = fopen( "Results/Unfolded.txt", "w" );
      for( i=0; i<N; i++ ){
         fprintf( f, "%lf \n", (*unfres2)[i] );
      }
      fclose( f );

      f = fopen( "Results/Unfolded_err.txt", "w" );
      for( i=0; i<N; i++ ){
         fprintf( f, "%lf \n", sqrt( (*covtoy)[i][i] ) );
      }
      fclose(f);

      TCanvas *corToyUnfN_ = new TCanvas( "corToysUnfoldingN_", "corToysUnfoldingN_", 400, 30, 400, 400 );
      corToyUnfN_->cd();
      corToyUnfN_->SetLogz();
      TH2D *covH = new TH2D( *covtoy );
      covH->Draw( "colz" );

      TCanvas *corrToyUnfN_ = new TCanvas( "corrToysUnfoldingN_", "corrToysUnfoldingN_", 400, 30, 400, 400 );
      corrToyUnfN_->cd();
      //      corrToyUnfN_->SetLogz();
      TH2D *corrH = new TH2D( *corrtoy );
      corrH->Draw( "colz" );

      TCanvas *corToyUnfN = new TCanvas( "corToysUnfoldingN", "corToysUnfoldingN", 400, 30, lCw, 400 );
      corToyUnfN->cd();
      unf1ErrH->SetLineColor( 8 );
      
      unf1ErrH->Draw( );
      unfErrH->Draw( "same" );
      errdataH->Draw("same");
	

      TCanvas *canUnfToyDistrib = new TCanvas( "UnfToyDistrib", "UnfToyDistrib", 400, 30, 400, 400);
      canUnfToyDistrib->cd();
      canUnfToyDistrib->SetLogz();
      unfDistribH->Draw( "LEGO");

      TCanvas *canNormImpDistrib = new TCanvas( "NormImpDistrib", "NormImpDistrib", 400, 30, 400, 400);
      canNormImpDistrib->cd();
      //canNormImpDistrib->SetLogz();
      NormImpDistribH->Draw( "LEGO");

      TCanvas *canNormImpLimits = new TCanvas( "NormImpLimits", "NormImpLimits", 400, 30, 400, 400);
      canNormImpLimits->cd();
      /*min_toy0TNH->SetLineColor( 8 );
      max_toy0TNH->SetLineColor( 8 );
      min_toy0TNH->Draw();
      max_toy0TNH->Draw( "SAME" );*/
      //min_toyTNH->SetLineStyle( 3 );
      //max_toyTNH->SetLineStyle( 3 );
      min_toyTNH->Draw( "SAME" );
      max_toyTNH->Draw( "SAME" );
      deltaY = 2*0.08 + 0.025;
      TLegend* legendNIL = new TLegend( 1 - canNormImpLimits->GetRightMargin() - 0.75,  1 - canNormImpLimits->GetTopMargin() - deltaY, 
                                        1 - canNormImpLimits->GetRightMargin() - 0.025, 1 - canNormImpLimits->GetTopMargin() - 0.025 );
      legendNIL->SetMargin( 0.4 );
      legendNIL->SetTextSize( 0.05 );
      legendNIL->SetBorderSize(0);
      legendNIL->SetFillColor( 0 );
      legendNIL->Draw("same");
      //legendNIL->AddEntry(min_toy0TNH,"Improvement no bkg.","L");
      legendNIL->AddEntry(min_toyTNH,"Improvement limits","L");
      legendNIL->Draw("same");

      for( i=0; i<N/Nlarge; i++ ){
         (*impIter_rel_large)[i] = ( (*avtoy_large)[i] - (*avtoy1_large)[i] )/( (*tot_data)[i] );
         cout << i << "   " << (*impIter_rel_large)[i] << endl;
      }

      delete datatoy;
      delete avtoy;
      delete covtoy;
      delete mToys;
      delete Atoy;

   }


   //************************* Test the Parameters **********************************************************************

   TMatrixD *ATest = new TMatrixD( N, N ), *probFoldTest = new TMatrixD( N, N ), *AmTest = new TMatrixD( N, N );
   TVectorD  *dataTest = new TVectorD( N ), *errdataTest = new TVectorD( N ), *biasTest = new TVectorD( N ), *true_dataTest = new TVectorD( N ), *soustrTest = new TVectorD( N ), *reco_mcTest = new TVectorD( N );
   TMatrixD *AfoldTest = new TMatrixD( *A );
   for( j=0; j<N; j++ ){
      (*dataTest)[j] = 0.;
      (*biasTest)[j] = 1.*((*dif2)[j]);
      (*true_dataTest)[j] = ((*true_mc)[j]) * (Nd/Nrmc) + (*biasTest)[j];
      (*errdataTest)[j] = (*errdata)[j];
      for( i=0; i<N; i++ ){
         ////(*AfoldTest)[i][j] = rnd->Poisson( (*A)[i][j] );
         (*ATest)[i][j] = rnd->Poisson( (*A)[i][j] ); // for Unfolding
      }
      (*reco_mcTest)[j] = 0.;
   }
   for( j=0; j<N; j++ ){
      Double_t sj = 0.;
      for( i=0; i<N; i++ ){
         sj += ((*AfoldTest)[i][j]);
         (*reco_mcTest)[i] += (*ATest)[i][j];
      }
      for( i=0; i<N; i++ ){
         if( sj!=0. ){
            ((*probFoldTest)[i][j]) = ((*AfoldTest)[i][j])/sj;
            (*dataTest)[i] += ((*probFoldTest)[i][j]) * ((*true_dataTest)[j]);
         }
         else{
            ((*probFoldTest)[i][j]) = 0.;
            if( i==j )
               (*dataTest)[j] += (*true_dataTest)[j];
         }
      }
   }
   for( i=0; i<N; i++ ){
      (*dataTest)[i] = rnd->Poisson((*dataTest)[i]);
   }

   // ************ UNFOLDING & SCAN Test *******************************************************************
   Double_t chi2true_Test = 0., chi2RD_Test = 0.;
   Double_t NunfresTest = 0., NdTest = 0., NrmcTest = 0.;
   TVectorD *UR1_Test_m_true_data = new TVectorD( N );

   for(i=0;i<N;i++){
      (*soustrTest)[i] = 0.;
      NdTest += (*dataTest)[i];
      NrmcTest += (*reco_mcTest)[i];
   }
   TVectorD* unfresTest = Unfold( dataTest, errdataTest, ATest, N, lambdaL, soustrTest );
   TH1D* unfresTestH = new TH1D( *unfresTest );

   for(i=0;i<N;i++){
      NunfresTest += (*unfresTest)[i];
      (*UR1_Test_m_true_data)[i] = (*unfresTest)[i] - (*true_dataTest)[i];
      if( (*errdataTest)[i] != 0. ){
         chi2true_Test += pow((*UR1_Test_m_true_data)[i] /*- (*soustrTest)[i]*/,2)/pow((*errdataTest)[i],2);
         chi2RD_Test += pow((*dataTest)[i] - (*soustrTest)[i] - ((*reco_mcTest)[i]) * (NdTest/NrmcTest),2)/(pow((*errdataTest)[i],2) + ((*reco_mcTest)[i]) * pow(NdTest/NrmcTest,2) );
      }
   }
   cout << "chi2true_Test UR~Bias = " << chi2true_Test << "   chi2 D~Rmc Test = " << chi2RD_Test << "    NunfresTest = " << NunfresTest << endl;

   // Scan for iterations with modified A 
   Int_t ilambda = 0, NlambdaU = 1, NlambdaM = 1, NstepsOptTest;
   Int_t NstepsOptMin_Test;
   Double_t chi2RD_TestMin = chi2RD_Test, chi2true_TestMin = chi2true_Test, lambdaMmin_Test, lambdaUmin_Test;
   TMatrixD* lambdaMat_Test = new TMatrixD(NlambdaM, NlambdaU);
   TMatrixD* lambdaMatRD_Test = new TMatrixD(NlambdaM, NlambdaU);
   TMatrixD* lambdaNStMat_Test = new TMatrixD(NlambdaM, NlambdaU);

   Double_t lambdaMstep = 0.2, lambdaUstep = 0.2, lambdaMstart = 0., lambdaUstart = 0.;
   for( Double_t lambdaM = lambdaMstart; ilambda < NlambdaM; ilambda++, lambdaM += lambdaMstep ){
      Int_t jlambda = 0;
      for(  Double_t lambdaU = lambdaUstart; jlambda < NlambdaU; jlambda++, lambdaU += lambdaUstep ){
         chi2RD_Test = Unfold_iterations( N, dataTest, errdataTest, ATest, 200, lambdaM, lambdaU, unfresTest, NstepsOptTest, chi2true_Test, true_dataTest, lambdaS );
         (*lambdaMatRD_Test)[ilambda][jlambda] = chi2RD_Test;
         (*lambdaMat_Test)[ilambda][jlambda] = chi2true_Test;
         (*lambdaNStMat_Test)[ilambda][jlambda] = NstepsOptTest;
         if( chi2true_Test < chi2true_TestMin ){
            chi2true_TestMin = chi2true_Test;
            lambdaMmin_Test = lambdaM;
            lambdaUmin_Test = lambdaU;
            NstepsOptMin_Test = NstepsOptTest;
            chi2RD_TestMin = chi2RD_Test;
         }
         cout << "lambdaM = " << lambdaM << "; lambdaU= " << lambdaU << " chi2RD_TestMin = " << chi2RD_Test << " chi2true_TestMin = " << chi2true_Test << endl;
      }
   }
   TCanvas *canLambdaRD_Test = new TCanvas( "chi2RD_Test_Flambda", "chi2RD_Test_Flambda", 400, 30, 400, 400);
   canLambdaRD_Test->cd();
   TH2D* lambdaRDH_Test = new TH2D(*lambdaMatRD_Test);
   lambdaRDH_Test->SetTitleOffset( 1.2, "X" );
   lambdaRDH_Test->SetXTitle( "\\lambda_{U}         " );
   lambdaRDH_Test->SetYTitle( "         \\lambda_{M}" );
   lambdaRDH_Test->GetXaxis()->SetLimits(lambdaUstart,lambdaUstart+NlambdaU*lambdaUstep);
   lambdaRDH_Test->GetYaxis()->SetLimits(lambdaMstart,lambdaMstart+NlambdaM*lambdaMstep);
   lambdaRDH_Test->Draw("LEGO");
   TCanvas *canLambdaTrue_Test = new TCanvas( "chi2true_Test_Flambda", "chi2true_Test_Flambda", 400, 30, 400, 400);
   canLambdaTrue_Test->cd();
   TH2D* lambdaTrueH_Test = new TH2D(*lambdaMat_Test);
   lambdaTrueH_Test->SetTitleOffset( 1.2, "X" );
   lambdaTrueH_Test->SetXTitle( "\\lambda_{U}         " );
   lambdaTrueH_Test->SetYTitle( "         \\lambda_{M}" );
   lambdaTrueH_Test->GetXaxis()->SetLimits(lambdaUstart,lambdaUstart+NlambdaU*lambdaUstep);
   lambdaTrueH_Test->GetYaxis()->SetLimits(lambdaMstart,lambdaMstart+NlambdaM*lambdaMstep);
   lambdaTrueH_Test->Draw("LEGO");
   TCanvas *canNStLambda_Test = new TCanvas( "NStFlambda_Test", "NStFlambda_Test", 400, 30, 400, 400);
   canNStLambda_Test->cd();
   TH2D* lambdaNStH_Test = new TH2D(*lambdaNStMat_Test);
   lambdaNStH_Test->SetTitleOffset( 1.2, "X" );
   lambdaNStH_Test->SetXTitle( "\\lambda_{U}         " );
   lambdaNStH_Test->SetYTitle( "         \\lambda_{M}" );
   lambdaNStH_Test->GetXaxis()->SetLimits(lambdaUstart,lambdaUstart+NlambdaU*lambdaUstep);
   lambdaNStH_Test->GetYaxis()->SetLimits(lambdaMstart,lambdaMstart+NlambdaM*lambdaMstep);
   lambdaNStH_Test->Draw("LEGO");

   cout << "Scan result: lambdaMmin_Test = " << lambdaMmin_Test << " lambdaUmin_Test = " << lambdaUmin_Test << " NstepsOptMin_Test " << NstepsOptMin_Test << " chi2RD_TestMin = " << chi2RD_TestMin << " chi2true_TestMin = " << chi2true_TestMin << endl;

 
   /*
   delete A; delete A1; delete data_m;
   delete reco_mc; delete true_mc;
   delete UR_m_trueMCn;
   delete recMC_m_trueMC; delete recMC_m_trueMCrel;
   delete data;
   delete prob1;
   delete dif1; delete dif2;
   delete Am; delete siM;
   delete unfres1;


   delete reco_mcH;
   */
}
