package com.example.helloaidl;
import com.example.helloaidl.ICallbackInterface;

interface IHelloInterface {
    void registerListener(ICallbackInterface listener);
    void unregisterListener(ICallbackInterface listener);

    String sayHello(String name);
}