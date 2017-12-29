package com.wonjuna.feel_light;

/**
 * Created by wonjun on 2017-11-23.
 */

import android.app.ProgressDialog;
import android.graphics.PorterDuff;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.URISyntaxException;

import info.hoang8f.widget.FButton;
import yuku.ambilwarna.AmbilWarnaDialog;

public class sentiment extends Fragment{
    EditText editText;
    FButton sendButton;
    RelativeLayout back_ground_color_button_page;
    ImageView img_icon;
    ImageView img_text;
    TextView reple_text_box;
    double comparative = 0.0;
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
        View rootView = inflater.inflate(R.layout.fragment_sentiment, container, false);
        {
            try {
                mSocket = IO.socket("http://52.79.41.31:3000/");
            } catch (URISyntaxException e) {
            }
        }
        editText = rootView.findViewById(R.id.editText);
        sendButton = rootView.findViewById(R.id.send_Button);
        editText.getBackground().setColorFilter(getResources().getColor(R.color.fbutton_color_concrete), PorterDuff.Mode.SRC_IN);
        img_icon = rootView.findViewById(R.id.img_icon);
        img_text = rootView.findViewById(R.id.img_text);
        reple_text_box = rootView.findViewById(R.id.reple_text_box);
        reple_text_box.setTextColor(getResources().getColor(R.color.fbutton_color_concrete));
        sendButton.setOnClickListener(new View.OnClickListener() {


            @Override
            public void onClick(View view) {
                String send_msg = editText.getText().toString();
                JSONObject jsonObject = new JSONObject();
                try {
                    jsonObject.put("send_msg", send_msg);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                mSocket.emit("sentiment_send_to_server", jsonObject);
            }
        });
        back_ground_color_button_page = (RelativeLayout)rootView.findViewById(R.id.back_ground_color_sentiment);
        mSocket.emit("color_init");
        mSocket.on("sentiment_send_to_android", listen_done_request_color);
        Bundle bundle = getArguments();
        int cal_hour = 0;
        int hourly_weather = 0;
        if(bundle != null){
            cal_hour = bundle.getInt("cal_hour");
            hourly_weather = bundle.getInt("hourly_weather");
            Log.d("mSocket", "cal_hour" + cal_hour);
            Log.d("mSocket", "hourly_weather" + hourly_weather);
            if(cal_hour >= 18 || cal_hour <= 6){
                back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Night));
            }else if(hourly_weather == 8 || hourly_weather == 6 || hourly_weather == 5){
                back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Sunny));
            }else{
                back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Cloud));
            }
        }
        back_ground_color_button_page.setBackgroundColor(getResources().getColor(R.color.BackGround_Color_Day_Sunny));

        return rootView;
    }
    private class CheckTypesTask extends AsyncTask<Void, Void, Void> {

        @Override
        protected void onPreExecute() {
//            asyncDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
//            asyncDialog.setMessage("로딩중입니다..");
//
//            // show dialog
//            asyncDialog.show();
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
//            asyncDialog.dismiss();
            super.onPostExecute(result);
        }
    }

    private Emitter.Listener listen_done_request_color = new Emitter.Listener() {
        @Override
        public void call(Object... args) {
            JSONObject received_JSON = (JSONObject) args[0];
            Log.d("mSocket", String.valueOf(received_JSON));
            try {
                comparative = received_JSON.getDouble("comparative");

            } catch (JSONException e) {
                e.printStackTrace();
            }

            if(isAdded() && getActivity() != null){

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        getActivity().runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                if(comparative <= -1.0){
                                    //분노
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.angry));
                                    reple_text_box.setText("세상이 불타고 있어요!");
                                }else if(comparative >= -0.7 &&  comparative < -0.3){
                                    //슬픔
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.sad));
                                    reple_text_box.setText("주륵 주륵 장대비가 쏟아져요.");
                                }else if(comparative >=-0.3  &&  comparative < 0){
                                    //우울
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.depressed));
                                    reple_text_box.setText("부슬 부슬 가랑비가 내려요.");
                                }else if(comparative >=0  &&  comparative <= 0.24){
                                    //조금 우울
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.little_depressed));
                                    reple_text_box.setText("구름이 잔뜩 끼었어요.");
                                }else if(comparative >=0.24  &&  comparative < 0.6){
                                    //찡찡댐
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.merong));
                                    reple_text_box.setText("바람이 살랑 살랑 불어요.");
                                }else if(comparative >=0.6  &&  comparative < 1.0){
                                    //기쁨
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.happy));
                                    reple_text_box.setText("하늘이 참 푸르고 맑아요.");
                                }else if(comparative >1.0){
                                    //환희
                                    img_text.setImageDrawable(getResources().getDrawable(R.drawable.veryhappy));
                                    reple_text_box.setText(" 구름이 두둥실, 내 마음도 두둥실.");
                                }
                            }
                        });

                    }
                }).start();

            }
        }
    };

}
