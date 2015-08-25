#ifndef SCT_helpers_h__
#define SCT_helpers_h__
#include "internal/platform.hh"
#include "Rtypes.h"
#include "S_Axis.h"
#include "TF1.h"
class TH2D;
class TH2;
class TH1;
class TTree;
class S_Cut;
class S_DrawOption;

class DllExport SCT_helpers {
public:
  static void CutTH2(TH2* h2, const S_Cut& cut_);
  static void CutTH1(TH1* h1, const S_Cut& cut_);
  static TH1* HistogrammSilhouette(TH2* h2, axis_def ax);
  static Long64_t DrawTTree(TTree * tree, const S_DrawOption& opt);
  static TF1 LinearFit_Of_Profile(TH2* h2, Double_t cut_prozent = 0);
  static TH1* calc_efficiency(TH1* trueHits, TH1* dutHits);
};


#ifdef __CINT__
#pragma link C++ class SCT_helpers;
#endif // __CINT__


#endif // SCT_helpers_h__