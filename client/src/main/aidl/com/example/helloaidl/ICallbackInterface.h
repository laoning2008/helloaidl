#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace example {
namespace helloaidl {
class ICallbackInterface : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CallbackInterface)
  virtual ::android::binder::Status fromService(const ::android::String16& aString) = 0;
};  // class ICallbackInterface

class ICallbackInterfaceDefault : public ICallbackInterface {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status fromService(const ::android::String16& /*aString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class ICallbackInterfaceDefault
}  // namespace helloaidl
}  // namespace example
}  // namespace com
