// Copyright 2021 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GRPC_CORE_EXT_TRANSPORT_BINDER_CLIENT_JNI_UTILS_H
#define GRPC_CORE_EXT_TRANSPORT_BINDER_CLIENT_JNI_UTILS_H

#if defined(ANDROID) || defined(__ANDROID__)

#include <grpc/support/port_platform.h>

#error #include <jni.h>

#include <functional>
#include <util/generic/string.h>
#include <util/string/cast.h>

#include "y_absl/strings/string_view.h"

namespace grpc_binder {

// Finds NativeConnectionHelper Java class and caches it. This is useful because
// FindClass only works when there is a Java class in the call stack. Typically
// user might want to call this once in a place that is called from Java (ex.
// JNI_OnLoad) so subsequent BinderTransport code can find Java class
jclass FindNativeConnectionHelper(JNIEnv* env);

jclass FindNativeConnectionHelper(
    JNIEnv* env, std::function<void*(TString)> class_finder);

// Calls Java method NativeConnectionHelper.tryEstablishConnection
void TryEstablishConnection(JNIEnv* env, jobject application,
                            y_absl::string_view pkg, y_absl::string_view cls,
                            y_absl::string_view conn_id);

}  // namespace grpc_binder

#endif

#endif  // GRPC_CORE_EXT_TRANSPORT_BINDER_CLIENT_JNI_UTILS_H
