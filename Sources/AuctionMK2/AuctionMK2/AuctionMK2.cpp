// Главный DLL-файл.
//#define __SERVER
#include "fonline_tla.h"
#include "sqlite/sqlite3.h"
#include <windows.h>
#include <iostream>


static char *unicodeToUtf8(const WCHAR *zWideFilename){
  int nByte;
  char *zFilename;

  nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, -1, 0, 0, 0, 0);
  zFilename = (char *)malloc( nByte );
  if( zFilename==0 ){
    return 0;
  }
  nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, -1, zFilename, nByte,
                              0, 0);
  if( nByte == 0 ){
    free(zFilename);
    zFilename = 0;
  }
  return zFilename;
}

static WCHAR *mbcsToUnicode(const char *zFilename){
  int nByte;
  WCHAR *zMbcsFilename;
  int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;

  nByte = MultiByteToWideChar(codepage, 0, zFilename, -1, NULL,0)*sizeof(WCHAR);
  zMbcsFilename = (WCHAR*)malloc( nByte*sizeof(zMbcsFilename[0]) );
  if( zMbcsFilename==0 ){
    return 0;
  }
  nByte = MultiByteToWideChar(codepage, 0, zFilename, -1, zMbcsFilename, nByte);
  if( nByte==0 ){
    free(zMbcsFilename);
    zMbcsFilename = 0;
  }
  return zMbcsFilename;
}


EXPORT void BackupDatabase()
{
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile("save\\database\\*.dbsave", &findData);
	int backupNumber = 0;
	int fileVersion = 0;

	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{		
			if(sscanf(findData.cFileName, "mk2%d.dbsave", &fileVersion) == 1)
				if(fileVersion > backupNumber)
					backupNumber = fileVersion;
		}
		while(FindNextFile(hFile, &findData) != 0);
		FindClose(hFile);
	}
	// Имя нового файла  с бекапом базы
	char buffer[40];
	std::string newFName = "save\\database\\mk2";
	newFName = newFName + _itoa(backupNumber + 1, buffer, 10) + ".dbsave";
	CopyFile("mk2.db",newFName.c_str(),false);
	Log("Auction database backup successful. FileName %s\n", newFName.c_str());	
}

EXPORT void RestoreDatabase()
{
	WIN32_FIND_DATA findData;
	HANDLE hFile = FindFirstFile("save\\database\\*.dbsave", &findData);
	int backupNumber = 0;
	int fileVersion = 0;

	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{		
			if(sscanf(findData.cFileName, "mk2%d.dbsave", &fileVersion) == 1)
				if(fileVersion > backupNumber)
					backupNumber = fileVersion;
		}
		while(FindNextFile(hFile, &findData) != 0);
		FindClose(hFile);
		char buffer[40];
		if(backupNumber > 0)
		{
			std::string fileName = "save\\database\\mk2";
			fileName = fileName + _itoa(backupNumber, buffer, 10) + ".dbsave";			
			CopyFile(fileName.c_str(),"mk2.db",false);
			Log("Fuction database restored. Backup filename %s\n", fileName.c_str());
		}
	}
}

int GetItemProtoId(uint pid)
{
	sqlite3* db = NULL;
	char* dbName = "mk2.db";
	int result;
	int id = 0;

	result = sqlite3_open(dbName, &db);
	if(result != SQLITE_OK)
	{
		Log("can't found db");
		sqlite3_close(db);
		return 0;
	}

	sqlite3_stmt* statement;
	char* sql = "select Id from tItemProto where FOProtoId = ?";
	sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	sqlite3_bind_int(statement,  1, pid);
	result = sqlite3_step(statement);

	if(result == SQLITE_ROW)
	{
		id = sqlite3_column_int( statement, 0);
	}
	else
	{
		sqlite3_stmt* statementIns;
		char* sqlIns = "insert into tItemProto (FoProtoId) values (?)";
		sqlite3_prepare_v2(db, sqlIns, -1, &statementIns, NULL);
		sqlite3_bind_int(statementIns,  1, pid);
		result = sqlite3_step(statementIns);
		if(result == SQLITE_DONE)
		{
			sqlite3_stmt* statementS;
			char* sqlS = "select Id from tItemProto where (RowId = last_insert_rowid())";
			sqlite3_prepare_v2(db, sqlS, -1, &statementS, NULL);
			result = sqlite3_step(statementS);
			if(result == SQLITE_ROW)
				id = sqlite3_column_int( statementS, 0); // Первый индекс колонки = 0
			sqlite3_finalize(statementS);
		}
		sqlite3_finalize(statementIns);
	}
	sqlite3_finalize(statement);
	sqlite3_close(db);

	return id;
}

