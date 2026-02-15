#ifndef ATLAS_DATABASE_UTILS_H
#define ATLAS_DATABASE_UTILS_H

#include <cstdint>
#include <expected>
#include <format>
#include <functional>
#include <memory>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace AtlasDatabaseUtilities
{
	struct DestroyStatement
	{
		void operator()(sqlite3_stmt* statement) const
		{
			sqlite3_finalize(statement);
		}
	};

	using MemorySafeStatement = std::unique_ptr<sqlite3_stmt, DestroyStatement>;

	std::expected<bool, std::string> open(sqlite3** database);

	std::expected<bool, std::string> close(sqlite3* database);

	std::expected<MemorySafeStatement, std::string> prepareStatement(sqlite3* database, std::string sql);

	static int bind(sqlite3_stmt* statement, int index, int64_t parameter)
	{
		return sqlite3_bind_int64(statement, index, parameter);
	}

	static int bind(sqlite3_stmt* statement, int index, int parameter)
	{
		return sqlite3_bind_int(statement, index, parameter);
	}

	static int bind(sqlite3_stmt* statement, int index, bool parameter)
	{
		return sqlite3_bind_int(statement, index, parameter ? 1 : 0);
	}

	static int bind(sqlite3_stmt* statement, int index, double parameter)
	{
		return sqlite3_bind_double(statement, index, parameter);
	}

	static int bind(sqlite3_stmt* statement, int index, float parameter)
	{
		return sqlite3_bind_double(statement, index, static_cast<double>(parameter));
	}

	static int bind(sqlite3_stmt* statement, int index, const std::string& parameter)
	{
		return sqlite3_bind_text(statement, index, parameter.c_str(), -1, SQLITE_TRANSIENT);
	}

	static int bind(sqlite3_stmt* statement, int index, const char* parameter)
	{
		return sqlite3_bind_text(statement, index, parameter, -1, SQLITE_TRANSIENT);
	}

	static int bind(sqlite3_stmt* statement, int index, std::nullptr_t)
	{
		return sqlite3_bind_null(statement, index);
	}

	static int bind(sqlite3_stmt* statement, int index, const std::vector<uint8_t>& parameter)
	{
		return sqlite3_bind_blob(statement, index, parameter.data(), static_cast<int>(parameter.size()), SQLITE_TRANSIENT);
	}

	template <typename T>
	std::expected<bool, std::string> bindStatementParameter(sqlite3_stmt* statement, int index, const T& parameter)
	{
		int resultCode = bind(statement, index, parameter);

		if (resultCode != SQLITE_OK) {
			std::string error = std::format("Error binding parameter at index {}: SQLite Code {}", index, resultCode);

			return std::unexpected<std::string>(error);
		}

		return true;
	}

	template <typename T>
	std::expected<bool, std::string> bindStatementParameter(const MemorySafeStatement& statement, int index, const T& parameter)
	{
		return bindStatementParameter(statement.get(), index, parameter);
	}

	template <typename... Args>
	std::expected<bool, std::string> bindStatementParameters(sqlite3_stmt* statement, Args&&... args)
	{
		std::expected<bool, std::string> bindStatementParametersResult = true;

		int index = 1;

		auto tryBind = [&](const auto& parameter) -> bool {
			bindStatementParametersResult = bindStatementParameter(statement, index++, parameter);

			return bindStatementParametersResult.has_value();
			};

		(tryBind(args) && ...);

		return bindStatementParametersResult;
	}

	template <typename... Args>
	std::expected<bool, std::string> bindStatementParameters(const MemorySafeStatement& statement, Args&&... args)
	{
		return bindStatementParameters(statement.get(), std::forward<Args>(args)...);
	}

	std::expected<bool, std::string> execute(sqlite3_stmt* statement, sqlite3* database);

	std::expected<bool, std::string> execute(const MemorySafeStatement& statement, sqlite3* database);

	template <typename T>
	std::expected <std::vector<T>, std::string> query(sqlite3_stmt* statement, sqlite3* database, std::function<T(sqlite3_stmt*)> initializeTypeFromStatement)
	{
		std::vector<T> data;

		int resultCode = SQLITE_OK;

		while ((resultCode = sqlite3_step(statement)) == SQLITE_ROW) {
			data.push_back(initializeTypeFromStatement(statement));
		}

		sqlite3_reset(statement);

		if (resultCode != SQLITE_DONE) {
			std::string error = std::format("Error executing query statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

			return std::unexpected<std::string>(error);
		}

		return data;
	}

	template <typename T>
	std::expected<std::vector<T>, std::string> query(const MemorySafeStatement& statement, sqlite3* database, std::function<T(sqlite3_stmt*)> initializeTypeFromStatement)
	{
		return query(statement.get(), database, initializeTypeFromStatement);
	}
};

#endif