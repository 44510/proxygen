/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "proxygen/lib/http/observer/HTTPSessionObserverInterface.h"
#include <cstdint>
#include <sys/types.h>

namespace proxygen {

HTTPSessionObserverInterface::RequestStartedEvent::Builder&&
HTTPSessionObserverInterface::RequestStartedEvent::Builder::setHeaders(
    const proxygen::HTTPHeaders& headersIn) {
  maybeHTTPHeadersRef = headersIn;
  return std::move(*this);
}

HTTPSessionObserverInterface::RequestStartedEvent
HTTPSessionObserverInterface::RequestStartedEvent::Builder::build() && {
  return RequestStartedEvent(*this);
}

HTTPSessionObserverInterface::RequestStartedEvent::RequestStartedEvent(
    const RequestStartedEvent::BuilderFields& builderFields)
    : requestHeaders(
          *CHECK_NOTNULL(builderFields.maybeHTTPHeadersRef.get_pointer())) {
}

HTTPSessionObserverInterface::PreWriteEvent::Builder&&
HTTPSessionObserverInterface::PreWriteEvent::Builder::setPendingEgressBytes(
    const uint64_t& pendingEgressBytesIn) {
  maybePendingEgressBytesRef = pendingEgressBytesIn;
  return std::move(*this);
}

HTTPSessionObserverInterface::PreWriteEvent::Builder&&
HTTPSessionObserverInterface::PreWriteEvent::Builder::setTimestamp(
    const TimePoint& timestampIn) {
  maybeTimestampRef = timestampIn;
  return std::move(*this);
}

HTTPSessionObserverInterface::PreWriteEvent
HTTPSessionObserverInterface::PreWriteEvent::Builder::build() && {
  return PreWriteEvent(*this);
}

HTTPSessionObserverInterface::PreWriteEvent::PreWriteEvent(
    PreWriteEvent::BuilderFields& builderFields)
    : pendingEgressBytes(*CHECK_NOTNULL(
          builderFields.maybePendingEgressBytesRef.get_pointer())) {
}

} // namespace proxygen
