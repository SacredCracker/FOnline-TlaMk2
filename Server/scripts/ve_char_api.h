unsigned int CharLength( const char* str )
{
    if( str )
    {
        unsigned int length = 0;
        while( str[ length++ ] != '\0' )
        {}
        return --length;
    }
    return 0;
}

bool CharIsWord( const unsigned int index, const char* input, const char* word, const unsigned int size_word )
{
    if( !input || !word )
        return false;
    unsigned int iEnd = CharLength( input ) - index;
    if( iEnd != size_word )
        return false;
    for( unsigned int i = 0; i < iEnd; i++ )
        if( input[ i + index ] != word[ i ] )
            return false;
    return true;
}

inline bool CharIsWord( unsigned int index, const char* input, const char* word )
{
    return CharIsWord( index, input, word, CharLength( word ) );
}

inline bool CharIsWord( const char* input, const char* word )
{
    return CharIsWord( 0, input, word, CharLength( word ) );
}

bool CharSubstring( const char* str, const unsigned int start, unsigned int len, char* outStr )
{
    if( str )
    {
        unsigned int len_str = CharLength( str );
        if( start < len_str )
        {
            len_str -= start;
            if( len_str < len )
                len = len_str;

            for( unsigned int i = 0; i < len; i++ )
                outStr[ i ] = str[ start + i ];
			outStr[ len ] = '\0';
            return true;
        }
    }
    return false;
}

bool CharFindPosition( const char* str, const char* word, unsigned int& pos )
{
    if( str && word  )
    {
        unsigned int len_str = CharLength( str ), len_word = CharLength( word ), out_pos = pos;
        if( len_str != 0 && len_word != 0 )
            for( char symbol = str[ out_pos ]; symbol != '\0' && ( len_str - out_pos ) >= len_word; symbol = str[ ++out_pos ] )
            {
                bool is_word = true;
                for( unsigned int i = 0; i < len_word; i++ )
                    if( str[ i + out_pos ] != word[ i ] )
                    {
                        is_word = false;
                        break;
                    }
                if( is_word )
                {
                    pos = out_pos;
                    return true;
                }
            }
    }
    return false;
}

inline bool IsSymbol( const char* chars, const char ch, uint len )
{
	for( uint i = 0; i < len; i++ )
		if( chars[i] == ch )
			return true;
	return false;
}

bool CharNextWordEx( const char* string, unsigned int& end_pos, char* outStr, unsigned int buffer, const char* chars )
{
    if( string && chars )
    {
        unsigned int length = 0, length_string = CharLength( string ), lenChars = CharLength( chars );
        if( length_string > end_pos )
        {
            while( string[ end_pos ] != '\0' )
            {
                char symbol = string[ end_pos++ ];
                if( length != 0 && IsSymbol( chars, symbol, lenChars ) )
                    break;
                else
				{
					if( !( buffer > length ) )
						return false;
					
					if( !IsSymbol( chars, symbol, lenChars ) )
                    outStr[ length++ ] = symbol;
				}
            }
			if( !( buffer > length ) )
				return false;
            outStr[ length ] = '\0';
			return true;
        }
        else
            end_pos = length_string;
    }
    return false;
}

inline bool CharNextWord( const char* string, unsigned int& end_pos, char* outStr, unsigned int buffer )
{
	const char* chars = "\t\n =";
	return CharNextWordEx( string, end_pos, outStr, buffer, chars );
}

void CharJoin( const char* input0, const char* input1, unsigned int position, char* out )
{
    if( input0 && input1 )
    {
        const unsigned int len0 = CharLength( input0 ), len1 = CharLength( input1 ), len = len0 + len1;
        unsigned int       current_pos0 = 0, current_pos = 0;
        while( input0[ current_pos0 ] != '\0' )
        {
            if( current_pos0 == position )
            {
                unsigned int current_pos1 = 0;
                while( input1[ current_pos1 ] != '\0' )
                    out[ current_pos++ ] = input1[ current_pos1++ ];
            }
            out[ current_pos++ ] = input0[ current_pos0++ ];
        }
        if( len0 == position )
        {
            unsigned int current_pos1 = 0;
            while( input1[ current_pos1 ] != '\0' )
                out[ current_pos++ ] = input1[ current_pos1++ ];
        }
    }
    else
    {
        if( input0 )
        {
            const unsigned int len = CharLength( input0 );
            for( unsigned int i = 0; i < len; i++ )
                out[ i ] = input0[ i ];
        }
        else if( input1 )
        {
            const unsigned int len = CharLength( input1 );
            for( unsigned int i = 0; i < len; i++ )
                out[ i ] = input1[ i ];
        }
    }
}

uint CharEndJoin( const char* input0, const char* input1, char* out )
{
    uint len = CharLength( input0 ) + CharLength( input1 );
    CharJoin( input0, input1, CharLength( input0 ), out );
    return len;
}
