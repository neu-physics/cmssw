#include "Geometry/MTDGeometryBuilder/interface/MTDGeomDetUnit.h"
#include "Geometry/MTDGeometryBuilder/interface/RectangularMTDTopology.h"
#include "Geometry/MTDGeometryBuilder/interface/ProxyMTDTopology.h"

#include "RecoLocalFastTime/FTLClusterizer/interface/BTLRecHitsErrorEstimatorIM.h"

#include "RecoLocalFastTime/FTLClusterizer/interface/MTDCPEFromSiPMTime.h"
#include "Geometry/CommonDetUnit/interface/GeomDetEnumerators.h"
// MessageLogger
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// Magnetic field
#include "MagneticField/Engine/interface/MagneticField.h"


#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
//  A constructor run for generic and templates
//
//-----------------------------------------------------------------------------
MTDCPEFromSiPMTime::MTDCPEFromSiPMTime(edm::ParameterSet const & conf,
                     const MTDGeometry& geom)
  : MTDCPEBase(conf, geom)
{
   //fillDetParams();
}

LocalPoint
MTDCPEFromSiPMTime::localPosition(DetParam const & dp, ClusterParam & cp) const
{
  //remember measurement point is row(col)+0.5f
  MeasurementPoint pos(cp.theCluster->x(),cp.theCluster->y());
  return dp.theTopol->localPosition(pos);
}

LocalError
MTDCPEFromSiPMTime::localError(DetParam const & dp,  ClusterParam & cp) const
{
  constexpr double one_over_twelve = 1./12.;
  //constexpr double one_over_twelve = 10;
  MeasurementPoint pos(cp.theCluster->x(),cp.theCluster->y());
  MeasurementError simpleRect(one_over_twelve,0,one_over_twelve);
  if (GeomDetEnumerators::isBarrel(dp.thePart) ){
    LocalPoint lp = localPosition(dp,cp);
    BTLRecHitsErrorEstimatorIM IM(dp.theDet,lp);
    LocalError err_improved = IM.localError();
    return err_improved;
  }
  else {
    return dp.theTopol->localError(pos,simpleRect);
  }

}
