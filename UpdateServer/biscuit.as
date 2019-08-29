
void Parse( file& f, filesystem& fs, string path )
{
	array<string> @ dirs = fs.getDirs();
	if( dirs !is null )
		for( uint i = 0, iend = dirs.length(); i < iend; i++ )
		{
			string str = fs.getCurrentPath( );
			if( fs.changeCurrentPath( dirs[i] ) )
			{
				Parse( f, fs, ( path == "" ) ? dirs[i] : ( path + "/" + dirs[i] ) );
				fs.changeCurrentPath( str );
			}
		}
	
	array<string> @ files = fs.getFiles();
	if( files !is null )
		for( uint i = 0, iend = files.length(); i < iend; i++ )
			f.writeString( ( ( path != "" ) ? ( path + "/" ) : ( "" ) ) + files[i] + "\n" );
}

void ModuleInit( )
{	
	file f;
	if( f.open( "UpdateFiles.lst","w" ) != -1 )
	{
		filesystem fs;
		if( fs.changeCurrentPath( "Update/" ) )
			Parse( f, fs, "" );
		
		f.close();
	}
	
	system( "start UpdaterServer.exe" );
}

