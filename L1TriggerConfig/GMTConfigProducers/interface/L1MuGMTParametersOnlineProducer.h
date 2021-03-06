//-------------------------------------------------
//
//   \class L1MuGMTParametersOnlineProducer
//
//   Description:  A class to produce the L1 GMT emulator parameters in the event setup
//                 by reading them from the online database.
//
//
//   Author :
//   Thomas Themel
//
//--------------------------------------------------
#ifndef GMTConfigProducers_L1MuGMTParametersOnlineProducer_h
#define GMTConfigProducers_L1MuGMTParametersOnlineProducer_h

// system include files
#include <memory>

// user include files

#include "CondFormats/L1TObjects/interface/L1MuGMTParameters.h"
#include "CondFormats/DataRecord/interface/L1MuGMTParametersRcd.h"
#include "CondTools/L1Trigger/interface/L1ConfigOnlineProdBase.h"

//
// class declaration
//

class L1MuGMTParametersOnlineProducer : public L1ConfigOnlineProdBase<L1MuGMTParametersRcd, L1MuGMTParameters> {
public:
  L1MuGMTParametersOnlineProducer(const edm::ParameterSet&);
  ~L1MuGMTParametersOnlineProducer() override;

  /// The method that actually implements the production of the parameter objects
  std::unique_ptr<L1MuGMTParameters> newObject(const std::string& objectKey) override;

protected:
  void checkCMSSWVersion(const coral::AttributeList& configRecord);

private:
  std::string lookupSoftwareConfigKey(const std::string& globalKey);
  bool ignoreVersionMismatch_;
};

#endif
