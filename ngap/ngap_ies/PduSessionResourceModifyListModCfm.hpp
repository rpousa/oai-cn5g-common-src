/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#ifndef _PDU_SESSION_RESOURCE_MODIFY_LIST_MOD_CFM_H_
#define _PDU_SESSION_RESOURCE_MODIFY_LIST_MOD_CFM_H_

#include <vector>

#include "PduSessionResourceModifyItemModCfm.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceModifyListModCfm.h"
}

namespace oai::ngap {

class PduSessionResourceModifyListModCfm {
 public:
  PduSessionResourceModifyListModCfm();
  virtual ~PduSessionResourceModifyListModCfm();

  void set(const std::vector<PduSessionResourceModifyItemModCfm>&
               pduSessionResourceModifyListModCfm);
  void get(std::vector<PduSessionResourceModifyItemModCfm>&
               pduSessionResourceModifyListModCfm) const;

  bool encode(Ngap_PDUSessionResourceModifyListModCfm_t&
                  pduSessionResourceModifyListModCfm) const;
  bool decode(const Ngap_PDUSessionResourceModifyListModCfm_t&
                  pduSessionResourceModifyListModCfm);

 private:
  std::vector<PduSessionResourceModifyItemModCfm> m_ItemList;
};

}  // namespace oai::ngap

#endif