EXPORT bool CheckSaleAllowed(uint pid)
{
	return GetItemProtoId(pid) > 0;
}

EXPORT bool CloseLot(int lotId, int playerId, int dateWhen)
{
	
	sqlite3* db = NULL;
	char* dbName = "mk2.db";
	int result;

	result = sqlite3_open(dbName, &db);
	if(result != SQLITE_OK)
	{
		sqlite3_close(db);
		return 0;
	}
	// Поиск игрока производится по паре Id/Имя, поскольку при delete_self возможна подмена Id
	sqlite3_stmt* statement;
	char* sql = "update tLots set PlayerIdBuyer = ?, TimeSold = ?, IsActual = 0 where LotId = ?";
	
	sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	sqlite3_bind_int(statement,  1, playerId);
	sqlite3_bind_int(statement,  2, dateWhen);
	sqlite3_bind_int(statement,  3, lotId);

	result = sqlite3_step(statement);
	
	sqlite3_finalize(statement);
	sqlite3_close(db);

	if(result == SQLITE_DONE)
		return true;
	return false;
}

EXPORT bool CancelLot(int lotId, int dateWhem)
{
	sqlite3* db = NULL;
	char* dbName = "mk2.db";
	int result;
	int playerId = 0;

	result = sqlite3_open(dbName, &db);
	if(result != SQLITE_OK)
	{
		sqlite3_close(db);
		return 0;
	}
	// Поиск игрока производится по паре Id/Имя, поскольку при delete_self возможна подмена Id
	sqlite3_stmt* statement;
	char* sql = "update tLots set TimeCanceled = ? , IsActual = 0 where LotId = ?";
	
	sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	sqlite3_bind_int(statement,  1, dateWhem);
	sqlite3_bind_int(statement,  2, lotId);

	result = sqlite3_step(statement);
	
	sqlite3_finalize(statement);
	sqlite3_close(db);

	if(result == SQLITE_DONE)
		return true;

	return false;
}

// Список
//EXPORT ScriptArray& GetLotsForClose(int dateWhen, int& rows, int& columns)
//{
//	char buffer[40];
//	std::string sql = " TimeToCancel < ";
//	sql = sql + _itoa(dateWhen, buffer, 10);
//	return GetOpenLots(0, 0, false, NULL, NULL, &ScriptString::Create( sql.c_str() ) ,true , 0, &rows, &columns);
//}
//

EXPORT int CountOpenLots(bool isActual, ScriptString* searchVal, ScriptString* additionalFilter, int typeFilter)
{
	sqlite3* db = NULL;
	char* dbName = "mk2.db";
	char buffer[40];
	int result;
	int lots = 0;

	result = sqlite3_open(dbName, &db);
	if(result != SQLITE_OK)
	{
		sqlite3_close(db);
		return 0;// arr;
	}

	std::string sql = "	SELECT     COUNT(*) lots \
						FROM	tLots INNER JOIN \
								tItemProto ON tLots.ItemProtoId = tItemProto.Id inner join\
								tPlayer on tPlayer.Id = tLots.PlayerIdSeller";
	if(typeFilter > 0)
	{
		sql = sql + " join tItemType on tItemType.TypeId = tItemProto.TypeId and tItemType.FilterFlag & " + _itoa(typeFilter, buffer, 10) + " > 0 ";
	}
	if(isActual)
		sql = sql + " where IsActual = 1 ";
	else
		sql = sql + " where IsActual = 0 ";
	if(searchVal!=NULL)
	{
		WCHAR* filter = mbcsToUnicode(searchVal->c_str());
		char* untf8Filter = unicodeToUtf8(filter);
		sql = sql + " and  tItemProto.FOProtoName like '%" + untf8Filter + "%'";
		free(filter);
		free(untf8Filter);
	}

	if(additionalFilter != NULL)
	{
		sql = sql + " and ";
		sql = sql + additionalFilter->c_std_str();
	}

	sqlite3_stmt* statement;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, NULL);

	result = sqlite3_step(statement);

	if(result == SQLITE_ROW)
	{
		lots = sqlite3_column_int( statement, 0);
	}
	else
	{
		return 0;
	}

	sqlite3_finalize(statement);
	sqlite3_close(db);

	return lots;
}


