#pragma once

#include <binder/IInterface.h>
#include <com/example/helloaidl/ICallbackInterface.h>

namespace com {
namespace example {
namespace helloaidl {
class BnCallbackInterface : public ::android::BnInterface<ICallbackInterface> {
public:
  static constexpr uint32_t TRANSACTION_fromService = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  explicit BnCallbackInterface();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnCallbackInterface

class ICallbackInterfaceDelegator : public BnCallbackInterface {
public:
  explicit ICallbackInterfaceDelegator(::android::sp<ICallbackInterface> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status fromService(const ::android::String16& aString) override {
    return _aidl_delegate->fromService(aString);
  }
private:
  ::android::sp<ICallbackInterface> _aidl_delegate;
};  // class ICallbackInterfaceDelegator
}  // namespace helloaidl
}  // namespace example
}  // namespace com
