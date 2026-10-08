/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#ifndef _PDU_SESSION_RESOURCE_MODIFY_ITEM_MOD_CFM_H_
#define _PDU_SESSION_RESOURCE_MODIFY_ITEM_MOD_CFM_H_

#include "PduSessionId.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceModifyItemModCfm.h"
}

namespace oai::ngap {

class PduSessionResourceModifyItemModCfm {
 public:
  PduSessionResourceModifyItemModCfm();
  virtual ~PduSessionResourceModifyItemModCfm();

  void set(
      const PduSessionId& pduSessionId,
      const OCTET_STRING_t& pduSessionResourceModifyConfirmTransfer);
  void get(
      PduSessionId& pduSessionId,
      OCTET_STRING_t& pduSessionResourceModifyConfirmTransfer) const;

  bool encode(
      Ngap_PDUSessionResourceModifyItemModCfm_t& pduSessionResourceItem) const;
  bool decode(
      const Ngap_PDUSessionResourceModifyItemModCfm_t& pduSessionResourceItem);

 private:
  PduSessionId m_PduSessionId;                                    // Mandatory
  OCTET_STRING_t m_PduSessionResourceModifyConfirmTransfer = {};  // Mandatory
  // TODO: iE-Extensions (Optional)
};

}  // namespace oai::ngap

#endif