EXPORT void GetOpenLots(int fromPage, int pageSize, bool isActual, ScriptString* searchVal, ScriptString* orderBy, ScriptString* additionalFilter, 
						bool orderDesc,  int typeFilter, int& rows, int& columns, ScriptArray& arr)
{
	//Log("GetOpenLots called");
	//ScriptArray& arr =  ScriptArray::Create( "string" );
	sqlite3* db = NULL;
	char* dbName = "mk2.db";
	char buffer[40];
	int result;

	result = sqlite3_open(dbName, &db);
	if(result != SQLITE_OK)
	{
		sqlite3_close(db);
		return ;// arr;
	}
	std::string sql = "	SELECT     tLots.FOItemId, tItemProto.FOProtoId, tLots.LotId, tPlayer.FOCritterId, tLots.LotComission, tLots.LotSize, tLots.LotSM, tLots.FOItemId_AContainer, \
							tLots.TimeOpened,  replace(tLots.FoItemLexems,'@msg game ','@?') as FOItemLexems, tLots.FOItemInfo, tLots.TimeToCancel \
						FROM	tLots INNER JOIN \
								tItemProto ON tLots.ItemProtoId = tItemProto.Id inner join\
								tPlayer on tPlayer.Id = tLots.PlayerIdSeller";
	//Log("cmd: '%s'", sql.c_str());
	if(typeFilter > 0)
	{
		//Q: вклейка параметра через itoa,а  как правильно?
		sql = sql + " join tItemType on tItemType.TypeId = tItemProto.TypeId and tItemType.FilterFlag & " + _itoa(typeFilter, buffer, 10) + " > 0 ";
	}
	//Log("cmd: %s \n", sql);

	if(isActual)
		sql = sql + " where IsActual = 1 ";
	else
		sql = sql + " where IsActual = 0 ";
		

	// Как тут правильно записать? нужно проверить что значение не null
	if(searchVal!=NULL)
	{
		//sql = sql + " and  tItemProto.FOProtoName like '%" + searchVal->c_std_str() + "%'";
		WCHAR* filter = mbcsToUnicode(searchVal->c_str());
		char* untf8Filter = unicodeToUtf8(filter);
		sql = sql + " and  tItemProto.FOProtoName like '%" + untf8Filter + "%'";
		free(filter);
		free(untf8Filter);
	}

	if(additionalFilter != NULL)
	{
		sql = sql + " and ";
		sql = sql + additionalFilter->c_std_str();
	}
	// Сортировка
	sql = sql + " order by ";
	if(orderBy != NULL)
	{
		sql = sql + orderBy->c_std_str();
		if(orderDesc)
			sql = sql + " desc ";
		sql = sql + ",";
	}
	sql = sql + " tItemProto.FOProtoName, tItemProto.Id, tLots.LotId ";
	// страница
	if(pageSize > 0)
		sql = sql + " limit " + _itoa(pageSize, buffer, 10);
	if( fromPage>0 )
		sql = sql + " offset " + _itoa((pageSize*(fromPage - 1)), buffer, 10);
	char **sql_results;
	char* error_msg;
	//Log("cmd: %s \n", sql.c_str());
	result = sqlite3_get_table(db, sql.c_str(),
        &sql_results, &rows, &columns, &error_msg);
	if( result ==  SQLITE_OK && rows > 0)
	{
		for(int i = 1; i <= rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				 arr.InsertLast( &ScriptString::Create( sql_results[i*columns + j] ) );
			}

		}
	}
	//Log("\n Result: %d; arr length: %d", result, arr.GetSize());
	sqlite3_free_table(sql_results);
    sqlite3_close(db);
	//return arr;
}

