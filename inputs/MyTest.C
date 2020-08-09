#define MyTest_cxx
#include "MyTest.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>

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

#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

void MyTest::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyTest.C
//      root> MyTest t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
 
   Long64_t nentries = fChain->GetEntriesFast();

        TFile* output = new TFile("output.root","RECREATE"); 
       
	//**************************************************

	TH1F* h_el_pt  = new TH1F("h_el_pt","pT of electron",100,0,100);
	TH1F* h_el_pt_ap = new TH1F("h_el_pt_ap","pT of electron-ap",100,0,100);
        TH1F* h_el_pt_apm = new TH1F("h_el_pt_apm","pT of electron-ap-",100,0,100);

        TH1F* h_true_pt = new TH1F("h_true_pt","tlep- true - pt",72,29.5,100.5); 
	TH1F* h_true_pt_ap = new TH1F("h_true_pt_ap","tlep- true  pT-ap",72,29.5,100.5);
	TH1F* h_true_pt_apm = new TH1F("h_true_pt_apm","tlep-true pT_ap-",100,0,100);

        TH1F* h_mt = new TH1F("h_mt","masse transverse reco",72,-0.5,141.5); // unit GeV
        TH1F* h_mt_rec = new TH1F("h_mt_rec","masse transverse reco after smearing",72,-0.5,141.5); // unit GeV

        TH1F* h_mt_rec_ap = new TH1F("h_mt_rec_ap","masse transverse reco after smearing_Weight",72,-0.5,141.5); // unit GeV

	TH1F* h_mt_ap = new TH1F("h_mt_ap","masse transverse reco-ap",72,-0.5,141.5);
	TH1F* h_mt_apm  = new TH1F("h_mt_apm","masse transverse reco_ap-",100,0,100);
 

	// ************************* calibration **********************************************


	TH1F* per   = new TH1F("per","recoil perpendiculaire",100,-100,100);
        TH1F* par   = new TH1F("par","recoil parallele",100,-100,100);
        TH1F* px   = new TH1F("px","recoil compo x ",100,-100,100);
        TH1F* py   = new TH1F("py","recoil compo y ",100,-100,100);

	TH1F* pers  = new TH1F("pers","recoil perpendiculaire apres smearing ",100,-100,100);
        TH1F* pars  = new TH1F("pars","recoil paralle�l apeéssmeari",100,-100,100);

	TH1F* upfos = new TH1F("upfos","recoil apres smearing",100,0,100);
        TH1F* upfo = new TH1F("upfo","recoil avant smearing",100,0,100);


	// ************************************************************************************								


        TH1F* h_tmT = new TH1F("h_tmT","masse transvrse true",72,29.5,100.5);	
        TH1F* h_tmT_ap = new TH1F("h_tmT_ap","masse transvrse true-ap",72,29.5,100.5);
	TH1F* h_tmT_apm = new TH1F("h_tmT_apm","masse transvrse true-ap-",72,29.5,100.5);

        TH1F* poids = new TH1F("poids","poid",100,0.8,1.2);

        TH1F* UNF  = new TH1F("UNF"," UNFolding  Without smearing ",72,29.5,100.5);
        TH1F* UNFo  = new TH1F("UNFo"," UNFolding with smearing ",72,29.5,100.5);


        TH1F* PW = new TH1F("PW","PT de w-true ",100,0,100);
        TH1F* PW_ap = new TH1F("PW_ap","PT de w-true-ap ",100,0,100);
        TH1F* PW_apm = new TH1F("PW_apm","PT de w-true-ap- ",100,0,100);

	
        TH1F* PW1 = new TH1F("PW1","PT de W-rec",100,0,100);
        TH1F* PW1_ap = new TH1F("PW1_ap","PT de W-rec-ap",100,0,100);
        TH1F* PW1_apm = new TH1F("PW1_apm","PT de W-rec-ap-",100,0,100);

	
	// *************************************************	


	TH1F* h_el_eta = new TH1F("h_el_eta","eta of electron",50,-3,3);
        TH1F* h_el_phi = new TH1F("h_el_phi","phi of el ",50,-4,4);
        TH1F* h_t_m    = new TH1F("h_t_m","nombre de electrons True",100,0,10);
        TH1F* h_t_n    = new TH1F("h_t_n","nombre de notrons True ",100,0,10);
        TH1F* h_met = new TH1F("h_met","MissingET",50,0,200); 
        TH1F* h_met_phi = new TH1F("h_met_phi","phi of MissingET",50,-4,4);
        TH1F* h_met1 = new TH1F("h_met1","Messing E-T",50,0,200);
        TH1F* h_met1_phi = new TH1F("h_met1_phi","phi de la missing E-T",50,-4,4);
	TH1F* MW = new TH1F("MW","masse du bosons W",100,0,100);
        TH1F* pnt = new TH1F("pnt","impulsion transversal du neutrino",100,0,100);
		
	TH1F* PWW = new TH1F("PWW","PW true avec dressed",100,0,100);
        TH1F* drs   = new TH1F("drs"," dressed ",100,0,100);									
	TH1F* bar  = new TH1F("bar","bare",100,0,100);							
	TH1F* dif = new TH1F("dif","bare-dressed",100,-50,50); 
 	TH2F* MAT = new TH2F("MAT","MATRICE",100,0,150,100,0,100);					
        TH2F* MATA = new TH2F("MATA","MATRICE",100,0,100,100,0,100);
        TH2F* MATAQ = new TH2F("MATAQ","MATRICE",100,0,100,100,0,100);
	TH2F* REPONSE = new TH2F("REPONSE","REPONSE MATRICE",100,0,100,100,0,100);
	TH2D* LAP = new TH2D("LAP","   ",152,-0.5,151.5,202,-0.5,201.5);
        TH2D* LAPP = new TH2D("LAPP","   ",152,-0.5,151.5,202,-0.5,201.5);
		
        TH2D* LAPI = new TH2D("LAPI","   ",102,-0.5,101.5,102,-0.5,101.5);
        TH2D* LAPPI = new TH2D("LAPPI","   ",102,-0.5,101.5,102,-0.5,101.5);

	TH2D* LAPL = new TH2D("LAPL","   ",102,-0.5,101.5,102,-0.5,101.5);
        TH2D* LAPPL = new TH2D("LAPPL","   ",102,-0.5,101.5,102,-0.5,101.5);		

	int dimr = 500 ;
	int dimt = 500 ;
	double  MATR[dimr][dimt] ;
	double  MATRI[dimr][dimt] ;
        double  MATRL[dimr][dimt] ;	
	double VEC[dimt];
	double VECI[dimt];
	double VECL[dimt];
	double VECP[dimt];
	double EFF[dimt];
	double EFFI[dimt];
	double EFFL[dimt];	
	double VER[dimt];
	double REP[dimr][dimt];
 	double REPI[dimr][dimt];
        double REPL[dimr][dimt];	
        double delta_r = 2    ;
        double delta_t = 1  ;
	double delta_rI = 1   ;
	double delta_tI = 1   ;
        double delta_rL = 1   ;
        double delta_tL = 1   ;
	double rec[100];
	int j = 0 ;
        int k = 0 ;
	int jj = 0;
	int kk = 0;
	int jjj = 0;
	int kkk = 0;
	double dd = 0 ;
 	double sum = 0;
	double som = 0;	
	rec[1]=0.441385   ;	
        rec[2]=1.43002   ;
        rec[3]=1.72423   ;
        rec[4]=1.87036   ;
        rec[5]=2.07309   ;
        rec[6]=2.56433   ;
        rec[7]=2.87418   ;
        rec[8]=2.83436   ;
        rec[9]=3.11024   ;
        rec[10]=3.50204   ;
	double norm = 0;

	double yt[72]; 
	double xt[72];
                                for( int i=0; i <= 71 ; i++){
	                        for( int j=0; j <= 71 ; j++){
				MATR[j][j]=0;
                                cout<<"MATR["<<i<<"]["<<j<<"]="<<MATR[i][j]<<endl;
				}}


 Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	 double mT = 0;
	 double mTn = 0;
         double mww = 0;
         double tmT = 0;
	 double tmTn = 0;
	 double param1 = 0;
	 double param2 = 0;
	 double nbins = 100;
	 double plr = 0;
	 double plt = 0;
	 double ptt = 0;
         double ptr = 0;
         double pttt = 0;
         double p = 0;
         double ptrrr = 0;
         double dphi = 0;
         double ptn = 0;
         double phi = 0;
	 double pv = 0;
	 double ptt1 = 0;
	 double ptd = 0;
	 double ptb = 0;
	 double dii = 0;
	 double teta =0;
	 double tetan =0;	
	 double mw2 = pow(80.37,2) ;
         double mw2p = pow(80.37+0.1,2) ;
	 double mw2pm = pow(80.37-0.1,2) ;
         double sei = 0;
         double se = 0;
         double se1 = 0;
	 double se1m = 0;
         double pi=3.14159265 ;
         double lar= 2.085 ;
         double larp = pow(mw2p/mw2,3/2)*lar ;
	 double larpm = pow(mw2pm/mw2,3/2)*lar ;
	 double poid = 0;
	 double poidm = 0;
	 double fact = 0.02167542507*pow(10,-10) ;
	 double tr = 1000 ;	
	 double upar = 0 ;
	 double uparx = 0;
	 double uperx = 0;
	 double uper = 0 ;
	 double upfo_pts = 0;
	 int rr = 0;
	 double ptnr = 0;
	 double phir = 0;
	 double mt_rec = 0 ;
	 double phiu = 0 ;
	 double phiu1 = 0 ;
	 double phiu2 = 0 ;		
	 double fi = 0 ;

