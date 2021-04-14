#include "PBClass.h"
//#include "nominal.cpp"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "math.h"
#include <iostream>  
#include "TApplication.h"
using namespace std;

int main (int argc, char *argv[]) { 
    //TString MyInput("/home/petr/GitLab/unfolding/production/DelphesRootFiles/pp2ttbarj_ljets_both_LO.root"), MyTree("Delphes"), MyOutput("out_data_nominal.root"), MyPathToTree("");
    TString MyInput("/home/petr/production-ttbar/DelphesRootFiles/pp2ttbarj_ljets_both_LO_matrix.root"), MyTree("Delphes"), MyOutput("out_data_nominal_matrix.root"), MyPathToTree("");
    
    TApplication theApp("App",&argc, argv);
    if (argc > 1){
        MyInput = argv[1];
        MyOutput = argv[2];
        MyTree = argv[3];
        //MyPathToTree = argv[4];
    }
    
    PBClass * t = new PBClass(0, MyInput, MyTree, "");
    t->Loop(MyOutput, MyTree);
    theApp.Run();
    return 0;
    
 } 