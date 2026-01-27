#include "demo_v_User.h"

using namespace demo;

// Add definition of your processing function here

void demo::v::User::login(const HttpRequestPtr &req,
		std::function<void (const HttpResponsePtr &)> &&callback,
		std::string &&userId,
		const std::string &password)
{
      LOG_DEBUG<<"User  "<<userId<<"  login";
      // Authentification algorithm, read database, verify, identify, etc ...
      Json::Value ret;
      ret["result"]="ok";
      ret["id"]= 3; // drogon::utils::getUuid();
      // ret["password"] = password;
      auto resp=HttpResponse::newHttpJsonResponse(ret);
      callback(resp);
}

void demo::v::User::getInfo(const HttpRequestPtr &req,
		std::function<void (const HttpResponsePtr &)> &&callback,
		std::string userId,
		const std::string &token) const
{
       LOG_DEBUG<<"User   "<<userId<<" get his information";

       // Verify validity of the token
       
       Json::Value ret;
       ret["result"]="ok";
       ret["user_name"]="Jack";
       ret["user_id"]=userId;
       ret["gender"]=1;
       ret["token"] = 3;
       auto resp=HttpResponse::newHttpJsonResponse(ret);
       callback(resp);

}
