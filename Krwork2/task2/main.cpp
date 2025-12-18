#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

struct Vector
{
    void** data;
    std::size_t size;
    std::size_t capacity;
    void (*deleter)(void*);
};

static const std::size_t INITIAL_CAPACITY = 4;

static bool reserveVector(Vector* vector, std::size_t newCapacity)
{
    if (vector == nullptr)
    {
        return false;
    }

    if (newCapacity <= vector->capacity)
    {
        return true;
    }

    void** newData = static_cast<void**>(std::realloc(vector->data, newCapacity * sizeof(void*)));
    if (newData == nullptr)
    {
        return false;
    }

    vector->data = newData;
    vector->capacity = newCapacity;
    return true;
}

static bool growVector(Vector* vector)
{
    std::size_t newCapacity = (vector->capacity == 0) ? INITIAL_CAPACITY : (vector->capacity * 2);
    return reserveVector(vector, newCapacity);
}

Vector* newVector()
{
    Vector* vector = static_cast<Vector*>(std::malloc(sizeof(Vector)));
    if (vector == nullptr)
    {
        return nullptr;
    }

    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    vector->deleter = nullptr;

    return vector;
}

void setVectorDeleter(Vector* vector, void (*deleter)(void*))
{
    if (vector == nullptr)
    {
        return;
    }

    vector->deleter = deleter;
}

std::size_t sizeVector(const Vector* vector)
{
    if (vector == nullptr)
    {
        return 0;
    }

    return vector->size;
}

bool pushBack(Vector* vector, void* element)
{
    if (vector == nullptr)
    {
        return false;
    }

    if (vector->size == vector->capacity)
    {
        if (!growVector(vector))
        {
            return false;
        }
    }

    vector->data[vector->size] = element;
    vector->size++;

    return true;
}

void* atVector(const Vector* vector, std::size_t index)
{
    if (vector == nullptr)
    {
        return nullptr;
    }

    if (index >= vector->size)
    {
        return nullptr;
    }

    return vector->data[index];
}

void* getVector(const Vector* vector, std::size_t index)
{
    return atVector(vector, index);
}

void deleteVector(Vector* vector)
{
    if (vector == nullptr)
    {
        return;
    }

    if (vector->deleter != nullptr)
    {
        for (std::size_t i = 0; i < vector->size; i++)
        {
            vector->deleter(vector->data[i]);
        }
    }

    std::free(vector->data);
    std::free(vector);
}

typedef struct
{
    std::size_t id;
    double latitude;
    double longitude;
    std::uint8_t signal;
} NavPoint;

static void freeNavPoint(void* p)
{
    std::free(p);
}

static NavPoint* copyNavPoint(const NavPoint* src)
{
    if (src == nullptr)
    {
        return nullptr;
    }

    NavPoint* dst = static_cast<NavPoint*>(std::malloc(sizeof(NavPoint)));
    if (dst == nullptr)
    {
        return nullptr;
    }

    *dst = *src;
    return dst;
}

Vector* filterReliablePoints(const Vector* points, std::uint8_t minSignal)
{
    Vector* reliablePoints = newVector();
    if (reliablePoints == nullptr)
    {
        return nullptr;
    }

    setVectorDeleter(reliablePoints, freeNavPoint);

    if (points == nullptr || sizeVector(points) == 0)
    {
        return reliablePoints;
    }

    std::size_t n = sizeVector(points);
    for (std::size_t i = 0; i < n; i++)
    {
        const NavPoint* point = static_cast<const NavPoint*>(atVector(points, i));
        if (point == nullptr)
        {
            continue;
        }

        if (point->signal >= minSignal)
        {
            NavPoint* pointCopy = copyNavPoint(point);
            if (pointCopy == nullptr)
            {
                deleteVector(reliablePoints);
                return nullptr;
            }

            if (!pushBack(reliablePoints, pointCopy))
            {
                std::free(pointCopy);
                deleteVector(reliablePoints);
                return nullptr;
            }
        }
    }

    return reliablePoints;
}

void analyzeReliablePoints(const Vector* reliablePoints)
{
    if (reliablePoints == nullptr || sizeVector(reliablePoints) == 0)
    {
        std::printf("No reliable points to analyze.\n");
        return;
    }

    std::size_t n = sizeVector(reliablePoints);

    std::uint32_t sumSignal = 0;
    const NavPoint* bestPoint = static_cast<const NavPoint*>(atVector(reliablePoints, 0));

    for (std::size_t i = 0; i < n; i++)
    {
        const NavPoint* p = static_cast<const NavPoint*>(atVector(reliablePoints, i));
        if (p == nullptr)
        {
            continue;
        }

        sumSignal += p->signal;

        if (bestPoint == nullptr || p->signal > bestPoint->signal)
        {
            bestPoint = p;
        }
    }

    double averageSignal = static_cast<double>(sumSignal) / static_cast<double>(n);

    std::printf("Reliable points count: %zu\n", n);
    std::printf("Average signal: %.2f\n", averageSignal);

    if (bestPoint != nullptr)
    {
        std::printf("Best point id: %zu\n", bestPoint->id);
    }
}

int main()
{
    Vector* points = newVector();
    setVectorDeleter(points, freeNavPoint);

    for (std::size_t i = 0; i < 5; i++)
    {
        NavPoint* p = (NavPoint*)std::malloc(sizeof(NavPoint));
        p->id = i;
        p->latitude = 55.0 + i;
        p->longitude = 37.0 + i;
        p->signal = (std::uint8_t)(200 + i * 10);

        pushBack(points, p);
    }

    Vector* reliable = filterReliablePoints(points, 220);
    analyzeReliablePoints(reliable);

    deleteVector(reliable);
    deleteVector(points);

    return 0;
}
