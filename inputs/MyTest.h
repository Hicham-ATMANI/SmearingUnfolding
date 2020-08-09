//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 10 14:46:56 2017 by ROOT version 6.04/14
// from TTree treeAnaWZ/Tree for NI calibration
// found on file: outT.root
//////////////////////////////////////////////////////////

#ifndef MyTest_h
#define MyTest_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

const Int_t kMaxjet_sys = 1;
   const Int_t kMaxmu_syspt = 1;
   const Int_t kMaxmu_syssf = 1;
   const Int_t kMaxmu_systrigsf = 1;
   const Int_t kMaxel_syspt = 1;
   const Int_t kMaxel_syssf = 1;
   const Int_t kMaxel_systrigsf = 1;
   const Int_t kMaxmet_sys = 1;
   const Int_t kMaxmet_phi_sys = 1;
   const Int_t kMaxupfo_pt_sys = 1;
   const Int_t kMaxupfo_eta_sys = 1;
   const Int_t kMaxupfo_phi_sys = 1;
   const Int_t kMaxupfo_e_sys = 1;
   const Int_t kMaxupfovor_pt_sys = 1;
   const Int_t kMaxupfovor_eta_sys = 1;
   const Int_t kMaxupfovor_phi_sys = 1;
   const Int_t kMaxupfovor_e_sys = 1;
   const Int_t kMaxupfovorsp_pt_sys = 1;
   const Int_t kMaxupfovorsp_eta_sys = 1;
   const Int_t kMaxupfovorsp_phi_sys = 1;
   const Int_t kMaxupfovorsp_e_sys = 1;

