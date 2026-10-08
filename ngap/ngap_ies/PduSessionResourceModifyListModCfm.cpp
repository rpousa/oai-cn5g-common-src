/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyListModCfm.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyListModCfm::PduSessionResourceModifyListModCfm() {}

//------------------------------------------------------------------------------
PduSessionResourceModifyListModCfm::~PduSessionResourceModifyListModCfm() {}

//------------------------------------------------------------------------------
void PduSessionResourceModifyListModCfm::set(
    const std::vector<PduSessionResourceModifyItemModCfm>& list) {
  m_ItemList = list;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyListModCfm::encode(
    Ngap_PDUSessionResourceModifyListModCfm_t& list) const {
  for (auto pdu : m_ItemList) {
    Ngap_PDUSessionResourceModifyItemModCfm_t* item =
        (Ngap_PDUSessionResourceModifyItemModCfm_t*) calloc(
            1, sizeof(Ngap_PDUSessionResourceModifyItemModCfm_t));

    if (!item) return false;
    if (!pdu.encode(*item)) return false;
    if (ASN_SEQUENCE_ADD(&list.list, item) != 0) return false;
  }

  return true;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyListModCfm::decode(
    const Ngap_PDUSessionResourceModifyListModCfm_t&
        pdu_session_resource_modify_list) {
  uint32_t num_pdu_sessions = pdu_session_resource_modify_list.list.count;

  for (int i = 0; i < num_pdu_sessions; i++) {
    PduSessionResourceModifyItemModCfm item = {};

    if (!item.decode(*pdu_session_resource_modify_list.list.array[i]))
      return false;
    m_ItemList.push_back(item);
  }

  return true;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyListModCfm::get(
    std::vector<PduSessionResourceModifyItemModCfm>& list) const {
  list = m_ItemList;
}

}  // namespace oai::ngap
