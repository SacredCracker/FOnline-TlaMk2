// Работа с клиентскими файлами.
// Автор: TabaK

#ifdef __SERVER

#include <excpt.h>
#include "fonline_tla.h"

EXPORT void RemoveClient( Critter& client );
EXPORT void AddClient( Critter& client );
EXPORT bool UnsetKnownLoc( ScriptString* filename, uint id );
EXPORT bool SetKnownLoc( ScriptString* filename, uint locId );
EXPORT bool ToGlobal( ScriptString* filename );
EXPORT bool SetParam( ScriptString* filename, uint index, int val );
EXPORT bool TransitToMap( ScriptString* filename, uint mapId, uint16 hexX, uint16 hexY );
EXPORT int  GetParameter( ScriptString* name, uint id, uint index );
EXPORT bool IsKnownLocation( ScriptString* name, uint id, uint locId );
EXPORT uint GetMapId( ScriptString* name, uint id );


typedef map< uint, Critter* >           OffCrMap;
typedef map< uint, Critter* >::iterator OffCrIt;
OffCrMap OffClients;


FONLINE_DLL_ENTRY( isCompiler )
{
    Log( "Loading OffPlayer.dll...\n" );
}

EXPORT void ClearClients()
{
    int typeId = ASEngine->GetTypeIdByDecl( "Critter" );

    /*for(OffCrIt it = OffClients.begin(), end = OffClients.end(); it != end; ++it )
       {
            ASEngine->ReleaseScriptObject((*it).second, typeId);
       }*/
    OffClients.clear();
}

EXPORT void RemoveClient( Critter& client )
{
    OffCrIt it = OffClients.find( client.Id );
    if( it != OffClients.end() )
    {
        // int typeId=ASEngine->GetTypeIdByDecl("Critter");
        // ASEngine->ReleaseScriptObject(&client, typeId);
        OffClients.erase( it );
    }
}

EXPORT void AddClient( Critter& client )
{
    /*int typeId=ASEngine->GetTypeIdByDecl("Critter");
       ASEngine->AddRefScriptObject(&client, typeId);*/
    OffClients[ client.Id ] = &client;
}

EXPORT bool UnsetKnownLocation( ScriptString* name, uint crId, uint locId )
{
    OffCrIt it = OffClients.find( crId );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == crId )
            {
                uint16 count = cl->DataExt->LocationsCount;
                for( uint n = 0; n < count; n++ )
                {
                    if( cl->DataExt->LocationsId[ n ] == locId )
                    {
                        const_cast< uint* >( cl->DataExt->LocationsId )[ n ] = cl->DataExt->LocationsId[ --count ];
                        const_cast< uint* >( cl->DataExt->LocationsId )[ count ] = 0;
                        const_cast< uint16& >( cl->DataExt->LocationsCount ) = count;
                        return true;
                    }
                }
                return false;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }

    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
    {
        return false;
    }
    uint16 number = 0;
    fseek( f, 0x26FE, SEEK_SET );
    fread( &number, sizeof( uint16 ), 1, f );
    uint* locs = new uint[ number ];
    fread( locs, sizeof( uint ), number, f );
    for( uint n = 0; n < number; n++ )
    {
        if( locs[ n ] == locId )
        {
            locs[ n ] = locs[ --number ];
            locs[ number ] = 0;
            fseek( f, 0x26FE, SEEK_SET );
            fwrite( &number, sizeof( uint16 ), 1, f );
            fwrite( locs, sizeof( uint ), number, f );
            fclose( f );
            delete[] locs;
            return true;
        }
    }
    fclose( f );
    delete[] locs;
    return false;
}


EXPORT bool SetKnownLocation( ScriptString* name, uint crId, uint locId )
{
    OffCrIt it = OffClients.find( crId );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == crId )
            {
                uint16 count = cl->DataExt->LocationsCount;
                if( count == MAX_STORED_LOCATIONS )
                    return false;
                const_cast< uint* >( cl->DataExt->LocationsId )[ count ] = locId;
                const_cast< uint16& >( cl->DataExt->LocationsCount ) = count++;
                return true;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }


    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
    {
        return false;
    }
    uint16 number = 0;
    fseek( f, 0x26FE, SEEK_SET );
    fread( &number, sizeof( uint16 ), 1, f );
    fseek( f, number * 4, SEEK_CUR );
    fwrite( &locId, sizeof( uint ), 1, f );
    number++;
    fseek( f, 0x26FE, SEEK_SET );
    fwrite( &number, sizeof( uint16 ), 1, f );
    fclose( f );
    return true;
}

EXPORT bool ToGlobalMap( ScriptString* name, uint crId )
{
    OffCrIt it = OffClients.find( crId );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == crId )
            {
                const_cast< uint16& >( cl->HexX ) = 0;
                const_cast< uint16& >( cl->HexX ) = 0;
                const_cast< uint& >( cl->MapId ) = 0;
                const_cast< uint16& >( cl->MapPid ) = 0;
                return true;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }

    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
    {
        return false;
    }
    uint n = 0;
    fseek( f, 0x28, SEEK_SET );
    fwrite( &n, sizeof( uint ), 1, f );
    fseek( f, 0x64, SEEK_SET );
    fwrite( &n, sizeof( uint ), 1, f );
    fwrite( &n, sizeof( uint ), 1, f );
    fclose( f );
    return true;
}