class MyTest {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        EventWeight;
   Double_t        RunNumber;
   Double_t        EvtNumber;
   Double_t        npv;
   Double_t        npuv;
   Double_t        zvertex;
   Double_t        average_mu;
   Double_t        jet_n;
   vector<float>   *jet_pt;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   Int_t           jet_sys_;
   Float_t         jet_sys_first[kMaxjet_sys];   //[jet_sys_]
   string          jet_sys_second[kMaxjet_sys];
   Double_t        mu_n;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_sf;
   vector<float>   *mu_charge;
   vector<float>   *mu_trigMatch;
   Int_t           mu_syspt_;
   Float_t         mu_syspt_first[kMaxmu_syspt];   //[mu_syspt_]
   string          mu_syspt_second[kMaxmu_syspt];
   Int_t           mu_syssf_;
   Float_t         mu_syssf_first[kMaxmu_syssf];   //[mu_syssf_]
   string          mu_syssf_second[kMaxmu_syssf];
   vector<float>   *mu_trigmceff;
   vector<float>   *mu_trigsf;
   Int_t           mu_systrigsf_;
   Float_t         mu_systrigsf_first[kMaxmu_systrigsf];   //[mu_systrigsf_]
   string          mu_systrigsf_second[kMaxmu_systrigsf];
   Double_t        el_n;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_phi;
   vector<float>   *el_sf;
   vector<float>   *el_charge;
   vector<float>   *el_trigMatch;
   vector<float>   *el_trigmceff;
   vector<float>   *el_trigsf;
   Int_t           el_syspt_;
   Float_t         el_syspt_first[kMaxel_syspt];   //[el_syspt_]
   string          el_syspt_second[kMaxel_syspt];
   Int_t           el_syssf_;
   Float_t         el_syssf_first[kMaxel_syssf];   //[el_syssf_]
   string          el_syssf_second[kMaxel_syssf];
   Int_t           el_systrigsf_;
   Float_t         el_systrigsf_first[kMaxel_systrigsf];   //[el_systrigsf_]
   string          el_systrigsf_second[kMaxel_systrigsf];
   Float_t         met;
   Float_t         met_phi;
   Float_t         sumet;
   Int_t           met_sys_;
   Float_t         met_sys_first[kMaxmet_sys];   //[met_sys_]
   string          met_sys_second[kMaxmet_sys];
   Int_t           met_phi_sys_;
   Float_t         met_phi_sys_first[kMaxmet_phi_sys];   //[met_phi_sys_]
   string          met_phi_sys_second[kMaxmet_phi_sys];
   Bool_t          passTrigger_el;
   Bool_t          passTrigger_mu;
   Double_t        HadRecoil;
   Float_t         upfo_pt;
   Float_t         upfo_eta;
   Float_t         upfo_phi;
   Float_t         upfo_e;
   Float_t         upfovor_pt;
   Float_t         upfovor_eta;
   Float_t         upfovor_phi;
   Float_t         upfovor_e;
   Float_t         upfovorsp_pt;
   Float_t         upfovorsp_eta;
   Float_t         upfovorsp_phi;
   Float_t         upfovorsp_e;
   Int_t           upfo_pt_sys_;
   Float_t         upfo_pt_sys_first[kMaxupfo_pt_sys];   //[upfo_pt_sys_]
   string          upfo_pt_sys_second[kMaxupfo_pt_sys];
   Int_t           upfo_eta_sys_;
   Float_t         upfo_eta_sys_first[kMaxupfo_eta_sys];   //[upfo_eta_sys_]
   string          upfo_eta_sys_second[kMaxupfo_eta_sys];
   Int_t           upfo_phi_sys_;
   Float_t         upfo_phi_sys_first[kMaxupfo_phi_sys];   //[upfo_phi_sys_]
   string          upfo_phi_sys_second[kMaxupfo_phi_sys];
   Int_t           upfo_e_sys_;
   Float_t         upfo_e_sys_first[kMaxupfo_e_sys];   //[upfo_e_sys_]
   string          upfo_e_sys_second[kMaxupfo_e_sys];
   Int_t           upfovor_pt_sys_;
   Float_t         upfovor_pt_sys_first[kMaxupfovor_pt_sys];   //[upfovor_pt_sys_]
   string          upfovor_pt_sys_second[kMaxupfovor_pt_sys];
   Int_t           upfovor_eta_sys_;
   Float_t         upfovor_eta_sys_first[kMaxupfovor_eta_sys];   //[upfovor_eta_sys_]
   string          upfovor_eta_sys_second[kMaxupfovor_eta_sys];
   Int_t           upfovor_phi_sys_;
   Float_t         upfovor_phi_sys_first[kMaxupfovor_phi_sys];   //[upfovor_phi_sys_]
   string          upfovor_phi_sys_second[kMaxupfovor_phi_sys];
   Int_t           upfovor_e_sys_;
   Float_t         upfovor_e_sys_first[kMaxupfovor_e_sys];   //[upfovor_e_sys_]
   string          upfovor_e_sys_second[kMaxupfovor_e_sys];
   Int_t           upfovorsp_pt_sys_;
   Float_t         upfovorsp_pt_sys_first[kMaxupfovorsp_pt_sys];   //[upfovorsp_pt_sys_]
   string          upfovorsp_pt_sys_second[kMaxupfovorsp_pt_sys];
   Int_t           upfovorsp_eta_sys_;
   Float_t         upfovorsp_eta_sys_first[kMaxupfovorsp_eta_sys];   //[upfovorsp_eta_sys_]
   string          upfovorsp_eta_sys_second[kMaxupfovorsp_eta_sys];
   Int_t           upfovorsp_phi_sys_;
   Float_t         upfovorsp_phi_sys_first[kMaxupfovorsp_phi_sys];   //[upfovorsp_phi_sys_]
   string          upfovorsp_phi_sys_second[kMaxupfovorsp_phi_sys];
   Int_t           upfovorsp_e_sys_;
   Float_t         upfovorsp_e_sys_first[kMaxupfovorsp_e_sys];   //[upfovorsp_e_sys_]
   string          upfovorsp_e_sys_second[kMaxupfovorsp_e_sys];
   vector<float>   *tjet_pt;
   vector<float>   *tjet_eta;
   vector<float>   *tjet_phi;
   vector<float>   *tjet_e;
   vector<float>   *tboson_pt;
   vector<float>   *tboson_eta;
   vector<float>   *tboson_phi;
   vector<float>   *tboson_e;
   vector<float>   *tboson_pdgId;
   vector<float>   *tphoton_pt;
   vector<float>   *tphoton_eta;
   vector<float>   *tphoton_phi;
   vector<float>   *tphoton_e;
   vector<float>   *tlep_dressed_pt;
   vector<float>   *tlep_dressed_eta;
   vector<float>   *tlep_dressed_phi;
   vector<float>   *tlep_dressed_e;
   vector<float>   *tlep_dressed_pdgId;
   vector<float>   *tlep_bare_pt;
   vector<float>   *tlep_bare_eta;
   vector<float>   *tlep_bare_phi;
   vector<float>   *tlep_bare_e;
   vector<float>   *tlep_bare_pdgId;
   vector<float>   *tlep_born_pt;
   vector<float>   *tlep_born_eta;
   vector<float>   *tlep_born_phi;
   vector<float>   *tlep_born_e;
   vector<float>   *tlep_born_pdgId;
   vector<float>   *tneutrino_pt;
   vector<float>   *tneutrino_eta;
   vector<float>   *tneutrino_phi;
   vector<float>   *tneutrino_e;
   vector<float>   *tneutrino_pdgID;
   Double_t        tparton_pdgId1;
   Double_t        tparton_pdgId2;

