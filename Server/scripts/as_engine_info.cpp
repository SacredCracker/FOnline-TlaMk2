#ifdef __ASEngineInfo
# ifndef __ASEngineInfo0

void InfoASE()
{
    /*
       uint countGlFuncdef=ASEngine->GetFuncdefCount();
       Log("Funcdef в скриптовом движке: %u \n",countGlFuncdef);
       for(uint i=0;i<countGlFuncdef;i++)
       {
            asIScriptFunction* func=ASEngine->GetFuncdefByIndex(i);
            func->AddRef();
            Log("Memmory %i\n", (func->Release()));
            Log("Id %u Index %u ModuleName %s Declaration \"%s\" \n",func->GetId(),i,func->GetModuleName() ,func->GetDeclaration());
       }
     */
    uint countGlFunc = ASEngine->GetGlobalFunctionCount();
    Log( "\n\nФункций в скриптовом движке: %u \n", countGlFunc );
    for( uint i = 0; i < countGlFunc; i++ )
    {
        asIScriptFunction* func = ASEngine->GetGlobalFunctionByIndex( i );
        // Log("Id %u Index %u ModuleName %s Declaration \"%s\" \n",func->GetId(),i,func->GetModuleName() ,func->GetDeclaration(false,false));
        // func->AddRef();
        // Log("Memmory %i\n", (func->Release()));
        if( func )
            Log( "Id %u Index %u ModuleName %s Declaration \"%s\" \n", func->GetId(), i, func->GetModuleName(), func->GetDeclaration( true, true ) );
    }

    uint countObType = ASEngine->GetObjectTypeCount();
    Log( "\n" );
    Log( "Количесто типов в скриптовом движке %u\n\n", countObType );
    for( uint i = 0; i < countObType; i++ )
    {
        Log( "+++++++\n" );
        asIObjectType* type = ASEngine->GetObjectTypeByIndex( i );
        /*
           virtual int AddRef() const = 0;
           virtual int Release() const = 0;
         */
        // type->AddRef();
        // Log("Memmory %i\n", (type->Release()));
        if( type )
        {
            uint factCount = type->GetFactoryCount();
            uint methCount = type->GetMethodCount();
            uint propCount = type->GetPropertyCount();
            Log( "Index %u Id %u Name \"%s\" Size %u factCount %u\n", i, type->GetTypeId(), type->GetName(), type->GetSize(), factCount );
            Log( "\n" );
            for( uint i = 0; i < factCount; i++ )
            {
                asIScriptFunction* func = type->GetFactoryByIndex( i );
                // func->AddRef();
                // Log("Memmory %i\n", (func->Release()));
                Log( "Id %u Index %u ModuleName %s Declaration \"%s\" \n", func->GetId(), i, func->GetModuleName(), func->GetDeclaration( true, true ) );
            }
            Log( "\n" );
            Log( "MethodCount %u\n", methCount );
            for( uint i = 0; i < methCount; i++ )
            {
                asIScriptFunction* func = type->GetMethodByIndex( i );
                // func->AddRef();
                // Log("Memmory %i\n", (func->Release()));
                Log( "Id %u Index %u ModuleName %s Declaration \"%s\" \n", func->GetId(), i, func->GetModuleName(), func->GetDeclaration( true, true ) );
            }
            Log( "\n" );
            Log( "propCount %u\n", propCount );
            for( uint i = 0; i < propCount; i++ )
            {
                Log( "Index %u Declaration \"%s\" \n", i, type->GetPropertyDeclaration( i ) );
            }
            Log( "+++++++\n\n" );
        }
    }
}

void FullInfoASEWriteToFile( )
{
	/*ofstream write( ".\\InfoEngine.full" );
	if( !write.is_open( ) )
		return;
	
    uint countGlFuncdef = ASEngine->GetFuncdefCount();
    write << "Funcdef:\n";
    for( uint i = 0; i < countGlFuncdef; i++ )
    {
        asIScriptFunction* func = ASEngine->GetFuncdefByIndex( i );
        write << func->GetNamespace() << "::" << func->GetName( ) << " ";
    }

    uint countGlFunc = ASEngine->GetGlobalFunctionCount();
    write << "\nFunction:\n";
    for( uint i = 0; i < countGlFunc; i++ )
    {
        asIScriptFunction* func = ASEngine->GetGlobalFunctionByIndex( i );
        write << func->GetNamespace() << "::" << func->GetName() << " ";
    }
  
    uint countObType = ASEngine->GetObjectTypeCount();
    write << "\nType:\n";
    for( uint i = 0; i < countObType; i++ )
	{
		asIObjectType* type = ASEngine->GetObjectTypeByIndex( i );
		write << type->GetName();
	}
    for( uint i = 0; i < countObType; i++ )
    {
        //Log( "+++++++\n" );
        asIObjectType* type = ASEngine->GetObjectTypeByIndex( i );
        uint factCount = type->GetFactoryCount();
        uint methCount = type->GetMethodCount();
        uint propCount = type->GetPropertyCount();
        //Log( "Index %u Id %u Name \"%s\" Size %u factCount %u\n", i, type->GetTypeId(), type->GetName(), type->GetSize(), factCount );
       // Log( "\n" );
        for( uint i = 0; i < factCount; i++ )
        {
            asIScriptFunction* func = type->GetFactoryByIndex( i );
            func->AddRef();
            //Log( "Memmory %i\n", ( func->Release() ) );
            //Log( "Id %u Index %u ModuleName %s Declaration \"%s\" \n", func->GetId(), i, func->GetModuleName(), func->GetDeclaration( false, false ) );
        }
        //Log( "\n" );
        //Log( "MethodCount %u\n", methCount );
        for( uint i = 0; i < methCount; i++ )
        {
            asIScriptFunction* func = type->GetMethodByIndex( i );
            func->AddRef();
            //Log( "Memmory %i\n", ( func->Release() ) );
            //Log( "Id %u Index %u ModuleName %s Declaration \"%s\" \n", func->GetId(), i, func->GetModuleName(), func->GetDeclaration( false, false ) );
        }
        //Log( "\n" );
        //Log( "propCount %u\n", propCount );
        for( uint i = 0; i < propCount; i++ )
        {
           // Log( "Index %u Declaration \"%s\" \n", i, type->GetPropertyDeclaration( i ) );
        }
       // Log( "+++++++\n\n" );
    }
    write.close();*/
}

# endif
#else
void InfoASE()
{}

void FullInfoASEWriteToFile()
{}
#endif
