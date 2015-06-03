#include "treeCollection.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

#include "sct_global.h"






treeCollection::treeCollection(const char *name)
{
  fChain = NULL;
  if (!getGlobalPlotCollection()->get(name, &m_buffer))
  {
    std::cout << "collection not found. name: \"" << name << "\"" << std::endl;
  }

  event_nr = *m_buffer.m_event_nr;
}





treeCollection::treeCollection(TTree *tree) : fChain(0)
{

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("ID", &m_buffer.m_ID, &b_ID);
  fChain->SetBranchAddress("x", &m_buffer.m_x, &b_x);
  fChain->SetBranchAddress("y", &m_buffer.m_y, &b_y);
  fChain->SetBranchAddress("event_nr", &event_nr, &b_event_nr);
  m_buffer.m_event_nr=&event_nr;
  getGlobalPlotCollection()->set(tree->GetName(), &m_buffer);
}
treeCollection::~treeCollection()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t treeCollection::GetEntry(Long64_t entry)
{
  if (fChain== NULL)
  {
    event_nr = *m_buffer.m_event_nr;
    return 0;
  }
  return fChain->GetEntry(entry);
}

Int_t treeCollection::GetEntries() const 
{
  if (fChain == NULL)
  {
    return kMaxInt;
  }
  return fChain->GetEntries();
}














treeCollection_ouput::treeCollection_ouput(const char * name, TArrayD* x, TArrayD* y, TArrayD* ID, Int_t * event_nr, bool save2disk/*=true*/) :m_buffer(ID, x, y, event_nr), m_name(name)
{
 
  getGlobalPlotCollection()->set(name ,&m_buffer);
  if (save2disk)
  {
    m_tree = new TTree(name, name);
    m_tree->Branch("ID", ID);
    m_tree->Branch("x", x);
    m_tree->Branch("y", y);
    m_tree->Branch("event_nr", event_nr);
  }
  
  

}

treeCollection_ouput::~treeCollection_ouput()
{
 
}

void treeCollection_ouput::fill()
{
  if (m_tree)
  {
    m_tree->Fill();
  }
}

Int_t treeCollection_ouput::Draw(const char* axis, const char* cuts, const char * options)
{
  if (!m_tree)
  {
    std::cout << "collection not stored: \"" << m_name << "\"" << std::endl;
    return -1; // nothing to do 
  }
  return m_tree->Draw(axis, cuts, options);
}

treeCollection_ouput::treeCollection_ouput(const treeCollection_ouput& tree) :m_tree(tree.m_tree), m_buffer(tree.m_buffer), m_name(tree.m_name)
{

}
