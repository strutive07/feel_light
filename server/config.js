var path = require('path');
module.exports = {
	server_port: 3000,
	route_info: [
			{file:path.join(process.cwd(),'server/process'), path:'/ho', method:'login_html', type:'get'},
			{file:path.join(process.cwd(),'server/socket_server'), path:'/weather_get', method:'weather_get', type:'get'}
			//{file:path.join(process.cwd(),'server/socket_server'), path:'/weather_get', method:'weather_get', type:'get'}
	]
};
