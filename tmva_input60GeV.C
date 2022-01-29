#include <stdio.h>
#include "iostream"
#include "TH1F.h"
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



//    Double_t   sigma_MG [] = {xtar, xbr, xtr, xtai, xbi, xti, ep2bbjvbkg1, ep2ccjvbkg2, ep2vjz2bbbkg3, ep2vjz2ccbkg4, ep2vjz2jjbkg5, ep2jt2w2jjbkg6, ep2vjh2bbSMbkg7}; 
const Double_t sigma_MG [13] = { 0.048347, 0.4084 , 0.048347, 0.048347, 0.9135, 0.048347 , 0.02782, 0.06266, 0.0454442, 0.0469327, 0.2624102, 0.22345151, 0.048347}; //pb,

Double_t            sigma;
Double_t            sigma_pre;
Double_t            N_total;
Double_t            N_accepted;
Double_t            N_accepted_pre;
Double_t            efficiency_pre;
Double_t            efficiency;

//char *samplename[] = {"xtar", "xbr"};
//vector  <TString> name = {xtar, xbr, xtr, xtai, xbi, xti, ep2bbjvbkg1, ep2ccjvbkg2, ep2vjz2bbbkg3, ep2vjz2ccbkg4, ep2vjz2jjbkg5, ep2jt2w2jjbkg6, ep2vjh2bbSMbkg7};



TFile *f0 = new TFile("TMVA_input60Gev.root","RECREATE");
TFile *f;



