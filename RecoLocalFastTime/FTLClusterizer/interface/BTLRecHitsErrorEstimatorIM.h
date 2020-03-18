#ifndef RecoLocalFastTime_FTLClusterizer_BTLRecHitsErrorEstimatorIM_H
#define RecoLocalFastTime_FTLClusterizer_BTLRecHitsErrorEstimatorIM_H 1

//-----------------------------------------------------------------------------
// \class         BTLRecHitsErrorEstimatorIM
// Used to improve the local error of recHits and TrackingrecHits in BTL
//-----------------------------------------------------------------------------

#include "Geometry/MTDGeometryBuilder/interface/MTDGeomDetUnit.h"
#include "Geometry/MTDGeometryBuilder/interface/RectangularMTDTopology.h"
#include "Geometry/MTDGeometryBuilder/interface/ProxyMTDTopology.h"

#include "Geometry/CommonDetUnit/interface/GeomDetEnumerators.h"

#include "Geometry/MTDGeometryBuilder/interface/MTDGeometry.h"

#include "MagneticField/Engine/interface/MagneticField.h"

#include <iostream>

class BTLRecHitsErrorEstimatorIM
{
  public:
    BTLRecHitsErrorEstimatorIM(const MTDGeomDet* det, const LocalPoint& lp)
      :det_(det), lp_(lp)
    {
    }
    //BTLRecHitsErrorEstimatorIM(const MTDGeomDetUnit* det, const LocalPoint& lp)
    LocalError localError(){
      if (GeomDetEnumerators::isEndcap(det_->type().subDetector())){
        std::cout << "This is an object from Endcap. Only use it for the Barrel!" << std::endl;
        return LocalError(0,0,0);
      }
      const ProxyMTDTopology& topoproxy = static_cast<const ProxyMTDTopology&>(det_->topology());
      const RectangularMTDTopology& topo = static_cast<const RectangularMTDTopology&>(topoproxy.specificTopology());
      //GlobalPoint gp = det_->toGlobal(lp_);
      //std::cout << "gp: " << gp.x() << "  " << gp.y() << " " << gp.z();
      //std::pair<float,float> pitch = topo_->pitch(); //get the pitch
      //double pitchX = pitch.first;
      //double pitchY = pitch.second;
      MeasurementPoint mp = topo.measurementPosition(lp_);
      //std::cout << "mp_IM: " << mp.x() << " " << mp.y()<< std::endl;
      MeasurementError simpleRect(1./12.,0,1./12.);
      LocalError error_before = topo.localError(mp,simpleRect);
      LocalError error_modified(error_before.xx(),error_before.xy(),0.36);
      return error_modified;
    }
  private:
    //const MTDGeomDetUnit * detU_;
    const MTDGeomDet * det_;
    const LocalPoint & lp_;

};

#endif
