/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides a simple example on how to use the trained classifiers
/// within an analysis module
/// - Project   : TMVA - a Root-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Exectuable: TMVAClassificationApplication
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"



using namespace TMVA;

void TMVAClassificationApplication60GeV( TString myMethodList = "" )
{

 double AS_cut[8][2]={0}; // number of events: AS_cut[n_samples][0=before cut, 1=after cut]
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
   //============================================================= we have to swich on just 1 method in this application code:
   // Cut optimisation
   Use["Cuts"]            = 0;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   //
   // 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 0;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodMIX"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // k-nearest neighbour method
   //
   // Linear Discriminant Analysis
   Use["LD"]              = 0; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // Function Discriminant analysis
   Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   Use["DNN"]             = 0; // improved implementation of a NN (Deep Neural Network)
   //
   // Support Vector Machine
   Use["SVM"]             = 0;
   //
   // Boosted Decision Trees
   Use["BDT"]             = 0; // uses Adaptive Boost
   Use["BDTG"]            = 1; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------
   Use["Plugin"]          = 0;
   Use["Category"]        = 0;
   Use["SVM_Gauss"]       = 0;
   Use["SVM_Poly"]        = 0;
   Use["SVM_Lin"]         = 0;


   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication60GeV" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used

// ======================================================================================================

   Float_t jet_pt, jet_eta, bjetsInvariantMass, MET, deltaeta_bjets, deltaeta_jetbjet, deltaR_bjets, deltaR_jetbjet, deltaR_jetsubbjet, cos_bjets, jetmultiplicity;


// ======================================================================================================

   reader->AddVariable( "jet_pt", &jet_pt );
   reader->AddVariable( "jet_eta", &jet_eta );
   reader->AddVariable( "bjetsInvariantMass", &bjetsInvariantMass );
   reader->AddVariable( "MET", &MET );
   reader->AddVariable( "deltaeta_bjets", &deltaeta_bjets );
   reader->AddVariable( "deltaeta_jetbjet", &deltaeta_jetbjet );
   reader->AddVariable( "deltaR_bjets", &deltaR_bjets );
   reader->AddVariable( "deltaR_jetbjet", &deltaR_jetbjet );
   reader->AddVariable( "deltaR_jetsubbjet", &deltaR_jetsubbjet );
   reader->AddVariable( "cos_bjets", &cos_bjets );
   reader->AddVariable( "jetmultiplicity", &jetmultiplicity );

// ======================================================================================================

   // Book the MVA methods

   TString dir    = "dataset_xbr/weights/";
   TString prefix = "TMVAClassification";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }
   
     // Book output histograms

   UInt_t nbin = 100;
/*
   TH1F * histBdt_ctll;
   TH1F * histBdt_ctrr;
   TH1F * histBdt_ctrl;
   TH1F * histBdt_ctlr;
   TH1F * histBdt_bkg_etavv;
   TH1F * histBdt_bkg_llqq;
   TH1F * histBdt_bkg_tata;
   TH1F * histBdt_bkg_llll;
*/

   TH1F * histBdtG[8];

 // *histBdtG[3], *histBdtD[3];
   //TFile * input[3];
   //TString fname[3];
  
