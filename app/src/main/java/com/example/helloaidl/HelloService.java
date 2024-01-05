package com.example.helloaidl;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteCallbackList;
import android.os.RemoteException;

import androidx.core.app.NotificationCompat;

public class HelloService extends Service {
    private RemoteCallbackList<ICallbackInterface> mListenerList = new RemoteCallbackList<>();
    private Handler handler;
    public static final String CHANNEL_ID = "hello_service_channel_id";


    private Runnable runnable = new Runnable() {
        @Override
        public void run() {
            int callbackCount = mListenerList.beginBroadcast();

            for (int i  = 0; i < callbackCount; ++i) {
                try {
                    mListenerList.getBroadcastItem(i).fromService("hello from service");
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }

            mListenerList.finishBroadcast();

            handler.postDelayed(runnable, 3*1000);
        }
    };

    public HelloService() {
    }

    @Override
    public void onCreate() {
        super.onCreate();
        createNotificationChannel();

        startForeground(1, buildForegroundNotification());

        handler = new Handler(getMainLooper());
        handler.postDelayed(runnable, 3*1000);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        return false;
    }

    private void createNotificationChannel() {
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            NotificationChannel serviceChannel = new NotificationChannel(CHANNEL_ID, "Example Service Channel",NotificationManager.IMPORTANCE_DEFAULT);
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(serviceChannel);
        }
    }

    private Notification buildForegroundNotification() {
        Notification.Builder b = new Notification.Builder(this);

        b.setOngoing(true)
                .setContentTitle("hell service")
                .setContentText("hell service")
                .setSmallIcon(android.R.drawable.stat_sys_download)
                .setTicker("hell service");

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            b.setChannelId(CHANNEL_ID);
        }

        return(b.build());
    }


    private IHelloInterface.Stub mBinder = new IHelloInterface.Stub() {
        @Override
        public void registerListener(ICallbackInterface listener) throws RemoteException {
            mListenerList.register(listener);
        }

        @Override
        public void unregisterListener(ICallbackInterface listener) throws RemoteException {
            mListenerList.unregister(listener);
        }

        @Override
        public String sayHello(String name) throws RemoteException {
            return "hello " + name;
        }
    };
}