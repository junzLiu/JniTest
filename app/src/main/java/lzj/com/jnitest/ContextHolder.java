package lzj.com.jnitest;

import android.content.Context;

/**
 * Created by Mark on 2017/6/19.
 */

public class ContextHolder {

        private static Context sContext;

        public static void setContext(Context context) {
            ContextHolder.sContext = context;
        }

        public static Context getContext() {
            return sContext;
        }
}
