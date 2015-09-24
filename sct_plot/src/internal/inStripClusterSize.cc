#include <iostream>
#include "internal/inStripClusterSize.hh"
#include "sct_processors.h"
#include "s_plane_def.h"
#include "s_cuts.h"
#include "s_DrawOption.h"
#include "TH2.h"
#include "TProfile.h"

sct_corr::inStripClusterSize::inStripClusterSize(
  const S_plane_def& trueHits_with_dut,
  const S_plane_def& sz_data,
  int max_cluster_size,
  axis_def search_axis,
  const sct_type::modulo_t & mod_,
  const s_plot_prob& plot_prob
  )
  :m_plot_prob(plot_prob),
  m_mod(mod_),
  m_search_axis(search_axis),
  m_max_cluster(max_cluster_size) {

  double mod_x = 10000000;
  double mod_y = 10000000;
  if (search_axis == x_axis_def) {
    mod_x = mod_.value;
  }

  if (search_axis == y_axis_def) {
    mod_y = mod_.value;
  }
  auto cluster_ = sct_processor::cluster_strip(
    sz_data,
    x_axis_def,
    2,
    s_plot_prob().doNotSaveToDisk()
    );
  auto cluster__cut = sct_processor::cut_x_y(
    cluster_,
    S_YCut(0, max_cluster_size),
    s_plot_prob().doNotSaveToDisk()
    );

  auto cluster_closest = sct_processor::find_nearest_strip(
    cluster__cut,
    trueHits_with_dut, //used to be all hits 
    search_axis,
    1000,
    s_plot_prob().doNotSaveToDisk()
    );
  auto mod_total_closest = sct_processor::moduloHitMap(
    cluster_closest.getHitOnPlaneB(),
    mod_x,
    mod_y,
    s_plot_prob().doNotSaveToDisk()
    );
  if (search_axis == x_axis_def) {
    auto cluster_size_vs_rel_pos = sct_processor::hitmap(
      mod_total_closest.getX_def(),
      cluster_closest.getHitOnPlaneA().getY_def(),
      plot_prob
      );

    m_cluster_size_vs_rel_pos = cluster_size_vs_rel_pos.copy();

  } else if (search_axis == y_axis_def) {

    auto cluster_size_vs_rel_pos = sct_processor::hitmap(
      mod_total_closest.getY_def(),
      cluster_closest.getHitOnPlaneA().getY_def(),
      plot_prob
      );

    m_cluster_size_vs_rel_pos = cluster_size_vs_rel_pos.copy();

  } else {
    std::cout << "[inStripClusterSize]: axis not supported \n";
  }

}

Long64_t sct_corr::inStripClusterSize::Draw(const S_DrawOption& d_option) {
  return m_cluster_size_vs_rel_pos->Draw(d_option);
}

TProfile* sct_corr::inStripClusterSize::getProfile() const {
  if (!m_profile) {
    return nullptr;
  }

  return m_profile.get();
}

TH2* sct_corr::inStripClusterSize::getHistogram() const {
  if (!m_cluster_size_plot) {
    return nullptr;
  }
  return m_cluster_size_plot.get();
}

Long64_t sct_corr::inStripClusterSize::Draw() {
  std::string name = std::string(m_plot_prob.getName()) + "_hist";
  m_cluster_size_plot = std::make_shared<TH2D>(
    name.c_str(),
    m_plot_prob.getName(),
    100, 0, m_mod.value,
    m_max_cluster * 100, -0.5, m_max_cluster - 0.5
    );
  Draw(S_DrawOption(m_plot_prob.getName()).draw_y_VS_x().opt_colz().output_object(m_cluster_size_plot.get()));

  m_profile = std::shared_ptr<TProfile>(dynamic_cast<TProfile*>(m_cluster_size_plot->ProfileX()));

  m_cluster_size_plot = std::make_shared<TH2D>(
    name.c_str(),
    m_plot_prob.getName(),
    100, 0, m_mod.value,
    m_max_cluster, -0.5, m_max_cluster - 0.5
    );
  auto ret = Draw(S_DrawOption(m_plot_prob.getName()).draw_y_VS_x().opt_colz().output_object(m_cluster_size_plot.get()));

  m_profile->Draw("same");
  
  return ret;
}
