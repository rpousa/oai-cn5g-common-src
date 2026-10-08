/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#ifndef _PDU_SESSION_RESOURCE_MODIFY_LIST_MOD_IND_H_
#define _PDU_SESSION_RESOURCE_MODIFY_LIST_MOD_IND_H_

#include <vector>

#include "PduSessionResourceModifyItemModInd.hpp"

extern "C" {
#include "Ngap_PDUSessionResourceModifyListModInd.h"
}

namespace oai::ngap {

class PduSessionResourceModifyListModInd {
 public:
  PduSessionResourceModifyListModInd();
  virtual ~PduSessionResourceModifyListModInd();

  void set(const std::vector<PduSessionResourceModifyItemModInd>&
               pduSessionResourceModifyListModInd);
  void get(std::vector<PduSessionResourceModifyItemModInd>&
               pduSessionResourceModifyListModInd) const;

  bool encode(Ngap_PDUSessionResourceModifyListModInd_t&
                  pduSessionResourceModifyListModInd) const;
  bool decode(const Ngap_PDUSessionResourceModifyListModInd_t&
                  pduSessionResourceModifyListModInd);

 private:
  std::vector<PduSessionResourceModifyItemModInd> m_ItemList;
};

}  // namespace oai::ngap

#endif
