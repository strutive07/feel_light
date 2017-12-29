var socketio = require('socket.io');
var path = require('path');
var cors = require('cors');
var get_request = require('request');
var socketio_server = {};
var sentiment = require('sentiment');
var sky;
var temperature;
var dust_value;
var dust_grade;
var form_hour;
var now_weather;
var hourly_weather;
var hourly_temperature;
var now_mode = 1;
var mood_color = "FFFFFFFF";
var on_off = 0;
var startDate;
var endDate;
var demo_now_mode = 1;
var demo_mood_color = 0;
var demo_dust_value = 0;
var cnt = 1;
var demo_temperature = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,];
var demo_now_weather = 8;
var now_emotion = 20;
var ai_flag = 0;

//Big Data

var Big_Data_time_tabl_appe = new Array();
for(var i=0; i<50; i++){
    Big_Data_time_tabl_appe[i] = 0;
}
var Big_Data_time_table_arduino = 3;

//Sentiment

var r1 = sentiment('I am sad');
console.log('r1 : ', r1);
{
  for(var i=0; i<3; i++){
    var BIGDATE_HOUR = 14;
    var BIGDATE_MINUTE = i*15;
    if(BIGDATE_MINUTE > 30){
      Big_Data_time_tabl_appe[BIGDATE_HOUR*2+1]++;
    }else{
      Big_Data_time_tabl_appe[BIGDATE_HOUR*2]++;
    }
  }
}







