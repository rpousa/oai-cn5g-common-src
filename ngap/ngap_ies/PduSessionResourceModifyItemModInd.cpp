/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyItemModInd.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyItemModInd::PduSessionResourceModifyItemModInd() {}

//------------------------------------------------------------------------------
PduSessionResourceModifyItemModInd::~PduSessionResourceModifyItemModInd() {}

//------------------------------------------------------------------------------
void PduSessionResourceModifyItemModInd::set(
    const PduSessionId& pduSessionId,
    const OCTET_STRING_t& pduSessionResourceModifyIndicationTransfer) {
  m_PduSessionId = pduSessionId;
  m_PduSessionResourceModifyIndicationTransfer =
      pduSessionResourceModifyIndicationTransfer;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyItemModInd::encode(
    Ngap_PDUSessionResourceModifyItemModInd_t& pduSessionResourceItem) const {
  if (!m_PduSessionId.encode(pduSessionResourceItem.pDUSessionID)) return false;

  pduSessionResourceItem.pDUSessionResourceModifyIndicationTransfer =
      m_PduSessionResourceModifyIndicationTransfer;

  return true;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyItemModInd::decode(
    const Ngap_PDUSessionResourceModifyItemModInd_t& pduSessionResourceItem) {
  if (!m_PduSessionId.decode(pduSessionResourceItem.pDUSessionID)) return false;

  m_PduSessionResourceModifyIndicationTransfer =
      pduSessionResourceItem.pDUSessionResourceModifyIndicationTransfer;

  return true;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyItemModInd::get(
    PduSessionId& pduSessionId,
    OCTET_STRING_t& pduSessionResourceModifyIndicationTransfer) const {
  pduSessionId = m_PduSessionId;
  pduSessionResourceModifyIndicationTransfer =
      m_PduSessionResourceModifyIndicationTransfer;
}

}  // namespace oai::ngap