/*
   if (Use["BDT"])     histBdt_ctll      = new TH1F( "signal", "signal", nbin, -1.0, 1.0 );

  if (Use["BDT"])     histBdt_bkg_etavv      = new TH1F( "etavv",  "etavv", nbin, -1.0, 1.0 );
   if (Use["BDT"])     histBdt_bkg_llqq      = new TH1F( "llqq",  "llqq", nbin, -1.0, 1.0 );
   if (Use["BDT"])     histBdt_bkg_tata      = new TH1F( "tata",  "tata", nbin, -1.0, 1.0 );
   if (Use["BDT"])     histBdt_bkg_llll      = new TH1F( "llll",  "llll", nbin, -1.0, 1.0 );
*/

   if (Use["BDTG"])
    {
     histBdtG[0]      = new TH1F( "xbr", "xbr", nbin, -1.0, 1.0 );
     histBdtG[1]      = new TH1F( "ep2bbjvbkg1",  "ep2bbjvbkg1", nbin, -1.0, 1.0 );
     histBdtG[2]      = new TH1F( "ep2ccjvbkg2",  "ep2ccjvbkg2", nbin, -1.0, 1.0 );
     histBdtG[3]      = new TH1F( "ep2vjz2bbbkg3",  "ep2vjz2bbbkg3", nbin, -1.0, 1.0 );
     histBdtG[4]      = new TH1F( "ep2vjz2ccbkg4",  "ep2vjz2ccbkg4", nbin, -1.0, 1.0 );
     histBdtG[5]      = new TH1F( "ep2vjz2jjbkg5",  "ep2vjz2jjbkg5", nbin, -1.0, 1.0 );
     histBdtG[6]      = new TH1F( "ep2jt2w2jjbkg6",  "ep2jt2w2jjbkg6", nbin, -1.0, 1.0 );
     histBdtG[7]      = new TH1F( "ep2vjhSMbkg7",  "ep2vjhSMbkg7", nbin, -1.0, 1.0 );

    }

