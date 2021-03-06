#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
 
#define MAXN 100010
#define INF 1234567890

using namespace std;

int P[ MAXN + 1 ];

void prefix( string pattern )
{
	P[ 0 ] = P[ 1 ] = 0;
	int N = pattern.length();
	for( int i = 2; i <= N; i++ ) {
		int j = P[ i - 1 ];
		while( true ) {
			if( pattern[ i - 1 ] == pattern[ j ] ) {
				P[ i ] = j + 1;
				break;
			}
			else if( j == 0 ) {
				P[ i ] = 0;
				break;
			} else {
				j = P[ j ];
			}
		}
	}
}

int KMP( string text, string pattern )
{
	int i = 0, j = 0;
	int N = text.length(), M = pattern.length();
	while( true ) {
		if( i == N ) {
			break;
		}
		if( text[ i ] == pattern[ j ] ) {
			if( j == M - 1 ) {
				return M;
			}
			i++;
			j++;
		}
		else if( j == 0 ) {
			i++;
		} else {
			j = P[ j ];
		}
	}
	return j;
}

int main( void )
{
	while( !feof( stdin ) ) {
		string str[ 3 ];
		int ans = INF;
		for( int i = 0; i < 3; i++ ) {
			cin >> str[ i ];
			if( feof( stdin ) ) {
				return 0;
			}
		}
		sort( str, str + 3 );
		do {
			prefix( str[ 1 ] );
			int newans = KMP( str[ 0 ], str[ 1 ] );
			string newstr = str[ 0 ];
			for( int i = newans; i < str[ 1 ].length(); i++ ) {
				newstr += str[ 1 ][ i ];
			}
			prefix( str[ 2 ] );
			newans = KMP( newstr, str[ 2 ] );
			for( int i = newans; i < str[ 2 ].length(); i++ ) {
				newstr += str[ 2 ][ i ];
			}
			ans = min( ans, ( int ) newstr.length() );
		} while( next_permutation( str, str + 3 ) );
		printf("%d\n", ans );
	}
	return 0;
}
