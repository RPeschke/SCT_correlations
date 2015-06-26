#include <memory>
#include "treeCollection.h"
#include "sct_plots.h"
#include "internal/plot2d.hh"
#include "internal/plane.hh"
#include "sct_plots.h"
#include <iostream>

namespace sct_corr{

  plot2d::plot2d(const s_plot_prob& plot_prob) :plot(plot_prob)
  {

  }

  Long64_t plot2d::Draw(const char* options, const char* cuts /*= ""*/, const char* axis /*= "y:x"*/)
  {
    return Draw(S_DrawOption(options, cuts, axis));
  }

  Long64_t plot2d::Draw(const S_DrawOption& opt)
  {
    return opt.Draw(m_outTree->getTTree());
    
  }

  bool plot2d::fill()
  {
    m_outputEvent.reset();


    ProcessEvent();

    m_outTree->fill();
    ++m_current;
    return true;
  }

  void plot2d::pushHit(Double_t x, Double_t y)
  {
    
    pushHit(x, y, 0);
  }

  void plot2d::pushHit(Double_t x, Double_t y, Double_t ID)
  {
    m_outputEvent.push_Hit(x, y, ID);
  }

  bool plot2d::isReady()
  {
    if (m_x &&m_y)
    {
      m_outputEvent = rootEvent_X_Y_hits(getName());
      m_outTree = std::make_shared<treeCollection_ouput>( m_outputEvent, getSave2disk());
      return true;
    }

    return false;
  }

  void plot2d::pushAxis(const axis_ref* axis)
  {
    if (!m_x)
    {
      m_x = axis;
      return;
    }

    if (!m_y)
    {
      m_y = axis;
      return;
    }


    std::cout << "[plot2d::pushAxis(axis_ref* axis)] only two axis are supported\n";
  }

  void plot2d::pushPlane(S_plane* plane_)
  {
    if (!m_x&&!m_y)
    {
      m_x = plane_->getPlane()->getAxis(x_axis_def);
      m_y = plane_->getPlane()->getAxis(y_axis_def);
      return;
    }
    std::cout << "[plot2d::pushPlane(S_plane* plane)] only one plane is supported \n";
  }

  const char* plot2d::getOutputName() const
  {
    return m_outTree->m_name.c_str();
  }

}