if(tlep_born_pt->size() != 0 ){
              ptt=sqrt(pow(tlep_born_pt->at(0)/tr,2)+pow(tneutrino_pt->at(0)/tr,2)+2*(tlep_born_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*cos(tlep_born_phi->at(0)-tneutrino_phi->at(0)));  } 
									
if ( tlep_born_pt->size() == 0 &&  tlep_bare_pt->size() != 0 ){
	      ptt=sqrt(pow(tlep_bare_pt->at(0)/tr,2)+pow(tneutrino_pt->at(0)/tr,2)+2*(tlep_bare_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*cos(tlep_bare_phi->at(0)-tneutrino_phi->at(0))); }	


//i

	//*****************************************************************
								
		   for (int i = 0; i < el_pt->size(); i++){
			
						 plr=el_pt->at(i)/tr;
                                                        h_el_pt->Fill(el_pt->at(i)/tr); //unit GeV
                                                        h_el_pt_ap->Fill(el_pt->at(i)/tr,poid);
                                                        h_el_pt_apm->Fill(el_pt->at(i)/tr,poidm);

                                                        h_el_eta->Fill(el_eta->at(i));
                                                        h_el_phi->Fill(el_phi->at(i));
                                                        h_met->Fill(met/tr); //unit GeV
                                                        h_met_phi->Fill(met_phi);
                                                        h_t_n->Fill(tneutrino_pt->size());
 
 							ptn=sqrt(pow(el_pt->at(i)/tr,2)+pow(upfo_pt/tr,2)+2*(el_pt->at(i)/tr)*(upfo_pt/tr)*cos(el_phi->at(i)-upfo_phi));
                                                        phi=atan2(-((el_pt->at(i)/tr)*sin(el_phi->at(i))+(upfo_pt/tr)*sin(upfo_phi)),-((el_pt->at(i)/tr)*cos(el_phi->at(i))+(upfo_pt/tr)*cos(upfo_phi)));

							h_met1->Fill(ptn);
                                                        h_met1_phi->Fill(phi);
                                                        ptr=sqrt(pow(el_pt->at(0)/tr,2)+pow(ptn,2)+2*(el_pt->at(0)/tr)*(ptn)*cos(el_phi->at(0)-phi));
                                                        mT=sqrt(2*(el_pt->at(0)/tr)*(ptn)*(1-cos(el_phi->at(0)-phi)));// Note the unit
															

							//**************************************************************************
							//**************************************************************************
 
 						  //    phiu=pi-(upfo_phi-(phi-el_phi->at(i)));
                                                  //    phiu=phi;
/*
 						        if(phiu>pi) phiu=phiu-2*pi ;
 						        if(phiu<-pi) phiu=phiu+2*pi;


fi=acos((cos(upfo_phi)*((el_pt->at(i)/tr)*cos(el_phi->at(i)))+sin(upfo_phi)*((el_pt->at(i)/tr)*sin(el_phi->at(i))))/sqrt(pow((el_pt->at(i)/tr)*cos(el_phi->at(i)),2)+pow((el_pt->at(i)/tr)*sin(el_phi->at(i)),2)));
			
*/							//**************************************************************************
							//**************** recoil Calibration **************************************  
					/*		if(fi>(pi/2)) fi=fi-pi ;
                                                        if(fi<-(pi+2)) fi=fi+pi;
					*/
				                        uparx = (upfo_pt/tr)*cos(upfo_phi);
                                                        uperx = (upfo_pt/tr)*sin(upfo_phi);
							px->Fill(uparx);
							py->Fill(uperx);
	
  							rr=int(ptr/5)+1;
							if(rr>=10) rr=10 ;
						//	rr=10;
							gRandom->SetSeed();
							upar =(upfo_pt/tr)*cos(upfo_phi)*cos(el_phi->at(i))+(upfo_pt/tr)*sin(upfo_phi)*sin(el_phi->at(i)) ;							
							double upars=gRandom->Gaus(upar,rec[rr]);
 
 							uper =(upfo_pt/tr)*cos(upfo_phi)*sin(el_phi->at(i))-(upfo_pt/tr)*sin(upfo_phi)*cos(el_phi->at(i)) ;
							double upers=gRandom->Gaus(uper,rec[rr]);
 
//	cout<<ptr<<"                 rr="<<rr<<"          "<<rec[rr]<<"			"<<upfo_pt/tr<<"               "<<"upar="<<upar<<"       "<<"cos="<<cos(fi)<<"       "<<"uper="<<uper<<"     "<<"sin="<<sin(fi)<<endl;
							                                                    
							
							per->Fill(uper);
							par->Fill(upar);
							pers->Fill(upers);
							pars->Fill(upars);							
							upfo_pts=sqrt(pow(upers,2)+pow(upars,2));
							upfos->Fill(upfo_pts);	
							upfo->Fill(upfo_pt/tr);	

							//*************************************************************************
							//************************************************************************* 			

                                        		ptnr=sqrt(pow(el_pt->at(i)/tr,2)+pow(upfo_pts,2)+2*(el_pt->at(i)/tr)*(upfo_pts)*cos(el_phi->at(i)-upfo_phi));
                                                        phir=atan2(-((el_pt->at(i)/tr)*sin(el_phi->at(i))+(upfo_pts)*sin(upfo_phi)),-((el_pt->at(i)/tr)*cos(el_phi->at(i))+(upfo_pts)*cos(upfo_phi)));

                                                    //    cout<<phiu<<"                  "<<phi<<"       "<<phir<<"		"<<ptn<<"	"<<ptnr<<endl;
					                mt_rec=sqrt(2*(el_pt->at(0)/tr)*(ptnr)*(1-cos(el_phi->at(0)-phir)));// Note the unit
							h_mt_rec->Fill(mt_rec);	
							
					

       				        if ( tlep_born_pt->size() != 0 ){ 
													
								sei=2*(tlep_born_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*(cosh(tlep_born_eta->at(0)-tneutrino_eta->at(0))-cos(tlep_born_phi->at(0)-tneutrino_phi->at(0)));
                                				se=fact*pow(mw2,2)*sei/(pow(sei-mw2,2)+sei*lar*lar);
                                				se1=fact*pow(mw2p,2)*sei/(pow(sei-mw2p,2)+sei*larp*larp);
								poid=se1/se;
								se1m=fact*pow(mw2pm,2)*sei/(pow(sei-mw2pm,2)+sei*larpm*larpm);
								poidm=se1m/se ;	           			
	
								poids->Fill(poid);
								plt=tlep_born_pt->at(0)/tr;
	 		    	        			h_true_pt->Fill(tlep_born_pt->at(0)/tr);
	              		        			h_true_pt_ap->Fill((tlep_born_pt->at(0)/tr),poid);
								h_true_pt_apm->Fill((tlep_born_pt->at(0)/tr),poidm);
					
    	                        				h_t_m->Fill(tlep_born_pt->size());
															
	                	        			tmT=sqrt(2*(tlep_born_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*(1-cos(tlep_born_phi->at(0)-tneutrino_phi->at(0))));
	                        				h_tmT->Fill(tmT);
 	                        				h_tmT_ap->Fill(tmT,poid);
                                				h_tmT_apm->Fill(tmT,poidm);
				
				
 	        	                			teta=2*atan(exp(-tlep_born_eta->at(0))) ;
        	        	        			tetan=2*atan(exp(-tneutrino_eta->at(0))) ;
	
		                        			mww=sqrt(2*(tlep_born_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*(cosh(teta-tetan))-cos(tlep_born_phi->at(0)-tneutrino_phi->at(0)));
                	               		 		MW->Fill(mww);
																						
	                        				PW->Fill(ptt);
  	                        				PW_ap->Fill(ptt,poid);
                                				PW_apm->Fill(ptt,poidm); 

								//matrice de migration Pour masse transverse ************************************
	
	 			                        	if(mT<0) j=0;
	 			                        	if(mT>140) j=71;
	                      					if(mT>0 && mT<140){     j=int(mT/delta_r)+1; }

	                     			        	if(tmT<30) k=0;
	                        				if(tmT>100) k=71;
       		                				if(tmT>30 && tmT<100){    k=int(tmT/delta_t)+1-30;     }
 								norm=norm+1;				              		        
								MATR[j][k]=MATR[j][k]+1;
								
								//matrice de migration Pour p-W transverse ************************************
				                                if(ptr<=0) jj=0;
				                                if(ptr>100) jj=101;
                                				if(ptr>0 && ptr<=100){     jj=int(ptr/delta_rI)+1; }
 
 			  	                                if(ptt<=0) kk= 0;
                               					if(ptt>100) kk=101;
                               					if(ptt>0 && ptt<=100){    kk=int(ptt/delta_tI)+1;     }
                                 				MATRI[jj][kk]=MATRI[jj][kk]+1;
					
								//matrice de migration Pour p-Lepton transverse ************************************
								if(plr<=0) jjj=0;
                                				if(plr>100) jjj=101;
                               					if(plr>0 && plr<=100){     jjj=int(plr/delta_rL)+1; }

                               					if(plt<=0) kkk= 0;
                                				if(plt>100) kkk=101;
                                				if(plt>0 && plt<=100){    kkk=int(plt/delta_tL)+1;     }
        				                        MATRL[jjj][kkk]=MATRL[jjj][kkk]+1;}
																	
	

        				if ( tlep_born_pt->size() == 0 &&  tlep_bare_pt->size() != 0 ){              
						
                                				plt=tlep_bare_pt->at(0)/tr;									
		             			        	sei=2*(tlep_bare_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*(cosh(tlep_bare_eta->at(0)-tneutrino_eta->at(0))-cos(tlep_bare_phi->at(0)-tneutrino_phi->at(0)));
		                
								se=fact*pow(mw2,2)*sei/(pow(sei-mw2,2)+sei*lar*lar);
                               					se1=fact*pow(mw2p,2)*sei/(pow(sei-mw2p,2)+sei*larp*larp);
                              					poid=se1/se;
                              					se1m=fact*pow(mw2pm,2)*sei/(pow(sei-mw2pm,2)+sei*larpm*larpm);
                                				poidm=se1m/se ;

	                					poids->Fill(poid);
			        				h_true_pt->Fill(tlep_bare_pt->at(0)/tr);
	                        				h_true_pt_ap->Fill((tlep_bare_pt->at(0)/tr),poid);
                               			 		h_true_pt_apm->Fill((tlep_bare_pt->at(0)/tr),poidm);
											
	                        				h_t_m->Fill(tlep_bare_pt->size());																						
	                        				tmT=sqrt(2*(tlep_bare_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*(1-cos(tlep_bare_phi->at(0)-tneutrino_phi->at(0))));
	                    	    				h_tmT->Fill(tmT);
	                        				h_tmT_ap->Fill(tmT,poid);
                                				h_tmT_apm->Fill(tmT,poidm);

	                        				teta=((tlep_bare_eta->at(0))) ;
	                        				tetan=((tneutrino_eta->at(0))) ;
														
 	                        				mww=sqrt(2*(tlep_bare_pt->at(0)/tr)*(tneutrino_pt->at(0)/tr)*(cosh(teta-tetan))-cos(tlep_bare_phi->at(0)-tneutrino_phi->at(0)));
	                        				MW->Fill(mww);
																							
	                        				PW->Fill(ptt);
	                        				PW_ap->Fill(ptt,poid);
                                				PW_apm->Fill(ptt,poidm);
				
 				
 
								//matrice de migration Pour masse transverse ************************************
	                                                        

								if(mT<0) j=0;
                                                                if(mT>140) j=71;
                                                                if(mT>0 && mT<140){     j=int(mT/delta_r)+1; }

                                                                if(tmT<30) k=0;
                                                                if(tmT>100) k=71;
                                                                if(tmT>30 && tmT<100){    k=int(tmT/delta_t)+1-30;     }
                                                                norm=norm+1;
                                                                MATR[j][k]=MATR[j][k]+1;


                                                                //matrice de migration Pour p-W transverse ************************************
							   //  	  if(ptr<=0) jj=0;
                                                           //     if(ptr>100) jj=101;
                                                                if(ptr>0 && ptr<=100){     jj=int(ptr/delta_rI)+1; }

                                                          //      if(ptt<=0) kk= 0;
                                                          //      if(ptt>100) kk=101;
                                                                if(ptt>0 && ptt<=100){    kk=int(ptt/delta_tI)+1;     }
                                                                MATRI[jj][kk]=MATRI[jj][kk]+1;
                                                                
								//matrice de migration Pour p-Lepton transverse ************************************
								if(plr<=0) jjj=0;
                                                                if(plr>100) jjj=101;
                                                                if(plr>0 && plr<=100){     jjj=int(plr/delta_rL)+1; }

                                                                if(plt<=0) kkk= 0;
                                                                if(plt>100) kkk=101;
                                                                if(plt>0 && plt<=100){    kkk=int(plt/delta_tL)+1;     }
                                                                MATRL[jjj][kkk]=MATRL[jjj][kkk]+1;}

								

		                			PW1->Fill(ptr);
                   	        			PW1_ap->Fill(ptr,poid);
	                        			PW1_apm->Fill(ptr,poidm);
   	                        			MAT->Fill(mT,tmT);
       	        	        			MATA->Fill(ptr,ptt);

                                                        
							h_mt->Fill(mT);
                                                        h_mt_ap->Fill(mT,poid);
							h_mt_rec_ap->Fill(mt_rec,poid);
                                                        h_mt_apm->Fill(mT,poidm);
							}//fin de boucle sur pt lepton
					}//fin de boucle sur les evenements 			
			





					
// Resultat final De la matrice de MIgration ****************************
			cout<<norm<<endl;
		
                        for (int j = 0; j <= 71; j++){
                                 for(int k = 0; k <= 71 ; k++){
					MATR[j][k]=MATR[j][k]/norm;
			                cout<<"MATR["<<j<<"]["<<k<<"]="<<MATR[j][k]<<endl;        
					LAP->Fill(j,k,MATR[j][k]);
						
			                        std::ofstream fichierz("Migration.txt",ios::app);
                                                if( fichierz.is_open() )
                                                {
                                                fichierz << MATR[j][k]*norm << std::endl;
                                                }
                                                fichierz.close();
  
                                              }}		

/*

                        for (int jj = 0; jj < 100; jj++){
                                 for(int kk = 0; kk < 100 ; kk++){
                                        MATRI[jj][kk]=MATRI[jj][kk]/norm;
                                        LAPI->Fill(jj,kk,MATRI[jj][kk]);

					std::ofstream fichi("MigrationPW.txt",ios::app);
                                                if( fichi.is_open() )
                                                {
                                                fichi << MATRI[jj][kk]*norm << std::endl;
                                                }
                                        fichi.close();
	
					}}
										
		
			for (int jj = 0; jj <= 101; jj++){
                                 for(int kk = 0; kk <= 101 ; kk++){
                                        MATRL[jj][kk]=MATRL[jj][kk]/norm;
                                        LAPL->Fill(jj,kk,MATRL[jj][kk]);
	
						std::ofstream fichierzl("MigraLepton.txt",ios::app);
                                                if( fichierzl.is_open() )
                                                {
                                                fichierzl << MATRL[jj][kk]*norm << std::endl;
                                                }
                                                fichierzl.close();
          
                                      }}
	*/									

// Probabilté *p[t<delta] ***************************************************
//double sum = 0;
/*                         for(int k = 0; k <= 201 ; k++){
                                 for (int j = 0; j <= 151; j++){
                                            VEC[k]=MATR[j][k]+VEC[k];}
//			 	    	    cout<<"VEC["<<k<<"]="<<VEC[k]<<endl;
							}

			 for(int k = 0; k <= 101 ; k++){
                                 for (int j = 0; j <= 101; j++){
                                            VECI[k]=MATRI[j][k]+VECI[k];  } }                                                                                         

                         for(int k = 0; k <= 101 ; k++){
                                 for (int j = 0; j <= 101; j++){
                                            VECL[k]=MATRL[j][k]+VECL[k]; }
                                       //         cout<<"VEC["<<k<<"]="<<VECL[k]<<endl;
			}

// Matrice de REPONSE ***************************************************
  			//Masse Transverse ---------------
                     for (int j = 0; j <= 151; j++){
	                                for(int k = 0; k <= 201 ; k++){
				if(VEC[k]!=0) {REP[j][k]=MATR[j][k]/VEC[k];}
				cout<<"REP["<<j<<"]["<<k<<"]="<<REP[j][k]<<endl;	
				}}
			
				//Efficacité
			
				for(int k = 0; k <= 201 ; k++){
                                	 for (int j = 0; j <= 151; j++){
                                        	    EFF[k]=REP[j][k]+EFF[k];  } }

 		     		for (int j = 0; j <= 151; j++){			
					 for(int k = 0; k <= 201 ; k++){
						    REP[j][k]=REP[j][k]*EFF[k];}}
				
				 for (int j = 0; j <= 151; j++){
                                         for(int k = 0; k <= 201 ; k++){
                                                    LAPP->Fill(j,k,REP[j][k]);	

 						std::ofstream fichier("Reponse.txt",ios::app);
                                                if( fichier.is_open() )
                                                {
                                                fichier << REP[j][k] << std::endl;
                                                }
                                                fichier.close();
  
                                              }}
	

			//pT du W ------------------------		
                     for (int j = 0; j <= 101; j++){
                                        for(int k = 0; k <= 101 ; k++){
                                     if(VECI[k]!=0){   REPI[j][k]=MATRI[j][k]/VECI[k];}}}

				//Efficacité

				for(int k = 0; k <= 101 ; k++){
                                         for (int j = 0; j <= 101; j++){
                                                    EFFI[k]=REPI[j][k]+EFFI[k];  } }

                                for (int j = 0; j <= 101; j++){
                                         for(int k = 0; k <= 101 ; k++){
                                                    REPI[j][k]=REPI[j][k]*EFFI[k];}}								

	                        for (int j = 0; j <= 101; j++){   
           	                         for(int k = 0; k <= 101 ; k++){
                   	                            LAPPI->Fill(j,k,REPI[j][k]);}}

			//pT du Lepton ------------------
                     for (int j = 0; j <= 101; j++){
                                        for(int k = 0; k <= 101 ; k++){
                       		            if(VECL[k]!=0){    REPL[j][k]=MATRL[j][k]/VECL[k];}}}

				//Efficacité 

                                for(int k = 0; k <= 101 ; k++){
                                         for (int j = 0; j <= 101; j++){
                                                     EFFL[k]=REPL[j][k]+EFFL[k];  } }

                                for (int j = 0; j <= 101; j++){
                                         for(int k = 0; k <= 101 ; k++){
                                                    REPL[j][k]=REPL[j][k]*EFFL[k];}}

                   	        for (int j = 0; j <= 101; j++){
                                	 for(int k = 0; k <= 101 ; k++){
                                        	    LAPPL->Fill(j,k,REPL[j][k]);}}				
*/
	UNF->Write();
	UNFo->Write();
	px->Write();
	py->Write();
	per->Write();
	par->Write();
	pers->Write();
	pars->Write();
	upfos->Write();
	upfo->Write();
	h_mt_rec->Write();
	h_mt_rec_ap->Write();
	h_el_pt->Write();
	h_el_pt_ap->Write();
	h_el_pt_apm->Write();
	poids->Write();
	h_true_pt->Write();
	h_true_pt_ap->Write();
	h_true_pt_apm->Write();
        h_el_eta->Write();
        h_el_phi->Write();
        h_met->Write();
        h_met_phi->Write();
	h_met1->Write();
	h_met1_phi->Write(); 
	h_mt->Write(); 
	h_mt_ap->Write();
	h_mt_apm->Write();
	h_tmT->Write();	
	h_tmT_ap->Write();
        h_tmT_apm->Write();
	MW->Write();
	PW->Write();
	PW_ap->Write();
        PW_apm->Write();
	PW1->Write();
	PW1_ap->Write();
	PW1_apm->Write();
	PWW->Write();
	drs->Write();
	bar->Write(); 
 	dif->Write();
 	LAP->Write();
 	LAPP->Write();
        LAPI->Write();
        LAPPI->Write(); 
        LAPL->Write();
        LAPPL->Write();        
	MAT->Write();
	MATA->Write();
	MATAQ->Write();
	output->Close();
}
