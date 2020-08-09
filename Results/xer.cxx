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

int xer() {

   TH1F* h_tmTT = new TH1F("h_tmTT"," pt de W   ",72,30,100);
   TH1F* h_tmTU = new TH1F("h_tmTU"," pt de W   ",72,30,100);


double x[100];
double y[100];
double z[100];
double xx = 0;

// Les donn√es pour #delta(m)=100MeV ***************************************

	ifstream monFluz("DataReco.txt");  //Ouverture d'un fichier en lecture
	   if(monFluz)
      	        {
	        double nombr;
                for( int j=1; j <= 72 ; j++){
                monFluz >> nombr; //Lit un nombre ?|  virgule depuis le fichier
                y[j]=nombr;
                cout<<nombr<<endl;
                h_tmTU->SetBinContent(j,y[j]);
                }}
    
// les donn√es Reco ********************************************************

        ifstream monFl("DataReco_int.txt");  //Ouverture d'un fichier en lecture
           if(monFl)
        	{
        	double nomb;
                for( int j=1; j <= 72 ; j++){
                monFl >> nomb; //Lit un nombre ?|  virgule depuis le fichier
                x[j]=nomb;
          //    cout<<nomb<<endl;
                h_tmTT->SetBinContent(j,x[j]);
                }}

// *************************************************************************
	         for( int j=1; j <= 72 ; j++){
            	 if (x[j] != 0){
	         xx=xx+pow((y[j]-x[j]),2)/x[j];
                 cout<<"x["<<j<<"]=    "<<x[j]<<"		"<<"y["<<j<<"]=    " <<y[j]<<"		"<<xx<<endl;
                 }}

// h_tmTT->Draw();
// h_tmTT->SetLineColor(2);
// h_tmTU->Draw("same");


return 0;
}

