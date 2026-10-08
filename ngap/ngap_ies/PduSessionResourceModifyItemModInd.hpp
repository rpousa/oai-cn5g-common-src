/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#ifndef _PDU_SESSION_RESOURCE_MODIFY_ITEM_MOD_IND_H_
#define _PDU_SESSION_RESOURCE_MODIFY_ITEM_MOD_IND_H_

#include "PduSessionId.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceModifyItemModInd.h"
}

namespace oai::ngap {

class PduSessionResourceModifyItemModInd {
 public:
  PduSessionResourceModifyItemModInd();
  virtual ~PduSessionResourceModifyItemModInd();

  void set(
      const PduSessionId& pduSessionId,
      const OCTET_STRING_t& pduSessionResourceModifyIndicationTransfer);
  void get(
      PduSessionId& pduSessionId,
      OCTET_STRING_t& pduSessionResourceModifyIndicationTransfer) const;

  bool encode(
      Ngap_PDUSessionResourceModifyItemModInd_t& pduSessionResourceItem) const;
  bool decode(
      const Ngap_PDUSessionResourceModifyItemModInd_t& pduSessionResourceItem);

 private:
  PduSessionId m_PduSessionId;  // Mandatory
  OCTET_STRING_t m_PduSessionResourceModifyIndicationTransfer =
      {};  // Mandatory
  // TODO: iE-Extensions (Optional)
};

}  // namespace oai::ngap

#endif
