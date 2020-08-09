#include <vector>
#include "ball.h"
class Table
{
	Ball balls[16];
 //Sadrzace verovatno lopte, stapove, i potrebne stvari za animaciju.

public:
	Table();
	void start();
	void draw();
};