EXPORT bool SetParameter( ScriptString* name, uint crId, uint index, int val )
{
    if( index > MAX_PARAMS - 1 )
        return false;
    OffCrIt it = OffClients.find( crId );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == crId )
            {
                const_cast< int* >( cl->Params )[ index ] = val;
                return true;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }

    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
    {
        return false;
    }
    fseek( f, 0x6C + index * sizeof( int ), SEEK_SET );
    fwrite( &val, sizeof( int ), 1, f );
    fclose( f );
    return true;
}

EXPORT bool Transit( ScriptString* name, uint id, Map& map, uint16 pid, uint16 hexX, uint16 hexY, uint16 locX, uint16 locY )
{
    if( map.Proto->Header.NoLogOut )
        return false;
    OffCrIt it = OffClients.find( id );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* client = ( *it ).second;
            if( client->Id == id )
            {
                const_cast< uint16& >( client->HexX ) = hexX;
                const_cast< uint16& >( client->HexY ) = hexY;
                const_cast< uint16& >( client->WorldX ) = locX;
                const_cast< uint16& >( client->WorldY ) = locY;
                const_cast< uint& >( client->MapId ) = map.Data.MapId;
                const_cast< uint16& >( client->MapPid ) = pid;
                return true;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }

    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
    {
        return false;
    }
    fseek( f, 0x28, SEEK_SET );
    fwrite( &hexX, sizeof( uint16 ), 1, f );
    fwrite( &hexY, sizeof( uint16 ), 1, f );
    fwrite( &locX, sizeof( uint16 ), 1, f );
    fwrite( &locY, sizeof( uint16 ), 1, f );
    fseek( f, 0x64, SEEK_SET );
    fwrite( &map.Data.MapId, sizeof( uint ), 1, f );
    fwrite( &pid, sizeof( uint16 ), 1, f );
    fclose( f );
    return true;
}

EXPORT int GetParameter( ScriptString* name, uint id, uint index )
{
    if( index > MAX_PARAMS - 1 )
        return -1;
    OffCrIt it = OffClients.find( id );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == id )
            {
                return cl->Params[ index ];
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }
    FILE* f;
    char  filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );
    int   retVal = -1;
    if( fopen_s( &f, filename, "r" ) == 0 )
    {
        fseek( f, 0x6C + index * sizeof( int ), SEEK_SET );
        fread( &retVal, sizeof( int ), 1, f );
        fclose( f );
    }
    return retVal;
}

EXPORT bool IsKnownLocation( ScriptString* name, uint id, uint locId )
{
    OffCrIt it = OffClients.find( id );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == id )
            {
                uint16 count = cl->DataExt->LocationsCount;
                for( uint n = 0; n < count; n++ )
                {
                    if( cl->DataExt->LocationsId[ n ] == locId )
                        return true;
                }
                return false;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }

    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
        return false;
    uint16 count = 0;
    fseek( f, 0x26FE, SEEK_SET );
    fread( &count, sizeof( uint16 ), 1, f );
    uint* locs = new uint[ count ];
    fread( locs, sizeof( uint ), count, f );
    fclose( f );
    uint cur = 0;
    for( uint n = 0; n < count; n++ )
    {
        if( locs[ n ] == locId )
        {
            delete[] locs;
            return true;
        }
    }
    delete[] locs;
    return false;
}

EXPORT uint GetMapId( ScriptString* name, uint id )
{
    OffCrIt it = OffClients.find( id );
    if( it != OffClients.end() )
    {
        __try
        {
            Critter* cl = ( *it ).second;
            if( cl->Id == id )
            {
                return cl->MapId;
            }
        }
        __except( EXCEPTION_EXECUTE_HANDLER )
        {
            Log( "Exception handled in OffPlayer.dll\n" );
        }
        OffClients.erase( it );
    }

    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
        return 0;
    uint mapId = 0;
    fseek( f, 0x64, SEEK_SET );
    fread( &mapId, sizeof( uint ), 1, f );
    fclose( f );
    return mapId;
}

EXPORT bool SaveParams( ScriptString* name, Critter& cr )
{
    if( cr.IsNotValid )
        return false;
    char filename[ 60 ];
    sprintf_s( filename, ".//save//clients//%s.client", name->c_str() );

    FILE* f;
    if( fopen_s( &f, filename, "r+b" ) != 0 )
    {
        return false;
    }
    fseek( f, 0x28, SEEK_SET );
    fwrite( &cr.HexX, sizeof( uint16 ), 1, f );
    fwrite( &cr.HexY, sizeof( uint16 ), 1, f );
    fwrite( &cr.WorldX, sizeof( uint16 ), 1, f );
    fwrite( &cr.WorldY, sizeof( uint16 ), 1, f );
    fseek( f, 0x64, SEEK_SET );
    fwrite( &cr.MapId, sizeof( uint ), 1, f );
    fwrite( &cr.MapPid, sizeof( uint16 ), 1, f );
    fseek( f, 0x6C, SEEK_SET );
    fwrite( &( cr.Params ), sizeof( int ), MAX_PARAMS, f );
    fclose( f );
    return true;
}

#endif
