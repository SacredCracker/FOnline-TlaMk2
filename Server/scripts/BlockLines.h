#ifndef __BLOCK_LINES_H
#define __BLOCK_LINES_H

#define RegItemBlockLines( reg )    if( reg < 0 ) \
        Log( "ќшибка регистрации класса ItemBlockLines <%d>.\n", __LINE__ )

union BlockData
{
    uint8 Block;
    struct
    {
        uint8 Dist : 4;
        uint8 Dir : 4;
    };

};

struct ItemBlockLines
{
    ItemBlockLines();
    void AddRef();
    void Release();

    uint8 get_Dir( uint idx );
    uint8 get_Dist( uint idx );

    uint      ItemId;

    BlockData Data[ ITEM_MAX_BLOCK_LINES ];

    int       RefCount;
};

ItemBlockLines* ItemBlockLinesFactory();
void            RegistrationItemBlockLinesClass();

void RegistrationItemBlockLinesClass()
{
    const char* defName = ASEngine->GetDefaultNamespace();
    ASEngine->SetDefaultNamespace( "Mk2" );

    RegItemBlockLines( ASEngine->RegisterObjectType( "ItemBlockLines", 0, asOBJ_REF ) );
    RegItemBlockLines( ASEngine->RegisterObjectBehaviour( "ItemBlockLines", asBEHAVE_FACTORY, "ItemBlockLines@ f( )", asFUNCTION( ItemBlockLinesFactory ), asCALL_CDECL ) );
    RegItemBlockLines( ASEngine->RegisterObjectBehaviour( "ItemBlockLines", asBEHAVE_ADDREF, "void f()", asMETHOD( ItemBlockLines, AddRef ), asCALL_THISCALL ) );
    RegItemBlockLines( ASEngine->RegisterObjectBehaviour( "ItemBlockLines", asBEHAVE_RELEASE, "void f()", asMETHOD( ItemBlockLines, Release ), asCALL_THISCALL ) );

    RegItemBlockLines( ASEngine->RegisterObjectMethod( "ItemBlockLines", "uint8 get_Dir( uint )", asMETHOD( ItemBlockLines, get_Dir ), asCALL_THISCALL ) );
    RegItemBlockLines( ASEngine->RegisterObjectMethod( "ItemBlockLines", "uint8 get_Dist( uint )", asMETHOD( ItemBlockLines, get_Dist ), asCALL_THISCALL ) );
    RegItemBlockLines( ASEngine->RegisterObjectProperty( "ItemBlockLines", "const uint ItemId", offsetof( ItemBlockLines, ItemId ) ) );
    ASEngine->SetDefaultNamespace( defName );
}


ItemBlockLines::ItemBlockLines()
{
    RefCount = 1;

    for( uint i = 0; i < ITEM_MAX_BLOCK_LINES; i++ )
        Data[ i ].Block = 0;

    ItemId = 0;
}

void ItemBlockLines::AddRef()
{
    RefCount++;
    // Log("RefCount %i\n",RefCount);
}

void ItemBlockLines::Release()
{
    // Log("--RefCount %i\n",RefCount-1);
    if( --RefCount == 0 )
    {
        delete this;
    }
}

uint8 ItemBlockLines::get_Dist( uint idx )
{
    if( idx >= ITEM_MAX_BLOCK_LINES )
        return 0;
    return Data[ idx ].Dist;
}

uint8 ItemBlockLines::get_Dir( uint idx )
{
    if( idx >= ITEM_MAX_BLOCK_LINES )
        return 0;
    return Data[ idx ].Dir;
}

ItemBlockLines* ItemBlockLinesFactory()
{
    return new ItemBlockLines();
}
#endif
