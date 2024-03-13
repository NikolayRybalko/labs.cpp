#include <iostream>
#include <memory>

using namespace std;

// Объявление статических переменных для подсчета экземпляров
static int vectCount = 0;
static int matrCount = 0;

class vect {
public:
    int dim;
    unique_ptr<double[]> b;
    int num;
    static int count;

    vect(int dimension) : dim(dimension), b(new double[dimension]), num(++vectCount) {
        cout << "Vect #" << num << " created." << endl;
    }

    ~vect() {
        cout << "Vect #" << num << " destroyed." << endl;
    }

    vect(const vect& v) : dim(v.dim), b(new double[v.dim]), num(++vectCount) {
        for (int i = 0; i < dim; ++i) {
            b[i] = v.b[i];
        }
        cout << "Vect #" << num << " created by copying." << endl;
    }

    vect& operator=(const vect& v) {
        if (this == &v) return *this;
        dim = v.dim;
        b = unique_ptr<double[]>(new double[dim]);
        for (int i = 0; i < dim; ++i) {
            b[i] = v.b[i];
        }
        cout << "Vect #" << num << " assigned." << endl;
        return *this;
    }

    vect operator+(const vect& v) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] + v.b[i];
        }
        return result;
    }

    // Добавление других операторов (v-v, -v, v*v, k*v) по аналогии
};

// Инициализация статической переменной
int vect::count = 0;

class matr {
    // Аналогичное описание для класса матриц, включая операторы (m+m, m-m, -m, m*m, k*m, m=m, m*v)
};

int main() {
    // Сценарий использования векторов и матриц
    vect v1(3); // Создание вектора
    vect v2(3); // Создание другого вектора
    // Демонстрация операций над векторами и матрицами
    return 0;
}