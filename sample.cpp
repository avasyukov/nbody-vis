#include "GLBall.hpp"
#include "NBodyScene.hpp"

#include <vector>

// Ваш класс для описания тела.
// Унаследован от GLBall, реализует его интерфейс с методами getX / getY / getR.
// (Для точечных тел внутри getR можете сделать возврат константы.)
class sample : public GLBall {
protected:
    double vx;
    double vy;
    double x;
    double y;
    double r;

public:
    // Конструктор *ваш* - что нужно, то в нём и получаете.
    // Копировать этот конструктор *не* надо.
    sample(double x, double y, double r, double vx, double vy)
            : x(x), y(y), r(r), vx(vx), vy(vy) {}

    // Ваши методы, никак не связанные с GLBall
    void move(double dt) {
        x += vx * dt;
        y += vy * dt;
    }

    // Реализация методов интерфейса на базе *ваших* переменных.
    // Переписывать всю свою реализацию под эти имена *не* надо.
    double getX() const override {
        return x;
    }
    double getY() const override {
        return y;
    }
    double getR() const override {
        return r;
    }
};

// Ваш класс сцены. В него де-факто превратится текущий main или его аналог.
// Унаследован от NBodyScene, реализует интерфейс с методами getNumberOfBodies / getBody / doTimeStep.
class SampleScene : public NBodyScene {
protected:
    std::vector<sample> bodies;

public:
    // Реализация методов интерфейса на базе *ваших* переменных

    unsigned int getNumberOfBodies() const override {
        return bodies.size();
    }

    const GLBall& getBody(unsigned int number) const override {
        return bodies.at(number);
    }

    void doTimeStep() override {
        for(sample& b : bodies)
            b.move(0.1);
    }

    // Далее ещё куча ваших методов, никак не связанных с NBodyScene

    void initScene() {
        bodies.push_back(sample(0, 0, 10, 1, 0));
        bodies.push_back(sample(15, 15, 1, 0, 1));
    }
};

// Функция, которая готовит всю сцену и возвращает готовый объект.
// Если нужно читать из файла и консоли, вызывать кучу методов - это здесь.
NBodyScene* getScene()
{
    SampleScene* s = new SampleScene();
    s->initScene();
    return s;
}

/*
// Ваш отладочный main
int main()
{
    // Создаём сцену
    SampleScene* scene = (SampleScene*)getScene();

    // Некая работа со сценой в рамках вашей отладки
    // for(...) {
    //     scene->doTimeStep();
    //     scene->whatever();
    // }

    // Удаляем сцену
    delete scene;

    return 0;
};
*/