/*
****** we have to define these for each sample. We can use array like: histLk[samples]

   if (Use["Likelihood"])    histLk      = new TH1F( "MVA_Likelihood",    "MVA_Likelihood",    nbin, -1, 1 );
   if (Use["LikelihoodD"])   histLkD     = new TH1F( "MVA_LikelihoodD",   "MVA_LikelihoodD",   nbin, -1, 0.9999 );
   if (Use["LikelihoodMIX"]) histLkPCA   = new TH1F( "MVA_LikelihoodMIX", "MVA_LikelihoodMIX", nbin, -1, 1 );
   if (Use["LikelihoodKDE"]) histLkKDE   = new TH1F( "MVA_LikelihoodKDE", "MVA_LikelihoodKDE", nbin,  -0.00001, 0.99999 );
   if (Use["LikelihoodMIX"]) histLkMIX   = new TH1F( "MVA_LikelihoodMIX", "MVA_LikelihoodMIX", nbin,  0, 1 );
   if (Use["PDERS"])         histPD      = new TH1F( "MVA_PDERS",         "MVA_PDERS",         nbin,  0, 1 );
   if (Use["PDERSD"])        histPDD     = new TH1F( "MVA_PDERSD",        "MVA_PDERSD",        nbin,  0, 1 );
   if (Use["PDERSPCA"])      histPDPCA   = new TH1F( "MVA_PDERSPCA",      "MVA_PDERSPCA",      nbin,  0, 1 );
   if (Use["KNN"])           histKNN     = new TH1F( "MVA_KNN",           "MVA_KNN",           nbin,  0, 1 );
   if (Use["HMatrix"])       histHm      = new TH1F( "MVA_HMatrix",       "MVA_HMatrix",       nbin, -0.95, 1.55 );
   if (Use["Fisher"])        histFi      = new TH1F( "MVA_Fisher",        "MVA_Fisher",        nbin, -4, 4 );
   if (Use["FisherG"])       histFiG     = new TH1F( "MVA_FisherG",       "MVA_FisherG",       nbin, -1, 1 );
   if (Use["BoostedFisher"]) histFiB     = new TH1F( "MVA_BoostedFisher", "MVA_BoostedFisher", nbin, -2, 2 );
   if (Use["LD"])            histLD      = new TH1F( "MVA_LD",            "MVA_LD",            nbin, -2, 2 );
   if (Use["MLP"])           histNn      = new TH1F( "MVA_MLP",           "MVA_MLP",           nbin, -1.25, 1.5 );
   if (Use["MLPBFGS"])       histNnbfgs  = new TH1F( "MVA_MLPBFGS",       "MVA_MLPBFGS",       nbin, -1.25, 1.5 );
   if (Use["MLPBNN"])        histNnbnn   = new TH1F( "MVA_MLPBNN",        "MVA_MLPBNN",        nbin, -1.25, 1.5 );
   if (Use["CFMlpANN"])      histNnC     = new TH1F( "MVA_CFMlpANN",      "MVA_CFMlpANN",      nbin,  0, 1 );
   if (Use["TMlpANN"])       histNnT     = new TH1F( "MVA_TMlpANN",       "MVA_TMlpANN",       nbin, -1.3, 1.3 );
   if (Use["DNN"])           histNdn     = new TH1F( "MVA_DNN",           "MVA_DNN",           nbin, -0.1, 1.1 );
   if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -1.0, 1.0 );
   if (Use["BDTG"])          histBdtG    = new TH1F( "MVA_BDTG",          "MVA_BDTG",          nbin, -1.0, 1.0 );
   if (Use["BDTB"])          histBdtB    = new TH1F( "MVA_BDTB",          "MVA_BDTB",          nbin, -1.0, 1.0 );
   if (Use["BDTD"])          histBdtD    = new TH1F( "MVA_BDTD",          "MVA_BDTD",          nbin, -1.0, 1.0 );
   if (Use["BDTF"])          histBdtF    = new TH1F( "MVA_BDTF",          "MVA_BDTF",          nbin, -1.0, 1.0 );
   if (Use["RuleFit"])       histRf      = new TH1F( "MVA_RuleFit",       "MVA_RuleFit",       nbin, -2.0, 2.0 );
   if (Use["SVM_Gauss"])     histSVMG    = new TH1F( "MVA_SVM_Gauss",     "MVA_SVM_Gauss",     nbin,  0.0, 1.0 );
   if (Use["SVM_Poly"])      histSVMP    = new TH1F( "MVA_SVM_Poly",      "MVA_SVM_Poly",      nbin,  0.0, 1.0 );
   if (Use["SVM_Lin"])       histSVML    = new TH1F( "MVA_SVM_Lin",       "MVA_SVM_Lin",       nbin,  0.0, 1.0 );
   if (Use["FDA_MT"])        histFDAMT   = new TH1F( "MVA_FDA_MT",        "MVA_FDA_MT",        nbin, -2.0, 3.0 );
   if (Use["FDA_GA"])        histFDAGA   = new TH1F( "MVA_FDA_GA",        "MVA_FDA_GA",        nbin, -2.0, 3.0 );
   if (Use["Category"])      histCat     = new TH1F( "MVA_Category",      "MVA_Category",      nbin, -2., 2. );
   if (Use["Plugin"])        histPBdt    = new TH1F( "MVA_PBDT",          "MVA_BDT",           nbin, -1.0, 1.0 );
*/

   //for ( int ifile = 1; ifile < 3; ifile++ ) { //ifile = sample numbers

   //if (Use["BDT"])     histBdt[ifile]      = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -1.0, 1.0 );
   //if (Use["BDTD"])    histBdtD[ifile]     = new TH1F( "TMVA_BDTD",         "TMVA_BDTD",         nbin, -0.6, 0.6 );
   //if (Use["BDTG"])    histBdtG[ifile]     = new TH1F( "TMVA_BDTG",         "TMVA_BDTG",         nbin, -1.0, 1.0 );


   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //

