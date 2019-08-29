#include "fonline_tla.h"

#define TYPE_CRITTER         ( 29 )
#define TYPE_DEAD_CRITTER    ( 10 )

EXPORT int getParam_Hp( CritterMutual & cr, uint );
EXPORT bool       GetCritterMonitorPosition( CritterMutual& cr, int& X, int& Y );
EXPORT bool       GetCritterMonitorPositionA( CritterMutual& cr, int& X, int& Y, int& W, int& H );
EXPORT bool       IsAdmin( CritterMutual& cr );
EXPORT bool       CritterSetAlpha( CritterMutual& cr, uint8 Alpha );
EXPORT CritterCl* GetMonCrExt( int x, int y );

FONLINE_DLL_ENTRY( isCompiler )
{
    Log( "Load RenderHelper...\n" );
    if( ASEngine->RegisterGlobalFunction( "CritterCl@ GetMonitorCritterExt(int x, int y)", asFUNCTION( GetMonCrExt ), asCALL_CDECL ) < 0 )
        Log( "Error reg CritterCl@ GetMonitorCritterExt(int, int)\n" );
}

EXPORT bool CritterSetColor( CritterMutual& cr, int cType, uint cColor, uint color )
{
    uint     count = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( count );
    int      type = cr.Cond == COND_DEAD ? TYPE_DEAD_CRITTER : TYPE_CRITTER;
    for( uint i = 0; i < count; i++ )
    {
        Sprite* spr = sprs[ i ];
        if( spr == NULL || spr->Valid == false )
            continue;
        if( spr->HexX == cr.HexX && spr->HexY == cr.HexY && ( spr->DrawOrderType == type ) )
        {
            const_cast< int& >( spr->ContourType ) = cType;
            const_cast< uint& >( spr->ContourColor ) = cColor;
            const_cast< uint& >( spr->Color ) = color;
            return true;
        }
    }
    return false;
}

EXPORT CritterCl* GetMonCrExt( int x, int y )
{
    uint     count = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( count );
	if( sprs )
		for( uint i = count; i-- != 0; )
		{
			Sprite* spr = sprs[ i ];
			if( !spr || !spr->Valid )
				continue;
			if( spr->DrawOrderType != TYPE_CRITTER )
				continue;
			SpriteInfo* info = spr->GetSprInfo();
			if( !info )
				continue;
			uint16 w = (uint16) ( (float) info->Width / FOnline->SpritesZoom ),
				   h = (uint16) ( (float) info->Height / FOnline->SpritesZoom );

			int sx = 0, sy = 0;
			spr->GetPos( sx, sy );

			// if(sx<=x && sy<=y && sx+w>=x && sy+h>=y)
			if( FOnline->IsSpriteHit( spr, x, y, false ) )
			{
				Field* f = GetField( spr->HexX, spr->HexY );
				if( !f ) continue;
				if( f->Crit )
				{
					CritterCl* cr = const_cast< CritterCl* >( f->Crit );
					int typeId = ASEngine->GetTypeIdByDecl( "CritterCl" );
					ASEngine->AddRefScriptObject( cr, typeId );
					return cr;
				}
			}
		}
    return NULL;
}

EXPORT void CallRenderCritters( )
{
	static uint funcId = FOnline->ScriptBind( "client_main", "void render_critter( CritterCl@ cr, int x, int y, int w, int h )", false );
	if(!funcId)
	{
		Log("No found critter render function\n");
		return;
	}
    uint     countSpr = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( countSpr );
    for( uint i = 0; i < countSpr; i++ )
    {
        Sprite* spr = sprs[ i ];
        if( spr == NULL || spr->Valid == false )
            continue;
        if( spr->DrawOrderType == TYPE_CRITTER /*|| spr->DrawOrderType == TYPE_DEAD_CRITTER */)
        {
            SpriteInfo* si = spr->GetSprInfo();
			if( si )
			{
				Field* field = GetField( spr->HexX, spr->HexY );
				if(field && field->Crit)
				{
					if( FOnline->ScriptPrepare( funcId ) )
					{
						int x = 0, y = 0;
						spr->GetPos( x, y );
						FOnline->ScriptSetArgObject( const_cast< CritterCl* >(field->Crit) );
						
						FOnline->ScriptSetArgInt( x );
						FOnline->ScriptSetArgInt( y );
						
						FOnline->ScriptSetArgInt( (int) ( (float) si->Width / FOnline->SpritesZoom ) );
						FOnline->ScriptSetArgInt( (int) ( (float) si->Height / FOnline->SpritesZoom ) );
						
						FOnline->ScriptRunPrepared();
					}
				}
			}
        }
    }
}

