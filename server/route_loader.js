var route_loader = {};

var config = require('./config');

route_loader.init = function(app, router){
  return initRoutes(app, router);
};

function initRoutes(app, router){
  var length = config.route_info.length;
  for(var i=0;i<length;i++){
    var curItem = config.route_info[i];
    var curModule = require(curItem.file);

    if (curItem.type == 'get') {
              router.route(curItem.path).get(curModule[curItem.method]);
  		} else if (curItem.type == 'post') {
              router.route(curItem.path).post(curModule[curItem.method]);
  		} else {
  			router.route(curItem.path).post(curModule[curItem.method]);
  		}
  }

  app.use('/', router);
}

module.exports = route_loader;