//======================================================================================================
   TFile *input(0);

      input = TFile::Open( "TMVA_input60Gev.root" ); // check if file in local directory exists

   std::cout << "--- TMVAClassificationApp    : Using input file: " << std::endl;

   // Event loop

   // Prepare the event tree
   // - Here the variable names have to corresponds to your tree
   // - You can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop

   std::cout << "--- Select signal sample" << std::endl;
   TTree *theTree[8];

   theTree[0] = (TTree*)input->Get("tree_xbr");
   theTree[1] =  (TTree*)input->Get("tree_ep2bbjvbkg1");
   theTree[2] =  (TTree*)input->Get("tree_ep2ccjvbkg2");
   theTree[3] =  (TTree*)input->Get("tree_ep2vjz2bbbkg3");
   theTree[4] =  (TTree*)input->Get("tree_ep2vjz2ccbkg4");
   theTree[5] =  (TTree*)input->Get("tree_ep2vjz2jjbkg5");
   theTree[6] =  (TTree*)input->Get("tree_ep2jt2w2jjbkg6");
   theTree[7] =  (TTree*)input->Get("tree_ep2vjhSMbkg7");


   Double_t weight[8];

   weight[0] = 1.0/585872; // = lum(ab^-1)/N_tot (for signals) ------------------------------------xbr
   weight[1] = 0.049093/1090329; // = sigma(pb)*lum(pb^-1)/N_tot (for backgrounds)----------------Weight_ep2bbjvbkg1
   weight[2] = 0.0619089/1045855;//----------------------------------------------------------Weight_ep2ccjvbkg2
   weight[3] = 0.07302/1564635;//----------------------------------------------------------Weight_ep2vjz2bbbkg3
   weight[4] = 0.04487/1037779;//--------------------------------------------------------Weight_ep2vjz2ccbkg4
   weight[5] = 0.160665/1173316;//--------------------------------------------------------Weight_ep2vjz2jjbkg5
   weight[6] = 0.03652/1118809;//--------------------------------------------------------Weight_ep2jt2w2jjbkg6
   weight[7] = 0.09841/1365598;//--------------------------------------------------------Weight_ep2vjhSMbkg7


   Double_t user_jet_pt, user_jet_eta, user_bjetsInvariantMass, user_MET, user_deltaeta_bjets, user_deltaeta_jetbjet, user_deltaR_bjets, user_deltaR_jetbjet, user_deltaR_jetsubbjet, user_cos_bjets;//due to "double v.s. float" Error , user_variable;
   Int_t user_jetmultiplicity;

//    Double_t   sigma_MG [] = {signal, ep2bbjvbkg1, ep2ccjvbkg2, ep2vjz2bbbkg3, ep2vjz2ccbkg4, ep2vjz2jjbkg5, ep2jt2w2jjbkg6, ep2vjh2bbSMbkg7}; 
const Double_t sigma_MG [8] = {1.0 , 0.058472, 0.221218, 0.1434801, 0.187287, 1.0059121, 2.6384222, 0.13925}; //pb,
const Double_t eff_pre [8] = {0.0744145 , 0.0928427, 0.000236327, 0.0952169, 0.000469105, 0.000124088, 0.0423568, 0.0664047}; //eff of preselection cuts, x_br=0.0744145 , x_bi=0.074687

