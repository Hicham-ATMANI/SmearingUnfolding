   void ratioplot() {
         
// ******************* pT du lepton - TRUE  ****************************
					
	   TFile* h = new TFile("output.root");
	   TH1F * h1 = new TH1F("h1","pt",72,30,100);
	   h1 = (TH1F*)h->Get("h_mt_ap");
  
	//   TH1F * h2 = new TH1F("h2","pt",72,30,100);
        //   h2 = (TH1F*)h->Get("h_mt_rec");

	   double x = 0;

           for(int i=1; i<=72;i++){
           x=h1->GetBinContent(i);
	   cout<<x<<endl;
	   }

	  /*
 	  TLegend *legendxa=new TLegend(0.12,0.7,0.4,0.87);
          legendxa->AddEntry(h1,"masse transverse reco ","lpe");
          legendxa->AddEntry(h2,"m_T reco + smearing","lpe");
	  */

/*
h1->SetTitle("Masse transverse reconstruite ");
h2->SetTitle("Masse transverse reconstruite + smearing ");
h1->SetLineColor(4);
h2->SetLineColor(2);
h2->Draw();
h1->Draw("same");
legendxa->Draw("same");

	   double x = 0;
	   double y = 0;
	   double z = 0;		
	   double err = 0;
	   for(int i=1; i<=10;i++){
	   x=h1->GetBinContent(i);
           y=h2->GetBinContent(i);
	   cout<<"x ="<<x<<"          "<<"y = "<<y<<endl;
	   z=sqrt(pow(x,2)-pow(y,2));
 	   cout<<z<<endl;
	   h22->SetBinContent(i,z);
           h22->SetBinError(i,2);
	   h22->SetStats(0);
	   h22->Draw();
*/
}                
