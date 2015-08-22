#ifndef setup_description_h__
#define setup_description_h__
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml.hpp"
#include "xml_helpers/xml_util.hh"
#define  sct_corr_XML_ERROR_DEFAULT_VALUE  -666666666666
namespace sct_corr {
using xml_n = rapidxml::xml_node < char >;
namespace linear_algebra {


struct xyz_hit {
  double x, y, z;

};

class Matrix_3x3 {
public:
  Matrix_3x3() {}

  xyz_hit a1, a2, a3;

};

Double_t operator*(const xyz_hit& ha, const xyz_hit& hb) {
  return ha.x*hb.x + ha.y*hb.y + ha.z*hb.z;
}
xyz_hit operator+(const xyz_hit& ha, const xyz_hit& hb) {

  xyz_hit ret;
  ret.x = ha.x + hb.x;
  ret.y = ha.y + hb.y;
  ret.z = ha.z + hb.z;

  return ret;
}
xyz_hit operator*(const Matrix_3x3& M, const xyz_hit& hb) {

  xyz_hit ret;
  ret.x = M.a1*hb;
  ret.y = M.a2*hb;
  ret.z = M.a3*hb;
  return ret;
}

Matrix_3x3 trans(const Matrix_3x3& Ma) {

  Matrix_3x3 ret;
  ret.a1.x = Ma.a1.x;
  ret.a2.x = Ma.a1.y;
  ret.a3.x = Ma.a1.z;

  ret.a1.y = Ma.a2.x;
  ret.a2.y = Ma.a2.y;
  ret.a3.y = Ma.a2.z;

  ret.a1.z = Ma.a3.x;
  ret.a2.z = Ma.a3.y;
  ret.a3.z = Ma.a3.z;

  return ret;

}
Matrix_3x3 operator*(const Matrix_3x3& Ma, const Matrix_3x3& Mb) {

  Matrix_3x3 ret;
  auto MB_trans = trans(Mb);
  ret.a1 = Ma*MB_trans.a1;
  ret.a2 = Ma*MB_trans.a2;
  ret.a3 = Ma*MB_trans.a3;

  return trans(ret);
}
Matrix_3x3 operator+(const Matrix_3x3& Ma, const Matrix_3x3& Mb) {

  Matrix_3x3 ret;
  ret.a1 = Ma.a1 + Mb.a1;
  ret.a2 = Ma.a2 + Mb.a2;
  ret.a3 = Ma.a3 + Mb.a3;
  return ret;
}
Matrix_3x3 RotX(Double_t phix) {

  Matrix_3x3 ret;

  ret.a1.x = 1; ret.a1.y = 0; ret.a1.z = 0;
  ret.a2.x = 0; ret.a2.y = TMath::Cos(phix); ret.a2.z = -TMath::Sin(phix);
  ret.a3.x = 0; ret.a3.y = TMath::Sin(phix); ret.a3.z = TMath::Cos(phix);

}
Matrix_3x3 RotX(Double_t phix) {

  Matrix_3x3 ret;

  ret.a1.x = 1; ret.a1.y = 0; ret.a1.z = 0;
  ret.a2.x = 0; ret.a2.y = TMath::Cos(phix); ret.a2.z = -TMath::Sin(phix);
  ret.a3.x = 0; ret.a3.y = TMath::Sin(phix); ret.a3.z = TMath::Cos(phix);
  return   ret;
}
Matrix_3x3 RotY(Double_t phiy) {

  Matrix_3x3 ret;

  ret.a1.x = TMath::Cos(phiy); ret.a1.y = 0; ret.a1.z = TMath::Sin(phiy);
  ret.a2.x = 0; ret.a2.y = 1; ret.a2.z = 0;
  ret.a3.x = -TMath::Sin(phiy); ret.a3.y = 0; ret.a3.z = TMath::Cos(phiy);


  return   ret;
}
Matrix_3x3 RotZ(Double_t phix) {

  Matrix_3x3 ret;

  ret.a1.x = 1; ret.a1.y = 0; ret.a1.z = 0;
  ret.a2.x = 0; ret.a2.y = TMath::Cos(phix); ret.a2.z = -TMath::Sin(phix);
  ret.a3.x = 0; ret.a3.y = TMath::Sin(phix); ret.a3.z = TMath::Cos(phix);
  return   ret;
}

}

struct Xladder {
public:
  Xladder(xml_n* n):
  
    ID(xml_util::getAtribute(n, "ID", ID)),
    positionX(xml_util::getAtribute(n, "positionX", positionX)),
    positionY(xml_util::getAtribute(n, "positionY", positionY)),
    positionZ(xml_util::getAtribute(n, "positionZ", positionZ)),
    radLength(xml_util::getAtribute(n, "radLength", radLength)),
    rotationXY(xml_util::getAtribute(n, "rotationXY", rotationXY)),
    rotationZX(xml_util::getAtribute(n, "rotationZX", rotationZX)),
    rotationZY(xml_util::getAtribute(n, "rotationZY", rotationZY)),


