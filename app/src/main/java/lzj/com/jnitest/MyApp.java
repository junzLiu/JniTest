package lzj.com.jnitest;

import android.app.Application;

/**
 * Created by Mark on 2017/6/19.
 */

public class MyApp extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        ContextHolder.setContext(this);
    }
}