// ======================================================================================================== 
   for (int ii=0;ii<8;ii++){ // sample loop

    theTree[ii]->SetBranchAddress( "jet_pt", &user_jet_pt );
    theTree[ii]->SetBranchAddress( "jet_eta", &user_jet_eta );
    theTree[ii]->SetBranchAddress( "bjetsInvariantMass", &user_bjetsInvariantMass );
    theTree[ii]->SetBranchAddress( "MET", &user_MET );
    theTree[ii]->SetBranchAddress( "deltaeta_bjets", &user_deltaeta_bjets );
    theTree[ii]->SetBranchAddress( "deltaeta_jetbjet", &user_deltaeta_jetbjet );
    theTree[ii]->SetBranchAddress( "deltaR_bjets", &user_deltaR_bjets );
    theTree[ii]->SetBranchAddress( "deltaR_jetbjet", &user_deltaR_jetbjet );
    theTree[ii]->SetBranchAddress( "deltaR_jetsubbjet", &user_deltaR_jetsubbjet );
    theTree[ii]->SetBranchAddress( "cos_bjets", &user_cos_bjets );
    theTree[ii]->SetBranchAddress( "jetmultiplicity", &user_jetmultiplicity );

//============================================================================================================
    TStopwatch sw;
    sw.Start();

//----------------------------------------------------------------------------------------

    
         //for (int ievt0=0; ievt0<10000;ievt0++) {  // Event loop
    for (int ievt0=0; ievt0<theTree[ii]-> GetEntries();ievt0++) {  // Event loop

       //if (ievt0%10000 == 0) std::cout << "--- ... Processing event: " << ievt0 << std::endl;

          AS_cut[ii][0]++;
          theTree[ii]->GetEntry(ievt0);  
      
          jet_pt= float(user_jet_pt);
          jet_eta= float(user_jet_eta);
          bjetsInvariantMass= float(user_bjetsInvariantMass);//due to double v.s. float Err
          MET= float(user_MET);
          deltaeta_bjets= float(user_deltaeta_bjets);
          deltaeta_jetbjet= float(user_deltaeta_jetbjet);
          deltaR_bjets= float(user_deltaR_bjets);
          deltaR_jetbjet= float(user_deltaR_jetbjet);
          deltaR_jetsubbjet= float(user_deltaR_jetsubbjet);
          cos_bjets= float(user_cos_bjets);
          jetmultiplicity= float(user_jetmultiplicity);


          // Return the MVA outputs and fill into histograms
//-------------------------------------------------------------------
/*      if(Use["BDT"])   histBdt[ii]->Fill( reader->EvaluateMVA("BDT method"), weight[ii] );
 
      if(Use["BDT"]) {

        //cout << (reader -> EvaluateMVA("BDT method")) << endl;
        if ( (reader -> EvaluateMVA("BDT method")) > 0.20 )   AS_cut[ii][1]++; // optimal cut from classification = -0.0828
      }

//-------------------------------------------------------------------
      if(Use["BDTF"]) {
        if ( (reader -> EvaluateMVA("BDTF method")) >     -0.3912   )    AS_cut[ii][1]++;
      }
*/
//-------------------------------------------------------------------
      if(Use["BDTG"])   histBdtG[ii]->Fill( reader->EvaluateMVA("BDTG method"), weight[ii] );

      if(Use["BDTG"]) {
        if ( (reader -> EvaluateMVA("BDTG method")) >     -0.33   )    AS_cut[ii][1]++; // -0.33 for x_br and -0.32 for x_bi
      }

//-------------------------------------------------------------------
/*
      if(Use["MLP"]) {
        if ( (reader -> EvaluateMVA("MLP method")) >     0.16  )    AS_cut[ii][1]++; // 0.16 for both x_br, x_bi
      }
//-------------------------------------------------------------------
      if(Use["MLPBFGS"]) {
        if ( (reader -> EvaluateMVA("MLPBFGS method")) >     0.45   )     AS_cut[ii][1]++;
      }
//-------------------------------------------------------------------
      if(Use["MLPBNN"]) {
        if ( (reader -> EvaluateMVA("MLPBNN method")) >     0.5   )     AS_cut[ii][1]++;
      }
//-------------------------------------------------------------------
      if(Use["DNN"]) {
        if ( (reader -> EvaluateMVA("DNN method")) >     0.65   )    AS_cut[ii][1]++;
      }
//-------------------------------------------------------------------
      if(Use["PDERS"]) {
        if ( (reader -> EvaluateMVA("PDERS method")) >     0.6  )    AS_cut[ii][1]++;
      }
//-------------------------------------------------------------------
      if(Use["SVM"]) {
        if ( (reader -> EvaluateMVA("SVM method")) >     0.3339   )    AS_cut[ii][1]++;
      }
//-------------------------------------------------------------------
      if(Use["LikelihoodMIX"]) {
        if ( (reader -> EvaluateMVA("LikelihoodMIX method")) >     0.6   )    AS_cut[ii][1]++;
      }
//-------------------------------------------------------------------
*/

    } //event loop


// ----------------- Get elapsed time
      sw.Stop();

//===================================================================================================================

std::cout << "================================================================" << std::endl;   

// ----------------- cout efficiencies :

     if(ii==0)  
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "---- xbr efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- xbr efficiency tot >>>>>>  = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==1)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "----  MG cross-section [pb]   = " <<  sigma_MG[ii] << std::endl;
        std::cout << "---- ep2bbjvbkg1 efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2bbjvbkg1 efficiency tot >>>>>>    = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2bbjvbkg1 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==2)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "----  MG cross-section [pb]   = " <<  sigma_MG[ii] << std::endl;
        std::cout << "---- ep2ccjvbkg2 efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2ccjvbkg2 efficiency tot >>>>>>    = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2ccjvbkg2 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==3)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "----  MG cross-section [pb]   = " <<  sigma_MG[ii] << std::endl;
        std::cout << "---- ep2vjz2bbbkg3 efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjz2bbbkg3 efficiency tot >>>>>>    = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjz2bbbkg3 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==4)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "----  MG cross-section [pb]   = " <<  sigma_MG[ii] << std::endl;
        std::cout << "---- ep2vjz2ccbkg4 efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjz2ccbkg4 efficiency tot >>>>>>    = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjz2ccbkg4 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==5)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "---- ep2vjz2jjbkg5 efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjz2jjbkg5 efficiency tot >>>>>>    = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjz2jjbkg5 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==6)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "---- ep2jt2w2jjbkg6 efficiency app    = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2jt2w2jjbkg6 efficiency tot >>>>>>    = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2jt2w2jjbkg6 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }
     if(ii==7)
        {
        std::cout << "----  total                   = " <<  AS_cut[ii][0] << std::endl;
        std::cout << "----  After_CUT               = " <<  AS_cut[ii][1] << std::endl;
        std::cout << "---- ep2vjhSMbkg7 efficiency app     = " <<  AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjhSMbkg7 efficiency tot >>>>>>     = " <<  eff_pre[ii]*AS_cut[ii][1]*1./ AS_cut[ii][0] << std::endl;
        std::cout << "---- ep2vjhSMbkg7 final cross-section [pb]     = " <<  eff_pre[ii]*AS_cut[ii][1]*sigma_MG[ii]/ AS_cut[ii][0] << std::endl;
std::cout << "================================================================" << std::endl;   
         }

   }  // sample loop
   
