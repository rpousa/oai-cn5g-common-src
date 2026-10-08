/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyIndication.hpp"

#include "logger_base.hpp"
extern "C" {
#include "Ngap_ProtocolIE_Container_compat.h"
}
#include "utils.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyIndicationMsg::PduSessionResourceModifyIndicationMsg()
    : NgapUeMessage() {
  m_PduSessionResourceModifyList = std::nullopt;
  setMessageType(NgapMessageType::PDU_SESSION_RESOURCE_MODIFY_INDICATION);
  initialize();
}

//------------------------------------------------------------------------------
PduSessionResourceModifyIndicationMsg::
    ~PduSessionResourceModifyIndicationMsg() {}

//------------------------------------------------------------------------------
void PduSessionResourceModifyIndicationMsg::initialize() {
  pduSessionResourceModifyIndicationIes =
      &(ngapPdu->choice.initiatingMessage->value.choice
            .PDUSessionResourceModifyIndication);
  if (!pduSessionResourceModifyIndicationIes->protocolIEs) {
    pduSessionResourceModifyIndicationIes->protocolIEs =
        (struct Ngap_ProtocolIE_Container*) calloc(
            1, sizeof(struct Ngap_ProtocolIE_Container));
  }
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyIndicationMsg::setAmfUeNgapId(const uint64_t& id) {
  NgapUeMessage::m_AmfUeNgapId.set(id);

  Ngap_PDUSessionResourceModifyIndicationIEs_t* ie =
      (Ngap_PDUSessionResourceModifyIndicationIEs_t*) calloc(
          1, sizeof(Ngap_PDUSessionResourceModifyIndicationIEs_t));
  ie->id          = Ngap_ProtocolIE_ID_id_AMF_UE_NGAP_ID;
  ie->criticality = Ngap_Criticality_reject;
  ie->value.present =
      Ngap_PDUSessionResourceModifyIndicationIEs__value_PR_AMF_UE_NGAP_ID;

  int ret =
      NgapUeMessage::m_AmfUeNgapId.encode(ie->value.choice.AMF_UE_NGAP_ID);
  if (!ret) {
    oai::logger::logger_common::ngap().error(
        "Encode NGAP AMF_UE_NGAP_ID IE error");
    oai::utils::utils::free_wrapper((void**) &ie);
    return;
  }

  ret = ASN_SEQUENCE_ADD(
      &pduSessionResourceModifyIndicationIes->protocolIEs->list, ie);
  if (ret != 0)
    oai::logger::logger_common::ngap().error(
        "Encode NGAP AMF_UE_NGAP_ID IE error");
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyIndicationMsg::setRanUeNgapId(
    const uint32_t& ranUeNgapId) {
  NgapUeMessage::m_RanUeNgapId.set(ranUeNgapId);

  Ngap_PDUSessionResourceModifyIndicationIEs_t* ie =
      (Ngap_PDUSessionResourceModifyIndicationIEs_t*) calloc(
          1, sizeof(Ngap_PDUSessionResourceModifyIndicationIEs_t));
  ie->id          = Ngap_ProtocolIE_ID_id_RAN_UE_NGAP_ID;
  ie->criticality = Ngap_Criticality_reject;
  ie->value.present =
      Ngap_PDUSessionResourceModifyIndicationIEs__value_PR_RAN_UE_NGAP_ID;

  int ret =
      NgapUeMessage::m_RanUeNgapId.encode(ie->value.choice.RAN_UE_NGAP_ID);
  if (!ret) {
    oai::logger::logger_common::ngap().error(
        "Encode NGAP RAN_UE_NGAP_ID IE error");
    oai::utils::utils::free_wrapper((void**) &ie);
    return;
  }

  ret = ASN_SEQUENCE_ADD(
      &pduSessionResourceModifyIndicationIes->protocolIEs->list, ie);
  if (ret != 0)
    oai::logger::logger_common::ngap().error(
        "Encode NGAP RAN_UE_NGAP_ID IE error");
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyIndicationMsg::
    setPduSessionResourceModifyIndicationList(
        const std::vector<PDUSessionResourceModifyIndicationItem_t>& list) {
  std::vector<PduSessionResourceModifyItemModInd> itemModIndList;

  for (int i = 0; i < list.size(); i++) {
    PduSessionId pduSessionId               = {};
    PduSessionResourceModifyItemModInd item = {};

    pduSessionId.set(list[i].pduSessionId);
    item.set(pduSessionId, list[i].pduSessionResourceModifyIndicationTransfer);
    itemModIndList.push_back(item);
  }

  PduSessionResourceModifyListModInd item_list = {};
  item_list.set(itemModIndList);
  m_PduSessionResourceModifyList =
      std::optional<PduSessionResourceModifyListModInd>(item_list);

  Ngap_PDUSessionResourceModifyIndicationIEs_t* ie =
      (Ngap_PDUSessionResourceModifyIndicationIEs_t*) calloc(
          1, sizeof(Ngap_PDUSessionResourceModifyIndicationIEs_t));
  ie->id          = Ngap_ProtocolIE_ID_id_PDUSessionResourceModifyListModInd;
  ie->criticality = Ngap_Criticality_reject;
  ie->value.present =
      Ngap_PDUSessionResourceModifyIndicationIEs__value_PR_PDUSessionResourceModifyListModInd;

  int ret = m_PduSessionResourceModifyList.value().encode(
      ie->value.choice.PDUSessionResourceModifyListModInd);
  if (!ret) {
    oai::logger::logger_common::ngap().error(
        "Encode NGAP PDUSessionResourceModifyListModInd IE error");
    oai::utils::utils::free_wrapper((void**) &ie);
    return;
  }

  ret = ASN_SEQUENCE_ADD(
      &pduSessionResourceModifyIndicationIes->protocolIEs->list, ie);
  if (ret != 0)
    oai::logger::logger_common::ngap().error(
        "Encode NGAP PDUSessionResourceModifyListModInd IE error");
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyIndicationMsg::
    getPduSessionResourceModifyIndicationList(
        std::vector<PDUSessionResourceModifyIndicationItem_t>& list) const {
  if (!m_PduSessionResourceModifyList.has_value()) return false;

  std::vector<PduSessionResourceModifyItemModInd> itemModIndList;
  m_PduSessionResourceModifyList.value().get(itemModIndList);

  for (auto& it : itemModIndList) {
    PDUSessionResourceModifyIndicationItem_t item = {};
    PduSessionId pduSessionId                     = {};
    it.get(pduSessionId, item.pduSessionResourceModifyIndicationTransfer);
    pduSessionId.get(item.pduSessionId);
    list.push_back(item);
  }

  return true;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyIndicationMsg::decode(
    Ngap_NGAP_PDU_t* ngapMsgPdu) {
  ngapPdu = ngapMsgPdu;

  if (ngapPdu->present != Ngap_NGAP_PDU_PR_initiatingMessage) {
    oai::logger::logger_common::ngap().error("MessageType error!");
    return false;
  }

  if (ngapPdu->choice.initiatingMessage &&
      ngapPdu->choice.initiatingMessage->procedureCode ==
          Ngap_ProcedureCode_id_PDUSessionResourceModifyIndication &&
      ngapPdu->choice.initiatingMessage->value.present ==
          Ngap_InitiatingMessage__value_PR_PDUSessionResourceModifyIndication) {
    pduSessionResourceModifyIndicationIes =
        &ngapPdu->choice.initiatingMessage->value.choice
             .PDUSessionResourceModifyIndication;
  } else {
    oai::logger::logger_common::ngap().error(
        "Check PDUSessionResourceModifyIndication message error!");
    return false;
  }

  if (!pduSessionResourceModifyIndicationIes->protocolIEs) {
    oai::logger::logger_common::ngap().error(
        "PDUSessionResourceModifyIndication carries no protocol IE");
    return false;
  }

  for (int i = 0;
       i < pduSessionResourceModifyIndicationIes->protocolIEs->list.count;
       i++) {
    Ngap_PDUSessionResourceModifyIndicationIEs_t* ngap_ie =
        (Ngap_PDUSessionResourceModifyIndicationIEs_t*)
            pduSessionResourceModifyIndicationIes->protocolIEs->list.array[i];
    switch (ngap_ie->id) {
      case Ngap_ProtocolIE_ID_id_AMF_UE_NGAP_ID: {
        if (ngap_ie->value.present !=
            Ngap_PDUSessionResourceModifyIndicationIEs__value_PR_AMF_UE_NGAP_ID) {
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
            Ngap_PDUSessionResourceModifyIndicationIEs__value_PR_RAN_UE_NGAP_ID) {
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
      case Ngap_ProtocolIE_ID_id_PDUSessionResourceModifyListModInd: {
        if (ngap_ie->value.present !=
            Ngap_PDUSessionResourceModifyIndicationIEs__value_PR_PDUSessionResourceModifyListModInd) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP PDUSessionResourceModifyListModInd IE error");
          return false;
        }
        PduSessionResourceModifyListModInd item_list = {};
        if (!item_list.decode(
                ngap_ie->value.choice.PDUSessionResourceModifyListModInd)) {
          oai::logger::logger_common::ngap().error(
              "Decoded NGAP PDUSessionResourceModifyListModInd IE error");
          return false;
        }
        m_PduSessionResourceModifyList =
            std::optional<PduSessionResourceModifyListModInd>(item_list);
      } break;
      default: {
        /* An IE this build does not know is not a reason to drop the message.
         * The only optional IE of this procedure is User Location
         * Information, and every mandatory one is handled above. Returning
         * false here -- as the sibling message classes do -- discards a
         * perfectly actionable message because of an IE nobody reads. */
        oai::logger::logger_common::ngap().debug(
            "PDUSessionResourceModifyIndication: ignoring protocol IE %ld",
            ngap_ie->id);
      } break;
    }
  }

  if (!m_PduSessionResourceModifyList.has_value()) {
    oai::logger::logger_common::ngap().error(
        "PDUSessionResourceModifyIndication without a PDU Session Resource "
        "Modify List (Mod Ind)");
    return false;
  }

  return true;
}

}  // namespace oai::ngap
