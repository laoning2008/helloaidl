#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/example/helloaidl/ICallbackInterface.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace example {
namespace helloaidl {
class IHelloInterface : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HelloInterface)
  virtual ::android::binder::Status registerListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& listener) = 0;
  virtual ::android::binder::Status unregisterListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& listener) = 0;
  virtual ::android::binder::Status sayHello(const ::android::String16& name, ::android::String16* _aidl_return) = 0;
};  // class IHelloInterface

class IHelloInterfaceDefault : public IHelloInterface {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status sayHello(const ::android::String16& /*name*/, ::android::String16* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class IHelloInterfaceDefault
}  // namespace helloaidl
}  // namespace example
}  // namespace com
