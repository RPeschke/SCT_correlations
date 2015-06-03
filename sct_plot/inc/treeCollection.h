//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 20 16:34:27 2015 by ROOT version 5.34/18
// from TTree fitpoints/fitpoints
// found on file: C:/Users/Argg/OneDrive/alibava/fitter.root
//////////////////////////////////////////////////////////

#ifndef fitpoints_h
#define fitpoints_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include "Rtypes.h"
#include "sct_event_buffer.h"

class TArrayD;





class treeCollection {
public :

  root_event m_buffer;
   // Declaration of leaf types
   Int_t                event_nr;

   treeCollection(TTree *tree);
   treeCollection(const char *name);
   virtual ~treeCollection();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntries() const;

private:

   // List of branches
   TBranch        *b_ID;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_event_nr;   //!
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain


  
};



class treeCollection_ouput {
public:

  treeCollection_ouput(const char * name, TArrayD* x, TArrayD* y, TArrayD* ID, Int_t * event_nr, bool save2disk = true);
  treeCollection_ouput(const treeCollection_ouput& tree);
  virtual ~treeCollection_ouput();
  void fill();
  Int_t Draw(const char* axis, const char* cuts, const char * options);

  root_event m_buffer;

 
 
  TTree          *m_tree=nullptr;   //!pointer to the analyzed TTree or TChain
 


  std::string m_name;
};

#endif



