#include "SoplonController.h"

void SoplonController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);

    std::string body = "<h1>Welcome to SoplonWebApp</h1>";
		body += "<ul>";
		body += "	<li><a href=\"http://localhost/accueil\">Generate Index</a></li>";
		body += "	<li>ResolveAuthors</li>";
		body += "</ul>";

    resp->setBody(body);
    callback(resp);
    ChallengeProfiles *  cp = new ChallengeProfiles(SIMPLE);
    delete cp;
   // auto dbc = drogon::app().getDbClient();
   //dbc->execSqlSync("CREATE table if not exists author(id int primary key not null)");
}
