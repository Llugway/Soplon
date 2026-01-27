#if USE_MYSQL
    static std::shared_ptr<DbClient> newMysqlClient(const std::string &connInfo, const size_t connNum);
#endif

orm::DbClientPtr getDbClient(const std::string &name = "default");
orm::DbClientPtr getFastDbClient(const std::string &name = "default");

template <
	typename FUNCTION1,
	typename FUNCTION2,
	typename... Arguments>
void execSqlAsync(const std::string &sql,
		 FUNCTION1 &&rCallback,
		 FUNCTION2 &&exceptCallback,
		 Arguments &&... args) noexcept;

template <typename... Arguments>
std::future<const Result> execSqlAsyncFuture(const std::string &sql,
					     Arguments &&.. args) noexcept;

template <typename.. Arguments>
const Result execSqlSync(const std::string &sql,
			 Arguments &&... args) noexcept(false);

internal::SqlBinder operator<<((const std::string &sql);
