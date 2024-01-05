package com.example.client;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.example.helloaidl.ICallbackInterface;
import com.example.helloaidl.IHelloInterface;

public class MainActivity extends AppCompatActivity {

    private IHelloInterface helloInterface;

    private Button btnStart;
    private Button btnStop;
    private Button btnBind;
    private Button btnUnbind;
    private Button btnSayHello;
    private Button btnRegister;
    private Button btnUnregister;

    private Handler handler;

    private boolean hasBind = false;

    private ServiceConnection mServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            helloInterface = IHelloInterface.Stub.asInterface(iBinder);
        }

//        Called when a connection to the Service has been lost.
//        This typically happens when the process hosting the service
//        has crashed or been killed. This does not remove
//        the ServiceConnection itself -- this binding to the service will remain active,
//        and you will receive a call to onServiceConnected when the Service is next running.

//        The onServiceDisconnected method is called when the connection to a service is unexpectedly lost,
//        typically due to the service process being killed or crashing.
//        However, if you explicitly call stopService or unbindService,
//        the onServiceDisconnected method may not be invoked,
//        as these are intentional actions on your part.
        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            unbindService();

            //should be careful----need to bind again instantly, need to control bind times?
            bindService();
        }
    };

    private ICallbackInterface.Stub callback = new ICallbackInterface.Stub() {

        @Override
        public void fromService(String aString) throws RemoteException {
            handler.post(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(MainActivity.this, aString, Toast.LENGTH_SHORT).show();
                }
            });
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unbindService();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        handler = new Handler(getMainLooper());

        btnStart = findViewById(R.id.btnStart);
        btnStop = findViewById(R.id.btnStop);
        btnBind = findViewById(R.id.btnBind);
        btnUnbind = findViewById(R.id.btnUnbind);
        btnSayHello = findViewById(R.id.btnSayHello);
        btnRegister = findViewById(R.id.btnRegister);
        btnUnregister = findViewById(R.id.btnUnregister);

        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startService();;
            }
        });

        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopService();
            }
        });

        btnBind.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bindService();
            }
        });

        btnUnbind.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                unbindService();
            }
        });

        btnSayHello.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sayHello();
            }
        });

        btnRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                registerCallback();
            }
        });

        btnUnregister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                unregisterCallback();
            }
        });
    }


    private void startService() {
        Intent intent = new Intent("com.example.helloaidl.IHelloInterface");
        intent.setPackage("com.example.helloaidl");

        ComponentName componentName = null;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            componentName = startForegroundService(intent);
        } else {
            componentName = startService(intent);
        }

        Toast.makeText(MainActivity.this, "start service: " + ((componentName != null) ? "success": "failed"), Toast.LENGTH_SHORT).show();
    }

    private void stopService() {
        //Note that if a stopped service still has ServiceConnection objects bound to it
        //with the BIND_AUTO_CREATE set, it will not be destroyed until all of these bindings are removed.
        unbindService();

        Intent intent = new Intent("com.example.helloaidl.IHelloInterface");
        intent.setPackage("com.example.helloaidl");
        boolean result = stopService(intent);
        Toast.makeText(MainActivity.this, "stop service: " + (result ? "success": "failed"), Toast.LENGTH_SHORT).show();
    }

    private void bindService() {
        if (hasBind) {
            return;
        }

        Intent intent = new Intent("com.example.helloaidl.IHelloInterface");
        intent.setPackage("com.example.helloaidl");
        //Regardless of the return value, you should later call unbindService to release the connection.
//        Note that if a stopped service still has ServiceConnection objects bound to it
//        with the BIND_AUTO_CREATE set, it will not be destroyed until all of these bindings are removed.
        boolean result = bindService(intent, mServiceConnection, BIND_AUTO_CREATE);
        if (result) {
            hasBind = true;
        } else {
            unbindService(mServiceConnection);
        }

        Toast.makeText(MainActivity.this, "bind service: " + (result ? "success": "failed"), Toast.LENGTH_SHORT).show();
    }

    private void unbindService() {
        if (!hasBind) {
            return;
        }

        hasBind = false;

        helloInterface = null;

        //always unbindService
        //Disconnect from an application service. You will no longer receive calls as the service is restarted, and the service is now allowed to stop at any time.
        unbindService(mServiceConnection);
        Toast.makeText(MainActivity.this, "unbind service:", Toast.LENGTH_SHORT).show();
    }

    private void sayHello() {
        if (helloInterface != null) {
            try {
                String text = helloInterface.sayHello("laoning");
                Toast.makeText(MainActivity.this, text, Toast.LENGTH_SHORT).show();
            } catch (RemoteException e) {
                Toast.makeText(MainActivity.this, "sayHello failed: e = " + e.toString(), Toast.LENGTH_SHORT).show();
            }
        } else {
            Toast.makeText(MainActivity.this, "need to bind service first", Toast.LENGTH_SHORT).show();
        }
    }

    private void registerCallback() {
        if (helloInterface != null) {
            try {
                helloInterface.registerListener(callback);
                Toast.makeText(MainActivity.this, "registerCallback success", Toast.LENGTH_SHORT).show();
            } catch (RemoteException e) {
                Toast.makeText(MainActivity.this, "registerCallback failed: e = " + e.toString(), Toast.LENGTH_SHORT).show();
            }
        } else {
            Toast.makeText(MainActivity.this, "need to bind service first", Toast.LENGTH_SHORT).show();
        }
    }

    private void unregisterCallback() {
        if (helloInterface != null) {
            try {
                helloInterface.unregisterListener(callback);
                Toast.makeText(MainActivity.this, "unregisterCallback success", Toast.LENGTH_SHORT).show();
            } catch (RemoteException e) {
                Toast.makeText(MainActivity.this, "unregisterCallback failed: e = " + e.toString(), Toast.LENGTH_SHORT).show();
            }
        } else {
            Toast.makeText(MainActivity.this, "need to bind service first", Toast.LENGTH_SHORT).show();
        }
    }
}