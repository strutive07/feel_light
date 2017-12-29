package com.wonjuna.feel_light;

/**
 * Created by wonjun on 2017-11-23.
 */
import android.app.Dialog;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.icu.util.Calendar;
import android.os.AsyncTask;
import android.os.Build;
import android.os.SystemClock;
import android.support.annotation.Nullable;
import android.support.annotation.RequiresApi;
import android.support.design.widget.AppBarLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.content.AsyncTaskLoader;
import android.support.v4.content.ContextCompat;
import android.support.v4.view.ViewPager;
import android.os.Bundle;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextClock;
import android.widget.TextView;
import android.graphics.Color;

import com.db.chart.animation.Animation;
import com.db.chart.model.ChartSet;
import com.db.chart.model.LineSet;
import com.db.chart.renderer.AxisRenderer;
import com.db.chart.view.ChartView;
import com.db.chart.view.LineChartView;
import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.net.URISyntaxException;
import java.text.SimpleDateFormat;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

public class mainPage extends Fragment{
    int isFirst = 1;
    MainActivity mainActivity = new MainActivity();
    int timer_isFirst = 1;
    FragmentActivity activity;
    int[] sky = new int[8];
    float[] temperature = new float[8];
    double dust_value;
    String dust_grade;
    int form_hour;
//    int now_weather;
    int[] BIG_DATA_push_cnt = new int[2];
    int now_weather;
    double Big_Data_time_table_arduino = 5000;
    View rootView;
    mainPage mainPage;
    LineChartView lineChartView;
    Paint paint;
    Animation anim;
    float min_temperature, max_temperature;
    TextClock now_time_clcok;
    TextView now_time;
    TextView[] temperature_text = new TextView[8];
    ImageView[] sky_img = new ImageView[8];
    ImageView hourly_sky_img;
    int tmp_form_hour;
    TextView Dust_grade;
    TextView Dust_value;
    TextView now_Temperature_text;
    float now_Temperature;
    int hourly_weather;
    Typeface a_godic_2;
    Typeface a_title_godic_2;
    TextView Divider1_text,Divider2_text;
    RelativeLayout back_ground_color;
    private final String[] mLabels = {
            "4시간뒤", "7시간뒤", "10시간뒤", "13시간뒤", "16시간뒤", "19시간뒤",  "22시간뒤","25시간뒤",
    };
    LineSet dataset;
    private Socket mSocket;
    {
        try {
            mSocket = IO.socket("http://52.79.41.31:3000/");
            mSocket.connect();
        } catch (URISyntaxException e) {
        }
    }

    @Override
    public void onStop() {
        super.onStop();
//        lineChartView.dismiss(anim);
        Log.d("mSocket", "onStop");
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        Log.d("mSocket", "onAttach");
    }

    @Override
    public void onPause() {
        super.onPause();
        Log.d("mSocket", "onPause");
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        Log.d("mSocket", "onDestroyView");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.d("mSocket", "onDestroy");
    }


    @Override
    public void onDetach() {
        super.onDetach();
        Log.d("mSocket", "onDetach");
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d("mSocket", "onCreate");
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        Log.d("mSocket", "onActivityCreated");
//        lineChartView.show(anim);
    }

