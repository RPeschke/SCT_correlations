#ifndef s_plot_collection_h__
#define s_plot_collection_h__
#include "internal/platform.hh"
#include "Rtypes.h"
#include <memory>
#include <map>
#include "s_plot.h"
#include "s_DrawOption.h"

class TFile;
class TTree;
class s_plane_collection;
class S_plot;
class S_DrawOption;
class S_plane_def;
class S_Axis;
class S_plane;
namespace sct_corr {
class axis_ref;
class treeCollection;
class sct_event_buffer;
}

template <typename plane_tA, typename plane_tB>
std::shared_ptr <sct_corr::plot_collection> getPlotCollectionIfUnique(plane_tA& first_, plane_tB& secound__) {
  auto plA = first_.get_plot();
  auto plB = secound__.get_plot();
  if (plA.get() != plB.get()) {

    return nullptr;
  }
  return plA;
}


template <typename plane_tA, typename plane_tB, typename... planes_t>
std::shared_ptr <sct_corr::plot_collection> getPlotCollectionIfUnique(plane_tA& first_, plane_tB& secound__, planes_t&... rest_) {
  auto plA = first_.get_plot();
  auto plB = secound__.get_plot();
  if (plA.get() != plB.get()) {

    return nullptr;
  }
  return getPlotCollectionIfUnique(secound__, rest_...);

}



namespace sct_corr {


std::shared_ptr<plot_collection> create_plot_collection();
class  DllExport plot_collection {
public:
  plot_collection();
  virtual  ~plot_collection();
  
  
  virtual void addFile(TFile* file)=0;
  virtual void setOutputFile(TFile* file)=0;
  virtual void reset()=0;
  virtual s_plane_collection addPlot(S_plot plot_def, const S_Axis& x_axis, const S_Axis& y_axis)=0;

  virtual s_plane_collection addPlot(S_plot plot_def, const S_plane_def& p1, const S_plane_def & p2)=0;
  virtual s_plane_collection addPlot(S_plot plot_def, const  S_plane_def& p1)=0;
  virtual s_plane_collection addPlot(S_plot plot_def, const  s_plane_collection& p1)=0;

  virtual void loop(Int_t last = -1, Int_t start = 0)=0;


  virtual Long64_t Draw(const char* name, const S_DrawOption& option)=0;
  virtual Long64_t Draw(const S_plane_def& name, const S_DrawOption& option)=0;
  virtual bool collectionExist(const char* name)  const =0 ;
};



}


#endif // s_plot_collection_h__