std::cout << "*****************************************************************" << std::endl;   


  std::cout << "---- Final (all) bkg xsec after TMVA Application [pb] = " << ((AS_cut[1][1]*eff_pre[1]*sigma_MG[1]/ AS_cut[1][0])+ // [0] is for signal, bkgs start from [1]
                                                                         (AS_cut[2][1]*eff_pre[2]*sigma_MG[2]/ AS_cut[2][0])+
                                                                         (AS_cut[3][1]*eff_pre[3]*sigma_MG[3]/ AS_cut[3][0])+
                                                                         (AS_cut[4][1]*eff_pre[4]*sigma_MG[4]/ AS_cut[4][0])+
                                                                         (AS_cut[5][1]*eff_pre[5]*sigma_MG[5]/ AS_cut[5][0])+
                                                                         (AS_cut[6][1]*eff_pre[6]*sigma_MG[6]/ AS_cut[6][0])+
                                                                         (AS_cut[7][1]*eff_pre[7]*sigma_MG[7]/ AS_cut[7][0]))
 << endl << std::endl;
std::cout << "*****************************************************************" << std::endl;   


//=============================================================================================================================

   // Write histograms

   TFile *target  = new TFile( "APPTMVA_xbr_60GeV.root","RECREATE" );

   if (Use["BDTG"])
    {    
       histBdtG[0]->Write();
       histBdtG[1]->Write();
       histBdtG[2]->Write();
       histBdtG[3]->Write();
       histBdtG[4]->Write();
       histBdtG[5]->Write();
       histBdtG[6]->Write();
       histBdtG[7]->Write();
    }

   target->Close();

   std::cout << "--- Created root file: \"APPTMVA_xbr_60GeV.root\" containing the MVA output histograms" << std::endl;

   delete reader;

   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
}

int main( int argc, char** argv )
{
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   TMVAClassificationApplication60GeV(methodList);
   return 0;
}