// Получает Id записи об игроке из таблицы tPlayer. Если запись не найдена
// добавлят новую
// todo: обработка ошибок
int GetPlayerId(uint foCrId, ScriptString& playerName)
{
	sqlite3* db = NULL;
	char* dbName = "mk2.db";
	int result;
	int playerId = 0;

	result = sqlite3_open(dbName, &db);
	if(result != SQLITE_OK)
	{

		sqlite3_close(db);
		return 0;
	}
	// Поиск игрока производится по паре Id/Имя, поскольку при delete_self возможна подмена Id
	sqlite3_stmt* statement;
	char* sql = "select Id from tPlayer where FOCritterId = ? and FoPlayerName = ? ";
	
	sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
	sqlite3_bind_int(statement,  1, foCrId);
	sqlite3_bind_text(statement, 2, playerName.c_str(), -1, SQLITE_TRANSIENT);

	result = sqlite3_step(statement);

	if(result == SQLITE_ROW)
	{
		playerId = sqlite3_column_int( statement, 0);
	}
	else
	{
		//Log("новый игрок");
		// Не найдена запись для игрока, заносим новую
		sqlite3_stmt* statementIns;
		char* sqlI = "insert into tPlayer(FOCritterId, FOPlayerName) values (?, ?)";
		sqlite3_prepare_v2(db, sqlI, -1, &statementIns, NULL);
		sqlite3_bind_int(statementIns,  1, foCrId);
		sqlite3_bind_text(statementIns, 2, playerName.c_str(), -1, SQLITE_TRANSIENT);

		result = sqlite3_step(statementIns);
		if(result == SQLITE_DONE)
		{
			sqlite3_stmt* statementS;
			char* sqlS = "select Id from tPlayer where (RowId = last_insert_rowid())";
			sqlite3_prepare_v2(db, sqlS, -1, &statementS, NULL);
			result = sqlite3_step(statementS);
			
			if(result == SQLITE_ROW)
				playerId = sqlite3_column_int( statementS, 0); // Первый индекс колонки = 0
			sqlite3_finalize(statementS);
		}
		
		sqlite3_finalize(statementIns);
	}

	sqlite3_finalize(statement);
	sqlite3_close(db);

	return playerId;
}

// Вопрос: как нужно правильно объявлять строки? как ScriptString* или ScriptString&?
// Открывает лот, возвращает полученный Id лота
EXPORT int OpenLot(
			uint FOItemProtoId, uint crId, ScriptString& playerName, uint itemId, 
			uint lotSize, uint cost, uint itemInfo, uint timeOpened, 
			uint timeCancel, ScriptString* lexems, uint containerId, 
			uint comissionOpen)
{	
	//Log("OPen lot called/ Proto %d", FOItemProtoId);
	int lotId = 0;
	int playerId = GetPlayerId(crId, playerName);
	int protoId = GetItemProtoId(FOItemProtoId);
	//Log("plId = %d protoId = %d ", protoId, playerId);
	if(playerId > 0 && protoId > 0)
	{
		// Блок инициализации бд было бы неплохо вынести в отдельное место, но, не могу сделать функцию 
		// с возвращаемым значением sqlite3, как это делается?
		sqlite3* db = NULL;
		char* dbName = "mk2.db";
		int result;
		int pIndex = 0;

		result = sqlite3_open(dbName, &db);
		if(result != SQLITE_OK)
		{
			Log("cannot open db");
			sqlite3_close(db);
			return 0;
		}
		sqlite3_stmt *statement;
		// В перспективе возможна модификация структуры, поэтому параметры именованные
		const char* sql = 
			"INSERT INTO tLots \
				(LotSize, LotPrice, LotSM, LotDeposit, LotComission, \
				 LotHours, PlayerIdSeller, FOItemId, ItemProtoId, FOItemInfo, \
				 FOItemLexems, FOItemId_AContainer, TimeOpened,\
				 TimeToCancel) \
			 values( @LotSize, @LotPrice, @LotSM, @LotDeposit, @LotComission, \
				 @LotHours, @PlayerIdSeller, @FOItemId, @ItemProtoId, @FOItemInfo, \
				 @FOItemLexems, @FOItemId_AContainer, @TimeOpened, \
				 @TimeToCancel)";
		sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
		pIndex = sqlite3_bind_parameter_index(statement, "@LotSize");
		sqlite3_bind_int(statement, pIndex, lotSize);
		pIndex = sqlite3_bind_parameter_index(statement, "@LotPrice");
		sqlite3_bind_int(statement, pIndex, 0); // todo
		pIndex = sqlite3_bind_parameter_index(statement, "@LotSM");
		sqlite3_bind_int(statement, pIndex, cost);
		pIndex = sqlite3_bind_parameter_index(statement, "@LotDeposit");
		sqlite3_bind_int(statement, pIndex, 0); // todo
		pIndex = sqlite3_bind_parameter_index(statement, "@LotComission");
		sqlite3_bind_int(statement, pIndex, comissionOpen);
		pIndex = sqlite3_bind_parameter_index(statement, "@LotHours");
		sqlite3_bind_int(statement, pIndex, 0); //todo
		pIndex = sqlite3_bind_parameter_index(statement, "@PlayerIdSeller");
		sqlite3_bind_int(statement, pIndex, playerId);
		pIndex = sqlite3_bind_parameter_index(statement, "@FOItemId");
		sqlite3_bind_int(statement, pIndex, itemId);
		pIndex = sqlite3_bind_parameter_index(statement, "@ItemProtoId");
		sqlite3_bind_int(statement, pIndex, protoId);
		pIndex = sqlite3_bind_parameter_index(statement, "@FOItemInfo");
		sqlite3_bind_int(statement, pIndex, itemInfo);
		pIndex = sqlite3_bind_parameter_index(statement, "@FOItemLexems");
		//Log("Before lex \n");
		if(lexems!=NULL)
		{
		const char* p = lexems->c_str ();
		sqlite3_bind_text(statement, pIndex, p , -1, NULL);
		}
		//Log("after lex/n");
		pIndex = sqlite3_bind_parameter_index(statement, "@FOItemId_AContainer");
		sqlite3_bind_int(statement, pIndex, containerId);
		pIndex = sqlite3_bind_parameter_index(statement, "@TimeOpened");
		sqlite3_bind_int(statement, pIndex, timeOpened);
		pIndex = sqlite3_bind_parameter_index(statement, "@TimeToCancel");
		sqlite3_bind_int(statement, pIndex, timeCancel);
		result = sqlite3_step(statement);
		//Log("1 result: %d", result);
		if(result == SQLITE_DONE)
		{
			sqlite3_stmt *statementGetId;
			const char* sqlGetId = "select LotId from tLots where (RowId = last_insert_rowid())";
			sqlite3_prepare_v2(db, sqlGetId, -1, &statementGetId, NULL);
			result = sqlite3_step(statementGetId);
			if(result == SQLITE_ROW)
				lotId = sqlite3_column_int( statementGetId, 0);
			sqlite3_finalize(statementGetId);
		}
		//Log("2 result: %d", result);
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}

	return lotId;
}


