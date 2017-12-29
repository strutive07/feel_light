var express = require('express');
var http = require('http');
var path = require('path');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var static = require('serve-static');
var errorHandler = require('express-error-handler');
var expressErrorHandler = require('express-error-handler');
var expressSession = require('express-session');
var app = express();
var crypto = require('crypto');

var config = require('./config');
var route_loader = require('./route_loader');

app.set('port', process.env.PORT || config.server_port);
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(cookieParser());
app.use(expressSession({
	secret:'m!y##Se@cre&*tKeyHO##$#',
	resave:true,
	saveUninitialized:true
}));
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');



var MongoClient = require('mongodb').MongoClient;
route_loader.init(app, express.Router());

var errorHandler = expressErrorHandler({
  static :{
    '404':'./server/public/404.html'
  }
});

app.use(expressErrorHandler.httpError(404));
app.use(errorHandler);
process.on('SIGTERM', function () {
    console.log("프로세스가 종료됩니다.");
});

app.on('close', function () {
	console.log("Express 서버 객체가 종료됩니다.");
});

var server = http.createServer(app).listen(process.env.PORT||app.get('port'), function(){
  console.log('서버가 시작되었습니다. 포트 : ' + app.get('port'));
});
//
var socketio_server = require('./server/socket_server');
socketio_server.init(app, server);