EXPORT bool CritterSetAlpha( CritterMutual& cr, uint8 Alpha )
{
    uint     count = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( count );
    int      type = cr.Cond == COND_DEAD ? TYPE_DEAD_CRITTER : TYPE_CRITTER;
    for( uint i = 0; i < count; i++ )
    {
        Sprite* spr = sprs[ i ];
        if( spr == NULL || spr->Valid == false )
            continue;
        if( spr->HexX == cr.HexX && spr->HexY == cr.HexY && ( spr->DrawOrderType == type ) )
        {
            uint8* a = const_cast< uint8* >( spr->Alpha );
            *a = Alpha;
            return true;
        }
    }
    return false;
}

EXPORT bool CritterSetEgg( CritterMutual& cr, int EggType )
{
    uint     count = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( count );
    int      type = cr.Cond == COND_DEAD ? TYPE_DEAD_CRITTER : TYPE_CRITTER;
    for( uint i = 0; i < count; i++ )
    {
        Sprite* spr = sprs[ i ];
        if( spr == NULL || spr->Valid == false )
            continue;
        if( spr->HexX == cr.HexX && spr->HexY == cr.HexY && ( spr->DrawOrderType == type ) )
        {
            const_cast< int& >( spr->EggType ) = EggType;
            return true;
        }
    }
    return false;
}

EXPORT void GetCrittersMonitorPosition( ScriptArray& crArray, ScriptArray& outCrArray, ScriptArray& outArray ) // int& X, int& Y, int& W, int& H )
{
    uint     lengthCrs = crArray.GetSize();
    uint     countSpr = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( countSpr );
    // outArray.Resize( lengthCrs * 5 );
    int      X = 0, Y = 0, id = 0, w = 0, h = 0, type = 0;
    for( uint l = 0; l < lengthCrs; l++ )
    {
        CritterMutual& cr = *( *(CritterMutual**) crArray.At( l ) );
        id = cr.Id;
        type = cr.Cond == COND_DEAD ? TYPE_DEAD_CRITTER : TYPE_CRITTER;
        for( uint i = 0; i < countSpr; i++ )
        {
            Sprite* spr = sprs[ i ];
            if( spr == NULL || spr->Valid == false )
                continue;
            if( spr->HexX == cr.HexX && spr->HexY == cr.HexY && spr->DrawOrderType == type )
            {
                spr->GetPos( X, Y );
                SpriteInfo* si = spr->GetSprInfo();

                outArray.InsertLast( &id );
                outArray.InsertLast( &X );
                outArray.InsertLast( &Y );
                w = (int) ( (float) si->Width / FOnline->SpritesZoom );
                outArray.InsertLast( &w );
                h = (int) ( (float) si->Height / FOnline->SpritesZoom );
                outArray.InsertLast( &h );
                outCrArray.InsertLast( crArray.At( l ) );
                break;
            }
        }
    }
}

EXPORT bool GetCritterMonitorPositionA( CritterMutual& cr, int& X, int& Y, int& W, int& H )
{
    uint     count = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( count );
    int      type = cr.Cond == COND_DEAD ? TYPE_DEAD_CRITTER : TYPE_CRITTER;
    for( uint i = count; i-- > 0; )
    {
        Sprite* spr = sprs[ i ];
        if( spr == NULL || spr->Valid == false )
            continue;
        if( spr->HexX == cr.HexX && spr->HexY == cr.HexY && spr->DrawOrderType == type )
        {
            spr->GetPos( X, Y );
            SpriteInfo* si = spr->GetSprInfo();
            W = (int) ( (float) si->Width / FOnline->SpritesZoom );
            H = (int) ( (float) si->Height / FOnline->SpritesZoom );
            return true;
        }
    }
    return false;
}

EXPORT bool GetCritterMonitorPosition( CritterMutual& cr, int& X, int& Y )
{
    uint     count = 0;
    Sprite** sprs = FOnline->GetDrawingSprites( count );
    int      type = cr.Cond == COND_DEAD ? TYPE_DEAD_CRITTER : TYPE_CRITTER;
    for( uint i = 0; i < count; i++ )
    {
        Sprite* spr = sprs[ i ];
        if( spr == NULL || spr->Valid == false )
            continue;
        if( spr->HexX == cr.HexX && spr->HexY == cr.HexY && ( spr->DrawOrderType == type ) )
        {
            spr->GetPos( X, Y );
            return true;
        }
    }
    return false;
}

EXPORT bool IsAdmin( CritterMutual& cr )
{
    return ( (Client*) &cr )->Access == ACCESS_ADMIN;
}

EXPORT int getParam_Hp( CritterMutual& cr, uint )
{
    return cr.Params[ ST_CURRENT_HP ];
}

#include "animation.cpp"