    sizeX(xml_util::getAtribute(n, "sizeX", sizeX)),
    sizeY(xml_util::getAtribute(n, "sizeY", sizeY)),
    thickness(xml_util::getAtribute(n, "thickness", thickness))
  {}
  double ID= sct_corr_XML_ERROR_DEFAULT_VALUE,
    positionX= sct_corr_XML_ERROR_DEFAULT_VALUE,
    positionY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    positionZ= sct_corr_XML_ERROR_DEFAULT_VALUE,
    radLength= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotationXY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotationZX= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotationZY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    sizeX= sct_corr_XML_ERROR_DEFAULT_VALUE,
    sizeY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    thickness = sct_corr_XML_ERROR_DEFAULT_VALUE;


};
struct Xsensitive {
public:
  Xsensitive(xml_n* n) :

    ID ( xml_util::getAtribute(n, "ID", ID)),
    npixelX(xml_util::getAtribute(n, "npixelX", npixelX)),
    npixelY(xml_util::getAtribute(n, "npixelY", npixelY)),


    pitchX(xml_util::getAtribute(n, "pitchX", pitchX)),
    pitchY(xml_util::getAtribute(n, "pitchY", pitchY)),
    positionX(xml_util::getAtribute(n, "positionX", positionX)),
    positionY(xml_util::getAtribute(n, "positionY", positionY)),
    positionZ(xml_util::getAtribute(n, "positionZ", positionZ)),
    radLength(xml_util::getAtribute(n, "radLength", radLength)),

    resolution(xml_util::getAtribute(n, "resolution", resolution)),
    rotation1(xml_util::getAtribute(n, "rotation1", rotation1)),
    rotation2(xml_util::getAtribute(n, "rotation2", rotation2)),
    rotation3(xml_util::getAtribute(n, "rotation3", rotation3)),


    rotation4(xml_util::getAtribute(n, "rotation4", rotation4)),
    sizeX(xml_util::getAtribute(n, "sizeX", sizeX)),
    sizeY(xml_util::getAtribute(n, "sizeY", sizeY)),
    thickness(xml_util::getAtribute(n, "thickness", thickness))

  {}
  double ID = sct_corr_XML_ERROR_DEFAULT_VALUE,
  npixelX = sct_corr_XML_ERROR_DEFAULT_VALUE,
    npixelY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    pitchX= sct_corr_XML_ERROR_DEFAULT_VALUE,
    pitchY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    positionX= sct_corr_XML_ERROR_DEFAULT_VALUE,
    positionY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    positionZ= sct_corr_XML_ERROR_DEFAULT_VALUE,
    radLength= sct_corr_XML_ERROR_DEFAULT_VALUE,
    resolution= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotation1= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotation2= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotation3= sct_corr_XML_ERROR_DEFAULT_VALUE,
    rotation4= sct_corr_XML_ERROR_DEFAULT_VALUE,
    sizeX= sct_corr_XML_ERROR_DEFAULT_VALUE,
    sizeY= sct_corr_XML_ERROR_DEFAULT_VALUE,
    thickness = sct_corr_XML_ERROR_DEFAULT_VALUE;

};
struct Xlayer {
public:
  Xlayer(xml_n* n) :ladder(n->first_node("ladder")), sensitive(n->first_node("sensitive")){}
  Xladder ladder;
  Xsensitive  sensitive;
  static const char* NodeName() {
    return "layer";
  }
};
struct Xdetector {
public:
  Xdetector(xml_n* n) {
    geartype = xml_util::getAtribute(n, "geartype", "notSet");
    name = xml_util::getAtribute(n, "name", "notSet");

    siplanesID = xml_util::getAtribute(n->first_node("siplanesID"), "ID", siplanesID);
    siplanesType = xml_util::getAtribute(n->first_node("siplanesType"), "type", "notSet");

    siplanesNumber = xml_util::getAtribute(n->first_node("siplanesNumber"), "number", siplanesNumber);

    layer = xml_util::getVectorOfT<Xlayer>(n->first_node("layers"));
  }
  std::string geartype, name;
  double siplanesID = 0;
  std::string siplanesType;
  double siplanesNumber=0;
  std::vector<Xlayer> layer;
};
struct XBField {
public:
  XBField(xml_n* n) :type(xml_util::getAtribute(n, "type", "notSet")), x(xml_util::getAtribute(n, "x", (double)0.0)), y(xml_util::getAtribute(n, "y", (double)0.0)), z(xml_util::getAtribute(n, "z", (double)0.0)) {}
  std::string type;
  double x, y, z;
};

struct Xgear {

public:
  Xgear(xml_n* n) :detectorName(xml_util::getAtribute(n->first_node("global"), "detectorName", "notSet")), bfield(n->first_node("BField")), detector(n->first_node("detectors")->first_node("detector")){}


  std::string detectorName;
  XBField bfield;
  Xdetector detector;
};

}

#endif // setup_description_h__
