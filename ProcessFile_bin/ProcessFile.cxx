
#include "../sct_plot/inc/s_process_files.h"
#include "../sct_plot/inc/sct_runs.h"
#include "TError.h"

#include "TApplication.h"
#include "TBrowser.h"
#include "../sct_plot/inc/s_cuts.h"
#include "TF1.h"
#include "TProfile.h"
#include "../sct_plot/inc/s_plot_collection.h"
#include "TCanvas.h"


int main(int argc, char **argv) {

  TApplication theApp("App", &argc, argv);
  s_process_files p;

 
  gErrorIgnoreLevel = kError;  // ignoring root printouts (replace of histograms) 
  if (false)
  {

    TFile * __file = new TFile("D:/data/DEVICE_2_ASIC_on_Position_7_150V/run001122-fitter.root");
    TFile * __file1 = new TFile("dummy.root", "recreate");

    S_plot_collection  plot_c(__file);

    s_plane_collection corr1 = plot_c.addPlot(sct_plot::correlation(""), sct_coll::tel_hit(3).getY_def(), sct_coll::DUT_hit().getY_def());
    s_plane_collection corr2 = plot_c.addPlot(sct_plot::correlation(""), sct_coll::tel_hit(3).getX_def(), sct_coll::DUT_hit().getX_def());
    auto trueHits = sct_plot::Crate_True_Fitted_DUT_Hits(plot_c);


    auto closest = plot_c.addPlot(sct_plot::find_nearest_strip(y_axis_def, 1000), sct_coll::DUT_hit(), trueHits);

    s_plane_collection resVSmissing = plot_c.addPlot(sct_plot::hitmap(), closest.get("nearest_strip_distance")().getY_def(), closest.get("nearest_strip_plane2")().getX_def());
    plot_c.loop();
    new TCanvas();
    plot_c.Draw(corr1(), S_DrawOption("colz", "", "y:x"));
    new TCanvas();
    plot_c.Draw(corr2(), S_DrawOption("colz", "", "y:x"));
    new TCanvas();
    plot_c.Draw(closest(), S_DrawOption("", "", "y"));
    new TCanvas();
    TH2D* h2 = new TH2D("h2", "23wads", 100, 0, 0, 100, 0, 0);
    plot_c.Draw(resVSmissing(), S_DrawOption("colz", "", "x:y").cut_x(-0.3, 0.3).output_object(h2));
    SCT_helpers::CutTH2(h2, S_Cut_BinContent(10));
    auto f = SCT_helpers::LinearFit_Of_Profile(h2);
    h2->Draw("colz");
    auto f1 = f.Clone("sada");
    f1->Draw("same");
    std::cout << "f.GetParameter(\"p1\")  " << f.GetParameter("p1") << std::endl;
    std::cout << "f.GetParameter(\"p0\")  " << f.GetParameter("p0") << std::endl;
  }
  else{
    sct_runs::DEVICE_2_ASIC_on_Position_7_150V(p, "D:/data/DEVICE_2_ASIC_on_Position_7_150V/", "D:/data/DEVICE_2_ASIC_on_Position_7_150V/");
    p.process();
    new TCanvas();
    p.Draw_Hit_map();
    new TCanvas();
    p.Draw_DUT_Hits_map();
    new TCanvas();
    p.DrawResidual();
  }
//   auto h2 = p.getResidualVsMissingCordinate();
// 
//   SCT_helpers::CutTH2(h2, S_Cut_BinContent(20));
//   h2->Draw("colz");
//   
//   
//   TF1 f = SCT_helpers::LinearFit_Of_Profile(h2);
// 
//   h2->Draw("colz");
//   f.Draw("same");
// 
//   std::cout << "f.GetParameter(\"p1\")  " << f.GetParameter("p1") << std::endl;
//   std::cout << "f.GetParameter(\"p0\")  " << f.GetParameter("p0") << std::endl;
  new TBrowser();
  theApp.Run();

}

 