/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyListModInd.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyListModInd::PduSessionResourceModifyListModInd() {}

//------------------------------------------------------------------------------
PduSessionResourceModifyListModInd::~PduSessionResourceModifyListModInd() {}

//------------------------------------------------------------------------------
void PduSessionResourceModifyListModInd::set(
    const std::vector<PduSessionResourceModifyItemModInd>& list) {
  m_ItemList = list;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyListModInd::encode(
    Ngap_PDUSessionResourceModifyListModInd_t& list) const {
  for (auto pdu : m_ItemList) {
    Ngap_PDUSessionResourceModifyItemModInd_t* item =
        (Ngap_PDUSessionResourceModifyItemModInd_t*) calloc(
            1, sizeof(Ngap_PDUSessionResourceModifyItemModInd_t));

    if (!item) return false;
    if (!pdu.encode(*item)) return false;
    if (ASN_SEQUENCE_ADD(&list.list, item) != 0) return false;
  }

  return true;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyListModInd::decode(
    const Ngap_PDUSessionResourceModifyListModInd_t&
        pdu_session_resource_modify_list) {
  uint32_t num_pdu_sessions = pdu_session_resource_modify_list.list.count;

  for (int i = 0; i < num_pdu_sessions; i++) {
    PduSessionResourceModifyItemModInd item = {};

    if (!item.decode(*pdu_session_resource_modify_list.list.array[i]))
      return false;
    m_ItemList.push_back(item);
  }

  return true;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyListModInd::get(
    std::vector<PduSessionResourceModifyItemModInd>& list) const {
  list = m_ItemList;
}

}  // namespace oai::ngap
