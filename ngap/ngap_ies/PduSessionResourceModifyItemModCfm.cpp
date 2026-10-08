/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyItemModCfm.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyItemModCfm::PduSessionResourceModifyItemModCfm() {}

//------------------------------------------------------------------------------
PduSessionResourceModifyItemModCfm::~PduSessionResourceModifyItemModCfm() {}

//------------------------------------------------------------------------------
void PduSessionResourceModifyItemModCfm::set(
    const PduSessionId& pduSessionId,
    const OCTET_STRING_t& pduSessionResourceModifyConfirmTransfer) {
  m_PduSessionId = pduSessionId;
  m_PduSessionResourceModifyConfirmTransfer =
      pduSessionResourceModifyConfirmTransfer;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyItemModCfm::encode(
    Ngap_PDUSessionResourceModifyItemModCfm_t& pduSessionResourceItem) const {
  if (!m_PduSessionId.encode(pduSessionResourceItem.pDUSessionID)) return false;

  pduSessionResourceItem.pDUSessionResourceModifyConfirmTransfer =
      m_PduSessionResourceModifyConfirmTransfer;

  return true;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyItemModCfm::decode(
    const Ngap_PDUSessionResourceModifyItemModCfm_t& pduSessionResourceItem) {
  if (!m_PduSessionId.decode(pduSessionResourceItem.pDUSessionID)) return false;

  m_PduSessionResourceModifyConfirmTransfer =
      pduSessionResourceItem.pDUSessionResourceModifyConfirmTransfer;

  return true;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyItemModCfm::get(
    PduSessionId& pduSessionId,
    OCTET_STRING_t& pduSessionResourceModifyConfirmTransfer) const {
  pduSessionId = m_PduSessionId;
  pduSessionResourceModifyConfirmTransfer =
      m_PduSessionResourceModifyConfirmTransfer;
}

}  // namespace oai::ngap
