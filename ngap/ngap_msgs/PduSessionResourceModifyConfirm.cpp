/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyConfirm.hpp"

#include "logger_base.hpp"
extern "C" {
#include "Ngap_ProtocolIE_Container_compat.h"
}
#include "utils.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyConfirmMsg::PduSessionResourceModifyConfirmMsg()
    : NgapUeMessage() {
  m_PduSessionResourceModifyList = std::nullopt;
  setMessageType(NgapMessageType::PDU_SESSION_RESOURCE_MODIFY_CONFIRM);
  initialize();
}

//------------------------------------------------------------------------------
PduSessionResourceModifyConfirmMsg::~PduSessionResourceModifyConfirmMsg() {}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmMsg::initialize() {
  pduSessionResourceModifyConfirmIes =
      &(ngapPdu->choice.successfulOutcome->value.choice
            .PDUSessionResourceModifyConfirm);
  if (!pduSessionResourceModifyConfirmIes->protocolIEs) {
    pduSessionResourceModifyConfirmIes->protocolIEs =
        (struct Ngap_ProtocolIE_Container*) calloc(
            1, sizeof(struct Ngap_ProtocolIE_Container));
  }
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmMsg::setAmfUeNgapId(const uint64_t& id) {
  NgapUeMessage::m_AmfUeNgapId.set(id);

  Ngap_PDUSessionResourceModifyConfirmIEs_t* ie =
      (Ngap_PDUSessionResourceModifyConfirmIEs_t*) calloc(
          1, sizeof(Ngap_PDUSessionResourceModifyConfirmIEs_t));
  ie->id          = Ngap_ProtocolIE_ID_id_AMF_UE_NGAP_ID;
  ie->criticality = Ngap_Criticality_ignore;
  ie->value.present =
      Ngap_PDUSessionResourceModifyConfirmIEs__value_PR_AMF_UE_NGAP_ID;

  int ret =
      NgapUeMessage::m_AmfUeNgapId.encode(ie->value.choice.AMF_UE_NGAP_ID);
  if (!ret) {
    oai::logger::logger_common::ngap().error(
        "Encode NGAP AMF_UE_NGAP_ID IE error");
    oai::utils::utils::free_wrapper((void**) &ie);
    return;
  }

  ret = ASN_SEQUENCE_ADD(
      &pduSessionResourceModifyConfirmIes->protocolIEs->list, ie);
  if (ret != 0)
    oai::logger::logger_common::ngap().error(
        "Encode NGAP AMF_UE_NGAP_ID IE error");
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmMsg::setRanUeNgapId(
    const uint32_t& ranUeNgapId) {
  NgapUeMessage::m_RanUeNgapId.set(ranUeNgapId);

  Ngap_PDUSessionResourceModifyConfirmIEs_t* ie =
      (Ngap_PDUSessionResourceModifyConfirmIEs_t*) calloc(
          1, sizeof(Ngap_PDUSessionResourceModifyConfirmIEs_t));
  ie->id          = Ngap_ProtocolIE_ID_id_RAN_UE_NGAP_ID;
  ie->criticality = Ngap_Criticality_ignore;
  ie->value.present =
      Ngap_PDUSessionResourceModifyConfirmIEs__value_PR_RAN_UE_NGAP_ID;

  int ret =
      NgapUeMessage::m_RanUeNgapId.encode(ie->value.choice.RAN_UE_NGAP_ID);
  if (!ret) {
    oai::logger::logger_common::ngap().error(
        "Encode NGAP RAN_UE_NGAP_ID IE error");
    oai::utils::utils::free_wrapper((void**) &ie);
    return;
  }

  ret = ASN_SEQUENCE_ADD(
      &pduSessionResourceModifyConfirmIes->protocolIEs->list, ie);
  if (ret != 0)
    oai::logger::logger_common::ngap().error(
        "Encode NGAP RAN_UE_NGAP_ID IE error");
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmMsg::setPduSessionResourceModifyConfirmList(
    const std::vector<PDUSessionResourceModifyConfirmItem_t>& list) {
  std::vector<PduSessionResourceModifyItemModCfm> itemModCfmList;

  for (int i = 0; i < list.size(); i++) {
    PduSessionId pduSessionId               = {};
    PduSessionResourceModifyItemModCfm item = {};

    pduSessionId.set(list[i].pduSessionId);
    item.set(pduSessionId, list[i].pduSessionResourceModifyConfirmTransfer);
    itemModCfmList.push_back(item);
  }

  PduSessionResourceModifyListModCfm item_list = {};
  item_list.set(itemModCfmList);
  m_PduSessionResourceModifyList =
      std::optional<PduSessionResourceModifyListModCfm>(item_list);

  Ngap_PDUSessionResourceModifyConfirmIEs_t* ie =
      (Ngap_PDUSessionResourceModifyConfirmIEs_t*) calloc(
          1, sizeof(Ngap_PDUSessionResourceModifyConfirmIEs_t));
  ie->id          = Ngap_ProtocolIE_ID_id_PDUSessionResourceModifyListModCfm;
  ie->criticality = Ngap_Criticality_ignore;
  ie->value.present =
      Ngap_PDUSessionResourceModifyConfirmIEs__value_PR_PDUSessionResourceModifyListModCfm;

  int ret = m_PduSessionResourceModifyList.value().encode(
      ie->value.choice.PDUSessionResourceModifyListModCfm);
  if (!ret) {
    oai::logger::logger_common::ngap().error(
        "Encode NGAP PDUSessionResourceModifyListModCfm IE error");
    oai::utils::utils::free_wrapper((void**) &ie);
    return;
  }

  ret = ASN_SEQUENCE_ADD(
      &pduSessionResourceModifyConfirmIes->protocolIEs->list, ie);
  if (ret != 0)
    oai::logger::logger_common::ngap().error(
        "Encode NGAP PDUSessionResourceModifyListModCfm IE error");
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyConfirmMsg::getPduSessionResourceModifyConfirmList(
    std::vector<PDUSessionResourceModifyConfirmItem_t>& list) const {
  if (!m_PduSessionResourceModifyList.has_value()) return false;

  std::vector<PduSessionResourceModifyItemModCfm> itemModCfmList;
  m_PduSessionResourceModifyList.value().get(itemModCfmList);

  for (auto& it : itemModCfmList) {
    PDUSessionResourceModifyConfirmItem_t item = {};
    PduSessionId pduSessionId                  = {};
    it.get(pduSessionId, item.pduSessionResourceModifyConfirmTransfer);
    pduSessionId.get(item.pduSessionId);
    list.push_back(item);
  }

  return true;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyConfirmMsg::decode(Ngap_NGAP_PDU_t* ngapMsgPdu) {
  ngapPdu = ngapMsgPdu;

  if (ngapPdu->present != Ngap_NGAP_PDU_PR_successfulOutcome) {
    oai::logger::logger_common::ngap().error("MessageType error!");
    return false;
  }

  if (ngapPdu->choice.successfulOutcome &&
      ngapPdu->choice.successfulOutcome->procedureCode ==
          Ngap_ProcedureCode_id_PDUSessionResourceModifyIndication &&
      ngapPdu->choice.successfulOutcome->value.present ==
          Ngap_SuccessfulOutcome__value_PR_PDUSessionResourceModifyConfirm) {
    pduSessionResourceModifyConfirmIes =
        &ngapPdu->choice.successfulOutcome->value.choice
             .PDUSessionResourceModifyConfirm;
  } else {
    oai::logger::logger_common::ngap().error(
        "Check PDUSessionResourceModifyConfirm message error!");
    return false;
  }

  if (!pduSessionResourceModifyConfirmIes->protocolIEs) {
    oai::logger::logger_common::ngap().error(
        "PDUSessionResourceModifyConfirm carries no protocol IE");
    return false;
  }

  for (int i = 0;
       i < pduSessionResourceModifyConfirmIes->protocolIEs->list.count; i++) {
    Ngap_PDUSessionResourceModifyConfirmIEs_t* ngap_ie =
        (Ngap_PDUSessionResourceModifyConfirmIEs_t*)
            pduSessionResourceModifyConfirmIes->protocolIEs->list.array[i];
    switch (ngap_ie->id) {
      case Ngap_ProtocolIE_ID_id_AMF_UE_NGAP_ID: {
        if (ngap_ie->value.present !=
            Ngap_PDUSessionResourceModifyConfirmIEs__value_PR_AMF_UE_NGAP_ID) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP AMF_UE_NGAP_ID IE error");
          return false;
        }
        if (!NgapUeMessage::m_AmfUeNgapId.decode(
                ngap_ie->value.choice.AMF_UE_NGAP_ID)) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP AMF_UE_NGAP_ID IE error");
          return false;
        }
      } break;
      case Ngap_ProtocolIE_ID_id_RAN_UE_NGAP_ID: {
        if (ngap_ie->value.present !=
            Ngap_PDUSessionResourceModifyConfirmIEs__value_PR_RAN_UE_NGAP_ID) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP RAN_UE_NGAP_ID IE error");
          return false;
        }
        if (!NgapUeMessage::m_RanUeNgapId.decode(
                ngap_ie->value.choice.RAN_UE_NGAP_ID)) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP RAN_UE_NGAP_ID IE error");
          return false;
        }
      } break;
      case Ngap_ProtocolIE_ID_id_PDUSessionResourceModifyListModCfm: {
        if (ngap_ie->value.present !=
            Ngap_PDUSessionResourceModifyConfirmIEs__value_PR_PDUSessionResourceModifyListModCfm) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP PDUSessionResourceModifyListModCfm IE error");
          return false;
        }
        PduSessionResourceModifyListModCfm item_list = {};
        if (!item_list.decode(
                ngap_ie->value.choice.PDUSessionResourceModifyListModCfm)) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP PDUSessionResourceModifyListModCfm IE error");
          return false;
        }
        m_PduSessionResourceModifyList =
            std::optional<PduSessionResourceModifyListModCfm>(item_list);
      } break;
      default: {
        /* see the note in PduSessionResourceModifyIndication::decode: an
         * unknown optional IE is skipped rather than failing the message */
        oai::logger::logger_common::ngap().debug(
            "PDUSessionResourceModifyConfirm: ignoring protocol IE %ld",
            ngap_ie->id);
      } break;
    }
  }

  return true;
}

}  // namespace oai::ngap
