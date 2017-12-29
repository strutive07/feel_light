package com.wonjuna.feel_light;

import android.os.Build;
import android.support.annotation.RequiresApi;

import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by wonjun on 2017-12-21.
 */

public class background_timer {
    public void bg_thread(int cnt_time11, int cnt_time22){
        final int cnt_time1 = cnt_time11;
        final int cnt_time2 = cnt_time22;
        TimerTask timerTask = new TimerTask() {
            @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
            @Override
            public void run() {
                Date now_Clock = new Date();
                int now_BIG_Hours = now_Clock.getHours();
                if(now_BIG_Hours == cnt_time1 || now_BIG_Hours == cnt_time2){
                    //gogo
                }
            }
        };
        Timer timer = new Timer();
        timer.schedule(timerTask, 1000, 1000);
    }
}
