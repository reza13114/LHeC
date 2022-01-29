#include <stdio.h>
#include "iostream"
#include "TH1F.h"
#include "TTree.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "stdlib.h"
#include "math.h"
#include "TPaveText.h"
#include <string>
#include <vector>
#include "TVirtualFitter.h"
#include "TBranch.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include"THStack.h"
#include"TPad.h"
#include"TLegend.h"
#include <vector>
#include "myclass.C"
//#if not defined(__CINT__) || defined(__MAKECINT__)

// define signal histograms



//    Double_t   sigma_MG [] = { xbr, xbi, ep2bbjvbkg1, ep2ccjvbkg2, ep2vjz2bbbkg3, ep2vjz2ccbkg4, ep2vjz2jjbkg5, ep2jt2w2jjbkg6, ep2vjh2bbSMbkg7}; 
const Double_t sigma_MG [9] = {0.4084, 0.9135, 0.02782,    0.06266,     0.0454442,     0.0469327,     0.2624102,     0.22345151,     0.048347}; //pb,

Double_t            sigma;
Double_t            sigma_pre;
Double_t            N_total;
Double_t            N_accepted;
Double_t            N_accepted_pre;
Double_t            efficiency_pre;
Double_t            efficiency;

//char *samplename[] = {"xtar", "xbr"};
//vector  <TString> name = {xtar, xbr, xtr, xtai, xbi, xti, ep2bbjvbkg1, ep2ccjvbkg2, ep2vjz2bbbkg3, ep2vjz2ccbkg4, ep2vjz2jjbkg5, ep2jt2w2jjbkg6, ep2vjh2bbSMbkg7};



TH1F *hjet_pt[9], *hbjet_pt[9], *hsubbjet_pt[9], *hjet_eta[9], *hbjet_eta[9], *hsubbjet_eta[9], *hjet_E[9], *hbjet_E[9], *hsubbjet_E[9], *hbjetsInvariantMass[9], *hMET[9], *hHT[9], *hdeltaeta_bjets[9], *hdeltaeta_jetbjet[9], *hdeltaeta_jetsubbjet[9], *hdeltaphi_bjets[9], *hdeltaphi_jetbjet[9], *hdeltaphi_jetsubbjet[9], *hdeltaR_bjets[9], *hdeltaR_jetbjet[9], *hdeltaR_jetsubbjet[9], *hcos_bjets[9], *hcos_jetbjet[9], *hcos_jetsubbjet[9], *hjetmultiplicity[9];

TFile *f;

