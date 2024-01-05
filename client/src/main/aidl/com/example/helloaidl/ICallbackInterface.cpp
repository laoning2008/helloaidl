#include <com/example/helloaidl/ICallbackInterface.h>
#include <com/example/helloaidl/BpCallbackInterface.h>
namespace com {
namespace example {
namespace helloaidl {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(CallbackInterface, "com.example.helloaidl.ICallbackInterface")
}  // namespace helloaidl
}  // namespace example
}  // namespace com
#include <com/example/helloaidl/BpCallbackInterface.h>
#include <com/example/helloaidl/BnCallbackInterface.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace example {
namespace helloaidl {

BpCallbackInterface::BpCallbackInterface(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<ICallbackInterface>(_aidl_impl){
}

::android::binder::Status BpCallbackInterface::fromService(const ::android::String16& aString) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeString16(aString);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCallbackInterface::TRANSACTION_fromService, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICallbackInterface::getDefaultImpl())) {
     return ICallbackInterface::getDefaultImpl()->fromService(aString);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_status.readFromParcel(_aidl_reply);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  if (!_aidl_status.isOk()) {
    return _aidl_status;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

}  // namespace helloaidl
}  // namespace example
}  // namespace com
#include <com/example/helloaidl/BnCallbackInterface.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace example {
namespace helloaidl {

BnCallbackInterface::BnCallbackInterface()
{
  ::android::internal::Stability::markCompilationUnit(this);
}

::android::status_t BnCallbackInterface::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnCallbackInterface::TRANSACTION_fromService:
  {
    ::android::String16 in_aString;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readString16(&in_aString);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    ::android::binder::Status _aidl_status(fromService(in_aString));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  default:
  {
    _aidl_ret_status = ::android::BBinder::onTransact(_aidl_code, _aidl_data, _aidl_reply, _aidl_flags);
  }
  break;
  }
  if (_aidl_ret_status == ::android::UNEXPECTED_NULL) {
    _aidl_ret_status = ::android::binder::Status::fromExceptionCode(::android::binder::Status::EX_NULL_POINTER).writeOverParcel(_aidl_reply);
  }
  return _aidl_ret_status;
}

}  // namespace helloaidl
}  // namespace example
}  // namespace com
