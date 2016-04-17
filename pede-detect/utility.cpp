#include "utility.hpp"
namespace xutility{
	int average(vector<Point> li) {
		int length = li.size();
		int xAver(0);
		for (auto it = li.begin(); it != li.end(); ++it) {
			xAver += (*(it)).x;
		}
		return xAver / length;
	}
}