fndef RecoLocalFastTime_FTLClusterizer_MTDCPEFromSiPMTime_H
#define RecoLocalFastTime_FTLClusterizer_MTDCPEFromSiPMTime_H 1

//-----------------------------------------------------------------------------
// \class        MTDCPEFromSiPMTime
//-----------------------------------------------------------------------------

#include <utility>
#include <memory>
#include <vector>
#include "TMath.h"

#include "MTDClusterParameterEstimator.h"

#include "Geometry/MTDGeometryBuilder/interface/MTDGeometry.h"
#include "Geometry/MTDGeometryBuilder/interface/MTDGeomDetUnit.h"
#include "Geometry/MTDGeometryBuilder/interface/ProxyMTDTopology.h"
#include "Geometry/MTDGeometryBuilder/interface/RectangularMTDTopology.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/GeometryCommonDetAlgo/interface/MeasurementPoint.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/MeasurementError.h"
#include "DataFormats/GeometrySurface/interface/GloballyPositioned.h"

#include "RecoLocalFastTime/FTLClusterizer/interface/MTDCPEBase.h"

#include <unordered_map>

#include <iostream>


class MTDCPEFromSiPMTime : public MTDCPEBase
{
   
public:
   MTDCPEFromSiPMTime(edm::ParameterSet const& conf, const MTDGeometry& geom);  
   
private:
   //--------------------------------------------------------------------------
   // This is where the action happens.
   //--------------------------------------------------------------------------
   virtual LocalPoint localPosition(DetParam const & dp, ClusterParam & cp) const override;
   virtual LocalError localError   (DetParam const & dp, ClusterParam & cp) const override;
};

#endif
