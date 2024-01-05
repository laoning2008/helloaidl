#pragma once

#include <binder/IInterface.h>
#include <com/example/helloaidl/IHelloInterface.h>

namespace com {
namespace example {
namespace helloaidl {
class BnHelloInterface : public ::android::BnInterface<IHelloInterface> {
public:
  static constexpr uint32_t TRANSACTION_registerListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_unregisterListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_sayHello = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  explicit BnHelloInterface();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnHelloInterface

class IHelloInterfaceDelegator : public BnHelloInterface {
public:
  explicit IHelloInterfaceDelegator(::android::sp<IHelloInterface> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status registerListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& listener) override {
    return _aidl_delegate->registerListener(listener);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::example::helloaidl::ICallbackInterface>& listener) override {
    return _aidl_delegate->unregisterListener(listener);
  }
  ::android::binder::Status sayHello(const ::android::String16& name, ::android::String16* _aidl_return) override {
    return _aidl_delegate->sayHello(name, _aidl_return);
  }
private:
  ::android::sp<IHelloInterface> _aidl_delegate;
};  // class IHelloInterfaceDelegator
}  // namespace helloaidl
}  // namespace example
}  // namespace com
