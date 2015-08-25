#include <exception>
#include <iostream>

#include "sct_plots_internal.h"
#include "internal/plane.hh"
#include "S_Axis.h"
#include "s_treeCollection.h"
#include "treeCollection.h"
#include "internal/plane_hit.hh"
#include "s_DrawOption.h"
#include "s_plane.h"
#include "s_plane_def.h"
#include "geometry/setup_description.hh"

  S_plane::S_plane() : m_plane(nullptr)
  {
    std::cout << "[s_plane] unsupported default constructor do not use" << std::endl;
  }


  S_plane::S_plane(const S_plane_def& plane_def, S_treeCollection* hits) : S_plane(plane_def, hits->m_tree.get())
  {


  }

  S_plane::S_plane(const S_plane_def& plane_def, sct_corr::treeCollection* hits) : m_plane_def(plane_def.copy())
  {

    m_plane = hits->m_rootBuffer.createPlane(m_plane_def->getID());


  }





  sct_corr::plane* S_plane::getPlane() const
  {
    return m_plane.get();
  }

  const char * S_plane::getName() const
  {
    return m_plane_def->getName();
  }
  Double_t S_plane::getID() const
  {
    return m_plane_def->getID();
  }

  bool S_plane::next()
  {

    return m_plane->next();
  }

 


 const sct_corr::axis_ref* S_plane::getX() const
  {
    if (!m_plane)
    {
      std::cout << "[s_plane] plane not set " << std::endl;
      return nullptr;
    }
    return m_plane->getAxis(x_axis_def);
  }

  const sct_corr::axis_ref* S_plane::getY() const
  {
    if (!m_plane)
    {
      std::cout << "[s_plane] plane not set " << std::endl;
      return nullptr;
    }
    return m_plane->getAxis(y_axis_def);
  }

  const sct_corr::Xlayer* S_plane_def::getLayer() const {
    if (m_layer)
    {
      return m_layer.get();
    }

    return nullptr;
  }
  std::shared_ptr<S_plot_collection> S_plane_def::get_plot() const {
    if (std::shared_ptr<S_plot_collection> ret = m_plot.lock()) {

      return ret;
    } else {
      std::cout << "plot is expired\n";
    }
    return nullptr;
  }

  std::shared_ptr<S_plane_def> S_plane_def::copy() const {
    return std::shared_ptr<S_plane_def>(new S_plane_def(*this));
  }
  void S_plane_def::set_s_plot_collection(std::weak_ptr<S_plot_collection> plot_collection) {
    m_plot = plot_collection;
    for (auto&e : m_axis) {
      e.set_plot_collection(plot_collection);

    }
  }
  Long64_t S_plane_def::Draw(const S_DrawOption& opt) const {
    return get_plot()->Draw(*this, opt);
  }

  S_plane_def::S_plane_def(const char* name, Double_t ID,const sct_corr::Xlayer* layer_) :m_name(name), m_ID(ID)
  {
    if (layer_)
    {
      m_layer = std::unique_ptr<sct_corr::Xlayer>(new sct_corr::Xlayer(*layer_));
    }
    m_axis.emplace_back(name, ID, x_axis_def);
    m_axis.emplace_back(name, ID, y_axis_def);
  }
  Double_t S_plane_def::getID() const
  {
    return m_ID;
  }

  const char* S_plane_def::getName() const
  {
    return m_name.c_str();
  }


  S_Axis S_plane_def::getX_def() const
  {
    return get_Axis(x_axis_def);
  }
  S_Axis S_plane_def::getY_def() const
  {
    return get_Axis(y_axis_def);
  }

  S_Axis S_plane_def::get_Axis(axis_def ax) const {
    for (const auto&e :m_axis)
    {
      if (e.m_axis == ax) {
        return e;
      }
    }
    throw std::exception("unknown type");
    return S_Axis();
  }

  const std::vector<S_Axis>& S_plane_def::get_axis_defs() const {
    return m_axis;
  }


  std::shared_ptr<S_plane_def> S_plane_def_GBL::copy() const {
    return std::shared_ptr<S_plane_def>(new S_plane_def_GBL(*this));
  }
  S_plane_def_GBL::S_plane_def_GBL(const char* name, Double_t ID, const sct_corr::Xlayer* layer_) :S_plane_def(name, ID, layer_) {
    m_axis.emplace_back(name, ID, chi2_axis_def);
    m_axis.emplace_back(name, ID, Ndf_axis_def);
    m_axis.emplace_back(name, ID, phi_axis_def);
    m_axis.emplace_back(name, ID, theta_axis_def);
  }

  S_Axis S_plane_def_GBL::getChi2_def() const {
    return get_Axis(chi2_axis_def);
  }

  S_Axis S_plane_def_GBL::getNdf_def() const {
    return get_Axis(Ndf_axis_def);
  }

  S_Axis S_plane_def_GBL::getPhi_def() const {
    return get_Axis(phi_axis_def);
  }

  S_Axis S_plane_def_GBL::getTheta_def() const {
    return get_Axis(theta_axis_def);
  }



  s_plane_collection_correlations::s_plane_collection_correlations() :s_plane_collection() {

  }

  void s_plane_collection_correlations::setResidual(const S_plane_def& plane_) {
    push_back("Residual", plane_);
  }

  void s_plane_collection_correlations::setResidualVsMissing(const S_plane_def& plane_) {
    push_back("ResidualVsMissing", plane_);
  }

  void s_plane_collection_correlations::setTotalTrueHits(const S_plane_def& plane_) {
    push_back("TotalTrueHits", plane_);
  }

  void s_plane_collection_correlations::setTrueHitsWithDUT(const S_plane_def& plane_) {
    push_back("TrueHitsWithDUT", plane_);
  }

  void s_plane_collection_correlations::setDUT_Hits(const S_plane_def& plane_) {
    push_back("DUT_Hits", plane_);
  }

  S_plane_def s_plane_collection_correlations::getResidual() const {
    return getByType("Residual")();
  }

  S_plane_def s_plane_collection_correlations::getResidualVSmissing() const {
    return getByType("ResidualVsMissing")();
  }

  S_plane_def s_plane_collection_correlations::getTotalTrueHits() const {
    return getByType("TotalTrueHits")();
  }

  S_plane_def s_plane_collection_correlations::getTrueHitsWithDUT() const {
    return getByType("TrueHitsWithDUT")();
  }

  S_plane_def s_plane_collection_correlations::getDUT_Hits() const {
    return getByType("DUT_Hits")();
  }

  s_plane_collection_find_closest::s_plane_collection_find_closest() :s_plane_collection() {

  }

  void s_plane_collection_find_closest::setResidual(const S_plane_def& plane_) {
    push_back("Residual", plane_);
  }

  void s_plane_collection_find_closest::setHitOnPlaneA(const S_plane_def& plane_) {
    push_back("HitOnPlaneA", plane_);
  }

  void s_plane_collection_find_closest::setHitOnPlaneB(const S_plane_def& plane_) {
    push_back("HitOnPlaneB", plane_);
  }

  S_plane_def s_plane_collection_find_closest::getResidual() const {
    return getByType("Residual")();
  }

  S_plane_def s_plane_collection_find_closest::getHitOnPlaneA() const {
    return getByType("HitOnPlaneA")();
  }

  S_plane_def s_plane_collection_find_closest::getHitOnPlaneB() const {
    return getByType("HitOnPlaneB")();
  }

  void s_plane_collection::clear() {
    m_planes.clear();
  }
