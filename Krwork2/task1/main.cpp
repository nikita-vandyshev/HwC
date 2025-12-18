#include <cstddef>
#include <cstdlib>
#include <cstdio>


struct Vector
{
    void** data;
    std::size_t size;
    std::size_t capacity;
};

static const std::size_t INITIAL_CAPACITY = 4;

Vector* newVector()
{
    Vector* v = (Vector*)std::malloc(sizeof(Vector));
    if (v == nullptr)
    {
        return nullptr;
    }

    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
    return v;
}

static bool growVector(Vector* v)
{
    std::size_t newCapacity =
        (v->capacity == 0) ? INITIAL_CAPACITY : v->capacity * 2;

    void** newData = (void**)std::realloc(v->data,
                                         newCapacity * sizeof(void*));
    if (newData == nullptr)
    {
        return false;
    }

    v->data = newData;
    v->capacity = newCapacity;
    return true;
}

bool pushBack(Vector* v, void* element)
{
    if (v == nullptr)
    {
        return false;
    }

    if (v->size == v->capacity)
    {
        if (!growVector(v))
        {
            return false;
        }
    }

    v->data[v->size] = element;
    v->size++;
    return true;
}

void* atVector(const Vector* v, std::size_t index)
{
    if (v == nullptr || index >= v->size)
    {
        return nullptr;
    }

    return v->data[index];
}

void* getVector(const Vector* v, std::size_t index)
{
    return atVector(v, index);
}

std::size_t sizeVector(const Vector* v)
{
    return (v == nullptr) ? 0 : v->size;
}

void deleteVector(Vector* v)
{
    if (v == nullptr)
    {
        return;
    }

    std::free(v->data);
    std::free(v);
}


struct MyType
{
    int value;
};


int main()
{
    Vector* v = newVector();

    while (true)
    {
        int x;
        std::scanf("%d", &x);

        if (x == 0)
        {
            break;
        }

        MyType* obj = (MyType*)std::malloc(sizeof(MyType));
        obj->value = x;

        pushBack(v, (void*)obj);
    }

    for (std::size_t i = 0; i < sizeVector(v); i++)
    {
        MyType* obj = (MyType*)atVector(v, i);
        std::printf("%d ", obj->value);
        std::free(obj);
    }

    std::printf("\n");

    deleteVector(v);
    return 0;
}
