#include <cstdio>
#include <algorithm>
#include <cmath>
 
#define MAXN 50000
#define INF 10000000000000LL
 
using namespace std;
 
struct pt {
	int x,y,idx;
};
 
bool cmpx( pt a, pt b )
{
	if( a.x == b.x ) {
		return a.y < b.y;
	} return a.x < b.x;
}
 
bool cmpy( pt a, pt b )
{
	if( a.y == b.y ) {
		return a.x < b.x;
	} return a.y < b.y;
}

long long D( pt a, pt b )
{
	return ( long long )( a.x - b.x ) * ( a.x - b.x ) + ( long long )( a.y - b.y ) * ( a.y - b.y );
}
 
pt X[ MAXN ],Y[ MAXN ];
int N;
 
long long combine( long long d, int mid, int lo, int hi, pt& A, pt& B )
{
	int cnt = 0;
	long long newmin = d;
	pt arr[ N + 1 ];
	for( int i = lo; i <= hi; i++ ) { 
		if( fabs( X[ mid ].x - Y[ i ].x ) < d ) {
			arr[ cnt++ ] = Y[ i ];
		}
	}
	for( int i = 0; i < cnt; i++ ) {
		for( int j = i + 1; j < cnt && ( long long )( arr[ j ].y - arr[ i ].y ) * ( arr[ j ].y - arr[ i ].y ) < d; j++ ) {
			if( D( arr[ i ], arr[ j ] ) < newmin ) {
				newmin = D( arr[ i ], arr[ j ] );
				A = arr[ i ];
				B = arr[ j ];
			}
		}
	}
	return newmin;
}
 
long long findmin( int i, int j, pt& A, pt& B )
{
	long long mindist = INF;
	if( j - i > 3 ) {
		int lo,hi;
		pt nA[ 2 ],nB[ 2 ];
		for( lo = ( i + j ) / 2; lo >= i && X[ lo ].x == X[ ( i + j ) / 2 ].x; lo-- );
		for( hi = ( i + j ) / 2; hi <= j && X[ hi ].x == X[ ( i + j ) / 2 ].x; hi++ ); 
		long long d1 = findmin( i, lo, nA[ 0 ], nB[ 0 ] );
		long long d2 = findmin( hi ,j, nA[ 1 ], nB[ 1 ] );
		if( d1 < d2 ) {
			mindist = d1;
			A = nA[ 0 ];
			B = nB[ 0 ];
		} else {
			mindist = d2;
			A = nA[ 1 ];
			B = nB[ 1 ];
		}
		mindist = min( combine( mindist, ( i + j ) >> 1, i, j, A, B ), mindist );
	} else {
		for( int k = i; k < j; k++ ) {
			for( int l = k + 1; l <= j; l++ ) {
				if( D( X[ k ], X[ l ] ) < mindist ) {
					mindist = D( X[ k ], X[ l ] );
					A = X[ k ];
					B = X[ l ];
				}
			}
		}
	}
	return mindist;
}
 
int main( void )
{
	scanf("%d", &N );
	pt A,B;
	for( int i = 0; i < N; i++ ) {
		scanf("%d%d", &X[ i ].x, &X[ i ].y );
		X[ i ].idx = i;
		Y[ i ] = X[ i ];
	}
	sort( X, X + N, cmpx );
	sort( Y, Y + N, cmpy );
	printf("%d %d %0.6lf\n", min( A.idx, B.idx ), max( A.idx, B.idx ), sqrt( findmin( 0, N - 1, A, B  ) ) );
	return 0;
}