void tmva_input60GeV(){

//======================================================= sample loop

    for(int r = 0; r < 13; r++)
    {
        cout << endl << "sample " << r << ": " << endl;

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

        if (r==0) 
        {
            TTree *tree_xtar = new TTree("tree_xtar", "xtar");

            tree_xtar->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_xtar->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_xtar->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_xtar->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_xtar->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_xtar->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_xtar->Branch("jet_E",&jet_E,"jet_E/D");
            tree_xtar->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_xtar->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_xtar->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_xtar->Branch("MET",&MET,"MET/D");
            tree_xtar->Branch("HT",&HT,"HT/D");
            tree_xtar->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_xtar->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_xtar->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_xtar->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_xtar->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_xtar->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_xtar->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_xtar->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_xtar->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_xtar->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_xtar->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_xtar->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_xtar->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("xtar.root","READ");
        }

        if (r==1) 
        {

            TTree *tree_xbr = new TTree("tree_xbr", "xbr");

            tree_xbr->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_xbr->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_xbr->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_xbr->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_xbr->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_xbr->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_xbr->Branch("jet_E",&jet_E,"jet_E/D");
            tree_xbr->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_xbr->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_xbr->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_xbr->Branch("MET",&MET,"MET/D");
            tree_xbr->Branch("HT",&HT,"HT/D");
            tree_xbr->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_xbr->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_xbr->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_xbr->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_xbr->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_xbr->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_xbr->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_xbr->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_xbr->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_xbr->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_xbr->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_xbr->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_xbr->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("xbr.root","READ");
        }

        if (r==2) 
        {

            TTree *tree_xtr = new TTree("tree_xtr", "xtr");

            tree_xtr->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_xtr->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_xtr->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_xtr->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_xtr->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_xtr->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_xtr->Branch("jet_E",&jet_E,"jet_E/D");
            tree_xtr->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_xtr->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_xtr->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_xtr->Branch("MET",&MET,"MET/D");
            tree_xtr->Branch("HT",&HT,"HT/D");
            tree_xtr->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_xtr->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_xtr->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_xtr->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_xtr->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_xtr->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_xtr->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_xtr->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_xtr->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_xtr->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_xtr->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_xtr->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_xtr->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("xtr.root","READ");
        }

        if (r==3) 
        {

            TTree *tree_xtai = new TTree("tree_xtai", "xtai");

            tree_xtai->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_xtai->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_xtai->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_xtai->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_xtai->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_xtai->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_xtai->Branch("jet_E",&jet_E,"jet_E/D");
            tree_xtai->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_xtai->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_xtai->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_xtai->Branch("MET",&MET,"MET/D");
            tree_xtai->Branch("HT",&HT,"HT/D");
            tree_xtai->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_xtai->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_xtai->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_xtai->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_xtai->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_xtai->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_xtai->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_xtai->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_xtai->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_xtai->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_xtai->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_xtai->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_xtai->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("xtai.root","READ");
        }

        if (r==4) 
        {

            TTree *tree_xbi = new TTree("tree_xbi", "xbi");

            tree_xbi->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_xbi->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_xbi->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_xbi->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_xbi->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_xbi->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_xbi->Branch("jet_E",&jet_E,"jet_E/D");
            tree_xbi->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_xbi->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_xbi->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_xbi->Branch("MET",&MET,"MET/D");
            tree_xbi->Branch("HT",&HT,"HT/D");
            tree_xbi->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_xbi->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_xbi->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_xbi->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_xbi->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_xbi->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_xbi->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_xbi->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_xbi->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_xbi->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_xbi->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_xbi->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_xbi->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");
            f = new TFile("xbi.root","READ");
        }

        if (r==5) 
        {

            TTree *tree_xti = new TTree("tree_xti", "xti");

            tree_xti->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_xti->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_xti->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_xti->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_xti->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_xti->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_xti->Branch("jet_E",&jet_E,"jet_E/D");
            tree_xti->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_xti->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_xti->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_xti->Branch("MET",&MET,"MET/D");
            tree_xti->Branch("HT",&HT,"HT/D");
            tree_xti->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_xti->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_xti->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_xti->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_xti->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_xti->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_xti->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_xti->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_xti->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_xti->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_xti->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_xti->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_xti->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("xti.root","READ");
        }

        if (r==6) 
        {

            TTree *tree_ep2bbjvbkg1 = new TTree("tree_ep2bbjvbkg1", "ep2bbjvbkg1");

            tree_ep2bbjvbkg1->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2bbjvbkg1->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2bbjvbkg1->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2bbjvbkg1->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2bbjvbkg1->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2bbjvbkg1->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2bbjvbkg1->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2bbjvbkg1->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2bbjvbkg1->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2bbjvbkg1->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2bbjvbkg1->Branch("MET",&MET,"MET/D");
            tree_ep2bbjvbkg1->Branch("HT",&HT,"HT/D");
            tree_ep2bbjvbkg1->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2bbjvbkg1->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2bbjvbkg1->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2bbjvbkg1->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2bbjvbkg1->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2bbjvbkg1->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2bbjvbkg1->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2bbjvbkg1->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2bbjvbkg1->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2bbjvbkg1->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2bbjvbkg1->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2bbjvbkg1->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2bbjvbkg1->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("ep2bbjvbkg1.root","READ");
        }

        if (r==7) 
        {

            TTree *tree_ep2ccjvbkg2 = new TTree("tree_ep2ccjvbkg2", "ep2ccjvbkg2");

            tree_ep2ccjvbkg2->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2ccjvbkg2->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2ccjvbkg2->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2ccjvbkg2->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2ccjvbkg2->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2ccjvbkg2->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2ccjvbkg2->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2ccjvbkg2->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2ccjvbkg2->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2ccjvbkg2->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2ccjvbkg2->Branch("MET",&MET,"MET/D");
            tree_ep2ccjvbkg2->Branch("HT",&HT,"HT/D");
            tree_ep2ccjvbkg2->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2ccjvbkg2->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2ccjvbkg2->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2ccjvbkg2->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2ccjvbkg2->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2ccjvbkg2->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2ccjvbkg2->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2ccjvbkg2->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2ccjvbkg2->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2ccjvbkg2->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2ccjvbkg2->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2ccjvbkg2->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2ccjvbkg2->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");
            f = new TFile("ep2ccjvbkg2.root","READ");
        }

        if (r==8) 
        {

            TTree *tree_ep2vjz2bbbkg3 = new TTree("tree_ep2vjz2bbbkg3", "ep2vjz2bbbkg3");

            tree_ep2vjz2bbbkg3->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2vjz2bbbkg3->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2vjz2bbbkg3->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2vjz2bbbkg3->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2vjz2bbbkg3->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2vjz2bbbkg3->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2vjz2bbbkg3->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2vjz2bbbkg3->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2vjz2bbbkg3->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2vjz2bbbkg3->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2vjz2bbbkg3->Branch("MET",&MET,"MET/D");
            tree_ep2vjz2bbbkg3->Branch("HT",&HT,"HT/D");
            tree_ep2vjz2bbbkg3->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2vjz2bbbkg3->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2vjz2bbbkg3->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2vjz2bbbkg3->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2vjz2bbbkg3->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2vjz2bbbkg3->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2vjz2bbbkg3->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2vjz2bbbkg3->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2vjz2bbbkg3->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2vjz2bbbkg3->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2vjz2bbbkg3->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2vjz2bbbkg3->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2vjz2bbbkg3->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("ep2vjz2bbbkg3.root","READ");
        }

        if (r==9) 
        {

            TTree *tree_ep2vjz2ccbkg4 = new TTree("tree_ep2vjz2ccbkg4", "ep2vjz2ccbkg4");

            tree_ep2vjz2ccbkg4->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2vjz2ccbkg4->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2vjz2ccbkg4->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2vjz2ccbkg4->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2vjz2ccbkg4->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2vjz2ccbkg4->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2vjz2ccbkg4->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2vjz2ccbkg4->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2vjz2ccbkg4->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2vjz2ccbkg4->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2vjz2ccbkg4->Branch("MET",&MET,"MET/D");
            tree_ep2vjz2ccbkg4->Branch("HT",&HT,"HT/D");
            tree_ep2vjz2ccbkg4->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2vjz2ccbkg4->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2vjz2ccbkg4->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2vjz2ccbkg4->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2vjz2ccbkg4->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2vjz2ccbkg4->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2vjz2ccbkg4->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2vjz2ccbkg4->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2vjz2ccbkg4->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2vjz2ccbkg4->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2vjz2ccbkg4->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2vjz2ccbkg4->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2vjz2ccbkg4->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("ep2vjz2ccbkg4.root","READ");
        }

        if (r==10) 
        {

            TTree *tree_ep2vjz2jjbkg5 = new TTree("tree_ep2vjz2jjbkg5", "ep2vjz2jjbkg5");

            tree_ep2vjz2jjbkg5->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2vjz2jjbkg5->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2vjz2jjbkg5->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2vjz2jjbkg5->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2vjz2jjbkg5->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2vjz2jjbkg5->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2vjz2jjbkg5->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2vjz2jjbkg5->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2vjz2jjbkg5->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2vjz2jjbkg5->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2vjz2jjbkg5->Branch("MET",&MET,"MET/D");
            tree_ep2vjz2jjbkg5->Branch("HT",&HT,"HT/D");
            tree_ep2vjz2jjbkg5->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2vjz2jjbkg5->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2vjz2jjbkg5->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2vjz2jjbkg5->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2vjz2jjbkg5->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2vjz2jjbkg5->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2vjz2jjbkg5->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2vjz2jjbkg5->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2vjz2jjbkg5->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2vjz2jjbkg5->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2vjz2jjbkg5->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2vjz2jjbkg5->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2vjz2jjbkg5->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("ep2vjz2jjbkg5.root","READ");
        }

        if (r==11) 
        {

            TTree *tree_ep2jt2w2jjbkg6 = new TTree("tree_ep2jt2w2jjbkg6", "ep2jt2w2jjbkg6");

            tree_ep2jt2w2jjbkg6->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2jt2w2jjbkg6->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2jt2w2jjbkg6->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2jt2w2jjbkg6->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2jt2w2jjbkg6->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2jt2w2jjbkg6->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2jt2w2jjbkg6->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2jt2w2jjbkg6->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2jt2w2jjbkg6->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2jt2w2jjbkg6->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2jt2w2jjbkg6->Branch("MET",&MET,"MET/D");
            tree_ep2jt2w2jjbkg6->Branch("HT",&HT,"HT/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2jt2w2jjbkg6->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2jt2w2jjbkg6->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("ep2jt2w2jjbkg6.root","READ");
        }

        if (r==12) 
        {

            TTree *tree_ep2vjhSMbkg7 = new TTree("tree_ep2vjhSMbkg7", "ep2vjhSMbkg7");

            tree_ep2vjhSMbkg7->Branch("jet_pt",&jet_pt,"jet_pt/D");
            tree_ep2vjhSMbkg7->Branch("bjet_pt",&bjet_pt,"bjet_pt/D");
            tree_ep2vjhSMbkg7->Branch("subbjet_pt",&subbjet_pt,"subbjet_pt/D");
            tree_ep2vjhSMbkg7->Branch("jet_eta",&jet_eta,"jet_eta/D");
            tree_ep2vjhSMbkg7->Branch("bjet_eta",&bjet_eta,"bjet_eta/D");
            tree_ep2vjhSMbkg7->Branch("subbjet_eta",&subbjet_eta,"subbjet_eta/D");
            tree_ep2vjhSMbkg7->Branch("jet_E",&jet_E,"jet_E/D");
            tree_ep2vjhSMbkg7->Branch("bjet_E",&bjet_E,"bjet_E/D");
            tree_ep2vjhSMbkg7->Branch("subbjet_E",&subbjet_E,"subbjet_E/D");
            tree_ep2vjhSMbkg7->Branch("bjetsInvariantMass",&bjetsInvariantMass,"bjetsInvariantMass/D");
            tree_ep2vjhSMbkg7->Branch("MET",&MET,"MET/D");
            tree_ep2vjhSMbkg7->Branch("HT",&HT,"HT/D");
            tree_ep2vjhSMbkg7->Branch("deltaeta_bjets",&deltaeta_bjets,"deltaeta_bjets/D");
            tree_ep2vjhSMbkg7->Branch("deltaeta_jetbjet",&deltaeta_jetbjet,"deltaeta_jetbjet/D");
            tree_ep2vjhSMbkg7->Branch("deltaeta_jetsubbjet",&deltaeta_jetsubbjet,"deltaeta_jetsubbjet/D");
            tree_ep2vjhSMbkg7->Branch("deltaphi_bjets",&deltaphi_bjets,"deltaphi_bjets/D");
            tree_ep2vjhSMbkg7->Branch("deltaphi_jetbjet",&deltaphi_jetbjet,"deltaphi_jetbjet/D");
            tree_ep2vjhSMbkg7->Branch("deltaphi_jetsubbjet",&deltaphi_jetsubbjet,"deltaphi_jetsubbjet/D");
            tree_ep2vjhSMbkg7->Branch("deltaR_bjets",&deltaR_bjets,"deltaR_bjets/D");
            tree_ep2vjhSMbkg7->Branch("deltaR_jetbjet",&deltaR_jetbjet,"deltaR_jetbjet/D");
            tree_ep2vjhSMbkg7->Branch("deltaR_jetsubbjet",&deltaR_jetsubbjet,"deltaR_jetsubbjet/D");
            tree_ep2vjhSMbkg7->Branch("cos_bjets",&cos_bjets,"cos_bjets/D");
            tree_ep2vjhSMbkg7->Branch("cos_jetbjet",&cos_jetbjet,"cos_jetbjet/D");
            tree_ep2vjhSMbkg7->Branch("cos_jetsubbjet",&cos_jetsubbjet,"cos_jetsubbjet/D");
            tree_ep2vjhSMbkg7->Branch("jetmultiplicity",&jetmultiplicity,"jetmultiplicity/I");

            f = new TFile("ep2vjhSMbkg7.root","READ");
        }


        TTree *tree_sample;
        f->GetObject("Delphes",tree_sample);   // Get objects from root file
        myclass     my(tree_sample);   // Define an object for Getting Entries
 /*
        TTree *tree_sample = (TTree*) f->Get( "Delphes" );
        myclass my(tree_sample);
  */ 

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


                if (r == 0) tree_xtar -> Fill();
                if (r == 1) tree_xbr -> Fill();    
                if (r == 2) tree_xtr -> Fill();    
                if (r == 3) tree_xtai -> Fill();    
                if (r == 4) tree_xbi -> Fill();    
                if (r == 5) tree_xti -> Fill();    
                if (r == 6) tree_ep2bbjvbkg1 -> Fill();    
                if (r == 7) tree_ep2ccjvbkg2 -> Fill();    
                if (r == 8) tree_ep2vjz2bbbkg3 -> Fill();    
                if (r == 9) tree_ep2vjz2ccbkg4 -> Fill();    
                if (r == 10) tree_ep2vjz2jjbkg5 -> Fill();    
                if (r == 11) tree_ep2jt2w2jjbkg6 -> Fill();    
                if (r == 12) tree_ep2vjhSMbkg7 -> Fill();    


                  //======================================= final cuts

                if (MET > 0.0 && HT > 0.0 && bjetsInvariantMass > 0.0)
                 {
                    N_accepted++;
                 } 

            } //======================================= event selection 
               
                jet.clear();
                bjet.clear();
                alljet.clear();
      
        } //======================================================= event loop

    f0->cd();

    if (r == 0) tree_xtar -> Write();
    if (r == 1) tree_xbr -> Write();    
    if (r == 2) tree_xtr -> Write();    
    if (r == 3) tree_xtai -> Write();    
    if (r == 4) tree_xbi -> Write();    
    if (r == 5) tree_xti -> Write();    
    if (r == 6) tree_ep2bbjvbkg1 -> Write();    
    if (r == 7) tree_ep2ccjvbkg2 -> Write();    
    if (r == 8) tree_ep2vjz2bbbkg3 -> Write();    
    if (r == 9) tree_ep2vjz2ccbkg4 -> Write();    
    if (r == 10) tree_ep2vjz2jjbkg5 -> Write();    
    if (r == 11) tree_ep2jt2w2jjbkg6 -> Write();    
    if (r == 12) tree_ep2vjhSMbkg7 -> Write();  

//============================================================ calculation of sigma and efficiency :
                 cout << "\n";
     if(r == 0)  cout << "For xtar60GeV:\n" << endl;
     if(r == 1)  cout << "For xbr60GeV:\n" << endl;
     if(r == 2)  cout << "For xtr60GeV:\n" << endl;
     if(r == 3)  cout << "For xtai60GeV:\n" << endl;
     if(r == 4)  cout << "For xbi60GeV:\n" << endl;
     if(r == 5)  cout << "For xti60GeV:\n" << endl;
     if(r == 6)  cout << "For ep2bbjvbkg1:\n" << endl;
     if(r == 7)  cout << "For ep2ccjvbkg2:\n" << endl;
     if(r == 8)  cout << "For ep2vjz2bbbkg3:\n" << endl;
     if(r == 9)  cout << "For ep2vjz2ccbkg4:\n" << endl;
     if(r == 10)  cout << "For ep2vjz2jjbkg5:\n" << endl;
     if(r == 11)  cout << "For ep2jt2w2jjbkg6:\n" << endl;
     if(r == 12)  cout << "For ep2vjhSMbkg7:\n" << endl;

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

f0->Close();

cout << endl;
cout << "=================================" << endl;
cout << "============= Finish ============" << endl;
cout << "=================================" << endl;

}//======================================================= analysis function



