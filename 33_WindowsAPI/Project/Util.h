#pragma once

template <typename T>
static T GetRandom(const T& start, const T& end)
{
	if (start >= end)
		return (T)0;

	return start + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / (end - start)));
}

static double GetDeltaTime()
{
    static LARGE_INTEGER frequency = { 0 };
    static LARGE_INTEGER prevCounter = { 0 };

    if (frequency.QuadPart == 0)
    {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&prevCounter);
        return 0.0;
    }

    LARGE_INTEGER currentCounter;
    QueryPerformanceCounter(&currentCounter);

    double deltaTime = static_cast<double>(currentCounter.QuadPart - prevCounter.QuadPart) / frequency.QuadPart;
    prevCounter = currentCounter;

    return deltaTime;
}