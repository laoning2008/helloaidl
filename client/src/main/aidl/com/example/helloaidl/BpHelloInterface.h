#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/example/helloaidl/IHelloInterface.h>

namespace com {
namespace example {
namespace helloaidl {
class BpHelloInterface : public ::android::BpInterface<IHelloInterface> {
public:
  explicit BpHelloInterface(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHelloInterface() = default;
  ::android::binder::Status registerListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& listener) override;
  ::android::binder::Status unregisterListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& listener) override;
  ::android::binder::Status sayHello(const ::android::String16& name, ::android::String16* _aidl_return) override;
};  // class BpHelloInterface
}  // namespace helloaidl
}  // namespace example
}  // namespace com
