var path = require('path');

var login_html = function(req, res){
  console.log('/login 호출');
  req.app.render(path.join(process.cwd(),'server/chat'), function(err, html){
    if(err){
      console.log(err);
      return;
    }
    console.log('rendered : process.ejs');
    res.end(html);
  });
};

module.exports.login_html = login_html;