void plots60GeV(){

//======================================================= sample loop

    for(int r = 0; r < 9; r++)
    {
        cout << endl << "sample " << r << ": " << endl;

        hjet_pt[r] = new TH1F("hjet_pt","", 35, 0 ,350);
        hbjet_pt[r]  = new TH1F("hbjet_pt","", 30, 0 ,300);
        hsubbjet_pt[r]  = new TH1F("hsubbjet_pt","", 20, 0 ,200);

        hjet_eta[r]  = new TH1F("hjet_eta","", 55, -6 ,5);
        hbjet_eta[r]  = new TH1F("hbjet_eta","", 40, -4 ,4);
        hsubbjet_eta[r]  = new TH1F("hsubbjet_eta","", 40, -4 ,4);

        hjet_E[r]  = new TH1F("hjet_E","", 65, 0, 2600);
        hbjet_E[r]  = new TH1F("hbjet_E","", 50, 0, 1000);
        hsubbjet_E[r]  = new TH1F("hsubbjet_E","", 40, 0, 800);

        hbjetsInvariantMass[r]  = new TH1F("hbjetsInvariantMass","", 60, 0 ,300);
        hMET[r]  = new TH1F("hMET","", 50, 0 ,500);
        hHT[r]  = new TH1F("hHT","", 60, 0 ,600);

        hdeltaeta_bjets[r]  = new TH1F("hdeltaeta_bjets","", 50, -5 ,5);
        hdeltaeta_jetbjet[r]  = new TH1F("hdeltaeta_jetbjet","", 55, -5 ,6);
        hdeltaeta_jetsubbjet[r]  = new TH1F("hdeltaeta_jetsubbjet","", 55, -5 ,6);

        hdeltaphi_bjets[r]  = new TH1F("hdeltaphi_bjets","", 40, -8 ,8);
        hdeltaphi_jetbjet[r]  = new TH1F("hdeltaphi_jetbjet","", 40, -8 ,8);
        hdeltaphi_jetsubbjet[r]  = new TH1F("hdeltaphi_jetsubbjet","", 40, -8 ,8);

        hdeltaR_bjets[r]  = new TH1F("hdeltaR_bjets","", 25, 0 ,5);
        hdeltaR_jetbjet[r]  = new TH1F("hdeltaR_jetbjet","", 35, 0 ,7);
        hdeltaR_jetsubbjet[r]  = new TH1F("hdeltaR_jetsubbjet","", 35, -0 ,7);

        hcos_bjets[r]  = new TH1F("hcos_bjets","", 30, -1.5, 1.5);
        hcos_jetbjet[r]  = new TH1F("hcos_jetbjet","", 30, -1.5, 1.5);
        hcos_jetsubbjet[r]  = new TH1F("hcos_jetsubbjet","", 30, -1.5, 1.5);

        hjetmultiplicity[r]  = new TH1F("hjetmultiplicity","", 30, 0, 30);

        hjet_pt[r]->SetDirectory(0);
        hbjet_pt[r]->SetDirectory(0);
        hsubbjet_pt[r]->SetDirectory(0);

        hjet_eta[r]->SetDirectory(0);
        hbjet_eta[r]->SetDirectory(0);
        hsubbjet_eta[r]->SetDirectory(0);

        hjet_E[r]->SetDirectory(0);
        hbjet_E[r]->SetDirectory(0);
        hsubbjet_E[r]->SetDirectory(0);

        hbjetsInvariantMass[r]->SetDirectory(0);
        hMET[r]->SetDirectory(0);
        hHT[r]->SetDirectory(0);

        hdeltaeta_bjets[r]->SetDirectory(0);
        hdeltaeta_jetbjet[r]->SetDirectory(0);
        hdeltaeta_jetsubbjet[r]->SetDirectory(0);

        hdeltaphi_bjets[r]->SetDirectory(0);
        hdeltaphi_jetbjet[r]->SetDirectory(0);
        hdeltaphi_jetsubbjet[r]->SetDirectory(0);

        hdeltaR_bjets[r]->SetDirectory(0);
        hdeltaR_jetbjet[r]->SetDirectory(0);
        hdeltaR_jetsubbjet[r]->SetDirectory(0);

        hcos_bjets[r]->SetDirectory(0);
        hcos_jetbjet[r]->SetDirectory(0);
        hcos_jetsubbjet[r]->SetDirectory(0);

        hjetmultiplicity[r]->SetDirectory(0);

        if (r==0)  f = new TFile("xbr.root","READ");
        if (r==1) f = new TFile("xbi.root","READ");

        if (r==2) f = new TFile("ep2bbjvbkg1.root","READ");
        if (r==3)  f = new TFile("ep2ccjvbkg2.root","READ");
        if (r==4) f = new TFile("ep2vjz2bbbkg3.root","READ");
        if (r==5) f = new TFile("ep2vjz2ccbkg4.root","READ");
        if (r==6)  f = new TFile("ep2vjz2jjbkg5.root","READ");
        if (r==7) f = new TFile("ep2jt2w2jjbkg6.root","READ");
        if (r==8) f = new TFile("ep2vjhSMbkg7.root","READ");


/*
        if (r==0)  f = new TFile("xtar.root","READ");
        if (r==1) f = new TFile("xbr.root","READ");
        if (r==2) f = new TFile("xtr.root","READ");
        if (r==3)  f = new TFile("xtai.root","READ");
        if (r==4) f = new TFile("xbi.root","READ");
        if (r==5) f = new TFile("xti.root","READ");

        if (r==6)  f = new TFile("ep2bbjvbkg1.root","READ");
        if (r==7) f = new TFile("ep2ccjvbkg2.root","READ");
        if (r==8) f = new TFile("ep2vjz2bbbkg3.root","READ");
        if (r==9)  f = new TFile("ep2vjz2ccbkg4.root","READ");
        if (r==10) f = new TFile("ep2vjz2jjbkg5.root","READ"); 
        if (r==11) f = new TFile("ep2jt2w2jjbkg6.root","READ");
        if (r==12) f = new TFile("ep2vjhSMbkg7.root","READ");
*/


        TTree *tree_sample;
        f->GetObject("Delphes",tree_sample);   // Get objects from root file
        myclass     my(tree_sample);   // Define an object for Getting Entries
 /*
        TTree *tree_sample = (TTree*) f->Get( "Delphes" );
        myclass my(tree_sample);
  */ 
        TLorentzVector                   jet_4v;
        vector <TLorentzVector>          jet;

        TLorentzVector                   alljet_4v;
        vector <TLorentzVector>          alljet;

        TLorentzVector                   bjet_4v;
        vector <TLorentzVector>          bjet;

        Double_t                         jet_pt;
        Double_t                         bjet_pt;
        Double_t                         subbjet_pt;

        Double_t                         jet_eta;
        Double_t                         bjet_eta;
        Double_t                         subbjet_eta;

        Double_t                         jet_E;
        Double_t                         bjet_E;
        Double_t                         subbjet_E;

        TVector3                         jet_P;
        TVector3                         bjet_P;
        TVector3                         subbjet_P;

        Double_t                         bjetsInvariantMass;
        Double_t                         MET;
        Double_t                         HT;

        Double_t                         deltaeta_bjets;
        Double_t                         deltaeta_jetbjet;
        Double_t                         deltaeta_jetsubbjet;

        Double_t                         deltaphi_bjets;
        Double_t                         deltaphi_jetbjet;
        Double_t                         deltaphi_jetsubbjet;

        Double_t                         deltaR_bjets;
        Double_t                         deltaR_jetbjet;
        Double_t                         deltaR_jetsubbjet;

        Double_t                         cos_bjets;
        Double_t                         cos_jetbjet;
        Double_t                         cos_jetsubbjet;

        Int_t                            jetmultiplicity;

//======================================================= event loop
        N_accepted = 0;
        N_accepted_pre = 0;

        for (int i = 0; i < my.fChain->GetEntriesFast(); i++) {
        //for (int i = 0; i<10000; i++) {

            //if (i%100000 == 0) std::cout << "sample number " << r << ": ---------- ... Processing event: " << i << std::endl;
                   
            my.GetEntry(i);

            //if (my.Jet_size < 3) continue;

            for (int m = 0; m < my.Jet_size; m++)
            {
                if (/*my.Jet_BTag[m] == 0 &&*/ // Non-BTagged jets
                    my.Jet_PT[m] >= 20 &&
                    fabs(my.Jet_Eta[m]) <= 5.0)
                {
                    alljet_4v.SetPtEtaPhiM(my.Jet_PT[m],my.Jet_Eta[m],my.Jet_Phi[m],0);
                    alljet.push_back(alljet_4v);
                    
                    if (-5.0 <= (my.Jet_Eta[m]) && (my.Jet_Eta[m]) <= 1.0) // forward-jet
                    {
                        jet_4v.SetPtEtaPhiM(my.Jet_PT[m],my.Jet_Eta[m],my.Jet_Phi[m],0);
                        jet.push_back(jet_4v);
                    }
                }
                if (my.Jet_BTag[m] == 1 && // BTag == 1
                    my.Jet_PT[m] >= 20 && 
                    fabs(my.Jet_Eta[m]) <= 2.5)
                { 
                    bjet_4v.SetPtEtaPhiM(my.Jet_PT[m],my.Jet_Eta[m],my.Jet_Phi[m],0);
                    bjet.push_back(bjet_4v);
                }
            }
//======================================= event selection =============================================

            if (bjet.size() == 2 &&
                jet.size() >= 1 && // forward-jet : can be a l-jet or a b-jet ( 1 < Eta < 5 )
                alljet.size() >= 3 && // it is different from "my.Jet_size", and "jet.size()" because of PT and Eta range
                bjet.at(0) != jet.at(0) &&
                bjet.at(1) != jet.at(0) &&
                bjet.at(0).DeltaR(bjet.at(1)) > 0.5 &&
                bjet.at(0).DeltaR(jet.at(0)) > 0.5 &&
                bjet.at(1).DeltaR(jet.at(0)) > 0.5)
            {
                N_accepted_pre++;

                jet_pt = jet[0].Pt();
                bjet_pt = bjet[0].Pt(); 
                subbjet_pt = bjet[1].Pt(); 

                jet_eta = jet[0].Eta();
                bjet_eta = bjet[0].Eta(); 
                subbjet_eta = bjet[1].Eta(); 

                jet_E = jet[0].E();
                bjet_E = bjet[0].E(); 
                subbjet_E = bjet[1].E(); 
                jet_P = jet[0].Vect();
                bjet_P = bjet[0].Vect(); 
                subbjet_P = bjet[1].Vect(); 

                bjetsInvariantMass = (bjet.at(0) + bjet.at(1)).M();
                MET = my.MissingET_MET[0];
                HT = jet[0].Pt() + bjet[0].Pt() + bjet[1].Pt();

                deltaeta_bjets = bjet[0].Eta() - bjet[1].Eta();
                deltaeta_jetbjet = bjet[0].Eta() - jet[0].Eta();
                deltaeta_jetsubbjet = bjet[1].Eta() - jet[0].Eta();

                deltaphi_bjets = bjet[0].Phi() - bjet[1].Phi();
                deltaphi_jetbjet = bjet[0].Phi() - jet[0].Phi();
                deltaphi_jetsubbjet = bjet[1].Phi() - jet[0].Phi();

                deltaR_bjets = bjet.at(0).DeltaR(bjet.at(1));
                deltaR_jetbjet = bjet.at(0).DeltaR(jet.at(0));
                deltaR_jetsubbjet = bjet.at(1).DeltaR(jet.at(0));

                cos_bjets = (bjet_P.Dot(subbjet_P)) / (bjet_P.Mag() * subbjet_P.Mag());
                cos_jetbjet = (bjet_P.Dot(jet_P)) / (bjet_P.Mag() * jet_P.Mag());
                cos_jetsubbjet = (jet_P.Dot(subbjet_P)) / (jet_P.Mag() * subbjet_P.Mag());

                jetmultiplicity = my.Jet_size;

                 //======================================= Fill histograms

                hjet_pt[r]->Fill(jet_pt); 
                hbjet_pt[r]->Fill(bjet_pt); 
                hsubbjet_pt[r]->Fill(subbjet_pt); 

                hjet_eta[r]->Fill(jet_eta); 
                hbjet_eta[r]->Fill(bjet_eta); 
                hsubbjet_eta[r]->Fill(subbjet_eta); 

                hjet_E[r]->Fill(jet_E); 
                hbjet_E[r]->Fill(bjet_E); 
                hsubbjet_E[r]->Fill(subbjet_E); 

                hbjetsInvariantMass[r]->Fill(bjetsInvariantMass); 
                hMET[r]->Fill(MET); 
                hHT[r]->Fill(HT); 

                hdeltaeta_bjets[r]->Fill(deltaeta_bjets); 
                hdeltaeta_jetbjet[r]->Fill(deltaeta_jetbjet); 
                hdeltaeta_jetsubbjet[r]->Fill(deltaeta_jetsubbjet); 

                hdeltaphi_bjets[r]->Fill(deltaphi_bjets); 
                hdeltaphi_jetbjet[r]->Fill(deltaphi_jetbjet); 
                hdeltaphi_jetsubbjet[r]->Fill(deltaphi_jetsubbjet); 

                hdeltaR_bjets[r]->Fill(deltaR_bjets); 
                hdeltaR_jetbjet[r]->Fill(deltaR_jetbjet); 
                hdeltaR_jetsubbjet[r]->Fill(deltaR_jetsubbjet); 

                hcos_bjets[r]->Fill(cos_bjets); 
                hcos_jetbjet[r]->Fill(cos_jetbjet); 
                hcos_jetsubbjet[r]->Fill(cos_jetsubbjet); 

                hjetmultiplicity[r]->Fill(jetmultiplicity); 

                  //======================================= final cuts

                if (MET > 0.0 && HT > 0.0 && bjetsInvariantMass > 0.0)
                 {
                    N_accepted++;

                 } 

            } //======================================= event selection 
               
                jet.clear();
                alljet.clear();
                bjet.clear();
      
        } //======================================================= event loop

//============================================================ calculation of sigma and efficiency :
                 cout << "\n";
     if(r == 0)  cout << "For xbr60GeV:\n" << endl;
     if(r == 1)  cout << "For xbi60GeV:\n" << endl;
     if(r == 2)  cout << "For ep2bbjvbkg1:\n" << endl;
     if(r == 3)  cout << "For ep2ccjvbkg2:\n" << endl;
     if(r == 4)  cout << "For ep2vjz2bbbkg3:\n" << endl;
     if(r == 5)  cout << "For ep2vjz2ccbkg4:\n" << endl;
     if(r == 6)  cout << "For ep2vjz2jjbkg5:\n" << endl;
     if(r == 7)  cout << "For ep2jt2w2jjbkg6:\n" << endl;
     if(r == 8)  cout << "For ep2vjhSMbkg7:\n" << endl;

    efficiency_pre = N_accepted_pre / my.fChain->GetEntriesFast();
    efficiency = N_accepted / my.fChain->GetEntriesFast();

    sigma_pre = efficiency_pre * sigma_MG [r] * 1000; //fb 
    sigma = efficiency * sigma_MG [r] * 1000; //fb 

    cout << "N_total = " << my.fChain->GetEntriesFast() << endl;

    cout << "N_accepted_pre = " << N_accepted_pre << endl;
    cout << "N_accepted = " << N_accepted << endl;

    cout << "efficiency_pre = " << efficiency_pre << endl;
    cout << "efficiency = " << efficiency << endl;

    cout << "sigma_pre = " << sigma_pre << " fb" << endl; //fb 
    cout << "sigma = " << sigma << " fb" << endl; //fb 

  } //======================================================= sample loop


    //======================================= Draw histograms

    TCanvas *c1 = new TCanvas("c1","jet_pt"); c1->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c2 = new TCanvas("c2","p_{T}(bjet)");    c2->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c3 = new TCanvas("c3","p_{T}(subbjet)");    c3->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c4 = new TCanvas("c4","#eta(ljet)");    c4->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c5 = new TCanvas("c5","#eta(bjet)");    c5->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c6 = new TCanvas("c6","#eta(subbjet)");    c6->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c7 = new TCanvas("c7","E(ljet)");    c7->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c8 = new TCanvas("c8","E(bjet)");    c8->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c9 = new TCanvas("c9","E(subbjet)");    c9->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c10 = new TCanvas("c10","IM_{bjets}");    c10->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c11 = new TCanvas("c11","MET");    c11->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c12 = new TCanvas("c12","HT");    c12->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c13 = new TCanvas("c13","deltaeta_bjets");    c13->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c14 = new TCanvas("c14","deltaeta_jetbjet");    c14->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c15 = new TCanvas("c15","deltaeta_jetsubbjet");    c15->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c16 = new TCanvas("c16","deltaphi_bjets");    c16->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c17 = new TCanvas("c17","deltaphi_jetbjet");    c17->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c18 = new TCanvas("c18","deltaphi_jetsubbjet");    c18->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c19 = new TCanvas("c19","deltaR_bjets");    c19->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c20 = new TCanvas("c20","deltaR_jetbjet");    c20->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c21 = new TCanvas("c21","deltaR_jetsubbjet");    c21->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c22 = new TCanvas("c22","cos_bjets");    c22->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c23 = new TCanvas("c23","cos_jetbjet");    c23->Divide(1,1); gStyle->SetOptStat(0);
    TCanvas *c24 = new TCanvas("c24","cos_jetsubbjet");    c24->Divide(1,1); gStyle->SetOptStat(0);

    TCanvas *c25 = new TCanvas("c25","jetmultiplicity");    c25->Divide(1,1); gStyle->SetOptStat(0);

    gStyle->SetLineStyleString(11,"100 15");
    gStyle->SetLineStyleString(12,"150 15");
    gStyle->SetLineStyleString(13,"200 15");

    for(r = 0; r < 9; r++) // other loop over samples
    {

        hjet_pt[r]->Scale(1 /(hjet_pt[r]->Integral())); 
        hjet_pt[r]->SetLineWidth(2);
        if (r < 2){ hjet_pt[r]->SetLineColor(600-1-r);  hjet_pt[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hjet_pt[r]->SetLineStyle(2+r);
            //hjet_pt[r]->SetLineColor(632-1-r); 
            hjet_pt[2]->SetLineColor(2);  
            hjet_pt[3]->SetLineColor(3);  
            hjet_pt[4]->SetLineColor(7);  
            hjet_pt[5]->SetLineColor(6);  
            hjet_pt[6]->SetLineColor(kOrange-3);  
            hjet_pt[7]->SetLineColor(kPink+2);
            hjet_pt[8]->SetLineColor(8); 
            hjet_pt[8]->SetLineStyle(1); 
        }
        hjet_pt[r]->GetXaxis()->SetTitle("p_{T}^{light jet} [GeV]");
        hjet_pt[r]->GetXaxis()->SetLabelFont(132);
        hjet_pt[r]->GetXaxis()->SetTitleFont(22);
        hjet_pt[r]->GetXaxis()->SetTitleOffset(1.10);
        hjet_pt[r]->GetYaxis()->SetTitle("Normalized distribution");
        hjet_pt[r]->GetYaxis()->SetLabelFont(132);
        hjet_pt[r]->GetYaxis()->SetTitleFont(22);
        hjet_pt[r]->GetYaxis()->SetTitleOffset(1.10);
        //hjet_pt[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hbjet_pt[r]->Scale(1 /(hbjet_pt[r]->Integral()));
        hbjet_pt[r]->SetLineStyle(2+r);
        hbjet_pt[r]->SetLineWidth(2);
        if (r < 2){ hbjet_pt[r]->SetLineColor(600-1-r);  hbjet_pt[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hbjet_pt[r]->SetLineStyle(2+r);
            //hbjet_pt[r]->SetLineColor(632-1-r); 
            hbjet_pt[2]->SetLineColor(2);  
            hbjet_pt[3]->SetLineColor(3);  
            hbjet_pt[4]->SetLineColor(7);  
            hbjet_pt[5]->SetLineColor(6);  
            hbjet_pt[6]->SetLineColor(kOrange-3);  
            hbjet_pt[7]->SetLineColor(kPink+2);  
            hbjet_pt[8]->SetLineColor(8); 
            hbjet_pt[8]->SetLineStyle(1);  
        }
        hbjet_pt[r]->GetXaxis()->SetTitle("p_{T}^{b_{1}} [GeV]");
        hbjet_pt[r]->GetXaxis()->SetLabelFont(132);
        hbjet_pt[r]->GetXaxis()->SetTitleFont(22);
        hbjet_pt[r]->GetXaxis()->SetTitleOffset(1.10);
        hbjet_pt[r]->GetYaxis()->SetTitle("Normalized distribution");
        hbjet_pt[r]->GetYaxis()->SetLabelFont(132);
        hbjet_pt[r]->GetYaxis()->SetTitleFont(22);
        hbjet_pt[r]->GetYaxis()->SetTitleOffset(1.10);
        //hbjet_pt[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hsubbjet_pt[r]->Scale(1 /(hsubbjet_pt[r]->Integral()));
        hsubbjet_pt[r]->SetLineStyle(2+r);
        hsubbjet_pt[r]->SetLineWidth(2);
        if (r < 2){ hsubbjet_pt[r]->SetLineColor(600-1-r);  hsubbjet_pt[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hsubbjet_pt[r]->SetLineStyle(2+r);
            //hsubbjet_pt[r]->SetLineColor(632-1-r); 
            hsubbjet_pt[2]->SetLineColor(2);  
            hsubbjet_pt[3]->SetLineColor(3);  
            hsubbjet_pt[4]->SetLineColor(7);  
            hsubbjet_pt[5]->SetLineColor(6);  
            hsubbjet_pt[6]->SetLineColor(kOrange-3);  
            hsubbjet_pt[7]->SetLineColor(kPink+2);  
            hsubbjet_pt[8]->SetLineColor(8);  
            hsubbjet_pt[8]->SetLineStyle(1); 
        }
        hsubbjet_pt[r]->GetXaxis()->SetTitle("p_{T}^{b_{2}} [GeV]");
        hsubbjet_pt[r]->GetXaxis()->SetLabelFont(132);
        hsubbjet_pt[r]->GetXaxis()->SetTitleFont(22);
        hsubbjet_pt[r]->GetXaxis()->SetTitleOffset(1.10);
        hsubbjet_pt[r]->GetYaxis()->SetTitle("Normalized distribution");
        hsubbjet_pt[r]->GetYaxis()->SetLabelFont(132);
        hsubbjet_pt[r]->GetYaxis()->SetTitleFont(22);
        hsubbjet_pt[r]->GetYaxis()->SetTitleOffset(1.10);
        //hsubbjet_pt[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hjet_eta[r]->Scale(1 /(hjet_eta[r]->Integral()));
        hjet_eta[r]->SetLineStyle(2+r);
        hjet_eta[r]->SetLineWidth(2);
        if (r < 2){ hjet_eta[r]->SetLineColor(600-1-r);  hjet_eta[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hjet_eta[r]->SetLineStyle(2+r);
            //hjet_eta[r]->SetLineColor(632-1-r); 
            hjet_eta[2]->SetLineColor(2);  
            hjet_eta[3]->SetLineColor(3);  
            hjet_eta[4]->SetLineColor(7);  
            hjet_eta[5]->SetLineColor(6);  
            hjet_eta[6]->SetLineColor(kOrange-3);  
            hjet_eta[7]->SetLineColor(kPink+2);  
            hjet_eta[8]->SetLineColor(8);  
            hjet_eta[8]->SetLineStyle(1); 
        }
        hjet_eta[r]->GetXaxis()->SetTitle("#eta_{light jet}");
        hjet_eta[r]->GetXaxis()->SetLabelFont(132);
        hjet_eta[r]->GetXaxis()->SetTitleFont(22);
        hjet_eta[r]->GetXaxis()->SetTitleOffset(1.10);
        hjet_eta[r]->GetYaxis()->SetTitle("Normalized distribution");
        hjet_eta[r]->GetYaxis()->SetLabelFont(132);
        hjet_eta[r]->GetYaxis()->SetTitleFont(22);
        hjet_eta[r]->GetYaxis()->SetTitleOffset(1.10);
        //hjet_eta[r]->GetYaxis()->SetRangeUser(0.0, .3);

        hbjet_eta[r]->Scale(1 /(hbjet_eta[r]->Integral()));
        hbjet_eta[r]->SetLineStyle(2+r);
        hbjet_eta[r]->SetLineWidth(2);
        if (r < 2){ hbjet_eta[r]->SetLineColor(600-1-r);  hbjet_eta[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hbjet_eta[r]->SetLineStyle(2+r);
            //hbjet_eta[r]->SetLineColor(632-1-r); 
            hbjet_eta[2]->SetLineColor(2);  
            hbjet_eta[3]->SetLineColor(3);  
            hbjet_eta[4]->SetLineColor(7);  
            hbjet_eta[5]->SetLineColor(6);  
            hbjet_eta[6]->SetLineColor(kOrange-3);  
            hbjet_eta[7]->SetLineColor(kPink+2);  
            hbjet_eta[8]->SetLineColor(8);  
            hbjet_eta[8]->SetLineStyle(1); 
        }
        hbjet_eta[r]->GetXaxis()->SetTitle("#eta_{b1}");
        hbjet_eta[r]->GetXaxis()->SetLabelFont(132);
        hbjet_eta[r]->GetXaxis()->SetTitleFont(22);
        hbjet_eta[r]->GetXaxis()->SetTitleOffset(1.10);
        hbjet_eta[r]->GetYaxis()->SetTitle("Normalized distribution");
        hbjet_eta[r]->GetYaxis()->SetLabelFont(132);
        hbjet_eta[r]->GetYaxis()->SetTitleFont(22);
        hbjet_eta[r]->GetYaxis()->SetTitleOffset(1.10);
        //hbjet_eta[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hsubbjet_eta[r]->Scale(1 /(hsubbjet_eta[r]->Integral()));
        hsubbjet_eta[r]->SetLineStyle(2+r);
        hsubbjet_eta[r]->SetLineWidth(2);
        if (r < 2){ hsubbjet_eta[r]->SetLineColor(600-1-r);  hsubbjet_eta[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hsubbjet_eta[r]->SetLineStyle(2+r);
            //hsubbjet_eta[r]->SetLineColor(632-1-r); 
            hsubbjet_eta[2]->SetLineColor(2);  
            hsubbjet_eta[3]->SetLineColor(3);  
            hsubbjet_eta[4]->SetLineColor(7);  
            hsubbjet_eta[5]->SetLineColor(6);  
            hsubbjet_eta[6]->SetLineColor(kOrange-3);  
            hsubbjet_eta[7]->SetLineColor(kPink+2);  
            hsubbjet_eta[8]->SetLineColor(8);  
            hsubbjet_eta[8]->SetLineStyle(1); 
        }
        hsubbjet_eta[r]->GetXaxis()->SetTitle("#eta_{b2}");
        hsubbjet_eta[r]->GetXaxis()->SetLabelFont(132);
        hsubbjet_eta[r]->GetXaxis()->SetTitleFont(22);
        hsubbjet_eta[r]->GetXaxis()->SetTitleOffset(1.10);
        hsubbjet_eta[r]->GetYaxis()->SetTitle("Normalized distribution");
        hsubbjet_eta[r]->GetYaxis()->SetLabelFont(132);
        hsubbjet_eta[r]->GetYaxis()->SetTitleFont(22);
        hsubbjet_eta[r]->GetYaxis()->SetTitleOffset(1.10);
        //hsubbjet_eta[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hjet_E[r]->Scale(1 /(hjet_E[r]->Integral()));
        hjet_E[r]->SetLineStyle(2+r);
        hjet_E[r]->SetLineWidth(2);
        if (r < 2){ hjet_E[r]->SetLineColor(600-1-r);  hjet_E[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hjet_E[r]->SetLineStyle(2+r);
            //hjet_E[r]->SetLineColor(632-1-r); 
            hjet_E[2]->SetLineColor(2);  
            hjet_E[3]->SetLineColor(3);  
            hjet_E[4]->SetLineColor(7);  
            hjet_E[5]->SetLineColor(6);  
            hjet_E[6]->SetLineColor(kOrange-3);  
            hjet_E[7]->SetLineColor(kPink+2);  
            hjet_E[8]->SetLineColor(8);  
            hjet_E[8]->SetLineStyle(1); 
        }
        hjet_E[r]->GetXaxis()->SetTitle("E_{light jet} [GeV]");
        hjet_E[r]->GetXaxis()->SetLabelFont(132);
        hjet_E[r]->GetXaxis()->SetTitleFont(22);
        hjet_E[r]->GetXaxis()->SetTitleOffset(1.10);
        hjet_E[r]->GetYaxis()->SetTitle("Normalized distribution");
        hjet_E[r]->GetYaxis()->SetLabelFont(132);
        hjet_E[r]->GetYaxis()->SetTitleFont(22);
        hjet_E[r]->GetYaxis()->SetTitleOffset(1.10);
        //hjet_E[r]->GetYaxis()->SetRangeUser(0.0, .05);

        hbjet_E[r]->Scale(1 /(hbjet_E[r]->Integral()));
        hbjet_E[r]->SetLineStyle(2+r);
        hbjet_E[r]->SetLineWidth(2);
        if (r < 2){ hbjet_E[r]->SetLineColor(600-1-r);  hbjet_E[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hbjet_E[r]->SetLineStyle(2+r);
            //hbjet_E[r]->SetLineColor(632-1-r); 
            hbjet_E[2]->SetLineColor(2);  
            hbjet_E[3]->SetLineColor(3);  
            hbjet_E[4]->SetLineColor(7);  
            hbjet_E[5]->SetLineColor(6);  
            hbjet_E[6]->SetLineColor(kOrange-3);  
            hbjet_E[7]->SetLineColor(kPink+2);  
            hbjet_E[8]->SetLineColor(8);  
            hbjet_E[8]->SetLineStyle(1); 
        }
        hbjet_E[r]->GetXaxis()->SetTitle("E_{b1} [GeV]");
        hbjet_E[r]->GetXaxis()->SetLabelFont(132);
        hbjet_E[r]->GetXaxis()->SetTitleFont(22);
        hbjet_E[r]->GetXaxis()->SetTitleOffset(1.10);
        hbjet_E[r]->GetYaxis()->SetTitle("Normalized distribution");
        hbjet_E[r]->GetYaxis()->SetLabelFont(132);
        hbjet_E[r]->GetYaxis()->SetTitleFont(22);
        hbjet_E[r]->GetYaxis()->SetTitleOffset(1.10);
        //hbjet_E[r]->GetYaxis()->SetRangeUser(0.0, .07);

        hsubbjet_E[r]->Scale(1 /(hsubbjet_E[r]->Integral()));
        hsubbjet_E[r]->SetLineStyle(2+r);
        hsubbjet_E[r]->SetLineWidth(2);
        if (r < 2){ hsubbjet_E[r]->SetLineColor(600-1-r);  hsubbjet_E[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hsubbjet_E[r]->SetLineStyle(2+r);
            //hsubbjet_E[r]->SetLineColor(632-1-r); 
            hsubbjet_E[2]->SetLineColor(2);  
            hsubbjet_E[3]->SetLineColor(3);  
            hsubbjet_E[4]->SetLineColor(7);  
            hsubbjet_E[5]->SetLineColor(6);  
            hsubbjet_E[6]->SetLineColor(kOrange-3);  
            hsubbjet_E[7]->SetLineColor(kPink+2);  
            hsubbjet_E[8]->SetLineColor(8);  
            hsubbjet_E[8]->SetLineStyle(1); 
        }
        hsubbjet_E[r]->GetXaxis()->SetTitle("E_{b2} [GeV]");
        hsubbjet_E[r]->GetXaxis()->SetLabelFont(132);
        hsubbjet_E[r]->GetXaxis()->SetTitleFont(22);
        hsubbjet_E[r]->GetXaxis()->SetTitleOffset(1.10);
        hsubbjet_E[r]->GetYaxis()->SetTitle("Normalized distribution");
        hsubbjet_E[r]->GetYaxis()->SetLabelFont(132);
        hsubbjet_E[r]->GetYaxis()->SetTitleFont(22);
        hsubbjet_E[r]->GetYaxis()->SetTitleOffset(1.10);
        //hsubbjet_E[r]->GetYaxis()->SetRangeUser(0.0, .12);

        hbjetsInvariantMass[r]->Scale(1 /(hbjetsInvariantMass[r]->Integral()));
        hbjetsInvariantMass[r]->SetLineStyle(2+r);
        hbjetsInvariantMass[r]->SetLineWidth(2);
        if (r < 2){ hbjetsInvariantMass[r]->SetLineColor(600-1-r);  hbjetsInvariantMass[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hbjetsInvariantMass[r]->SetLineStyle(2+r);
            //hbjetsInvariantMass[r]->SetLineColor(632-1-r); 
            hbjetsInvariantMass[2]->SetLineColor(2);  
            hbjetsInvariantMass[3]->SetLineColor(3);  
            hbjetsInvariantMass[4]->SetLineColor(7);  
            hbjetsInvariantMass[5]->SetLineColor(6);  
            hbjetsInvariantMass[6]->SetLineColor(kOrange-3);  
            hbjetsInvariantMass[7]->SetLineColor(kPink+2);  
            hbjetsInvariantMass[8]->SetLineColor(8);  
            hbjetsInvariantMass[8]->SetLineStyle(1); 
        }
        hbjetsInvariantMass[r]->GetXaxis()->SetTitle("M_{b1,b2} [GeV]");
        hbjetsInvariantMass[r]->GetXaxis()->SetLabelFont(132);
        hbjetsInvariantMass[r]->GetXaxis()->SetTitleFont(22);
        hbjetsInvariantMass[r]->GetXaxis()->SetTitleOffset(1.10);
        hbjetsInvariantMass[r]->GetYaxis()->SetTitle("Normalized distribution");
        hbjetsInvariantMass[r]->GetYaxis()->SetLabelFont(132);
        hbjetsInvariantMass[r]->GetYaxis()->SetTitleFont(22);
        hbjetsInvariantMass[r]->GetYaxis()->SetTitleOffset(1.10);
        //hbjetsInvariantMass[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hMET[r]->Scale(1 /(hMET[r]->Integral()));
        hMET[r]->SetLineStyle(2+r);
        hMET[r]->SetLineWidth(2);
        if (r < 2){ hMET[r]->SetLineColor(600-1-r);  hMET[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hMET[r]->SetLineStyle(2+r);
            //hMET[r]->SetLineColor(632-1-r); 
            hMET[2]->SetLineColor(2);  
            hMET[3]->SetLineColor(3);  
            hMET[4]->SetLineColor(7);  
            hMET[5]->SetLineColor(6);  
            hMET[6]->SetLineColor(kOrange-3);  
            hMET[7]->SetLineColor(kPink+2);  
            hMET[8]->SetLineColor(8);  
            hMET[8]->SetLineStyle(1); 
        }
        hMET[r]->GetXaxis()->SetTitle("Missing transverse momentum [GeV]");
        hMET[r]->GetXaxis()->SetLabelFont(132);
        hMET[r]->GetXaxis()->SetTitleFont(22);
        hMET[r]->GetXaxis()->SetTitleOffset(1.10);
        hMET[r]->GetYaxis()->SetTitle("Normalized distribution");
        hMET[r]->GetYaxis()->SetLabelFont(132);
        hMET[r]->GetYaxis()->SetTitleFont(22);
        hMET[r]->GetYaxis()->SetTitleOffset(1.10);
        //hMET[r]->GetYaxis()->SetRangeUser(0.0, .1);

        hHT[r]->Scale(1 /(hHT[r]->Integral()));
        hHT[r]->SetLineStyle(2+r);
        hHT[r]->SetLineWidth(2);
        if (r < 2){ hHT[r]->SetLineColor(600-1-r);  hHT[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hHT[r]->SetLineStyle(2+r);
            //hHT[r]->SetLineColor(632-1-r); 
            hHT[2]->SetLineColor(2);  
            hHT[3]->SetLineColor(3);  
            hHT[4]->SetLineColor(7);  
            hHT[5]->SetLineColor(6);  
            hHT[6]->SetLineColor(kOrange-3);  
            hHT[7]->SetLineColor(kPink+2);  
            hHT[8]->SetLineColor(8);  
            hHT[8]->SetLineStyle(1); 
        }
        hHT[r]->GetXaxis()->SetTitle("H_{T} [GeV]");
        hHT[r]->GetXaxis()->SetLabelFont(132);
        hHT[r]->GetXaxis()->SetTitleFont(22);
        hHT[r]->GetXaxis()->SetTitleOffset(1.10);
        hHT[r]->GetYaxis()->SetTitle("Normalized distribution");
        hHT[r]->GetYaxis()->SetLabelFont(132);
        hHT[r]->GetYaxis()->SetTitleFont(22);
        hHT[r]->GetYaxis()->SetTitleOffset(1.10);
        //hHT[r]->GetYaxis()->SetRangeUser(0.0, .07);

        hdeltaeta_bjets[r]->Scale(1 /(hdeltaeta_bjets[r]->Integral()));
        hdeltaeta_bjets[r]->SetLineStyle(2+r);
        hdeltaeta_bjets[r]->SetLineWidth(2);
        if (r < 2){ hdeltaeta_bjets[r]->SetLineColor(600-1-r);  hdeltaeta_bjets[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaeta_bjets[r]->SetLineStyle(2+r);
            //hdeltaeta_bjets[r]->SetLineColor(632-1-r); 
            hdeltaeta_bjets[2]->SetLineColor(2);  
            hdeltaeta_bjets[3]->SetLineColor(3);  
            hdeltaeta_bjets[4]->SetLineColor(7);  
            hdeltaeta_bjets[5]->SetLineColor(6);  
            hdeltaeta_bjets[6]->SetLineColor(kOrange-3);  
            hdeltaeta_bjets[7]->SetLineColor(kPink+2);  
            hdeltaeta_bjets[8]->SetLineColor(8); 
            hdeltaeta_bjets[8]->SetLineStyle(1);  
        }
        hdeltaeta_bjets[r]->GetXaxis()->SetTitle("#Delta#eta_{b1,b2}");
        hdeltaeta_bjets[r]->GetXaxis()->SetLabelFont(132);
        hdeltaeta_bjets[r]->GetXaxis()->SetTitleFont(22);
        hdeltaeta_bjets[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaeta_bjets[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaeta_bjets[r]->GetYaxis()->SetLabelFont(132);
        hdeltaeta_bjets[r]->GetYaxis()->SetTitleFont(22);
        hdeltaeta_bjets[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaeta_bjets[r]->GetYaxis()->SetRangeUser(0.0, .18);

        hdeltaeta_jetbjet[r]->Scale(1 /(hdeltaeta_jetbjet[r]->Integral()));
        hdeltaeta_jetbjet[r]->SetLineStyle(2+r);
        hdeltaeta_jetbjet[r]->SetLineWidth(2);
        if (r < 2){ hdeltaeta_jetbjet[r]->SetLineColor(600-1-r);  hdeltaeta_jetbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaeta_jetbjet[r]->SetLineStyle(2+r);
            //hdeltaeta_jetbjet[r]->SetLineColor(632-1-r); 
            hdeltaeta_jetbjet[2]->SetLineColor(2);  
            hdeltaeta_jetbjet[3]->SetLineColor(3);  
            hdeltaeta_jetbjet[4]->SetLineColor(7);  
            hdeltaeta_jetbjet[5]->SetLineColor(6);  
            hdeltaeta_jetbjet[6]->SetLineColor(kOrange-3);  
            hdeltaeta_jetbjet[7]->SetLineColor(kPink+2);  
            hdeltaeta_jetbjet[8]->SetLineColor(8);  
            hdeltaeta_jetbjet[8]->SetLineStyle(1); 
        }
        hdeltaeta_jetbjet[r]->GetXaxis()->SetTitle("#Delta#eta_{j,b1}");
        hdeltaeta_jetbjet[r]->GetXaxis()->SetLabelFont(132);
        hdeltaeta_jetbjet[r]->GetXaxis()->SetTitleFont(22);
        hdeltaeta_jetbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaeta_jetbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaeta_jetbjet[r]->GetYaxis()->SetLabelFont(132);
        hdeltaeta_jetbjet[r]->GetYaxis()->SetTitleFont(22);
        hdeltaeta_jetbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaeta_jetbjet[r]->GetYaxis()->SetRangeUser(0.0, .1);

        hdeltaeta_jetsubbjet[r]->Scale(1 /(hdeltaeta_jetsubbjet[r]->Integral()));
        hdeltaeta_jetsubbjet[r]->SetLineStyle(2+r);
        hdeltaeta_jetsubbjet[r]->SetLineWidth(2);
        if (r < 2){ hdeltaeta_jetsubbjet[r]->SetLineColor(600-1-r);  hdeltaeta_jetsubbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaeta_jetsubbjet[r]->SetLineStyle(2+r);
            //hdeltaeta_jetsubbjet[r]->SetLineColor(632-1-r); 
            hdeltaeta_jetsubbjet[2]->SetLineColor(2);  
            hdeltaeta_jetsubbjet[3]->SetLineColor(3);  
            hdeltaeta_jetsubbjet[4]->SetLineColor(7);  
            hdeltaeta_jetsubbjet[5]->SetLineColor(6);  
            hdeltaeta_jetsubbjet[6]->SetLineColor(kOrange-3);  
            hdeltaeta_jetsubbjet[7]->SetLineColor(kPink+2);  
            hdeltaeta_jetsubbjet[8]->SetLineColor(8);  
            hdeltaeta_jetsubbjet[8]->SetLineStyle(1); 
        }
        hdeltaeta_jetsubbjet[r]->GetXaxis()->SetTitle("#Delta#eta_{j,b2}");
        hdeltaeta_jetsubbjet[r]->GetXaxis()->SetLabelFont(132);
        hdeltaeta_jetsubbjet[r]->GetXaxis()->SetTitleFont(22);
        hdeltaeta_jetsubbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaeta_jetsubbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaeta_jetsubbjet[r]->GetYaxis()->SetLabelFont(132);
        hdeltaeta_jetsubbjet[r]->GetYaxis()->SetTitleFont(22);
        hdeltaeta_jetsubbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaeta_jetsubbjet[r]->GetYaxis()->SetRangeUser(0.0, .1);

        hdeltaphi_bjets[r]->Scale(1 /(hdeltaphi_bjets[r]->Integral()));
        hdeltaphi_bjets[r]->SetLineStyle(2+r);
        hdeltaphi_bjets[r]->SetLineWidth(2);
        if (r < 2){ hdeltaphi_bjets[r]->SetLineColor(600-1-r);  hdeltaphi_bjets[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaphi_bjets[r]->SetLineStyle(2+r);
            //hdeltaphi_bjets[r]->SetLineColor(632-1-r); 
            hdeltaphi_bjets[2]->SetLineColor(2);  
            hdeltaphi_bjets[3]->SetLineColor(3);  
            hdeltaphi_bjets[4]->SetLineColor(7);  
            hdeltaphi_bjets[5]->SetLineColor(6);  
            hdeltaphi_bjets[6]->SetLineColor(kOrange-3);  
            hdeltaphi_bjets[7]->SetLineColor(kPink+2);  
            hdeltaphi_bjets[8]->SetLineColor(8);  
            hdeltaphi_bjets[8]->SetLineStyle(1); 
        }
        hdeltaphi_bjets[r]->GetXaxis()->SetTitle("#Delta#phi_{b1,b2}");
        hdeltaphi_bjets[r]->GetXaxis()->SetLabelFont(132);
        hdeltaphi_bjets[r]->GetXaxis()->SetTitleFont(22);
        hdeltaphi_bjets[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaphi_bjets[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaphi_bjets[r]->GetYaxis()->SetLabelFont(132);
        hdeltaphi_bjets[r]->GetYaxis()->SetTitleFont(22);
        hdeltaphi_bjets[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaphi_bjets[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hdeltaphi_jetbjet[r]->Scale(1 /(hdeltaphi_jetbjet[r]->Integral()));
        hdeltaphi_jetbjet[r]->SetLineStyle(2+r);
        hdeltaphi_jetbjet[r]->SetLineWidth(2);
        if (r < 2){ hdeltaphi_jetbjet[r]->SetLineColor(600-1-r);  hdeltaphi_jetbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaphi_jetbjet[r]->SetLineStyle(2+r);
            //hdeltaphi_jetbjet[r]->SetLineColor(632-1-r); 
            hdeltaphi_jetbjet[2]->SetLineColor(2);  
            hdeltaphi_jetbjet[3]->SetLineColor(3);  
            hdeltaphi_jetbjet[4]->SetLineColor(7);  
            hdeltaphi_jetbjet[5]->SetLineColor(6);  
            hdeltaphi_jetbjet[6]->SetLineColor(kOrange-3);  
            hdeltaphi_jetbjet[7]->SetLineColor(kPink+2);  
            hdeltaphi_jetbjet[8]->SetLineColor(8);  
            hdeltaphi_jetbjet[8]->SetLineStyle(1); 
        }
        hdeltaphi_jetbjet[r]->GetXaxis()->SetTitle("#Delta#phi_{j,b1}");
        hdeltaphi_jetbjet[r]->GetXaxis()->SetLabelFont(132);
        hdeltaphi_jetbjet[r]->GetXaxis()->SetTitleFont(22);
        hdeltaphi_jetbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaphi_jetbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaphi_jetbjet[r]->GetYaxis()->SetLabelFont(132);
        hdeltaphi_jetbjet[r]->GetYaxis()->SetTitleFont(22);
        hdeltaphi_jetbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaphi_jetbjet[r]->GetYaxis()->SetRangeUser(0.0, .1);

        hdeltaphi_jetsubbjet[r]->Scale(1 /(hdeltaphi_jetsubbjet[r]->Integral()));
        hdeltaphi_jetsubbjet[r]->SetLineStyle(2+r);
        hdeltaphi_jetsubbjet[r]->SetLineWidth(2);
        if (r < 2){ hdeltaphi_jetsubbjet[r]->SetLineColor(600-1-r);  hdeltaphi_jetsubbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaphi_jetsubbjet[r]->SetLineStyle(2+r);
            //hdeltaphi_jetsubbjet[r]->SetLineColor(632-1-r); 
            hdeltaphi_jetsubbjet[2]->SetLineColor(2);  
            hdeltaphi_jetsubbjet[3]->SetLineColor(3);  
            hdeltaphi_jetsubbjet[4]->SetLineColor(7);  
            hdeltaphi_jetsubbjet[5]->SetLineColor(6);  
            hdeltaphi_jetsubbjet[6]->SetLineColor(kOrange-3);  
            hdeltaphi_jetsubbjet[7]->SetLineColor(kPink+2);  
            hdeltaphi_jetsubbjet[8]->SetLineColor(8);  
            hdeltaphi_jetsubbjet[8]->SetLineStyle(1); 
        }
        hdeltaphi_jetsubbjet[r]->GetXaxis()->SetTitle("#Delta#phi_{j,b2}");
        hdeltaphi_jetsubbjet[r]->GetXaxis()->SetLabelFont(132);
        hdeltaphi_jetsubbjet[r]->GetXaxis()->SetTitleFont(22);
        hdeltaphi_jetsubbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaphi_jetsubbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaphi_jetsubbjet[r]->GetYaxis()->SetLabelFont(132);
        hdeltaphi_jetsubbjet[r]->GetYaxis()->SetTitleFont(22);
        hdeltaphi_jetsubbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaphi_jetsubbjet[r]->GetYaxis()->SetRangeUser(0.0, .1);

        hdeltaR_bjets[r]->Scale(1 /(hdeltaR_bjets[r]->Integral()));
        hdeltaR_bjets[r]->SetLineStyle(2+r);
        hdeltaR_bjets[r]->SetLineWidth(2);
        if (r < 2){ hdeltaR_bjets[r]->SetLineColor(600-1-r);  hdeltaR_bjets[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaR_bjets[r]->SetLineStyle(2+r);
            //hdeltaR_bjets[r]->SetLineColor(632-1-r); 
            hdeltaR_bjets[2]->SetLineColor(2);  
            hdeltaR_bjets[3]->SetLineColor(3);  
            hdeltaR_bjets[4]->SetLineColor(7);  
            hdeltaR_bjets[5]->SetLineColor(6);  
            hdeltaR_bjets[6]->SetLineColor(kOrange-3);  
            hdeltaR_bjets[7]->SetLineColor(kPink+2);  
            hdeltaR_bjets[8]->SetLineColor(8);  
            hdeltaR_bjets[8]->SetLineStyle(1); 
        }
        hdeltaR_bjets[r]->GetXaxis()->SetTitle("#DeltaR(b_{1},b_{2})");
        hdeltaR_bjets[r]->GetXaxis()->SetLabelFont(132);
        hdeltaR_bjets[r]->GetXaxis()->SetTitleFont(22);
        hdeltaR_bjets[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaR_bjets[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaR_bjets[r]->GetYaxis()->SetLabelFont(132);
        hdeltaR_bjets[r]->GetYaxis()->SetTitleFont(22);
        hdeltaR_bjets[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaR_bjets[r]->GetYaxis()->SetRangeUser(0.0, .3);

        hdeltaR_jetbjet[r]->Scale(1 /(hdeltaR_jetbjet[r]->Integral()));
        hdeltaR_jetbjet[r]->SetLineStyle(2+r);
        hdeltaR_jetbjet[r]->SetLineWidth(2);
        if (r < 2){ hdeltaR_jetbjet[r]->SetLineColor(600-1-r);  hdeltaR_jetbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaR_jetbjet[r]->SetLineStyle(2+r);
            //hdeltaR_jetbjet[r]->SetLineColor(632-1-r); 
            hdeltaR_jetbjet[2]->SetLineColor(2);  
            hdeltaR_jetbjet[3]->SetLineColor(3);  
            hdeltaR_jetbjet[4]->SetLineColor(7);  
            hdeltaR_jetbjet[5]->SetLineColor(6);  
            hdeltaR_jetbjet[6]->SetLineColor(kOrange-3);  
            hdeltaR_jetbjet[7]->SetLineColor(kPink+2);  
            hdeltaR_jetbjet[8]->SetLineColor(8);  
            hdeltaR_jetbjet[8]->SetLineStyle(1); 
        }
        hdeltaR_jetbjet[r]->GetXaxis()->SetTitle("#DeltaR(j,b_{1})");
        hdeltaR_jetbjet[r]->GetXaxis()->SetLabelFont(132);
        hdeltaR_jetbjet[r]->GetXaxis()->SetTitleFont(22);
        hdeltaR_jetbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaR_jetbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaR_jetbjet[r]->GetYaxis()->SetLabelFont(132);
        hdeltaR_jetbjet[r]->GetYaxis()->SetTitleFont(22);
        hdeltaR_jetbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaR_jetbjet[r]->GetYaxis()->SetRangeUser(0.0, .15);

        hdeltaR_jetsubbjet[r]->Scale(1 /(hdeltaR_jetsubbjet[r]->Integral()));
        hdeltaR_jetsubbjet[r]->SetLineStyle(2+r);
        hdeltaR_jetsubbjet[r]->SetLineWidth(2);
        if (r < 2){ hdeltaR_jetsubbjet[r]->SetLineColor(600-1-r);  hdeltaR_jetsubbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hdeltaR_jetsubbjet[r]->SetLineStyle(2+r);
            //hdeltaR_jetsubbjet[r]->SetLineColor(632-1-r); 
            hdeltaR_jetsubbjet[2]->SetLineColor(2);  
            hdeltaR_jetsubbjet[3]->SetLineColor(3);  
            hdeltaR_jetsubbjet[4]->SetLineColor(7);  
            hdeltaR_jetsubbjet[5]->SetLineColor(6);  
            hdeltaR_jetsubbjet[6]->SetLineColor(kOrange-3);  
            hdeltaR_jetsubbjet[7]->SetLineColor(kPink+2);  
            hdeltaR_jetsubbjet[8]->SetLineColor(8);  
            hdeltaR_jetsubbjet[8]->SetLineStyle(1); 
        }
        hdeltaR_jetsubbjet[r]->GetXaxis()->SetTitle("#DeltaR(j,b_{2})");
        hdeltaR_jetsubbjet[r]->GetXaxis()->SetLabelFont(132);
        hdeltaR_jetsubbjet[r]->GetXaxis()->SetTitleFont(22);
        hdeltaR_jetsubbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hdeltaR_jetsubbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hdeltaR_jetsubbjet[r]->GetYaxis()->SetLabelFont(132);
        hdeltaR_jetsubbjet[r]->GetYaxis()->SetTitleFont(22);
        hdeltaR_jetsubbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hdeltaR_jetsubbjet[r]->GetYaxis()->SetRangeUser(0.0, .15);

        hcos_bjets[r]->Scale(1 /(hcos_bjets[r]->Integral()));
        hcos_bjets[r]->SetLineStyle(2+r);
        hcos_bjets[r]->SetLineWidth(2);
        if (r < 2){ hcos_bjets[r]->SetLineColor(600-1-r);  hcos_bjets[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hcos_bjets[r]->SetLineStyle(2+r);
            //hcos_bjets[r]->SetLineColor(632-1-r); 
            hcos_bjets[2]->SetLineColor(2);  
            hcos_bjets[3]->SetLineColor(3);  
            hcos_bjets[4]->SetLineColor(7);  
            hcos_bjets[5]->SetLineColor(6);  
            hcos_bjets[6]->SetLineColor(kOrange-3);  
            hcos_bjets[7]->SetLineColor(kPink+2);  
            hcos_bjets[8]->SetLineColor(8);  
            hcos_bjets[8]->SetLineStyle(1); 
        }
        hcos_bjets[r]->GetXaxis()->SetTitle("cos (b_{1},b_{2})");
        hcos_bjets[r]->GetXaxis()->SetLabelFont(132);
        hcos_bjets[r]->GetXaxis()->SetTitleFont(22);
        hcos_bjets[r]->GetXaxis()->SetTitleOffset(1.10);
        hcos_bjets[r]->GetYaxis()->SetTitle("Normalized distribution");
        hcos_bjets[r]->GetYaxis()->SetLabelFont(132);
        hcos_bjets[r]->GetYaxis()->SetTitleFont(22);
        hcos_bjets[r]->GetYaxis()->SetTitleOffset(1.10);
        //hcos_bjets[r]->GetYaxis()->SetRangeUser(0.0, .2);

        hcos_jetbjet[r]->Scale(1 /(hcos_jetbjet[r]->Integral()));
        hcos_jetbjet[r]->SetLineStyle(2+r);
        hcos_jetbjet[r]->SetLineWidth(2);
        if (r < 2){ hcos_jetbjet[r]->SetLineColor(600-1-r);  hcos_jetbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hcos_jetbjet[r]->SetLineStyle(2+r);
            //hcos_jetbjet[r]->SetLineColor(632-1-r); 
            hcos_jetbjet[2]->SetLineColor(2);  
            hcos_jetbjet[3]->SetLineColor(3);  
            hcos_jetbjet[4]->SetLineColor(7);  
            hcos_jetbjet[5]->SetLineColor(6);  
            hcos_jetbjet[6]->SetLineColor(kOrange-3);  
            hcos_jetbjet[7]->SetLineColor(kPink+2);  
            hcos_jetbjet[8]->SetLineColor(8);  
            hcos_jetbjet[8]->SetLineStyle(1); 
        }
        hcos_jetbjet[r]->GetXaxis()->SetTitle("cos (j,b_{1})");
        hcos_jetbjet[r]->GetXaxis()->SetLabelFont(132);
        hcos_jetbjet[r]->GetXaxis()->SetTitleFont(22);
        hcos_jetbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hcos_jetbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hcos_jetbjet[r]->GetYaxis()->SetLabelFont(132);
        hcos_jetbjet[r]->GetYaxis()->SetTitleFont(22);
        hcos_jetbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hcos_jetbjet[r]->GetYaxis()->SetRangeUser(0.0, .45);

        hcos_jetsubbjet[r]->Scale(1 /(hcos_jetsubbjet[r]->Integral()));
        hcos_jetsubbjet[r]->SetLineStyle(2+r);
        hcos_jetsubbjet[r]->SetLineWidth(2);
        if (r < 2){ hcos_jetsubbjet[r]->SetLineColor(600-1-r);  hcos_jetsubbjet[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hcos_jetsubbjet[r]->SetLineStyle(2+r);
            //hcos_jetsubbjet[r]->SetLineColor(632-1-r); 
            hcos_jetsubbjet[2]->SetLineColor(2);  
            hcos_jetsubbjet[3]->SetLineColor(3);  
            hcos_jetsubbjet[4]->SetLineColor(7);  
            hcos_jetsubbjet[5]->SetLineColor(6);  
            hcos_jetsubbjet[6]->SetLineColor(kOrange-3);  
            hcos_jetsubbjet[7]->SetLineColor(kPink+2);  
            hcos_jetsubbjet[8]->SetLineColor(8);  
            hcos_jetsubbjet[8]->SetLineStyle(1); 
        }
        hcos_jetsubbjet[r]->GetXaxis()->SetTitle("cos (j,b2)");
        hcos_jetsubbjet[r]->GetXaxis()->SetLabelFont(132);
        hcos_jetsubbjet[r]->GetXaxis()->SetTitleFont(22);
        hcos_jetsubbjet[r]->GetXaxis()->SetTitleOffset(1.10);
        hcos_jetsubbjet[r]->GetYaxis()->SetTitle("Normalized distribution");
        hcos_jetsubbjet[r]->GetYaxis()->SetLabelFont(132);
        hcos_jetsubbjet[r]->GetYaxis()->SetTitleFont(22);
        hcos_jetsubbjet[r]->GetYaxis()->SetTitleOffset(1.10);
        //hcos_jetsubbjet[r]->GetYaxis()->SetRangeUser(0.0, .4);

        hjetmultiplicity[r]->Scale(1 /(hjetmultiplicity[r]->Integral()));
        hjetmultiplicity[r]->SetLineStyle(2+r);
        hjetmultiplicity[r]->SetLineWidth(2);
        if (r < 2){ hjetmultiplicity[r]->SetLineColor(600-1-r);  hjetmultiplicity[r]->SetLineStyle(2+r);}
        if (r > 1 && r < 9){
            hjetmultiplicity[r]->SetLineStyle(2+r);
            //hjetmultiplicity[r]->SetLineColor(632-1-r); 
            hjetmultiplicity[2]->SetLineColor(2);  
            hjetmultiplicity[3]->SetLineColor(3);  
            hjetmultiplicity[4]->SetLineColor(7);  
            hjetmultiplicity[5]->SetLineColor(6);  
            hjetmultiplicity[6]->SetLineColor(kOrange-3);  
            hjetmultiplicity[7]->SetLineColor(kPink+2);  
            hjetmultiplicity[8]->SetLineColor(8);  
            hjetmultiplicity[8]->SetLineStyle(1); 
        }
        hjetmultiplicity[r]->GetXaxis()->SetTitle("Jet multiplicity");
        hjetmultiplicity[r]->GetXaxis()->SetLabelFont(132);
        hjetmultiplicity[r]->GetXaxis()->SetTitleFont(22);
        hjetmultiplicity[r]->GetXaxis()->SetTitleOffset(1.10);
        hjetmultiplicity[r]->GetYaxis()->SetTitle("Normalized distribution");
        hjetmultiplicity[r]->GetYaxis()->SetLabelFont(132);
        hjetmultiplicity[r]->GetYaxis()->SetTitleFont(22);
        hjetmultiplicity[r]->GetYaxis()->SetTitleOffset(1.10);
        //hjetmultiplicity[r]->GetYaxis()->SetRangeUser(0.0, .2);

        if (r == 0)
        {
            c1->cd(1);    hjet_pt[r]->Draw();    
            c2->cd(1);    hbjet_pt[r]->Draw();
            c3->cd(1);    hsubbjet_pt[r]->Draw();

            c4->cd(1);    hjet_eta[r]->Draw();
            c5->cd(1);    hbjet_eta[r]->Draw();
            c6->cd(1);    hsubbjet_eta[r]->Draw();

            c7->cd(1);    hjet_E[r]->Draw();
            c8->cd(1);    hbjet_E[r]->Draw();
            c9->cd(1);    hsubbjet_E[r]->Draw();

            c10->cd(1);    hbjetsInvariantMass[r]->Draw();
            c11->cd(1);    hMET[r]->Draw();
            c12->cd(1);    hHT[r]->Draw();

            c13->cd(1);    hdeltaeta_bjets[r]->Draw();
            c14->cd(1);    hdeltaeta_jetbjet[r]->Draw();
            c15->cd(1);    hdeltaeta_jetsubbjet[r]->Draw();

            c16->cd(1);    hdeltaphi_bjets[r]->Draw();
            c17->cd(1);    hdeltaphi_jetbjet[r]->Draw();
            c18->cd(1);    hdeltaphi_jetsubbjet[r]->Draw();

            c19->cd(1);    hdeltaR_bjets[r]->Draw();
            c20->cd(1);    hdeltaR_jetbjet[r]->Draw();
            c21->cd(1);    hdeltaR_jetsubbjet[r]->Draw();

            c22->cd(1);    hcos_bjets[r]->Draw();
            c23->cd(1);    hcos_jetbjet[r]->Draw();
            c24->cd(1);    hcos_jetsubbjet[r]->Draw();

            c25->cd(1);    hjetmultiplicity[r]->Draw();

        }
        else
        {
            c1->cd(1);    hjet_pt[r]->Draw("same");
            c2->cd(1);    hbjet_pt[r]->Draw("same");
            c3->cd(1);    hsubbjet_pt[r]->Draw("same");

            c4->cd(1);    hjet_eta[r]->Draw("same");
            c5->cd(1);    hbjet_eta[r]->Draw("same");
            c6->cd(1);    hsubbjet_eta[r]->Draw("same");

            c7->cd(1);    hjet_E[r]->Draw("same");
            c8->cd(1);    hbjet_E[r]->Draw("same");
            c9->cd(1);    hsubbjet_E[r]->Draw("same");

            c10->cd(1);    hbjetsInvariantMass[r]->Draw("same");
            c11->cd(1);    hMET[r]->Draw("same");
            c12->cd(1);    hHT[r]->Draw("same");

            c13->cd(1);    hdeltaeta_bjets[r]->Draw("same");
            c14->cd(1);    hdeltaeta_jetbjet[r]->Draw("same");
            c15->cd(1);    hdeltaeta_jetsubbjet[r]->Draw("same");

            c16->cd(1);    hdeltaphi_bjets[r]->Draw("same");
            c17->cd(1);    hdeltaphi_jetbjet[r]->Draw("same");
            c18->cd(1);    hdeltaphi_jetsubbjet[r]->Draw("same");

            c19->cd(1);    hdeltaR_bjets[r]->Draw("same");
            c20->cd(1);    hdeltaR_jetbjet[r]->Draw("same");
            c21->cd(1);    hdeltaR_jetsubbjet[r]->Draw("same");

            c22->cd(1);    hcos_bjets[r]->Draw("same");
            c23->cd(1);    hcos_jetbjet[r]->Draw("same");
            c24->cd(1);    hcos_jetsubbjet[r]->Draw("same");

            c25->cd(1);    hjetmultiplicity[r]->Draw("same");

        }

    } // other loop over samples

        c1->cd(1);
        TLegend *legend1 = new TLegend(0.65,0.4,0.83,0.87);// or: (0.73,0.6,0.87,0.87)
        legend1->SetMargin(0.5); 
        legend1->SetNColumns(1);
        //legend1->AddEntry(hjet_pt[0], "#font[12]{xtar}", "l"); //#font[132]
        legend1->AddEntry(hjet_pt[0], "#font[12]{X^{b}_{R}}", "l");
        //legend1->AddEntry(hjet_pt[2], "#font[12]{xtr}", "l");
        //legend1->AddEntry(hjet_pt[3], "#font[12]{xtai}", "l");
        legend1->AddEntry(hjet_pt[1], "#font[12]{X^{b}_{I}}", "l");
        //legend1->AddEntry(hjet_pt[5], "#font[12]{xti}", "l");
        legend1->AddEntry(hjet_pt[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend1->AddEntry(hjet_pt[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend1->AddEntry(hjet_pt[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend1->AddEntry(hjet_pt[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend1->AddEntry(hjet_pt[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend1->AddEntry(hjet_pt[7], "#font[12]{#nu_{e}jt}", "l");
        legend1->AddEntry(hjet_pt[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend1->SetLineStyle(1);
        legend1->SetLineWidth(1);
        legend1->SetTextSize(0.035);
        //legend1->SetTextSize(0.045);
        legend1->SetLineColor(10);
        legend1->SetFillColor(10);
        legend1->Draw();

        c2->cd(1);
        TLegend *legend2 = new TLegend(0.65,0.4,0.83,0.87);
        legend2->SetMargin(0.5);
        legend2->SetNColumns(1);
        //legend2->AddEntry(hbjet_pt[0], "#font[12]{xtar}", "l");
        legend2->AddEntry(hbjet_pt[0], "#font[12]{X^{b}_{R}}", "l");
        //legend2->AddEntry(hbjet_pt[2], "#font[12]{xtr}", "l");
        //legend2->AddEntry(hbjet_pt[3], "#font[12]{xtai}", "l");
        legend2->AddEntry(hbjet_pt[1], "#font[12]{X^{b}_{I}}", "l");
        //legend2->AddEntry(hbjet_pt[5], "#font[12]{xti}", "l");
        legend2->AddEntry(hbjet_pt[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend2->AddEntry(hbjet_pt[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend2->AddEntry(hbjet_pt[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend2->AddEntry(hbjet_pt[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend2->AddEntry(hbjet_pt[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend2->AddEntry(hbjet_pt[7], "#font[12]{#nu_{e}jt}", "l");
        legend2->AddEntry(hbjet_pt[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend2->SetLineStyle(1);
        legend2->SetLineWidth(1);
        legend2->SetTextSize(0.035);
        legend2->SetLineColor(10);
        legend2->SetFillColor(10);
        legend2->Draw();

        c3->cd(1);
        TLegend *legend3 = new TLegend(0.65,0.4,0.83,0.87);
        legend3->SetMargin(0.5);
        legend3->SetNColumns(1);
        //legend3->AddEntry(hsubbjet_pt[0], "#font[12]{xtar}", "l");
        legend3->AddEntry(hsubbjet_pt[0], "#font[12]{X^{b}_{R}}", "l");
        //legend3->AddEntry(hsubbjet_pt[2], "#font[12]{xtr}", "l");
        //legend3->AddEntry(hsubbjet_pt[3], "#font[12]{xtai}", "l");
        legend3->AddEntry(hsubbjet_pt[1], "#font[12]{X^{b}_{I}}", "l");
        //legend3->AddEntry(hsubbjet_pt[5], "#font[12]{xti}", "l");
        legend3->AddEntry(hsubbjet_pt[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend3->AddEntry(hsubbjet_pt[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend3->AddEntry(hsubbjet_pt[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend3->AddEntry(hsubbjet_pt[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend3->AddEntry(hsubbjet_pt[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend3->AddEntry(hsubbjet_pt[7], "#font[12]{#nu_{e}jt}", "l");
        legend3->AddEntry(hsubbjet_pt[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend3->SetLineStyle(1);
        legend3->SetLineWidth(1);
        legend3->SetTextSize(0.035);
        legend3->SetLineColor(10);
        legend3->SetFillColor(10);
        legend3->Draw();

        c4->cd(1);
        TLegend *legend4 = new TLegend(0.65,0.4,0.83,0.87);
        legend4->SetMargin(0.5);
        legend4->SetNColumns(1);
        //legend4->AddEntry(hjet_eta[0], "#font[12]{xtar}", "l");
        legend4->AddEntry(hjet_eta[0], "#font[12]{X^{b}_{R}}", "l");
        //legend4->AddEntry(hjet_eta[2], "#font[12]{xtr}", "l");
        //legend4->AddEntry(hjet_eta[3], "#font[12]{xtai}", "l");
        legend4->AddEntry(hjet_eta[1], "#font[12]{X^{b}_{I}}", "l");
        //legend4->AddEntry(hjet_eta[5], "#font[12]{xti}", "l");
        legend4->AddEntry(hjet_eta[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend4->AddEntry(hjet_eta[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend4->AddEntry(hjet_eta[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend4->AddEntry(hjet_eta[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend4->AddEntry(hjet_eta[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend4->AddEntry(hjet_eta[7], "#font[12]{#nu_{e}jt}", "l");
        legend4->AddEntry(hjet_eta[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend4->SetLineStyle(1);
        legend4->SetLineWidth(1);
        legend4->SetTextSize(0.035);
        legend4->SetLineColor(10);
        legend4->SetFillColor(10);
        legend4->Draw();

        c5->cd(1);
        TLegend *legend5 = new TLegend(0.65,0.4,0.83,0.87);
        legend5->SetMargin(0.5);
        legend5->SetNColumns(1);
        //legend5->AddEntry(hbjet_eta[0], "#font[12]{xtar}", "l");
        legend5->AddEntry(hbjet_eta[0], "#font[12]{X^{b}_{R}}", "l");
        //legend5->AddEntry(hbjet_eta[2], "#font[12]{xtr}", "l");
        //legend5->AddEntry(hbjet_eta[3], "#font[12]{xtai}", "l");
        legend5->AddEntry(hbjet_eta[1], "#font[12]{X^{b}_{I}}", "l");
        //legend5->AddEntry(hbjet_eta[5], "#font[12]{xti}", "l");
        legend5->AddEntry(hbjet_eta[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend5->AddEntry(hbjet_eta[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend5->AddEntry(hbjet_eta[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend5->AddEntry(hbjet_eta[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend5->AddEntry(hbjet_eta[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend5->AddEntry(hbjet_eta[7], "#font[12]{#nu_{e}jt}", "l");
        legend5->AddEntry(hbjet_eta[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend5->SetLineStyle(1);
        legend5->SetLineWidth(1);
        legend5->SetTextSize(0.035);
        legend5->SetLineColor(10);
        legend5->SetFillColor(10);
        legend5->Draw();

        c6->cd(1);
        TLegend *legend6 = new TLegend(0.65,0.4,0.83,0.87);
        legend6->SetMargin(0.5);
        legend6->SetNColumns(1);
        //legend6->AddEntry(hsubbjet_eta[0], "#font[12]{xtar}", "l");
        legend6->AddEntry(hsubbjet_eta[0], "#font[12]{X^{b}_{R}}", "l");
        //legend6->AddEntry(hsubbjet_eta[2], "#font[12]{xtr}", "l");
        //legend6->AddEntry(hsubbjet_eta[3], "#font[12]{xtai}", "l");
        legend6->AddEntry(hsubbjet_eta[1], "#font[12]{X^{b}_{I}}", "l");
        //legend6->AddEntry(hsubbjet_eta[5], "#font[12]{xti}", "l");
        legend6->AddEntry(hsubbjet_eta[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend6->AddEntry(hsubbjet_eta[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend6->AddEntry(hsubbjet_eta[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend6->AddEntry(hsubbjet_eta[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend6->AddEntry(hsubbjet_eta[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend6->AddEntry(hsubbjet_eta[7], "#font[12]{#nu_{e}jt}", "l");
        legend6->AddEntry(hsubbjet_eta[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend6->SetLineStyle(1);
        legend6->SetLineWidth(1);
        legend6->SetTextSize(0.035);
        legend6->SetLineColor(10);
        legend6->SetFillColor(10);
        legend6->Draw();


        c7->cd(1);
        TLegend *legend7 = new TLegend(0.65,0.4,0.83,0.87);
        legend7->SetMargin(0.5);
        legend7->SetNColumns(1);
        //legend7->AddEntry(hjet_E[0], "#font[12]{xtar}", "l");
        legend7->AddEntry(hjet_E[0], "#font[12]{X^{b}_{R}}", "l");
        //legend7->AddEntry(hjet_E[2], "#font[12]{xtr}", "l");
        //legend7->AddEntry(hjet_E[3], "#font[12]{xtai}", "l");
        legend7->AddEntry(hjet_E[1], "#font[12]{X^{b}_{I}}", "l");
        //legend7->AddEntry(hjet_E[5], "#font[12]{xti}", "l");
        legend7->AddEntry(hjet_E[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend7->AddEntry(hjet_E[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend7->AddEntry(hjet_E[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend7->AddEntry(hjet_E[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend7->AddEntry(hjet_E[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend7->AddEntry(hjet_E[7], "#font[12]{#nu_{e}jt}", "l");
        legend7->AddEntry(hjet_E[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend7->SetLineStyle(1);
        legend7->SetLineWidth(1);
        legend7->SetTextSize(0.035);
        legend7->SetLineColor(10);
        legend7->SetFillColor(10);
        legend7->Draw();

        c8->cd(1);
        TLegend *legend8 = new TLegend(0.65,0.4,0.83,0.87);
        legend8->SetMargin(0.5);
        legend8->SetNColumns(1);
        //legend8->AddEntry(hbjet_E[0], "#font[12]{xtar}", "l");
        legend8->AddEntry(hbjet_E[0], "#font[12]{X^{b}_{R}}", "l");
        //legend8->AddEntry(hbjet_E[2], "#font[12]{xtr}", "l");
        //legend8->AddEntry(hbjet_E[3], "#font[12]{xtai}", "l");
        legend8->AddEntry(hbjet_E[1], "#font[12]{X^{b}_{I}}", "l");
        //legend8->AddEntry(hbjet_E[5], "#font[12]{xti}", "l");
        legend8->AddEntry(hbjet_E[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend8->AddEntry(hbjet_E[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend8->AddEntry(hbjet_E[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend8->AddEntry(hbjet_E[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend8->AddEntry(hbjet_E[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend8->AddEntry(hbjet_E[7], "#font[12]{#nu_{e}jt}", "l");
        legend8->AddEntry(hbjet_E[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend8->SetLineStyle(1);
        legend8->SetLineWidth(1);
        legend8->SetTextSize(0.035);
        legend8->SetLineColor(10);
        legend8->SetFillColor(10);
        legend8->Draw();

        c9->cd(1);
        TLegend *legend9 = new TLegend(0.65,0.4,0.83,0.87);
        legend9->SetMargin(0.5);
        legend9->SetNColumns(1);
        //legend9->AddEntry(hsubbjet_E[0], "#font[12]{xtar}", "l");
        legend9->AddEntry(hsubbjet_E[0], "#font[12]{X^{b}_{R}}", "l");
        //legend9->AddEntry(hsubbjet_E[2], "#font[12]{xtr}", "l");
        //legend9->AddEntry(hsubbjet_E[3], "#font[12]{xtai}", "l");
        legend9->AddEntry(hsubbjet_E[1], "#font[12]{X^{b}_{I}}", "l");
        //legend9->AddEntry(hsubbjet_E[5], "#font[12]{xti}", "l");
        legend9->AddEntry(hsubbjet_E[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend9->AddEntry(hsubbjet_E[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend9->AddEntry(hsubbjet_E[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend9->AddEntry(hsubbjet_E[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend9->AddEntry(hsubbjet_E[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend9->AddEntry(hsubbjet_E[7], "#font[12]{#nu_{e}jt}", "l");
        legend9->AddEntry(hsubbjet_E[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend9->SetLineStyle(1);
        legend9->SetLineWidth(1);
        legend9->SetTextSize(0.035);
        legend9->SetLineColor(10);
        legend9->SetFillColor(10);
        legend9->Draw();

        c10->cd(1);
        TLegend *legend10 = new TLegend(0.65,0.4,0.83,0.87);
        legend10->SetMargin(0.5);
        legend10->SetNColumns(1);
        //legend10->AddEntry(hbjetsInvariantMass[0], "#font[12]{xtar}", "l");
        legend10->AddEntry(hbjetsInvariantMass[0], "#font[12]{X^{b}_{R}}", "l");
        //legend10->AddEntry(hbjetsInvariantMass[2], "#font[12]{xtr}", "l");
        //legend10->AddEntry(hbjetsInvariantMass[3], "#font[12]{xtai}", "l");
        legend10->AddEntry(hbjetsInvariantMass[1], "#font[12]{X^{b}_{I}}", "l");
        //legend10->AddEntry(hbjetsInvariantMass[5], "#font[12]{xti}", "l");
        legend10->AddEntry(hbjetsInvariantMass[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend10->AddEntry(hbjetsInvariantMass[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend10->AddEntry(hbjetsInvariantMass[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend10->AddEntry(hbjetsInvariantMass[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend10->AddEntry(hbjetsInvariantMass[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend10->AddEntry(hbjetsInvariantMass[7], "#font[12]{#nu_{e}jt}", "l");
        legend10->AddEntry(hbjetsInvariantMass[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend10->SetLineStyle(1);
        legend10->SetLineWidth(1);
        legend10->SetTextSize(0.035);
        legend10->SetLineColor(10);
        legend10->SetFillColor(10);
        legend10->Draw();

        c11->cd(1);
        TLegend *legend11 = new TLegend(0.65,0.4,0.83,0.87);
        legend11->SetMargin(0.5);
        legend11->SetNColumns(1);
        //legend11->AddEntry(hMET[0], "#font[12]{xtar}", "l");
        legend11->AddEntry(hMET[0], "#font[12]{X^{b}_{R}}", "l");
        //legend11->AddEntry(hMET[2], "#font[12]{xtr}", "l");
        //legend11->AddEntry(hMET[3], "#font[12]{xtai}", "l");
        legend11->AddEntry(hMET[1], "#font[12]{X^{b}_{I}}", "l");
        //legend11->AddEntry(hMET[5], "#font[12]{xti}", "l");
        legend11->AddEntry(hMET[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend11->AddEntry(hMET[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend11->AddEntry(hMET[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend11->AddEntry(hMET[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend11->AddEntry(hMET[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend11->AddEntry(hMET[7], "#font[12]{#nu_{e}jt}", "l");
        legend11->AddEntry(hMET[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend11->SetLineStyle(1);
        legend11->SetLineWidth(1);
        legend11->SetTextSize(0.035);
        legend11->SetLineColor(10);
        legend11->SetFillColor(10);
        legend11->Draw();


        c12->cd(1);
        TLegend *legend12 = new TLegend(0.65,0.4,0.83,0.87);
        legend12->SetMargin(0.5);
        legend12->SetNColumns(1);
        //legend12->AddEntry(hHT[0], "#font[12]{xtar}", "l");
        legend12->AddEntry(hHT[0], "#font[12]{X^{b}_{R}}", "l");
        //legend12->AddEntry(hHT[2], "#font[12]{xtr}", "l");
        //legend12->AddEntry(hHT[3], "#font[12]{xtai}", "l");
        legend12->AddEntry(hHT[1], "#font[12]{X^{b}_{I}}", "l");
        //legend12->AddEntry(hHT[5], "#font[12]{xti}", "l");
        legend12->AddEntry(hHT[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend12->AddEntry(hHT[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend12->AddEntry(hHT[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend12->AddEntry(hHT[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend12->AddEntry(hHT[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend12->AddEntry(hHT[7], "#font[12]{#nu_{e}jt}", "l");
        legend12->AddEntry(hHT[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend12->SetLineStyle(1);
        legend12->SetLineWidth(1);
        legend12->SetTextSize(0.035);
        legend12->SetLineColor(10);
        legend12->SetFillColor(10);
        legend12->Draw();

        c13->cd(1);
        TLegend *legend13 = new TLegend(0.65,0.4,0.83,0.87);
        legend13->SetMargin(0.5);
        legend13->SetNColumns(1);
        //legend13->AddEntry(hdeltaeta_bjets[0], "#font[12]{xtar}", "l");
        legend13->AddEntry(hdeltaeta_bjets[0], "#font[12]{X^{b}_{R}}", "l");
        //legend13->AddEntry(hdeltaeta_bjets[2], "#font[12]{xtr}", "l");
        //legend13->AddEntry(hdeltaeta_bjets[3], "#font[12]{xtai}", "l");
        legend13->AddEntry(hdeltaeta_bjets[1], "#font[12]{X^{b}_{I}}", "l");
        //legend13->AddEntry(hdeltaeta_bjets[5], "#font[12]{xti}", "l");
        legend13->AddEntry(hdeltaeta_bjets[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend13->AddEntry(hdeltaeta_bjets[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend13->AddEntry(hdeltaeta_bjets[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend13->AddEntry(hdeltaeta_bjets[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend13->AddEntry(hdeltaeta_bjets[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend13->AddEntry(hdeltaeta_bjets[7], "#font[12]{#nu_{e}jt}", "l");
        legend13->AddEntry(hdeltaeta_bjets[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend13->SetLineStyle(1);
        legend13->SetLineWidth(1);
        legend13->SetTextSize(0.035);
        legend13->SetLineColor(10);
        legend13->SetFillColor(10);
        legend13->Draw();

        c14->cd(1);
        TLegend *legend14 = new TLegend(0.65,0.4,0.83,0.87);
        legend14->SetMargin(0.5);
        legend14->SetNColumns(1);
        //legend14->AddEntry(hdeltaeta_jetbjet[0], "#font[12]{xtar}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend14->AddEntry(hdeltaeta_jetbjet[2], "#font[12]{xtr}", "l");
        //legend14->AddEntry(hdeltaeta_jetbjet[3], "#font[12]{xtai}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend14->AddEntry(hdeltaeta_jetbjet[5], "#font[12]{xti}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend14->AddEntry(hdeltaeta_jetbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend14->SetLineStyle(1);
        legend14->SetLineWidth(1);
        legend14->SetTextSize(0.035);
        legend14->SetLineColor(10);
        legend14->SetFillColor(10);
        legend14->Draw();

        c15->cd(1);
        TLegend *legend15 = new TLegend(0.65,0.4,0.83,0.87);
        legend15->SetMargin(0.5);
        legend15->SetNColumns(1);
        //legend15->AddEntry(hdeltaeta_jetsubbjet[0], "#font[12]{xtar}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend15->AddEntry(hdeltaeta_jetsubbjet[2], "#font[12]{xtr}", "l");
        //legend15->AddEntry(hdeltaeta_jetsubbjet[3], "#font[12]{xtai}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend15->AddEntry(hdeltaeta_jetsubbjet[5], "#font[12]{xti}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend15->AddEntry(hdeltaeta_jetsubbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend15->SetLineStyle(1);
        legend15->SetLineWidth(1);
        legend15->SetTextSize(0.035);
        legend15->SetLineColor(10);
        legend15->SetFillColor(10);
        legend15->Draw();

        c16->cd(1);
        TLegend *legend16 = new TLegend(0.65,0.4,0.83,0.87);
        legend16->SetMargin(0.5);
        legend16->SetNColumns(1);
        //legend16->AddEntry(hdeltaphi_bjets[0], "#font[12]{xtar}", "l");
        legend16->AddEntry(hdeltaphi_bjets[0], "#font[12]{X^{b}_{R}}", "l");
        //legend16->AddEntry(hdeltaphi_bjets[2], "#font[12]{xtr}", "l");
        //legend16->AddEntry(hdeltaphi_bjets[3], "#font[12]{xtai}", "l");
        legend16->AddEntry(hdeltaphi_bjets[1], "#font[12]{X^{b}_{I}}", "l");
        //legend16->AddEntry(hdeltaphi_bjets[5], "#font[12]{xti}", "l");
        legend16->AddEntry(hdeltaphi_bjets[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend16->AddEntry(hdeltaphi_bjets[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend16->AddEntry(hdeltaphi_bjets[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend16->AddEntry(hdeltaphi_bjets[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend16->AddEntry(hdeltaphi_bjets[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend16->AddEntry(hdeltaphi_bjets[7], "#font[12]{#nu_{e}jt}", "l");
        legend16->AddEntry(hdeltaphi_bjets[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend16->SetLineStyle(1);
        legend16->SetLineWidth(1);
        legend16->SetTextSize(0.035);
        legend16->SetLineColor(10);
        legend16->SetFillColor(10);
        legend16->Draw();


        c17->cd(1);
        TLegend *legend17 = new TLegend(0.65,0.4,0.83,0.87);
        legend17->SetMargin(0.5);
        legend17->SetNColumns(1);
        //legend17->AddEntry(hdeltaphi_jetbjet[0], "#font[12]{xtar}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend17->AddEntry(hdeltaphi_jetbjet[2], "#font[12]{xtr}", "l");
        //legend17->AddEntry(hdeltaphi_jetbjet[3], "#font[12]{xtai}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend17->AddEntry(hdeltaphi_jetbjet[5], "#font[12]{xti}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend17->AddEntry(hdeltaphi_jetbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend17->SetLineStyle(1);
        legend17->SetLineWidth(1);
        legend17->SetTextSize(0.035);
        legend17->SetLineColor(10);
        legend17->SetFillColor(10);
        legend17->Draw();

        c18->cd(1);
        TLegend *legend18 = new TLegend(0.65,0.4,0.83,0.87);
        legend18->SetMargin(0.5);
        legend18->SetNColumns(1);
        //legend18->AddEntry(hdeltaphi_jetsubbjet[0], "#font[12]{xtar}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend18->AddEntry(hdeltaphi_jetsubbjet[2], "#font[12]{xtr}", "l");
        //legend18->AddEntry(hdeltaphi_jetsubbjet[3], "#font[12]{xtai}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend18->AddEntry(hdeltaphi_jetsubbjet[5], "#font[12]{xti}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend18->AddEntry(hdeltaphi_jetsubbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend18->SetLineStyle(1);
        legend18->SetLineWidth(1);
        legend18->SetTextSize(0.035);
        legend18->SetLineColor(10);
        legend18->SetFillColor(10);
        legend18->Draw();

        c19->cd(1);
        TLegend *legend19 = new TLegend(0.65,0.4,0.83,0.87);
        legend19->SetMargin(0.5);
        legend19->SetNColumns(1);
        //legend19->AddEntry(hdeltaR_bjets[0], "#font[12]{xtar}", "l");
        legend19->AddEntry(hdeltaR_bjets[0], "#font[12]{X^{b}_{R}}", "l");
        //legend19->AddEntry(hdeltaR_bjets[2], "#font[12]{xtr}", "l");
        //legend19->AddEntry(hdeltaR_bjets[3], "#font[12]{xtai}", "l");
        legend19->AddEntry(hdeltaR_bjets[1], "#font[12]{X^{b}_{I}}", "l");
        //legend19->AddEntry(hdeltaR_bjets[5], "#font[12]{xti}", "l");
        legend19->AddEntry(hdeltaR_bjets[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend19->AddEntry(hdeltaR_bjets[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend19->AddEntry(hdeltaR_bjets[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend19->AddEntry(hdeltaR_bjets[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend19->AddEntry(hdeltaR_bjets[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend19->AddEntry(hdeltaR_bjets[7], "#font[12]{#nu_{e}jt}", "l");
        legend19->AddEntry(hdeltaR_bjets[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend19->SetLineStyle(1);
        legend19->SetLineWidth(1);
        legend19->SetTextSize(0.035);
        legend19->SetLineColor(10);
        legend19->SetFillColor(10);
        legend19->Draw();

        c20->cd(1);
        TLegend *legend20 = new TLegend(0.65,0.4,0.83,0.87);
        legend20->SetMargin(0.5);
        legend20->SetNColumns(1);
        //legend20->AddEntry(hdeltaR_jetbjet[0], "#font[12]{xtar}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend20->AddEntry(hdeltaR_jetbjet[2], "#font[12]{xtr}", "l");
        //legend20->AddEntry(hdeltaR_jetbjet[3], "#font[12]{xtai}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend20->AddEntry(hdeltaR_jetbjet[5], "#font[12]{xti}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend20->AddEntry(hdeltaR_jetbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend20->SetLineStyle(1);
        legend20->SetLineWidth(1);
        legend20->SetTextSize(0.035);
        legend20->SetLineColor(10);
        legend20->SetFillColor(10);
        legend20->Draw();

        c21->cd(1);
        TLegend *legend21 = new TLegend(0.65,0.4,0.83,0.87);
        legend21->SetMargin(0.5);
        legend21->SetNColumns(1);
        //legend21->AddEntry(hdeltaR_jetsubbjet[0], "#font[12]{xtar}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend21->AddEntry(hdeltaR_jetsubbjet[2], "#font[12]{xtr}", "l");
        //legend21->AddEntry(hdeltaR_jetsubbjet[3], "#font[12]{xtai}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend21->AddEntry(hdeltaR_jetsubbjet[5], "#font[12]{xti}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend21->AddEntry(hdeltaR_jetsubbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend21->SetLineStyle(1);
        legend21->SetLineWidth(1);
        legend21->SetTextSize(0.035);
        legend21->SetLineColor(10);
        legend21->SetFillColor(10);
        legend21->Draw();


        c22->cd(1);
        TLegend *legend22 = new TLegend(0.65,0.4,0.83,0.87);
        legend22->SetMargin(0.5);
        legend22->SetNColumns(1);
        //legend22->AddEntry(hcos_bjets[0], "#font[12]{xtar}", "l");
        legend22->AddEntry(hcos_bjets[0], "#font[12]{X^{b}_{R}}", "l");
        //legend22->AddEntry(hcos_bjets[2], "#font[12]{xtr}", "l");
        //legend22->AddEntry(hcos_bjets[3], "#font[12]{xtai}", "l");
        legend22->AddEntry(hcos_bjets[1], "#font[12]{X^{b}_{I}}", "l");
        //legend22->AddEntry(hcos_bjets[5], "#font[12]{xti}", "l");
        legend22->AddEntry(hcos_bjets[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend22->AddEntry(hcos_bjets[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend22->AddEntry(hcos_bjets[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend22->AddEntry(hcos_bjets[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend22->AddEntry(hcos_bjets[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend22->AddEntry(hcos_bjets[7], "#font[12]{#nu_{e}jt}", "l");
        legend22->AddEntry(hcos_bjets[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend22->SetLineStyle(1);
        legend22->SetLineWidth(1);
        legend22->SetTextSize(0.035);
        legend22->SetLineColor(10);
        legend22->SetFillColor(10);
        legend22->Draw();

        c23->cd(1);
        TLegend *legend23 = new TLegend(0.65,0.4,0.83,0.87);
        legend23->SetMargin(0.5);
        legend23->SetNColumns(1);
        //legend23->AddEntry(hcos_jetbjet[0], "#font[12]{xtar}", "l");
        legend23->AddEntry(hcos_jetbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend23->AddEntry(hcos_jetbjet[2], "#font[12]{xtr}", "l");
        //legend23->AddEntry(hcos_jetbjet[3], "#font[12]{xtai}", "l");
        legend23->AddEntry(hcos_jetbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend23->AddEntry(hcos_jetbjet[5], "#font[12]{xti}", "l");
        legend23->AddEntry(hcos_jetbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend23->AddEntry(hcos_jetbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend23->AddEntry(hcos_jetbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend23->AddEntry(hcos_jetbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend23->AddEntry(hcos_jetbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend23->AddEntry(hcos_jetbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend23->AddEntry(hcos_jetbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend23->SetLineStyle(1);
        legend23->SetLineWidth(1);
        legend23->SetTextSize(0.035);
        legend23->SetLineColor(10);
        legend23->SetFillColor(10);
        legend23->Draw();

        c24->cd(1);
        TLegend *legend24 = new TLegend(0.65,0.4,0.83,0.87);
        legend24->SetMargin(0.5);
        legend24->SetNColumns(1);
        //legend24->AddEntry(hcos_jetsubbjet[0], "#font[12]{xtar}", "l");
        legend24->AddEntry(hcos_jetsubbjet[0], "#font[12]{X^{b}_{R}}", "l");
        //legend24->AddEntry(hcos_jetsubbjet[2], "#font[12]{xtr}", "l");
        //legend24->AddEntry(hcos_jetsubbjet[3], "#font[12]{xtai}", "l");
        legend24->AddEntry(hcos_jetsubbjet[1], "#font[12]{X^{b}_{I}}", "l");
        //legend24->AddEntry(hcos_jetsubbjet[5], "#font[12]{xti}", "l");
        legend24->AddEntry(hcos_jetsubbjet[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend24->AddEntry(hcos_jetsubbjet[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend24->AddEntry(hcos_jetsubbjet[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend24->AddEntry(hcos_jetsubbjet[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend24->AddEntry(hcos_jetsubbjet[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend24->AddEntry(hcos_jetsubbjet[7], "#font[12]{#nu_{e}jt}", "l");
        legend24->AddEntry(hcos_jetsubbjet[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend24->SetLineStyle(1);
        legend24->SetLineWidth(1);
        legend24->SetTextSize(0.035);
        legend24->SetLineColor(10);
        legend24->SetFillColor(10);
        legend24->Draw();

        c25->cd(1);
        TLegend *legend25 = new TLegend(0.65,0.4,0.83,0.87);
        legend25->SetMargin(0.5);
        legend25->SetNColumns(1);
        //legend25->AddEntry(hjetmultiplicity[0], "#font[12]{xtar}", "l");
        legend25->AddEntry(hjetmultiplicity[0], "#font[12]{X^{b}_{R}}", "l");
        //legend25->AddEntry(hjetmultiplicity[2], "#font[12]{xtr}", "l");
        //legend25->AddEntry(hjetmultiplicity[3], "#font[12]{xtai}", "l");
        legend25->AddEntry(hjetmultiplicity[1], "#font[12]{X^{b}_{I}}", "l");
        //legend25->AddEntry(hjetmultiplicity[5], "#font[12]{xti}", "l");
        legend25->AddEntry(hjetmultiplicity[2], "#font[12]{b#bar{b}j#nu_{e}}", "l");
        legend25->AddEntry(hjetmultiplicity[3], "#font[12]{c#bar{c}j#nu_{e}}", "l");
        legend25->AddEntry(hjetmultiplicity[4], "#font[12]{#nu_{e}jZ,Z#rightarrowb#bar{b}}", "l");
        legend25->AddEntry(hjetmultiplicity[5], "#font[12]{#nu_{e}jZ,Z#rightarrowc#bar{c}}", "l");
        legend25->AddEntry(hjetmultiplicity[6], "#font[12]{#nu_{e}jZ,Z#rightarrowjj}", "l");
        legend25->AddEntry(hjetmultiplicity[7], "#font[12]{#nu_{e}jt}", "l");
        legend25->AddEntry(hjetmultiplicity[8], "#font[12]{#nu_{e}jH (SM)}", "l");
        legend25->SetLineStyle(1);
        legend25->SetLineWidth(1);
        legend25->SetTextSize(0.035);
        legend25->SetLineColor(10);
        legend25->SetFillColor(10);
        legend25->Draw();

c1->SaveAs("jet_pt.pdf");c1->SaveAs("jet_pt.C");
c2->SaveAs("bjet_pt.pdf");c2->SaveAs("bjet_pt.C");
c3->SaveAs("subbjet_pt.pdf");c3->SaveAs("subbjet_pt.C");
c4->SaveAs("jet_eta.pdf");c4->SaveAs("jet_eta.C");
c5->SaveAs("bjet_eta.pdf");c5->SaveAs("bjet_eta.C");
c6->SaveAs("subbjet_eta.pdf");c6->SaveAs("subbjet_eta.C");
c7->SaveAs("jet_E.pdf");c7->SaveAs("jet_E.C");
c8->SaveAs("bjet_E.pdf");c8->SaveAs("bjet_E.C");
c9->SaveAs("subbjet_E.pdf");c9->SaveAs("subbjet_E.C");
c10->SaveAs("bjetsInvariantMass.pdf");c10->SaveAs("bjetsInvariantMass.C");
c11->SaveAs("MET.pdf");c11->SaveAs("MET.C");
c12->SaveAs("HT.pdf");c12->SaveAs("HT.C");
c13->SaveAs("deltaeta_bjets.pdf");c13->SaveAs("deltaeta_bjets.C");
c14->SaveAs("deltaeta_jetbjet.pdf");c14->SaveAs("deltaeta_jetbjet.C");
c15->SaveAs("deltaeta_jetsubbjet.pdf");c15->SaveAs("deltaeta_jetsubbjet.C");
c16->SaveAs("deltaphi_bjets.pdf");c16->SaveAs("deltaphi_bjets.C");
c17->SaveAs("deltaphi_jetbjet.pdf");c17->SaveAs("deltaphi_jetbjet.C");
c18->SaveAs("deltaphi_jetsubbjet.pdf");c18->SaveAs("deltaphi_jetsubbjet.C");
c19->SaveAs("deltaR_bjets.pdf");c19->SaveAs("deltaR_bjets.C");
c20->SaveAs("deltaR_jetbjet.pdf");c20->SaveAs("deltaR_jetbjet.C");
c21->SaveAs("deltaR_jetsubbjet.pdf");c21->SaveAs("deltaR_jetsubbjet.C");
c22->SaveAs("cos_bjets.pdf");c22->SaveAs("cos_bjets.C");
c23->SaveAs("cos_jetbjet.pdf");c23->SaveAs("cos_jetbjet.C");
c24->SaveAs("cos_jetsubbjet.pdf");c24->SaveAs("cos_jetsubbjet.C");
c25->SaveAs("jetmultiplicity.pdf");c25->SaveAs("jetmultiplicity.C");


cout << endl;
cout << "=================================" << endl;
cout << "============= Finish ============" << endl;
cout << "=================================" << endl;

}//======================================================= analysis function



