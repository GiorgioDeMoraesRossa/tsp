using namespace std;
class Vertice
{
  int x, y, num;

public:
  Vertice(int num, int x, int y);
  Vertice();
  int getX();
  int getY();
  void setX(int x);
  void setY(int y);
  int getNum();
};