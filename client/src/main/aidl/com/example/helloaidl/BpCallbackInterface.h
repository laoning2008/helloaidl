#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/example/helloaidl/ICallbackInterface.h>

namespace com {
namespace example {
namespace helloaidl {
class BpCallbackInterface : public ::android::BpInterface<ICallbackInterface> {
public:
  explicit BpCallbackInterface(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCallbackInterface() = default;
  ::android::binder::Status fromService(const ::android::String16& aString) override;
};  // class BpCallbackInterface
}  // namespace helloaidl
}  // namespace example
}  // namespace com