   // List of branches
   TBranch        *b_EventWeight;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EvtNumber;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_npuv;   //!
   TBranch        *b_zvertex;   //!
   TBranch        *b_average_mu;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_sys_;   //!
   TBranch        *b_jet_sys_first;   //!
   TBranch        *b_jet_sys_second;   //!
   TBranch        *b_mu_n;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_sf;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_trigMatch;   //!
   TBranch        *b_mu_syspt_;   //!
   TBranch        *b_mu_syspt_first;   //!
   TBranch        *b_mu_syspt_second;   //!
   TBranch        *b_mu_syssf_;   //!
   TBranch        *b_mu_syssf_first;   //!
   TBranch        *b_mu_syssf_second;   //!
   TBranch        *b_mu_trigmceff;   //!
   TBranch        *b_mu_trigsf;   //!
   TBranch        *b_mu_systrigsf_;   //!
   TBranch        *b_mu_systrigsf_first;   //!
   TBranch        *b_mu_systrigsf_second;   //!
   TBranch        *b_el_n;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_sf;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_trigMatch;   //!
   TBranch        *b_el_trigmceff;   //!
   TBranch        *b_el_trigsf;   //!
   TBranch        *b_el_syspt_;   //!
   TBranch        *b_el_syspt_first;   //!
   TBranch        *b_el_syspt_second;   //!
   TBranch        *b_el_syssf_;   //!
   TBranch        *b_el_syssf_first;   //!
   TBranch        *b_el_syssf_second;   //!
   TBranch        *b_el_systrigsf_;   //!
   TBranch        *b_el_systrigsf_first;   //!
   TBranch        *b_el_systrigsf_second;   //!
   TBranch        *b_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_sumet;   //!
   TBranch        *b_met_sys_;   //!
   TBranch        *b_met_sys_first;   //!
   TBranch        *b_met_sys_second;   //!
   TBranch        *b_met_phi_sys_;   //!
   TBranch        *b_met_phi_sys_first;   //!
   TBranch        *b_met_phi_sys_second;   //!
   TBranch        *b_passTrigger_el;   //!
   TBranch        *b_passTrigger_mu;   //!
   TBranch        *b_HadRecoil;   //!
   TBranch        *b_upfo_pt;   //!
   TBranch        *b_upfo_eta;   //!
   TBranch        *b_upfo_phi;   //!
   TBranch        *b_upfo_e;   //!
   TBranch        *b_upfovor_pt;   //!
   TBranch        *b_upfovor_eta;   //!
   TBranch        *b_upfovor_phi;   //!
   TBranch        *b_upfovor_e;   //!
   TBranch        *b_upfovorsp_pt;   //!
   TBranch        *b_upfovorsp_eta;   //!
   TBranch        *b_upfovorsp_phi;   //!
   TBranch        *b_upfovorsp_e;   //!
   TBranch        *b_upfo_pt_sys_;   //!
   TBranch        *b_upfo_pt_sys_first;   //!
   TBranch        *b_upfo_pt_sys_second;   //!
   TBranch        *b_upfo_eta_sys_;   //!
   TBranch        *b_upfo_eta_sys_first;   //!
   TBranch        *b_upfo_eta_sys_second;   //!
   TBranch        *b_upfo_phi_sys_;   //!
   TBranch        *b_upfo_phi_sys_first;   //!
   TBranch        *b_upfo_phi_sys_second;   //!
   TBranch        *b_upfo_e_sys_;   //!
   TBranch        *b_upfo_e_sys_first;   //!
   TBranch        *b_upfo_e_sys_second;   //!
   TBranch        *b_upfovor_pt_sys_;   //!
   TBranch        *b_upfovor_pt_sys_first;   //!
   TBranch        *b_upfovor_pt_sys_second;   //!
   TBranch        *b_upfovor_eta_sys_;   //!
   TBranch        *b_upfovor_eta_sys_first;   //!
   TBranch        *b_upfovor_eta_sys_second;   //!
   TBranch        *b_upfovor_phi_sys_;   //!
   TBranch        *b_upfovor_phi_sys_first;   //!
   TBranch        *b_upfovor_phi_sys_second;   //!
   TBranch        *b_upfovor_e_sys_;   //!
   TBranch        *b_upfovor_e_sys_first;   //!
   TBranch        *b_upfovor_e_sys_second;   //!
   TBranch        *b_upfovorsp_pt_sys_;   //!
   TBranch        *b_upfovorsp_pt_sys_first;   //!
   TBranch        *b_upfovorsp_pt_sys_second;   //!
   TBranch        *b_upfovorsp_eta_sys_;   //!
   TBranch        *b_upfovorsp_eta_sys_first;   //!
   TBranch        *b_upfovorsp_eta_sys_second;   //!
   TBranch        *b_upfovorsp_phi_sys_;   //!
   TBranch        *b_upfovorsp_phi_sys_first;   //!
   TBranch        *b_upfovorsp_phi_sys_second;   //!
   TBranch        *b_upfovorsp_e_sys_;   //!
   TBranch        *b_upfovorsp_e_sys_first;   //!
   TBranch        *b_upfovorsp_e_sys_second;   //!
   TBranch        *b_tjet_pt;   //!
   TBranch        *b_tjet_eta;   //!
   TBranch        *b_tjet_phi;   //!
   TBranch        *b_tjet_e;   //!
   TBranch        *b_tboson_pt;   //!
   TBranch        *b_tboson_eta;   //!
   TBranch        *b_tboson_phi;   //!
   TBranch        *b_tboson_e;   //!
   TBranch        *b_tboson_pdgId;   //!
   TBranch        *b_tphoton_pt;   //!
   TBranch        *b_tphoton_eta;   //!
   TBranch        *b_tphoton_phi;   //!
   TBranch        *b_tphoton_e;   //!
   TBranch        *b_tlep_dressed_pt;   //!
   TBranch        *b_tlep_dressed_eta;   //!
   TBranch        *b_tlep_dressed_phi;   //!
   TBranch        *b_tlep_dressed_e;   //!
   TBranch        *b_tlep_dressed_pdgId;   //!
   TBranch        *b_tlep_bare_pt;   //!
   TBranch        *b_tlep_bare_eta;   //!
   TBranch        *b_tlep_bare_phi;   //!
   TBranch        *b_tlep_bare_e;   //!
   TBranch        *b_tlep_bare_pdgId;   //!
   TBranch        *b_tlep_born_pt;   //!
   TBranch        *b_tlep_born_eta;   //!
   TBranch        *b_tlep_born_phi;   //!
   TBranch        *b_tlep_born_e;   //!
   TBranch        *b_tlep_born_pdgId;   //!
   TBranch        *b_tneutrino_pt;   //!
   TBranch        *b_tneutrino_eta;   //!
   TBranch        *b_tneutrino_phi;   //!
   TBranch        *b_tneutrino_e;   //!
   TBranch        *b_tneutrino_pdgID;   //!
   TBranch        *b_tparton_pdgId1;   //!
   TBranch        *b_tparton_pdgId2;   //!

