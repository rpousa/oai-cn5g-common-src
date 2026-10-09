/*
 * SPDX-License-Identifier: LicenseRef-CSSL-1.0
 */

#include "PduSessionResourceModifyConfirmTransfer.hpp"

#include "logger_base.hpp"
#include "ngap_utils.hpp"
#include "utils.hpp"

namespace oai::ngap {

//------------------------------------------------------------------------------
PduSessionResourceModifyConfirmTransfer::
    PduSessionResourceModifyConfirmTransfer() {
  m_Ie = (Ngap_PDUSessionResourceModifyConfirmTransfer_t*) calloc(
      1, sizeof(Ngap_PDUSessionResourceModifyConfirmTransfer_t));
  m_QosFlowFailedToModifyList = std::nullopt;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::setQosFlowModifyConfirmList(
    const std::vector<QosFlowModifyConfirmItem> list) {
  m_QosFlowModifyConfirmList.set(list);
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::setQosFlowModifyConfirmList(
    const QosFlowModifyConfirmList& list) {
  m_QosFlowModifyConfirmList = list;
}
//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::getQosFlowModifyConfirmList(
    QosFlowModifyConfirmList& list) const {
  list = m_QosFlowModifyConfirmList;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::setUlNgUUpTnlInformation(
    const UpTransportLayerInformation& ulNgUUpTnlInformation) {
  m_UlNgUUpTnlInformation = ulNgUUpTnlInformation;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::getUlNgUUpTnlInformation(
    UpTransportLayerInformation& ulNgUUpTnlInformation) const {
  ulNgUUpTnlInformation = m_UlNgUUpTnlInformation;
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::setQosFlowFailedToModifyList(
    const QosFlowListWithCause& qosFlowFailedToModifyList) {
  m_QosFlowFailedToModifyList =
      std::make_optional<QosFlowListWithCause>(qosFlowFailedToModifyList);
}

//------------------------------------------------------------------------------
void PduSessionResourceModifyConfirmTransfer::getQosFlowFailedToModifyList(
    std::optional<QosFlowListWithCause>& qosFlowFailedToModifyList) const {
  qosFlowFailedToModifyList = m_QosFlowFailedToModifyList;
}

//------------------------------------------------------------------------------
int PduSessionResourceModifyConfirmTransfer::encode(uint8_t* buf, int bufSize) {
  /* The setters populate the C++ members only.  They have to be transferred
   * into m_Ie here: without this, aper_encode is handed a zeroed SEQUENCE
   * whose two mandatory members are NULL, and it returns -1 -- this encode
   * path could never have produced output.  Every member of
   * Ngap_PDUSessionResourceModifyConfirmTransfer_t is a pointer, so each one
   * is allocated before it is filled. */

  // QoS Flow Modify Confirm List (Mandatory)
  if (!m_Ie->qosFlowModifyConfirmList) {
    m_Ie->qosFlowModifyConfirmList = (Ngap_QosFlowModifyConfirmList_t*) calloc(
        1, sizeof(Ngap_QosFlowModifyConfirmList_t));
    if (!m_Ie->qosFlowModifyConfirmList) {
      oai::logger::logger_common::ngap().error(
          "Allocation of QoS Flow Modify Confirm List IE failed");
      return -1;
    }
  }
  if (!m_QosFlowModifyConfirmList.encode(*m_Ie->qosFlowModifyConfirmList)) {
    oai::logger::logger_common::ngap().error(
        "Encode QoS Flow Modify Confirm List IE failed");
    return -1;
  }

  // UL NG-U UP TNL Information (Mandatory)
  if (!m_Ie->uLNGU_UP_TNLInformation) {
    m_Ie->uLNGU_UP_TNLInformation =
        (Ngap_UPTransportLayerInformation_t*) calloc(
            1, sizeof(Ngap_UPTransportLayerInformation_t));
    if (!m_Ie->uLNGU_UP_TNLInformation) {
      oai::logger::logger_common::ngap().error(
          "Allocation of UL NG-U UP TNL Information IE failed");
      return -1;
    }
  }
  if (!m_UlNgUUpTnlInformation.encode(*m_Ie->uLNGU_UP_TNLInformation)) {
    oai::logger::logger_common::ngap().error(
        "Encode UL NG-U UP TNL Information IE failed");
    return -1;
  }

  // QoS Flow Failed to Modify List (Optional)
  if (m_QosFlowFailedToModifyList.has_value()) {
    if (!m_Ie->qosFlowFailedToModifyList) {
      m_Ie->qosFlowFailedToModifyList = (Ngap_QosFlowListWithCause_t*) calloc(
          1, sizeof(Ngap_QosFlowListWithCause_t));
      if (!m_Ie->qosFlowFailedToModifyList) {
        oai::logger::logger_common::ngap().error(
            "Allocation of QoS Flow Failed to Modify List IE failed");
        return -1;
      }
    }
    if (!m_QosFlowFailedToModifyList.value().encode(
            *m_Ie->qosFlowFailedToModifyList)) {
      oai::logger::logger_common::ngap().error(
          "Encode QoS Flow Failed to Modify List IE failed");
      return -1;
    }
  }

  ngap_utils::print_asn_msg(
      &asn_DEF_Ngap_PDUSessionResourceModifyConfirmTransfer, m_Ie);
  asn_enc_rval_t er = aper_encode_to_buffer(
      &asn_DEF_Ngap_PDUSessionResourceModifyConfirmTransfer, NULL, m_Ie, buf,
      bufSize);
  oai::logger::logger_common::ngap().debug("er.encoded( %d)", er.encoded);
  // asn_fprint(stderr, er.failed_type, er.structure_ptr);
  return er.encoded;
}

//------------------------------------------------------------------------------
bool PduSessionResourceModifyConfirmTransfer::decode(
    uint8_t* buf, int bufSize) {
  asn_dec_rval_t rc = asn_decode(
      NULL, ATS_ALIGNED_CANONICAL_PER,
      &asn_DEF_Ngap_PDUSessionResourceModifyConfirmTransfer, (void**) &m_Ie,
      buf, bufSize);
  if (rc.code == RC_OK) {
    oai::logger::logger_common::ngap().debug("Decoded successfully");
  } else if (rc.code == RC_WMORE) {
    oai::logger::logger_common::ngap().debug("More data expected, call again");
    return false;
  } else {
    oai::logger::logger_common::ngap().debug("Failure to decode data");
    return false;
  }

  // asn_fprint(stderr, &asn_DEF_Ngap_PDUSessionResourceModifyConfirmTransfer,
  // m_Ie);

  // Decode QoS Flow Modify Confirm List
  if (!m_Ie->qosFlowModifyConfirmList) return false;
  if (!m_QosFlowModifyConfirmList.decode(*m_Ie->qosFlowModifyConfirmList)) {
    oai::logger::logger_common::ngap().error(
        "Failure to decode QoS Flow Modify Confirm List IE");
    return false;
  }

  // Decode UL NG-U UP TNL Information
  UpTransportLayerInformation ulNgUUpTnlInformation = {};
  if (!m_Ie->uLNGU_UP_TNLInformation) return false;
  if (!m_UlNgUUpTnlInformation.decode(*m_Ie->uLNGU_UP_TNLInformation)) {
    oai::logger::logger_common::ngap().error(
        "Failure to decode UL NG-U UP TNL Information IE");
    return false;
  }

  // Decode QoS Flow Failed Modify List
  if (m_Ie->qosFlowFailedToModifyList) {
    QosFlowListWithCause qosFlowFailedToModifyList = {};
    if (!qosFlowFailedToModifyList.decode(*m_Ie->qosFlowFailedToModifyList)) {
      oai::logger::logger_common::ngap().error(
          "Failure to decode  QoS Flow Failed Modify List IE");
      return false;
    }
    m_QosFlowFailedToModifyList =
        std::make_optional<QosFlowListWithCause>(qosFlowFailedToModifyList);
  }

  return true;
}

}  // namespace oai::ngap
