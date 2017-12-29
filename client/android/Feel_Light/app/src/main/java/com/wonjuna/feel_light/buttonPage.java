package com.wonjuna.feel_light;

/**
 * Created by wonjun on 2017-11-23.
 */

import android.app.ProgressDialog;
import android.os.AsyncTask;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.db.chart.animation.Animation;
import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.net.URISyntaxException;
import java.text.SimpleDateFormat;
import java.util.Date;

import info.hoang8f.widget.*;
import yuku.ambilwarna.AmbilWarnaDialog;

public class buttonPage extends Fragment{
    final int[] initialColor = {0};
    info.hoang8f.widget.FButton fButton_on_off;
    info.hoang8f.widget.FButton fButton_mood;
    info.hoang8f.widget.FButton fButton_weather;
    info.hoang8f.widget.FButton fButton_temperature;
    info.hoang8f.widget.FButton fButton_dust;
    TextView now_weather_text_view_inButtonPage;
    double Big_Data_time_table_arduino = 0;
    private Socket mSocket;
    {
        try {
            mSocket = IO.socket("http://52.79.41.31:3000/");
            mSocket.connect();
        } catch (URISyntaxException e) {
        }
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_button_page, container, false);
        {
            try {
                mSocket = IO.socket("http://52.79.41.31:3000/");
            } catch (URISyntaxException e) {
            }
        }
        now_weather_text_view_inButtonPage = (TextView) rootView.findViewById(R.id.now_mode);
        fButton_on_off = (info.hoang8f.widget.FButton) rootView.findViewById(R.id.FButton_on_off);
        fButton_mood = (info.hoang8f.widget.FButton) rootView.findViewById(R.id.FButton_mood);
        mSocket.emit("color_init");
        mSocket.on("color_init_to_arduino", listen_done_request_color);
        Bundle bundle = getArguments();


        if(bundle != null){
            Big_Data_time_table_arduino = bundle.getDouble("Big_Data_time_table_arduino");
        }

        fButton_on_off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Feel Light 끄기", 5000)
                        .setAction("Action", null).show();
                mSocket.emit("off_mood");
                CheckTypesTask task = new CheckTypesTask();
                task.execute();
                now_weather_text_view_inButtonPage.setText("OFF");
            }
        });
        fButton_mood.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "무드등 모드로 변경", 5000)
                        .setAction("Action", null).show();





                AmbilWarnaDialog dialog = new AmbilWarnaDialog(getActivity(), initialColor[0], new AmbilWarnaDialog.OnAmbilWarnaListener() {

                    @Override
                    public void onCancel(AmbilWarnaDialog dialog) {

                    }

                    @Override
                    public void onOk(AmbilWarnaDialog dialog, int color) {
//                        JSONObject tmp_json = new JSONObject();
//                        try {
//                            tmp_json.put("color", color);
//                        } catch (JSONException e) {
//                            e.printStackTrace();
//                        }
                        Log.d("mSocket", Integer.toHexString(color));
                        initialColor[0] = color;
                        fButton_mood.setButtonColor(color);


                        mSocket.emit("mode_change_mood", Integer.toHexString(color));
                        CheckTypesTask task = new CheckTypesTask();
                        task.execute();


                    }
                });
                dialog.show();
                now_weather_text_view_inButtonPage.setText("무드등");
            }
        });
        fButton_weather = (info.hoang8f.widget.FButton) rootView.findViewById(R.id.FButton_weather);
        fButton_weather.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "날씨 모드로 변경", 5000)
                        .setAction("Action", null).show();
                mSocket.emit("mode_change_weather");
                CheckTypesTask task = new CheckTypesTask();
                task.execute();
                now_weather_text_view_inButtonPage.setText("날씨");
            }
        });
        fButton_temperature = (info.hoang8f.widget.FButton) rootView.findViewById(R.id.FButton_temperature);
        fButton_temperature.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "온도 모드로 변경", 5000)
                        .setAction("Action", null).show();
                mSocket.emit("mode_change_temperature");
                CheckTypesTask task = new CheckTypesTask();
                task.execute();
                now_weather_text_view_inButtonPage.setText("온도");
            }
        });
        fButton_dust = (info.hoang8f.widget.FButton) rootView.findViewById(R.id.FButton_dust);
        fButton_dust.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "미세먼지 모드로 변경", 5000)
                        .setAction("Action", null).show();
                mSocket.emit("mode_change_dust");
                CheckTypesTask task = new CheckTypesTask();
                task.execute();
                now_weather_text_view_inButtonPage.setText("미세먼지");
            }
        });

        return rootView;
    }
    private class CheckTypesTask extends AsyncTask<Void, Void, Void> {
        ProgressDialog asyncDialog = new ProgressDialog(getActivity());

        @Override
        protected void onPreExecute() {
            asyncDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
            asyncDialog.setMessage("로딩중입니다..");

            // show dialog
            asyncDialog.show();
            super.onPreExecute();
        }

        @Override
        protected Void doInBackground(Void... arg0) {
            try {
                    //asyncDialog.setProgress(i * 30);
                    Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            asyncDialog.dismiss();
            super.onPostExecute(result);
        }
    }

    private Emitter.Listener listen_done_request_color = new Emitter.Listener() {
        @Override
        public void call(Object... args) {
            JSONObject received_JSON = (JSONObject) args[0];
            Log.d("mSocket", String.valueOf(received_JSON));
            try {
                initialColor[0] = received_JSON.getInt("mood_color");
            } catch (JSONException e) {
                e.printStackTrace();
            }

        }
    };

}
