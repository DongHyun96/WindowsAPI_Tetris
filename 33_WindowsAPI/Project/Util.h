#pragma once

template <typename T>
static T GetRandom(const T& start, const T& end)
{
	if (start >= end)
		return (T)0;

	return start + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / (end - start)));
}
