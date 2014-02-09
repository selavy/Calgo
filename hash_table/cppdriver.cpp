#include <unordered_map>

using namespace std;

#define N 20000

int main( int argc, char ** argv )
{
  unordered_map<int, int> amap;

  for( int i = 0; i < N; ++i )
    {
      amap.emplace( i, i );
    }
  return 0;
}