// Entry point
FONLINE_DLL_ENTRY( isCompiler )
{
	/*//ASEngine->RegisterObjectType("CLot",sizeof(CLot),asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
	ASEngine->RegisterObjectType("CLot",sizeof(CLot),asOBJ_REF);
	ASEngine->RegisterObjectBehaviour("CLot", asBEHAVE_FACTORY, "CLot@ f()", asFUNCTION(Lot_Factory), asCALL_CDECL);
	ASEngine->RegisterObjectBehaviour("CLot",  asBEHAVE_ADDREF, "void f()", asMETHOD(CLot,AddRef), asCALL_THISCALL);
	ASEngine->RegisterObjectBehaviour("CLot",  asBEHAVE_RELEASE, "void f()", asMETHOD(CLot,Release), asCALL_THISCALL);
	//ASEngine->RegisterObjectBehaviour("CLot",asBEHAVE_CONSTRUCT,"void f()",asFUNCTION(CLot_ctor), asCALL_CDECL_OBJLAST);
	//ASEngine ->RegisterObjectBehaviour("CLot",asBe
	//ASEngine->RegisterObjectBehaviour("CLot",asBEHAVE_DESTRUCT,"void f()",asFUNCTION(CLot_dtor), asCALL_CDECL_OBJLAST);
	ASEngine->RegisterObjectMethod("CLot", "void DL()",asMETHOD(CLot, DL), asCALL_THISCALL );
	ASEngine->RegisterObjectMethod("CLot", "string& GetLexems()",asMETHOD(CLot, GetLexems), asCALL_THISCALL );
	ASEngine->RegisterObjectProperty("CLot", "int ItemId", offsetof(CLot, ItemId));
	ASEngine->RegisterObjectProperty("CLot", "int ItemPid", offsetof(CLot, ItemPid));
	ASEngine->RegisterObjectProperty("CLot", "int LotId", offsetof(CLot, LotId));
	ASEngine->RegisterObjectProperty("CLot", "int PlayerId", offsetof(CLot, PlayerId));
	ASEngine->RegisterObjectProperty("CLot", "int LotOpenComission", offsetof(CLot, LotOpenComission));
	ASEngine->RegisterObjectProperty("CLot", "int LotSize", offsetof(CLot, LotSize));
	ASEngine->RegisterObjectProperty("CLot", "int Cost", offsetof(CLot, Cost));
	ASEngine->RegisterObjectProperty("CLot", "int ContainerId", offsetof(CLot, ContainerId));
	ASEngine->RegisterObjectProperty("CLot", "int TimeCreate", offsetof(CLot, TimeCreate));
	ASEngine->RegisterObjectProperty("CLot", "int Info", offsetof(CLot, Info));
	ASEngine->RegisterObjectProperty("CLot", "int TimeToCancel", offsetof(CLot, TimeToCancel));
	//engine->RegisterObjectType(
	//engine*/
    if( isCompiler )
        return;
}
