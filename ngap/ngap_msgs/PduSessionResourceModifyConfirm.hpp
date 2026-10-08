/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#ifndef PDU_SESSION_RESOURCE_MODIFY_CONFIRM_H_
#define PDU_SESSION_RESOURCE_MODIFY_CONFIRM_H_

#include "NgapUeMessage.hpp"
#include "PduSessionResourceModifyListModCfm.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceModifyConfirm.h"
}

namespace oai::ngap {

/*
 * PDU Session Resource Modify Confirm (clause 9.2.1.7 of TS 38.413): the
 * successful outcome of the PDU Session Resource Modify Indication procedure,
 * the core's answer telling the NG-RAN its new downlink endpoint is in use.
 */
class PduSessionResourceModifyConfirmMsg : public NgapUeMessage {
 public:
  PduSessionResourceModifyConfirmMsg();
  virtual ~PduSessionResourceModifyConfirmMsg();

  void initialize();

  void setAmfUeNgapId(const uint64_t& id) override;
  void setRanUeNgapId(const uint32_t& id) override;
  bool decode(Ngap_NGAP_PDU_t* ngapMsgPdu) override;

  void setPduSessionResourceModifyConfirmList(
      const std::vector<PDUSessionResourceModifyConfirmItem_t>& list);
  bool getPduSessionResourceModifyConfirmList(
      std::vector<PDUSessionResourceModifyConfirmItem_t>& list) const;

 private:
  Ngap_PDUSessionResourceModifyConfirm_t* pduSessionResourceModifyConfirmIes;

  std::optional<PduSessionResourceModifyListModCfm>
      m_PduSessionResourceModifyList;  // Optional
  // TODO: PDU Session Resource Failed to Modify List (Mod Cfm) (Optional)
  // TODO: Criticality Diagnostics (Optional)
};

}  // namespace oai::ngap
#endif