socketio_server.init = function(app, server){
  app.use(cors());
  function get_most_cnt_BIG_DATA(){
    var tmp_max_elem = new Array();
    var max = Big_Data_time_tabl_appe[0];
    var max_index = 0;
    for(var i=0; i<Big_Data_time_tabl_appe.length; i++){
      if(max < Big_Data_time_tabl_appe[i]){
        max_index = i;
      }
    }
    tmp_max_elem[0] = max_index;
    max = Big_Data_time_tabl_appe[0];
    var max_index2=0;
    for(var i=0; i<Big_Data_time_tabl_appe.length; i++){
      if(i != max_index){
        if(max < Big_Data_time_tabl_appe[i]){
          max_index2 = i;
        }
      }
    }
    tmp_max_elem[1] = max_index2;
    return tmp_max_elem;
  }
  function print_BIG_DATA(){
    for(var i=0; i<Big_Data_time_tabl_appe.length; i++){
      console.log('Big_Data_time_tabl_appe['+i+'] : '+ Big_Data_time_tabl_appe[i]);
    }
  }
  function print_data(){
    var r1 = sentiment('I hate cat');
    console.log('r1 : ', r1);
    console.log("form_hour : ", form_hour);
    console.log("sky : ", sky);
    console.log("now_weather : ", now_weather);
    console.log("temperature : ", temperature);
    console.log("dust_value : ", dust_value);
    console.log("dust_grade : ", dust_grade);
  }
  console.log('cors 모듈 사용 완료');
  var weather_api_info ={
    url : 'http://apis.skplanetx.com/weather/forecast/3days?version=1&lat=37.496375&lon=126.95687900000007&foretxt=Y&appKey=83480fbf-88ce-3919-bf7a-edfb540d73c9'
  };
  var dust_api_info ={
    url : 'http://apis.skplanetx.com/weather/dust?version=1&lat=37.496375&lon=126.95687900000007&appKey=83480fbf-88ce-3919-bf7a-edfb540d73c9'
  };
  var alert_api_info ={
    url : 'http://apis.skplanetx.com/weather/severe/alert?version=1&lat=37.496375&lon=126.95687900000007&appKey=83480fbf-88ce-3919-bf7a-edfb540d73c9'
  };
  var now_temperature ={
    url : 'http://apis.skplanetx.com/weather/current/hourly?version=1&lat=37.496375&lon=126.95687900000007&appKey=83480fbf-88ce-3919-bf7a-edfb540d73c9'
  };
  // var weather_api_info ={
  //   url : 'http://apis.skplanetx.com/weather/forecast/3days?version=1&lat=37.5062404&lon=126.99385370000005&foretxt=Y&appKey=883fa1c3-0119-3f92-b201-3174e69df38c'
  // };
  // var dust_api_info ={
  //   url : 'http://apis.skplanetx.com/weather/dust?version=1&lat=37.5062404&lon=126.99385370000005&appKey=883fa1c3-0119-3f92-b201-3174e69df38c'
  // };
  // var alert_api_info ={
  //   url : 'http://apis.skplanetx.com/weather/severe/alert?version=1&lat=37.5062404&lon=126.99385370000005&appKey=883fa1c3-0119-3f92-b201-3174e69df38c'
  // };
  // var now_temperature ={
  //   url : 'http://apis.skplanetx.com/weather/current/hourly?version=1&lat=37.5062404&lon=126.99385370000005&appKey=883fa1c3-0119-3f92-b201-3174e69df38c'
  // };
  function now_weather_get(){
    get_request(now_temperature, function(err2, response2, body2){
      if(err2){
        console.log(err2);
        return;
      }
      var info2 = JSON.parse(body2);
      if(info2 !== null || info2 !== undefined){
        if(info2.length != 0){

            if(info2.result.code == 9200){
              if(info2.weather.hourly.length != 0){
                hourly_weather = info2.weather.hourly[0].sky.code;
                hourly_temperature = info2.weather.hourly[0].temperature.tc;
                  if(hourly_weather == 'SKY_O01' ||hourly_weather == 'SKY_O02' || hourly_weather == 'SKY_O03'){
                    //맑음
                    hourly_weather = 8;
                  }else if(hourly_weather == 'SKY_O04' || hourly_weather == 'SKY_O06' || hourly_weather == 'SKY_O08' || hourly_weather == 'SKY_O10'){
                    hourly_weather = 1;
                    //비
                  }else if(hourly_weather == 'SKY_O05' || hourly_weather == 'SKY_O09'){
                    hourly_weather = 3;
                    //눈
                  }else if(hourly_weather == 'SKY_O07'){
                    hourly_weather = 7;
                    //흐림
                  }else if(hourly_weather == 'SKY_O11'){
                    hourly_weather = 4;
                    //천둥
                  }else if(hourly_weather == 'SKY_O12' || hourly_weather == 'SKY_O14'){
                    hourly_weather = 0;
                    //천둥 + 비
                  }else if(hourly_weather == 'SKY_O13'){
                    hourly_weather = 2;
                    //천둥 + 눈
                  }
                  console.log("hourly_weather : ", hourly_weather);
                  if(hourly_weather >=7 && now_weather == 6){
                    hourly_weather = now_weather;
                  }else if(hourly_weather >=7 && now_weather == 5){
                    hourly_weather = now_weather;
                  }
              }
            }
            print_data();

        }
      }


    });
  }
  function alert_get(){
    get_request(alert_api_info, function(err2, response2, body2){
      if(err2){
        console.log(err2);
        return;
      }
      var info2 = JSON.parse(body2);
      if(info2 !== null || info2 !== undefined){
        if(info2.length != 0){

            if(info2.result.code == 9200){
              if(info2.weather.alert.length != 0){
                if(info2.weather.alert[0].alert51.cmdCode == 1){
                  if(info2.weather.alert[0].alert51.varCode == 3 || info2.weather.alert[0].alert51.varCode == 12){
                    if(now_weather >= 7){
                      if(info2.weather.alert[0].alert51.varCode == 3){
                        now_weather = 6;
                      }else if(info2.weather.alert[0].alert51.varCode == 12){
                        now_weather = 5;
                      }
                    }
                  }
                }
              }

            }
          now_weather_get();

        }
      }


  });
}
  function dust_get(){
    get_request(dust_api_info, function(err2, response2, body2){
      if(err2){
        console.log(err2);
        return;
      }
      var info2 = JSON.parse(body2);
      if(info2 !== null || info2 !== undefined){
        if(info2.length != 0){

            if(info2.result.code == 9200){
              dust_value = info2.weather.dust[0].pm10.value;
              dust_grade = info2.weather.dust[0].pm10.grade;
            }

        }
      }
      alert_get();
    });
  }
  function api_get(){
    get_request(weather_api_info, function(err, response, body){
      if(err){
        console.log(err);
        return;
      }
      var info = JSON.parse(body);
      if(info !== null || info !== undefined){
        if(info.length != 0){

            if(info.result.code == 9200){
              var today_weather = 0;
              var user_info = info.weather.forecast3days[0].grid;
              var fcstext = info.weather.forecast3days[0].fcstext;
              var now_time = info.weather.forecast3days[0].timeRelease;
              var fcst3hour = info.weather.forecast3days[0].fcst3hour;
              sky = [fcst3hour.sky.code4hour, fcst3hour.sky.code7hour, fcst3hour.sky.code10hour, fcst3hour.sky.code13hour, fcst3hour.sky.code16hour, fcst3hour.sky.code19hour, fcst3hour.sky.code22hour, fcst3hour.sky.code25hour];
              for(var i=0; i<8; i++){
                if(sky[i] == 'SKY_S01' || sky[i] == 'SKY_S02' || sky[i] == 'SKY_S03'){
                  //맑음
                  sky[i] = 8;
                }else if(sky[i] == 'SKY_S04' || sky[i] == 'SKY_S06' || sky[i] == 'SKY_S08' || sky[i] == 'SKY_S10'){
                  sky[i] = 1;
                  //비
                }else if(sky[i] == 'SKY_S05' || sky[i] == 'SKY_S09'){
                  sky[i] = 3;
                  //눈
                }else if(sky[i] == 'SKY_S07'){
                  sky[i] = 7;
                  //흐림
                }else if(sky[i] == 'SKY_S11'){
                  sky[i] = 4;
                  //천둥
                }else if(sky[i] == 'SKY_S12' || sky[i] == 'SKY_S14'){
                  sky[i] = 0;
                  //천둥 + 비
                }else if(sky[i] == 'SKY_S13'){
                  sky[i] = 2;
                  //천둥 + 눈
                }
              }
              //우선순위
              //천둥 + 비 : 0
              // 비 : 1
              //천둥 + 눈 : 2
              //눈 : 3
              //천둥 : 4
              //폭염 : 5
              //한파 : 6
              //흐림 : 7
              //맑음 :
              now_weather = sky[0];
              for(var j=1; j<8; j++){
                if(sky[i] < 7){
                  if(now_weather > sky[j]){
                    now_weather = sky[j];
                  }
                }
              }
              temperature = [
                fcst3hour.temperature.temp4hour,
                fcst3hour.temperature.temp7hour,
                fcst3hour.temperature.temp10hour,
                fcst3hour.temperature.temp13hour,
                fcst3hour.temperature.temp16hour,
                fcst3hour.temperature.temp19hour,
                fcst3hour.temperature.temp22hour,
                fcst3hour.temperature.temp25hour,
              ];

            }

        }

      }

      dust_get();
    });
  }
  // api_get();

  function get_data(){
    console.log("ho?");
    var date = new Date();
    tmp_getHours = date.getHours();
    console.log("tmp_getHours : ", tmp_getHours);
    if(tmp_getHours == 0){
      form_hour = tmp_getHours - 1;
    }else if(tmp_getHours == 1){
      form_hour = tmp_getHours - 2;
    }else{
      if((tmp_getHours - 2)%3 == 0){
        form_hour = tmp_getHours;
      }else if((tmp_getHours - 2)%3 == 1){
        form_hour = tmp_getHours - 1;
      }else{
        form_hour = tmp_getHours - 2;
      }
    }
      if(date.getHours() == 2 || date.getHours() == 5 || date.getHours() == 8 ||date.getHours() == 11 || date.getHours() == date.getHours() == 17 || date.getHours() == 20 || date.getHours() == 23){
        api_get();
        console.log("ho!!!!!!!!!!");
        print_data();
      }
  }
  var date = new Date();
  var tmp_getHours = date.getHours();
  if(tmp_getHours == 0){
    form_hour = tmp_getHours - 1;
  }else if(tmp_getHours == 1){
    form_hour = tmp_getHours - 2;
  }else{
    if((tmp_getHours - 2)%3 == 0){
      form_hour = tmp_getHours;
    }else if((tmp_getHours - 2)%3 == 1){
      form_hour = tmp_getHours - 1;
    }else{
      form_hour = tmp_getHours - 2;
    }
  }
  api_get();
  setInterval(get_data, 1000*60*20);
  // setInterval(now_weather_get, 1000*60*20);
io = socketio.listen(server);
  io.sockets.on('connection',function(socket){
    console.log('connection info :', socket.request.connection._peername);

    socket.remoteAddress = socket.request.connection._peername.address;
    socket.remotePort = socket.request.connection._peername.port;
    socket.on('android_weather_toServer', function(){
      console.log("android_weather_toServer");
      var tmp_max_elem = new Array();
      tmp_max_elem = get_most_cnt_BIG_DATA();
      var tmp_Json = {
        now_mode : now_mode,
        sky0 : sky[0],
        sky1 : sky[1],
        sky2 : sky[2],
        sky3 : sky[3],
        sky4 : sky[4],
        sky5 : sky[5],
        sky6 : sky[6],
        sky7 : sky[7],
        temperature0 : temperature[0],
        temperature1 : temperature[1],
        temperature2 : temperature[2],
        temperature3 : temperature[3],
        temperature4 : temperature[4],
        temperature5 : temperature[5],
        temperature6 : temperature[6],
        temperature7 : temperature[7],
        dust_value : dust_value,
        dust_grade : dust_grade,
        form_hour : form_hour,
        now_weather : now_weather,
        hourly_weather : hourly_weather,
        hourly_temperature : hourly_temperature,
        Big_Data_time_table_arduino : Big_Data_time_table_arduino/cnt,
        BIg_Date_time_table_android_max_one : tmp_max_elem[0],
        BIg_Date_time_table_android_max_two : tmp_max_elem[1]
      };
      socket.emit('android_weather_toPhone', tmp_Json);
      console.log('tmp_Json : ', tmp_Json);
    });
    socket.on('color_init', function(){
      console.log("color_init");
      var tmp_json = {
        mood_color : mood_color
      };
      socket.emit('color_init_to_arduino', tmp_json);
    });

    socket.on('off_mood', function(){
      console.log("off_mood");
      now_mode = 4;
      on_off = 0;
      endDate = new Date();
      endDate = endDate.getTime();
      var gap = (endDate - startDate)/1000;
      console.log("GAP : ", gap);
      Big_Data_time_table_arduino += gap;
      console.log("Big_Data_time_table_arduino : ", Big_Data_time_table_arduino);
      cnt++;
      console.log("cnt : ", cnt);

    });

    socket.on('sentiment_send_to_server', function(data){
      console.log("sentiment_send_to_server");
      var tmp_string = data.send_msg;
      var r1 = sentiment(tmp_string);
      console.log(' r1.comparative : ', r1.comparative);
      var comparative = r1.comparative;
      now_mode = 5;
      ai_flag = 1;
      if(comparative <= -1.0){
        //분노
          now_emotion = 20;
      }else if(comparative >= -0.7 &&  comparative < -0.3){
          //슬픔
          now_emotion = 21;
      }else if(comparative >=-0.3  &&  comparative < 0){
          //우울
          now_emotion = 22;
      }else if(comparative >=0  &&  comparative <= 0.24){
          //조금 우울
          now_emotion = 23;
      }else if(comparative >=0.24  &&  comparative < 0.6){
          //찡찡댐
          now_emotion = 24;
      }else if(comparative >=0.6  &&  comparative < 1.0){
          //기쁨
          now_emotion = 25;
      }else if(comparative >1.0){
          //환희
          now_emotion = 26;
      }



      var tmp_json = {"comparative" : r1.comparative};

      socket.emit('sentiment_send_to_android', tmp_json);
    });


    socket.on('mode_change_mood', function(data){
      console.log("mode_change_mood");
      now_mode = 0;
      console.log("color : ",data);
      mood_color =  data;
      ai_flag = 0;
      if(on_off == 0){
        on_off = 1;
        var date_tmp = new Date();
        startDate = date_tmp.getTime();
      }
      var BIGDATE_DATE = new Date();
      var BIGDATE_HOUR = BIGDATE_DATE.getHours();
      var BIGDATE_MINUTE = BIGDATE_DATE.getMinutes();
      if(BIGDATE_MINUTE > 30){
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2+1]++;
      }else{
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2]++;
      }
      print_BIG_DATA();
    });
    socket.on('mode_change_weather', function(){
      console.log("mode_change_mood");
      now_mode = 1 ;
      ai_flag = 0;
      if(on_off == 0){
        on_off = 1;
        var date_tmp = new Date();
        startDate = date_tmp.getTime();
      }
      var BIGDATE_DATE = new Date();
      var BIGDATE_HOUR = BIGDATE_DATE.getHours();
      var BIGDATE_MINUTE = BIGDATE_DATE.getMinutes();
      if(BIGDATE_MINUTE > 30){
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2+1]++;
      }else{
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2]++;
      }
      print_BIG_DATA();
    });
    socket.on('mode_change_temperature', function(){
      console.log("mode_change_mood");
      now_mode = 2;
      ai_flag = 0;
      if(on_off == 0){
        on_off = 1;
        var date_tmp = new Date();
        startDate = date_tmp.getTime();
      }
      var BIGDATE_DATE = new Date();
      var BIGDATE_HOUR = BIGDATE_DATE.getHours();
      var BIGDATE_MINUTE = BIGDATE_DATE.getMinutes();
      if(BIGDATE_MINUTE > 30){
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2+1]++;
      }else{
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2]++;
      }
      print_BIG_DATA();
    });
    socket.on('mode_change_dust', function(){
      console.log( "mode_change_mood");
      now_mode = 3;
      ai_flag = 0;
      if(on_off == 0){
        on_off = 1;
        var date_tmp = new Date();
        startDate = date_tmp.getTime();
        console.log('startDate : ', startDate);
      }
      var BIGDATE_DATE = new Date();
      var BIGDATE_HOUR = BIGDATE_DATE.getHours();
      var BIGDATE_MINUTE = BIGDATE_DATE.getMinutes();
      if(BIGDATE_MINUTE > 30){
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2+1]++;
      }else{
        Big_Data_time_tabl_appe[BIGDATE_HOUR*2]++;
      }
      print_BIG_DATA();
    });
    socket.on('connection_to_server', function(data){
      console.log("Connected?");
      console.log("data : ", data);
    });


    //demo mode
    socket.on('start_demo', function(){
      ai_flag = 0;
      demo_now_mode = now_mode;
      demo_dust_value = dust_value;
      demo_now_weather = now_weather;
      for(var k=0; k<8; k++){
        demo_temperature[k] = temperature[k];
      }
      demo_now_weather = now_weather;
      var tmp_json = {
        demo_now_mode : demo_now_mode,
        demo_dust_value : demo_dust_value,
        demo_now_weather : now_weather,
        demo_temperature : demo_temperature[0]
      };
      socket.emit('init_demo_mode', tmp_json);
      console.log("start_demo");
    });

    socket.on('demo_now_weather_change', function(data){
      now_mode = 1;
      now_weather = data;
      console.log("demo_now_weather_change");
    });
    socket.on('demo_dust_value_change', function(data){
      now_mode = 3;
      dust_value = data;
      console.log("demo_dust_value_change");
    });
    socket.on('demo_temperature_change', function(data){
      now_mode = 2;
      for(var k=0; k<8; k++){
        temperature[k] = data;
      }

      console.log("demo_temperature_change");
    });

    socket.on('end_demo', function(){
      now_mode = demo_now_mode;
      if(ai_flag == 0){
        ai_flag = 1;
      }else {
      ai_flag = 0;
      }
      dust_value = demo_dust_value;
      for(var k=0; k<8; k++){
        temperature[k] = demo_temperature[k];
      }
      now_weather = demo_now_weather;
      console.log("end_demo");
    });

  console.log('socket.io 요청을 받아들일 준비가 되었습니다.');
  app.set('socketio_server', socketio_server);
  });
};


var weather_get = function(req, res){
  console.log('/weather_get 호출');
  // res.writeHead('200', {'Content-Type':'text/html;charset=utf8'});
    res.write('<div>');

    res.write('now_mode : ' + now_mode+'\n');
    res.write('mood_color : ' + mood_color+'\n');
    res.write('dust_value : ' + dust_value+'\n');
    // res.write('on_off : ' + on_off+'\n');
  for(var i=0; i<8; i++){
    res.write('weather : ' + sky[i]+'\n');
  }

  res.write('temperature\n');
  for(var k=0; k<8; k++){
    res.write('temperature : ' + temperature[k]+'\n');
  }
  if(ai_flag == 1){
    res.write('now_real_wea : ' + now_emotion+'\n');
  }else{
    res.write('now_real_wea : ' + now_weather+'\n');
  }

  res.write('</div>');
  // for(var k=0; k<8; k++){
  //   res.write('<div><p> ' +temperature[k]+'</p></div>');
  // }
  // res.end();
};


module.exports = socketio_server;
module.exports.weather_get = weather_get;
