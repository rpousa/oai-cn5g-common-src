/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#ifndef PDU_SESSION_RESOURCE_MODIFY_INDICATION_H_
#define PDU_SESSION_RESOURCE_MODIFY_INDICATION_H_

#include "NgapUeMessage.hpp"
#include "PduSessionResourceModifyListModInd.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceModifyIndication.h"
}

namespace oai::ngap {

/*
 * PDU Session Resource Modify Indication (clause 9.2.1.6 of TS 38.413): the
 * NG-RAN telling the core it has moved the downlink N3 endpoint of one or more
 * PDU sessions on its own. A change of gNB-CU-UP under one gNB-CU-CP (clause
 * 8.9.5 of TS 38.401) is the case this exists for.
 */
class PduSessionResourceModifyIndicationMsg : public NgapUeMessage {
 public:
  PduSessionResourceModifyIndicationMsg();
  virtual ~PduSessionResourceModifyIndicationMsg();

  void initialize();

  void setAmfUeNgapId(const uint64_t& id) override;
  void setRanUeNgapId(const uint32_t& id) override;
  bool decode(Ngap_NGAP_PDU_t* ngapMsgPdu) override;

  void setPduSessionResourceModifyIndicationList(
      const std::vector<PDUSessionResourceModifyIndicationItem_t>& list);
  bool getPduSessionResourceModifyIndicationList(
      std::vector<PDUSessionResourceModifyIndicationItem_t>& list) const;

 private:
  Ngap_PDUSessionResourceModifyIndication_t*
      pduSessionResourceModifyIndicationIes;

  std::optional<PduSessionResourceModifyListModInd>
      m_PduSessionResourceModifyList;  // Mandatory
  // TODO: User Location Information (Optional)
};

}  // namespace oai::ngap
#endif