   MyTest(TTree *tree=0);
   virtual ~MyTest();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyTest_cxx
MyTest::MyTest(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("outT.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("outT.root");
      }
      f->GetObject("treeAnaWZ",tree);

   }
   Init(tree);
}

MyTest::~MyTest()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyTest::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyTest::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyTest::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet_pt = 0;
   jet_eta = 0;
   jet_phi = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_sf = 0;
   mu_charge = 0;
   mu_trigMatch = 0;
   mu_trigmceff = 0;
   mu_trigsf = 0;
   el_pt = 0;
   el_eta = 0;
   el_phi = 0;
   el_sf = 0;
   el_charge = 0;
   el_trigMatch = 0;
   el_trigmceff = 0;
   el_trigsf = 0;
   tjet_pt = 0;
   tjet_eta = 0;
   tjet_phi = 0;
   tjet_e = 0;
   tboson_pt = 0;
   tboson_eta = 0;
   tboson_phi = 0;
   tboson_e = 0;
   tboson_pdgId = 0;
   tphoton_pt = 0;
   tphoton_eta = 0;
   tphoton_phi = 0;
   tphoton_e = 0;
   tlep_dressed_pt = 0;
   tlep_dressed_eta = 0;
   tlep_dressed_phi = 0;
   tlep_dressed_e = 0;
   tlep_dressed_pdgId = 0;
   tlep_bare_pt = 0;
   tlep_bare_eta = 0;
   tlep_bare_phi = 0;
   tlep_bare_e = 0;
   tlep_bare_pdgId = 0;
   tlep_born_pt = 0;
   tlep_born_eta = 0;
   tlep_born_phi = 0;
   tlep_born_e = 0;
   tlep_born_pdgId = 0;
   tneutrino_pt = 0;
   tneutrino_eta = 0;
   tneutrino_phi = 0;
   tneutrino_e = 0;
   tneutrino_pdgID = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventWeight", &EventWeight, &b_EventWeight);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EvtNumber", &EvtNumber, &b_EvtNumber);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("npuv", &npuv, &b_npuv);
   fChain->SetBranchAddress("zvertex", &zvertex, &b_zvertex);
   fChain->SetBranchAddress("average_mu", &average_mu, &b_average_mu);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_sys", &jet_sys_, &b_jet_sys_);
   fChain->SetBranchAddress("jet_sys.first", &jet_sys_first, &b_jet_sys_first);
   fChain->SetBranchAddress("jet_sys.second", &jet_sys_second, &b_jet_sys_second);
   fChain->SetBranchAddress("mu_n", &mu_n, &b_mu_n);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_sf", &mu_sf, &b_mu_sf);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_trigMatch", &mu_trigMatch, &b_mu_trigMatch);
   fChain->SetBranchAddress("mu_syspt", &mu_syspt_, &b_mu_syspt_);
   fChain->SetBranchAddress("mu_syspt.first", &mu_syspt_first, &b_mu_syspt_first);
   fChain->SetBranchAddress("mu_syspt.second", &mu_syspt_second, &b_mu_syspt_second);
   fChain->SetBranchAddress("mu_syssf", &mu_syssf_, &b_mu_syssf_);
   fChain->SetBranchAddress("mu_syssf.first", &mu_syssf_first, &b_mu_syssf_first);
   fChain->SetBranchAddress("mu_syssf.second", &mu_syssf_second, &b_mu_syssf_second);
   fChain->SetBranchAddress("mu_trigmceff", &mu_trigmceff, &b_mu_trigmceff);
   fChain->SetBranchAddress("mu_trigsf", &mu_trigsf, &b_mu_trigsf);
   fChain->SetBranchAddress("mu_systrigsf", &mu_systrigsf_, &b_mu_systrigsf_);
   fChain->SetBranchAddress("mu_systrigsf.first", &mu_systrigsf_first, &b_mu_systrigsf_first);
   fChain->SetBranchAddress("mu_systrigsf.second", &mu_systrigsf_second, &b_mu_systrigsf_second);
   fChain->SetBranchAddress("el_n", &el_n, &b_el_n);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_sf", &el_sf, &b_el_sf);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_trigMatch", &el_trigMatch, &b_el_trigMatch);
   fChain->SetBranchAddress("el_trigmceff", &el_trigmceff, &b_el_trigmceff);
   fChain->SetBranchAddress("el_trigsf", &el_trigsf, &b_el_trigsf);
   fChain->SetBranchAddress("el_syspt", &el_syspt_, &b_el_syspt_);
   fChain->SetBranchAddress("el_syspt.first", &el_syspt_first, &b_el_syspt_first);
   fChain->SetBranchAddress("el_syspt.second", &el_syspt_second, &b_el_syspt_second);
   fChain->SetBranchAddress("el_syssf", &el_syssf_, &b_el_syssf_);
   fChain->SetBranchAddress("el_syssf.first", &el_syssf_first, &b_el_syssf_first);
   fChain->SetBranchAddress("el_syssf.second", &el_syssf_second, &b_el_syssf_second);
   fChain->SetBranchAddress("el_systrigsf", &el_systrigsf_, &b_el_systrigsf_);
   fChain->SetBranchAddress("el_systrigsf.first", &el_systrigsf_first, &b_el_systrigsf_first);
   fChain->SetBranchAddress("el_systrigsf.second", &el_systrigsf_second, &b_el_systrigsf_second);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("sumet", &sumet, &b_sumet);
   fChain->SetBranchAddress("met_sys", &met_sys_, &b_met_sys_);
   fChain->SetBranchAddress("met_sys.first", &met_sys_first, &b_met_sys_first);
   fChain->SetBranchAddress("met_sys.second", &met_sys_second, &b_met_sys_second);
   fChain->SetBranchAddress("met_phi_sys", &met_phi_sys_, &b_met_phi_sys_);
   fChain->SetBranchAddress("met_phi_sys.first", &met_phi_sys_first, &b_met_phi_sys_first);
   fChain->SetBranchAddress("met_phi_sys.second", &met_phi_sys_second, &b_met_phi_sys_second);
   fChain->SetBranchAddress("passTrigger_el", &passTrigger_el, &b_passTrigger_el);
   fChain->SetBranchAddress("passTrigger_mu", &passTrigger_mu, &b_passTrigger_mu);
   fChain->SetBranchAddress("HadRecoil", &HadRecoil, &b_HadRecoil);
   fChain->SetBranchAddress("upfo_pt", &upfo_pt, &b_upfo_pt);
   fChain->SetBranchAddress("upfo_eta", &upfo_eta, &b_upfo_eta);
   fChain->SetBranchAddress("upfo_phi", &upfo_phi, &b_upfo_phi);
   fChain->SetBranchAddress("upfo_e", &upfo_e, &b_upfo_e);
   fChain->SetBranchAddress("upfovor_pt", &upfovor_pt, &b_upfovor_pt);
   fChain->SetBranchAddress("upfovor_eta", &upfovor_eta, &b_upfovor_eta);
   fChain->SetBranchAddress("upfovor_phi", &upfovor_phi, &b_upfovor_phi);
   fChain->SetBranchAddress("upfovor_e", &upfovor_e, &b_upfovor_e);
   fChain->SetBranchAddress("upfovorsp_pt", &upfovorsp_pt, &b_upfovorsp_pt);
   fChain->SetBranchAddress("upfovorsp_eta", &upfovorsp_eta, &b_upfovorsp_eta);
   fChain->SetBranchAddress("upfovorsp_phi", &upfovorsp_phi, &b_upfovorsp_phi);
   fChain->SetBranchAddress("upfovorsp_e", &upfovorsp_e, &b_upfovorsp_e);
   fChain->SetBranchAddress("upfo_pt_sys", &upfo_pt_sys_, &b_upfo_pt_sys_);
   fChain->SetBranchAddress("upfo_pt_sys.first", &upfo_pt_sys_first, &b_upfo_pt_sys_first);
   fChain->SetBranchAddress("upfo_pt_sys.second", &upfo_pt_sys_second, &b_upfo_pt_sys_second);
   fChain->SetBranchAddress("upfo_eta_sys", &upfo_eta_sys_, &b_upfo_eta_sys_);
   fChain->SetBranchAddress("upfo_eta_sys.first", &upfo_eta_sys_first, &b_upfo_eta_sys_first);
   fChain->SetBranchAddress("upfo_eta_sys.second", &upfo_eta_sys_second, &b_upfo_eta_sys_second);
   fChain->SetBranchAddress("upfo_phi_sys", &upfo_phi_sys_, &b_upfo_phi_sys_);
   fChain->SetBranchAddress("upfo_phi_sys.first", &upfo_phi_sys_first, &b_upfo_phi_sys_first);
   fChain->SetBranchAddress("upfo_phi_sys.second", &upfo_phi_sys_second, &b_upfo_phi_sys_second);
   fChain->SetBranchAddress("upfo_e_sys", &upfo_e_sys_, &b_upfo_e_sys_);
   fChain->SetBranchAddress("upfo_e_sys.first", &upfo_e_sys_first, &b_upfo_e_sys_first);
   fChain->SetBranchAddress("upfo_e_sys.second", &upfo_e_sys_second, &b_upfo_e_sys_second);
   fChain->SetBranchAddress("upfovor_pt_sys", &upfovor_pt_sys_, &b_upfovor_pt_sys_);
   fChain->SetBranchAddress("upfovor_pt_sys.first", &upfovor_pt_sys_first, &b_upfovor_pt_sys_first);
   fChain->SetBranchAddress("upfovor_pt_sys.second", &upfovor_pt_sys_second, &b_upfovor_pt_sys_second);
   fChain->SetBranchAddress("upfovor_eta_sys", &upfovor_eta_sys_, &b_upfovor_eta_sys_);
   fChain->SetBranchAddress("upfovor_eta_sys.first", &upfovor_eta_sys_first, &b_upfovor_eta_sys_first);
   fChain->SetBranchAddress("upfovor_eta_sys.second", &upfovor_eta_sys_second, &b_upfovor_eta_sys_second);
   fChain->SetBranchAddress("upfovor_phi_sys", &upfovor_phi_sys_, &b_upfovor_phi_sys_);
   fChain->SetBranchAddress("upfovor_phi_sys.first", &upfovor_phi_sys_first, &b_upfovor_phi_sys_first);
   fChain->SetBranchAddress("upfovor_phi_sys.second", &upfovor_phi_sys_second, &b_upfovor_phi_sys_second);
   fChain->SetBranchAddress("upfovor_e_sys", &upfovor_e_sys_, &b_upfovor_e_sys_);
   fChain->SetBranchAddress("upfovor_e_sys.first", &upfovor_e_sys_first, &b_upfovor_e_sys_first);
   fChain->SetBranchAddress("upfovor_e_sys.second", &upfovor_e_sys_second, &b_upfovor_e_sys_second);
   fChain->SetBranchAddress("upfovorsp_pt_sys", &upfovorsp_pt_sys_, &b_upfovorsp_pt_sys_);
   fChain->SetBranchAddress("upfovorsp_pt_sys.first", &upfovorsp_pt_sys_first, &b_upfovorsp_pt_sys_first);
   fChain->SetBranchAddress("upfovorsp_pt_sys.second", &upfovorsp_pt_sys_second, &b_upfovorsp_pt_sys_second);
   fChain->SetBranchAddress("upfovorsp_eta_sys", &upfovorsp_eta_sys_, &b_upfovorsp_eta_sys_);
   fChain->SetBranchAddress("upfovorsp_eta_sys.first", &upfovorsp_eta_sys_first, &b_upfovorsp_eta_sys_first);
   fChain->SetBranchAddress("upfovorsp_eta_sys.second", &upfovorsp_eta_sys_second, &b_upfovorsp_eta_sys_second);
   fChain->SetBranchAddress("upfovorsp_phi_sys", &upfovorsp_phi_sys_, &b_upfovorsp_phi_sys_);
   fChain->SetBranchAddress("upfovorsp_phi_sys.first", &upfovorsp_phi_sys_first, &b_upfovorsp_phi_sys_first);
   fChain->SetBranchAddress("upfovorsp_phi_sys.second", &upfovorsp_phi_sys_second, &b_upfovorsp_phi_sys_second);
   fChain->SetBranchAddress("upfovorsp_e_sys", &upfovorsp_e_sys_, &b_upfovorsp_e_sys_);
   fChain->SetBranchAddress("upfovorsp_e_sys.first", &upfovorsp_e_sys_first, &b_upfovorsp_e_sys_first);
   fChain->SetBranchAddress("upfovorsp_e_sys.second", &upfovorsp_e_sys_second, &b_upfovorsp_e_sys_second);
   fChain->SetBranchAddress("tjet_pt", &tjet_pt, &b_tjet_pt);
   fChain->SetBranchAddress("tjet_eta", &tjet_eta, &b_tjet_eta);
   fChain->SetBranchAddress("tjet_phi", &tjet_phi, &b_tjet_phi);
   fChain->SetBranchAddress("tjet_e", &tjet_e, &b_tjet_e);
   fChain->SetBranchAddress("tboson_pt", &tboson_pt, &b_tboson_pt);
   fChain->SetBranchAddress("tboson_eta", &tboson_eta, &b_tboson_eta);
   fChain->SetBranchAddress("tboson_phi", &tboson_phi, &b_tboson_phi);
   fChain->SetBranchAddress("tboson_e", &tboson_e, &b_tboson_e);
   fChain->SetBranchAddress("tboson_pdgId", &tboson_pdgId, &b_tboson_pdgId);
   fChain->SetBranchAddress("tphoton_pt", &tphoton_pt, &b_tphoton_pt);
   fChain->SetBranchAddress("tphoton_eta", &tphoton_eta, &b_tphoton_eta);
   fChain->SetBranchAddress("tphoton_phi", &tphoton_phi, &b_tphoton_phi);
   fChain->SetBranchAddress("tphoton_e", &tphoton_e, &b_tphoton_e);
   fChain->SetBranchAddress("tlep_dressed_pt", &tlep_dressed_pt, &b_tlep_dressed_pt);
   fChain->SetBranchAddress("tlep_dressed_eta", &tlep_dressed_eta, &b_tlep_dressed_eta);
   fChain->SetBranchAddress("tlep_dressed_phi", &tlep_dressed_phi, &b_tlep_dressed_phi);
   fChain->SetBranchAddress("tlep_dressed_e", &tlep_dressed_e, &b_tlep_dressed_e);
   fChain->SetBranchAddress("tlep_dressed_pdgId", &tlep_dressed_pdgId, &b_tlep_dressed_pdgId);
   fChain->SetBranchAddress("tlep_bare_pt", &tlep_bare_pt, &b_tlep_bare_pt);
   fChain->SetBranchAddress("tlep_bare_eta", &tlep_bare_eta, &b_tlep_bare_eta);
   fChain->SetBranchAddress("tlep_bare_phi", &tlep_bare_phi, &b_tlep_bare_phi);
   fChain->SetBranchAddress("tlep_bare_e", &tlep_bare_e, &b_tlep_bare_e);
   fChain->SetBranchAddress("tlep_bare_pdgId", &tlep_bare_pdgId, &b_tlep_bare_pdgId);
   fChain->SetBranchAddress("tlep_born_pt", &tlep_born_pt, &b_tlep_born_pt);
   fChain->SetBranchAddress("tlep_born_eta", &tlep_born_eta, &b_tlep_born_eta);
   fChain->SetBranchAddress("tlep_born_phi", &tlep_born_phi, &b_tlep_born_phi);
   fChain->SetBranchAddress("tlep_born_e", &tlep_born_e, &b_tlep_born_e);
   fChain->SetBranchAddress("tlep_born_pdgId", &tlep_born_pdgId, &b_tlep_born_pdgId);
   fChain->SetBranchAddress("tneutrino_pt", &tneutrino_pt, &b_tneutrino_pt);
   fChain->SetBranchAddress("tneutrino_eta", &tneutrino_eta, &b_tneutrino_eta);
   fChain->SetBranchAddress("tneutrino_phi", &tneutrino_phi, &b_tneutrino_phi);
   fChain->SetBranchAddress("tneutrino_e", &tneutrino_e, &b_tneutrino_e);
   fChain->SetBranchAddress("tneutrino_pdgID", &tneutrino_pdgID, &b_tneutrino_pdgID);
   fChain->SetBranchAddress("tparton_pdgId1", &tparton_pdgId1, &b_tparton_pdgId1);
   fChain->SetBranchAddress("tparton_pdgId2", &tparton_pdgId2, &b_tparton_pdgId2);
   Notify();
}

Bool_t MyTest::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyTest::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyTest::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyTest_cxx