    public void push_timer(int timer_isFirst_method1){
        final int timer_isFirst_method = timer_isFirst_method1;
        if(timer_isFirst_method == 1){
            Log.d("mSocket", "BIG_DATA_push_cnt[0] : " + BIG_DATA_push_cnt[0] + "BIG_DATA_push_cnt[1] : " + BIG_DATA_push_cnt[1]);
            final Timer timer = new Timer();
            for(int i=0; i<2; i++){
                if(BIG_DATA_push_cnt[i]%2 == 1){
                    BIG_DATA_push_cnt[i] = (BIG_DATA_push_cnt[i]-1)/2;
                }else{
                    BIG_DATA_push_cnt[i] = (BIG_DATA_push_cnt[i])/2;
                }
            }
            TimerTask timerTask = new TimerTask() {


                @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
                @Override
                public void run() {

                    Date now_Clock = new Date();
                    int now_BIG_Hours = now_Clock.getHours();

//                    background_timer backgroundTimer = new background_timer();
//                    backgroundTimer.bg_thread();
                    Log.d("mSocket", "now_BIG_Hours : " + now_BIG_Hours + "BIG_DATA_push_cnt[0] : " + BIG_DATA_push_cnt[0] + "BIG_DATA_push_cnt[1] : " + BIG_DATA_push_cnt[1]);
                    if(now_BIG_Hours == BIG_DATA_push_cnt[0] || now_BIG_Hours == BIG_DATA_push_cnt[1]){
                        NotificationManager notificationManager;
                        if(getActivity() != null){
                            notificationManager = (NotificationManager) getActivity().getSystemService(getActivity().getApplicationContext().NOTIFICATION_SERVICE);
                            Notification notification;
                            if(now_weather == 8){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 맑음, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 7){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 흐림, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 6){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 한파, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 5){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 폭염, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 4){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 천둥, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 3){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 눈, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 2){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 눈 + 천둥, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 1){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 비, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else if(now_weather == 0){
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 비 + 천둥, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }else{
                                notification = new Notification.Builder(getActivity().getApplicationContext())
                                        .setContentTitle("Feel Light")
                                        .setContentText(now_BIG_Hours + "시 날씨 : 맑음, 기온 :" + now_Temperature + "°C")
                                        .setSmallIcon(R.drawable.icon)
                                        .setTicker(now_BIG_Hours+"시 날씨 도착!")
                                        .build();
                            }
                            Log.d("mSocket", "notifi");
                            notificationManager.notify(1, notification);
//                        mainActivity.noti(now_Temperature,hourly_weather,now_BIG_Hours);
                            timer.cancel();
                        }


                    }
                }
            };

            timer.schedule(timerTask, 1000, 10000);
            timer_isFirst = 0;
        }
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        rootView = inflater.inflate(R.layout.fragment_main, container, false);

        {
            try {
                mSocket = IO.socket("http://52.79.41.31:3000/");
            } catch (URISyntaxException e) {
            }
        }


        activity = getActivity();
        Date now_Clock = new Date();
        back_ground_color = (RelativeLayout) rootView.findViewById(R.id.back_ground_color);
        now_time = (TextView)  rootView.findViewById(R.id.now_time);
        now_time_clcok = (TextClock) rootView.findViewById(R.id.textClock3);
        SimpleDateFormat year_month_day = new SimpleDateFormat("yyyy년 MM월 dd일");
        now_time.setText(year_month_day.format(now_Clock).toString());




        temperature_text[0] = (TextView) rootView.findViewById(R.id.temperature_01);
        temperature_text[1] = (TextView) rootView.findViewById(R.id.temperature_02);
        temperature_text[2] = (TextView) rootView.findViewById(R.id.temperature_03);
        temperature_text[3] = (TextView) rootView.findViewById(R.id.temperature_04);
        temperature_text[4] = (TextView) rootView.findViewById(R.id.temperature_05);
        temperature_text[5] = (TextView) rootView.findViewById(R.id.temperature_06);
        temperature_text[6] = (TextView) rootView.findViewById(R.id.temperature_07);
        temperature_text[7] = (TextView) rootView.findViewById(R.id.temperature_08);
        sky_img[0] = (ImageView) rootView.findViewById(R.id.temperature_img_01);
        sky_img[1] = (ImageView) rootView.findViewById(R.id.temperature_img_02);
        sky_img[2] = (ImageView) rootView.findViewById(R.id.temperature_img_03);
        sky_img[3] = (ImageView) rootView.findViewById(R.id.temperature_img_04);
        sky_img[4] = (ImageView) rootView.findViewById(R.id.temperature_img_05);
        sky_img[5] = (ImageView) rootView.findViewById(R.id.temperature_img_06);
        sky_img[6] = (ImageView) rootView.findViewById(R.id.temperature_img_07);
        sky_img[7] = (ImageView) rootView.findViewById(R.id.temperature_img_08);
        hourly_sky_img = (ImageView) rootView.findViewById(R.id.now_weather_img) ;
        Dust_value = (TextView) rootView.findViewById(R.id.Dust_Value);
        Dust_grade = (TextView) rootView.findViewById(R.id.Dust_grade);
        now_Temperature_text = (TextView) rootView.findViewById(R.id.now_temperature);
        Divider1_text = (TextView) rootView.findViewById(R.id.Divider1_text);
        Divider2_text = (TextView) rootView.findViewById(R.id.Divider2_text);
        a_godic_2 = Typeface.createFromAsset(activity.getAssets(), "fonts/a_godic_2.ttf");
        a_title_godic_2 = Typeface.createFromAsset(activity.getAssets(), "fonts/a_title_godic_2.ttf");
        now_Temperature_text.setTypeface(a_godic_2);
        now_time.setTypeface(a_godic_2);
        now_time_clcok.setTypeface(a_godic_2);
        Dust_value.setTypeface(a_godic_2);
        Dust_grade.setTypeface(a_godic_2);
        Divider1_text.setTypeface(a_title_godic_2);
        Divider2_text.setTypeface(a_title_godic_2);

        Log.d("mSocket", String.valueOf(mSocket));
        mSocket.emit("android_weather_toServer");
        mSocket.on("android_weather_toPhone", listen_done_request_report);
        mSocket.connect();
        lineChartView = (LineChartView) rootView.findViewById(R.id.mChartLine);
        lineChartView.setYAxis(false);
        lineChartView.setYLabels(AxisRenderer.LabelPosition.NONE);
        lineChartView.setXAxis(true);
        lineChartView.setAxisColor(getResources().getColor(R.color.fbutton_color_belize_hole));
        lineChartView.setStep(1);
        lineChartView.setAxisThickness(5).setLabelsColor(getResources().getColor(R.color.fbutton_color_concrete));
        lineChartView.setAxisBorderValues(-5, 5);
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("HH");
        tmp_form_hour = Integer.parseInt(sdf.format(date).toString());
        if(tmp_form_hour == 0){
            tmp_form_hour = tmp_form_hour - 1;
        }else if(tmp_form_hour == 1){
            tmp_form_hour = tmp_form_hour - 2;
        }else{
            if((tmp_form_hour - 2)%3 == 0){
                tmp_form_hour = tmp_form_hour;
            }else if((tmp_form_hour - 2)%3 == 1){
                tmp_form_hour = tmp_form_hour - 1;
            }else{
                tmp_form_hour = tmp_form_hour - 2;
            }
        }
        for(int i=0; i<8; i++){
            int tmp_real_time;
            tmp_real_time = tmp_form_hour + 4 + 3*i;
            if(tmp_real_time >= 24){
                tmp_real_time = tmp_real_time - 24;
            }
            mLabels[i] = tmp_real_time + " 시";
        }
        dataset = new LineSet(mLabels, temperature);
        dataset.setColor(Color.parseColor("#FFFFFF"))
                .setDotsColor(Color.parseColor("#537ABB"))
                .setThickness(10)
                .beginAt(0);

        lineChartView.addData(dataset);
        return rootView;
    }
    private Emitter.Listener listen_done_request_report = new Emitter.Listener() {
        @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
        @Override
        public void call(Object... args) {
            JSONObject received_JSON = (JSONObject) args[0];
            Log.d("mSocket", String.valueOf(received_JSON));
            try {
                sky[0] = received_JSON.getInt("sky0");
                sky[1] = received_JSON.getInt("sky1");
                sky[2] = received_JSON.getInt("sky2");
                sky[3] = received_JSON.getInt("sky3");
                sky[4] = received_JSON.getInt("sky4");
                sky[5] = received_JSON.getInt("sky5");
                sky[6] = received_JSON.getInt("sky6");
                sky[7] = received_JSON.getInt("sky7");
                temperature[0] = (float)received_JSON.getDouble("temperature0");
                temperature[1] = (float)received_JSON.getDouble("temperature1");
                temperature[2] = (float)received_JSON.getDouble("temperature2");
                temperature[3] = (float)received_JSON.getDouble("temperature3");
                temperature[4] = (float)received_JSON.getDouble("temperature4");
                temperature[5] = (float)received_JSON.getDouble("temperature5");
                temperature[6] = (float)received_JSON.getDouble("temperature6");
                temperature[7] = (float)received_JSON.getDouble("temperature7");
                dust_value = received_JSON.getDouble("dust_value");
                dust_grade = received_JSON.getString("dust_grade");
                form_hour = received_JSON.getInt("form_hour");
                now_weather = received_JSON.getInt("now_weather");
                BIG_DATA_push_cnt[0] = received_JSON.getInt("BIg_Date_time_table_android_max_one");
                BIG_DATA_push_cnt[1] = received_JSON.getInt("BIg_Date_time_table_android_max_two");
                Big_Data_time_table_arduino = received_JSON.getDouble("Big_Data_time_table_arduino");
                Log.d("mSocket", "BIG_DATA_push_cnt[0] : " + BIG_DATA_push_cnt[0] + "BIG_DATA_push_cnt[1] : " + BIG_DATA_push_cnt[1]);


                push_timer(timer_isFirst);
                min_temperature = temperature[0];
                max_temperature = temperature[0];
                now_Temperature = (float)received_JSON.getDouble("hourly_temperature");
                hourly_weather = received_JSON.getInt("hourly_weather");
                for(int i=0; i<8; i++){
                    if(min_temperature > temperature[i]){
                        min_temperature = temperature[i];
                    }
                    if(max_temperature < temperature[i]){
                        max_temperature = temperature[i];
                    }
                }
                while(activity == null){

                }
                if(isAdded() && activity != null){
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            Log.d("mSocket", "IN Threads");

                            activity.runOnUiThread(new Runnable() {
                                @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
                                @Override
                                public void run() {
                                    anim = new Animation(1000);
                                    lineChartView.setAxisBorderValues(min_temperature -5, max_temperature + 5);
                                    lineChartView.show(anim);
                                    lineChartView.updateValues(0, temperature);
                                    for(int j = 0; j<8; j++){
                                        temperature_text[j].setText(temperature[j] + "°");
                                    }
                                    for(int j=0; j<8; j++){
                                        int tmp_real_time = tmp_form_hour + 4 + 3*j;
                                        if(tmp_real_time >= 24){
                                            tmp_real_time = tmp_real_time - 24;
                                        }
                                        switch (sky[j]){
                                            case 8 :
                                                if(tmp_real_time >= 18 || tmp_real_time <= 6){
                                                    sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.moon));
                                                }else{
                                                    sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.sun));
                                                }
                                                break;
                                            case 7 :
                                                if(tmp_real_time >= 18 || tmp_real_time <= 6){
                                                    sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.moon_cloud));
                                                }else{
                                                    sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.sun_cloud));
                                                }
                                                break;
                                            case 6 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.verycold));
                                                break;
                                            case 5 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.veryhot));
                                                break;
                                            case 4 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.thunder));
                                                break;
                                            case 3 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.snow));
                                                break;
                                            case 2 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.thunder_snow));
                                                break;
                                            case 1 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.rain));
                                                break;
                                            case 0 :
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.thunder_rain));
                                                break;
                                            default:
                                                sky_img[j].setImageDrawable(getResources().getDrawable(R.drawable.sun));
                                                break;
                                        }
                                    }
                                    Dust_value.setText(dust_value + "㎍/㎥");
                                    now_Temperature_text.setText(now_Temperature + "°C");
                                    Dust_grade.setText(dust_grade);
                                    Date hourly_date = new Date();
                                    SimpleDateFormat hourly_sdf = new SimpleDateFormat("HH");
                                    int hourly_tmp_form_hour = Integer.parseInt(hourly_sdf.format(hourly_date).toString());
                                    java.util.Calendar cal = java.util.Calendar.getInstance();
                                    int cal_hour = cal.get(java.util.Calendar.HOUR_OF_DAY);
                                    AppBarLayout appBarLayout;
                                    appBarLayout = (AppBarLayout) getActivity().findViewById(R.id.appbar);
                                    Window window = getActivity().getWindow();


                                    RelativeLayout back_ground_color_button_page = (RelativeLayout) getActivity().findViewById(R.id.back_ground_color_button_page);
                                    Bundle bundle = new Bundle();
                                    bundle.putInt("hourly_weather",hourly_weather);
                                    bundle.putInt("cal_hour",cal_hour);
                                    bundle.putDouble("Big_Data_time_table_arduino",Big_Data_time_table_arduino);
                                    Fragment f = new sentiment();
                                    f.setArguments(bundle);
                                    Fragment fg = new buttonPage();
                                    fg.setArguments(bundle);
                                    if(cal_hour >= 18 || cal_hour <= 6){
                                        back_ground_color.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Night));
                                        appBarLayout.setBackgroundColor(getResources().getColor(R.color.Tool_Bar_Color_Night));
                                        window.setStatusBarColor(ContextCompat.getColor(getActivity(), R.color.statusBar_color));
                                        back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Night));



                                    }else if(hourly_weather == 8 || hourly_weather == 6 || hourly_weather == 5){
                                        back_ground_color.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Sunny));
                                        appBarLayout.setBackgroundColor(getResources().getColor(R.color.Tool_Bar_Color_Day_Sunny));
                                        window.setStatusBarColor(ContextCompat.getColor(getActivity(), R.color.statusBar_color));
                                        back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Sunny));

                                    }else{
                                        back_ground_color.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Cloud));
                                        appBarLayout.setBackgroundColor(getResources().getColor(R.color.Tool_Bar_Color_Day_Cloud));
                                        window.setStatusBarColor(ContextCompat.getColor(getActivity(), R.color.statusBar_color));
                                        back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Cloud));

                                    }

                                    switch (hourly_weather){
                                        case 8 :
                                            if(hourly_tmp_form_hour >= 18 || hourly_tmp_form_hour <= 6){
                                                hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.moon));
                                            }else{
                                                hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.sun));
                                            }
                                            break;
                                        case 7 :
                                            if(hourly_tmp_form_hour >= 18 || hourly_tmp_form_hour <= 6){
                                                hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.moon_cloud));
                                            }else{
                                                hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.sun_cloud));
                                            }
                                            break;
                                        case 6 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.verycold));
                                            break;
                                        case 5 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.veryhot));
                                            break;
                                        case 4 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.thunder));
                                            break;
                                        case 3 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.snow));
                                            break;
                                        case 2 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.thunder_snow));
                                            break;
                                        case 1 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.rain));
                                            break;
                                        case 0 :
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.thunder_rain));
                                            break;
                                        default:
                                            hourly_sky_img.setImageDrawable(getResources().getDrawable(R.drawable.sun));
                                            break;
                                    }
                                }
                            });
                        }
                    }).start();
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }

        }
    };


    public class weather_chart extends ChartView{


        public weather_chart(Context context, AttributeSet attrs) {
            super(context, attrs);
        }

        public weather_chart(Context context) {
            super(context);
        }

        @Override
        protected void onDrawChart(Canvas canvas, ArrayList<ChartSet> data) {

        }

    }
}
